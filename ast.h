#pragma once

#include <memory>
#include <string>

namespace kaleidoscope {

  class ExprAST {
  public:
    virtual ~ExprAST() = default;
  };

  class NumberExprAST : public ExprAST {
    double _val;
  public:
    NumberExprAST(double val) : val(_val) {}
  };

  class VariableExprAST : public ExprAST {
    std::string _name;
  public:
    VariableExprAST(const std::string& name) : _name(name) {}
  };

  class BinaryExprAST : public ExprAST {
    char _op;
    std::unique_ptr<ExprAST> _lhs, _rhs;
  public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                  std::unique_ptr<ExprAST> rhs)
      : _op(op), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}
  };

  class CallExprAST : public ExprAST {
    std::string _callee;
    std::vector<std::unique_ptr<ExprAST>> _args;
  public:
    CallExprAST(const std::string& callee, std::vector<std::unique_ptr<ExprAST>> args) : _callee(callee), _args(std::move(args)) {}
  };

  class PrototypeAST {
    std::string _name;
    std::vector<std::string> _args;
  public:
    PrototypeAST(const std::string& name, std::vector<std::string> args) : _name(name), _args(std::move(args)) {}

    const string& name() const { return _name; }
  };

  class FunctionAST {
    std::unique_ptr<PrototypeAST> _proto;
    std::unique_ptr<ExprAST> _body;
  public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body) : _proto(std::move(proto)), _body(std::move(body)) {}
  };

}
