
%{

#include <cstring>  // for strlen(), etc.
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <list>
#include <utility>

#include "yacc_functions.h"

#include "command.h"
#include "expr.h"
#include "assigned_val.h"
#include "assertion.h"

#include "program.h"
#include "logger.h"

   
using namespace std;

#define YYERROR_VERBOSE

extern Location_Manager PA_LOC_MAN;
extern int yylex();
extern int yyerror (const char *);
extern Program PROGRAM; 


%}


%union {
   string *str;
   Token *token_ptr;
   list<Token *> *list_of_token_ptr;
   int intt;
   bool boolian;
   list<string *> *list_of_string_ptr;

   Assigned_Val *assigned_val_ptr;
   Assignment *assignment_ptr;
   Command *command_ptr;
   list<Command *> *list_of_command_ptr;
   Expr *expr_ptr;
   
   Atom *atom_ptr;
   Andc *andc_ptr;
   Orc *orc_ptr;
}


%token ASSUME;
%token ASSERT;
%token PRINT;
%token SKIP;
%token TRUE;
%token FALSE;
%token EVEN_tkn;
%token ODD_tkn;



%token <token_ptr> OPEN_BRACE;
%token <token_ptr> CLOSE_BRACE;
%token <token_ptr> OPEN_PARANTESSIS;
%token <token_ptr> CLOSE_PARANTESSIS;
%token <token_ptr> NEGATION;

%token <token_ptr> IDENTIFIER
%token <token_ptr> NUMBER
%token <token_ptr> STRING

%token ASSIGN
%token BIGGER_OR_EQ
%token LESS_OR_EQ
%token EQUAL
%token DIFFER

%token AND
%token IMPLY
%token OR
%token QUESTION_MARK
%token COLON
%token CONVERT_TO
%token FIRST_LEVEL

%type <list_of_string_ptr> list_of_identifier

%type <assigned_val_ptr> assigned_val
%type <assignment_ptr> assignment

%type <expr_ptr> expr
%type <expr_ptr> var_var
%type <expr_ptr> var_num
%type <expr_ptr> true_false

%type <command_ptr> command
%type <command_ptr> assume
%type <command_ptr> assert
 //%type <command_ptr> print
%type <command_ptr> skip

%type <command_ptr> line
%type <list_of_command_ptr> list_of_line

%type <atom_ptr> atom
%type <andc_ptr> andc
%type <orc_ptr> orc


%left '.'
%left IMPLY
%left OR
%left AND
%left NEGATION

%%


start: list_of_identifier ';' list_of_line 
       {
          PROGRAM.set_list_of_var($1);
          PROGRAM.set_all_command($3);
       }
;


line: IDENTIFIER command IDENTIFIER
      {
         $2->set_label($1->get_txt());
         $2->set_goto_label($3->get_txt());
         $$ = $2;
      }
;

list_of_line: line
              {
                 $$ = new list<Command *>;
                 $$->push_front($1);
              }
            | line list_of_line
              {
                 $2->push_front($1);
                 $$=$2;
              }
;


command: skip {$$=$1;} | assignment {$$=$1;} | assume {$$=$1;} | assert {$$ = $1;}
;



assignment: IDENTIFIER ASSIGN assigned_val
            {
               $$ = new Assignment($1->get_txt(),$3);
            }
;

assigned_val: NUMBER
            {
               $$=new Number($1->get_txt());
            }
            | IDENTIFIER
            {
               $$=new Var($1->get_txt());
            }
            | IDENTIFIER '+' NUMBER
            {
               $$=new Plus1($1->get_txt());
            }
            | IDENTIFIER '-' NUMBER
            {
               $$=new Minus1($1->get_txt());
            }
            | '?'
            {
               $$=new Question_Mark();
            }
;

assume: ASSUME OPEN_PARANTESSIS expr CLOSE_PARANTESSIS
        {
           $$ = new Assume($3);
        }
;
 

expr: var_var {$$=$1;} | var_num {$$=$1;} | true_false {$$=$1;}
;


var_var: IDENTIFIER EQUAL IDENTIFIER
         {
            $$ = new Var_EQ_Var($1->get_txt(),$3->get_txt());
         }
       | IDENTIFIER DIFFER IDENTIFIER
         {
            $$ = new Var_DF_Var($1->get_txt(),$3->get_txt());
         } 
;

var_num: IDENTIFIER EQUAL NUMBER
         {
            $$ = new Var_EQ_Num($1->get_txt(),$3->get_txt());
         }
       | IDENTIFIER DIFFER NUMBER
         {
            $$ = new Var_DF_Num($1->get_txt(),$3->get_txt());
         } 
;

true_false: TRUE
            {
               $$ = new True_False(1);
            }
          | FALSE
            {
               $$ = new True_False(0);
            }
;

assert: ASSERT orc
        {
           //cerr << "Got ASSERT" << endl;
           $$ = new Assertion($2);
        }
;

orc: OPEN_PARANTESSIS andc CLOSE_PARANTESSIS
     {
        $$ = new Orc();
        $$->add_andc($2);
     }
   | OPEN_PARANTESSIS andc CLOSE_PARANTESSIS orc
     {
        $4->add_andc($2);
        $$ = $4;
     }
;

andc: atom
     {
        $$ = new Andc ();
        $$->add_atom($1);
     }
   | atom andc
     {
        $2->add_atom($1);
        $$ = $2;
     } 
;

atom: EVEN_tkn IDENTIFIER
      {
         $$ = new Atom($2->get_txt(), Atom::EVEN);
      }
    | ODD_tkn IDENTIFIER
      {
         $$ = new Atom($2->get_txt(), Atom::ODD);
      }
;


skip: SKIP {$$ = new Skip();}
;


list_of_identifier: IDENTIFIER
                    {
                       //cerr << "Got identifier 1: " << *$1->get_txt() << endl;
                       $$ = new list <string *>;
                       $$->push_front($1->get_txt());
                    }
                  | IDENTIFIER list_of_identifier
                    {
                       //cerr << "Got identifier 2: " << *$1->get_txt() << endl;
                       $2->push_front($1->get_txt());
                       $$=$2;
                    }
;





%%
