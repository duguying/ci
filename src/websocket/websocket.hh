#ifndef _OJSERVER_WEBSOCKET_HH_
#define _OJSERVER_WEBSOCKET_HH_

#include <iostream>
#include <string>

#pragma warning(disable : 4786)

#include "regex++/regex.hh"
#include "websocket/encrypt.hh"

using namespace std;

typedef struct _ojs_table_item
{
	char* key;
	char* value;
} ojs_table_item;

class Websocket  
{
public:
	static unsigned char frame_def[22][2];
	static char* key;

	/// 聚合后的信息
	string message;

	/// 是否已经握手
	bool shaked_hands;
	/// 握手返回信息
	string handshake_response;
	/// 当前连接的头部信息
	ojs_table_item header[20];

	char* header_content;



	Websocket();
	~Websocket();

	/**
	 * 解析帧 聚合帧为信息
	 * @param  response [description]
	 * @return          [description]
	 */
	bool response_gather(char* response);

	/**
	 * 握手 解析头部
	 * @param  response [description]
	 * @return          [description]
	 */
	bool shakehands(char* response);

	bool header_parser(const char* header);

	/* data */
};

#endif
