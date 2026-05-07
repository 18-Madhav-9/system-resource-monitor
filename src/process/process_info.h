#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include "windows.h"
#include <string>
struct ProcessInfo {
    std::string name;
    DWORD pid ;
    double memoryMb;

    bool operator<(const ProcessInfo &other) const{ 
        return memoryMb > other.memoryMb ;
    }
};


#endif 
