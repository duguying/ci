#pragma warning(disable : 4786)

#include <iostream>
#include <string>
#include "websocket/socket.hh"
#include "websocket/thread.hh"
#include "websocket/encrypt.hh"
#include "regex++/regex.hh"
#include <assert.h>

using namespace std;



int test_deal_msg(char* response, SOCKET sid, void* websocket){
	Websocket* wsp=(Websocket*)websocket;
	if (wsp->shaked_hands==false)
	{
		if(wsp->shakehands(response)){
			int dec;
			string skhmsg=wsp->handshake_response;
			dec=Socket::send_msg(sid, ((char* )skhmsg.c_str()), skhmsg.length());
			// cout<<"result"<<dec<<endl;
			dec=Socket::send_msg(sid, "\x81\x7fhi!", 8);
			// cout<<"result"<<dec<<endl;
		}
	}else{
		cout<<"recvd: "<<response<<endl;
		// string message=wsp.response_gather(response);
		// if(""!=message){
			// cout<<"Socket ID: "<<sid<<"\nResponse: "<<message<<endl;
		// }
	}
	// Socket::send_msg(sid,"ok!",4);
	return 0;
}

int main(int argc, char const *argv[])
{
	Socket ts("127.0.0.1",107);
	ts.dealmsg=test_deal_msg;
	ts.start();

	RegEx re;
	re.Compile("(a|b)*");
	bool match;
	assert (true == (match = re.Match("a")));
	assert (true == (match = re.Match("b")));
	assert (true == (match = re.Match ("aa")));
	assert (true == (match = re.Match ("ab")));

	while(1){
		Sleep(1);
	}
	


	return 0;
}




