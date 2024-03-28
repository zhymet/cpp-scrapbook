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
#include <iterator>
#include <list>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

// Full Expr Split Parse Algorithm
// More complex split parse using a vector of tokens
// This is the same as the above, but using a vector of tokens instead of a
// string. The working 'last_pass' is actually a statement, not a node.
namespace full_expr_split_parse {
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
  open_parenthesis_,
  close_parenthesis_,
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
  open_scope_,
  close_scope_,
  eof_
};
enum class Associativity : bool { left_ = true, right_ = false };
enum class Operation : int { binary_ = 0, unary_ = 1, none_ = 2 };
enum class TokenTraitIndex : std::size_t {
  importance_ = 0,
  associativity_ = 1,
  operation_ = 2,
  produced_statement_ = 3
};
enum class StatementTraitIndex : std::size_t {
  importance_ = 0,
  associativity_ = 1,
  operation_ = 2
};

using TokenTraitsMapType =
    std::map<TokenType,
             std::tuple<int, Associativity, Operation, StatementType>>;
using StatementTraitsMapType =
    std::map<StatementType, std::tuple<int, Associativity, Operation>>;
class Statement;  // Forward declaration

class Token {
  static TokenTraitsMapType token_traits;
  TokenType type_;
  std::string literal_;
  const auto& traits() const { return token_traits; }

 public:
  Token(TokenType type, std::string literal) : type_(type), literal_(literal) {}
  Token(TokenType type) : type_(type), literal_("") {}

  TokenType type() const { return type_; }
  std::string literal() const { return literal_; }

  // Inherited properties
  int importance() const {
    return std::get<static_cast<std::size_t>(TokenTraitIndex::importance_)>(
        token_traits[type_]);
  }
  Associativity associativity() const {
    return std::get<static_cast<std::size_t>(TokenTraitIndex::associativity_)>(
        token_traits[type_]);
  }
  Operation operation() const {
    return std::get<static_cast<std::size_t>(TokenTraitIndex::operation_)>(
        token_traits[type_]);
  }

  // Convert to statement
  Statement to_statement() const;
};

class Statement {
  static StatementTraitsMapType statement_traits;
  // Node Properties
  StatementType type_;
  std::string literal_;
  // Node Relations
  std::list<Statement> body_;

 public:
  static const auto& traits() { return statement_traits; }
  Statement() : type_(StatementType::eof_), literal_("") {}
  Statement(StatementType type) : type_(type), literal_("") {}
  Statement(StatementType type, const std::string& literal)
      : type_(type), literal_(literal) {}
  const std::string& literal() const { return literal_; }
  StatementType type() const { return type_; }
  const std::list<Statement>& body() const { return body_; }
  Statement& front() { return body_.front(); }
  Statement& back() { return body_.back(); }
  Statement& push_back(Statement stmt) {
    body_.push_back(stmt);
    return body_.back();
  }
  Statement& push_front(Statement stmt) {
    body_.push_front(stmt);
    return body_.front();
  }

  // Inherited properties
  int importance() {
    return std::get<static_cast<std::size_t>(StatementTraitIndex::importance_)>(
        statement_traits[type_]);
  }
  Associativity associativity() {
    return std::get<static_cast<std::size_t>(
        StatementTraitIndex::associativity_)>(statement_traits[type_]);
  }
  Operation operation() {
    return std::get<static_cast<std::size_t>(StatementTraitIndex::operation_)>(
        statement_traits[type_]);
  }
};

