#include "processor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "linux_parser.h"

Processor::Processor() { get_data_(); }

void Processor::get_data_() {
  std::string line;
  std::string key;
  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key >> user_ >> nice_ >> system_ >> idle_ >> iowait_ >>
        irq_ >> softirq_ >> steal_ >> guest_ >> guest_nice_;
  }
}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  auto user = user_;
  auto nice = nice_;
  auto system = system_;
  auto idle = idle_;
  auto iowait = iowait_;
  auto irq = irq_;
  auto softirq = softirq_;
  auto steal = steal_;
  auto guest = guest_;
  auto guest_nice = guest_nice_;

  get_data_();

  auto prevIdle = idle + iowait;
  auto currentIdle = idle_ + iowait_;

  auto prevNonIdle =
      user - guest + nice - guest_nice + system + irq + softirq + steal;
  auto currentNonIdle =
      user_ - guest_ + nice_ - guest_nice_ + system_ + irq_ + softirq_ + steal_;

  auto prevTotal = prevIdle + prevNonIdle;
  auto currentTotal = currentIdle + currentNonIdle;

  // Calculate difference and percentage difference
  long double diffTotal = currentTotal - prevTotal;
  long double diffIdle = currentIdle - prevIdle;
  auto cpuPercentage = (diffTotal - diffIdle) / diffTotal;

  return cpuPercentage;
}