#ifndef ASSETRION_H
#define ASSETRION_H

#include <string>
#include <list>
#include <map>
#include <set>

#include "command.h"

class Program;

/* ======================================================================================
   Note: All the interface methods listed below may be used only after 
   process_after_parsing() is performed.
   ======================================================================================*/


/*===============================================================================================
  Atom is "EVEN <var>"  or  "ODD <var>"
  =============================================================================================*/
class Atom {
public:
   // ******   Interface methods ************************************
   enum parity_type{EVEN=0, ODD=1};
   Command *get_parent() {return _parent;}   // return a pointer to the parent command
   const std::string &get_var_name() {return _var_name;}
   parity_type get_parity() {return _p;} // return EVEN or ODD


   // ******    Internal work methods    ****************************
   Atom(std::string *var_name, parity_type p) :
      _var_name(*var_name), _p(p) ,_program(NULL), _parent(NULL) {}
   void print();
   virtual void process_after_parsing(Program *prog, Command *parent);

private:
   std::string _var_name;
   parity_type _p;
   Program *_program;
   Command *_parent;
};


class Andc {
public:
   // ******   Interface methods ************************************
   std::list<Atom *> &get_all_atom() {return _all_atom;}
   Command *get_parent() {return _parent;}   // return a pointer to the parent command



   // ******    Internal work methods    ****************************
   Andc() : _program(NULL), _parent(NULL) {}
   void add_atom(Atom *atom) {_all_atom.push_back(atom);}
   void print();
   virtual void process_after_parsing(Program *prog, Command *parent);
private:
   std::list<Atom *> _all_atom;
   Program *_program;
   Command *_parent;
};

class Orc {
public:
   // ******   Interface methods ************************************
   std::list<Andc *> &get_all_andc() {return _all_andc;}
   Command *get_parent() {return _parent;}   // return a pointer to the parent command
   

   // ******    Internal work methods    ****************************
   Orc() : _program(NULL), _parent(NULL) {}
   void print();
   void add_andc(Andc *andc) {_all_andc.push_back(andc);}
   virtual void process_after_parsing(Program *prog, Command *parent);
private:
   std::list<Andc *> _all_andc;
   Program *_program;
   Command *_parent;
};




/*===============================================================================================
  Assertion: for lines like: L0  assert (ODD i ODD j) (ODD k)  L1
  =============================================================================================*/
class Assertion : public Command {
public:
   // ******   Interface methods ************************************
   virtual bool is_assertion() {return true;}
   Orc *get_orc() {return _orc;}

   // ******    Internal work methods    ****************************
   Assertion(Orc *orc): _orc(orc) {}
   virtual void print();
   virtual void process_after_parsing(Program *prog, Command *next);
private:
   Orc *_orc;
};




#endif
