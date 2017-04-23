#include "lexer.h"
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <string>
#include <istream>

namespace kaleidoscope {

  int Lexer::gettok() {
    _last_char = _stream.get();

    // we skip whitespaces
    while (isspace(_last_char))
      _last_char = _stream.get();

    if (isalpha(_last_char)) { // only alphanumerics, regex: [a-zA-z][a-zA-Z0-9]*
      _token_value.identifier_str = _last_char;
      while (isalnum((_last_char = _stream.get())))
        _token_value.identifier_str += _last_char;
      _stream.unget();

      if (_token_value.identifier_str == "def")
        return tok_def;
      if (_token_value.identifier_str == "extern")
        return tok_extern;
      return tok_identifier;
    }

    if (isdigit(_last_char) || _last_char == '.') { // floating-point nums, regex: [0-9.]+; actually, should be [0-9]([0-9]+|\.[0-9]+)
      std::string num_str;
      do {
        num_str += _last_char;
        _last_char = _stream.get();
      } while (isdigit(_last_char) || _last_char == '.');
      _stream.unget();

      _token_value.num_val = strtod(num_str.c_str(), 0);
      return tok_number;
    }

    if (_last_char == '#') { // comments start with #
      do {
        _last_char = _stream.get();
      } while (_last_char != EOF && _last_char != '\n' && _last_char != '\r');

      if (_last_char != EOF)
        return gettok();
    }

    if (_last_char == EOF)
      return tok_eof;

    int this_char = _last_char;
    /* _last_char = _stream.get(); */
    return this_char;
  }

}
