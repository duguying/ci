#ifndef _OJSERVER_THREAD_HH_
#define _OJSERVER_THREAD_HH_

#include <iostream>
#include "windows.h"
#include "windef.h"

using namespace std;

/**
 * fun为hook函数的函数名，必须，其命名遵循函数名命名规则
 */
#define THR_HOOK(fun, arg)	DWORD WINAPI fun(LPVOID arg) 	//hook函数简写方式
/**
 * hook函数的结尾方式
 */
#define THR_HOOK_END()	{return NULL;}

class Thread
{
private:
	DWORD (WINAPI *hook)(LPVOID);
	DWORD tid;
	LPVOID arg;
public:
	Thread(DWORD WINAPI fun(LPVOID), LPVOID arg);
	~Thread();

	bool go();
	DWORD get_tid();

};

#endif
