#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include "windows.h"
#include <string>
struct ProcessInfo {
    std::string name;
    DWORD id ;
    double memoryMb;
};


#endif 
