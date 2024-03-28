#pragma once
#ifndef GTL_HEADGUARD_requires_std_hpp
#define GTL_HEADGUARD_requires_std_hpp

#include "shortcuts.hpp" // Shorthand notations for GTL library

#include <concepts>
#include <ranges>
#include <utility>
#include <type_traits>
#include <limits>

namespace gtl::req {
    /* Core Language Concepts */

    __CASET concept CopyConstructible_ = std::is_copy_constructible_v<T>;

    __CASET concept CopyAssignable_ = std::is_copy_assignable_v<T>;

    __CASET concept Copyable_ = CopyConstructible_<T> && CopyAssignable_<T>;

    __CASET concept NonCopyable_ = (not CopyConstructible_<T>) && (not CopyAssignable_<T>);

    __CASET concept MoveAssignable_ = std::is_move_assignable_v<T>;

    __CASET concept MoveConstructible_ = std::move_constructible<T>;  // note: Types without a move constructor, but with a copy constructor that accepts const T& arguments,
                                                                      //       satisfy std::is_move_constructible.

    __CASET concept Movable_ = MoveConstructible_<T> && MoveAssignable_<T>;

    __CASET concept NonMovable_ = (not MoveConstructible_<T>) && (not MoveAssignable_<T>);

    __CASET concept MoveOnly_ = Movable_<T> && (not Copyable_<T>);

    __CASET concept NoThrowMoveConstructible_ = std::is_nothrow_move_constructible_v<T>;

    __CASET concept NoThrowMoveAssignable_ = std::is_nothrow_move_assignable_v<T>;

    __CASET concept MemberObjectPointer_ = std::is_member_object_pointer_v<T>;

    __CASET concept MemberFunctionPointer_ = std::is_member_function_pointer_v<T>;

    __CASET concept Swappable_ = std::swappable<T>;

    __CASET concept Singular_ = NonCopyable_<T> && NonMovable_<T> && (not Swappable_<T>);    /// Cannot be moved copied or swapped

    __CASE<typename T, typename U> concept SameAs_ = std::same_as<T, U>; /// Specifies that a type is the same as another type.

    __CASE<typename T, typename U> concept DerivedFrom_ = std::derived_from<T, U>; 

    __CASE<typename T, typename U> concept ConvertibleTo_ = std::convertible_to<T, U>; 

    __CASE<typename T, typename U> concept CommonRefWith_ = std::common_reference_with<T, U>; 

    __CASE<typename T, typename U> concept CommonWith_ = std::common_with<T, U>; 

    __CASET concept Integral_ = std::integral<T>;

    __CASET concept SignedIntegral_ = std::signed_integral<T>; 

    __CASET concept UnsignedIntegral_ = std::unsigned_integral<T>; 

    __CASET concept FloatingPoint_ = std::floating_point<T>; 

    __CASE<typename LhsT, typename RhsT> concept AssignableFrom_ = std::assignable_from<LhsT, RhsT>; 

    __CASE<typename T, typename U> concept SwappableWith_ = std::swappable_with<T, U>; 

    __CASET concept Destructible_ = std::destructible<T>; 

    __CASE<typename T, typename U> concept ConstructibleFrom_ = std::constructible_from<T, U>; 

    __CASET concept DefaultInitializable_ = std::default_initializable<T>; 

    __CASET concept CopyAndMoveConstructible_ = std::move_constructible<T>;

    /* Comparison concepts */
    __CASET concept EqualityComparable_ = std::equality_comparable<T>; 

    __CASE<typename T, typename U> concept EqualityComparableWith_ = std::equality_comparable_with<T, U>; 

    __CASET concept TotallyOrdered_ = std::totally_ordered<T>; 

    __CASE<typename T, typename U> concept TotallyOrderedWith_ = std::totally_ordered_with<T, U>; 

    __CASET concept MoveAndSwappable_ = std::movable<T>; 

    __CASET concept CopyMoveAndSwappable_ = std::copyable<T>;

    __CASET concept Semiregular_ = std::semiregular<T>; 

    __CASET concept Regular_ = std::regular<T>; 

    __CASET concept Invocable_ = std::invocable<T>; 

    __CASET concept RegularInvocable_ = std::regular_invocable<T>; 

    __CASET concept Predicate_ = std::predicate<T>;

    __CASE<typename R, typename T, typename U> concept EquivalenceRelation_ = std::equivalence_relation<R, T, U>; 

    __CASE<typename R, typename T, typename U> concept StrictWeakOrder_ = std::strict_weak_order<R, T, U>; 

