
/* 
**              MOTOROLA CONFIDENTIAL PROPRIETARY 
**  Copyright (c) 1993-2001 Motorola, Inc.  All Rights Reserved. 
*/ 
 
%{

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

#include "yacc_functions.h"
#include "assertion.h"

#include "pa_parser.tab.h"

//int PA_LINE_NUMBER = 1;        //  the current line number
//int PA_COL_NUM = 0;              //  the current column number
extern Location_Manager PA_LOC_MAN;

#define COL(x) {PA_LOC_MAN.update_col(x);}
//#define COL_0  {PA_COL_NUM = 0;}

%}

space                   [ \t]*
letter                  [a-zA-Z_]
digit                   [0-9]
hexadigit		[0-9a-fA-F]

identifier              ({letter})(({letter})|({digit}))*
unsigned		({digit}+)|({digit}+U)
hexanumber		("0x"|"0X")({hexadigit}+)
string                  \"[^\"\n]*\"
float_simple            {digit}*\.{digit}+
float                   ([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+))|{float_simple}


unary_operator          ("!")
not_for_cons            ("not")
bin_op0			("."|"->")
bin_op1			("*"|"/"|"%")
bin_op2			("+"|"-")
bin_op4			(">"|">="|"<"|"<=")
bin_op5			("=="|"!=")
bin_op9 		("&&")
bin_op10		("||")
bin_op11		("and")
bin_op12		("or")

%x COMMENT
%x LINE_COMMENT

%%

"/*"                {COL(2); BEGIN COMMENT;}
"//"                {COL(2); BEGIN LINE_COMMENT; }
<COMMENT>.          {COL(1);}
<COMMENT>\n         {PA_LOC_MAN.set_new_line(); }
<COMMENT>"*/"       {COL(2); BEGIN 0;}
<LINE_COMMENT>.     {COL(1);}
<LINE_COMMENT>\n    {PA_LOC_MAN.set_new_line(); BEGIN 0;}

"assume"            {COL(10); return ASSUME;}
"assert"            {COL(10); return ASSERT;}
"print"             {COL(10); return PRINT;}
"skip"              {COL(10); return SKIP;}
"TRUE"              {COL(10); return TRUE;}
"FALSE"             {COL(10); return FALSE;}
"EVEN"              {COL(10); return EVEN_tkn;}
"ODD"               {COL(10); return ODD_tkn;}



":"                 {COL(1); return ':';}



">="  {COL(2); return BIGGER_OR_EQ; }
"<="  {COL(2); return LESS_OR_EQ; }
"=="  {COL(2); return EQUAL; }
"!="  {COL(2); return DIFFER; }
"&&"  {COL(2); return AND; }
"||"  {COL(2); return OR; }
"->"  {COL(2); return IMPLY; }
"~>"  {COL(2); return CONVERT_TO; }

":="  {COL(2); return ASSIGN;}

"|"|"&"|"$"|"@"|","|"["|"]"|"="|"#"|";"|"."|"!" {COL(1); return yytext[0];}
"{" {
   COL(1);
   string *tmp = new std::string (yytext);
   yylval.token_ptr = new Token (tmp,PA_LOC_MAN.get_line(),PA_LOC_MAN.get_col()-1);
   return OPEN_BRACE;
}

"}" {
   COL(1);
   string *tmp = new std::string (yytext);
   yylval.token_ptr = new Token (tmp,PA_LOC_MAN.get_line(),PA_LOC_MAN.get_col()-1);
   return CLOSE_BRACE;
}

"(" {
   COL(1);
   string *tmp = new std::string (yytext);
   yylval.token_ptr = new Token (tmp,PA_LOC_MAN.get_line(),PA_LOC_MAN.get_col()-1);
   return OPEN_PARANTESSIS;
}

")" {
   COL(1);
   string *tmp = new std::string (yytext);
   yylval.token_ptr = new Token (tmp,PA_LOC_MAN.get_line(),PA_LOC_MAN.get_col()-1);
   return CLOSE_PARANTESSIS;
}

"~" {
   COL(1);
   string *tmp = new std::string (yytext);
   yylval.token_ptr = new Token (tmp,PA_LOC_MAN.get_line(),PA_LOC_MAN.get_col()-1);
   return NEGATION;
}



"*"|"/"|"%" {COL(1); return yytext[0];}
"+"|"-" {COL(1); return yytext[0];}
"<"|">" {COL(1); return yytext[0];}

{identifier}    {COL(strlen(yytext));
                 yylval.token_ptr = new Token (new string (yytext),
                                               PA_LOC_MAN.get_line(),
                                               PA_LOC_MAN.get_col()-strlen(yytext));
                 PA_LOC_MAN.saw_identifier(yytext);
                 yylval.token_ptr->set_identifier_counter(PA_LOC_MAN.get_identifier_counter(yytext));
                 return IDENTIFIER;
                }
{unsigned}      {COL(strlen(yytext));
   //                 yylval.str = new std::string (yytext);
                 yylval.token_ptr = new Token (new string (yytext),
                                               PA_LOC_MAN.get_line(),
                                               PA_LOC_MAN.get_col()-strlen(yytext));
                 PA_LOC_MAN.saw_number(yytext);
                 return NUMBER;}
{string}        {COL(strlen(yytext));
                 yylval.str = new std::string (yytext);
                 return STRING;}


" "           {COL(1); }
.            {COL(1); cerr << "In LEX: GOT ==>" << yytext << "<==" << endl;}
\n           {PA_LOC_MAN.set_new_line();}

%%

int yywrap () {return 1;}

int yyerror (const char * s) {
   cerr << "At line " << PA_LOC_MAN.get_line() << ": Unexpected token ==>" << yytext << "<==" << endl;
   return 0;
}
