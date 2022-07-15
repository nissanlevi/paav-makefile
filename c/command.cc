#include <sstream>
#include <iostream>
#include <stdlib.h>

#include <assert.h>

#include "logger.h"
#include "line_command.h"
#include "command.h"
#include "expr.h"
#include "assigned_val.h"
#include "program.h"

using namespace std;


void Command::print_after_parsing() {
   cerr << _label << "   ";
   print();
   cerr << "   " << _goto_label ;
}



void Assignment::print() {
   cerr << _var_name << " := ";
   _assigned_val->print();
}

void Assume::print() {
   cerr << "assume (";
   _expr->print();
   cerr << ")";
}

void Skip::print() {
   cerr << "skip";
}



void Command::process_after_parsing(Program *prog, Command *next) {
   _program = prog;

   Command *__goto = prog->get_command_for_label(_goto_label);
   _goto_command = __goto;
   if (_goto_command==NULL)
      _goto_terminate = true;
   if(_goto_command != NULL)
      _goto_command->set_has_incoming_edges();
      
}

void Assume::process_after_parsing(Program *prog, Command *next) {
   Command::process_after_parsing(prog,next);
   
   _else_command = next;
   if (_else_command==NULL)
      _else_terminate = true;

   if (_else_command!=NULL)
      _else_command->set_has_incoming_edges();

   _expr->process_after_parsing(prog,this);
}

void Assignment::process_after_parsing(Program *prog, Command *next) {
   Command::process_after_parsing(prog,next);

   if (!prog->exist_variable(_var_name)) {
      log_error("Usage of undeclared variable. Var name is: " << _var_name << endl);
      exit(1);
   }

   _assigned_val->process_after_parsing(prog,this);
}

void Skip::process_after_parsing(Program *prog, Command *next) {
   Command::process_after_parsing(prog,next);
}

























#ifdef IGNORE

void Substitute::validate(const Top &top) {
   if (top.get_item(_item_name) == NULL) {
      log_error("substitute command uses an undefined item: " << _item_name << endl);
      exit (2);
   }

   list<pair<string *, Term *> >::iterator itr = _all_subs->begin();
   set<string> all_vars;
   for ( ; itr!=_all_subs->end(); ++itr) {
      const string &from = *(*itr).first;
      if (all_vars.find(from) != all_vars.end()) {
         log_error("substitute command: Variable \"" << from << "\" appears more than once." << endl);
         exit (1);
      }
      all_vars.insert(from);
   }
}


void Substitute::process(const Top &top) {
   validate(top);
   
   Item *item = NULL;
   if ((item = top.get_item(_item_name)) == NULL) {
      log_error("substitute command uses an undefined item: " << _item_name << endl);
      exit (2);
   }
   assert (_all_subs != NULL);

   string message = "Performing substitution in ";
   if (dynamic_cast<Formula *>(item) != NULL)
      message += "Formula ";
   else
      message += "Term ";
   message += _item_name + ":";
   log_info(message << endl);


   Item *new_item = item->clone();
   new_item->process();

   list<pair<string *, Term *> >::iterator itr = _all_subs->begin();
   for(; itr != _all_subs->end(); ++itr) {
      Term *term = (*itr).second;
      term->process();
   }

   new_item->substitute(_all_subs);

   log_info("Substitution result : " ); new_item->print_flat();  cerr << endl;


   
   /*
      const string &free_var_name = (*itr_assi)->get_free_var_name();
      if (_assignments.find(free_var_name) != _assignments.end()) {
         log_error("substituion of variable " << free_var_name << " more that once" << endl);
         exit(2);
      }
      pair<string, Term *> p(free_var_name, (*itr_assi)->get_term());
      _assignments[free_var_name] = p;*/

}






void Rename_Bound::validate(const Top &top) {
   if (top.get_item(_item_name) == NULL) {
      log_error("bound-rename command uses an undefined item: " << _item_name << endl);
      exit (2);
   }
   list<pair<string *, string *> >::iterator itr = _all_from_to->begin();
   set<string> all_vars;
   for ( ; itr!=_all_from_to->end(); ++itr) {
      const string &from = *(*itr).first;
      if (all_vars.find(from) != all_vars.end()) {
         log_error("bound-rename command: illegal list of renaming. Variable \"" << from << "\" appears more than once." << endl);
         exit (1);
      }
      all_vars.insert(from);
      const string &to = *(*itr).second;
      if (all_vars.find(to) != all_vars.end()) {
         log_error("bound-rename command: illegal list of renaming. A variable \"" << to << "\" appears more than once." << endl);
         exit (1);
      }
      all_vars.insert(to);
   }
}

void Rename_Bound::process(const Top &top) {
   validate(top);

   Item *item = top.get_item(_item_name);
   Item *new_item = item->clone();
   new_item->process();
   string failing_from;
   string failing_to;
   if (!new_item->possible_to_rename_bound(failing_from,failing_to,_all_from_to)) {
      log_error("bound-rename command: illegal to rename " << failing_from << " with " << failing_to << " in " << _item_name << " due to capturing of free variables" << endl);
      exit (2);
   }
   new_item->perform_rename_bound_list(_all_from_to);

   string message = "Changing bounded variables in ";
   if (dynamic_cast<Formula *>(new_item) != NULL)
      message += "Formula ";
   else
      message += "Term ";
   message += _item_name + ":";
   log_info(message << endl);
   log_info("" ); new_item->print_flat();
   cerr << endl;
}

#endif
