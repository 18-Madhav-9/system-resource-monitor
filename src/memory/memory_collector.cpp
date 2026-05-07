#include "memory/memory_info.h"
#include <windows.h>

// converting bytes to GB
#define GB (1024.0*1024*1024)

MemoryInfo getMemoryInfo() {

    MEMORYSTATUSEX status ;
    status.dwLength = sizeof(status) ;

    MemoryInfo info ;
    if ( GlobalMemoryStatusEx(&status) ){ 
        info.usedPercent = status.dwMemoryLoad ;
        info.free = status.ullAvailPhys/GB ;
        info.total= status.ullTotalPhys/GB; 
    }
    info.used = info.total-info.free;
    
    return info ;

}