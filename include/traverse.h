#ifndef TRAVERSE_H
#define TRAVERSE_H

class Program;
class Command;
class Expr;
class Assigned_Val;
class Orc;
class Andc;
class Atom;

class Traverse {
public:
   Traverse() : _prog(NULL) {}

   void set_program(Program *prog) {_prog = prog;}
   void pretty_print();

   void print_all_vars();
   void print_all_commands();
   void print_command(Command *cmd);
   void print_goto_label(Command *cmd, bool put_endl=true);

   void print_expr(Expr *expr);
   void print_assigned_val(Assigned_Val *assigned_val);
   void print_orc(Orc *);
   void print_andc(Andc *);
   void print_atom(Atom *);
   
private:
   Program *_prog;

};





#endif
