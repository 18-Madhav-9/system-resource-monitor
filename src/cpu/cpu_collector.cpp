#include "cpu_info.h"
#include <windows.h>

// coverting FILETIME struct to actual ticks 
ULONGLONG filetimeToULL(const FILETIME &f ) {
    return  (((ULONGLONG)f.dwHighDateTime << 32 ))|f.dwLowDateTime ;
}

CpuInfo getCpuInfo() {
    FILETIME idle1,kernel1,user1;
    FILETIME idle2,kernel2,user2 ;

    GetSystemTimes(&idle1,&kernel1,&user1);
    Sleep(1000);
    GetSystemTimes(&idle2,&kernel2,&user2) ;

    ULONGLONG idle = filetimeToULL(idle2)-filetimeToULL(idle1);
    ULONGLONG kernel = filetimeToULL(kernel2)-filetimeToULL(kernel1);
    ULONGLONG user = filetimeToULL(user2)-filetimeToULL(user1) ;

    double usage =  (1.0 - (double)idle/(kernel+user))*100 ;
    CpuInfo info ;
    info.usage = usage ;
    return info ;

}
