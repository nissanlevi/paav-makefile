#ifndef LOGGER_H
#define LOGGER_H


#include <iostream>
#include <stdlib.h>

#define log_print(prm) {/*print_indent();*/ std::cerr << prm;}


#define log_debug(prm) {std::cerr << "PA[DEBUG]::" << prm;}
#define log_info(prm)  {std::cerr << "PA[INFO ]::" << prm;}
#define log_warn(prm)  {std::cerr << "PA[WARN ]::" << prm;}
#define log_error(prm) {std::cerr << "PA[ERROR]::" << prm;}
#define log_fatal(prm) {std::cerr << "PA[FATAL]::" << prm; exit(2);}

#define log_error_and_exit(prm) {log_error(prm); exit(1);}



//#define print_verbosity(verbosity, prm) {print_indent(); cerr << prm;}

//void print_indent();
//void inc_indent(int inc=1);
//void dec_indent(int dec=1);



class Logger {
public:
   Logger() {}
   virtual ~Logger() {}
   
   virtual void debug(const std::string& msg) const;
   virtual void info(const std::string& msg) const;
   virtual void warning(const std::string& msg) const;
   virtual void error(const std::string& msg) const;
   virtual void fatal(const std::string& msg) const;
    
   virtual void do_exit(int i) const;
};



#endif

