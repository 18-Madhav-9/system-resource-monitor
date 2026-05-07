#include "process/process_info.h"
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#include <vector>

#define MB (1024.0 * 1024.0);

std::vector<ProcessInfo> getProcesses() {

    std::vector<ProcessInfo> processes;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return processes;
    }

    PROCESSENTRY32 current;
    current.dwSize = sizeof(current);

    if (Process32First(snapshot, &current)) {
        do {
            ProcessInfo process;
            process.name = current.szExeFile;
            process.pid = current.th32ProcessID;

            HANDLE hprocess =OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,FALSE,process.pid);
            if (!hprocess) {
                continue;
            }

            PROCESS_MEMORY_COUNTERS pmc;

            if (GetProcessMemoryInfo(hprocess,&pmc,sizeof(pmc))) {
                process.memoryMb = pmc.WorkingSetSize/MB ;
            }

            CloseHandle(hprocess);

            processes.push_back(process);

        } while (Process32Next(snapshot, &current));
    }

    CloseHandle(snapshot);

    return processes;
}