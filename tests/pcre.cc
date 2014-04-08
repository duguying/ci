// #define PCRE_STATIC

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "utils/pcre.hh"

int main(int argc, char const *argv[])
{
	unsigned int* pos;
	char* tmp=NULL;
	char* src="hey, hello world! wo shi li jun.";
	Regex regtest;
	regtest.compile("wo[^ ]");
	regtest.exec(src);
	pos=regtest.get_substring_pos();
	printf("start:%d\tlength:%d\n", pos[0], pos[1]);
	tmp=(char*)malloc(pos[1]+1);
	memset(tmp,0,pos[1]+1);
	strncpy(tmp,src+pos[0],pos[1]);
	printf("substring:%s\n", tmp);
 
	return 0;
}
