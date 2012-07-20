#include <stdio.h>
#include <ext/stdio_filebuf.h>
#include "installed_dynamic.h"
#include <string>

void close_stream(std::istream &stream) {
  __gnu_cxx::stdio_filebuf<char, std::char_traits<char> > *temp = (__gnu_cxx::stdio_filebuf<char, std::char_traits<char> >*)stream.rdbuf();
  pclose(temp->file());
  delete temp;
}

std::istream &get_istream(const char * command) {
  auto temp = new std::istream(new __gnu_cxx::stdio_filebuf<char, std::char_traits<char> >(popen(command, "r"), std::ios_base::in));
  return *temp;
}
