// MIT License
//
//     Copyright(c)[2024][Anton Yashchenko]
//
//     Permission is hereby granted,free of charge,
//     to any person obtaining a copy of this software and associated
//     documentation files(the "Software"), to deal in the Software without
//     restriction, including without limitation the rights to use, copy,
//     modify, merge, publish, distribute, sublicense, and / or sell copies
//     of the Software, and to permit persons to whom the Software is 
//     furnished to do so,subject to the following conditions :
//
//     The above copyright notice and this permission notice shall be included
//     in all copies or substantial portions of the Software.
//
//     THE SOFTWARE IS PROVIDED "AS IS",
//     WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//     INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
//     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//     OTHER DEALINGS IN THE SOFTWARE.
#include "basic_split_parse.hpp"
#include "complexsplitparse.hpp"
#include "full_expr_split_parse.hpp"
#include "scan_token_pack.hpp"
#include "token_statement_split_parser.hpp"

void test_basic_split_parse() {
  using namespace basic_split_parse;
  std::string source_code = "a+b*c^4-a+w";
  auto* ast = build_ast(source_code.cbegin(), source_code.cend());
  print_ast(ast, 0);
}

void test_complex_token_split_parse() {
  using namespace complex_split_parse;
  std::vector<Tok> t = {token_type_index(TokenType::unary_minus_),
                        token_type_index(TokenType::alnumus_),
                        token_type_index(TokenType::plus_),
                        token_type_index(TokenType::alnumus_),
                        token_type_index(TokenType::multiply_),
                        token_type_index(TokenType::unary_minus_),
                        token_type_index(TokenType::alnumus_),
                        token_type_index(TokenType::power_),
                        token_type_index(TokenType::dereference_),
                        token_type_index(TokenType::number_),
                        token_type_index(TokenType::plus_),
                        token_type_index(TokenType::unary_minus_),
                        token_type_index(TokenType::alnumus_)};

  std::vector<Tok> t2 = {
      token_type_index(TokenType::alnumus_),
      token_type_index(TokenType::plus_),
      token_type_index(TokenType::dereference_),
      token_type_index(TokenType::alnumus_),
      token_type_index(TokenType::power_),
      token_type_index(TokenType::alnumus_),
      token_type_index(TokenType::plus_),
      token_type_index(TokenType::alnumus_),
  };

  auto ast = build_statement(t.begin(), t.end());
  print_statement(ast.value());
}

void test_full_expr_split_parse() {
  using namespace full_expr_split_parse;
  std::vector<Token> t = {
      TokenType::unary_minus_, TokenType::alnumus_,  TokenType::plus_,
      TokenType::alnumus_,     TokenType::multiply_, TokenType::unary_minus_,
      TokenType::alnumus_,     TokenType::power_,    TokenType::dereference_,
      TokenType::number_,      TokenType::plus_,     TokenType::unary_minus_,
      TokenType::alnumus_};

  std::vector<Token> t2 = {TokenType::unary_minus_, TokenType::alnumus_,
                           TokenType::plus_, TokenType::number_};

  std::vector<Token> t3 = {TokenType::dereference_, TokenType::alnumus_,
                           TokenType::plus_, TokenType::number_};

  std::vector<Token> t4 = {TokenType::dereference_, TokenType::alnumus_,
                           TokenType::plus_, TokenType::unary_minus_,
                           TokenType::number_};

  std::vector<Token> t5 = {TokenType::dereference_, TokenType::alnumus_,
                           TokenType::plus_,        TokenType::unary_minus_,
                           TokenType::number_,      TokenType::plus_,
                           TokenType::alnumus_};

  std::vector<Token> t6 = {TokenType::dereference_, TokenType::alnumus_,
                           TokenType::plus_,        TokenType::unary_minus_,
                           TokenType::number_,      TokenType::plus_,
                           TokenType::unary_minus_, TokenType::alnumus_,
                           TokenType::multiply_,    TokenType::alnumus_};

  std::vector<Token> t7 = {TokenType::dereference_, TokenType::alnumus_,
                           TokenType::plus_,        TokenType::unary_minus_,
                           TokenType::number_,      TokenType::plus_,
                           TokenType::dereference_, TokenType::alnumus_,
                           TokenType::multiply_,    TokenType::alnumus_};

  std::vector<Token> t8 = {TokenType::open_parenthesis_,
                           TokenType::dereference_,
                           TokenType::alnumus_,
                           TokenType::close_parenthesis_,
                           TokenType::plus_,
                           TokenType::unary_minus_,
                           TokenType::number_,
                           TokenType::plus_,
                           TokenType::dereference_,
                           TokenType::alnumus_,
                           TokenType::multiply_,
                           TokenType::alnumus_};

  std::vector<Token> t9 = {
      TokenType::alnumus_,          TokenType::plus_,
      TokenType::number_,           TokenType::multiply_,
      TokenType::open_parenthesis_, TokenType::dereference_,
      TokenType::alnumus_,          TokenType::close_parenthesis_,
  };

  // Big Expr, with multiple scopes.
  std::vector<Token> t10 = {TokenType::open_parenthesis_,
                            TokenType::dereference_,
                            TokenType::alnumus_,
                            TokenType::close_parenthesis_,
                            TokenType::plus_,
                            TokenType::unary_minus_,
                            TokenType::number_,
                            TokenType::plus_,
                            TokenType::dereference_,
                            TokenType::alnumus_,
                            TokenType::multiply_,
                            TokenType::alnumus_,
                            TokenType::power_,
                            TokenType::open_parenthesis_,
                            TokenType::dereference_,
                            TokenType::alnumus_,
                            TokenType::close_parenthesis_,
                            TokenType::plus_,
                            TokenType::unary_minus_,
                            TokenType::number_,
                            TokenType::plus_,
                            TokenType::dereference_,
                            TokenType::alnumus_,
                            TokenType::multiply_,
                            TokenType::alnumus_};

  std::cout << "Test 1" << std::endl;
  auto ast = build_statement(t2.begin(), t2.end());
  print_statement(ast.value());

  std::cout << "Test 2" << std::endl;
  auto ast2 = build_statement(t3.begin(), t3.end());
  print_statement(ast2.value());

  std::cout << "Test 3" << std::endl;
  auto ast3 = build_statement(t4.begin(), t4.end());
  print_statement(ast3.value());

  std::cout << "Test 4" << std::endl;
  auto ast4 = build_statement(t5.begin(), t5.end());
  print_statement(ast4.value());

  std::cout << "Test 5: Inner Unary High Importance Operator" << std::endl;
  auto ast5 = build_statement(t6.begin(), t6.end());
  print_statement(ast5.value());

  std::cout << "Test 6: Inner Unary Low Importance Operator" << std::endl;
  auto ast6 = build_statement(t7.begin(), t7.end());
  print_statement(ast6.value());

  std::cout << "Test 7: Basic Scope at Start of Expr." << std::endl;
  auto ast7 = build_statement(t8.begin(), t8.end());
  print_statement(ast7.value());

  std::cout << "Test 8: Basic Scope at End of Expr." << std::endl;
  auto ast8 = build_statement(t9.begin(), t9.end());
  print_statement(ast8.value());

  std::cout << "Test 9: Big Expr with multiple scopes." << std::endl;
  auto ast9 = build_statement(t10.begin(), t10.end());
  print_statement(ast9.value());
}

