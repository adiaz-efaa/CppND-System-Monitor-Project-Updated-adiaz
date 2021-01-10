#include "processor.h"
#include <fstream>
#include <iostream>
#include <string>

Processor::Processor() { jiffies_ = LinuxParser::AllJiffies(); }
// DONE: Return the aggregate CPU utilization
// The algorithm shown in the checked answer in
// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
// is implemented. The class has a private variable of type LinuxParser::Jiffies
// which is just a struct containing the values obtained from the /proc/stat
// file.
float Processor::Utilization() {
  auto previous = jiffies_;  // The prevously assigned values are used.
  auto current = LinuxParser::AllJiffies();

  auto prevIdle = previous.idle + previous.iowait;
  auto currentIdle = current.idle + current.iowait;

  auto prevNonIdle = previous.user - previous.guest + previous.nice -
                     previous.guestNice + previous.system + previous.irq +
                     previous.softirq + previous.steal;
  auto currentNonIdle = current.user - current.guest + current.nice -
                        current.guestNice + current.system + current.irq +
                        current.softirq + current.steal;

  auto prevTotal = prevIdle + prevNonIdle;
  auto currentTotal = currentIdle + currentNonIdle;

  // Calculate difference and percentage difference
  double diffTotal = currentTotal - prevTotal;
  double diffIdle = currentIdle - prevIdle;
  double cpuPercentage;

  if (diffTotal == 0.0) {
    cpuPercentage = 0.0;
  } else {
    cpuPercentage = (diffTotal - diffIdle) / diffTotal;
  }

  // The values are updated so they are used as previous
  // in the next calculation.
  jiffies_ = current;

  return cpuPercentage;
}