     /// Range concepts

    __CASET concept Range_ = std::ranges::range<T>; 

    __CASET concept BorrowedRange_ = std::ranges::borrowed_range<T>;

    __CASET concept SizedRange_ = std::ranges::sized_range<T>; 

    __CASET concept RangeView_ = std::ranges::view<T>; 

    __CASET concept InputRange_ = std::ranges::input_range<T>;

    __CASE<typename T, typename U> concept OutputRange_ = std::ranges::output_range<T, U>; 

    __CASET concept ForwardRange_ = std::ranges::forward_range<T>; 

    __CASET concept BidirectionalRange_ = std::ranges::bidirectional_range<T>; 

    __CASET concept RandomAccessRange_ = std::ranges::random_access_range<T>;

    __CASET concept ContiguousRange_ = std::ranges::contiguous_range<T>; 

    __CASET concept CommonRange_ = std::ranges::common_range<T>; 

    __CASET concept ViewableRange_ = std::ranges::viewable_range<T>; 

    /* Iterator concepts */

    __CASET concept IndirectlyReadable_ = std::indirectly_readable<T>;

    __CASE<typename T, typename U> concept IndirectlyWritable_ = std::indirectly_writable<T, U>; 

    __CASET concept WeaklyIncrementableIter_ = std::weakly_incrementable<T>; 

    __CASET concept IncrementableIter_ = std::incrementable<T>; 

    __CASET concept InputOrOutputIter_ = std::input_or_output_iterator<T>; 

    __CASE<typename SentinelT, typename IterT> concept SentinelForIter_ = std::sentinel_for<SentinelT, IterT>; 

    __CASE<typename SentinelT, typename IterT> concept SizedSentinelForIter_ = std::sized_sentinel_for<SentinelT, IterT>; 

    __CASET concept InputIter_ = std::input_iterator<T>;

    __CASET concept OutputIter_ = std::input_iterator<T>; 

    __CASET concept ForwardIter_ = std::forward_iterator<T>; 

    __CASET concept BidirectionalIter_ = std::bidirectional_iterator<T>; 

    __CASET concept RandomAccessIter_ = std::random_access_iterator<T>; 

    __CASET concept ContiguousIter_ = std::contiguous_iterator<T>; 
     /* Indirect callable concepts */


    /* <@concept:IndirectlyUnaryInvocable_>
     * <@brief:Specifies that a callable type can be invoked with the result of dereferencing
     * an indirectly_readable type.>
     * */
    __CASE<typename T, typename U>
        concept IndirectlyUnaryInvocable_ = std::indirectly_unary_invocable<T, U>;


    /* <@concept:IndirectlyRegularUnaryInvocable_>
     * <@brief:Specifies that a callable type can be invoked with the result of dereferencing
     * an indirectly_readable regular type.>
     * */
    __CASE<typename T, typename U>
        concept IndirectlyRegularUnaryInvocable_ = std::indirectly_regular_unary_invocable<T, U>;


    /* <@concept:IndirectUnaryPredicate_>
     * <@brief:specifies that a callable type, when invoked with the result of dereferencing an
     * indirectly_readable type, satisfies predicate.>
     * */
    __CASE<typename T, typename U>
        concept IndirectUnaryPredicate_ = std::indirect_unary_predicate<T, U>;


    /* <@concept:IndirectBinaryPredicate_>
     * <@brief:	Specifies that a callable type, when invoked with the result of dereferencing two
     * indirectly_readable types, satisfies predicate.>
     * */
    __CASE<typename T, typename U, typename V>
        concept IndirectBinaryPredicate_ = std::indirect_binary_predicate<T, U, V>;


    /* <@concept:IndirectEquivalenceRelation_>
     * <@brief:	Specifies that a callable type, when invoked with the result of dereferencing two
     * indirectly_readable types, satisfies equivalence_relation.>
     * */
    __CASE<typename T, typename U, typename V = U>
        concept IndirectEquivalenceRelation_ = std::indirect_equivalence_relation<T, U, V>;


    /* <@concept:IndirectStrictWeakOrder_>
     * <@brief:	specifies that a callable type, when invoked with the result of dereferencing two
     * indirectly_readable types, satisfies strict_weak_order.>
     * */
    __CASE<typename T, typename U, typename V = U>
        concept IndirectStrictWeakOrder_ = std::indirect_strict_weak_order<T, U, V>;


    /* specifies that values may be moved from an indirectly_readable type to an indirectly_writable type */
    __CASE<typename T, typename U> concept IndirectlyMovable_ = std::indirectly_movable<T, U>;

