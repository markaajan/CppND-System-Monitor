#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
class Choice{
  public:
  char Ch;
  void setChoice();
  char getChoice();
  
};
class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      
  Choice opt;

  

  // TODO: Define any necessary private members
 private:
  char _Ch;
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif