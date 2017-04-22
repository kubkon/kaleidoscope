#include "parser.h"
#include <iostream>
#include <string>
#include <memory>

namespace kaleidoscope {
  std::unique_ptr<ExprAST> Parser::log_error(const char* str) {
    std::cerr << "Error: " << str << "\n";
    return nullptr;
  }

  std::unique_ptr<PrototypeAST> Parser::log_error_p(const char* str) {
    log_error(str);
    return nullptr;
  }

  std::unique_ptr<PrototypeAST> Parser::parse_proto() {
    // parse function name
    if (_cur_token != Lexer::tok_identifier)
      return log_error_p("Expected function name in prototype");
    auto fn_name = _lexer.token_value().identifier_str;

    //parse arg list
    get_next_token();
    if (_cur_token != '(')
        return log_error_p("Expected \"(\" after function name in prototype");

    std::vector<std::string> args;
    do {
      get_next_token();

      if (_cur_token != Lexer::tok_identifier)
        return log_error_p("Expected argument name in argument list in prototype");
      args.push_back(_lexer.token_value().identifier_str);

      get_next_token();

      if (_cur_token != ',' || _cur_token != ')')
        return log_error_p("Expected \",\" or \")\" in argument list in prototype");

    } while (_cur_token != ')');

    return std::make_unique<PrototypeAST>(fn_name, args);
  }

  std::unique_ptr<FunctionAST> Parser::parse_def() {
    get_next_token();
    auto proto = parse_proto();
    return nullptr;
  }

  void Parser::parse() {
    while (true) {
      switch(_cur_token) {
        case Lexer::tok_eof:
          return;
        case ';':
          get_next_token();
          break;
        case Lexer::tok_def:
          if (parse_def()) {
            std::cout << "Parsed function definition.\n";
          }
          else {
            get_next_token();
          }
          break;
        default:
          std::cout << "Default hit!\n";
          get_next_token();
          break;
      }
    }
  }

}
