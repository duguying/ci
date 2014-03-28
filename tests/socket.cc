#include <iostream>
#include <string>
#include "websocket/socket.hh"
#include "websocket/thread.hh"

using namespace std;

THR_HOOK(thread_fun, arg){
	Socket::pointer_to_socket(arg)->listening();
	THR_HOOK_END();
}

int main(int argc, char const *argv[])
{
	Socket ts("127.0.0.1",107);

	Thread tt(thread_fun, &ts);

	if(tt.go()){
		cout<<tt.get_tid()<<endl;
	};

	while(1){
		Sleep(1);
	}

	return 0;
}