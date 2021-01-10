#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// Not updated to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization.
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  float value, memTotal, memFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = value;
        } else if (key == "MemFree:") {
          memFree = value;
        } else {
          break;
        }
      }
    }
  }
  float memUtil = (memTotal - memFree) / memTotal;
  return memUtil;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime, whatever;
  string line;
  std::ifstream stream(kProcDirectory + "/uptime");

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> whatever;
  }
  return uptime;
}

/*
// The following three functions were not implemented. The necessary jiffies
// for the calculation of Cpu utilization in Processor::Utilization() are
// obtained using the function Jiffies AllJiffies().
// System CPU utilization is calculated in class Processor.

// NOT DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// NOT DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// NOT DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// NOT DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }
// *******************************************************************
*/

// This function is not included in the initial project.
// It is used by the Porcessor class to calculated CPU utilization.
// It returns a struct of type LinuxParser::Jiffies which contains
// the values in /proc/stat .

LinuxParser::Jiffies LinuxParser::AllJiffies() {
  std::string line;
  std::string key;
  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);
  LinuxParser::Jiffies jiffies;
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key >> jiffies.user >> jiffies.nice >> jiffies.system >>
        jiffies.idle >> jiffies.iowait >> jiffies.irq >> jiffies.softirq >>
        jiffies.steal >> jiffies.guest >> jiffies.guestNice;
  }
  return jiffies;
}

// DONE: Read and return the number of active jiffies for a PID
// This function returns the sum of the 4 values related to CPU
// activity in /proc/<pid>/stat .
long LinuxParser::ActiveJiffies(int pid) {
  long total = 0;
  string temp;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i = 1;
    while (linestream >> temp) {
      // Required values are in positions 14, 15 16 and 17.
      if (i == 14 || i == 15 || i == 16 || i == 17) {
        total += std::stol(temp);
      };
      ++i;
    }
  }
  return total;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return Pids().size(); }

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line;
  std::string key;
  int runningProcesses;
  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "procs_running") {
        linestream >> runningProcesses;
        break;
      }
    }
  }
  return runningProcesses;
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
    // std::istringstream linestream(line);
    // linestream >> os >> version >> kernel;
  }
  return "NA";
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  int value, vmSize;
  std::ifstream filestream(kProcDirectory + to_string(pid) + "/status");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          vmSize = value;
          return to_string(vmSize);
        }
      }
    }
  }

  return "0";
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  int value, uid;
  std::ifstream filestream(kProcDirectory + to_string(pid) + "/status");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          uid = value;
          break;
        }
      }
    }
  }

  return to_string(uid);
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line;
  string key;
  string x;
  string value;
  auto uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> x >> value) {
        if (value == uid) {
          return key;
        }
      }
    }
  }
  return key;
}

// DONE: Read and return the UpTime associated with a process
long int LinuxParser::UpTime(int pid) {
  string upTime;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    auto i = 1;
    while (linestream >> upTime) {
      if (i == 22) {
        return std::stol(upTime);
      };
      ++i;
    }
  }
  return 0;
}