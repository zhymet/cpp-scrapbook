#pragma once
// Generates random but valid C& expressions.
#include <algorithm>
#include <concepts>
#include <fstream>
#include <iostream>
#include <list>
#include <optional>
#include <random>
#include <ranges>
#include <span>
#include <stack>
#include <string>
#include <vector>

std::vector<char> alpha_chars = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
std::vector<char> numeric_chars = {'0', '1', '2', '3', '4',
                                   '5', '6', '7', '8', '9'};
std::vector<char> alnumus_chars = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};

std::vector<std::string> operands = {"a",  "'a'", "1",  "1.0",
                                     "1c", "1B",  "1u", "{a,b}"};
std::vector<std::string> binary_operators = {
    ".",  "+",  "-",  "*", "/", "%",  "&",  "|",  "<<",
    ">>", "==", "!=", "<", ">", "<=", ">=", "<=>"};
std::vector<std::string> unary_right_operators = {"++", "--", "~", "!"};
std::vector<std::string> unary_left_operators = {"++", "--"};
std::vector<std::string> variadic_operators = {"@["};

template <typename T>
concept IterableWithIndexOperator = requires(T t) {
  typename T::value_type;
  {
    t[std::declval<typename T::size_type>()]
  } -> std::same_as<typename T::value_type&>;
  { std::begin(t) } -> std::same_as<typename T::iterator>;
  { std::end(t) } -> std::same_as<typename T::iterator>;
};

using randomness_generator = std::mt19937;

template <typename T>
  requires std::integral<T>
auto rand_uniform_integral(randomness_generator& generator, T min, T max) {
  std::uniform_int_distribution<T> distribution(min, max);
  return distribution(generator);
}

template <typename T>
  requires std::floating_point<T>
auto rand_uniform_floating(randomness_generator& generator, T min, T max) {
  std::uniform_real_distribution<T> distribution(min, max);
  return distribution(generator);
}

template <typename T>
  requires std::floating_point<T>
auto rand_bernoulli(randomness_generator& generator, T percent) {
  std::bernoulli_distribution distribution(percent);
  return distribution(generator);
}

template <typename T>
  requires IterableWithIndexOperator<T>
auto rand_element(randomness_generator& generator, const T& container) {
  std::uniform_int_distribution<std::size_t> distribution(0,
                                                          container.size() - 1);
  return container[distribution(generator)];
}

std::string rand_alnumus_literal(randomness_generator& generator,
                                 std::size_t min_length,
                                 std::size_t max_length);
std::string rand_number_literal(randomness_generator& generator,
                                long long int min_val, long long int max_val);
std::string rand_real_literal(randomness_generator& generator,
                              long double min_val, long double max_val);
std::string rand_unsigned_literal(randomness_generator& generator,
                                  long long unsigned min_val,
                                  long long unsigned max_val);
std::string rand_char_literal(randomness_generator& generator);
std::string rand_byte_literal(randomness_generator& generator);
std::string rand_bit_literal(randomness_generator& generator);
std::string rand_string_literal(randomness_generator& generator,
                                std::size_t min_length, std::size_t max_length);
std::string rand_literal(randomness_generator& generator);
std::string rand_generic_list(randomness_generator& generator,
                              std::size_t min_length, std::size_t max_length);
std::string rand_operand(randomness_generator& generator);
std::string rand_paren_list(randomness_generator& generator,
                            std::size_t min_length, std::size_t max_length);
std::string rand_binary_operator(randomness_generator& generator);
std::string rand_unary_right_operator(randomness_generator& generator);
std::string rand_unary_left_operator(randomness_generator& generator);
std::string rand_variadic_operator(randomness_generator& generator,
                                   std::size_t min_args, std::size_t max_args);
std::string rand_expression(randomness_generator& generator);

std::string rand_alnumus_literal(randomness_generator& generator,
                                 std::size_t min_length,
                                 std::size_t max_length) {
  auto word_length = rand_uniform_integral(generator, min_length, max_length);
  std::string word;

  if (word_length == 0) return word;

  // first character is always an alpha character
  word += rand_element(generator, alpha_chars);

  for (std::size_t i = 1; i < word_length; ++i) {
    word += rand_element(generator, alnumus_chars);
  }

  return word;
}

std::string rand_number_literal(randomness_generator& generator,
                                long long int min_val, long long int max_val) {
  auto number = rand_uniform_integral(generator, min_val, max_val);
  return std::to_string(number);
}

std::string rand_real_literal(randomness_generator& generator,
                              long double min_val, long double max_val) {
  auto number = rand_uniform_floating(generator, min_val, max_val);
  return std::to_string(number);
}

std::string rand_unsigned_literal(randomness_generator& generator,
                                  long long unsigned min_val,
                                  long long unsigned max_val) {
  auto number = rand_uniform_integral(generator, min_val, max_val);
  return std::to_string(number) + "u";
}

std::string rand_char_literal(randomness_generator& generator) {
  return std::string("'") + rand_element(generator, alnumus_chars) + "'c";
}

std::string rand_byte_literal(randomness_generator& generator) {
  auto rand_unsigned_char = rand_uniform_integral(generator, 0, 255);
  return std::to_string(rand_unsigned_char) + "c";
}

std::string rand_bit_literal(randomness_generator& generator) {
  auto rand_bool = rand_uniform_integral(generator, 0, 1);
  return std::to_string(rand_bool) + "b";
}

std::string rand_string_literal(randomness_generator& generator,
                                std::size_t min_length,
                                std::size_t max_length) {
  auto word_length = rand_uniform_integral(generator, min_length, max_length);
  std::string word;

  if (word_length == 0) return word;

  word += "\'";
  for (std::size_t i = 0; i < word_length; ++i) {
    word += rand_element(generator, alnumus_chars);
  }
  word += "\'";

  return word;
}

