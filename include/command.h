#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <list>
#include <map>
#include <set>



class Top;
class Expr;
class Assigned_Val;
class Program;

#undef CANT_BE_CALLED
#define CANT_BE_CALLED(name) std::cerr << "Internal error. a call to void Command::" #name "()." << std::endl;  ; exit (2);

/* ======================================================================================
   Note: All the interface methods listed below may be used only after 
   process_after_parsing() is performed.
   ======================================================================================*/



/*===============================================================================================
  Command: Any line of the program including the first and seconf labels.
  =============================================================================================*/
class Command {
public:
   // ******   Interface methods ************************************
   virtual bool is_assume() {return false;}
   virtual bool is_assigment() {return false;}
   virtual bool is_skip() {return false;}
   virtual bool is_assertion() {return false;}

   // In the command:  "L0  i=22  L1", L0 is the label, and L1 is the goto_label.
   const std::string &get_label() const {return _label;}
   const std::string &get_goto_label() const {return _goto_label;}
   
   // In the command:  "L0  i=22  L1" the goto command is the command with label L1
   Command *get_goto_command() {return _goto_command;}

   // the following return true iff the goto-label doesn't exist as a label (so the execution terminates after current command)
   bool is_goto_terminate()  {return _goto_terminate;}

   // If no incoming edges, this is the enrty point to the program
   bool has_incoming_edges() {return _has_incoming_edges;}

   

   // ******    Internal work methods    ****************************
   Command() :
      _program(NULL), _goto_command(NULL), _goto_terminate(false), _has_incoming_edges(false) {}
   virtual void print() = 0;
   virtual void print_after_parsing();
   virtual void process_after_parsing(Program *prog, Command *next) = 0;
   void set_has_incoming_edges() {_has_incoming_edges = true;}

   //The following two methods are for the parsing stage
   void set_label(std::string *label) {_label = *label;}
   void set_goto_label(std::string *goto_label) {_goto_label = *goto_label;}
protected:
   std::string _label;
   std::string _goto_label;
   
   Program *_program;

   Command *_goto_command;
   bool _goto_terminate;
   bool _has_incoming_edges;
};


/*===============================================================================================
  Assume: for lines like: L0 assume(i = n) L1
  =============================================================================================*/
class Assume : public Command {
public:
   // ******   Interface methods ************************************
   virtual bool is_assume() {return true;}
   Command *get_else_command() {return _else_command;} // the else command is always the next one
   bool is_else_terminate()  {return _else_terminate;}
   Expr *get_expr() {return _expr;}



   // ******    Internal work methods    ****************************
   Assume(Expr *expr) : _expr(expr), _else_command(NULL), _else_terminate(false) {}
   virtual void print();
   virtual void process_after_parsing(Program *prog, Command *next);

private:
   Expr *_expr;
   Command *_else_command; // relevant only for assume command
   bool _else_terminate;
};







/*===============================================================================================
  Assignment: for lines like: L0  i=j+1  L1
  =============================================================================================*/
class Assignment : public Command {
public:
   // ******   Interface methods ************************************
   virtual bool is_assigment() {return true;}
   const std::string &get_var_name() {return _var_name;}
   Assigned_Val *get_assigned_val() {return _assigned_val;}


   // ******    Internal work methods    ****************************
   Assignment(std::string *var_name, Assigned_Val *assigned_val) :
      _var_name(*var_name), _assigned_val(assigned_val) {}
   virtual void print();
   virtual void process_after_parsing(Program *prog, Command *next);

private:
   std::string _var_name;
   Assigned_Val *_assigned_val;
};



class Skip : public Command {
public:
   // ******   Interface methods ************************************
   virtual bool is_skip() {return true;}

   
   // ******    Internal work methods    ****************************
   Skip() {}
   virtual void print() ;
   virtual void process_after_parsing(Program *prog, Command *next);
};













/*
class Command {
public:
   Command() {}
   
   virtual void process(const Top &top) = 0;
private:
   
};



class Substitute : public Command {
public:
   Substitute(std::string *item_name, std::list<std::pair<std::string *, Term *> > *all_subs) : _item_name(*item_name), _all_subs(all_subs) {}
   
   virtual void process(const Top &top);
   
private:
   void validate(const Top &top);

private:
   std::string _item_name;
   std::list<std::pair<std::string *, Term *> > *_all_subs;
};

class Rename_Bound : public Command {
public:
   Rename_Bound(std::string *item_name, std::list<std::pair<std::string *, std::string *> > *all_from_to) :
      _item_name(*item_name), _all_from_to(all_from_to) {}
   
   virtual void process(const Top &top);
   
private:
   void validate(const Top &top);

private:
   std::string _item_name;
   std::list<std::pair<std::string *, std::string *> > *_all_from_to;
};
*/


#endif
