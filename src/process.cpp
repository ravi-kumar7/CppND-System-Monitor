#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { 
    return Process::pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    float totaltime = LinuxParser::ActiveJiffies(Process::Pid())/sysconf(_SC_CLK_TCK);
    Process::cpu_usage_ =  (totaltime/Process::UpTime());
    return Process::cpu_usage_;
}

// TODO: Return the command that generated this process
string Process::Command() { return Process::command_;  }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return Process::user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()) ; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return this->cpu_usage_ < a.cpu_usage_; }