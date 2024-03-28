#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <locale>
#include <numeric>
#include <string>
#include <vector>

#ifndef IFTHENELSE_HPP
#define IFTHENELSE_HPP
// primary template: yield the second argument by default and rely on
// a partial specialization to yield the third argument
// if COND is false
template <bool COND, typename TrueType, typename FalseType>
struct IfThenElseT {
  using Type = TrueType;
};
// partial specialization: false yields third argument
template <typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType> {
  using Type = FalseType;
};
template <bool COND, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;
#endif  // IFTHENELSE_HPP

// yield T when using member Type:
template <typename T>
struct IdentityT {
  using Type = T;
};

/// <summary>
/// TypeList
/// </summary>
template <typename... Elements>
class Typelist {};

template <typename List>
class FrontT;

template <typename Head, typename... Tail>
class FrontT<Typelist<Head, Tail...>> {
 public:
  using Type = Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;

template <typename List>
class PopFrontT;
template <typename Head, typename... Tail>
class PopFrontT<Typelist<Head, Tail...>> {
 public:
  using Type = Typelist<Tail...>;
};
template <typename List>
using PopFront = typename PopFrontT<List>::Type;

template <typename List, typename NewElement>
class PushFrontT;
template <typename... Elements, typename NewElement>
class PushFrontT<Typelist<Elements...>, NewElement> {
 public:
  using Type = Typelist<NewElement, Elements...>;
};
template <typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

template <typename List, typename NewElement>
using SwapFront = PushFront<PopFront<List>, NewElement>;

// recursive case:
template <typename List, unsigned N>
class NthElementT : public NthElementT<PopFront<List>, N - 1> {};
// basis case:
template <typename List>
class NthElementT<List, 0> : public FrontT<List> {};
template <typename List, unsigned N>
using NthElement = typename NthElementT<List, N>::Type;

template <typename List>
class IsEmpty {
 public:
  static constexpr bool value = false;
};
template <>
class IsEmpty<Typelist<>> {
 public:
  static constexpr bool value = true;
};

template <typename List, bool Empty = IsEmpty<List>::value>
class LargestTypeT;
// recursive case:
template <typename List>
class LargestTypeT<List, false> {
 private:
  using Contender = Front<List>;
  using Best = typename LargestTypeT<PopFront<List>>::Type;

