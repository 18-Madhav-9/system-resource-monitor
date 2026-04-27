#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include "process_info.h"

// convert btyes to MB ;
#define MB (1024.0*1024)

std::vector<ProcessInfo> getProcess(){

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0) ;

    PROCESSENTRY32 current ;
    current.dwSize = sizeof(current) ;

    std::vector<ProcessInfo> plist;

    if (Process32First(snapshot,&current)) {
        int count = 0 ;
        do {
            ProcessInfo p ;
            p.name = current.szExeFile ;
            p.id = current.th32ProcessID ;
            p.memoryMb = 0.0 ;

            HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ , false,p.id) ;
            PROCESS_MEMORY_COUNTERS pmc ;

            if (!hprocess) {
                continue; // skip protected/system processes
            }
            
            if ( GetProcessMemoryInfo(hprocess,&pmc,sizeof(pmc)) ) {
                p.memoryMb = pmc.WorkingSetSize/MB ;
                if (p.memoryMb < 5.0) {
                    CloseHandle(hprocess);
                    continue; // skip small processes
                }
            }
            CloseHandle(hprocess) ;

            plist.push_back(p) ;
            //count++ ;
            //if ( count >=5 ) break ;
        }while ( Process32Next(snapshot,&current) ) ;
    }
    
    CloseHandle(snapshot) ;

    return plist ;
}
