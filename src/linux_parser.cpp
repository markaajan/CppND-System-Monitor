#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include "format.h"
#include "linux_parser.h"
#include <iostream>
#include "processor.h"
#include <unistd.h>
using std::stof;
using std::string;
using std::to_string;
using std::vector;


// An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  double mem_free, mem_total;
  string line, title, kB;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> title >> mem_total >>kB;
    std::getline(stream, line);
    std::istringstream linestream1(line);
    linestream1 >> title >> mem_free >>kB;
  }
  return ((float)(mem_total - mem_free)/mem_total);
  }

// Read and return the system uptime
long LinuxParser::UpTime() { 
  float seconds = 0;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> seconds;
  }
  return seconds; 
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return IdleJiffies() + ActiveJiffies(); 
  }

// Read and return the number of active jiffies for a PID

long LinuxParser::ActiveJiffies(int pid) { 
    std::string word;
    std::ifstream stream(kProcDirectory + to_string (pid) + kStatFilename);
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 14;i ++){
    linestream >> word;}
    int total = 0;
    for (int i = 0; i < 4; i ++)
    {
    total += atoi(word.c_str());
    linestream >> word;
    }
    return total;


 }

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  auto cpu = LinuxParser::CpuUtilization();
   
  return atoi(cpu[LinuxParser::CPUStates::kGuest_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kGuestNice_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kIRQ_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kNice_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kSystem_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kSteal_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kUser_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kSoftIRQ_].c_str()); }

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {   
  auto cpu = LinuxParser::CpuUtilization();
   
  return atoi(cpu[LinuxParser::CPUStates::kIdle_].c_str()) + atoi(cpu[LinuxParser::CPUStates::kIOwait_].c_str()); }

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
    vector<string> cpu = {};
    std::string title;
    std::ifstream stream(kProcDirectory + kStatFilename);
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> title;
    if (title == "cpu"){
      for (int i = 0;i < 10; i++)
      {
          linestream >> title;
          cpu.push_back(title);
          
      }}
    return cpu;

   }



// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string val;
  std::string line, title;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title >> val;
    if (!std::strcmp(title.c_str(),"processes")){
      return std::stoi(val);}
  }
  return 0;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string val;
  std::string line, title;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title >> val;
    if (!std::strcmp(title.c_str(),"procs_running"))
    {
        return std::stoi(val);
  } 
  }
  return 0;
}

// Read and return the command associated with a process

string LinuxParser::Command(int pid) 
{ 
  string command;
  std::string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> command;

  
  return command; }

// Read and return the memory used by a process

string LinuxParser::Ram(int pid) {   
  std::string ram,title;
  std::string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title>>ram;
    if (!std::strncmp(title.c_str(),"VmSize:",7))
    {
      float mem = stoi(ram);
      mem /= 1024;

      return to_string(mem);
    }
  }
  return "0";


  

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    string uid,title;
  std::string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title;
    if (!std::strcmp(title.c_str(),"Uid:")){

    
      linestream >> uid;
      return uid;
    }
  }
  return "0";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string sub = LinuxParser::Uid(pid);
  sub = ":x:" + sub + ":";
  std::string line;
  std::ifstream stream(kPasswordPath);
  std::istringstream linestream(line);
  while(std::getline(stream, line))
  {
    auto pos = (line.find(sub));
    if (pos != std::string::npos){

      return line.substr(0, pos);
    }

  }
  return string(); }






// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string line;
  string time;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  std::getline(stream, line);
  std::istringstream linestream(line);
  for (int i = 0 ;i<22;i++)
  {
    linestream >> time;
  }
  float sec = atoi(time.c_str());
  return sec;
}
