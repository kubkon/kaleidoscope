#pragma once

#include "ast.h"
#include "lexer.h"
#include <memory>
#include <map>

namespace kaleidoscope {
  class Parser {
  public:
    Parser(Lexer& lexer) : _lexer(lexer), _cur_token(0) {}

    void parse();
  private:
    Lexer& _lexer;
    char _cur_token;

    static std::map<char, int> binary_op_precedence;
    int get_op_precedence(const char op) const;

    int get_next_token() { return _cur_token = _lexer.gettok(); }

    std::unique_ptr<ExprAST> log_error(const char* str);
    std::unique_ptr<PrototypeAST> log_error_p(const char* str);

    std::unique_ptr<ExprAST> parse_number_expr();
    std::unique_ptr<ExprAST> parse_identifier_expr();
    std::unique_ptr<ExprAST> parse_paren_expr();
    std::unique_ptr<ExprAST> parse_expr();
    std::unique_ptr<ExprAST> parse_primary();
    std::unique_ptr<ExprAST> parse_bin_op_rhs(int precedence, std::unique_ptr<ExprAST> lhs);

    std::unique_ptr<PrototypeAST> parse_proto();
    std::unique_ptr<FunctionAST> parse_def();
    std::unique_ptr<PrototypeAST> parse_extern();
    std::unique_ptr<FunctionAST> parse_top_level_expr();
  };
}

