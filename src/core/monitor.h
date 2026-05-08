#pragma once 

#include "monitor_state.h"
class Monitor{
public :
    void update();
    const MonitorState& getState() const ;

private:
    MonitorState state ;
};