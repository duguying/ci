#include "exec.hh"

using namespace ojs;

string Exec::execute(string cmd){
    char buffer[MAX_PATH_LENGTH] = {0};       //保存命令行输出   

    DWORD bytesRead = 0;  
    SECURITY_ATTRIBUTES sa = {0};                                              
    HANDLE hRead = NULL, hWrite = NULL;                                  //设置管道读写句柄   
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);    
    sa.lpSecurityDescriptor = NULL;    
    sa.bInheritHandle = TRUE;    
    if (!CreatePipe(&hRead, &hWrite, &sa,0))                             //创建管道   
    {    
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
					&pi))  
    {
		cout<<"Create Process Error: "<<GetLastError()<<endl;
		cout<<"Execute: ["<<cmdstring<<"] failed!"<<endl;
        CloseHandle(hWrite);   
        CloseHandle(hRead);   
        return NULL;   
    }    
    WaitForSingleObject(pi.hProcess,INFINITE);                         //等待进程结束   
         
    CloseHandle(pi.hProcess);                                          //关闭新进程的主线程   
    CloseHandle(pi.hThread);										   //关闭新进程   
    CloseHandle(hWrite);                                               //关闭管道的写句柄   
    ReadFile(hRead, buffer, MAX_PATH_LENGTH, &bytesRead, NULL);        //从管道中读取 运行结果   
    CloseHandle(hRead);                                                //关闭管道的读句柄   
       
	// cout<<"result:"<<buffer<<endl;
    return buffer;   
}  
