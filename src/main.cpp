#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "ncurses_display.h"
#include "process.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
}

// Please forgive this mess, the following code was used in main
// for testing while developing the assigment.

// auto pids = LinuxParser::Pids();
// for (auto pid : pids) {
//   Process p{pid};
//   std::cout << "pid: " << pid << std::endl;
//   std::cout << "user: " << p.User() << std::endl;
//   std::cout << "ram: " << p.Ram() << std::endl;
//   std::cout << "cmd: " << p.Command() << std::endl;
//   std::cout << LinuxParser::kProcDirectory + std::to_string(pid) +
//                    LinuxParser::kStatFilename
//             << std::endl;
//   std::cout << "uptime: " << p.UpTime() << std::endl;
//   std::cout << "cpu util: " << p.CpuUtilization() << std::endl;
//   std::cout << std::endl;
// }

// std::cout << (Process{1} < Process{2}) << std::endl;

// auto pid = 2395;
// Process p{pid};
// System s;
// while (true) {
//   std::string upTime;
//   std::string line;
//   std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid) +
//                        LinuxParser::kStatFilename);
//   if (stream.is_open()) {
//     std::getline(stream, line);
//     std::istringstream linestream(line);
//     auto i = 1;
//     while (linestream >> upTime) {
//       if (i == 2) {
//         std::cout << upTime << std::endl;
//         ;
//       };
//       ++i;
//     }
//   }
//   std::cout << "pid: " << pid << std::endl;
//   std::cout << "system uptime: " << s.UpTime() << std::endl;
//   std::cout << "process uptime: " << p.UpTime() << std::endl;
//   std::cout << "active seconds: " << p.ActiveClicks() << std::endl;
//   std::cout << "cpu utilization: " << p.CpuUtilization() << std::endl;
//   std::cout << "user: " << p.User() << std::endl;
//   std::cout << "ram: " << p.Ram() << std::endl;
//   std::cout << "cmd: " << p.Command() << std::endl;
//   std::cout << LinuxParser::kProcDirectory + std::to_string(pid) +
//                    LinuxParser::kStatFilename
//             << std::endl;
//   std::cout << std::endl;
//   sleep(3);
// }

// auto pids = LinuxParser::Pids().size();
// std::cout << pids << std::endl << "Finito" << std::endl;