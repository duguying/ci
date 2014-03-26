#include <iostream>
#include "websocket/socket.hh"

using namespace std;

int main(int argc, char const *argv[])
{
	Socket ts("127.0.0.1",107);
	ts.listening();
	return 0;
}