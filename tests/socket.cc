#pragma warning(disable : 4786)

#include <iostream>
#include <string>
#include "websocket/socket.hh"
#include "websocket/thread.hh"
#include "websocket/encrypt.hh"
#include "regex++/regex.hh"
#include <assert.h>

using namespace std;

int main(int argc, char const *argv[])
{
	Socket ts("127.0.0.1",107);
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




