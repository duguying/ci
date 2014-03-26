#include "thread.hh"

Thread::Thread(void fun(void)){
	this->hook=&fun;	//成功将函数传入对象
}

Thread::~Thread(){}

void Thread::go(){
	(*this->hook)();
}

