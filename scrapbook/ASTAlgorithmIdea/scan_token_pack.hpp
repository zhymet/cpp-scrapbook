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
#include <string>
#include <tuple>
#include <vector>

// Implementation of a token scanner allowing for predefined masks with optional tokens.
namespace stp {  // Scanning Token Pack
enum class TkAssoc : int { none_ = 0, left_, right_ };

enum class TkOperation { none_ = 0, unary_, binary_, ternary_, variadic_ };

enum class TkT : int {
  // Abstract
  none = -1,
  invalid,
  eof,

  // Base
  line_comment,
  block_comment,
  string_literal,
  number_literal,
  real_literal,
  newline,
  whitespace,
  alnumus,

  // Assignemnt operators
  simple_assignment,          // =
  addition_assignment,        // +=
  subtraction_assignment,     // -=
  multiplication_assignment,  // *=
  division_assignment,        // /=
  remainder_assignment,       // %=
  bitwise_and_assignment,     // &=
  bitwise_or_assignment,      // |=
  bitwise_xor_assignment,     // ^=
  left_shift_assignment,      // <<=
  right_shift_assignment,     // >>=

  // Increment and decrement operators
  increment,  // ++
  decrement,  // --

  // Arithmetic operators
  addition,             // +
  subtraction,          // -
  multiplication,       // *
  division,             // /
  remainder,            // %
  bitwise_NOT,          // ~
  bitwise_AND,          // &
  bitwise_OR,           // |
  bitwise_XOR,          // ^
  bitwise_left_shift,   // <<
  bitwise_right_shift,  // >>

  // Logical
  negation,     // !
  logical_AND,  // &&
  logical_OR,   // ||

  // Comparison
  equal,                  // ==
  not_equal,              // !=
  less_than,              // <
  greater_than,           // >
  less_than_or_equal,     // <=
  greater_than_or_equal,  // >=
  three_way_comparison,   // <=>

  // Scopes
  open_scope,   // (
  close_scope,  // )
  open_list,    // {
  close_list,   // }
  open_frame,   // [
  close_frame,  // ]

  // Special
  eos,       // ;
  comma,     // ,
  ellipsis,  // ...
  // Special Tokens
  atype_,      // &type
  aidentity_,  // &identity
  avalue_,     // &value
  aint_,       // &int[RANGE[-inf-inf]]
  auint_,      // &uint[RANGE[0...inf]]
  areal_,      // &real[RANGE[-inf...inf]]
  aureal_,     // &ureal[RANGE[0...inf]]
  aoctet_,     // &octet[RANGE[0...255]]
  abit_,       // &bit[RANGE[0...1]]
  aarray_,     // &array[T,Size] // T is a type
  apointer_,   // &pointer[T] // T is a type
  amemory_,    // &memory[T,Size] // T is a type
  afunction_,  // &function

  // Directive Tokens
  enter_,  // #enter
  start_,  // #start
  type_,   // #type
  var_,    // #var
  class_,  // #class

  // Modifier Tokens
  const_,   // #const
  static_,  // #static
  ref_,     // #ref

  // Control Flow Tokens
  if_,        // #if
  else_,      // #else
  elif_,      // #elif
  while_,     // #while
  for_,       // #for
  switch_,    // #switch
  case_,      // #case
  default_,   // #default
  break_,     // #break
  continue_,  // #continue
  ret_,       // #ret
  into_,      // #into
};

enum class StT {
  none_ = -1,  // A none statement is a statement that is not a statement.
  invalid_,    // An invalid statement is a statement that is not a valid
               // statement.

  // Token Analogs (scopes , semicolor, comma are evaluated in this parse step)
  string_literal,
  number_literal,
  real_literal,
  alnumus,

  // Assignemnt operators
  simple_assignment,          // =
  addition_assignment,        // +=
  subtraction_assignment,     // -=
  multiplication_assignment,  // *=
  division_assignment,        // /=
  remainder_assignment,       // %=
  bitwise_and_assignment,     // &=
  bitwise_or_assignment,      // |=
  bitwise_xor_assignment,     // ^=
  left_shift_assignment,      // <<=
  right_shift_assignment,     // >>=

  // Increment and decrement operators
  increment,  // ++
  decrement,  // --

  // Arithmetic operators
  addition,             // +
  subtraction,          // -
  multiplication,       // *
  division,             // /
  remainder,            // %
  bitwise_NOT,          // ~
  bitwise_AND,          // &
  bitwise_OR,           // |
  bitwise_XOR,          // ^
  bitwise_left_shift,   // <<
  bitwise_right_shift,  // >>

