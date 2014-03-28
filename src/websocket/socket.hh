#ifndef _OJSERVER_SOCKET_HH_
#define _OJSERVER_SOCKET_HH_

#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Socket
{
private:
	WSADATA wsa_data;
	SOCKET listen_socket;
	SOCKET client_socket;
	struct sockaddr_in serv_addr;
public:
	Socket(string, int);
	~Socket();

	/**
	 * 持续监听来自客户端的连接
	 * @return [连接状态-1失败]
	 */
	int listening();
	/**
	 * 持续监听来自客户端的信息
	 * @return [description]
	 */
	int receiving();
	/**
	 * 向客户端发送信息
	 * @return [description]
	 */
	int send();

	/**
	 * 将空指针强制转换为Socket*
	 * @param  LPVOID [空指针]
	 * @return        [返回Socket指针]
	 */
	static Socket* pointer_to_socket(LPVOID);

	/* data */
};

#endif
