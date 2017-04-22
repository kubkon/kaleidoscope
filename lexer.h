#pragma once

#include <string>
#include <istream>
#include <functional>
#include <memory>

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

    Lexer(std::function<void(char, TokenValue)> parse_cb) : _parse_cb(parse_cb), _token_value(), _last_char(0) {}

    void operator()(std::iostream& ss);

  private:
    std::function<void(char, TokenValue)> _parse_cb;
    TokenValue _token_value;
    int _last_char;

    int gettok(std::iostream& ss);
  };

}
