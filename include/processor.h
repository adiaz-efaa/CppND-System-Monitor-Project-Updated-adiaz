#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <unistd.h>

#include "linux_parser.h"

class Processor {
 public:
  // Default constructor is explicitly implemented. It initializes the private
  // variable jiffies_.
  Processor();
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  LinuxParser::Jiffies jiffies_;
};

#endif