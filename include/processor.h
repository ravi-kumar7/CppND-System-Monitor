#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void setPrevValues() ;
  void CalculateCurrentTime();
  // TODO: Declare any necessary private members
 private:
    long prevIdle=0, prevNonIdle=0, prevTotal=0;
    long idle=0, nonIdle=0, total=0;
};

#endif