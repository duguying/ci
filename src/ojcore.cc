#include "ojcore.hh"

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
		
		if (0x08==(response[0]&0x0f))
		{
			return -1; // request close
		}
		
		///
		
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	if (argc<=1)
	{
		cout<<"show help\n";
	}else{// may =2
		if (!strcmp(argv[1],"start"))
		{
			cout<<"start as server\n";
		}else if (!strcmp(argv[1],"compiler"))
		{
			if (argc<3)
			{
				cout<<"need task file\n";
			}else{
				cout<<"compiler work for task: "<<argv[2]<<"\n";
			}
		}else{
			cout<<"unknow args\n";
		}
	}


	// Socket ts("127.0.0.1",107);
	// ts.dealmsg=deal_msg;
	// ts.start();

	

	// while(1){
	// 	Sleep(1);
	// }
	
	// Exec ex;
	// string result=ex.execute("ping www.baidu.com");
	// cout<<result<<endl;

	return 0;
}




