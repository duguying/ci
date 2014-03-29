#include <iostream>
#include <string>
#include "sha1/sha1.hh"
#include "base64/base64.hh"

using namespace std;

/**
 * sha1加密，返回十进制字符串
 * @param  message 待加密串
 * @return         加密后的串
 */
string sha1_decimal(const char* message);

/**
 * base64加密
 * @param  input 输入串
 * @return       加密后的串
 */
string base64_encode(const string& input);
