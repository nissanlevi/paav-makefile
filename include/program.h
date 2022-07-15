#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <list>
#include <map>
#include <set>

class Command;
class Formula;

#undef CANT_BE_CALLED
#define CANT_BE_CALLED(name) std::cerr << "Internal error. a call to void Program::" #name "()." << std::endl;  ; exit (2);


/* ======================================================================================
   Note: All the interface methods listed below may be used only after 
   process_after_parsing() is performed.
   ======================================================================================*/


/*==================================================================================
  Program: Holds the entire program
  ==================================================================================*/
class Program {
public:
   // ******   Interface methods ************************************
   std::set<std::string> &get_all_vars() {return _all_vars;}
   std::list<Command *> *get_all_command() {return _all_command;} // the commands in the order of appearance in the program
   std::map<std::string,Command *> get_label_2_command() {return _label_2_command;}
   
   Command *get_entry_point() {return _entry_point;}  // _entry_point is the first command to be executed
   Command *get_command_for_label(const std::string &label);



   
   // ******    Internal work methods    ****************************
   Program() : _entry_point(NULL) {}
   void print_after_parsing();
   bool exist_variable(const std::string &name);

   // The following method is called after parsing and perfoms the following:
   // 1. Basic sanity checks of label and variables.
   // 2. Each command has a pointer to its "goto command", and in case of assume
   //    command also to the "else command".
   void process_after_parsing(); 
   
   // The following two methods are called during parsing stage.
   void set_all_command(std::list<Command *> *all_command) {_all_command = all_command;}
   void set_list_of_var(std::list<std::string *> *list_of_var) {_list_of_var = list_of_var;}

private:
   void create_all_vars();
   void create_label_2_command();
   void process_goto_labels();
   void process_entry_point();

private:
   std::list<std::string *> *_list_of_var;
   std::list<Command *> *_all_command;

   std::set<std::string> _all_vars;
   std::map<std::string,Command *> _label_2_command;
   Command *_entry_point; // this is the first command
};


#endif
