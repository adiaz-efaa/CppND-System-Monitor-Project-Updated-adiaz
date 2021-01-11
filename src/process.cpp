#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"
#include "process.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: COnstructor.
Process::Process(int pid) : pid_(pid) {
  GetUser_();
  GetCommand_();
  GetUptime_();
}

void Process::GetUser_() { user_ = LinuxParser::User(pid_); }

void Process::GetCommand_() { command_ = LinuxParser::Command(pid_); }

void Process::GetUptime_() {
  uptime_ = LinuxParser::UpTime(pid_) / sysconf(_SC_CLK_TCK);
}

// DONE: Return this process's ID
int Process::Pid() const { return pid_; }

// DONE: Return this process's CPU utilization
// This function utilizes the algorithm in
// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
// in the preferred answer.
float Process::CpuUtilization() const {
  auto uptime = LinuxParser::UpTime();
  auto totalTime = LinuxParser::ActiveJiffies(pid_) / sysconf(_SC_CLK_TCK);
  auto seconds = uptime - uptime_;
  if (seconds > 0.0) {
    return 100 * totalTime / seconds;
  } else {
    return 0.0;
  }
}

// DONE: Return the command that generated this process
string Process::Command() const { return LinuxParser::Command(pid_); }

// DONE: Return this process's memory utilization
string Process::Ram() const {
  // Memory is converted to megabytes and rounded
  // to 0 decimal places.
  auto k = 0.0009765625;
  auto ram = (long)(stol(LinuxParser::Ram(pid_)) * k + .5);
  return to_string(ram);
}

// DONE: Return the user (name) that generated this process
string Process::User() const { return user_; }

// DONE: Return the age of this process (in seconds)
// Since uptime_ represents "The time the process started after system boot"
// this number is subtracted from total system uptime to get process uptime.
// COMMENT: this looks like a code smell (this code smells bad?). Even though it
// works the fact that the process is already contained in an instance of System
// makes this solution look a bit redundant. Maybe adding a to the project a
// controller class that communicates with System and the functions in
// ncurses_display could help ...
long int Process::UpTime() {
  System s;
  auto sysUptime = s.UpTime();
  return sysUptime - uptime_;
}

// DONE: Overload the "less than" comparison operator for Process objects
// Order by CPU utilization but in inverse order (more utilization goes first).
bool Process::operator<(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization();
}