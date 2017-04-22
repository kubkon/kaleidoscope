#include "parser.h"
#include <iostream>
#include <string>

namespace kaleidoscope {

  void Parser::operator()(char token, Lexer::TokenValue tok_value) {
    std::cout << "Received token: " << std::to_string(token);
    if (token == Lexer::Token::tok_number)
      std::cout << ", " << std::to_string(tok_value.num_val);
    if (token == Lexer::Token::tok_identifier)
      std::cout << ", " << tok_value.identifier_str;
    std::cout << "\n";
  }

}
