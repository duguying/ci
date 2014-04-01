#include <iostream>
#include <string>
#include "websocket/socket.hh"
#include "websocket/thread.hh"
#include "websocket/encrypt.hh"
#include "regex++/regex.hh"
#include <assert.h>

using namespace std;



int deal_msg(char* response, SOCKET sid, void* websocket){
	Websocket* wsp=(Websocket*)websocket;
	if (wsp->shaked_hands==false)
	{
		if(wsp->shakehands(response)){
			int dec;
			string skhmsg=wsp->handshake_response;
			dec=Socket::send_msg(sid, ((char* )skhmsg.c_str()), skhmsg.length());
			
		}
	}else{ // ready, send contents now!
		
		///
		
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	Socket ts("127.0.0.1",107);
	ts.dealmsg=deal_msg;
	ts.start();


	while(1){
		Sleep(1);
	}
	


	return 0;
}