  // Logical
  negation,     // !
  logical_AND,  // &&
  logical_OR,   // ||

  // Comparison
  equal,                  // ==
  not_equal,              // !=
  less_than,              // <
  greater_than,           // >
  less_than_or_equal,     // <=
  greater_than_or_equal,  // >=
  three_way_comparison,   // <=>

  // Special Tokens
  atype_,      // &type
  aidentity_,  // &identity
  avalue_,     // &value
  aint_,       // &int[RANGE[-inf-inf]]
  auint_,      // &uint[RANGE[0...inf]]
  areal_,      // &real[RANGE[-inf...inf]]
  aureal_,     // &ureal[RANGE[0...inf]]
  aoctet_,     // &octet[RANGE[0...255]]
  abit_,       // &bit[RANGE[0...1]]
  aarray_,     // &array[T,Size] // T is a type
  apointer_,   // &pointer[T] // T is a type
  amemory_,    // &memory[T,Size] // T is a type
  afunction_,  // &function

  // Directive Tokens
  enter_,  // #enter
  start_,  // #start
  type_,   // #type
  var_,    // #var
  class_,  // #class

  // Modifier Tokens
  const_,   // #const
  static_,  // #static
  ref_,     // #ref

  // Control Flow Tokens
  if_,        // #if
  else_,      // #else
  elif_,      // #elif
  while_,     // #while
  for_,       // #for
  switch_,    // #switch
  case_,      // #case
  default_,   // #default
  break_,     // #break
  continue_,  // #continue
  ret_,       // #ret
  into_,      // #into

  // Abstract
  statement_,    // A statement is a single line of code.
  expression_,   // An expression is a statement that returns a value.
  declaration_,  // A declaration is a statement that does not return a value.
  program_,      // A program is a collection of statements.
  compiled_program_,     // A compiled program is all the statements within the
                         // #enter block.
  interpreted_program_,  // An interpreted program is all statements within the
                         // #start block.

  // Declarations

  // EOF
  eof_,
};

struct Tk {
  TkT type = TkT::none;
  std::string value = "";
};

enum class mask_policy { mandatory, optional };

template <TkT TOKEN_TYPE, mask_policy POLICY = mask_policy::mandatory>
struct tk_mask {
  using type_t = std::integral_constant<TkT, TOKEN_TYPE>;
  using policy_t = std::integral_constant<mask_policy, POLICY>;
  static consteval TkT type() { return TOKEN_TYPE; }
  static consteval mask_policy policy() { return POLICY; }
};

template <size_t I = 0, typename... MaskT>
void constexpr scan_pack_impl(std::tuple<MaskT...> tup,
                              std::vector<Tk>::const_iterator it,
                              std::vector<Tk>::const_iterator end,
                              bool& is_found) {
  // If we have iterated through all elements
  if constexpr (I == sizeof...(MaskT)) {
    // Last case, if nothing is left to
    // iterate, then exit the function
    return;
  } else {
    if (it == end) {
      is_found = false;
      return;
    }
    is_found = false;

    // Check if the current element is mandatory or optional
    if ((std::tuple_element<I, std::tuple<MaskT...>>::type::policy() ==
         mask_policy::mandatory)) {
      // Acces the tuple and go to next element
      if (std::tuple_element_t<I, std::tuple<MaskT...>>::type() == it->type) {
        is_found = true;
      }
    } else if ((std::tuple_element<I, std::tuple<MaskT...>>::type::policy() ==
                mask_policy::optional)) {
      // Acces the tuple and go to next element
      if (std::tuple_element_t<I, std::tuple<MaskT...>>::type() == it->type) {
        is_found = true;
      } else {
        scan_pack_impl<I + 1>(tup, it, end, is_found);
        return;
      }
    }

    // Going for next element.
    scan_pack_impl<I + 1>(tup, it + 1, end, is_found);
  }
}

template <typename... MaskTs>
constexpr bool scan_tokens(std::vector<Tk>::const_iterator it,
                           std::vector<Tk>::const_iterator end) {
  bool is_found = false;
  scan_pack_impl(std::tuple<MaskTs...>(), std::move(it), std::move(end),
                 is_found);
  return is_found;
}

template <typename MaskTupleT>
constexpr bool scan_tokens_pack(std::vector<Tk>::const_iterator it,
                                std::vector<Tk>::const_iterator end) {
  bool is_found = false;
  scan_pack_impl(MaskTupleT(), std::move(it), std::move(end), is_found);
  return is_found;
}

}  // namespace stp
