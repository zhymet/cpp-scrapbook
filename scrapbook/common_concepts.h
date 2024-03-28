#pragma once
#include <concepts>
#include <ranges>
#include <utility>

namespace require {

/* Core Language Concepts */
template <typename T, typename U>
concept SameAs_ =
    std::same_as<T, U>;  /// Specifies that a type is the same as another type.

template <typename T, typename U>
concept DerivedFrom_ = std::derived_from<T, U>;  /// Specifies that a type is
                                                 /// the same as another type.

template <typename T, typename U>
concept ConvertibleTo_ =
    std::convertible_to<T, U>;  /// Specifies that a type is the same as another
                                /// type.

template <typename T, typename U>
concept CommonRefWith_ =
    std::common_reference_with<T, U>;  /// Specifies that a type is the same as
                                       /// another type.

template <typename T, typename U>
concept CommonWith_ =
    std::common_with<T,
                     U>;  /// Specifies that a type is the same as another type.

template <typename T>
concept Integral_ =
    std::integral<T>;  /// Specifies that a type is the same as another type.

template <typename T>
concept SignedIntegral_ =
    std::signed_integral<T>;  /// Specifies that a type is the same as another
                              /// type.

template <typename T>
concept UnsignedIntegral_ =
    std::unsigned_integral<T>;  /// Specifies that a type is the same as another
                                /// type.

template <typename T>
concept FloatingPoint_ = std::floating_point<T>;  /// Specifies that a type is
                                                  /// the same as another type.

template <typename LhsT, typename RhsT>
concept AssignableFrom_ =
    std::assignable_from<LhsT, RhsT>;  /// Specifies that a type is the same as
                                       /// another type.

template <typename T>
concept Swappable_ =
    std::swappable<T>;  /// Specifies that a type is the same as another type.

template <typename T, typename U>
concept SwappableWith_ =
    std::swappable_with<T, U>;  /// Specifies that a type is the same as another
                                /// type.

template <typename T>
concept Destructible_ = std::destructible<T>;  /// Specifies that a type is the
                                               /// same as another type.

template <typename T, typename U>
concept ConstructibleFrom_ =
    std::constructible_from<T, U>;  /// Specifies that a type is the same as
                                    /// another type.

template <typename T>
concept DefaultInitializable_ =
    std::default_initializable<T>;  /// Specifies that a type is the same as
                                    /// another type.

template <typename T>
concept MoveConstructible_ =
    std::move_constructible<T>;  /// Specifies that a type is the same as
                                 /// another type.

// note: Types without a move constructor, but with a copy constructor that
// accepts const T& arguments,
//       satisfy std::is_move_constructible.
template <typename T>
concept CopyAndMoveConstructible_ =
    std::move_constructible<T>;  /// Specifies that a type is the same as
                                 /// another type.

/* Comparison concepts */
template <typename T>
concept EqualityComparable_ =
    std::equality_comparable<T>;  /// Specifies that a type is the same as
                                  /// another type.

template <typename T, typename U>
concept EqualityComparableWith_ =
    std::equality_comparable_with<T, U>;  /// Specifies that a type is the same
                                          /// as another type.

template <typename T>
concept TotallyOrdered_ =
    std::totally_ordered<T>;  /// Specifies that a type is the same as another
                              /// type.

template <typename T, typename U>
concept TotallyOrderedWith_ =
    std::totally_ordered_with<T, U>;  /// Specifies that a type is the same as
                                      /// another type.

template <typename T>
concept MoveAndSwappable_ = std::movable<T>;  /// Specifies that an object of a
                                              /// type can be moved and swapped

template <typename T>
concept CopyMoveAndSwappable_ =
    std::copyable<T>;  /// Specifies that an object of a type can be moved and
                       /// swapped

template <typename T>
concept Semiregular_ = std::semiregular<T>;  /// Specifies that an object of a
                                             /// type can be moved and swapped

template <typename T>
concept Regular_ = std::regular<T>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept Invocable_ = std::invocable<T>;  /// Specifies that an object of a type
                                         /// can be moved and swapped

template <typename T>
concept RegularInvocable_ =
    std::regular_invocable<T>;  /// Specifies that an object of a type can be
                                /// moved and swapped

template <typename T>
concept Predicate_ = std::predicate<T>;  /// Specifies that an object of a type
                                         /// can be moved and swapped

template <typename R, typename T, typename U>
concept EquivalenceRelation_ =
    std::equivalence_relation<R, T, U>;  /// Specifies that an object of a type
                                         /// can be moved and swapped

template <typename R, typename T, typename U>
concept StrictWeakOrder_ =
    std::strict_weak_order<R, T, U>;  /// Specifies that an object of a type can
                                      /// be moved and swapped

/// Range concepts

template <typename T>
concept Range_ = std::ranges::range<T>;  /// Specifies that an object of a type
                                         /// can be moved and swapped

template <typename T>
concept BorrowedRange_ =
    std::ranges::borrowed_range<T>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept SizedRange_ =
    std::ranges::sized_range<T>;  /// Specifies that an object of a type can be
                                  /// moved and swapped

template <typename T>
concept RangeView_ = std::ranges::view<T>;  /// Specifies that an object of a
                                            /// type can be moved and swapped

template <typename T>
concept InputRange_ =
    std::ranges::input_range<T>;  /// Specifies that an object of a type can be
                                  /// moved and swapped

template <typename T, typename U>
concept OutputRange_ =
    std::ranges::output_range<T, U>;  /// Specifies that an object of a type can
                                      /// be moved and swapped

template <typename T>
concept ForwardRange_ =
    std::ranges::forward_range<T>;  /// Specifies that an object of a type can
                                    /// be moved and swapped

template <typename T>
concept BidirectionalRange_ =
    std::ranges::bidirectional_range<T>;  /// Specifies that an object of a type
                                          /// can be moved and swapped

template <typename T>
concept RandomAccessRange_ =
    std::ranges::random_access_range<T>;  /// Specifies that an object of a type
                                          /// can be moved and swapped

template <typename T>
concept ContiguousRange_ =
    std::ranges::contiguous_range<T>;  /// Specifies that an object of a type
                                       /// can be moved and swapped

template <typename T>
concept CommonRange_ =
    std::ranges::common_range<T>;  /// Specifies that an object of a type can be
                                   /// moved and swapped

template <typename T>
concept ViewableRange_ =
    std::ranges::viewable_range<T>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

/* Iterator concepts */

template <typename T>
concept IndirectlyReadable_ =
    std::indirectly_readable<T>;  /// Specifies that an object of a type can be
                                  /// moved and swapped

template <typename T, typename U>
concept IndirectlyWritable_ =
    std::indirectly_writable<T, U>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept WeaklyIncrementableIter_ =
    std::weakly_incrementable<T>;  /// Specifies that an object of a type can be
                                   /// moved and swapped

template <typename T>
concept IncrementableIter_ =
    std::incrementable<T>;  /// Specifies that an object of a type can be moved
                            /// and swapped

template <typename T>
concept InputOrOutputIter_ =
    std::input_or_output_iterator<T>;  /// Specifies that an object of a type
                                       /// can be moved and swapped

template <typename SentinelT, typename IterT>
concept SentinelForIter_ =
    std::sentinel_for<SentinelT, IterT>;  /// Specifies that an object of a type
                                          /// can be moved and swapped

template <typename SentinelT, typename IterT>
concept SizedSentinelForIter_ =
    std::sized_sentinel_for<SentinelT,
                            IterT>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept InputIter_ = std::input_iterator<T>;  /// Specifies that an object of a
                                              /// type can be moved and swapped

template <typename T>
concept OutputIter_ = std::input_iterator<T>;  /// Specifies that an object of a
                                               /// type can be moved and swapped

template <typename T>
concept ForwardIter_ =
    std::forward_iterator<T>;  /// Specifies that an object of a type can be
                               /// moved and swapped

template <typename T>
concept BidirectionalIter_ =
    std::bidirectional_iterator<T>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept RandomAccessIter_ =
    std::random_access_iterator<T>;  /// Specifies that an object of a type can
                                     /// be moved and swapped

template <typename T>
concept ContiguousIter_ =
    std::contiguous_iterator<T>;  /// Specifies that an object of a type can be
                                  /// moved and swapped

/* Indirect callable concepts */

/* <@concept:IndirectlyUnaryInvocable_>
 * <@brief:Specifies that a callable type can be invoked with the result of
 * dereferencing an indirectly_readable type.>
 * */
template <typename T, typename U>
concept IndirectlyUnaryInvocable_ = std::indirectly_unary_invocable<T, U>;

/* <@concept:IndirectlyRegularUnaryInvocable_>
 * <@brief:Specifies that a callable type can be invoked with the result of
 * dereferencing an indirectly_readable regular type.>
 * */
template <typename T, typename U>
concept IndirectlyRegularUnaryInvocable_ =
    std::indirectly_regular_unary_invocable<T, U>;

/* <@concept:IndirectUnaryPredicate_>
 * <@brief:specifies that a callable type, when invoked with the result of
 * dereferencing an indirectly_readable type, satisfies predicate.>
 * */
template <typename T, typename U>
concept IndirectUnaryPredicate_ = std::indirect_unary_predicate<T, U>;

/* <@concept:IndirectBinaryPredicate_>
 * <@brief:	Specifies that a callable type, when invoked with the result of
 * dereferencing two indirectly_readable types, satisfies predicate.>
 * */
template <typename T, typename U, typename V>
concept IndirectBinaryPredicate_ = std::indirect_binary_predicate<T, U, V>;

/* <@concept:IndirectEquivalenceRelation_>
 * <@brief:	Specifies that a callable type, when invoked with the result of
 * dereferencing two indirectly_readable types, satisfies equivalence_relation.>
 * */
template <typename T, typename U, typename V = U>
concept IndirectEquivalenceRelation_ =
    std::indirect_equivalence_relation<T, U, V>;

/* <@concept:IndirectStrictWeakOrder_>
 * <@brief:	specifies that a callable type, when invoked with the result of
 * dereferencing two indirectly_readable types, satisfies strict_weak_order.>
 * */
template <typename T, typename U, typename V = U>
concept IndirectStrictWeakOrder_ = std::indirect_strict_weak_order<T, U, V>;

/* specifies that values may be moved from an indirectly_readable type to an
 * indirectly_writable type */
template <typename T, typename U>
concept IndirectlyMovable_ = std::indirectly_movable<T, U>;

/* specifies that values may be moved from an indirectly_readable type to an
 * indirectly_writable type and that the move may be performed via an
 * intermediate object */
template <typename T, typename U>
concept IndirectlyMovableStorage_ = std::indirectly_movable_storable<T, U>;

/* specifies that values may be copied from an indirectly_readable type to an
 * indirectly_writable type */
template <typename T, typename U>
concept IndirectlyCopyable_ = std::indirectly_copyable<T, U>;

/* specifies that values may be copied from an indirectly_readable type to an
 * indirectly_writable type and that the copy may be performed via an
 * intermediate object */
template <typename T, typename U>
concept IndirectlyCopyableStorage_ = std::indirectly_copyable_storable<T, U>;

/* specifies that the values referenced by two indirectly_readable types can be
 * swapped */
template <typename T, typename U>
concept IndirectlySwappable_ = std::indirectly_swappable<T, U>;

/* specifies that the values referenced by two indirectly_readable types can be
 * compared */
template <typename T, typename U, typename V, typename X = std::identity,
          typename Y = std::identity>
concept IndirectlyComparable_ = std::indirectly_comparable<T, U, V, X, Y>;

/* <@concept: Mergeable_>
 * <@brief: Specifies the common requirements of algorithms that reorder
 * elements in place.>
 * */
template <typename T>
concept Permutable_ = std::permutable<T>;

/* <@concept: Mergeable_>
 * <@brief: Specifies the requirements for algorithms that merge two input
 * ranges into a single output range according to the strict weak ordering
 * imposed by X.>
 * */
template <typename T, typename U, typename V, typename X = std::ranges::less,
          typename Y = std::identity, typename Z = std::identity>
concept Mergeable_ = std::mergeable<T, U, V, X, Y, Z>;

/* <@concept: Mergeable_>
 * <@brief: Specifies the requirements for algorithms that permute a range into
 * an ordered range according to R..>
 * */
template <typename T, typename U = std::ranges::less,
          typename V = std::identity>
concept Sortable_ = std::sortable<T, U, V>;

/// <@concept:Arithmetic_>
/// <@brief: Specifies an integral type, a floating-point type; or a
/// cv-qualified version thereof.>
template <typename T>
concept Arithmetic_ = std::is_arithmetic_v<T>;

/// <@concept:Boolean_>
/// <@brief: Specifies a type which is a bool, or any cv ref qualified version
/// thereof.>
template <typename T>
concept Boolean_ = SameAs_<std::remove_cvref_t<T>, bool>;

/// <@concept:IntegralNumeral_>
/// <@brief: Specifies a type which is an integral excluding bool; or any cv ref
/// qualified version thereof.>
template <typename T>
concept IntegralNumeral_ = Integral_<T> && not Boolean_<T>;

/// <@concept:IntegralNumeral_>
/// <@brief: Specifies a type which is an unsigned integral excluding bool; or
/// any cv ref qualified version thereof.>
template <typename T>
concept UnsignedIntegralNumeral_ = IntegralNumeral_<T> && UnsignedIntegral_<T>;

/// <@concept:IntegralNumeral_>
/// <@brief: Specifies a type which is an signed integral excluding bool; or any
/// cv ref qualified version thereof.>
template <typename T>
concept SignedIntegralNumeral_ = IntegralNumeral_<T> && SignedIntegral_<T>;

/// <@concept:Numeral_>
/// <@brief: Specifies an integral numeral type, a floating-point type; or a
/// cv-qualified version thereof.>
template <typename T>
concept Numeral_ = IntegralNumeral_<T> || FloatingPoint_<T>;

/// <@concept:SpecializedArithmetic_>
/// <@brief: Specifies an arithmetic type that is specialized in
/// std::numeric_limits.>
template <typename T>
concept SpecializedArithmetic_ =
    Arithmetic_<T> && std::numeric_limits<T>::is_specialized;

/// <@concept:SpecializedArithmetic_>
/// <@brief: Specifies an arithmetic type that is specialized and has at least
/// one value that,
///          if used as an argument to an arithmetic operation, will generate a
///          trap.>
template <typename T>
concept TrappingArithmetic_ =
    SpecializedArithmetic_<T> && std::numeric_limits<T>::traps;

/// <@concept:Iec559Floating_>
/// <@brief: Specifies floating-point type which fulfill the requirements of IEC
/// 559 (IEEE 754) standard. This means that
/// std::numeric_limits<T>::has_infinity, std::numeric_limits<T>::has_quiet_NaN,
/// and std::numeric_limits<T>::has_signaling_NaN are also true.>
template <typename T>
concept Iec559Floating_ =
    FloatingPoint_<T> && std::numeric_limits<T>::is_iec559;

/// <@concept: TrappingFloating_>
/// <@brief: Specifies an floating type that is specialized and has at least one
/// value that,
///          if used as an argument to an arithmetic operation, will generate a
///          trap.>
template <typename T>
concept TrappingFloating_ = FloatingPoint_<T> && TrappingArithmetic_<T>;

/// <@concept: FloatingHasInf_>
/// <@brief: Specifies an floating type that is specialized and capable of
/// representing
///          the positive infinity as a distinct special value.>
template <typename T>
concept FloatingHasInf_ =
    FloatingPoint_<T> && std::numeric_limits<T>::has_infinity;

/// <@concept: FloatingHasQuietNan_>
/// <@brief: Specifies an floating type that is capable of representing the
/// special value
///          "Quiet Not-A-Number".>
template <typename T>
concept FloatingHasQuietNan_ =
    FloatingPoint_<T> && std::numeric_limits<T>::has_quiet_NaN;

/// <@concept: FloatingHasSignalingNan_>
/// <@brief: Specifies an floating type that can represent the special value
/// "signaling not-a-number" (NaN).>
template <typename T>
concept FloatingHasSignalingNan_ =
    FloatingPoint_<T> && std::numeric_limits<T>::has_signaling_NaN;

/// <@concept:SafeFloating_>
/// <@brief: Iec559 compliant, non-trapping floating point types.>
template <typename T>
concept SafeFloating_ = Iec559Floating_<T> && not TrappingFloating_<T>;

///< @concept FloatingUnsafe_
///< Possibly trapping floating point types
template <typename T>
concept FloatingUnsafe_ =
    std::is_arithmetic_v<T> && FloatingPoint_<T> &&
    std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::traps;

//@concept
// non-arithmetic, trivial, non-abstract class or struct types
template <typename T>
concept TrivialObject_ =
    !std::is_arithmetic_v<T> && std::is_trivial_v<T> && !std::is_abstract_v<T>;

template <typename T>
concept CopyConstructible_ = std::is_copy_constructible_v<T>;

template <typename T>
concept CopyAssignable_ = std::is_copy_assignable_v<T>;

template <typename T>
concept Copyable_ = CopyConstructible_<T> && CopyAssignable_<T>;

template <typename T>
concept NonCopyable_ = (not CopyConstructible_<T>)&&(not CopyAssignable_<T>);

template <typename T>
concept MoveAssignable_ = std::is_move_assignable_v<T>;

template <typename T>
concept Movable_ = MoveConstructible_<T> && MoveAssignable_<T>;

template <typename T>
concept NonMovable_ = (not MoveConstructible_<T>)&&(not MoveAssignable_<T>);

template <typename T>
concept MoveOnly_ = Movable_<T> && (not Copyable_<T>);

template <typename T>
concept NoThrowMoveConstructible_ = std::is_nothrow_move_constructible_v<T>;

template <typename T>
concept NoThrowMoveAssignable_ = std::is_nothrow_move_assignable_v<T>;

template <typename T>
concept MemberObjectPointer_ = std::is_member_object_pointer_v<T>;

template <typename T>
concept MemberFunctionPointer_ = std::is_member_function_pointer_v<T>;

/// Cannot be moved copied or swapped
template <typename T>
concept Singular_ = NonCopyable_<T> && NonMovable_<T> && (not Swappable_<T>);

}  // namespace require