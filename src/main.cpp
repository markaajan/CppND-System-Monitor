#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  system.opt.setChoice();
  NCursesDisplay::Display(system);
} 