Statement Token::to_statement() const {
  return Statement(
      std::get<static_cast<std::size_t>(TokenTraitIndex::produced_statement_)>(
          token_traits[type_]),
      literal_);
}
StatementTraitsMapType Statement::statement_traits = {
    {StatementType::literal_alnumus_,
     {INT_MAX, Associativity::left_, Operation::none_}},
    {StatementType::literal_number_,
     {INT_MAX, Associativity::left_, Operation::none_}},
    {StatementType::dereference_,
     {900, Associativity::right_, Operation::unary_}},
    {StatementType::addition_,
     {1000, Associativity::left_, Operation::binary_}},
    {StatementType::subtraction_,
     {1000, Associativity::left_, Operation::binary_}},
    {StatementType::multiplication_,
     {2000, Associativity::left_, Operation::binary_}},
    {StatementType::division_,
     {2000, Associativity::left_, Operation::binary_}},
    {StatementType::inversion_,
     {4000, Associativity::right_, Operation::unary_}},
    {StatementType::exponentation_,
     {3000, Associativity::right_, Operation::binary_}},
    {StatementType::open_scope_,
     {INT_MAX, Associativity::left_, Operation::none_}},
    {StatementType::close_scope_,
     {INT_MAX, Associativity::left_, Operation::none_}},
    {StatementType::eof_, {INT_MAX, Associativity::left_, Operation::none_}}};
TokenTraitsMapType Token::token_traits = {
    {TokenType::alnumus_,
     {INT_MAX, Associativity::left_, Operation::none_,
      StatementType::literal_alnumus_}},
    {TokenType::number_,
     {INT_MAX, Associativity::left_, Operation::none_,
      StatementType::literal_number_}},
    {TokenType::plus_,
     {1000, Associativity::left_, Operation::binary_,
      StatementType::addition_}},
    {TokenType::minus_,
     {1000, Associativity::left_, Operation::binary_,
      StatementType::subtraction_}},
    {TokenType::multiply_,
     {2000, Associativity::left_, Operation::binary_,
      StatementType::multiplication_}},
    {TokenType::divide_,
     {2000, Associativity::left_, Operation::binary_,
      StatementType::division_}},
    {TokenType::dereference_,
     {900, Associativity::right_, Operation::unary_,
      StatementType::dereference_}},
    {TokenType::power_,
     {3000, Associativity::right_, Operation::binary_,
      StatementType::exponentation_}},
    {TokenType::unary_minus_,
     {4000, Associativity::right_, Operation::unary_,
      StatementType::inversion_}},
    {TokenType::open_parenthesis_,
     {INT_MAX, Associativity::left_, Operation::none_,
      StatementType::open_scope_}},
    {TokenType::close_parenthesis_,
     {INT_MAX, Associativity::left_, Operation::none_,
      StatementType::close_scope_}},
    {TokenType::eof_,
     {INT_MAX, Associativity::left_, Operation::none_, StatementType::eof_}}};

// For debugging/printing NOT the literal.
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

// Method inline for std::next
inline auto next(std::vector<Token>::const_iterator it) {
  return std::next(it);
}

// Method for determining the start and end of a scope. Result is two pairs of
// iterators to the start and end of the scope, and the start and end of the
// inside of the scope. The scope is defined by the first open parenthesis and
// the last close parenthesis.
// <@class:ScopeResult>
// <@brief> A struct containing the result of a scope search. Use member methods
// to access the scope.
// <@member:valid> If the scope is valid, invalid scopes indicate a mismatched
// parenthesis.
struct ScopeResult {
  bool valid{false};
  std::vector<Token>::const_iterator begin_;
  std::vector<Token>::const_iterator end_;

  // <@method:contained_end> Returns the end of the scope, not including the
  // close token.
  auto contained_end() const { return end_ - 1; }
  // <@method:contained_begin> Returns the beginning of the scope, not including
  // the open token.
  auto contained_begin() const { return begin_ + 1; }
  // <@method:is_empty> Returns true if the scope is empty.
  auto is_empty() const { return contained_begin() == contained_end(); }
  // <@method:scope_end> Returns the end of the scope, including the close
  // token.
  auto scope_end() const { return end_; }
  // <@method:scope_begin> Returns the beginning of the scope, including the
  // open token.
  auto scope_begin() const { return begin_; }

