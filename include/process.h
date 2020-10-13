#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int id):pid_(id) {
      user_ = LinuxParser::User(id);
      command_ = LinuxParser::Command(id);
  }
  // TODO: Declare any necessary private members
 private:
   std::string user_="";
    std::string command_="";
    std::string ram_;
    float cpu_usage_=0;
    int pid_=-1;
};

#endif