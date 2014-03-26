#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Socket
{
private:
	WSADATA wsa_data;
	SOCKET listen_socket;
	SOCKET server_socket;
	struct sockaddr_in serv_addr;
public:
	Socket(string, int);
	~Socket();

	/* data */
};