#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include "format.h"
#include "linux_parser.h"
#include <iostream>
#include "processor.h"
using std::stof;
using std::string;
using std::to_string;
using std::vector;


// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
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

// BONUS: Update this to use std::filesystem
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

// DONE: Read and return the system memory utilization
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

// DONE: Read and return the system uptime
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

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
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

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string val;
  std::string line, title;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title >> val;
    if (!std::strcmp(title.c_str(),"processes"))
      return std::stoi(val);
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string val;
  std::string line, title;
  std::ifstream stream(kProcDirectory + kStatFilename);
  while(std::getline(stream, line))
  {
    std::istringstream linestream(line);
    linestream >> title >> val;
    if (!std::strcmp(title.c_str(),"procs_running"))
      return std::stoi(val);
  } 
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
