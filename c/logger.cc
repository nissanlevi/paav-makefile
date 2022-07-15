
#include <iostream>
#include <stdlib.h>

#include "logger.h"

using namespace std;


/*
int indent = 0;

void print_indent() {
   for (int i=0; i<indent; ++i)
      cerr << "   ";
}

void inc_indent(int inc) {
   indent += inc;
}

void dec_indent(int dec) {
   indent -= dec;
}
*/




#ifdef ARCH_SUFFIX_W
ostream& operator<<(ostream& os, const std::string& msg)
{
  os << msg.c_str();
  return os;
}
#endif

void Logger::debug(const std::string& msg) const {
  cerr << "PA[DEBUG]::" << msg << endl;
}

void Logger::info(const std::string& msg) const {
  cerr << "PA[INFO]::" << msg << endl;
}

void Logger::warning(const std::string& msg) const {
  cerr << "PA[WARNING]::" << msg << endl;
}

void Logger::error(const std::string& msg) const {
  cerr << "PA[ERROR]::" << msg << endl;
}

void Logger::fatal(const std::string& msg) const {
  cerr << "PA[FATAL]::" << msg << endl;
}

void Logger::do_exit(int i) const {
  ::exit(i); 
}
