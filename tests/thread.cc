#include "websocket/thread.hh"

using namespace std;

THR_HOOK(test){
	cout<<"hello world!\n";
}

int main(int argc, char const *argv[])
{
	/* code */

	Thread tt(test);
	tt.go();
	return 0;
}
