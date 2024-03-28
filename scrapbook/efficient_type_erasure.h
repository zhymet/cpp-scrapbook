#pragma once
#include <any>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <variant>

// Utilities for cleaner code.

using namespace std;
template <typename Sig>
struct signature;
template <typename Ret, typename... Args>
struct signature<Ret(Args...)> {
  using type = tuple<Args...>;
};

template <typename Ret, typename Obj, typename... Args>
struct signature<Ret (Obj::*)(Args...)> {
  using type = tuple<Args...>;
};
template <typename Ret, typename Obj, typename... Args>
struct signature<Ret (Obj::*)(Args...) const> {
  using type = tuple<Args...>;
};
template <typename Fun>
concept is_fun = is_function_v<Fun>;

template <typename Fun>
concept is_mem_fun = is_member_function_pointer_v<decay_t<Fun>>;

template <typename Fun>
concept is_functor = is_class_v<decay_t<Fun>> &&
                     requires(Fun&& t) { &decay_t<Fun>::operator(); };

template <is_functor T>
auto arguments(T&& t) -> signature<decltype(&decay_t<T>::operator())>::type;

template <is_functor T>
auto arguments(const T& t)
    -> signature<decltype(&decay_t<T>::operator())>::type;

// template<is_fun T>
// auto arguments(T&& t)->signature<T>::type;

template <is_fun T>
auto arguments(const T& t) -> signature<T>::type;

template <is_mem_fun T>
auto arguments(T&& t) -> signature<decay_t<T>>::type;

template <is_mem_fun T>
auto arguments(const T& t) -> signature<decay_t<T>>::type;

#define CASE_T template <typename T>
#define CASE_Z template <>

using meta_int_t = int;
using meta_float_t = double;
using meta_bit_t = bool;
using meta_byte_t = char;
using meta_string_t = std::string;
using meta_literal_variant_t =
    std::variant<meta_int_t, meta_float_t, meta_bit_t, meta_byte_t,
                 meta_string_t>;

template <typename T>
concept MetaLiteralValueType = requires(T t) {
  std::same_as<T, meta_int_t> or std::same_as<T, meta_float_t> or
      std::same_as<T, meta_bit_t> or std::same_as<T, meta_byte_t> or
      std::same_as<T, meta_string_t>;
};

////////////////////////////////////////////////////////////////////////////////////////////////
/// Boilerplate/Black Magic
////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>  // <@gmethod: cp_string>
std::string cp_string(const T& t) = delete;

template <typename T>  // <@gmethod: add_int>
void add_literal(T& t, meta_literal_variant_t i) = delete;

// CAUTION: Workaround for clang and msvc.
// The following forward declarations of explicit specialization of
// `serialize()` and `draw()` prevent Clang from complaining about redefintion
// errors.
struct Base;  // Forward declaration, Must be defined after the deleted template
              // methods.

template <>  // <@gmethod: cp_string>
std::string cp_string(const Base& obj);

template <>  // <@gmethod: add_int>
void add_literal(Base& obj, meta_literal_variant_t i);

struct Base {
  // NOTE: Definition of the explicit specialization has to appear separately
  // later outside of class `Base`, otherwise it results in error such as:
  //
  // ```
  // error: defining explicit specialization 'serialize<Base>' in friend
  // declaration
  // ```
  //
  // Reference: https://en.cppreference.com/w/cpp/language/friend
  friend std::string cp_string<>(const Base& shape);
  friend void add_literal<>(Base& shape, meta_literal_variant_t i);
  friend std::ostream& operator<<(std::ostream& os, const Base& shape) {
    return os << *shape.impl_;
  }

  // The External Polymorphism Design Pattern
  class BaseInterface {
   public:
    virtual ~BaseInterface() {}
    virtual void print(std::ostream& os) const = 0;
    virtual void add_literal(meta_literal_variant_t i) = 0;
    virtual std::string cp_string() const = 0;

    // The Prototype Design Pattern
    virtual std::unique_ptr<BaseInterface> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os,
                                    const BaseInterface& shape) {
      shape.print(os);
      return os;
    }
  };

  template <typename T>
  class BaseModel : public BaseInterface {
    T object_;

   public:
    BaseModel(const T& value) : object_{value} {}

    //    // CAUTION: The using declaration tells the compiler to look up the
    //    free
    //    // serialize() function rather than the member function.
    //    //
    //    // Reference: https://stackoverflow.com/a/32091297/4475887

    std::string cp_string() const override {
      using ::cp_string;

      return cp_string(object_);
    }

    void add_literal(meta_literal_variant_t i) override {
      using ::add_literal;

      add_literal(object_, i);
    }

    void print(std::ostream& os) const override { os << object_; }

    // The Prototype Design Pattern
    std::unique_ptr<BaseInterface> clone() const override {
      return std::make_unique<BaseModel>(*this);
    }
  };

  // The Bridge Design Pattern
  std::unique_ptr<BaseInterface> impl_;

 public:
  // A constructor template to create a bridge.
  template <typename T>
  Base(const T& x) : impl_{new BaseModel<T>(x)} {}

  Base(const Base& s) : impl_{s.impl_->clone()} {}

  Base(Base&& s) noexcept : impl_{std::move(s.impl_)} {}

  Base& operator=(const Base& s) {
    impl_ = s.impl_->clone();
    return *this;
  }

  Base& operator=(Base&& s) noexcept {
    impl_ = std::move(s.impl_);
    return *this;
  }
};

