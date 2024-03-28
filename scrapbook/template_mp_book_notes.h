#pragma once
#include <string>
//	Type Deduction for Default Arguments
//	Note also that type deduction does not work for default call arguments.
//	For example :
// template<typename T>
// void f(T = "");
//
// f(1); // OK: deduced T to be int, so that it calls f<int>(1)
// f(); // ERROR: cannot deduce T
// To support this case, you also have to declare a default argument for the
// template parameter, which will be discussed in Section 1.4 on page 13:

// template<typename T = std::string>
// constexpr bool foo(T = "") {
//	return true;
// };
// static_assert(foo());

// It may appear desirable to be able to pass parameters of different types to
// the max() template, but, as this example shows, it raises a problem.If you
// use one of the parameter types as return type, the argument for the other
// parameter might get converted to this type, regardless of the caller’s
// intention. Thus, the return type depends on the call argument order.The
// maximum of 66.66 and 42 will be the double 66.66, while the maximum of 42
// and 66.66 will be the int 66. C++ provides different ways to deal with this
// problem: • Introduce a third template parameter for the return type. • Let
// the compiler find out the return type. • Declare the return type to be the
// “common type” of the two parameter types. All these options are discussed
// next

// We also mentioned, however, that we can specify the types to use for the
// template parameters explicitly : template<typename T> T max(T a, T b);
//...
//::max<double>(4, 7.2); // instantiate T as double
// In cases when there is no connection between template and call parameters and
// when template parameters cannot be determined, you must specify the template
// argument explicitly with the call.For example, you can introduce a third
// template argument type to define the return type of a function template:
// template<typename T1, typename T2, typename RT>
// RT max(T1 a, T2 b);
// However, template argument deduction does not take return types into account,
// 7 and RT does not appear in the types of the function call
// parameters.Therefore, RT cannot be deduced.8 As a consequence, you have to
// specify the template argument list explicitly.For example : template<typename
// T1, typename T2, typename RT> RT max(T1 a, T2 b);
//...
//::max<int, double, double>(4, 7.2); // OK, but tedious
// So far, we have looked at cases in which either all or none of the function
// template arguments were mentioned explicitly.Another approach is to specify
// only the first arguments explicitly and to allow the deduction process to
// derive the rest.In general, you must specify all the argument types up to the
// last argument type that cannot be determined implicitly.Thus, if you change
// the order of the template parameters in our example, the caller needs to
// specify only the return type: template<typename RT, typename T1, typename T2>
// RT max(T1 a, T2 b);
//...
//::max<double>(4, 7.2) // OK: return type is double, T1 and T2 are deduced
// In this example, the call to max<double> explicitly sets RT to double, but
// the parameters T1 and T2 are deduced to be int and double from the arguments.
// Note that these modified versions of max() don’t lead to significant
// advantages.

// If a return type depends on template parameters, the simplest and best
// approach to deduce the return type is to let the compiler find out.Since
// C++14, this is possible by simply not declaring any return type(you still
// have to declare the return type to be auto) : 	basics / maxauto.hpp ? ?
//	template<typename T1, typename T2>
// auto max(T1 a, T2 b)
//{
//	return b < a ? a : b;
// }
//? ?
// In fact, the use of auto for the return type without a corresponding trailing
// return type(which would 	be introduced with a->at the end) indicates that
// the
// actual return type must be deduced from the 	return statements in the
// function body.Of course, deducing the return type from the function body
// has to be possible.Therefore, the code must be available and multiple return
// statements have to 	match. 	Before C++14, it is only possible to let the
// compiler determine the return type by more or less 	making the
// implementation of the function part of its declaration.In C++11 we can
// benefit from the 	fact that the trailing return type syntax allows us to
// use the call parameters.That is, we can declare 	that the return type is
// derived from what operator ? : yields : 	basics
/// maxdecltype.hpp ? ? 	template<typename T1, typename T2> auto max(T1 a, T2
/// b)
// -> decltype(b < a ? a : b)
//{
//	return b < a ? a : b;
// }
//? ?
// Here, the resulting type is determined by the rules for operator ? : , which
// are fairly elaborate but generally produce an intuitively expected
// result(e.g., if a and b have different arithmetic types, a 	common
// arithmetic
// type is found for the result). 	Note that 	template<typename T1,
// typename T2>
// auto max(T1 a, T2 b) -> decltype(b < a ? a : b);
// ensurehelveticaisembedded_()
// 12 Chapter 1: Function Templates
// is a declaration, so that the compiler uses the rules of operator ? : called
// for parameters a and b to find out the return type of max() at compile
// time.The implementation does not necessarily have to match.In fact, using
// true as the condition for operator ? : in the declaration is enough :
// template<typename T1, typename T2>
// auto max(T1 a, T2 b) -> decltype(true ? a : b);
// However, in any case this definition has a significant drawback : It might
// happen that the return type is a reference type, because under some
// conditions T might be a reference.For this reason you should return the type
// decayed from T, which looks as follows : basics / maxdecltypedecay.hpp ? ?
// #include <type_traits>
// template<typename T1, typename T2>
// auto return_type_deduction_example_max(T1 a, T2 b) -> typename
// std::decay<decltype(true ? a : b)>::type
//{
//	return b < a ? a : b;
// }
//? ?
// Here, the type trait std::decay<> is used, which returns the resulting type
// in a member type. It is defined by the standard library in <type_trait>(see
// Section D.5 on page 732).Because the member type is a type, you have to
// qualify the expression with typename to access it(see Section 5.1 	on page
// 67). 	Note that an initialization of type auto always decays.This also
// applies to return values when 	the return type is just auto. auto as a
// return type
// behaves just as in the following code, where a is 	declared by the decayed
// type of i, int: int i = 42; int const& ir = i; // ir refers to i auto a = ir;
// // a
// is declared as new object of type int

