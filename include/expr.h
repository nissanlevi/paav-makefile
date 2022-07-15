#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <list>
#include <map>
#include <set>



class Program;
class Command;

#undef CANT_BE_CALLED
#define CANT_BE_CALLED(name) std::cerr << "Internal error. a call to void Message::" #name "()." << std::endl;  ; exit (2);

/* ======================================================================================
   Note: All the interface methods listed below may be used only after 
   process_after_parsing() is performed.
   ======================================================================================*/


/*===============================================================================================
  Expr: any expression that can appear in assume( )
  For example: i != j
  =============================================================================================*/
class Expr {
public:
   // ******   Interface methods ************************************
   virtual bool is_var_eq_var() {return false;}
   virtual bool is_var_df_var() {return false;}
   virtual bool is_var_eq_num() {return false;}
   virtual bool is_var_df_num() {return false;}
   virtual bool is_true() {return false;}
   virtual bool is_false() {return false;}
   Command *get_parent() {return _parent;}   // return a pointer to the parent command


   // ******    Internal work methods    ****************************
   Expr() : _program(NULL), _parent(NULL) {} 
   virtual void print() = 0;

   virtual void process_after_parsing(Program *prog, Command *parent);
protected:
   Program *_program;
   Command *_parent;
};



class Var_Var : public Expr {
public:
   // ******   Interface methods ************************************
   const std::string &get_var_left() {return _var_left;}
   const std::string &get_var_right() {return _var_right;}


   // ******    Internal work methods    ****************************
   Var_Var (std::string *var_left, std::string *var_right) :
      Expr(), _var_left(*var_left), _var_right(*var_right) {}
   //   virtual void print();

   virtual void process_after_parsing(Program *prog, Command *next);

protected:
   std::string _var_left;
   std::string _var_right;
};



class Var_Num : public Expr {
public:
   // ******   Interface methods ************************************
   const std::string &get_var() {return _var;}
   int get_num() {return _num;}


   // ******    Internal work methods    ****************************
   Var_Num (std::string *var, std::string *num_str);
   virtual void process_after_parsing(Program *prog, Command *next);

protected:
   std::string _var;
   std::string _num_str;
   int _num;
};



class Var_EQ_Var : public Var_Var {
public:
   // ******   Interface methods ************************************
   virtual bool is_var_eq_var() {return true;}


   // ******    Internal work methods    ****************************
   Var_EQ_Var(std::string *var_left, std::string *var_right) : Var_Var(var_left,var_right) {}
   virtual void print();
};



class Var_DF_Var : public Var_Var {
public:
   // ******   Interface methods ************************************
   virtual bool is_var_df_var() {return true;}


   // ******    Internal work methods    ****************************
   Var_DF_Var(std::string *var_left, std::string *var_right) : Var_Var(var_left,var_right) {}
   virtual void print();
};



class Var_EQ_Num : public Var_Num {
public:
   // ******   Interface methods ************************************
   virtual bool is_var_eq_num() {return true;}


   // ******    Internal work methods    ****************************
   Var_EQ_Num(std::string *var_left, std::string *var_right) : Var_Num(var_left,var_right) {}
   virtual void print();
};



class Var_DF_Num : public Var_Num {
public:
   // ******   Interface methods ************************************
   virtual bool is_var_df_num() {return true;}


   // ******    Internal work methods    ****************************
   Var_DF_Num(std::string *var_left, std::string *var_right) : Var_Num(var_left,var_right) {}
   virtual void print();
};


class True_False : public Expr {
public:
   // ******   Interface methods ************************************
   virtual bool is_true() {return _val;}
   virtual bool is_false() {return !_val;}


   // ******    Internal work methods    ****************************
   True_False (bool val) : Expr(), _val(val) {}
   virtual void print();

protected:
   bool _val;
};



#endif
