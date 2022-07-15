#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "logger.h"
#include "assigned_val.h"
#include "program.h"

using namespace std;

/*
void Assignment::print() {
   cerr << _var_name << " := ";
   _assigned_val->print();
}
*/

Number::Number(std::string *name) : _name(*name), _number(INT_MIN) {
   _number = stoi(*name);
}

void Number::print() {
   cerr << _name;
}

void Var::print() {
   cerr << _name;
}

void Question_Mark::print() {
   cerr << " ? ";
}

void Minus1::print() {
   cerr << _name << "-1";
}

void Plus1::print() {
   cerr << _name << "+1";
}

void Var::process_after_parsing(Program *prog, Command *parent) {
   Assigned_Val::process_after_parsing(prog, parent);
   
   if (!prog->exist_variable(_name)) {
      log_error("Usage of undeclared variable. Var name is: " << _name << endl);
      exit(1);
   }
}

void Oper1::process_after_parsing(Program *prog, Command *parent) {
   Assigned_Val::process_after_parsing(prog, parent);
   
   if (!prog->exist_variable(_name)) {
      log_error("Usage of undeclared variable. Var name is: " << _name << endl);
      exit(1);
   }
}



