#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  
  char _Ch;

 private:
    int _pid;
    std::string _command;
    float _cpu;
    std::string _user;
    long int _uptime;
    long int _ram;
    long int current[10] = {0,0,0,0,0,0,0,0,0,0};
    long int prev[10];

};

#endif