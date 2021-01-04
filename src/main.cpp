#include "ncurses_display.h"
#include "system.h"
#include <iostream>

int main() {
  System system;
  NCursesDisplay::Display(system);
  // System p;
  // std::cout << p.RunningProcesses() << std::endl;
  // std::cout << "Finito" << std::endl;
}