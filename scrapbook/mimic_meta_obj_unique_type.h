#pragma once
#include <concepts>
#include <iostream>
#include <string>

// Mimic is a meta object. Mimics a type and its operations but is a dirrent
// type. Like a distinct typedef. UNIQUE_TYPE macro is a shortcut for a decltype
// of a void lamnbda which is unique every time.
//

// A type that is unique every time - but equivalent to its own type.
#define UNIQUE_TYPE decltype([]() {})

template <typename T, typename DistinctT = T>
struct Type {
  using type = T;
  using disctict_type = DistinctT;
  using value_type = T;
  using pointer_type = T*;
  using reference_type = T&;
  using const_pointer_type = const T*;
  using const_reference_type = const T&;
};

template <typename T>
concept IsType = requires(T t) {
  typename T::type;
  typename T::disctict_type;
  typename T::value_type;
  typename T::pointer_type;
  typename T::reference_type;
  typename T::const_pointer_type;
  typename T::const_reference_type;
};

// NOTE: this class is incomplete and not fully implemented.
// To finish the object must be able to mimic all operations of underlying type.
template <IsType T>
struct Mimic {
  using cand_type = T;
  using type = T::type;
  using disctict_type = T::disctict_type;
  using value_type = T::value_type;
  using pointer_type = T::pointer_type;
  using reference_type = T::reference_type;
  using const_pointer_type = const T::const_pointer_type;
  using const_reference_type = const T::const_reference_type;
  typename type value;

  // Constructors
  constexpr Mimic(typename type value) : value(value) {}

  // Operators
  constexpr Mimic& operator+=(const Mimic& var) {
    this->value += var.value;
    return *this;
  }

  constexpr Mimic& operator+(const Mimic& var) {
    this->value += var.value;
    return *this;
  }

  // Special C& methods.
  std::string Stringify() {
    if constexpr (std::is_integral<type> || std::floating_point<type>) {
      return std::to_string(value);
    } else {
      return ToStr(value);
    }
  }
};

struct Money {};
Mimic<Type<int>> v1 = 100;
Mimic<Type<int, Money>> v4 = 100;  // Use a custom type.
Mimic<Type<int, UNIQUE_TYPE>> v2 =
    100;  // Unique type is diff every time - upon definition of the type.
Mimic<Type<int, UNIQUE_TYPE>> v3 = 100;  // diff type from above.

int mimic_example() {
  v2 = v2 + v2;
  v2 += v2;
  /*v2 = v1 + v2; not allowed!*/
  // v3 = v3 + v2;
  std::cout << v2.Stringify() << "Hello World!\n";
}