// 1.3.3 Return Type as Common Type
// Since C++11, the C++ standard library provides a means to specify choosing
// “the more general type.” std::common_type<>::type yields the “common type” of
// two(or more) different types passed as template arguments.For example :
// basics / maxcommon.hpp ? ?
// #include <type_traits>
// template<typename T1, typename T2>
// std::common_type_t<T1, T2> max(T1 a, T2 b)
//{
//	return b < a ? a : b;
// }
//? ?
// ensurehelveticaisembedded_()
// 1.4 Default Template Arguments 13
// Again, std::common_type is a type trait, defined in <type_traits>, which
// yields a structure having a type member for the resulting type.Thus, its core
// usage is as follows : typename std::common_type<T1, T2>::type // since C++11
// However, since C++14 you can simplify the usage of traits like this by
// appending _t to the trait name and skipping typename and ::type(see
// Section 2.8 on page 40 for details), so that the return type definition
// simply becomes : std::common_type_t<T1, T2> // equivalent since C++14 The way
// std::common_type<> is implemented uses some tricky template programming,
// which is discussed in Section 26.5.2 on page 622. Internally, it chooses the
// resulting type according to the language rules of operator ? : or
// specializations for specific types.Thus, both::max(4, 7.2) and
//::max(7.2, 4) yield the same value 7.2 of type double.Note that
//: std::common_type<> also
// decays.See Section D.5 on page 732 for details

// 1.4 Default Template Arguments
// You can also define default values for template parameters.These values are
// called default template arguments and can be used with any kind of template.9
// They may even refer to previous template parameters. For example, if you want
// to combine the approaches to define the return type with the ability to have
// multiple parameter types(as discussed in the section before), you can
// introduce a template parameter RT for the return type with the common type of
// the two arguments as default.Again, we have multiple options :
// 1. We can use operator ? : directly.However, because we have to apply
// operator ? : before the call parameters a and b are declared, we can only use
// their types : basics / maxdefault1.hpp ? ? #include <type_traits>
// template<typename T1, typename T2,
//	typename RT = std::decay_t<decltype(true ? T1() : T2())>>
//	RT max(T1 a, T2 b)
//{
//	return b < a ? a : b;
// }
//? ?
// Note again the usage of std::decay_t<> to ensure that no reference can be
// returned.10 9 Prior to C++11, default template arguments were only permitted
// in class templates, due to a historical glitch in the development of function
// templates. 10 Again, in C++11 you had to use typename std::decay<...>::type
// instead of std::decay_t<...>(see 	Section 2.8 on page 40).
//	ensurehelveticaisembedded_()
//	14 Chapter 1 : Function Templates
//	Note also that this implementation requires that we are able to call
// default constructors for 	the passed types.There is another solution,
// using std::declval, which, however, makes the 	declaration even more
// complicated.See Section 11.2.3 on page 166 for an example.
//	2. We can also use the std::common_type<> type trait to specify the
// default value for the return 	type : 	basics / maxdefault3.hpp ? ?
// #include
// <type_traits> 	template<typename T1, typename T2, 	typename RT =
// std::common_type_t<T1, T2>> 	RT max(T1 a, T2 b)
//{
//	return b < a ? a : b;
// }
//? ?
// Again, note that std::common_type<> decays so that the return value can’t
// become a reference. In all cases, as a caller, you can now use the default
// value for the return type: auto a = ::max(4, 7.2); or specify the return type
// after all other argument types explicitly : auto b = ::max<double, int, long
// double>(7.2, 4); However, again we have the problem that we have to specify
// three types to be able to specify the return type only.Instead, we would need
// the ability to have the return type as the first template parameter, while
// still being able to deduce it from the argument types.In principle, it is
// possible to have default arguments for leading function template parameters
// even if parameters without default arguments follow : template<typename RT =
// long, typename T1, typename T2> RT max(T1 a, T2 b)
//{
//	return b < a ? a : b;
// }
// With this definition, for example, you can call :
// int i;
// long l;
//...
// max(i, l); // returns long (default argument of template parameter for return
// type) max<int>(4, 42); // returns int as explicitly requested However, this
// approach only makes sense, if there is a “natural” default for a template
// parameter. Here, we need the default argument for the template parameter to
// depend from previous template parameters.In principle, this is possible as we
// discuss in Section 26.5.1 on page 621, but the technique depends on type
// traits and complicates the definition. For all these reasons, the best and
// easiest solution is to let the compiler deduce the return type as proposed in
// Section 1.3.2 on page 11