#include <fstream>
#include "installed.h"
std::istream &get_istream() {
  auto temp = new std::ifstream("installed", std::ios_base::in);
  return *temp;
}
void close_stream(std::istream &stream) {
  ((std::ifstream&)stream).close();
}
void close_stream(std::ostream &stream) {
  ((std::ofstream&)stream).close();
}
std::ostream &get_ostream() {
  auto temp = new std::ofstream("installed", std::ios_base::out|std::ios_base::trunc);
  return *temp;
}
