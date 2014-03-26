#include "socket.hh"

Socket::Socket(string addr, int port){
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
}

Socket::~Socket(){}

int Socket::listening(){
    int op_ret=0;

    op_ret = bind(this->listen_socket, (struct sockaddr*)&this->serv_addr, sizeof(this->serv_addr));
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
            cout<<"Connected!\n";
        }
        cout<<"OK!";
    }
};
