#include "exec.hh"

using namespace ojs;

#if defined _WIN32  //Windows

Exec::Exec(){}

Exec::~Exec(){}

string Exec::execute(string cmd){
    char buffer[MAX_PATH_LENGTH] = {0};                                  //保存命令行输出   

    DWORD bytesRead = 0;  
    SECURITY_ATTRIBUTES sa = {0};                                              
    HANDLE hRead = NULL, hWrite = NULL;                                  //设置管道读写句柄   
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);    
    sa.lpSecurityDescriptor = NULL;    
    sa.bInheritHandle = TRUE;    
    if (!CreatePipe(&hRead, &hWrite, &sa,0)){//创建管道  
        cout<<"CreatePipe Error: "<<GetLastError()<<endl;
        return NULL;
    }    
    STARTUPINFO si = {0};    
    PROCESS_INFORMATION pi = {0};    
    si.cb = sizeof(STARTUPINFO);    
    GetStartupInfo(&si);   
    si.hStdError = hWrite; 
    si.hStdOutput = hWrite; 
    si.wShowWindow = SW_HIDE;    
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;   
	
    cmd="cmd.exe /C "+cmd;
    char* cmdstring=(char*)cmd.c_str();
    if (!CreateProcess(NULL,
					cmdstring, 
					NULL, 
					NULL, 
					true, 
					NULL, 
					NULL, 
					NULL,
					&si,
					&pi)){
		cout<<"Create Process Error: "<<GetLastError()<<endl;
		cout<<"Execute: ["<<cmdstring<<"] failed!"<<endl;
        CloseHandle(hWrite);   
        CloseHandle(hRead);   
        return NULL;   
    }    
    // WaitForSingleObject(pi.hProcess,INFINITE);                         //等待进程结束   
         
    CloseHandle(pi.hProcess);                                          //关闭新进程的主线程   
    CloseHandle(pi.hThread);										   //关闭新进程   
    CloseHandle(hWrite);                                               //关闭管道的写句柄   
    for (;;)
    {
        memset(buffer,0,MAX_PATH_LENGTH);
        if(0==ReadFile(hRead, buffer, MAX_PATH_LENGTH, &bytesRead, NULL)){        //从管道中读取 运行结果   
            break;
            }
        cout<<buffer;
    }
    
    CloseHandle(hRead);                                                //关闭管道的读句柄   
    
    return buffer;   
}

#else   // Unix, Linux, MacOS

string Exec::execute(string cmd){   
    char buf_ps[1024];
    string buffer="";
    FILE *ptr;

    if((ptr=popen(cmd.c_str(), "r"))!=NULL){
        while(fgets(buf_ps, 1024, ptr)!=NULL){  
           buffer=buffer+buf_ps; 
        }   
        pclose(ptr);
        ptr = NULL;   
    }else{
        cout<<"popen "<<cmd<<" error"<<endl;
        return NULL;
    }  
    return buffer; 
}

#endif
