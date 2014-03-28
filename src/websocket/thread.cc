#include "thread.hh"

Thread::Thread(DWORD WINAPI fun(LPVOID), LPVOID arg){
	this->hook=&fun;	//成功将函数传入对象
	this->arg=arg;
}

Thread::~Thread(){}

bool Thread::go(){
	HANDLE hthrd;
	hthrd=CreateThread(
		NULL,
		0,
		*this->hook,
		this->arg,
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
