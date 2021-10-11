#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  
 private:
    long _prevJiffies = 0;
    long _prevActJiffies = 0;
    long _Jiffies;
    long _ActJiffies;
};

#endif