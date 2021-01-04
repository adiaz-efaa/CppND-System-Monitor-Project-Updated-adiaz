#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  void get_data_();
  long long user_;
  long long nice_;
  long long system_;
  long long idle_;
  long long iowait_;
  long long irq_;
  long long softirq_;
  long long steal_;
  long long guest_;
  long long guest_nice_;
};

#endif