#include "websocket.hh"

Websocket::Websocket(){
	this->shaked_hands=false;
	memset(this->header,0,sizeof(ojs_table_item)*20);
	this->message="";
}

Websocket::~Websocket(){
	free(this->header_content);
}

unsigned char Websocket::frame_def[22][2]={
	{0x00,0x7f},    {0x01,0x7f},    {0x02,0x7f},    {0x03,0x7f},   {0x04,0x7f},   {0x05,0x7f},   {0x06,0x7f},   {0x07,0x7f},   {0x08,0x00},    {0x09,0x00},    {0x0a,0x00},        /* 非尾帧 */
    /* 0附加数据,   1文本数据,      2二进制数据,    3未定义        4未定义        5未定义        6未定义        7未定义        8连接关闭,      9ping,          10pong                        */
	{0x80,0x7f},    {0x81,0x7f},    {0x82,0x7f},    {0x83,0x7f},   {0x84,0x7f},   {0x85,0x7f},   {0x86,0x7f},   {0x87,0x7f},   {0x88,0x00},    {0x89,0x00},    {0x8a,0x00}         /* 尾  帧 */
};

char* Websocket::key="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

bool Websocket::response_gather(char* response){
	unsigned char frame_header_1=response[0];
	unsigned char frame_header_2=response[1];

	if (
		((Websocket::frame_def[8][1]==frame_header_1)   &&   (Websocket::frame_def[8][2]==frame_header_1)) || \
		((Websocket::frame_def[19][1]==frame_header_1)  &&   (Websocket::frame_def[19][2]==frame_header_1)) 
		) // 关闭
	{
		cout<<"operat closed!\n";
		return false;
	}else if (
		((Websocket::frame_def[1][1]==frame_header_1)   &&   (Websocket::frame_def[1][2]==frame_header_1))
		) // 0x00 文本 非尾帧
	{
		this->message+=*(response+2);
		cout<<"operat fragm: "<<*(response+2)<<"\n";
		return false;
	}else if (
		((Websocket::frame_def[12][1]==frame_header_1)  &&   (Websocket::frame_def[12][2]==frame_header_1)) 
		) // 0x80 文本 尾帧
	{
		this->message+=*(response+2);
		cout<<"operat msg: "<<this->message<<endl;
		// return this->message;
		return true;
	}else{
		// printf("%p\t%p\n", frame_header_1, frame_header_2);
		// cout<<response<<endl;
		return true;
	}

	return false;
}

bool Websocket::shakehands(char* response){
	if (response[128]!=0)
	{
		this->message+=response;
		return false;
	}else{
		this->message+=response;
		this->shaked_hands=true;
		{
			// 处理头信息
			this->header_parser(this->message.c_str());
		}
		return true;
	}
}

bool Websocket::header_parser(const char* ws_header){
	unsigned int len=strlen(ws_header);
	unsigned int buf_size=len+1;
	bool str_head=true;
	bool break_flag=false;
	unsigned j=0;

	this->header_content=(char*)malloc(buf_size*sizeof(char));
	memset(this->header_content,0,buf_size);
	strncpy(this->header_content,ws_header,len);

	for (int i = 0; i < len; ++i)
	{
		if (str_head)
		{
			// mark i as head
			// cout<<"mark "<<i<<" as head"<<endl;
			this->header[j].key=this->header_content+i; // key
			str_head=false;
		}else if (((char)(*(ws_header+i)))==':' && !break_flag)
		{
			// cout<<"mark "<<i<<" as break"<<endl;
			this->header[j].value=this->header_content+i+1; // value
			this->header_content[i]=0; // 敲除:
			break_flag=true;
		}else if (((char)(*(ws_header+i)))=='\n'){ //tail
			// mark i as tail
			str_head=true;
			// cout<<"mark "<<i<<" as tail"<<endl;
			this->header_content[i]=0; // 敲除换行符
			j++;
			break_flag=false;
		}else if (((char)(*(ws_header+i)))=='\r')
		{
			this->header_content[i]=0;
		}
	}

	RegEx re;
	re.Compile("Sec-WebSocket-Key");

	for (int k = 0; k < 20; ++k)
	{
		char* request_key=this->header[k].key;

		if (re.Match(request_key))
		{
			int len=strlen(this->header[k].value);
			for (int i = 0; i < len+1; ++i)
			{
				if (this->header[k].value[i]==' ')
				{
					this->header[k].value++;
				}else{
					break;
				}
			}

			string key_appended=Websocket::key;
			char request_key_char_buffer[50];
			
			memset(request_key_char_buffer,0,50);
			strncpy(request_key_char_buffer,this->header[k].value,strlen(this->header[k].value));
			strcat(request_key_char_buffer,key_appended.c_str());
			string after_encode=base64_encode(sha1_decimal(request_key_char_buffer));
			this->handshake_response="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+after_encode+"\r\n\r\n";
			return true;
			// break;
		}

	}

	return false;
}
