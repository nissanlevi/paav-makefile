
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <queue>

#include <assert.h>

#include "logger.h"
#include "traverse.h"
#include "program.h"
#include "command.h"
#include "assertion.h"
#include "expr.h"
#include "assigned_val.h"

using namespace std;


void Traverse::pretty_print() {
   cerr << endl << "From Traverse::pretty_print" << endl;
   print_all_vars();
   print_all_commands();
}

void Traverse::print_all_vars() {
   cerr << "Vars are: ";
   
   set<string> &all_vars = _prog->get_all_vars();
   set<string>::iterator itr;
   for(itr = all_vars.begin(); itr != all_vars.end(); ++itr)
      cerr << *itr << "  ";
   cerr << endl << endl;
}

void Traverse::print_all_commands() {
   Command *entry_command = _prog->get_entry_point();
   assert (entry_command != NULL);
   
   queue<Command *> q;
   set <Command *> already_printed;
   q.push(entry_command);
   
   while (!q.empty()) {
      Command *curr = q.front();
      q.pop();
      if (already_printed.find(curr) == already_printed.end()) { // need to print the command
         already_printed.insert(curr);
         print_command(curr);
         Command *goto_command = curr->get_goto_command();
         Command *else_command = NULL;
         if (curr->is_assume())
            else_command = (dynamic_cast<Assume *>(curr))->get_else_command();

         if (goto_command != NULL)
            q.push(goto_command);
         if (else_command != NULL)
            q.push(else_command);
      }
   }
}

void Traverse::print_command(Command *cmd) {
   cerr << cmd->get_label() << " ";
   if (cmd->is_assume()) {
      Assume *assume = dynamic_cast<Assume *>(cmd);
      cerr << "if/assume (";
      print_expr(assume->get_expr());
      cerr << ")";
      cerr << " goto ";
      print_goto_label(cmd,false);
      cerr << " else goto ";
      if (assume->is_else_terminate())
         cerr << "terminate" << endl;
      else
         cerr << assume->get_else_command()->get_label() << endl ;
   }
   else if (cmd->is_assigment()) {
      Assignment *assignment = dynamic_cast<Assignment *>(cmd);
      cerr << assignment->get_var_name() << " := ";
      print_assigned_val(assignment->get_assigned_val());
      print_goto_label(cmd);
   }
   else if (cmd->is_skip()) {
      cerr << " skip";
      print_goto_label(cmd);      
   }
   else if (cmd->is_assertion()) {
      Assertion *assertion = dynamic_cast<Assertion *>(cmd);
      cerr << "assert ( ";
      print_orc(assertion->get_orc());
      cerr << " )";
      print_goto_label(cmd);            
   }
   else {
      log_error("Can't come here" << endl);
      exit(1) ;
   }
}

void Traverse::print_goto_label(Command *cmd, bool put_endl) {
   if (cmd->is_goto_terminate())
      cerr << " terminate";
   else
      cerr << " " << cmd->get_goto_command()->get_label();

   if (put_endl)
      cerr << endl;
}

void Traverse::print_expr(Expr *expr) {
   if (expr->is_var_eq_var()) {
      Var_EQ_Var *ex = dynamic_cast<Var_EQ_Var *>(expr);
      cerr << ex->get_var_left() << "==" << ex->get_var_right() ;
   }
   else if (expr->is_var_df_var()) {
      Var_DF_Var *ex = dynamic_cast<Var_DF_Var *>(expr);
      cerr << ex->get_var_left() << "!=" << ex->get_var_right() ;
   }
   else if (expr->is_var_eq_num()) {
      Var_EQ_Num *ex = dynamic_cast<Var_EQ_Num *>(expr);
      cerr << ex->get_var() << "==" << ex->get_num();
   }
   else if (expr->is_var_df_num()) {
      Var_DF_Num *ex = dynamic_cast<Var_DF_Num *>(expr);
      cerr << ex->get_var() << "!=" << ex->get_num();
   }
   else if (expr->is_true()) {
      cerr << "TRUE";
   }
   else if (expr->is_false()) {
      cerr << "FALSE";
   }
   else {
      log_error("Can't come here" << endl);
      exit(1) ;
   }

}

void Traverse::print_assigned_val(Assigned_Val *assigned_val) {
   if (assigned_val->is_number()) {
      Number *num = dynamic_cast<Number *>(assigned_val);
      cerr << num->get_number();
   }
   else if (assigned_val->is_var()) {
      Var *v = dynamic_cast<Var *>(assigned_val);
      cerr << v->get_name();
   }
   else if (assigned_val->is_question_mark()) {
      cerr << " ? ";
   }
   else if (assigned_val->is_plus1()) {
      Plus1 *p = dynamic_cast<Plus1 *>(assigned_val);
      cerr << p->get_name() << " + 1 ";
   }
   else if (assigned_val->is_minus1()) {
      Minus1 *m = dynamic_cast<Minus1 *>(assigned_val);
      cerr << m->get_name() << " - 1 ";
   }
}


void Traverse::print_orc(Orc *orc) {
   list<Andc *> &all_andc = orc->get_all_andc();
   list<Andc *>::iterator i;
   for (i=all_andc.begin(); i != all_andc.end(); ++i) {
      cerr << "( ";
      print_andc(*i);
      cerr << " ) ";
   }
}

void Traverse::print_andc(Andc *andc) {
   list<Atom *> &all_atom = andc->get_all_atom();
   list<Atom *>::iterator i;
   for (i=all_atom.begin(); i != all_atom.end(); ++i) {
      //      cerr << "( ";
      print_atom(*i);
      cerr << " ";
   }
}

void Traverse::print_atom(Atom *atom) {
   if (atom->get_parity() == Atom::EVEN)
      cerr << "EVEN ";
   else
      cerr << "ODD ";

   cerr << atom->get_var_name();
}





