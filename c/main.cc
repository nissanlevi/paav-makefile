
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "yacc_functions.h"
#include "logger.h"
#include "line_command.h"
#include "program.h"
#include "traverse.h"

using namespace std;


int pa_parser_yyparse();
extern FILE *pa_parser_yyin;

Program PROGRAM;
Location_Manager PA_LOC_MAN;

int main(int argc, char ** argv) {
  Command_Line &command_line = Command_Line::get_instance();
   
   if (!command_line.process(argc,argv)) {
      log_error_and_exit("Got error in command line" << endl);
   }

   
   string file_name = command_line.get_input_file();

   
   // PARSING
   pa_parser_yyin = fopen(file_name.c_str() ,"r");
   if (pa_parser_yyin==NULL)
      log_error_and_exit ("The file " << file_name << " doesn't exist. Exiting ..." << endl);
   
   log_info ("Parsing file: " << file_name.c_str() << endl);
   PA_LOC_MAN.set_current_file(file_name.c_str());
   int ret = pa_parser_yyparse();
   if (!ret) {
      PROGRAM.process_after_parsing();
   }
   else {
      log_error_and_exit("Error when parsing. Exiting ..." << endl);
   }
   if (command_line.print_after_parsing())
      PROGRAM.print_after_parsing();

   if (command_line.traverse()) {
      Traverse trvs;
      trvs.set_program(&PROGRAM);
      trvs.pretty_print();
   }

   return 0;
}
