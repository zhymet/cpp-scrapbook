#pragma once
#include <any>
#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <vector>

template <typename T>
concept Addable = requires(T Value) { Value + Value; };

template <typename T>
concept Subtractable = requires(T Value) { Value - Value; };

template <typename T>
concept Multiplicable = requires(T Value) { Value* Value; };

template <typename T>
concept Dividable = requires(T Value) { Value / Value; };

template <typename T>
concept Modulable = requires(T Value) { Value % Value; };

template <typename T>
concept Stringable = requires(T Value) { std::to_string(Value); };

class Foo {
  int bar = 1;
  int baz = 2;
  friend constexpr auto operator+(Foo lhs, Foo rhs);
  friend constexpr auto operator+(Foo lhs, int rhs);
  friend constexpr auto operator+(int lhs, Foo rhs);

 public:
  auto barbaz() { return bar + baz; }
};

constexpr auto operator+(Foo lhs, Foo rhs) {
  Foo result;
  result.bar = lhs.bar + rhs.bar;
  result.baz = lhs.baz + rhs.baz;
  return result;
}
constexpr auto operator+(Foo lhs, int rhs) {
  Foo result;
  result.bar = lhs.bar + rhs;
  result.baz = lhs.baz + rhs;
  return result;
}

constexpr auto operator+(int lhs, Foo rhs) {
  Foo result;
  result.bar = rhs.bar + lhs;
  result.baz = rhs.baz + lhs;
  return result;
}

template <typename T>
static inline auto operator+(T lhs, std::string rhs)
  requires((not std::is_same_v<T, std::string>) && Addable<T> && Stringable<T>)
{
  // Todo: custom to-string method
  return std::to_string(lhs) + rhs;
}

template <typename T>
static inline auto operator+(std::string lhs, T rhs)
  requires((not std::is_same_v<T, std::string>) && Addable<T> && Stringable<T>)
{
  // Todo: custom to-string method
  return lhs + std::to_string(rhs);
}

Addable auto constexpr static inline add(Addable auto Value,
                                         Addable auto OtherValue) {
  return Value + OtherValue;
};

Subtractable auto constexpr static inline subtract(
    Subtractable auto Value, Subtractable auto OtherValue) {
  return Value - OtherValue;
};

Multiplicable auto constexpr static inline multiply(
    Multiplicable auto Value, Multiplicable auto OtherValue) {
  return Value * OtherValue;
};

Dividable auto constexpr static inline divide(Dividable auto Value,
                                              Dividable auto OtherValue) {
  return Value / OtherValue;
};

Modulable auto constexpr static inline modulate(Modulable auto Value,
                                                Modulable auto OtherValue) {
  return Value % OtherValue;
};

 static_assert(add(5, 6) == 11);
 static_assert(add(5.0, 6.0) == 11.0);
 static_assert(add(std::string("Hello"), std::string(" World")) ==
 std::string("Hello World"));
 static_assert(std::is_same_v<decltype(add(int(5), 10.f)),float>);
 static_assert(add(5, 10.f) == 15.f);


//  The actual function expanding the tuple:
template <typename CallableT, typename... ValTs>
auto apply_callable_impl(CallableT&& callable, ValTs... v) {
  return callable(v...);
}

// The interface to call. Sadly, it needs to dispatch to another function
// to deduce the sequence of indices created from std::make_index_sequence<N>
template <typename CallableT>
auto apply_callable(CallableT&& callable, auto&&... args) {
  return apply_callable_impl(std::forward<CallableT>(callable),
                             std::forward<decltype(args)>(args)...);
}

template <class CallableT, class Tuple, std::size_t... Is>
auto apply_callable_to_tuple_impl(CallableT&& callable, const Tuple& tup,
                                  std::index_sequence<Is...>) {
  return apply_callable(callable, std::get<Is>(tup)...);
}

template <class CallableT, class... Args>
auto apply_callable_to_tuple(CallableT&& callable,
                             const std::tuple<Args...>& t) {
  return apply_callable_to_tuple_impl(
      std::forward<CallableT>(callable),
      std::forward<const std::tuple<Args...>&>(t),
      std::index_sequence_for<Args...>{});
}

int test() {
  std::vector<std::any> opstack;
  opstack.push_back(5);
  opstack.push_back(5.f);
  opstack.push_back(std::string("hello"));

  auto value_tuple = std::make_tuple(5, 5.f, std::string("hello"));

  auto accumulate = [](auto... args) { return (args + ...); };
  auto add_tuple_elements = apply_callable_to_tuple(accumulate, value_tuple);

  std::cout << add_tuple_elements << std::endl;
};