#include <iostream>
#include "windows.h"
#include "windef.h"

using namespace std;

/**
 * fun为hook函数的函数名，必须，其命名遵循函数名命名规则
 */
#define THR_HOOK(fun)	DWORD WINAPI fun(LPVOID) 	//hook函数简写方式
/**
 * hook函数的结尾方式
 */
#define THR_HOOK_END()	{return NULL;}

class Thread
{
private:
	DWORD (WINAPI *hook)(LPVOID);
	DWORD tid;
public:
	Thread(DWORD WINAPI fun(LPVOID));
	~Thread();

	bool go();
	DWORD get_tid();

};
