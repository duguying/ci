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
	Socket ts("127.0.0.1",107);
	ts.dealmsg=deal_msg;
	ts.start();

	/**
	 * 创建进程，【编译测试】进程与【网络通讯】进程之间
	 * 通讯，当网络通讯进程发现【编译测试】正在处理当前
	 * 任务，则两者之间建立通讯关系。由【编译测试】进程
	 * 向【网络通讯】进程发送消息，若当前用户不存在【网
	 * 络通讯】进程，则消息[编译结果]保存
	 */

	while(1){
		Sleep(1);
	}
	
	Exec ex;
	string result=ex.execute("ping www.baidu.com");
	cout<<result<<endl;

	return 0;
}




