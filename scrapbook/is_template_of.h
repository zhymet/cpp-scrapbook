#pragma once
/// <@class> is_specialization_of
/// <@brief> Boolean constant object, generalized check if a type is a template
/// specialization
template <typename SpecializedT, template <typename...> class BaseT>
struct is_specialization_of : std::false_type {};

template <typename... SpecializedT, template <typename...> class BaseT>
struct is_specialization_of<BaseT<SpecializedT...>, BaseT> : std::true_type {};

/// <@method> is_specialization_of_v
/// <@brief> return true if a type is a template specialization of another type
template <typename SpecializedT, template <typename...> class BaseT>
inline constexpr bool is_specialization_of_v =
    is_specialization_of<SpecializedT, BaseT>::value;

/// <@concept> Specializes_
/// <@brief> a template type which specializes a given template type
template <typename T, template <typename...> class Z>
concept Specializes_ = is_specialization_of_v<T, Z>;

template <typename T>
struct falsify_type : std::false_type {};

/// Throws a compile time error with a message given a type, used to disable
/// template cases.
#define __FALSE_TYPE_ERROR(type, stringliteral) \
  static_assert(falsify_type<type>::value, stringliteral)
