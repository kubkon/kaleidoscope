#pragma once

#include <string>
#include <istream>

namespace kaleidoscope {

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

    struct TokenValue {
      std::string identifier_str;
      double num_val;

      TokenValue() : identifier_str(""), num_val(0.0) {}
    };

    Lexer(std::iostream& stream) : _stream(stream), _token_value(), _last_char(0) {}

    int gettok();

  private:
    std::iostream& _stream;
    TokenValue _token_value;
    int _last_char;
  };

}
