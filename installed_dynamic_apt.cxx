#include "installed_dynamic.h"

std::istream &get_istream() {
  return get_istream("apt-mark showmanual");
}
