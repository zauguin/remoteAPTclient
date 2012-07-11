#include "common.h"

void execute(std::vector<std::string> install, std::vector<std::string> deinstall) {
  execCommand("apt-get", {"update"}, {});
  if(deinstall.size())
    execCommand("apt-mark", {"markauto"}, deinstall);
  if(install.size()) {
    execCommand("apt-get", {"install"}, install);
    execCommand("apt-mark", {"unmarkauto"}, install);
  }
  execCommand("apt-get", {"dist_upgrade"}, {});
  execCommand("apt-get", {"autoremove"}, {});
}
