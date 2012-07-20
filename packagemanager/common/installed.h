#include <iostream>
#include <fstream>
#include <config.h>
std::istream &get_istream();
void close_stream(std::istream&);
#ifdef WRITE_TO_INSTALLED_FILE
std::ostream &get_ostream();
void close_stream(std::ostream&);
#endif
