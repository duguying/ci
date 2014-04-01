#include "socket.hh"
#include "thread.hh"


THR_HOOK(listening_hook, arg){
    Socket* skt=Socket::pointer_to_socket(arg);
    skt->listening();
    THR_HOOK_END();
}

Socket::Socket(string addr, int port){
    memset(this->buffer,0,BUFFER_LEN);

	int result=0;
	result=WSAStartup(MAKEWORD(2,2),&(this->wsa_data));
	if (result!=0)
	{
		cerr<<"WSAStartup Error:"<<GetLastError()<<endl;
		throw "WSAStartup Error:"+GetLastError();
	}

	//Create Socket
    this->listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( listen_socket == INVALID_SOCKET )
    {
        cerr<<"Create Socket Failed::"<<GetLastError()<<endl;
        throw "Create Socket Failed::"+GetLastError();
    }

    memset(this->serv_addr.sin_zero, 0, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = inet_addr(addr.c_str());
    this->serv_addr.sin_port = htons(port);

    dealmsg=NULL;
}

Socket::~Socket(){}

int Socket::start(){
    Thread listen_thr(listening_hook, this);

    if(listen_thr.go()){
        cout<<"client thread id: "<<listen_thr.get_tid()<<endl;
    };

    return 0;
}

THR_HOOK(receiving_hook, arg){
    int rev_rst;
    Websocket wsp; // Websocket

    Socket* skt=Socket::pointer_to_socket(arg);

    SOCKET recv_skt=skt->client_socket;

    while(true){
        memset(skt->buffer,0,BUFFER_LEN);
        rev_rst=recv(
            recv_skt,
            skt->buffer,
            BUFFER_LEN-1,
            0);
        if (rev_rst>0){
            if(skt->dealmsg==NULL){
                cout<<"Respnose Handler Function Dose Not Exist!\n";
            }else{
                if(-1==skt->dealmsg(skt->buffer,recv_skt,&wsp)){
                    cout<<"status: client request close!"<<endl;
                    return 0;
                }
            }
        }else if(rev_rst==0){
            cout<<"status: closed!"<<endl;
            return 0;
        }else{
            cerr<<"Recv Error: "<<GetLastError()<<endl;
            return -1;
        }
    }
}

int Socket::listening(){
    int op_ret=0;

    op_ret = bind(
        this->listen_socket, 
        (struct sockaddr*)&this->serv_addr, 
        sizeof(this->serv_addr));

    if ( op_ret != 0 )
    {
        cerr<<"Bind Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }
    
    op_ret = listen(this->listen_socket, 10);
    if ( op_ret != 0 )
    {
        cerr<<"listen Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }
    while(1){
        this->client_socket=accept(this->listen_socket,NULL,NULL);
        if (INVALID_SOCKET==this->client_socket)
        {
            cerr<<"Connect Failed!\n";
        }else{
            //start recv
            Thread rev_thr(receiving_hook, this);
            if(rev_thr.go()){
                // cout<<"Thread id: "<<rev_thr.get_tid()<<" Connected!"<<endl;
            };
        }
    }
};

int Socket::send_msg(SOCKET skt, char* message, int len){
    char send_buffer[BUFFER_LEN*2];

    memset(send_buffer, 0, 2*BUFFER_LEN*sizeof(char));
    memcpy(send_buffer, message, len);

    int send_rst=send(skt,
        send_buffer,
        len,
        0);

    return send_rst;
}

Socket* Socket::pointer_to_socket(LPVOID arg){
    return ((Socket*)arg);
}
