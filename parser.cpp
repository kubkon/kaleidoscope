#include "parser.h"
#include <iostream>
#include <string>

namespace kaleidoscope {

  void Parser::parse() {
    while (true) {
      switch(_cur_token) {
        case Lexer::tok_eof:
          return;
        case ';':
          get_next_token();
          break;
        default:
          std::cout << "Default hit!\n";
          get_next_token();
          break;
      }
    }
  }

}
