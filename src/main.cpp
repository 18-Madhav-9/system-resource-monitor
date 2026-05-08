#include <iostream>
#include "ui/renderer.h"
#include "core/monitor.h" 
#include <windows.h>

int main() {
    
    std::cout << "\n----------------------\n" ;
    std::cout << "    System Monitor     " ;
    std::cout << "\n----------------------\n" ;
    Sleep(1000);
    std::cout << "\033[2J" ;
    std::cout << "\033[H";

    Monitor monitor ;
    drawLayout() ;
    while (true) {
        monitor.update() ;
        render(monitor.getState()) ;
        Sleep(1000) ;
    }

    return 0;
}