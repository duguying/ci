#ifndef _OJSERVER_WEBSOCKET_HH_
#define _OJSERVER_WEBSOCKET_HH_

#include <iostream>

using namespace std;

class Websocket
{
public:
	/// 基本帧缓冲区长度4
	static unsigned int base_frame_buf_len;
	static unsigned char frame_def[22][2];
	static char* key;

	Websocket();
	~Websocket();

	/* data */
};

#endif
