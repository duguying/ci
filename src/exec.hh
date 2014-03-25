#include <iostream>
#include <string>
#include "windows.h"
#include "tchar.h"

using namespace std;

#define MAX_PATH_LENGTH 1024

namespace ojs{
	class Exec
	{
	public:
		Exec(){};
		~Exec(){};

		string execute(string cmd);
	
		/* data */
	};
}