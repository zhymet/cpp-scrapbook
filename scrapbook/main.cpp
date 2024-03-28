#include <algorithm>
#include <array>
#include <tuple>
#include <type_traits>
#include <vector>

// Type trait to check if a type is a container.
// A minimal container is a type with a cbegin and cend method.
template <typename T>
auto is_minimal_container(int)
    -> decltype(cbegin(std::declval<T>()) == cend(std::declval<T>()),
                std::true_type{});

template <typename T>
std::false_type is_minimal_container(...);

template <typename T>
constexpr bool is_minimal_container_v =
    decltype(is_minimal_container<T>(0))::value;

namespace any_of_element_detail {
template <typename... Args>
struct compile_time_any_of_impl {
  std::tuple<Args...> values;

  constexpr compile_time_any_of_impl(Args&&... values)
      : values(std::forward<Args>(values)...) {}

  template <typename T>
  [[nodiscard]] friend constexpr bool operator==(
      T lhs, compile_time_any_of_impl const& rhs) noexcept {
    bool found = false;
    return std::apply([&](auto&&... vals) { return ((lhs == vals) || ...); },
                      rhs.values);
  }
};

template <typename Container>
struct runtime_any_of_impl {
  Container const& values;

  constexpr runtime_any_of_impl(Container const& values) : values(values) {}

  template <typename T>
  [[nodiscard]] friend constexpr bool operator==(
      T&& lhs, runtime_any_of_impl&& rhs) noexcept {
    return std::any_of(cbegin(rhs.values), cend(rhs.values),
                       [&](auto val) { return lhs == val; });
  }
};
}  // namespace any_of_element_detail

// any_of_element : compile time meta method 
// which returns a result which is equal to all elements within a
// container. A compile time any_of that works like so:
//  any_of_element(container_or_element_pack) == the_value;
// eg. any_of_element(1, 2, 3) == 2
//     any_of_element(std::vector{1, 2, 3}) != 5
template <typename... Args>
[[nodiscard]] constexpr auto any_of_element(Args&&... values) {
  using namespace any_of_element_detail;

  if constexpr (sizeof...(Args) == 1 &&
                is_minimal_container_v<
                    std::tuple_element_t<0, std::tuple<Args...>>>)
    return runtime_any_of_impl(std::forward<Args>(values)...);
  else
    return compile_time_any_of_impl(std::forward<Args>(values)...);
}

static_assert(any_of_element(1, 2, 3) == 2);
static_assert(any_of_element(1, 2, 3) != 5);
static_assert(any_of_element(std::vector{1, 2, 3}) == 2);
static_assert(any_of_element(std::vector{1, 2, 3}) != 5);
static_assert(any_of_element(std::array{1, 2, 3}) == 2);
static_assert(any_of_element(std::array{1, 2, 3}) != 5);

int main() {}