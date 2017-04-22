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

    Lexer(std::function<void(char)> parse_cb) : _parse_cb(parse_cb), _identifier_str(""), _num_val(0.0), _last_char(0) {}

    std::string identifier_str() const {
      return _identifier_str;
    }
    double num_val() const {
      return _num_val;
    }

    void operator()(std::iostream& ss);

  private:
    std::function<void(char)> _parse_cb;
    std::string _identifier_str;
    double _num_val;
    int _last_char;

    int gettok(std::iostream& ss);
  };

}
