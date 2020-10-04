#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
        string line, key;
        std::getline(filestream, line);
        std::istringstream linestream(line);
        long total_mem, free_mem;
        linestream >> key >> total_mem;
        std::getline(filestream, line);
        std::istringstream secondlinestream(line);
        secondlinestream >> key >> free_mem;
        float mem_utilization = (total_mem - free_mem)/1000.0f;
        return mem_utilization;  
  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
    std::ifstream filestream(kProcDirectory+kUptimeFilename);
    string line;
    std::getline(filestream, line);
    std::istringstream stream(line);
    long uptime;
    stream >> uptime;
    return uptime;
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
  std::vector<string> cpu_data;
  std::ifstream filestream("./proc/stat");
  string line,value;
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream >> value;
  while(linestream >> value ){
    if(value!= "")
      cpu_data.push_back(value);
  }
    return cpu_data; 
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
    std::ifstream filestream(kProcDirectory+kStatFilename);
    string line,key;
    int value;
    while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key>> value;
        if(key == "procs_running")
         break;
    }
    return value;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
    std::ifstream filestream(kProcDirectory+kStatFilename);
    string line,key;
    int value;
    while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key>> value;
        if(key == "processes")
         break;
    }
    return value;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  string cmd;
  std::getline(filestream, cmd);
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream filestream("./proc/"+std::to_string(pid)+"/status");
  string line,key;
  long value;
  while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key>> value;
        if(key == "VmSize:")
         break;
  } 
  float ram = value/1000.0;
  return std::to_string(ram) + " MB"; 
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
    string line,key;
    int value;
    while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key>> value;
        if(key == "Uid:")
         break;
    }
    return std::to_string(value); 
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
   string user_id =  Uid(pid);
    std::ifstream filestream(kPasswordPath);
    string line,key,value;
    while(std::getline(filestream, line)){
        std::replace(line.begin(),line.end(),':',' ');
        std::istringstream linestream(line);
        linestream >> key>> value;
        if(value == user_id)
         break;
    }
    return key;
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
    std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
    string line,key;
    long value;
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value>> key >> key >> value>> value>> value>> value>> value>> value>> value >> value>> value>> value>> value>> value>> value>> value>> value>> value>> value>> value>> value ;
    return value; 
 }