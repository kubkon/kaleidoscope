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

  std::unique_ptr<ExprAST> Parser::parse_expr() {
    return log_error("Sorry, don't know how to parse expressions yet!");
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

      if (_cur_token != ',' && _cur_token != ')')
        return log_error_p("Expected \",\" or \")\" in argument list in prototype");

    } while (_cur_token != ')');

    return std::make_unique<PrototypeAST>(fn_name, args);
  }

  std::unique_ptr<FunctionAST> Parser::parse_def() {
    get_next_token();
    auto proto = parse_proto();
    if (!proto)
      return nullptr;

    auto body = parse_expr();
    if (!body)
      return nullptr;
    return std::make_unique<FunctionAST>(std::move(proto), std::move(body));
  }

  std::unique_ptr<PrototypeAST> Parser::parse_extern() {
    get_next_token();
    return parse_proto();
  }

  std::unique_ptr<FunctionAST> Parser::parse_top_level_expr() {
    auto body = parse_expr();
    if (!body)
      return nullptr;
    auto proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>{ });
    return std::make_unique<FunctionAST>(std::move(proto), std::move(body));
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
        case Lexer::tok_extern:
          if (parse_extern()) {
            std::cout << "Parsed an extern.\n";
          }
          else {
            get_next_token();
          }
          break;
        default:
          if (parse_top_level_expr()) {
            std::cout << "Parse a top level expression.\n";
          }
          else {
            get_next_token();
          }
          break;
      }
    }
  }

}
