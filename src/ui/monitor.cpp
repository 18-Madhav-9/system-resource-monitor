#include <iostream>
#include <iomanip>
#include "cpu/cpu_collector.h"
#include "memory/memory_collector.h"
#include "process/process_collector.h"
#include <algorithm>

void moveCursor(int row,int col) {
    std::cout << "\033[" << row <<";" <<col << "H" ;
}

void drawLayout() {
    std::cout << "\033[2J" ;
//  layout    << "12345678912345678912345678912345678912345678912345"
    std::cout << "+------------------------------------------------+\n" ;
    std::cout << "| CPU :            |Mem  :                       |\n" ;
    std::cout << "|                  |Used :        |Free:         |\n" ;
    std::cout << "+------------------------------------------------+\n" ;
    
    std::cout << "+------------------------------------------------+\n" ;
    for (int i = 0 ; i < 20 ; i++) {
        std::cout << "|                                                |\n" ;
    }

    std::cout << "+-------------------------------------------------+\n" ;
}

void updateStats() {

    CpuInfo cpuinfo = getCpuInfo() ;
    MemoryInfo memoryinfo = getMemoryInfo() ;
    auto processes = getProcesses() ;

    moveCursor(2,8) ;
    std::cout << std::fixed
              << std::setprecision(2)
              << cpuinfo.usage<< " %"; 
    moveCursor(2,28);
    std::cout << std::fixed
              << std::setprecision(2)
              << memoryinfo.used << "/" << memoryinfo.total << " GB" ;
    moveCursor(3,28);
    std::cout << std::fixed
              << std::setprecision(2)
              << memoryinfo.usedPercent << " %" ;
    moveCursor(3,42) ;
    std::cout << std::fixed
              << std::setprecision(2)
              << memoryinfo.free << "GB" ;

    int row = 6 ;
    std::sort(processes.begin(), processes.end());
    for ( int i = 0 ; i < 20 ;i++ ) {
        moveCursor(row+i,2) ;

        if (i < processes.size()) {
            const auto &p = processes[i];
            std::ostringstream ss;
            ss << p.name
               << " PID:" << p.pid
               << " "
               << std::fixed << std::setprecision(2)
               << p.memoryMb << "MB";

            std::cout << ss.str();
        }
    }
}
