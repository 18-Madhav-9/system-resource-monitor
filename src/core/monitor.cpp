#include "cpu/cpu_collector.h"
#include "memory/memory_collector.h"
#include "process/process_collector.h"
#include "monitor.h"
#include "monitor_state.h"

void Monitor::update() {
    state.cpu = getCpuInfo() ;
    state.memory = getMemoryInfo() ;
    state.processes = getProcesses() ;
}

const MonitorState& Monitor::getState() const{
    return state;
}
