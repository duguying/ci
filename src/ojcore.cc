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

void father(){
	cout<<"father, hello world!\n";

	// Exec ex;
	// string result=ex.execute("ping www.baidu.com");
	// cout<<result<<endl;
	
	
	
	while(true){
		Sleep(1);
	}
}

void son(){
	// cout<<"son, hello world!\n";
	
	Exec ex;
	string result=ex.execute("ping www.baidu.com");
	cout<<result<<endl;

	// Socket ts("127.0.0.1",107);
	// ts.dealmsg=deal_msg;
	// ts.start();
	
	while(true){
		Sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	if (argc<=1)
	{
		// Process::pfork(father,son);
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


	

	
	
	

	return 0;
}