void test_token_split_parse() {
  using namespace token_statement_split_parse;
  std::vector<Token> t = {
      Token::unary_minus_, Token::alnumus_,     Token::plus_,
      Token::alnumus_,     Token::multiply_,    Token::unary_minus_,
      Token::alnumus_,     Token::power_,       Token::number_,
      Token::plus_,        Token::unary_minus_, Token::alnumus_,
  };

  auto ast = build_statement(t.begin(), t.end());
  print_statement(ast);
}

void test_scan_token_pack() {
  using namespace stp;
  bool bb = false;
  std::vector<Tk> tokens = {Tk(TkT::eof), Tk(TkT::eof), Tk(TkT::eof)};

  using constrained_int_type_mask =
      std::tuple<tk_mask<TkT::aint_>, tk_mask<TkT::open_frame>,
                 tk_mask<TkT::number_literal>, tk_mask<TkT::ellipsis>,
                 tk_mask<TkT::number_literal>, tk_mask<TkT::close_frame>>;

  std::vector int_decl_tokens1 = {
      Tk(TkT::aint_),          Tk(TkT::open_frame), Tk(TkT::subtraction),
      Tk(TkT::number_literal), Tk(TkT::ellipsis),   Tk(TkT::subtraction),
      Tk(TkT::number_literal), Tk(TkT::close_frame)};

  std::vector int_decl_tokens2 = {Tk(TkT::aint_),          Tk(TkT::open_frame),
                                  Tk(TkT::number_literal), Tk(TkT::ellipsis),
                                  Tk(TkT::number_literal), Tk(TkT::close_frame),
                                  Tk(TkT::close_frame)};

  using test_mask =
      std::tuple<tk_mask<TkT::eof>, tk_mask<TkT::eof, mask_policy::optional>,
                 tk_mask<TkT::eof>>;
  bb = scan_tokens<tk_mask<TkT::eof>, tk_mask<TkT::eof, mask_policy::optional>,
                   tk_mask<TkT::eof>>(tokens.cbegin(), tokens.cend());
  bb = scan_tokens_pack<test_mask>(tokens.cbegin(), tokens.cend());

  // bb = scan_tokens_pack<constrained_int_type_mask>(int_decl_tokens1.cbegin(),
  // int_decl_tokens1.cend());
  bb = scan_tokens_pack<constrained_int_type_mask>(int_decl_tokens2.cbegin(),
                                                   int_decl_tokens2.cend());
}

int main() {
  test_basic_split_parse();
  test_complex_token_split_parse();
  test_full_expr_split_parse();
  test_token_split_parse();
  test_scan_token_pack();
  return 0;
}
