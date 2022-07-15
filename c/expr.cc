#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

#include "expr.h"
#include "logger.h"
#include "program.h"

using namespace std;



void Var_EQ_Var::print() {
   cerr << _var_left << " == " << _var_right;
}

void Var_DF_Var::print() {
   cerr << _var_left << " != " << _var_right;
}

void Var_EQ_Num::print() {
   cerr << _var << " == " << _num;
}

void Var_DF_Num::print() {
   cerr << _var << " != " << _num;
}

void True_False::print() {
   if (_val)
      cerr << "TRUE";
   else
      cerr << "FALSE";
}

void Expr::process_after_parsing(Program *prog, Command *parent) {
   _program = prog;
   _parent = parent;
}

void Var_Var::process_after_parsing(Program *prog, Command *parent) {
   Expr::process_after_parsing(prog,parent);

   if (!prog->exist_variable(_var_left)) {
      log_error("Usage of undeclared variable. Var name is: " << _var_left << endl);
      exit(1);
   }
   if (!prog->exist_variable(_var_right)) {
      log_error("Usage of undeclared variable. Var name is: " << _var_right << endl);
      exit(1);
   }
}

Var_Num::Var_Num (std::string *var, std::string *num_str): Expr(), _var(*var), _num_str(*num_str),_num(INT_MIN)  {
   _num = stoi(_num_str);
}


void Var_Num::process_after_parsing(Program *prog, Command *parent) {
   Expr::process_after_parsing(prog,parent);
   if (!prog->exist_variable(_var)) {
      log_error("Usage of undeclared variable. Var name is: " << _var << endl);
      exit(1);
   }
}




