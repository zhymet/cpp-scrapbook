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
#pragma once
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Complex Split Parse Algorithm
// More complex split parse using a vector of tokens
// This is the same as the above, but using a vector of tokens instead of a
// string. The working 'last_pass' is actually a statement, not a node.
namespace complex_split_parse {
enum class TokenType : int {
  alnumus_,
  number_,
  plus_,
  minus_,
  multiply_,
  divide_,
  dereference_,
  power_,
  unary_minus_,
  eof_ = INT_MAX
};
enum class StatementType : int {
  literal_alnumus_ = 0,
  literal_number_,
  dereference_,
  addition_,
  subtraction_,
  multiplication_,
  division_,
  inversion_,
  exponentation_,
  eof_
};
enum Associativity { left_ = true, right_ = false };
enum Operation { binary_ = 0, unary_ = 1, none_ = 2 };

auto token_type_index(TokenType tok) {
  switch (tok) {
    case TokenType::alnumus_:
      return 0;
    case TokenType::number_:
      return 1;
    case TokenType::plus_:
      return 2;
    case TokenType::minus_:
      return 3;
    case TokenType::multiply_:
      return 4;
    case TokenType::divide_:
      return 5;
    case TokenType::dereference_:
      return 10;
    case TokenType::power_:
      return 6;
    case TokenType::unary_minus_:
      return 7;
    case TokenType::eof_:
      return 8;
    default:
      return 9;
  }
}
auto token_importance =
    std::map<std::size_t, int>{{token_type_index(TokenType::plus_), 1},
                               {token_type_index(TokenType::minus_), 1},
                               {token_type_index(TokenType::multiply_), 2},
                               {token_type_index(TokenType::divide_), 2},
                               {token_type_index(TokenType::dereference_), 0},
                               {token_type_index(TokenType::power_), 3},
                               {token_type_index(TokenType::unary_minus_), 4},
                               {token_type_index(TokenType::alnumus_), INT_MAX},
                               {token_type_index(TokenType::number_), INT_MAX},
                               {token_type_index(TokenType::eof_), INT_MAX}};
auto token_operation = std::map<std::size_t, Operation>{
    {token_type_index(TokenType::plus_), Operation::binary_},
    {token_type_index(TokenType::minus_), Operation::binary_},
    {token_type_index(TokenType::multiply_), Operation::binary_},
    {token_type_index(TokenType::divide_), Operation::binary_},
    {token_type_index(TokenType::dereference_), Operation::unary_},
    {token_type_index(TokenType::power_), Operation::binary_},
    {token_type_index(TokenType::unary_minus_), Operation::unary_},
    {token_type_index(TokenType::alnumus_), Operation::none_},
    {token_type_index(TokenType::number_), Operation::none_},
    {token_type_index(TokenType::eof_), Operation::none_}};
auto token_associativity = std::map<std::size_t, bool>{
    {token_type_index(TokenType::plus_), true},
    {token_type_index(TokenType::minus_), true},
    {token_type_index(TokenType::multiply_), true},
    {token_type_index(TokenType::divide_), true},
    {token_type_index(TokenType::power_), false},
    {token_type_index(TokenType::dereference_), false},
    {token_type_index(TokenType::unary_minus_), false},
    {token_type_index(TokenType::alnumus_), true},
    {token_type_index(TokenType::number_), true},
    {token_type_index(TokenType::eof_), true}};
auto token_to_statement_type = std::map<std::size_t, StatementType>{
    {token_type_index(TokenType::alnumus_), StatementType::literal_alnumus_},
    {token_type_index(TokenType::number_), StatementType::literal_number_},
    {token_type_index(TokenType::dereference_), StatementType::dereference_},
    {token_type_index(TokenType::plus_), StatementType::addition_},
    {token_type_index(TokenType::minus_), StatementType::subtraction_},
    {token_type_index(TokenType::multiply_), StatementType::multiplication_},
    {token_type_index(TokenType::divide_), StatementType::division_},
    {token_type_index(TokenType::power_), StatementType::exponentation_},
    {token_type_index(TokenType::unary_minus_), StatementType::inversion_},
    {token_type_index(TokenType::eof_), StatementType::eof_}};

auto statement_type_index(StatementType tok) {
  switch (tok) {
    case StatementType::literal_alnumus_:
      return 0;
    case StatementType::literal_number_:
      return 1;
    case StatementType::addition_:
      return 2;
    case StatementType::subtraction_:
      return 3;
    case StatementType::multiplication_:
      return 4;
    case StatementType::division_:
      return 5;
    case StatementType::inversion_:
      return 6;
    case StatementType::exponentation_:
      return 7;
    case StatementType::dereference_:
      return 9;
    default:
      return 8;
  }
}
auto statement_index_type(std::size_t tok) {
  switch (tok) {
    case 0:
      return StatementType::literal_alnumus_;
    case 1:
      return StatementType::literal_number_;
    case 2:
      return StatementType::addition_;
    case 3:
      return StatementType::subtraction_;
    case 4:
      return StatementType::multiplication_;
    case 5:
      return StatementType::division_;
    case 6:
      return StatementType::inversion_;
    case 7:
      return StatementType::exponentation_;
    case 9:
      return StatementType::dereference_;
    default:
      return StatementType::eof_;
  }
}
auto statement_importance = std::map<std::size_t, int>{
    {statement_type_index(StatementType::dereference_), 0},
    {statement_type_index(StatementType::addition_), 1},
    {statement_type_index(StatementType::subtraction_), 1},
    {statement_type_index(StatementType::multiplication_), 2},
    {statement_type_index(StatementType::division_), 2},
    {statement_type_index(StatementType::exponentation_), 3},
    {statement_type_index(StatementType::inversion_), 4},
    {statement_type_index(StatementType::literal_alnumus_), INT_MAX},
    {statement_type_index(StatementType::literal_number_), INT_MAX},
    {statement_type_index(StatementType::eof_), INT_MAX}

};
auto statement_operation = std::map<std::size_t, Operation>{
    {statement_type_index(StatementType::dereference_), Operation::unary_},
    {statement_type_index(StatementType::addition_), Operation::binary_},
    {statement_type_index(StatementType::subtraction_), Operation::binary_},
    {statement_type_index(StatementType::multiplication_), Operation::binary_},
    {statement_type_index(StatementType::division_), Operation::binary_},
    {statement_type_index(StatementType::exponentation_), Operation::binary_},
    {statement_type_index(StatementType::inversion_), Operation::unary_},
    {statement_type_index(StatementType::literal_alnumus_), Operation::none_},
    {statement_type_index(StatementType::literal_number_), Operation::none_},
    {statement_type_index(StatementType::eof_), Operation::none_}};
auto statement_associativity = std::map<std::size_t, bool>{
    {statement_type_index(StatementType::dereference_), false},
    {statement_type_index(StatementType::addition_), true},
    {statement_type_index(StatementType::subtraction_), true},
    {statement_type_index(StatementType::multiplication_), true},
    {statement_type_index(StatementType::division_), true},
    {statement_type_index(StatementType::exponentation_), false},
    {statement_type_index(StatementType::inversion_), false},
    {statement_type_index(StatementType::literal_alnumus_), true},
    {statement_type_index(StatementType::literal_number_), true},
    {statement_type_index(StatementType::eof_), true}};
auto statement_type_to_string = std::map<StatementType, std::string>{
    {StatementType::dereference_, "dereference_"},
    {StatementType::literal_alnumus_, "literal_alnumus_"},
    {StatementType::literal_number_, "literal_number_"},
    {StatementType::addition_, "addition_"},
    {StatementType::subtraction_, "subtraction_"},
    {StatementType::multiplication_, "multiplication_"},
    {StatementType::division_, "division_"},
    {StatementType::inversion_, "inversion_"},
    {StatementType::exponentation_, "exponentation_"},
    {StatementType::eof_, "eof_"}};

struct Tok {
  std::size_t type_index;
  std::string literal;

