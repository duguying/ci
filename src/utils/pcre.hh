#define PCRE_STATIC

#include "pcre.h"
#include "iostream"

using namespace std;

class Regex
{
private:
	pcre *code;
	int ovector[2];
	unsigned int pos[2];
	int rc;
	const char *errptr;
	int erroffet;

public:
	Regex();
	~Regex();

	bool compile(const char* regex);
	int exec(const char* str);
	unsigned* get_substring_pos();

	/* data */
};
