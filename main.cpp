#include <iostream>
#include <fstream>
#include "lexer.h"

using namespace kaleidoscope;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Too few arguments; you need to specify the input filename.\n";
    return -1;
  }

  std::fstream f(argv[1]);
  if (f.fail()) {
    std::cout << "Error reading file: " << argv[1] << "\n";
    return -1;
  }
  std::cout << "Reading file: " << argv[1] << "...\n";

  Lexer lexer;
  char token;
  while ((token = lexer.gettok(f)) != Lexer::Token::tok_eof) {
    std::cout << "Next token: " << std::to_string(token);
    if (token == Lexer::Token::tok_number)
      std::cout << ", " << std::to_string(lexer.num_val());
    if (token == Lexer::Token::tok_identifier)
      std::cout << ", " << lexer.identifier_str();
    std::cout << "\n";
  }

  f.close();

  return 0;
}
