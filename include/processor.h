#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
    long int current[10] = {0,0,0,0,0,0,0,0,0,0};
    long int prev[10];
};

#endif