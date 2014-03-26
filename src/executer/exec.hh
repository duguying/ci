#include <iostream>
#include <string>

#ifndef _OJ_EXEC_HH_
#define _OJ_EXEC_HH_ 

#if defined _WIN32
	#include "windows.h"
	#include "tchar.h"
#else
	#include "stdio.h"
#endif

using namespace std;

#define MAX_PATH_LENGTH 1024

namespace ojs{
	class Exec
	{
	public:
		Exec();
		~Exec();

		string execute(string);
	
		/* data */
	};
}

#endif
