#pragma once

#include <memory>
#include <string>
#include <vector>

namespace kaleidoscope {

  class ExprAST {
  public:
    virtual ~ExprAST() = default;
  };

  class NumberExprAST : public ExprAST {
    double _val;
  public:
    NumberExprAST(double val) : _val(val) {}

    double val() const { return _val; }
  };

  class VariableExprAST : public ExprAST {
    std::string _name;
  public:
    VariableExprAST(const std::string& name) : _name(name) {}

    const std::string& name() const { return _name; }
  };

  class BinaryExprAST : public ExprAST {
    char _op;
    std::unique_ptr<ExprAST> _lhs, _rhs;
  public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                  std::unique_ptr<ExprAST> rhs)
      : _op(op), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

    char op() const { return _op; }
    const ExprAST* lhs() const { return _lhs.get(); }
    const ExprAST* rhs() const { return _rhs.get(); }
  };

  class CallExprAST : public ExprAST {
    std::string _callee;
    std::vector<std::unique_ptr<ExprAST>> _args;
  public:
    CallExprAST(const std::string& callee, std::vector<std::unique_ptr<ExprAST>> args) : _callee(callee), _args(std::move(args)) {}

    const std::string& callee() const { return _callee; }
    std::vector<const ExprAST*> args() const {
      std::vector<const ExprAST*> ags;
      for (const auto& a : _args)
        ags.push_back(a.get());
      return ags;
    }
  };

  class PrototypeAST {
    std::string _name;
    std::vector<std::string> _args;
  public:
    PrototypeAST(const std::string& name, std::vector<std::string> args) : _name(name), _args(std::move(args)) {}

    const std::string& name() const { return _name; }
    const std::vector<std::string>& args() const { return _args; }
  };

  class FunctionAST {
    std::unique_ptr<PrototypeAST> _proto;
    std::unique_ptr<ExprAST> _body;
  public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body) : _proto(std::move(proto)), _body(std::move(body)) {}

    const PrototypeAST* proto() const { return _proto.get(); }
    const ExprAST* body() const { return _body.get(); }
  };

}
