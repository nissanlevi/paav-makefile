#include <sstream>
#include <iostream>
#include <stdlib.h>

#include <assert.h>

#include "logger.h"
#include "line_command.h"
#include "program.h"
#include "command.h"
//#include "line.h"

using namespace std;



void Program::print_after_parsing () {
   cerr << "vars are: " << endl;
   cerr << "========= " << endl;
   
   list<string *>::iterator i;
   for (i=_list_of_var->begin(); i != _list_of_var->end(); ++i)
      cerr << **i << " ";
   cerr << endl << endl;


   cerr << "Commands are: " << endl;
   cerr << "========= " << endl << endl;
   list<Command *>::iterator itr_cmd;
   for (itr_cmd = _all_command->begin(); itr_cmd != _all_command->end(); ++itr_cmd) {
      (*itr_cmd)->print_after_parsing();
      cerr << endl;
   }
}


void Program::process_after_parsing () {
   create_all_vars();
   create_label_2_command();

   list<Command *>::iterator itr;
   for (itr = _all_command->begin(); itr != _all_command->end(); ++itr) {
      list<Command *>::iterator itr_temp = itr;
      ++itr_temp;
      if (itr_temp != _all_command->end())
         (*itr)->process_after_parsing(this, *itr_temp);
      else
         (*itr)->process_after_parsing(this, NULL);
   }
   
   process_entry_point();
}


void Program::create_all_vars() {
   list<string *>::iterator itr_var;
   for (itr_var = _list_of_var->begin(); itr_var != _list_of_var->end(); ++itr_var) {
      if(_all_vars.find(**itr_var) != _all_vars.end()) {
         log_warn("The variable " << **itr_var << " is declared more than once." << endl);
      }
      else
         _all_vars.insert(**itr_var);
   }
}

bool Program::exist_variable(const std::string &name) {
   if (_all_vars.find(name) != _all_vars.end())
      return true;
   else
      return false;
}


void Program::create_label_2_command() {
   list<Command *>::const_iterator itr;
   for (itr = _all_command->begin(); itr != _all_command->end(); ++itr) {
      if (_label_2_command.find((*itr)->get_label()) != _label_2_command.end() ) {
         log_error("Label " << (*itr)->get_label() << " appear more than once." << endl);
         exit (1);
      }
      else {
         _label_2_command[(*itr)->get_label()] = *itr;
      }
   }
}

Command *Program::get_command_for_label(const std::string &label) {
   if (_label_2_command.find(label) != _label_2_command.end())
      return(_label_2_command[label]);
   else
      return(NULL);
}

void Program::process_entry_point() {
   list<Command *>::iterator itr;
   for (itr = _all_command->begin(); itr != _all_command->end(); ++itr) 
      if (!(*itr)->has_incoming_edges()) {
         if (_entry_point != NULL) {
            log_error("The program has more than one node with no incoming edges." \
                      << " Detected label " << (*itr)->get_label() << endl;)
               exit (1);
         }
         _entry_point = *itr;
      }

   if (_entry_point == NULL) {
      log_error("The program has no entry point. (entry point is a node with no incoming edges.)" << endl;);
      exit (1);
   }
}


