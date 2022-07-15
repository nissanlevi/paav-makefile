#include<stdlib.h>
#include<sstream>

#include "logger.h"
#include "line_command.h"


using namespace std;


Command_Line & Command_Line::get_instance () {
  static Command_Line instance;
  return instance;
}



Command_Line::Command_Line() :_print_after_parsing(false),
                              _traverse(false)
{}

int Command_Line::process(int argc, char *argv[]) {
   if (argc==1) {
      log_error("Missing command line flags:" << endl << endl);
      print_options();
      exit (1);
   }

   if (parse(argc, argv) == 0)
      return 0;

   if (check_args() == 0)
      return 0;

   return 1;
}


int Command_Line::parse(int argc, char *argv[]) {
   for (int i=0; i<argc; ++i) {
      _all_strings.push_back(argv[i]);
   }

   for (unsigned i = 0; i<_all_strings.size(); ++i) {
      if (_all_strings[i] == "-fi") {
         _input_file = _all_strings[i+1];
      }
      else if (_all_strings[i] == "-help") {
         _help = true;
      }
      else if (_all_strings[i] == "-print_after_parsing") {
         _print_after_parsing = true;
      }
      else if (_all_strings[i] == "-traverse") {
         _traverse = true;
      }
      else if (_all_strings[i][0] == '-') {
         log_error_and_exit ("Error in command line. Unknown option: " << _all_strings[i] << endl
                             << "Try 'run -help'" << endl
                             );
         return 0;
      }
   }
   
   return 1;
}


int Command_Line::check_args() {
   if (_help) {
      print_options();
      exit (0);
   }

   if (_input_file.size()==0) {
      log_error_and_exit("Please specify -fi <input file>" << endl);
      return 0;
   }

   return 1;
}


void Command_Line::print_options() {
   log_print("Mandatory:" << endl << //
             "==========" << endl << //
             "-fi <input file>" << endl );

   log_print(endl);
   log_print("Optional:" << endl);
   log_print("==========" << endl);
   log_print("-print_after_parsing: prints the program after the parsing, but before processing" << endl);
   log_print("-traverse : run Traverse::pretty_print() after processing stage" << endl);
   log_print("-help : prints this message" << endl);
}
