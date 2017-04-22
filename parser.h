#pragma once

#include "lexer.h"

namespace kaleidoscope {
  class Parser {
  public:
    Parser(Lexer& lexer) : _lexer(lexer), _cur_token(0) {}

    void parse();
  private:
    Lexer& _lexer;
    char _cur_token;

    int get_next_token() { return _cur_token = _lexer.gettok(); }
  };
}

