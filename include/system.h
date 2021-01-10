#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  // Default constructor is explicitly defined in order to initialize
  // private members os_, kernel_ and cpu_ .
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
  // The next three variables do not change over time
  // so they are kept as private variables.
  std::string os_;
  std::string kernel_;
  Processor cpu_;

  // Since in the member function Processes() we need to return
  // a reference to this vector, we keep it as a private variable.
  std::vector<Process> processes_;
};

#endif