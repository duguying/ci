#include "thread.hh"

Thread::Thread(DWORD WINAPI fun(LPVOID)){
	this->hook=&fun;	//成功将函数传入对象
}

Thread::~Thread(){}

bool Thread::go(){
	HANDLE hthrd;
	hthrd=CreateThread(
		NULL,
		0,
		*this->hook,
		NULL,
		0,
		&this->tid);

	if (hthrd==NULL)
	{
		cerr<<"CreateThread Error:"+GetLastError();
		ExitProcess(0);
	}else{
		return true;
	}
}

DWORD Thread::get_tid(){
	return this->tid;
}
