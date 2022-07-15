#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "yacc_functions.h"

using namespace std;


void Location::print() const {
   cerr << "<"
        << _line << "," 
        << _col << "," 
        << _counter_in_line 
        << ">"
        ;
}

void Location_Manager::set_new_line() {
   _curr_col = 0;
   ++_curr_line;

   map<string, int>::iterator itr;
   for (itr=_iden_counter.begin(); itr!=_iden_counter.end(); ++itr)
      (*itr).second = 0;
  
}


void Location_Manager::saw_identifier(const char *iden) {
   if (_iden_counter.find(iden) != _iden_counter.end())
      ++_iden_counter[iden];
   else {
      _iden_counter[iden] = 1;
   }
}


void Location_Manager::saw_number(const char *num) {
   
}

int Location_Manager::get_identifier_counter(const char *iden) {
   assert (_iden_counter.find(iden) != _iden_counter.end());
   return _iden_counter[iden];
}

Location Location_Manager::get_start_loc_of_a_token(Token *token) {
   Location loc;

   loc._file = _file;
   loc._line = token->get_start_line();
   loc._col =  token->get_start_col();
   
   //loc._counter_in_line = _iden_counter[*token->get_txt()];
   loc._counter_in_line = token->get_identifier_counter();
   
   return loc;
}


Location Location_Manager::get_end_loc_of_a_token(Token *token) {
   Location loc;

   loc._file = _file;
   loc._line = token->get_end_line();
   loc._col =  token->get_end_col();

   //   loc._counter_in_line = _iden_counter[*token->get_txt()];
   loc._counter_in_line = token->get_identifier_counter();

   return loc;
}



