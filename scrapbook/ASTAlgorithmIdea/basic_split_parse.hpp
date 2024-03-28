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
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <iostream>
// Basic Scplit Parse Algorithm
// Algorithm:
/*
1.a Iterator is on operand? -> Look for a following operator.
1.b Iterator is on operator? -> Look for a following operand in the direction
opposite of the operator's associativity.
                                                        -> operands alwats
search for operators left to right.
2. Check if the following operator is more or less important, or the end of the
expression. a. More important? -> Split the expression in 2 parts. Solve the
right side first. Set as right hand side of the left side. Go to 1. b. Less
important? -> This operator is a finished expression. Solve it. Set as left hand
side of next operator. Go to 1.
*/
// This implementation will handle +, -, *, /, ^, and single character operands.
// All operators are binary. Left associative.
// It will not handle parenthesis, function calls, or any other complex
// expressions.

namespace basic_split_parse {
std::unordered_map<char, int> operator_importance = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

struct Node {
  char value;
  Node* left;
  Node* right;
  Node() : value(' '), left(nullptr), right(nullptr) {}
  Node(char value) : value(value), left(nullptr), right(nullptr) {}
};

static Node* build_ast(std::string::const_iterator begin,
                       std::string::const_iterator end,
                       Node* last_pass = nullptr) {
  auto it = begin;

  // If there was no last pass: this is the first pass.-> initialize split
  // parsing.
  if (last_pass == nullptr) {
    Node* first_pass = new Node();
    first_pass->value = *(it + 1);
    first_pass->left = new Node(*it);
    // advance by 1
    return build_ast(begin + 1, end, first_pass);
  } else {  // This is a following pass
    // Input Validation:
    // If there is no following operand. Error. Operator must be followed by
    // operand.
    if (it + 1 == end) {
      throw std::runtime_error(
          "End of expression after operator. Operator must be followed by "
          "operand.");
    }
    // If the following operand is not an operand. Error. Operator must be
    // followed by operand.
    if (!std::isalnum(*(it + 1))) {
      throw std::runtime_error(
          "Invalid right hand side operand. Operator must be followed by "
          "operand.");
    }

    // Algorithm:
    // If there is no following operator, this is the end of the expression.
    if (it + 2 == end) {
      last_pass->right = new Node(*(it + 1));
      return last_pass;
    } else {
      // 2. Check if the following operator is more or less important
      if (operator_importance[*it] < operator_importance[*(it + 2)]) {
        // Split the expression in 2 parts.Solve the right side first.Set as
        // right hand side of the left side.Finished. advance by 1
        last_pass->right = build_ast(begin + 1, end, nullptr);
        return last_pass;
      } else if (operator_importance[*it] >= operator_importance[*(it + 2)]) {
        // Less important ? -> This operator is a finished expression.Solve
        // it.Set as left hand side of next operator.Go to 1.
        Node* lhs_expression = new Node();
        lhs_expression->value = last_pass->value;
        lhs_expression->left = last_pass->left;
        lhs_expression->right = new Node(*(it + 1));

        Node* next_pass = new Node();
        next_pass->value = *(it + 2);
        next_pass->left = lhs_expression;
        return build_ast(begin + 2, end, next_pass);
      }
    }
  }
}

void print_ast(Node* ast, int depth) {
  if (ast == nullptr) {
    return;
  }
  std::cout << std::string(depth, ' ') << ast->value << std::endl;
  print_ast(ast->left, depth + 1);
  print_ast(ast->right, depth + 1);
}

}  // namespace basic_split_parse 
