#include "encrypt.hh"

string sha1_decimal(const char* message){
	SHA1        sha;
    unsigned    message_digest[5];

    sha.Reset();
    sha << message;

    if (!sha.Result(message_digest))
    {
        cerr << "ERROR-- could not compute message digest" << endl;
        return NULL;
    }else{
    	string buffer="";
    	unsigned int tmp;

	    for(int i = 0; i < 5 ; i++){
	        string inner_buffer="";
	        char stmp[10];
	        sprintf(stmp,"%p",message_digest[i]);
	        tmp=message_digest[i];
	        for (int j = 0; j < 4; ++j){
	            char c=tmp&0x000000ff;
	            inner_buffer=c+inner_buffer;
	            tmp=tmp>>8;
	        }
	        buffer=buffer+inner_buffer;
	    }
	    return buffer;
	}
}

string base64_encode(const string& input){
    ulong size = Base64::getEncodedSize(input.length()) + 1;
    
    char * buffer = new char[size];
    buffer[size - 1] = '\0';
    
    Base64::encodeBuffer(reinterpret_cast<const byte *>(input.c_str()), buffer, input.length());
    
    std::string result(buffer);
    delete [] buffer;
    
    return result;
}
