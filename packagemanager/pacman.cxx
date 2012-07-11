#include "common.h"

void execute(std::vector<std::string> install, std::vector<std::string> deinstall) {
  execCommand("pacman", {"--noconfirm", "-Sy"}, {});
  if(install.size()) {
    execCommand("pacman", {"--noconfirm", "--asexplicit", "-S"}, install);
  if(deinstall.size())
    execCommand("pacman", {"--noconfirm", "-Rs"}, deinstall);
  }
  execCommand("pacman", {"--noconfirm", "-Su"}, {});
}
