#ifndef _OJSERVER_WEBSOCKET_HH_
#define _OJSERVER_WEBSOCKET_HH_

#include <iostream>
#include "socket.hh"

using namespace std;

class Websocket : Socket 
{
public:
	/// 基本帧缓冲区长度4
	static unsigned int base_frame_buf_len;
	static unsigned char frame_def[22][2];
	static char* key;

	Websocket(string, int);
	~Websocket();

	/* data */
};

#endif
