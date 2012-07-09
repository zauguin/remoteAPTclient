#include <iostream>
#include <fstream>
std::istream &get_istream();
#ifdef WRITE_TO_INSTALLED_FILE
std::ostream &get_ostream();
#endif
