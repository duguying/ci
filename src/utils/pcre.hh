#define PCRE_STATIC

#include "pcre/pcre.h"
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

	/**
	 * 通过正则表达式编译PCRE模式
	 * @param  regex 正则表达式
	 * @return       编译是否成功
	 */
	bool compile(const char* regex);

	/**
	 * 执行编译好的模式进行匹配
	 * @param  str 待匹配串
	 * @return     匹配结果，-1失败
	 */
	int exec(const char* str);
	
	/**
	 * 获取子串起始位置及长度
	 * @return 起始位及长度数组
	 */
	unsigned* get_substring_pos();

	/* data */
};
