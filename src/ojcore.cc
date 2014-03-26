#include "ojcore.hh"

#include "executer/exec.hh"

using namespace ojs;

int main(int argc, char const *argv[])
{
	/* code */
	Exec ex;
	string result=ex.execute("ping www.baidu.com");
	cout<<result<<endl;
	return 0;
}

