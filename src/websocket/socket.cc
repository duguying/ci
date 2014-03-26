#include "socket.hh"

Socket::Socket(string addr, int port){
	int result=0,op_ret=0;
	result=WSAStartup(MAKEWORD(2,2),&(this->wsa_data));
	if (result!=0)
	{
		cout<<"WSAStartup Error:"<<GetLastError()<<endl;
		return ;
	}

	//Create Socket
    this->listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( listen_socket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        return ;
    }

    memset(this->serv_addr.sin_zero, 0, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = inet_addr(addr.c_str());
    this->serv_addr.sin_port = htons(port);

    //Bind Socket
    op_ret = bind(this->listen_socket, (struct sockaddr*)&this->serv_addr, sizeof(this->serv_addr));
    if ( op_ret != 0 )
    {
		cout<<"Bind Socket Failed::"<<GetLastError()<<endl;
		return ;
    }
    
    op_ret = listen(this->listen_socket, 10);
    if ( op_ret != 0 )
    {
        cout<<"listen Socket Failed::"<<GetLastError()<<endl;
        return ;
    }

    printf("%s\n", "hello");
}

Socket::~Socket(){}
