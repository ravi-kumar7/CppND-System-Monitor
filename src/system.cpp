#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() {
    System::kernel_ = LinuxParser::Kernel();
    System::operating_system_ = LinuxParser::OperatingSystem();
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    auto processess_ids = LinuxParser::Pids();
    processes_.clear();
    for(int id:processess_ids){
        Process p(id);
        p.CpuUtilization();
        processes_.push_back(p);
    }
    //sort the process on the basis of CPU utilization, higher to lower
    std::sort(processes_.begin(),processes_.end());
    std::reverse(processes_.begin(), processes_.end());
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return System::kernel_;
 }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return System::operating_system_;
 }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime() ; }