std::string rand_literal(randomness_generator& generator) {
  std::uniform_int_distribution<int> literal_distribution(0, 6);
  switch (literal_distribution(generator)) {
    case 0:
      return rand_alnumus_literal(generator, 1, 10);
    case 1:
      return rand_number_literal(generator, 0, 10000);
    case 2:
      return rand_real_literal(generator, -5000, 100000);
    case 3:
      return rand_unsigned_literal(generator, 0, 100000);
    case 4:
      return rand_char_literal(generator);
    case 5:
      return rand_byte_literal(generator);
    case 6:
      return rand_bit_literal(generator);
    case 7:
      return rand_string_literal(generator, 1, 10);
    default:
      return rand_alnumus_literal(generator, 1, 10);
  }
}

std::string rand_generic_list(randomness_generator& generator,
                              std::size_t min_length, std::size_t max_length) {
  auto list_length = rand_uniform_integral(generator, min_length, max_length);
  std::string list;

  if (list_length == 0) {
    list = "{}";
    return list;
  }

  list += "{";
  for (std::size_t i = 0; i < list_length; ++i) {
    list += rand_literal(generator);
    if (i != list_length - 1) list += ",";
  }
  list += "}";

  return list;
}

std::string rand_paren_list(randomness_generator& generator,
                            std::size_t min_length, std::size_t max_length) {
  auto list_length = rand_uniform_integral(generator, min_length, max_length);
  std::string list;

  if (list_length == 0) {
    list = "()";
    return list;
  }

  list += "(";
  for (std::size_t i = 0; i < list_length; ++i) {
    list += rand_literal(generator);
    if (i != list_length - 1) list += ",";
  }
  list += ")";

  return list;
}

std::string rand_operand(randomness_generator& generator) {
  auto a = rand_uniform_integral(generator, 0, 4);
  switch (a) {
    case 0:  // Literal
      return rand_literal(generator);
    case 2:  // List
      return rand_generic_list(generator, 1, 10);
    case 3:  // Func call
    {
      bool b = rand_bernoulli(
          generator, 0.25);  // Randomly add variadic after function call.
      if (b) {
        // randomly decide if it will be before or after the function call.
        if (rand_bernoulli(generator, 0.5)) {
          return rand_alnumus_literal(generator, 1, 10) +
                 rand_paren_list(generator, 1, 10) +
                 rand_variadic_operator(generator, 1, 5);
        } else {
          return rand_alnumus_literal(generator, 1, 10) +
                 rand_variadic_operator(generator, 1, 5) +
                 rand_paren_list(generator, 1, 10);
        }
      } else {
        return rand_alnumus_literal(generator, 1, 10) +
               rand_paren_list(generator, 1, 10);
      }
    }
    case 4:  // alnumus with variadic operator
      return rand_alnumus_literal(generator, 1, 10) +
             rand_variadic_operator(generator, 1, 5);
    default:
      return rand_literal(generator);
  }
}

std::string rand_binary_operator(randomness_generator& generator) {
  return rand_element(generator, binary_operators);
}

std::string rand_unary_right_operator(randomness_generator& generator) {
  return rand_element(generator, unary_right_operators);
}

std::string rand_unary_left_operator(randomness_generator& generator) {
  return rand_element(generator, unary_left_operators);
}

std::string rand_variadic_operator(randomness_generator& generator,
                                   std::size_t min_args, std::size_t max_args) {
  auto op_start = rand_element(generator, variadic_operators);
  auto n_args = rand_uniform_integral(generator, min_args, max_args);
  std::string args = op_start;

  for (std::size_t i = 0; i < n_args; ++i) {
    args += rand_literal(generator);
    if (i != n_args - 1) args += ",";
  }
  args += "]";

  return args;
}

std::string rand_expression(randomness_generator& generator) {
  auto expr_size = rand_uniform_integral(generator, 1, 3);
  std::string expr;

  if (expr_size == 0) {
    expr = rand_operand(generator);
    return expr;
  }

  for (std::size_t i = 0; i < expr_size; ++i) {
    auto op = rand_operand(generator);

    if (rand_bernoulli(generator, 0.25)) {
      auto n_unary_right_ops = rand_uniform_integral(generator, 1, 5);
      for (std::size_t j = 0; j < n_unary_right_ops; ++j) {
        op = rand_unary_right_operator(generator) + op;
      }
    }

    if (rand_bernoulli(generator, 0.25)) {
      auto n_unary_left_ops = rand_uniform_integral(generator, 1, 5);
      for (std::size_t j = 0; j < n_unary_left_ops; ++j) {
        op += rand_unary_left_operator(generator);
      }
    }

    // If this isnt the last operand, add a binary operator
    if (i != expr_size - 1) {
      op += rand_binary_operator(generator);
    }

    expr += op;
  }

  return expr;
}

auto generate_expression_file(std::size_t nof_expressions,
                              std::string filename) {
  std::random_device rd;
  std::mt19937 gen(rd());
  auto n_expressions = nof_expressions;
  std::ofstream file(filename, std::ios::app);
  for (int i = 0; i < n_expressions / 1000; ++i) {
    std::cout << "Generating expressions " << i * 1000 << " to "
              << (i + 1) * 1000 << std::endl;
    std::vector<std::string> expressions;
    expressions.reserve(1000);
    for (int j = 0; j < 1000; ++j) {
      expressions.push_back(rand_expression(gen));
    }
    for (int j = 0; j < 1000; ++j) {
      file << expressions[j] << ";\n";
    }
  }
  std::cout << "Done generating expressions" << std::endl;
  file.close();
  return 0;
}