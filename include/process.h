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
  // Constructs the object using the process' pid.
  Process(int pid);

  // Explicitly forbidding the default constructor.
  Process() = delete;

  int Pid() const;                         // DONE: See src/process.cpp
  std::string User() const;                // DONE: See src/process.cpp
  std::string Command() const;             // DONE: See src/process.cpp
  float CpuUtilization() const;            // DONE: See src/process.cpp
  std::string Ram() const;                 // DONE: See src/process.cpp
  long int UpTime();                       // DONE: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp

  // DONE: Declare any necessary private members
 private:
  // Variables whose values do not change overtime are kept
  // as private variables.
  int pid_;
  std::string user_;
  std::string command_;
  long int uptime_;

  // These functions are used only in the constructor
  // to initialize variables user_, command_ and uptime_.
  void GetUser_();
  void GetCommand_();
  void GetUptime_();
};

#endif