 public:
  using Type = IfThenElse<(sizeof(Contender) >= sizeof(Best)), Contender, Best>;
};
// basis case:
template <typename List>
class LargestTypeT<List, true> {
 public:
  using Type = char;
};
template <typename List>
using LargestType = typename LargestTypeT<List>::Type;

template <typename List, typename NewElement, bool = IsEmpty<List>::value>
class PushBackRecT;
// recursive case:
template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, false> {
  using Head = Front<List>;
  using Tail = PopFront<List>;
  using NewTail = typename PushBackRecT<Tail, NewElement>::Type;

 public:
  using Type = PushFront<Head, NewTail>;
};
// basis case:
template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, true> {
 public:
  using Type = PushFront<List, NewElement>;
};
// generic push-back operation:
template <typename List, typename NewElement>
class PushBackT : public PushBackRecT<List, NewElement> {};
template <typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

template <typename List, bool Empty = IsEmpty<List>::value>
class ReverseT;
template <typename List>
using Reverse = typename ReverseT<List>::Type;
// recursive case:
template <typename List>
class ReverseT<List, false>
    : public PushBackT<Reverse<PopFront<List>>, Front<List>> {};
// basis case:
template <typename List>
class ReverseT<List, true> {
 public:
  using Type = List;
};

template <typename List>
class PopBackT {
 public:
  using Type = Reverse<PopFront<Reverse<List>>>;
};
template <typename List>
using PopBack = typename PopBackT<List>::Type;

template <typename List, template <typename T> class MetaFun,
          bool Empty = IsEmpty<List>::value>

class TransformT;
// recursive case:
template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, false>
    : public PushFrontT<typename TransformT<PopFront<List>, MetaFun>::Type,
                        typename MetaFun<Front<List>>::Type> {};
// basis case:
template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, true> {
 public:
  using Type = List;
};

// pack expansion version:
template <typename... Elements, template <typename T> class MetaFun>
class TransformT<Typelist<Elements...>, MetaFun, false> {
 public:
  using Type = Typelist<typename MetaFun<Elements>::Type...>;
};

template <typename List, template <typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

template <typename List, template <typename X, typename Y> class F, typename I,
          bool = IsEmpty<List>::value>
class AccumulateT;
// recursive case:
template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, false>
    : public AccumulateT<PopFront<List>, F, typename F<I, Front<List>>::Type> {
};
// basis case:
template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, true> {
 public:
  using Type = I;
};
template <typename List, template <typename X, typename Y> class F, typename I>
using Accumulate = typename AccumulateT<List, F, I>::Type;

template <typename T, typename U>
class LargerTypeT : public IfThenElseT<sizeof(T) >= sizeof(U), T, U> {};
template <typename Typelist, bool = IsEmpty<Typelist>::value>
class LargestTypeAccT;
template <typename Typelist>
class LargestTypeAccT<Typelist, false>
    : public AccumulateT<PopFront<Typelist>, LargerTypeT, Front<Typelist>> {};
template <typename Typelist>
class LargestTypeAccT<Typelist, true> {};
template <typename Typelist>
using LargestTypeAcc = typename LargestTypeAccT<Typelist>::Type;

template <typename List, typename Element,
          template <typename T, typename U> class Compare,
          bool = IsEmpty<List>::value>
class InsertSortedT;
// recursive case:
template <typename List, typename Element,
          template <typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, false> {
  // compute the tail of the resulting list:
  using NewTail = typename IfThenElse<
      Compare<Element, Front<List>>::value, IdentityT<List>,
      InsertSortedT<PopFront<List>, Element, Compare>>::Type;
  // compute the head of the resulting list:
  using NewHead =
      IfThenElse<Compare<Element, Front<List>>::value, Element, Front<List>>;

 public:
  using Type = PushFront<NewTail, NewHead>;
};
// basis case:
template <typename List, typename Element,
          template <typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, true>
    : public PushFrontT<List, Element> {};
template <typename List, typename Element,
          template <typename T, typename U> class Compare>
using InsertSorted = typename InsertSortedT<List, Element, Compare>::Type;

template <typename List, template <typename T, typename U> class Compare,
          bool = IsEmpty<List>::value>
class InsertionSortT;
template <typename List, template <typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;
// recursive case (insert first element into sorted list):
template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, false>
    : public InsertSortedT<InsertionSort<PopFront<List>, Compare>, Front<List>,
                           Compare> {};
// basis case (an empty list is sorted):
template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true> {
 public:
  using Type = List;
};

template <typename T, typename U>
struct SmallerThanT {
  static constexpr bool value = sizeof(T) < sizeof(U);
};

template <typename T, T Value>
struct CTValue {
  static constexpr T value = Value;
};

template <typename T, T... Values>
using CTTypelist = Typelist<CTValue<T, Values>...>;

template <typename T, T... Values>
struct Valuelist {};
template <typename T, T... Values>
struct IsEmpty<Valuelist<T, Values...>> {
  static constexpr bool value = sizeof...(Values) == 0;
};
template <typename T, T Head, T... Tail>
struct FrontT<Valuelist<T, Head, Tail...>> {
  using Type = CTValue<T, Head>;
  static constexpr T value = Head;
};
template <typename T, T Head, T... Tail>
struct PopFrontT<Valuelist<T, Head, Tail...>> {
  using Type = Valuelist<T, Tail...>;
};
template <typename T, T... Values, T New>
struct PushFrontT<Valuelist<T, Values...>, CTValue<T, New>> {
  using Type = Valuelist<T, New, Values...>;
};
template <typename T, T... Values, T New>
struct PushBackT<Valuelist<T, Values...>, CTValue<T, New>> {
  using Type = Valuelist<T, Values..., New>;
};

template <typename T, typename U>
struct GreaterThanT;
template <typename T, T First, T Second>
struct GreaterThanT<CTValue<T, First>, CTValue<T, Second>> {
  static constexpr bool value = First > Second;
};

template <typename T>
struct AddConstT {
  using Type = T const;
};
template <typename T>
using AddConst = typename AddConstT<T>::Type;

// Note that you can provide the ability to initialize CTValue by using the
// literal operator, e.g., auto a = 42_c; // initializes a as CTValue<int,42>
// See Section 25.6 on page 599 for details.

void valuelisttest() {
  using Integers = Valuelist<char, ' '>;
  using TestTypelist =
      Typelist<CTValue<char, 'a'>, CTValue<char, '1'>, CTValue<char, '3'>>;
  using SortedIntegers = InsertionSort<Integers, GreaterThanT>;
}