template <>
std::string cp_string(const Base& shape) {
  return shape.impl_->cp_string();
}

template <>
void add_literal(Base& shape, meta_literal_variant_t i) {
  shape.impl_->add_literal(i);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Object Definitions
////////////////////////////////////////////////////////////////////////////////////////////////

struct Integer {
  int value;
};

struct Circle {
  double radius;
};

struct MetaLiteral {
  meta_literal_variant_t value;

  MetaLiteral(const MetaLiteralValueType auto& value) : value(value) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Object methods.
// All objects must define all methods, even if they are not used.
// Template metaprogramming may be used to reduce code duplication.
////////////////////////////////////////////////////////////////////////////////////////////////

// MetaLiteral
std::ostream& operator<<(std::ostream& os, const MetaLiteral& x) {
  std::visit([&os](const auto& value) { os << value; }, x.value);
  return os;
}

std::string cp_string(const MetaLiteral& x) {
  return std::visit(
      []<MetaLiteralValueType T>(const T& value) -> std::string {
        if constexpr (std::same_as<T, meta_string_t>) {
          return value;
        } else {
          return std::to_string(value);
        }
      },
      x.value);
}

void add_literal(MetaLiteral& obj, meta_literal_variant_t lit_value) {
  // First visit the passed literal.
  std::visit(
      [&lit_value]<MetaLiteralValueType T>(T& value) {
        // If we are adding a string. Then object must also be a string.
        if constexpr (std::same_as<T, meta_string_t>) {
          if (!std::holds_alternative<meta_string_t>(lit_value)) {
            throw std::runtime_error("Cannot add string to non-string");
          } else {
            // Perform string concatenation.
            value += std::get<meta_string_t>(lit_value);
          }
        } else {
          // If we are adding a non-string. Then object must also be a
          // non-string.
          if (std::holds_alternative<meta_string_t>(lit_value)) {
            throw std::runtime_error("Cannot add non-string to string");
          } else {
            // Visit the object and add the literal value.
            std::visit(
                [&value]<MetaLiteralValueType U>(const U& rhs_value) {
                  // Account for string here- only for the compiler.(Compile
                  // time check anyways).
                  if constexpr (std::same_as<U, meta_string_t>) {
                    throw std::runtime_error("Cannot add non-string to string");
                  } else {
                    value += rhs_value;
                  }
                },
                lit_value);
          }
        }
      },
      obj.value);
}

//// Circle
std::ostream& operator<<(std::ostream& os, const Circle& x) {
  os << "Circle{ radius: " << x.radius << " }";
  return os;
}

std::string cp_string(const Circle& x) { return std::to_string(x.radius); }

void add_literal(Circle& x, meta_literal_variant_t lit_value) {
  // Visit lit_value
  std::visit(
      [&x]<MetaLiteralValueType U>(const U& lit_value) {
        // Account for string here- only for the compiler.(Compile
        // time check anyways).
        if constexpr (std::same_as<U, meta_string_t>) {
          throw std::runtime_error("Cannot add string to caobj::Circle.");
        } else {
          x.radius += lit_value;
        }
      },
      lit_value);
}

template <typename T>
void add_literal(T& x, meta_literal_variant_t lit_value)
  requires(!std::is_same_v<T, MetaLiteral> && !std::is_same_v<T, Circle>)
{
  throw std::runtime_error("Cannot add literal to unknown type");
}
template <typename T>
  requires(!std::is_same_v<T, MetaLiteral> && !std::is_same_v<T, Circle>)
std::string cp_string(const T& x) {
  return "";
}
////////////////////////////////////////////////////////////////////////////////////////////////
// A method is a combination of basic operations. Arguments.With a result.
template <typename OperationT, typename RT, typename... Args>
struct meta_method {
  RT return_value;
  std::tuple<Args...> args;
  std::function<RT(Args...)> operation;

  meta_method(OperationT&& operation) : operation(operation){};

  void perform() { return_value = std::apply(operation, args); }
  void set_args(Args... args) { this->args = std::make_tuple(args...); }
  auto get_result() { return return_value; }
};

template <typename OpT>
constexpr auto make_meta_method(OpT&& operation) {
  using args_t = decltype(arguments(operation));

  auto operation_result =
      [&operation]<typename... Args>(Args&&... args) constexpr {
        return operation(std::forward<Args>(args)...);
      };

  auto apply_arg_tuple = [&operation_result](args_t args) constexpr {
    return std::apply(operation_result, args);
  };

  using return_t = std::invoke_result_t<decltype(apply_arg_tuple), args_t>;

  auto meta_method_value = std::apply(
      [&operation](auto&&... args) {
        return meta_method<OpT, return_t, std::decay_t<decltype(args)>...>{
            std::forward<OpT>(operation)};
      },
      args_t{});

  return meta_method_value;
};

class runtime {
  struct VarInstance {
    std::string name;
    meta_literal_variant_t value;

    VarInstance() = default;
    VarInstance(std::string name) : name(name) {}
    VarInstance(std::string name, meta_literal_variant_t value)
        : name(name), value(value) {}
  };

 public:
  enum OpCode {
    MAKE_GVAR,   // make global variable
    SET_GVAR,    // set global variable
    DEL_GVAR,    // delete global variable
    MAKE_VALUE,  // make anonymous variable
    DEL_VALUE,   // delete anonymous variable
    ADD,         // addition operation
  };

  struct OpCodeLine {
    OpCode code;
    std::vector<meta_literal_variant_t> args;
  };

 private:
  std::vector<VarInstance> global_stack;
  std::vector<VarInstance> working_stack;

  void execute(OpCodeLine line) {
    std::string string_arg_1;
    std::string string_arg_2;
    std::vector<VarInstance>::iterator target_var;
    std::vector<VarInstance>::iterator target_rhs;

    switch (line.code) {
      case MAKE_GVAR:
        // Create a new variable name in the global scope.
        // Check that the argument is a string.
        if (!std::holds_alternative<meta_string_t>(line.args[0])) {
          throw std::runtime_error("Expected string for variable name");
        }
        global_stack.push_back(
            VarInstance{std::get<meta_string_t>(line.args[0])});
        break;
      case SET_GVAR:
        // Set the value of a global variable.
        // There should be 2 arguments.
        if (line.args.size() != 2) {
          throw std::runtime_error("Expected 2 arguments for SET_GVAR");
        }

        // Check that the 1st argument is a string.
        if (!std::holds_alternative<meta_string_t>(line.args[0])) {
          throw std::runtime_error("Expected string for variable name");
        }

        // Check that the variable exists.
        string_arg_1 = std::get<meta_string_t>(line.args[0]);
        target_var = std::find_if(global_stack.begin(), global_stack.end(),
                                  [&string_arg_1](const VarInstance& v) {
                                    return v.name == string_arg_1;
                                  });

        if (target_var == global_stack.end()) {
          throw std::runtime_error("Variable not found");
        }
        target_var->value = line.args[1];
        break;
      case DEL_GVAR:
        // Delete a global variable.
        // There should be 1 argument.
        if (line.args.size() != 1) {
          throw std::runtime_error("Expected 1 argument for DEL_GVAR");
        }

        // Check that the 1st argument is a string.
        if (!std::holds_alternative<meta_string_t>(line.args[0])) {
          throw std::runtime_error("Expected string for variable name");
        }

        // Check that the variable exists.
        string_arg_1 = std::get<meta_string_t>(line.args[0]);
        target_var = std::find_if(global_stack.begin(), global_stack.end(),
                                  [&string_arg_1](const VarInstance& v) {
                                    return v.name == string_arg_1;
                                  });

        if (target_var == global_stack.end()) {
          throw std::runtime_error("Variable not found");
        }
        global_stack.erase(target_var);
        break;
    }
  }

 public:
  void run(std::vector<OpCodeLine> program) {
    for (auto& code : program) {
      execute(code);
    }
  }
};

// Sample program
/*
*  1 + 1;
    #var a;

    a = 10;

    #del a;

    /////////////////////////////
    OpCode Output:

    1 MAKE_GVAR, "a"
    2 SET_GVAR, "a", 10
    3 DEL_GVAR, "a"

*/

auto test_runtime() {
  using rt = runtime;
  rt r;

  r.run({{rt::MAKE_GVAR, {"a"}},
         {rt::SET_GVAR, {"a", 10}},
         {rt::DEL_GVAR, {"a"}}});
}

int main() {
  // test_runtime();
  std::unique_ptr<Base> shape = std::make_unique<Base>(Circle{5.0});
  std::cout << *shape << std::endl;
  std::cout << cp_string(*shape) << std::endl;
  add_literal(*shape, 1);

  std::vector<Base> vmstack;

  auto foomethod = make_meta_method([](int i) { return 42; });
  foomethod.set_args(1);
  foomethod.perform();
  vmstack.push_back(Circle{5.0});
  vmstack.push_back(Integer{100});
  vmstack.push_back(MetaLiteral{3.14});
  vmstack.push_back(MetaLiteral{std::string("Hello")});
  vmstack.push_back(foomethod);

  for (auto index = 0; auto& object : vmstack) {
    std::cout << object << std::endl;
    cp_string(object);

    try {
      add_literal(object, 1);
      std::cout << "Added literal\n";
      std::cout << object << std::endl;
    } catch (std::runtime_error& e) {
      std::cout << "Failed to add literal 1\n";
      std::cout << e.what() << std::endl;
    }

    try {
      add_literal(object, meta_string_t(" World"));
      std::cout << "Added literal\n";
      std::cout << object << std::endl;
    } catch (std::runtime_error& e) {
      std::cout << "Failed to add literal \" World\"\n";
    }

    std::cout << "[ITER:" << index << "]" << std::endl;
    index++;
  }

  return 0;
}