#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "lexer.h"

namespace kaleidoscope {
  TEST(FunctionPrototype, SingleArgument) {
    std::vector<std::string> inputs = {
      "def fib(x)\n",
      "def fib (x)\n",
      "def fib ( x)\n",
      "def fib (x )\n",
      "def fib ( x ) \n"
    };
    for (const auto& input : inputs) {
      std::stringstream ss;
      ss << input;
      Lexer lexer(ss);
      ASSERT_EQ(Lexer::tok_def, lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "fib");
      ASSERT_EQ('(', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "x");
      ASSERT_EQ(')', lexer.gettok());
      ASSERT_EQ(Lexer::tok_eof, lexer.gettok());
    }
  }

  TEST(FunctionPrototype, MultipleArguments) {
    std::vector<std::string> inputs = {
      "def fib(x,y)\n",
      "def fib (x,y)\n",
      "def fib ( x, y)\n",
      "def fib (x, y )\n",
      "def fib ( x , y ) \n"
    };
    for (const auto& input : inputs) {
      std::stringstream ss;
      ss << input;
      Lexer lexer(ss);
      ASSERT_EQ(Lexer::tok_def, lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "fib");
      ASSERT_EQ('(', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "x");
      ASSERT_EQ(',', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "y");
      ASSERT_EQ(')', lexer.gettok());
      ASSERT_EQ(Lexer::tok_eof, lexer.gettok());
    }
  }
}
