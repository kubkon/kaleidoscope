#pragma once

#include <string>
#include <istream>

class Lexer {
public:
  enum Token {
    tok_eof = -1,

    // commands (keywords)
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
  };

  Lexer() : _identifier_str(""), _num_val(0.0), _last_char(0) {}

  std::string identifier_str() const {
    return _identifier_str;
  }
  double num_val() const {
    return _num_val;
  }

  int gettok(std::iostream& ss);

private:
  std::string _identifier_str;
  double _num_val;
  int _last_char;
};

