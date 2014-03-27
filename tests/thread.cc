#include "websocket/thread.hh"

using namespace std;

THR_HOOK(test){
	cout<<"hello world!\n";
	THR_HOOK_END();
}

int main(int argc, char const *argv[])
{
	Thread tt(test);
	if(tt.go()){
		cout<<tt.get_tid()<<endl;
	};

	while(1){
		Sleep(1);
	}
	return 0;
}
