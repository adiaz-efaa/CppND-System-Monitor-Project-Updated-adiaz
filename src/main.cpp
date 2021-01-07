#include <iostream>
#include "linux_parser.h"
#include "ncurses_display.h"
#include "process.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
  // Process p{3140};
  // std::cout << p.Command() << std::endl;
  // std::cout << "Finito" << std::endl;
}