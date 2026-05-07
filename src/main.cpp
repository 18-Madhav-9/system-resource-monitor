#include <iostream>
#include <ui/monitor.h>
#include <algorithm>
#include <windows.h>

int main() {
    
    std::cout << "\n----------------------\n" ;
    std::cout << "    System Monitor     " ;
    std::cout << "\n----------------------\n" ;
    Sleep(1000);
    std::cout << "\033[2J" ;
    std::cout << "\033[H";
    drawLayout() ;
    while (true) {
        updateStats() ;
        Sleep(1000) ;
    }

    return 0;
}