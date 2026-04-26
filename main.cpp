#include <iostream>
#include <iomanip>
#include "memory.cpp"
#include "cpu.cpp"
#include "process.cpp"

void monitorBox() {
    double cpuUsage;
    cpu(cpuUsage);

    double ramusage, availram, totalram, usedram;
    memory(ramusage, availram, totalram);
    usedram = totalram - availram;

    // Build strings
    std::string left1, left2, right1, right2;

    {
        std::ostringstream ss;
        ss << "CPU: " << std::fixed << std::setprecision(2) << cpuUsage << "%";
        left1 = ss.str();
    }

    left2 = ""; 

    {
        std::ostringstream ss;
        ss << "Mem: " << std::fixed << std::setprecision(2)
           << usedram << "/" << totalram << " GB";
        right1 = ss.str();
    }

    {
        std::ostringstream ss;
        ss << "Used: " << std::fixed << std::setprecision(2)
           << ramusage << "% | Free: " << availram << " GB";
        right2 = ss.str();
    }

    size_t leftWidth = std::max(left1.length(), left2.length()) + 2;
    size_t rightWidth = std::max(right1.length(), right2.length()) + 2;

    std::cout << "+" << std::string(leftWidth, '-')
          << "+" << std::string(rightWidth, '-') << "+\n";

    std::cout << "|"
            << std::left << std::setw(leftWidth) << left1
            << "|"
            << std::left << std::setw(rightWidth) << right1
            << "|\n";

    std::cout << "|"
            << std::left << std::setw(leftWidth) << left2
            << "|"
            << std::left << std::setw(rightWidth) << right2
            << "|\n";

    std::cout << "+" << std::string(leftWidth, '-')
            << "+" << std::string(rightWidth, '-') << "+\n";
}



int main() {
    
    std::cout << "\n----------------------\n" ;
    std::cout << "    System Monitor     " ;
    std::cout << "\n----------------------\n" ;
    Sleep(1000);
    while(true) {
        system("cls") ;
        monitorBox() ;
        Sleep(500);
    }


    return 0;
}