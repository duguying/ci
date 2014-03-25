#include "ojserver.hh"

#include "exec.hh"

using namespace ojs;

int main(int argc, char const *argv[])
{
	/* code */
	Exec ex;
	string result=ex.execute("echo hello world");
	cout<<result<<endl;
	return 0;
}

