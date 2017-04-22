#include "parser.h"
#include <iostream>
#include <string>

namespace kaleidoscope {

  void Parser::operator()(char token) {
    std::cout << "Received token: " << std::to_string(token) << "\n";
  }

}
