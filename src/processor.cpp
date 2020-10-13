#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    Processor::setPrevValues();
    Processor::CalculateCurrentTime();
    float totald = Processor::total - Processor::prevTotal;
    float idled = Processor::idle -Processor::prevIdle;
    float result =  (totald-idled)/totald; 
    return result;
 }

 void Processor::CalculateCurrentTime(){
	 std::vector<std::string> cpu_data = LinuxParser::CpuUtilization();
     Processor::nonIdle = std::stoi(cpu_data[0]) + std::stoi(cpu_data[1]) + std::stoi(cpu_data[2])
     + std::stoi(cpu_data[5]) + std::stoi(cpu_data[6]) + std::stoi(cpu_data[7]);
     Processor::idle = std::stoi(cpu_data[3])+ std::stoi(cpu_data[4]);
     Processor::total = Processor::idle + Processor::nonIdle;
 }

void Processor::setPrevValues()
{
    Processor::prevIdle = Processor::idle;
    Processor::prevNonIdle = Processor::nonIdle;
    Processor::prevTotal = Processor::total;
}