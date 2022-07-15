#ifndef ASSIGNED_VAL_H
#define ASSIGNED_VAL_H

#include <string>
#include <list>
#include <map>
#include <set>


class Program;
class Command;
class Expr;

#undef CANT_BE_CALLED
#define CANT_BE_CALLED(name) std::cerr << "Internal error. a call to void Message::" #name "()." << std::endl;  ; exit (2);


/* ======================================================================================
   Note: All the interface methods listed below may be used only after 
   process_after_parsing() is performed.
   ======================================================================================*/


/*===============================================================================================
  Assigned_Val: any expression that can appear right to :=.
                For example in "i:=j+1", the "j+1".
  =============================================================================================*/
class Assigned_Val {
public:
   // ******   Interface methods ************************************
   Command *get_parent() {return _parent;}   // return a pointer to the parent command
   virtual bool is_number() {return false;}
   virtual bool is_var() {return false;}
   virtual bool is_question_mark() {return false;}
   virtual bool is_plus1() {return false;}
   virtual bool is_minus1() {return false;}

   

   // ******    Internal work methods    ****************************
   Assigned_Val() : _program(NULL), _parent(NULL) {}
   virtual void print() = 0;
   virtual void process_after_parsing(Program *prog, Command *parent) {_program=prog; _parent=parent;}

protected:
   Program *_program;
   Command *_parent;
};


class Number : public Assigned_Val {
public:
   // ******   Interface methods ************************************
   virtual bool is_number() {return true;}
   int get_number() {return _number;}



   // ******    Internal work methods    ****************************
   Number(std::string *name);// : _name(*name), _number(INT_MIN) {}

   virtual void validate_variables() {}
   virtual void print();

private:
   std::string _name;
   int _number; // Nissan need to calculate _number
};

class Var : public Assigned_Val {
public:
   // ******   Interface methods ************************************
   virtual bool is_var() {return true;}
   const std::string &get_name() {return _name;}


   // ******    Internal work methods    ****************************
   Var(std::string *name) : _name(*name) {}

   virtual void print();
   virtual void process_after_parsing(Program *prog, Command *parent);
private:
   std::string _name;
};

class Question_Mark : public Assigned_Val {
public:
   // ******   Interface methods ************************************
   virtual bool is_question_mark() {return true;}



   // ******    Internal work methods    ****************************
   Question_Mark() {}

   virtual void print();
};

class Oper1 : public Assigned_Val {
public:
   Oper1(std::string *name) : _name(*name) {}

   virtual void process_after_parsing(Program *prog, Command *parent);
protected:
   std::string _name;
};



class Plus1 : public Oper1 {
public:
   // ******   Interface methods ************************************
   virtual bool is_plus1() {return true;}
   const std::string &get_name() {return _name;}

   // ******    Internal work methods    ****************************
   Plus1(std::string *name) : Oper1(name) {}
   virtual void print();
};

class Minus1 : public Oper1 {
public:
   // ******   Interface methods ************************************
   virtual bool is_minus1() {return true;}
   const std::string &get_name() {return _name;}


   // ******    Internal work methods    ****************************
   Minus1(std::string *name) : Oper1(name) {}
   virtual void print();
};


#endif


