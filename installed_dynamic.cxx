#include <stdio.h>
#include <ext/stdio_filebuf.h>
#include "installed.h"

std::istream &get_istream() {
  auto temp = new std::istream(new __gnu_cxx::stdio_filebuf<char, std::char_traits<char> >(popen("apt-mark showmanual", "r"), std::ios_base::in));
  return *temp;
}
