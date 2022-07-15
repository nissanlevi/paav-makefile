#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "assertion.h"
#include "logger.h"
#include "program.h"

 
using namespace std;



void Atom::print() {
   if (_p==EVEN)
      cerr << "EVEN ";
   else
      cerr << "ODD ";

   cerr << _var_name;
}

void Andc::print() {
   list<Atom *>::iterator itr;
   for (itr = _all_atom.begin(); itr != _all_atom.end(); ++itr) {
      (*itr)->print();
      cerr << " ";
   }
   
}

void Orc::print() {
   list<Andc *>::iterator itr;
   for (itr = _all_andc.begin(); itr != _all_andc.end(); ++itr) {
      cerr << "(";
      (*itr)->print();
      cerr << ") ";
   }
}

void Assertion::print() {
   cerr << "assert (";
   _orc->print();
   cerr << ")";
}

void Assertion::process_after_parsing(Program *prog, Command *next) {
   Command::process_after_parsing(prog,next);

   _orc->process_after_parsing(prog,this);
}


void Orc::process_after_parsing(Program *prog, Command *parent) {
   _program=prog;
   _parent = parent;

   std::list<Andc *>::iterator itr;
   for (itr=_all_andc.begin(); itr != _all_andc.end(); ++itr)
      (*itr)->process_after_parsing(prog,parent);
}

void Andc::process_after_parsing(Program *prog, Command *parent) {
   _program=prog;
   _parent = parent;

   std::list<Atom *>::iterator itr;
   for (itr=_all_atom.begin(); itr != _all_atom.end(); ++itr)
      (*itr)->process_after_parsing(prog,parent);
}

void Atom::process_after_parsing(Program *prog, Command *parent) {
   _program=prog;
   _parent = parent;

   if (!prog->exist_variable(_var_name)) {
      log_error("Usage of undeclared variable. Var name is: " << _var_name << endl);
      exit(1);
   }
}








