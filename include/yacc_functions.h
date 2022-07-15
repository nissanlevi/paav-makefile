#ifndef YACC_FUNCTIONS_H
#define YACC_FUNCTIONS_H

#include <string>
#include <list>
#include <map>

#include <limits.h>


class Token {
public:
   Token(std::string *txt, int start_line, int start_col)
      : _txt(*txt),
        _start_line(start_line), _start_col(start_col),
        _end_line(start_line), _end_col(INT_MIN),
        _identifier_counter(INT_MIN)
   {
      _end_col  = _start_col + txt->size() - 1;
   }

   std::string *get_txt() {return &_txt;}
   int get_start_line() {return _start_line;}
   int get_start_col() {return _start_col;}
   int get_end_line() {return _end_line;}
   int get_end_col() {return _end_col;}
   void set_identifier_counter(int identifier_counter) {_identifier_counter = identifier_counter;}
   int get_identifier_counter() {return _identifier_counter;}
private:
   std::string &_txt;
   int _start_line;
   int _start_col;
   int _end_line;
   int _end_col;
   int _identifier_counter;
};


class Location {
public:
   Location() {}

   void print() const;
   
   std::string _file;
   int _line;
   int _col;
   
   int _counter_in_line;
};


class Location_Manager {
public:
   Location_Manager() : _curr_line(1),_curr_col(0) {}

   void set_current_file (const std::string &file) {_file=file;}
   void set_new_line();
   void update_col(int add) {_curr_col+=add;}
   
   int get_line() {return _curr_line;}
   int get_col() {return _curr_col;}
   
   void saw_identifier(const char *iden);
   void saw_number(const char *num);
   int get_identifier_counter(const char *iden);
   Location get_start_loc_of_a_token(Token *token);
   Location get_end_loc_of_a_token(Token *token);


private:
   std::string _file;
   int _curr_line;
   int _curr_col;

   std::map<std::string, int> _iden_counter;
   std::map<std::string, int> _num_counter;
};





#endif

