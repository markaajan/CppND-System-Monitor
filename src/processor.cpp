#include <string>
#include <vector>
#include "processor.h"
#include <sstream>
#include "linux_parser.h"


// Return the aggregate CPU utilization
float Processor::Utilization() { 
    _prevActJiffies = _ActJiffies;
    _prevJiffies =  _Jiffies;
    _ActJiffies = LinuxParser::ActiveJiffies();
    _Jiffies = LinuxParser::Jiffies();

    return ((float)_ActJiffies/(float)_Jiffies);
}