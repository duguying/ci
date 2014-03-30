#ifndef _OJSERVER_SOCKET_HH_
#define _OJSERVER_SOCKET_HH_

#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

#define BUFFER_LEN 129

class Socket
{
private:
	WSADATA wsa_data;
	SOCKET listen_socket;
	
	struct sockaddr_in serv_addr;
	
public:
	Socket(string, int);
	~Socket();

	SOCKET client_socket;
	char buffer[BUFFER_LEN];

	/**
	 * 持续监听来自客户端的连接
	 * @return [连接状态-1失败]
	 */
	int listening();

	/**
	 * 启动socket
	 * @return [description]
	 */
	int start();

	/**
	 * 处理信息函数指针
	 */
	int (*dealmsg)(char*,SOCKET);
	
	/**
	 * 向客户端发送信息
	 * @return [description]
	 */
	static int send_msg(SOCKET skt, char* buffer, int len);

	/**
	 * 将空指针强制转换为Socket*
	 * @param  LPVOID [空指针]
	 * @return        [返回Socket指针]
	 */
	static Socket* pointer_to_socket(LPVOID);

	/* data */
};

#endif
