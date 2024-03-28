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
#include <cstdint>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

// Token Statement Split Parse Algorithm
// More complex split parse using a vector of tokens
// This is the same as the above, but using a vector of tokens instead of a
// string. The working 'last_pass' is actually a statement, not a node.
namespace token_statement_split_parse {
enum class Token : int {
  alnumus_,
  number_,
  plus_,
  minus_,
  multiply_,
  divide_,
  power_,
  unary_minus_,
  eof_ = INT_MAX
};

enum class StatementType : int {
  literal_alnumus_ = 0,
  literal_number_,
  addition_,
  subtraction_,
  multiplication_,
  division_,
  inversion_,
  exponentation_
};

auto token_importance =
    std::map<Token, int>{{Token::plus_, 1},          {Token::minus_, 1},
                         {Token::multiply_, 2},      {Token::divide_, 2},
                         {Token::power_, 3},         {Token::unary_minus_, 4},
                         {Token::alnumus_, INT_MAX}, {Token::number_, INT_MAX},
                         {Token::eof_, INT_MAX}};

// true = left associative, false = right associative
enum Associativity { left_ = true, right_ = false };

enum Operation { binary_ = 0, unary_ = 1, none_ = 2 };

auto token_operation =
    std::map<Token, Operation>{{Token::plus_, Operation::binary_},
                               {Token::minus_, Operation::binary_},
                               {Token::multiply_, Operation::binary_},
                               {Token::divide_, Operation::binary_},
                               {Token::power_, Operation::binary_},
                               {Token::unary_minus_, Operation::unary_},
                               {Token::alnumus_, Operation::none_},
                               {Token::number_, Operation::none_},
                               {Token::eof_, Operation::none_}};

auto token_associativity = std::map<Token, bool>{
    {Token::plus_, true},     {Token::minus_, true},
    {Token::multiply_, true}, {Token::divide_, true},
    {Token::power_, false},   {Token::unary_minus_, false},
    {Token::alnumus_, true},  {Token::number_, true},
    {Token::eof_, true}};

auto token_to_statement_type = std::map<Token, StatementType>{
    {Token::alnumus_, StatementType::literal_alnumus_},
    {Token::number_, StatementType::literal_number_},
    {Token::plus_, StatementType::addition_},
    {Token::minus_, StatementType::subtraction_},
    {Token::multiply_, StatementType::multiplication_},
    {Token::divide_, StatementType::division_},
    {Token::power_, StatementType::exponentation_},
    {Token::unary_minus_, StatementType::inversion_},
    {Token::eof_, StatementType::literal_alnumus_}};

auto statement_type_to_string = std::map<StatementType, std::string>{
    {StatementType::literal_alnumus_, "alnumus"},
    {StatementType::literal_number_, "number"},
    {StatementType::addition_, "addition"},
    {StatementType::subtraction_, "subtraction"},
    {StatementType::multiplication_, "multiplication"},
    {StatementType::division_, "division"},
    {StatementType::exponentation_, "exponentation"},
    {StatementType::inversion_, "inversion"}};

struct Statement {
  StatementType type;
  Statement* left{nullptr};
  Statement* right{nullptr};

