#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  // Default constructor is explicitly defined in order to instantiate
  // private members std::string os_ and std::string kernel_
  System();

  std::string OperatingSystem();      // DONE: See src/system.cpp
  std::string Kernel();               // DONE: See src/system.cpp
  Processor& Cpu();                   // DONE: See src/system.cpp
  std::vector<Process>& Processes();  // DONE: See src/system.cpp
  float MemoryUtilization();          // DONE: See src/system.cpp
  long UpTime();                      // DONE: See src/system.cpp
  int TotalProcesses();               // DONE: See src/system.cpp
  int RunningProcesses();             // DONE: See src/system.cpp

  // DONE: Define any necessary private members
 private:
  std::string os_;
  std::string kernel_;
  Processor cpu_;
  std::vector<Process> processes_;
};

#endif