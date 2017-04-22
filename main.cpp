#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

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
  
  Parser parser;
  Lexer lexer([&parser](char token) { parser(token); });
  lexer(f);

  f.close();

  return 0;
}
