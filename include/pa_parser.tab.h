/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with pa_parser_YY_ or pa_parser_yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef pa_parser_YY_pa_parser_YY_PA_PARSER_TAB_H_INCLUDED
# define pa_parser_YY_pa_parser_YY_PA_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef pa_parser_YYDEBUG
# define pa_parser_YYDEBUG 0
#endif
#if pa_parser_YYDEBUG
extern int pa_parser_yydebug;
#endif

/* Token kinds.  */
#ifndef pa_parser_YYTOKENTYPE
# define pa_parser_YYTOKENTYPE
  enum pa_parser_yytokentype
  {
    pa_parser_YYEMPTY = -2,
    pa_parser_YYEOF = 0,                     /* "end of file"  */
    pa_parser_YYerror = 256,                 /* error  */
    pa_parser_YYUNDEF = 257,                 /* "invalid token"  */
    ASSUME = 258,                  /* ASSUME  */
    ASSERT = 259,                  /* ASSERT  */
    PRINT = 260,                   /* PRINT  */
    SKIP = 261,                    /* SKIP  */
    TRUE = 262,                    /* TRUE  */
    FALSE = 263,                   /* FALSE  */
    EVEN_tkn = 264,                /* EVEN_tkn  */
    ODD_tkn = 265,                 /* ODD_tkn  */
    OPEN_BRACE = 266,              /* OPEN_BRACE  */
    CLOSE_BRACE = 267,             /* CLOSE_BRACE  */
    OPEN_PARANTESSIS = 268,        /* OPEN_PARANTESSIS  */
    CLOSE_PARANTESSIS = 269,       /* CLOSE_PARANTESSIS  */
    NEGATION = 270,                /* NEGATION  */
    IDENTIFIER = 271,              /* IDENTIFIER  */
    NUMBER = 272,                  /* NUMBER  */
    STRING = 273,                  /* STRING  */
    ASSIGN = 274,                  /* ASSIGN  */
    BIGGER_OR_EQ = 275,            /* BIGGER_OR_EQ  */
    LESS_OR_EQ = 276,              /* LESS_OR_EQ  */
    EQUAL = 277,                   /* EQUAL  */
    DIFFER = 278,                  /* DIFFER  */
    AND = 279,                     /* AND  */
    IMPLY = 280,                   /* IMPLY  */
    OR = 281,                      /* OR  */
    QUESTION_MARK = 282,           /* QUESTION_MARK  */
    COLON = 283,                   /* COLON  */
    CONVERT_TO = 284,              /* CONVERT_TO  */
    FIRST_LEVEL = 285              /* FIRST_LEVEL  */
  };
  typedef enum pa_parser_yytokentype pa_parser_yytoken_kind_t;
#endif
/* Token kinds.  */
#define pa_parser_YYEMPTY -2
#define pa_parser_YYEOF 0
#define pa_parser_YYerror 256
#define pa_parser_YYUNDEF 257
#define ASSUME 258
#define ASSERT 259
#define PRINT 260
#define SKIP 261
#define TRUE 262
#define FALSE 263
#define EVEN_tkn 264
#define ODD_tkn 265
#define OPEN_BRACE 266
#define CLOSE_BRACE 267
#define OPEN_PARANTESSIS 268
#define CLOSE_PARANTESSIS 269
#define NEGATION 270
#define IDENTIFIER 271
#define NUMBER 272
#define STRING 273
#define ASSIGN 274
#define BIGGER_OR_EQ 275
#define LESS_OR_EQ 276
#define EQUAL 277
#define DIFFER 278
#define AND 279
#define IMPLY 280
#define OR 281
#define QUESTION_MARK 282
#define COLON 283
#define CONVERT_TO 284
#define FIRST_LEVEL 285

/* Value type.  */
#if ! defined pa_parser_YYSTYPE && ! defined pa_parser_YYSTYPE_IS_DECLARED
union pa_parser_YYSTYPE
{
#line 35 "c/pa_parser.y"

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

#line 146 "pa_parser.tab.h"

};
typedef union pa_parser_YYSTYPE pa_parser_YYSTYPE;
# define pa_parser_YYSTYPE_IS_TRIVIAL 1
# define pa_parser_YYSTYPE_IS_DECLARED 1
#endif


extern pa_parser_YYSTYPE pa_parser_yylval;


int pa_parser_yyparse (void);


#endif /* !pa_parser_YY_pa_parser_YY_PA_PARSER_TAB_H_INCLUDED  */
