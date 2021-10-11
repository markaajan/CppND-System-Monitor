#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"
#include "linux_parser.h"
#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid)
{
    _pid = pid;
    _command = LinuxParser::Command(_pid);
    _uptime = LinuxParser::UpTime(_pid)/sysconf(_SC_CLK_TCK);
    _user = LinuxParser::User(_pid);
    _ram = std::stof(LinuxParser::Ram(_pid).c_str());
    long int sysuptime = LinuxParser::UpTime();
    //Utilization calculation
    long int total = LinuxParser::ActiveJiffies(_pid)/sysconf(_SC_CLK_TCK);
    float seconds = sysuptime - _uptime;
    _cpu = (total/seconds);
}

// Return this process's CPU utilization

float Process::CpuUtilization() 
{
    return _cpu;
}
int Process::Pid()
{
    return _pid;
}
// Return the command that generated this process

string Process::Command() 
{
    return _command; 
}

// Return this process's memory utilization

string Process::Ram() 
{   
    return std::to_string(_ram); 
}

// Return the user (name) that generated this process

string Process::User() 
{ 
    return _user; 
}

// Return the age of this process (in seconds)

long int Process::UpTime() 
{ 
    return (LinuxParser::UpTime() - _uptime); 
}

// Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const 
{ 
    if(this->_Ch == 'C')
    {
        if (_cpu < a._cpu)
        {
            return true; 
        }   
        else
        {
            return false;
        } 
    }  
    else
    {
        if (_ram < a._ram)
        {
            return true; 
        }
        else
        {
            return false;
        }
    }

}