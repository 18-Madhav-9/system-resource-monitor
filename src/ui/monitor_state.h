#pragma once

#include <vector>
#include "cpu/cpu_info.h"
#include "memory/memory_info.h"
#include "process/process_info.h"

struct MonitorState{
    CpuInfo cpu ;
    MemoryInfo memory ;
    std::vector<ProcessInfo> processes;
};