    /* specifies that values may be moved from an indirectly_readable type to an indirectly_writable
     * type and that the move may be performed via an intermediate object */
    __CASE<typename T, typename U> concept IndirectlyMovableStorage_ = std::indirectly_movable_storable<T, U>;

    /* specifies that values may be copied from an indirectly_readable type to an indirectly_writable type */
    __CASE<typename T, typename U> concept IndirectlyCopyable_ = std::indirectly_copyable<T, U>;

    /* specifies that values may be copied from an indirectly_readable type to an indirectly_writable
     * type and that the copy may be performed via an intermediate object */
    __CASE<typename T, typename U> concept IndirectlyCopyableStorage_ = std::indirectly_copyable_storable<T, U>;

    /* specifies that the values referenced by two indirectly_readable types can be swapped */
    __CASE<typename T, typename U> concept IndirectlySwappable_ = std::indirectly_swappable<T, U>;

    /* specifies that the values referenced by two indirectly_readable types can be compared */
    __CASE<typename T, typename U, typename V, typename X = std::identity, typename Y = std::identity>
        concept IndirectlyComparable_ = std::indirectly_comparable<T, U, V, X, Y>;

    /* <@concept: Mergeable_>
    * <@brief: Specifies the common requirements of algorithms that reorder elements in place.>
    * */
    __CASET concept Permutable_ = std::permutable<T>;

    /* <@concept: Mergeable_>
     * <@brief: Specifies the requirements for algorithms that merge two input ranges
     * into a single output range according to the strict weak ordering imposed by X.>
     * */
    __CASE<typename T, typename U, typename V, typename X = std::ranges::less, typename Y = std::identity, typename Z = std::identity
    >
        concept Mergeable_ = std::mergeable<T, U, V, X, Y, Z>;

    /* <@concept: Mergeable_>
     * <@brief: Specifies the requirements for algorithms that permute a range into
     * an ordered range according to R..>
     * */
    __CASE<typename T, typename U = std::ranges::less, typename V = std::identity > 
    concept Sortable_ = std::sortable<T, U, V>;

    /// <@concept:Arithmetic_>
/// <@brief: Specifies an integral type, a floating-point type; or a cv-qualified version thereof.>
    __CASET concept Arithmetic_ = std::is_arithmetic_v<T>;

    //@concept ArithSigned_
    // signed arithmetic types
    template<typename T>
    concept ArithSigned_ = std::is_arithmetic_v<T>
        && std::numeric_limits<T>::is_specialized
        && std::numeric_limits<T>::is_signed;

    //@concept ArithNoBool_
    // signed arithmetic types
    template<typename T>
    concept ArithNoBool_ = std::is_arithmetic_v<T>
        && std::numeric_limits<T>::is_specialized
        && std::numeric_limits<T>::is_signed
        && !std::is_same_v<bool, T>;

    /// <@concept:Boolean_>
    /// <@brief: Specifies a type which is a bool, or any cv ref qualified version thereof.>
    __CASET concept Boolean_ = SameAs_<std::remove_cvref_t<T>, bool>;

    /// <@concept:IntegralNumeral_>
    /// <@brief: Specifies a type which is an integral excluding bool; or any cv ref qualified version thereof.>
    __CASET concept IntegralNumeral_ = Integral_<T> && not Boolean_<T>;

    /// <@concept:IntegralNumeral_>
    /// <@brief: Specifies a type which is an unsigned integral excluding bool; or any cv ref qualified version thereof.>
    __CASET concept UnsignedIntegralNumeral_ = IntegralNumeral_<T> && UnsignedIntegral_<T>;

    /// <@concept:IntegralNumeral_>
    /// <@brief: Specifies a type which is an signed integral excluding bool; or any cv ref qualified version thereof.>
    __CASET concept SignedIntegralNumeral_ = IntegralNumeral_<T> && SignedIntegral_<T>;

    /// <@concept:Numeral_>
    /// <@brief: Specifies an integral numeral type, a floating-point type; or a cv-qualified version thereof.>
    __CASET
        concept Numeral_ = IntegralNumeral_<T> || FloatingPoint_<T>;

    /// <@concept:SpecializedArithmetic_>
    /// <@brief: Specifies an arithmetic type that is specialized in std::numeric_limits.>
    __CASET concept SpecializedArithmetic_ = Arithmetic_<T> && std::numeric_limits<T>::is_specialized;

