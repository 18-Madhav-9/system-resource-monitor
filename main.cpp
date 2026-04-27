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

    auto processes = process();

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

    size_t leftWidth  = std::max(left1.length(), left2.length()) + 2;
    size_t rightWidth = std::max(right1.length(), right2.length()) + 2;
    size_t fullWidth  = leftWidth + rightWidth + 1; // merged width

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

    // Separator before process list
    std::cout << "+" << std::string(fullWidth, '-') << "+\n";

    // Process list
    for (const auto &p : processes) {
        std::ostringstream ss;
        ss << p.name << " (PID: " << p.id << ") - "
           << std::fixed << std::setprecision(2)
           << p.memoryMb << " MB";

        std::string line = ss.str();

        if (line.length() > fullWidth)
            line = line.substr(0, fullWidth - 3) + "...";

        std::cout << "|"
                  << std::left << std::setw(fullWidth) << line
                  << "|\n";
    }

    // Bottom border
    std::cout << "+" << std::string(fullWidth, '-') << "+\n";
}



int main() {
    
    std::cout << "\n----------------------\n" ;
    std::cout << "    System Monitor     " ;
    std::cout << "\n----------------------\n" ;
    Sleep(1000);
    while(true) {
        system("cls") ;
        monitorBox() ;
        Sleep(1000);
    }


    return 0;
}