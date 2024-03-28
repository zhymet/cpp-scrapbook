#include <compare>

// The usual attempt to use a string literal as a template argument is to write
// something like this:
template <class T, T p>
class X {
  /* ... */
};

// error: string literal as template-argument
// X<const char*, "Studebaker"> x;

// External-Linakge string literal is okay.
const char p[] = "Vivisectionist";
X<const char*, p> y;  // OK

// C++17 solution.
template <unsigned N>
struct FixedString {
  char buf[N + 1]{};
  constexpr FixedString(char const* s) {
    for (unsigned i = 0; i != N; ++i) buf[i] = s[i];
  }
  constexpr operator char const*() const { return buf; }

  constexpr auto operator<=>(const FixedString&) const = default;
};
template <unsigned N>
FixedString(char const (&)[N]) -> FixedString<N - 1>;

template <FixedString Name>
class Foo {
 public:
  constexpr const char* hellocstr() const { return Name; }
  constexpr const decltype(Name)& hello() const { return Name; }
};

constexpr auto mystringobj = Foo<"Hello!">{};
constexpr const char* mystring = mystringobj.hello();
static_assert(mystringobj.hello() == FixedString("Hello!"));

int main() {}