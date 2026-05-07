#include <iostream>
#include <iomanip>
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "process/process.h"
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
    for (int i = 0 ; i < 15 ; i++) {
        std::cout << "|                                                |\n" ;
    }

    std::cout << "+-------------------------------------------------+\n" ;
}

void updateStats() {

    double cpuUsage,ramUsage,availRam,totalRam,usedRam ;
    getCpuUsage(cpuUsage) ;
    getMemoryUsage(ramUsage,availRam,totalRam) ;
    usedRam = totalRam-availRam ;
    auto processes = getProcess() ;

    moveCursor(2,8) ;
    std::cout << std::fixed
              << std::setprecision(2)
              << cpuUsage << " %"; 
    moveCursor(2,28);
    std::cout << std::fixed
              << std::setprecision(2)
              << usedRam << "/" << totalRam << " GB" ;
    moveCursor(3,28);
    std::cout << std::fixed
              << std::setprecision(2)
              << ramUsage << " %" ;
    moveCursor(3,42) ;
    std::cout << std::fixed
              << std::setprecision(2)
              << availRam << "GB" ;

    int row = 6 ;
    for ( int i = 0 ; i < 15 ;i++ ) {
        moveCursor(row+i,2) ;

        if (i < processes.size()) {
            const auto &p = processes[i];
            std::ostringstream ss;
            ss << p.name
               << " PID:" << p.id
               << " "
               << std::fixed << std::setprecision(2)
               << p.memoryMb << "MB";

            std::cout << ss.str();
        }
    }
}
