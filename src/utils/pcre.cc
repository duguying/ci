#include "pcre.hh"

Regex::Regex(){
	this->code=NULL;
	this->rc=0;
	this->errptr=NULL;
	this->erroffet=-1;

	memset(this->ovector,-1,2);
	memset(this->pos,-1,2);
}
Regex::~Regex(){
	if (this->code!=NULL)
	{
		free(this->code);
		this->code=NULL;
	}
}

bool Regex::compile(const char* regex){
	this->code=pcre_compile(regex,0,&this->errptr,&this->erroffet,NULL);
	if (this->code!=NULL)
	{
		return true;
	}else{
		return false;
	}
}

int Regex::exec(const char* str){
	unsigned int len=strlen(str);
	this->rc=pcre_exec(code,NULL,str,len,0,0,this->ovector,2);
	if (this->rc<=0)
	{
		return -1;
	}else{
		return this->rc;
	}
}

unsigned int* Regex::get_substring_pos(){
	if (this->ovector<=0)
	{
		return NULL;
	}else{
		this->pos[0]=this->ovector[0];		// start
		this->pos[1]=this->ovector[1]-this->ovector[0];		// length
		return this->pos;
	}
}