  Statement(StatementType type) : type(type), left(nullptr), right(nullptr) {}
};

static Statement* build_statement(std::vector<Token>::const_iterator begin,
                                  std::vector<Token>::const_iterator end,
                                  Statement* last_pass = nullptr) {
  auto it = begin;

  // If there was no last pass: this is the first pass.-> initialize split
  // parsing.
  if (last_pass == nullptr) {
    // If the operator is unary: 'it' is the operator and 'it + 1' is the
    // operand. Furthermore: This expression is complete and is the lhs of next
    // operator. Advance to the next operator if there is one.
    if (token_operation[*it] == Operation::unary_) {
      Statement* unary_operation = new Statement(token_to_statement_type[*it]);
      unary_operation->left = new Statement(token_to_statement_type[*(it + 1)]);

      // If there is no following operator, this is the end of the expression.
      if (it + 2 == end) {
        return unary_operation;
      } else {
        Statement* next_pass =
            new Statement(token_to_statement_type[*(it + 2)]);
        next_pass->left = unary_operation;
        return build_statement(begin + 2, end, next_pass);
      }
    } else {
      Statement* first_pass = new Statement(token_to_statement_type[*(it + 1)]);
      first_pass->left = new Statement(token_to_statement_type[*it]);
      // advance by 1
      return build_statement(begin + 1, end, first_pass);
    }
  } else {  // This is a following pass
    // Input Validation:
    // If there is no following operand. Error. Operator must be followed by
    // operand.
    if (it + 1 == end) {
      throw std::runtime_error(
          "End of expression after operator. Operator must be followed by "
          "operand.");
    }
    // If the following operand is not an valid operand. Error. Operator must be
    // followed by operand.
    if ((*(it + 1)) != Token::number_ && (*(it + 1)) != Token::alnumus_) {
      // check if the following operand is a unary operator
      if (token_operation[*(it + 1)] == Operation::unary_) {
        // The unary operator most definitley must be solved first. And must
        // have an operand to the right. If there is no following operand.
        // Error. Operator must be followed by operand.
        if (it + 2 == end) {
          throw std::runtime_error(
              "End of expression after operator. Operator must be followed by "
              "operand.");
        }
      } else
        throw std::runtime_error(
            "Invalid right hand side operand. Operator must be followed by "
            "operand.");
    }

    // Algorithm:
    // If there is no following operator, this is the end of the expression.
    if (it + 2 == end) {
      // If the operator is right associative. The right and left hand side are
      // swapped. if the left is actually a unary operator, the right hand side
      // is the unary operation.
      if (token_associativity[*it] == Associativity::right_) {
        if (token_operation[*(it + 1)] == Operation::unary_) {
          last_pass->right = last_pass->left;
          last_pass->left = new Statement(token_to_statement_type[*(it + 1)]);
          last_pass->left->left =
              new Statement(token_to_statement_type[*(it + 2)]);

        } else {
          last_pass->right = last_pass->left;
          last_pass->left = new Statement(token_to_statement_type[*(it + 1)]);
        }
        return last_pass;
      } else {
        if (token_operation[*(it + 1)] == Operation::unary_) {
          last_pass->right = new Statement(token_to_statement_type[*(it + 1)]);
          last_pass->right->left =
              new Statement(token_to_statement_type[*(it + 2)]);
        } else
          last_pass->right = new Statement(token_to_statement_type[*(it + 1)]);
        return last_pass;
      }
    } else {
      // 2. Check if the following operator is more or less important
      if (token_importance[*it] < token_importance[*(it + 2)]) {
        // Split the expression in 2 parts.Solve the right side first.Set as
        // right hand side of the left side.Finished.
        // // If the operator is right associative. The right and left hand side
        // are swapped. advance by 1
        if (token_associativity[*it] == Associativity::right_) {
          last_pass->right = last_pass->left;
          last_pass->left = build_statement(begin + 1, end, nullptr);
          return last_pass;
        } else {
          last_pass->right = build_statement(begin + 1, end, nullptr);
          return last_pass;
        }
      } else if (token_importance[*it] >= token_importance[*(it + 2)]) {
        // Less important ? -> This operator is a finished expression.Solve
        // it.Set as left hand side of next operator.Go to 1.
        // // If the operator is right associative. The right and left hand side
        // are swapped.
        Statement* lhs_expression = new Statement(last_pass->type);
        if (token_associativity[*it] == Associativity::right_) {
          lhs_expression->right = last_pass->left;
          lhs_expression->left =
              new Statement(token_to_statement_type[*(it + 1)]);
        } else {
          lhs_expression->left = last_pass->left;
          lhs_expression->right =
              new Statement(token_to_statement_type[*(it + 1)]);
        }

        Statement* next_pass =
            new Statement(token_to_statement_type[*(it + 2)]);
        next_pass->left = lhs_expression;
        return build_statement(begin + 2, end, next_pass);
      }
    }
  }
}

static void print_statement(Statement* statement, int depth = 0) {
  if (statement == nullptr) {
    return;
  }

  std::string indent = "";
  for (int i = 0; i < depth; i++) {
    indent += "  ";
  }

  std::cout << indent << "[" << statement_type_to_string[statement->type] << "]"
            << std::endl;

  if (statement->left != nullptr) {
    std::cout << indent << "  Left: ";
    print_statement(statement->left, depth + 1);
  }

  if (statement->right != nullptr) {
    std::cout << indent << "  Right: ";
    print_statement(statement->right, depth + 1);
  }
}

}  // namespace token_statement_split_parse
