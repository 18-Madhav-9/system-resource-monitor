#include "renderer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void clearField(int width) {
    std::cout << std::string(width, ' ');
}

void drawLayout() {
    std::cout << "\033[2J";
    std::cout
        << "+------------------------------------------------+\n"
        << "| CPU :            |Mem  :                       |\n"
        << "|                  |Used :        |Free:         |\n"
        << "+------------------------------------------------+\n"

        << "+------------------------------------------------+\n";

    for (int i = 0; i < 15; i++) {
        std::cout
        << "|                                                |\n";
    }
    std::cout
        << "+------------------------------------------------+\n";
    std::cout << "\033[?25l";
    std::cout.flush();
}

static void renderCpu(const CpuInfo& cpu) {
    moveCursor(2, 8);
    std::cout
        << std::fixed
        << std::setprecision(2)
        << cpu.usage;
}

static void renderMemory(const MemoryInfo& memory) {

    moveCursor(2, 28);
    std::ostringstream total;
    total << std::fixed
          << std::setprecision(2)
          << memory.used
          << "/"
          << memory.total
          << " GB";

    std::cout
        << std::left
        << std::setw(20)
        << total.str();

    moveCursor(3, 28);

    std::ostringstream usage;
    usage << std::fixed
          << std::setprecision(2)
          << memory.usedPercent
          << "%";
    std::cout
        << std::left
        << usage.str();

    moveCursor(3, 42);

    std::ostringstream free;
    free << std::fixed
         << std::setprecision(2)
         << memory.free
         << " GB";
    std::cout
        << std::left
        << free.str();
}

static void renderProcesses(std::vector<ProcessInfo> processes) {

    std::sort(processes.begin(),processes.end());

    int row = 6;
    for (int i = 0; i < 15; i++) {
        moveCursor(row + i, 2);

        if (i < processes.size()) {
            const auto& p = processes[i];

            std::ostringstream ss;
            ss << p.name
               << " PID:"
               << p.pid
               << " ";
            ss << std::fixed
               << std::setprecision(2)
               << p.memoryMb
               << "MB";
            std::string line = ss.str();

            if (line.size() > 48) {
                line = line.substr(0, 45) + "...";
            }

            std::cout
                << std::left
                << std::setw(48)
                << line;
        }
        else {
            std::cout
                << std::setw(48)
                << " ";
        }
    }
}

void render(const MonitorState& state) {

    renderCpu(state.cpu);
    renderMemory(state.memory);
    renderProcesses(state.processes);
    std::cout.flush();
}