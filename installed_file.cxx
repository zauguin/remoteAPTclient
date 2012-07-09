#include <fstream>
#include "installed.h"
std::istream &get_istream() {
  auto temp = new std::ifstream("installed", std::ios_base::in);
  return *temp;
}
std::ostream &get_ostream() {
  auto temp = new std::ofstream("installed", std::ios_base::out|std::ios_base::trunc);
  return *temp;
}
