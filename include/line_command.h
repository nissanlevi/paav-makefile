#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include<string>
#include<vector>

#include "logger.h"

class Command_Line : public Logger {
public:
   static Command_Line &get_instance();
   int process(int argc, char *argv[]);

   bool print_after_parsing() {return _print_after_parsing;}
   bool traverse() {return _traverse;}

   std::string get_input_file() {return _input_file;}

private:
   Command_Line();

   int parse(int argc, char *argv[]);
   int check_args();
   void print_options();

   std::vector<std::string> _all_strings;

   std::string _input_file;
   bool _print_after_parsing;
   bool _traverse;
   bool _help;
   
   std::string _out_dir;
   std::string _inp_dir;
};





#endif
