#pragma once

#include "lexer.h"

namespace kaleidoscope {
  class Parser {
  public:
    Parser() {}

    void operator()(char token, Lexer::TokenValue tok_value);
  };
}

