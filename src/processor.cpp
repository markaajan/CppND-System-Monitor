#include <string>
#include <vector>
#include "processor.h"
#include <sstream>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    for (int i = 0;i < 10; i++)
        prev[i] = current[i];
    std::vector<std::string> cpu = LinuxParser::CpuUtilization();
    for (int i = 0;i < 10; i++)
        current[i] = std::stoi(cpu[i]);

    
    int PrevIdle = prev[LinuxParser::CPUStates::kIdle_] + prev[LinuxParser::CPUStates::kIOwait_];
    int Idle = current[LinuxParser::CPUStates::kIdle_] + current[LinuxParser::CPUStates::kIOwait_];

    int PrevNonIdle = prev[LinuxParser::CPUStates::kUser_] + prev[LinuxParser::CPUStates::kNice_] + prev[LinuxParser::CPUStates::kSystem_] + prev[LinuxParser::CPUStates::kIRQ_] + prev[LinuxParser::CPUStates::kSoftIRQ_] + prev[LinuxParser::CPUStates::kSteal_];
    int NonIdle = current[LinuxParser::CPUStates::kUser_] + current[LinuxParser::CPUStates::kNice_] + current[LinuxParser::CPUStates::kSystem_] + current[LinuxParser::CPUStates::kIRQ_] + current[LinuxParser::CPUStates::kSoftIRQ_] + current[LinuxParser::CPUStates::kSteal_];
    
    int PrevTotal = PrevIdle + PrevNonIdle;
    int Total = Idle + NonIdle;

    int totald = Total - PrevTotal;
    int idled = Idle - PrevIdle;
    return ((totald - idled)/totald);
 
 
 
 }