  ScopeResult() = default;
  ScopeResult(bool valid, std::vector<Token>::const_iterator begin,
              std::vector<Token>::const_iterator end)
      : valid(valid), begin_(begin), end_(end) {}
};
ScopeResult find_scope(std::vector<Token>::const_iterator cursor,
                       std::vector<Token>::const_iterator end) {
  auto scope_depth = 0;
  std::vector<Token>::const_iterator last_open = cursor;
  std::vector<Token>::const_iterator last_closed = cursor;

  if (cursor->type() != TokenType::open_parenthesis_) {
    throw std::runtime_error(
        "find_scope: Cursor is not at an open parenthesis.");
  }

  // find the last matching close token, if there is no matching close token,
  // return false
  for (auto i = cursor; i < end; i++) {
    if (i->type() == TokenType::open_parenthesis_) {
      scope_depth++;
      last_open = i;
    } else if (i->type() == TokenType::close_parenthesis_) {
      scope_depth--;
      last_closed = i;
    }

    if (scope_depth == 0) {
      break;
    }
  }

  // NOTE: We are adding 1 to last closed because the end is 1 past the last
  // token.
  if (scope_depth != 0) {
    return ScopeResult{false, cursor,
                       last_closed + 1};  // No matching close token
  } else {
    return ScopeResult{true, cursor, last_closed + 1};
  }
}

