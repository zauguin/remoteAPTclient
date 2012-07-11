#include <stdio.h>
#include <ext/stdio_filebuf.h>
#include "installed_dynamic.h"

std::istream &get_istream() {
  return get_istream("pacman -Qeq");
}
