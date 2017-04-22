#include "lexer.h"
#include <cstdio>
#include <cctype>
#include <string>
#include <istream>

namespace kaleidoscope {

  void Lexer::operator()(std::iostream& ss) {
    char token;
    while ((token = gettok(ss)) != Token::tok_eof)
      _parse_cb(token, _token_value);
  }

  int Lexer::gettok(std::iostream& ss) {
    _last_char = ss.get();

    // we skip whitespaces
    while (isspace(_last_char))
      _last_char = ss.get();

    if (isalpha(_last_char)) { // only alphanumerics, regex: [a-zA-z][a-zA-Z0-9]*
      _token_value.identifier_str = _last_char;
      while (isalnum((_last_char = ss.get())))
        _token_value.identifier_str += _last_char;

      if (_token_value.identifier_str == "def")
        return Token::tok_def;
      if (_token_value.identifier_str == "extern")
        return Token::tok_extern;
      return Token::tok_identifier;
    }

    if (isdigit(_last_char) || _last_char == '.') { // floating-point nums, regex: [0-9.]+; actually, should be [0-9]([0-9]+|\.[0-9]+)
      std::string num_str;
      do {
        num_str += _last_char;
        _last_char = ss.get();
      } while (isdigit(_last_char) || _last_char == '.');

      _token_value.num_val = strtod(num_str.c_str(), 0);
      return Token::tok_number;
    }

    if (_last_char == '#') { // comments start with #
      do {
        _last_char = ss.get();
      } while (_last_char != EOF && _last_char != '\n' && _last_char != '\r');

      if (_last_char != EOF)
        return gettok(ss);
    }

    if (_last_char == EOF)
      return Token::tok_eof;

    int this_char = _last_char;
    _last_char = ss.get();
    return this_char;
  }

}