    /// <@concept:TrappingArithmetic_>
    /// <@brief: Specifies an arithmetic type that is specialized and has at least one value that,
    ///          if used as an argument to an arithmetic operation, will generate a trap.>
    __CASET concept TrappingArithmetic_ = SpecializedArithmetic_<T> && std::numeric_limits<T>::traps;

    /// <@concept:Iec559Floating_>
    /// <@brief: Specifies floating-point type which fulfill the requirements of IEC 559 (IEEE 754) standard.
    /// This means that std::numeric_limits<T>::has_infinity, std::numeric_limits<T>::has_quiet_NaN,
    /// and std::numeric_limits<T>::has_signaling_NaN are also true.>
    __CASET concept Iec559Floating_ = FloatingPoint_<T> && std::numeric_limits<T>::is_iec559;

    /// <@concept: TrappingFloating_>
    /// <@brief: Specifies an floating type that is specialized and has at least one value that,
    ///          if used as an argument to an arithmetic operation, will generate a trap.>
    __CASET
        concept TrappingFloating_ = FloatingPoint_<T> && TrappingArithmetic_<T>;

    /// <@concept: FloatingHasInf_>
    /// <@brief: Specifies an floating type that is specialized and capable of representing
    ///          the positive infinity as a distinct special value.>
    __CASET concept FloatingHasInf_ = FloatingPoint_<T> && std::numeric_limits<T>::has_infinity;

    /// <@concept: FloatingHasQuietNan_>
    /// <@brief: Specifies an floating type that is capable of representing the special value
    ///          "Quiet Not-A-Number".>
    __CASET concept FloatingHasQuietNan_ = FloatingPoint_<T> && std::numeric_limits<T>::has_quiet_NaN;

    /// <@concept: FloatingHasSignalingNan_>
    /// <@brief: Specifies an floating type that can represent the special value "signaling not-a-number" (NaN).>
    __CASET concept FloatingHasSignalingNan_ = FloatingPoint_<T> && std::numeric_limits<T>::has_signaling_NaN;


    /// <@concept:SafeFloating_>
    /// <@brief: Iec559 compliant, non-trapping floating point types.>
    __CASET concept SafeFloating_ = Iec559Floating_<T> && not TrappingFloating_<T>;
    
    ///< @concept FloatingUnsafe_
    ///<Possibly trapping floating point types
    template<typename T>
    concept FloatingUnsafe_ = std::is_arithmetic_v<T>
        && FloatingPoint_<T>
        && std::numeric_limits<T>::is_specialized
        && std::numeric_limits<T>::traps;

    //@concept
    // non-arithmetic, trivial, non-abstract class or struct types
    template<typename T>
    concept TrivialObject_ = !std::is_arithmetic_v<T>
        && std::is_trivial_v<T>
        && !std::is_abstract_v<T>;

    /// <@class> is_specialization_of
    /// <@brief> Boolean constant object, generalized check if a type is a template specialization
    __CASE <typename SpecializedT, template <typename...> class BaseT>
    struct is_specialization_of : std::false_type {};

    __CASE <typename... SpecializedT, template <typename...> class BaseT>
    struct is_specialization_of<BaseT<SpecializedT...>, BaseT> : std::true_type {};

    /// <@method> is_specialization_of_v
    /// <@brief> return true if a type is a template specialization of another type
    __CASE <typename SpecializedT, template <typename...> class BaseT>
    inline constexpr bool is_specialization_of_v = is_specialization_of<SpecializedT, BaseT>::value;

    /// <@concept> Specializes_
    /// <@brief> a template type which specializes a given template type
    __CASE<typename T, template <typename...> class Z>
    concept Specializes_ = is_specialization_of_v<T, Z>;

    template<typename T>
    struct falsify_type : std::false_type {
    };

    /*//\<@namespace:ppp::deduce> ////////////////////////////////////////////////////////////////////////
    /// <class> float_type_from_any_type
    /// <@brief> Defaults to float for non-floating types.If a floating point type is passed then the
    ///          float_type is the type of passed floating point type.
    ///\////////////////////////////////////////////////////////////////////////////////////////////////*/
    __CASET struct float_type_from_any_type { 
        using type = float; 
    };

    __CASE <FloatingPoint_ FloatT> struct float_type_from_any_type<FloatT> { 
        using type = FloatT; 
    };

    /// Throws a compile time error with a message given a type, used to disable template cases.
#define __FALSE_TYPE_ERROR(type,stringliteral) static_assert(falsify_type<type>::value, stringliteral )

} // end gtl::req

#endif // GTL_HEADGUARD_requires_gtl_hpp
