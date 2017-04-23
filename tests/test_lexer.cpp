#include <gtest/gtest.h>
#include <sstream>
#include "lexer.h"

namespace kaleidoscope {
  TEST(Lexer, FunctionPrototype) {
    {
      std::stringstream ss;
      ss << "def(x)\n";
      Lexer lexer(ss);
      ASSERT_EQ(Lexer::tok_def, lexer.gettok());
      ASSERT_EQ('(', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "x");
      ASSERT_EQ(')', lexer.gettok());
      ASSERT_EQ(Lexer::tok_eof, lexer.gettok());
    }
    {
      std::stringstream ss;
      ss << "def (x)\n";
      Lexer lexer(ss);
      ASSERT_EQ(Lexer::tok_def, lexer.gettok());
      ASSERT_EQ('(', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "x");
      ASSERT_EQ(')', lexer.gettok());
      ASSERT_EQ(Lexer::tok_eof, lexer.gettok());
    }
    {
      std::stringstream ss;
      ss << "def ( x ) \n";
      Lexer lexer(ss);
      ASSERT_EQ(Lexer::tok_def, lexer.gettok());
      ASSERT_EQ('(', lexer.gettok());
      ASSERT_EQ(Lexer::tok_identifier, lexer.gettok());
      ASSERT_EQ(lexer.token_value().identifier_str, "x");
      ASSERT_EQ(')', lexer.gettok());
      ASSERT_EQ(Lexer::tok_eof, lexer.gettok());
    }
  }
}
