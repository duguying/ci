#include <iostream>
#include "windows.h"

using namespace std;

/**
 * fun为hook函数的函数名，必须，其命名遵循函数名命名规则
 */
#define THR_HOOK(fun) void fun() 	//hook函数简写方式

class Thread
{
private:
	void (*hook)(void);
public:
	Thread(void fun(void));
	~Thread();

	void go();

};