  Tok(std::size_t type_index) : type_index(type_index), literal("") {}
};
struct StatementNode {
  // Node Properties
  std::size_t type_index;
  std::vector<Tok> tokens;
  // Node Relations
  // StatementNode* parent{ nullptr };
  std::list<StatementNode> body;

  StatementNode(std::size_t type_index) : type_index(type_index) {}
};

StatementNode make_statement_from_token_it(
    std::vector<Tok>::const_iterator tok) {
  return StatementNode(
      statement_type_index(token_to_statement_type[tok->type_index]));
}
auto next(std::vector<Tok>::const_iterator it) { return std::next(it); }

std::optional<StatementNode> build_statement(
    std::vector<Tok>::const_iterator begin,
    std::vector<Tok>::const_iterator end,
    std::optional<StatementNode> last_pass = std::nullopt) {
  auto it = begin;

  if (!last_pass.has_value()) {
    if (token_operation[it->type_index] == Operation::unary_) {
      StatementNode unary_operation = make_statement_from_token_it(it);

      if (next(it, 2) == end) {
        return unary_operation;
      } else {
        // Unary operation is followed by another operator.-> check the
        // importance of the following operator. If the following operator is
        // more important. The entire right side is an operand of the operator
        // preceding the unary op.Unary op is rhs of preceding operator.(if
        // there is one)
        if (token_importance[it->type_index] <
            token_importance[next(it, 2)->type_index]) {
          StatementNode next_operation = make_statement_from_token_it(
              next(it, 2));  // next op is the next operation.
          next_operation.body.push_back(make_statement_from_token_it(
              next(it)));  // lhs of next op is the operand of the unary op.
          unary_operation.body.push_back(
              build_statement(next(it, 2), end,
                              std::make_optional(next_operation))
                  .value());  // Rest of expr is operand of unary op.
          //  Entire statement is a unary operation with rest of expr as the
          //  operand.
          return std::make_optional(unary_operation);
        }
        // If the following operator is less important. The unary operator is
        // the left hand side of the following operator.
        else if (token_importance[it->type_index] >=
                 token_importance[next(it, 2)->type_index]) {
          StatementNode next_pass = make_statement_from_token_it(next(it, 2));
          unary_operation.body.push_back(
              make_statement_from_token_it(next(it)));
          next_pass.body.push_back(unary_operation);
          return build_statement(next(it, 2), end,
                                 std::make_optional(next_pass));
        }
      }
    } else {  // first token is an operand
      StatementNode first_pass = make_statement_from_token_it(next(it));
      first_pass.body.push_back(make_statement_from_token_it(it));
      return build_statement(next(it), end, first_pass);
    }
  } else {  // This is a following pass
    if (next(it) == end) {
      throw std::runtime_error(
          "End of expression after operator. Operator must be followed by "
          "operand.");
    }

    if (next(it)->type_index != token_type_index(TokenType::number_) &&
        next(it)->type_index != token_type_index(TokenType::alnumus_)) {
      if (token_operation[next(it)->type_index] == Operation::unary_) {
        if (next(it, 2) == end) {
          throw std::runtime_error(
              "End of expression after operator. Operator must be followed by "
              "operand.");
        }
      } else
        throw std::runtime_error(
            "Invalid right hand side operand. Operator must be followed by "
            "operand.");
    }

    // Following Operator is End of expression.
    if (next(it, 2) == end) {
      // If the operator is right associative. The right and left hand side are
      // swapped. if the left is actually a unary operator, the right hand side
      // is the unary operation.
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // TODO!!!!!: If the operator following the unary operator is more
      // important. Then the entire right side is an operand of the unary
      // operator.
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if (token_associativity[it->type_index] == Associativity::right_) {
        if (token_operation[next(it)->type_index] == Operation::unary_) {
          last_pass.value().body.push_front(
              make_statement_from_token_it(next(it)));
          last_pass.value().body.front().body.push_back(
              make_statement_from_token_it(next(it, 2)));
        } else {
          last_pass.value().body.push_front(
              make_statement_from_token_it(next(it)));
        }
        return last_pass;
      } else {
        if (token_operation[next(it)->type_index] == Operation::unary_) {
          last_pass.value().body.push_back(
              make_statement_from_token_it(next(it)));
          last_pass.value().body.back().body.push_back(
              make_statement_from_token_it(next(it, 2)));
        } else
          last_pass.value().body.push_back(
              make_statement_from_token_it(next(it)));
        return last_pass;
      }
    } else {
      if (token_importance[it->type_index] <
          token_importance[next(it, 2)->type_index]) {
        if (token_associativity[it->type_index] == Associativity::right_) {
          last_pass.value().body.push_front(
              build_statement(next(it), end, std::nullopt).value());
          return last_pass;
        } else {
          last_pass.value().body.push_back(
              build_statement(next(it), end, std::nullopt).value());
          return last_pass;
        }
      } else if (token_importance[it->type_index] >=
                 token_importance[next(it, 2)->type_index]) {
        // Less important ? -> This operator is a finished expression.Solve
        // it.Set as left hand side of next operator.Go to 1.
        // // If the operator is right associative. The right and left hand side
        // are swapped.
        StatementNode lhs_expression = StatementNode(last_pass->type_index);
        if (token_associativity[it->type_index] == Associativity::right_) {
          lhs_expression.body.push_back(make_statement_from_token_it(next(it)));
          lhs_expression.body.push_back(last_pass.value().body.front());
        } else {
          lhs_expression.body.push_back(last_pass.value().body.front());
          lhs_expression.body.push_back(make_statement_from_token_it(next(it)));
        }

        StatementNode next_pass = make_statement_from_token_it(next(it, 2));
        next_pass.body.push_back(lhs_expression);
        return build_statement(next(it, 2), end, next_pass);
      }
    }
  }
}

static void print_statement(const StatementNode& statement, int depth = 0) {
  for (int i = 0; i < depth; ++i) {
    std::cout << "  ";
  }
  std::cout
      << statement_type_to_string[statement_index_type(statement.type_index)]
      << std::endl;
  for (const StatementNode& child : statement.body) {
    print_statement(child, depth + 1);
  }
}
}  // namespace complex_split_parse