std::optional<Statement> build_statement(
    std::vector<Token>::const_iterator begin,
    std::vector<Token>::const_iterator end,
    std::optional<Statement> last_pass = std::nullopt) {
  auto it = begin;

  if (!last_pass.has_value()) {
    // Determine the following operator and operand.
    if (it->operation() ==
        Operation::unary_) {  // This expression starts with a unary operation.
      Statement unary_operation = it->to_statement();
      if (next(it, 2) == end) {  // Unary operation is not followed by operand.
        unary_operation.push_back(
            next(it)->to_statement());  // lhs of unary op is the operand of the
                                        // unary op.
        return unary_operation;  // Entire statement is this unary operation.
      } else {                   // Unary operation is followed by operand.
        if (it->importance() <
            next(it, 2)->importance()) {  // Unary operation is less important
                                          // than next operation.
          Statement next_operation =
              next(it, 2)->to_statement();  // next op is the next operation.
          next_operation.push_back(
              next(it)->to_statement());  // lhs of next op is the operand of
                                          // the unary op.
          unary_operation.push_back(
              build_statement(next(it, 2), end,
                              std::make_optional(next_operation))
                  .value());  // Rest of expr is operand of unary op.
          return std::make_optional(
              unary_operation);  // Entire statement is a unary operation with
                                 // rest of expr as the operand.
        } else if (it->importance() >=
                   next(it, 2)
                       ->importance()) {  // Unary operation is more or equally
                                          // important than next operation.
          Statement next_pass =
              next(it, 2)->to_statement();  // next pass is the next operation.
          unary_operation.push_back(
              next(it)->to_statement());  // lhs of unary op is the operand of
                                          // the unary op.
          next_pass.push_back(
              unary_operation);  // lhs of next pass is the unary op.
          return build_statement(
              next(it, 2), end,
              std::make_optional(next_pass));  // Rest of expr is the next pass.
        }
      }
    } else if (it->type() ==
               TokenType::open_parenthesis_) {  // This expression starts with a
                                                // scope.
      ScopeResult scope = find_scope(it, end);
      if (!scope.valid) {  // If the scope is invalid, throw an error.
        throw std::runtime_error("Mismatched parenthesis.");
      } else if (scope.is_empty()) {  // If the scope is empty, throw an error.
        throw std::runtime_error("Empty parenthesis.");
      } else {
        if (scope.scope_end() ==
            end) {  // Scope is redundant, the entire statement is the scope.
          return build_statement(scope.contained_begin(),
                                 scope.contained_end());
        } else {  // If the scope is followed by an operator, the scope is a lhs
                  // operand.
          Statement next_pass =
              scope.scope_end()
                  ->to_statement();  // next pass is the following operator.
          next_pass.push_back(
              build_statement(scope.contained_begin(), scope.contained_end())
                  .value());  // lhs of next pass is the scope.
          return build_statement(
              scope.scope_end(), end,
              std::make_optional(next_pass));  // Rest of expr is the next pass.
        }
      }
    } else {  // first token is assumed to be a singular operand NOTE: (may
              // change this later to throw an error on invalid token)
      Statement first_pass =
          next(it)->to_statement();  // first pass is the following operator.
      first_pass.push_back(
          it->to_statement());  // lhs of first pass is the this operand.
      return build_statement(next(it), end,
                             first_pass);  // Rest of expr is the first pass.
    }
  } else {
    // This is a following pass, assume 'it' is a binary operator.
    // Assume last_pass is an unfinished binary operation of type binary
    // operator. Do some input validation first to reduce code duplication.
    if (next(it) == end) {  // If there is no following operand. Error.Binary
                            // Operator must be followed by operand.
      throw std::runtime_error(
          "End of expression after binary operator. Operator must be followed "
          "by operand.");
    }

    // We will check for single operands, if it is not. Then we assume it must
    // be a scope or a unary operator.Otherwise Error.
    if (next(it)->type() != TokenType::number_ &&
        next(it)->type() != TokenType::alnumus_) {  // is not a single operand?
      if (next(it)->operation() == Operation::unary_) {  // is a unary operator?
        if (next(it, 2) == end) {
          throw std::runtime_error(
              "End of expression after unary operator. Operator must be "
              "followed by operand.");
        }
      } else if (next(it)->type() ==
                 TokenType::open_parenthesis_) {  // is a scope?
        ScopeResult scope = find_scope(next(it), end);
        if (!scope.valid) {
          throw std::runtime_error("Mismatched parenthesis.");
        } else if (scope.is_empty()) {
          throw std::runtime_error("Empty parenthesis.");
        }
      } else  // is not a unary operator or a scope? Error!
        throw std::runtime_error(
            "Invalid right hand side operand. Operator must be followed by "
            "operand.");
    }

    // Determine the following operator and operand.
    // If the following operand token is a unary operation, the next operator is
    // the one after that operation. If the following operand is a scope,
    // everything within the scope is a statement- which is the operand.
    //		-> next operator is the one after the scope.
    // Else the next operator is the token after the following operand.
    std::vector<Token>::const_iterator next_operator_it;
    if (next(it)->operation() == Operation::unary_) {
      next_operator_it = next(it, 3);
    } else if (next(it)->type() == TokenType::open_parenthesis_) {
      ScopeResult scope = find_scope(next(it), end);
      next_operator_it = scope.scope_end();
    } else {
      next_operator_it = next(it, 2);
    }

    // If we are at the end of the expression, this is the last pass. Complete
    // the binary operation based on associativity and rhs operand.
    if (next_operator_it == end) {
      if (it->associativity() ==
          Associativity::right_) {  // right assoc push front next operand as
                                    // lhs
        if (next(it)->operation() ==
            Operation::unary_) {  // next operand is a unary operation.
          last_pass.value().push_front(next(it)->to_statement());
          last_pass.value().front().push_back(next(it, 2)->to_statement());
        } else if (next(it)->type() ==
                   TokenType::open_parenthesis_) {  // next operand is a scope.
          ScopeResult scope = find_scope(it, end);
          last_pass.value().push_front(
              build_statement(scope.contained_begin(), scope.contained_end())
                  .value());
        } else {  // next operand is a single operand.
          last_pass.value().push_front(next(it)->to_statement());
        }
        return last_pass;
      } else {  // left assoc push back next operand as rhs
        if (next(it)->operation() ==
            Operation::unary_) {  // next operand is a unary operation.
          last_pass.value().push_back(next(it)->to_statement());
          last_pass.value().back().push_back(next(it, 2)->to_statement());
        } else if (next(it)->type() ==
                   TokenType::open_parenthesis_) {  // next operand is a scope.
          ScopeResult scope = find_scope(next(it), end);
          last_pass.value().push_back(
              build_statement(scope.contained_begin(), scope.contained_end())
                  .value());
        } else {  // next operand is a single operand.
          last_pass.value().push_back(next(it)->to_statement());
        }
        return last_pass;
      }
    } else {
      // Else we are inside a binary operation. Check if the following operator
      // is more or less important.
      if (it->importance() <
          next_operator_it->importance()) {  // More important?
        // Split the expression in 2 parts.Solve the right side first.Set as
        // right hand side of the left side.Finished.
        if (it->associativity() ==
            Associativity::right_) {  // right assoc swap lhs and rhs
          last_pass.value().push_front(
              build_statement(next(it), end, std::nullopt)
                  .value());  // lhs is the rest of the expression.
          return last_pass;   // End of expr.
        } else {              // left assoc
          last_pass.value().push_back(
              build_statement(next(it), end, std::nullopt)
                  .value());  // rhs is the rest of the expression.
          return last_pass;   // End of expr.
        }
      } else if (it->importance() >=
                 next_operator_it->importance()) {  // Less important ?
        // ->	This operator is a finished expression.Solve it.
        //		Set as left hand side of next operator. Call self with
        // next operator as the cursor. 		If the operator is right
        // associative. The right and left hand side are swapped.
        Statement lhs_expression =
            Statement(last_pass.value().type());  // lhs is the last pass.
        if (it->associativity() == Associativity::right_) {  // right Assoc
          if (next(it)->type() ==
              TokenType::open_parenthesis_) {  // next operand is a scope.
            ScopeResult scope = find_scope(next(it), end);  // find the scope.
            lhs_expression.push_back(
                build_statement(scope.contained_begin(), scope.contained_end())
                    .value());  // solve and set as lhs.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the rhs.
          } else if (next(it)->operation() ==
                     Operation::unary_) {  // next operand is a unary operation.
            lhs_expression.push_back(
                next(it)->to_statement());  // this unary op is the lhs.
            lhs_expression.back().push_back(
                next(it, 2)->to_statement());  // add operand to unary op.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the rhs.
          } else {  // next operand is a single operand.
            lhs_expression.push_back(
                next(it)->to_statement());  // this operand is the lhs.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the rhs.
          }
        } else {  // left Assoc
          if (next(it)->type() ==
              TokenType::open_parenthesis_) {  // next operand is a scope.
            ScopeResult scope = find_scope(next(it), end);  // find the scope.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the lhs.
            lhs_expression.push_back(
                build_statement(scope.contained_begin(), scope.contained_end())
                    .value());  // solve and set as rhs.

          } else if (next(it)->operation() ==
                     Operation::unary_) {  // next operand is a unary operation.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the lhs.
            lhs_expression.push_back(
                next(it)->to_statement());  // this unary op is the rhs.
            lhs_expression.back().push_back(
                next(it, 2)->to_statement());  // add operand to unary op.
          } else {  // next operand is a single operand.
            lhs_expression.push_back(
                last_pass.value().front());  // last operation's lhs is the lhs.
            lhs_expression.push_back(
                next(it)->to_statement());  // this operand is the rhs.
          }
        }

        Statement next_pass =
            next_operator_it
                ->to_statement();  // next pass is the next operator.
        next_pass.push_back(
            lhs_expression);  // lhs of next pass is the lhs expression.
        return build_statement(next_operator_it, end,
                               next_pass);  // Rest of expr is the next pass.
      }
    }
  }
}

static void print_statement(const Statement& statement, int depth = 0) {
  for (int i = 0; i < depth; ++i) {
    std::cout << "  ";
  }
  std::cout << statement_type_to_string[statement.type()] << std::endl;
  for (const Statement& child : statement.body()) {
    print_statement(child, depth + 1);
  }
}

}  // namespace full_expr_split_parse
