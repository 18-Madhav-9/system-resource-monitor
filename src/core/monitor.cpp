#include "cpu/cpu_collector.h"
#include "memory/memory_collector.h"
#include "process/process_collector.h"
#include "monitor.h"
#include "monitor_state.h"
#include <algorithm>

void Monitor::update() {
    state.cpu = getCpuInfo() ;
    state.memory = getMemoryInfo() ;
    state.processes = getProcesses() ;

    std:sort(state.processes.begin() , state.processes.end());
    auto newEnd = std::remove_if(state.processes.begin(), state.processes.end(),
        [](const ProcessInfo& p) {
            return p.memoryMb < 5.0;
        }
    );
    state.processes.erase(newEnd, state.processes.end());
    
}

const MonitorState& Monitor::getState() const{
    return state;
}
