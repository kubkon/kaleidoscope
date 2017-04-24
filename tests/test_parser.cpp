#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "lexer.h"
#include "parser.h"

namespace kaleidoscope {
  TEST(BinaryExpressions, NoParens) {
    std::stringstream ss;
    ss << "1 + 2 * 3";
    Lexer lexer(ss);
    Parser parser(lexer);

    auto result = parser.parse_top_level_expr();
    auto top_expr = dynamic_cast<const FunctionAST*>(result.get());
    ASSERT_NE(top_expr, nullptr);

    auto top_bin_expr = dynamic_cast<const BinaryExprAST*>(top_expr->body());
    ASSERT_NE(top_bin_expr, nullptr);
    ASSERT_EQ(top_bin_expr->op(), '+');
  
    auto lhs = dynamic_cast<const NumberExprAST*>(top_bin_expr->lhs());
    ASSERT_NE(lhs, nullptr);
    ASSERT_EQ(lhs->val(), static_cast<double>(1));

    auto rhs = dynamic_cast<const BinaryExprAST*>(top_bin_expr->rhs());
    ASSERT_NE(rhs, nullptr);
    ASSERT_EQ(rhs->op(), '*');
    
    auto inner_lhs = dynamic_cast<const NumberExprAST*>(rhs->lhs());
    ASSERT_NE(inner_lhs, nullptr);
    ASSERT_EQ(inner_lhs->val(), static_cast<double>(2));

    auto inner_rhs = dynamic_cast<const NumberExprAST*>(rhs->rhs());
    ASSERT_NE(inner_rhs, nullptr);
    ASSERT_EQ(inner_rhs->val(), static_cast<double>(3));
  }
}
