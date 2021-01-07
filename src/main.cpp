#include <iostream>
#include "linux_parser.h"
#include "ncurses_display.h"
#include "system.h"

int main() {
  // System system;
  // NCursesDisplay::Display(system);
  // System p;
  std::cout << LinuxParser::User(1) << std::endl;
  std::cout << "Finito" << std::endl;
}