#include "parser.h"
#include <iostream>
#include <string>
#include <memory>

namespace kaleidoscope {
  std::map<char, int> Parser::binary_op_precedence = {
      {'<', 10},
      {'+', 20},
      {'-', 20},
      {'*', 40}
  };

  int Parser::get_op_precedence(const char op) const {
      int prec = -1;
      auto found = binary_op_precedence.find(op);
      if (found != binary_op_precedence.cend())
        prec = found->second;
      return prec;
  }

  std::unique_ptr<ExprAST> Parser::log_error(const char* str) {
    std::cerr << "Error: " << str << "\n";
    return nullptr;
  }

  std::unique_ptr<PrototypeAST> Parser::log_error_p(const char* str) {
    log_error(str);
    return nullptr;
  }

  std::unique_ptr<ExprAST> Parser::parse_number_expr() {
    auto number = std::make_unique<NumberExprAST>(_lexer.token_value().num_val);
    get_next_token();
    return std::move(number);
  }

  std::unique_ptr<ExprAST> Parser::parse_identifier_expr() {
    auto id_name = _lexer.token_value().identifier_str;
    get_next_token();

    if (_cur_token != '(')
      return std::make_unique<VariableExprAST>(id_name);

    get_next_token();
    std::vector<std::unique_ptr<ExprAST>> args;
    if (_cur_token != ')') {
      while (true) {
        if (auto arg = parse_expr()) {
          args.push_back(std::move(arg));
        }
        else {
          return nullptr;
        }

        if (_cur_token == ')')
          break;

        if (_cur_token != ',')
          return log_error("Expected \")\" or \",\" in argument list to function call");

        get_next_token();
      }
    }

    get_next_token();
    return std::make_unique<CallExprAST>(id_name, std::move(args));
  }

  std::unique_ptr<ExprAST> Parser::parse_paren_expr() {
    get_next_token();
    auto expr = parse_expr();
    if (!expr)
      return nullptr;

    if (_cur_token != ')')
      return log_error("Expected \")\"");
    get_next_token();
    return std::move(expr);
  }

  std::unique_ptr<ExprAST> Parser::parse_expr() {
    auto lhs = parse_primary();
    if (!lhs)
      return nullptr;
    return parse_bin_op_rhs(0, std::move(lhs));
  }

  std::unique_ptr<ExprAST> Parser::parse_primary() {
    switch (_cur_token) {
      case Lexer::tok_identifier:
        return parse_identifier_expr();
      case Lexer::tok_number:
        return parse_number_expr();
      case '(':
        return parse_paren_expr();
      default:
        return log_error("Unknown token when expecting an expression");
    }
  }

  std::unique_ptr<ExprAST> Parser::parse_bin_op_rhs(int precedence, std::unique_ptr<ExprAST> lhs) {
    while (true) {
      auto curr_prec = get_op_precedence(_cur_token);
      if (curr_prec <= precedence) // precedence of previous op higher
        return std::move(lhs);

      int op = _cur_token; // preserve the op
      get_next_token();
      auto rhs = parse_primary();
      if (!rhs)
        return nullptr;

      auto next_prec = get_op_precedence(_cur_token);
      if (curr_prec <= next_prec) { // curr op less binding
        rhs = parse_bin_op_rhs(curr_prec, std::move(rhs));
        if (!rhs)
          return nullptr;
      }

      // reduce!
      lhs = std::make_unique<BinaryExprAST>(op, std::move(lhs), std::move(rhs));
    }
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
    get_next_token();

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
            std::cout << "Parsed a top level expression.\n";
          }
          else {
            get_next_token();
          }
          break;
      }
    }
  }

}
