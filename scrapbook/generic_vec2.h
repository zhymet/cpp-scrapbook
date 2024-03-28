#pragma once
///\/////////////////////////////////////////////////////////////////////////////////////////////////
/// <@header> vec2.hpp
/// <@author> Anton Yashchenko
/// <@updated> 7/22/2020 10:10:53 PM
/// <@brief> Generic 2 dimensional vector
///\/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PPP_VEC2_HPP
#define PPP_VEC2_HPP

#include <cmath>
#include <limits>
#include <numbers>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "common_concepts.h"
#include "is_approx.h"  // is_approx
#include "is_template_of.h"

namespace graphics {

namespace vec2_detail {
/*//\<@namespace:ppp::deduce>
////////////////////////////////////////////////////////////////////////
/// <class> float_type_from_any_type
/// <@brief> Defaults to float for non-floating types.If a floating point type
///          is passed then the
///          float_type is the type of passed floating point type.
///\//////////////////////////////////////////////////////////////////*/
template <typename T>
struct float_type_from_any_type {
  using type = float;
};

template <require::FloatingPoint_ FloatT>
struct float_type_from_any_type<FloatT> {
  using type = FloatT;
};
}  // namespace vec2_detail
/// <@class> vec2
/// <@case> invalid base
/// <@brief> 2 dimensional euclidean vector.
template <typename T>
struct vec2 {
  __FALSE_TYPE_ERROR(T, "Vec2 : Invalid template parameter T specialization");
};

/// <@class:> vec2
/// <@case> partial specialization for trivial objects
/// <@requires> value_type is a TrivialObject_
/// <@brief> 2 dimensional euclidean vector plain old data struct.
template <typename T>
  requires require::TrivialObject_<T>
struct vec2<T> {
  using value_type = T;
  using float_type = typename require::float_type_from_any_type<value_type>;
  value_type x;
  value_type y;

  constexpr vec2() = default;

  constexpr vec2(value_type x, value_type y) : x(x), y(y) {}
};

/// <@class:> vec2
/// <@case> partial specialization for arithmetic types
/// <@requires> value_type is an arithmetic type
/// <@brief> 2 dimensional euclidean vector struct with utility methods for
/// arithmetic types.
template <typename T>
  requires std::is_arithmetic_v<T>
struct vec2<T> {
  using value_type = T;
  using size_type = std::size_t;
  using float_type = typename vec2_detail::float_type_from_any_type<value_type>;
  value_type x;
  value_type y;

  constexpr vec2() = default;

  constexpr vec2(value_type x, value_type y) : x(x), y(y) {}

  /// <@section> Static constant convenience vectors.
  /// <@method> vec2::epsilon
  /// <@brief> The smallest possible difference between two values of this type.
  constexpr static inline vec2<value_type> epsilon() {
    return vec2<value_type>(std::numeric_limits<value_type>::epsilon(),
                            std::numeric_limits<value_type>::epsilon());
  }

  /// <@method> vec2::zero
  /// <@brief> The euclidean 2-space point of origin, zero vector.
  constexpr static inline vec2<value_type> zero() {
    return vec2<value_type>(value_type(), value_type());
  }

  /// <@method> vec2::min
  /// <@brief> A vector with the lowest finite values x and y,such that there is
  /// no other
  ///    		 finite value z where z < x || z < y.
  constexpr static inline vec2<value_type> min() {
    return vec2<value_type>(std::numeric_limits<value_type>::lowest(),
                            std::numeric_limits<value_type>::lowest());
  }

  /// <@method> vec2::max
  /// <@brief> A vector with both values set to the largest finite values of the
  /// stored type.
  constexpr static inline vec2<value_type> max() {
    return vec2<value_type>(std::numeric_limits<value_type>::max(),
                            std::numeric_limits<value_type>::max());
  }

  /// <@method> vec2::inf
  /// <@requires> require::FloatingPoint_ value type.
  /// <@brief> A vector with both values set to positive infinity.
  constexpr static inline vec2<value_type> inf()
    requires std::numeric_limits<T>::has_infinity
  {
    return vec2<value_type>(std::numeric_limits<value_type>::infinity(),
                            std::numeric_limits<value_type>::infinity());
  }

  /// <@method> vec2::nan
  /// <@requires> FloatingSafe_ value type.
  /// <@brief> A vector with both values set to quiet NaN floating point
  /// numbers.
  constexpr static inline vec2<value_type> nan()
    requires std::numeric_limits<T>::has_quiet_NaN
  {
    return vec2<value_type>(std::numeric_limits<value_type>::quiet_NaN(),
                            std::numeric_limits<value_type>::quiet_NaN());
  }

  /// <@method> vec2::denorm_min
  /// <@brief> A vector with both values set to the smallest positive subnormal
  /// value.
  constexpr static inline vec2<value_type> denorm_min()
    requires(std::numeric_limits<T>::has_denorm == std::denorm_present)
  {
    return vec2<value_type>(std::numeric_limits<value_type>::denorm_min(),
                            std::numeric_limits<value_type>::denorm_min());
  }

  /// <@section> Equality operators.

  /// <@operator> ==(vec2)
  /// <@brief> True if both x and y values are equal to their respective value
  /// in the passed vector.
  constexpr inline bool operator==(const vec2<value_type>& rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  /// <@operator> !=(vec2)
  /// <@brief> True if either x or y values are not equal to their respective
  ///			 value in the passed vector.
  constexpr inline bool operator!=(const vec2<value_type>& rhs) const {
    return x != rhs.x || y != rhs.y;
  }
  /// <@operator> ==(value_type)
  /// <@brief> True if both x and y values are equal to the passed value.
  constexpr inline bool operator==(const value_type& rhs) const {
    return x == rhs && y == rhs;
  }

  /// <@operator> !=(value_type)
  /// <@brief> True if either the x or y value is not equal to the passed value.
  constexpr inline bool operator!=(const value_type& rhs) const {
    return x != rhs || y != rhs;
  }

  /// <@section> Binary operators.

  constexpr inline vec2<value_type> operator*(vec2<value_type>&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x * std::move(rhs.x), y * std::move(rhs.y));
  }

  constexpr inline vec2<value_type> operator/(vec2<value_type>&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x / std::move(rhs.x), y / std::move(rhs.y));
  }

  constexpr inline vec2<value_type> operator+(vec2<value_type>&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x + std::move(rhs.x), y + std::move(rhs.y));
  }

  constexpr inline vec2<value_type> operator-(vec2<value_type>&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x - std::move(rhs.x), y - std::move(rhs.y));
  }

  constexpr inline vec2<value_type> operator*(value_type&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x * rhs, y * std::move(rhs));
  }

  constexpr inline vec2<value_type> operator/(value_type&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x / rhs, y / std::move(rhs));
  }

  constexpr inline vec2<value_type> operator+(value_type&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x + rhs, y + std::move(rhs));
  }

  constexpr inline vec2<value_type> operator-(value_type&& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x - rhs, y - std::move(rhs));
  }

  constexpr inline void operator*=(vec2<value_type>&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x *= std::move(rhs.x);
    y *= std::move(rhs.y);
  }

  constexpr inline void operator/=(vec2<value_type>&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x /= std::move(rhs.x);
    y /= std::move(rhs.y);
  }

  constexpr inline void operator+=(vec2<value_type>&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x += std::move(rhs.x);
    y += std::move(rhs.y);
  }

  constexpr inline void operator-=(vec2<value_type>&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x -= std::move(rhs.x);
    y -= std::move(rhs.y);
  }

  constexpr inline void operator*=(value_type&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x *= rhs;
    y *= std::move(rhs);
  }

  constexpr inline void operator/=(value_type&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x *= rhs;
    y *= std::move(rhs);
  }

  constexpr inline void operator+=(value_type&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x += rhs;
    y += std::move(rhs);
  }

  constexpr inline void operator-=(value_type&& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x -= rhs;
    y -= std::move(rhs);
  }
  /// <@section> Copy operators.

  constexpr inline vec2<value_type> operator*(const vec2<value_type>& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x * rhs.x, y * rhs.y);
  }

  constexpr inline vec2<value_type> operator/(const vec2<value_type>& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x / rhs.x, y / rhs.y);
  }

  constexpr inline vec2<value_type> operator+(const vec2<value_type>& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x + rhs.x, y + rhs.y);
  }

  constexpr inline vec2<value_type> operator-(const vec2<value_type>& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x - rhs.x, y - rhs.y);
  }

  constexpr inline vec2<value_type> operator*(const value_type& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x * rhs, y * rhs);
  }

  constexpr inline vec2<value_type> operator/(const value_type& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x / rhs, y / rhs);
  }

  constexpr inline vec2<value_type> operator+(const value_type& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x + rhs, y + rhs);
  }

  constexpr inline vec2<value_type> operator-(const value_type& rhs) const
    requires require::ArithNoBool_<value_type>
  {
    return vec2<value_type>(x - rhs, y - rhs);
  }

  constexpr inline void operator*=(const vec2<value_type>& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x *= rhs.x;
    y *= rhs.y;
  }

  constexpr inline void operator/=(const vec2<value_type>& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x /= rhs.x;
    y /= rhs.y;
  }

  constexpr inline void operator+=(const vec2<value_type>& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x += rhs.x;
    y += rhs.y;
  }

  constexpr inline void operator-=(const vec2<value_type>& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x -= rhs.x;
    y -= rhs.y;
  }

  constexpr inline void operator*=(const value_type& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x *= rhs;
    y *= rhs;
  }

  constexpr inline void operator/=(const value_type& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x /= rhs;
    y /= rhs;
  }

  constexpr inline void operator+=(const value_type& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x += rhs;
    y += rhs;
  }

  constexpr inline void operator-=(const value_type& rhs)
    requires require::ArithNoBool_<value_type>
  {
    x -= rhs;
    y -= rhs;
  }
  /// <@section> Unary operators.

  constexpr inline vec2<value_type> operator-() const {
    __CXIF(std::same_as<bool, value_type>) {
      return vec2<value_type>((!x), (!y));
    }
    else {
      return vec2<value_type>(-(x), -(y));
    }
  }
  /// <@section> Other operators.

  constexpr value_type& operator[](size_type idx) {
    if (idx == 0) {
      return x;
    } else if (idx == 1) {
      return y;
    } else {
      throw std::invalid_argument(
          "Invalid index passed to vec2<T> operator[], index out of range.");
    }
  }

  /// <@section> Vector properties.
  /// <@method> vec2::angle
  ///	<@brief> Angle in radians; from the zero vector to this vector,
  /// counter-clockwise rotation.
  [[nodiscard]] constexpr inline float_type angle() const
    requires(require::ArithNoBool_<value_type> &&
             require::ArithSigned_<value_type>)
  {
    if (std::signbit(x)) {
      return std::signbit(y) ? std::atan2(-y, x) : -(std::atan2(y, x));
    } else {
      return (std::numbers::pi_v<float_type> * 2.f) - std::atan2(y, x);
    }
  }

  /// <@method> vec2::length_squared
  /// <@requires> require::ArithNoBool_ value type.
  [[nodiscard]] constexpr inline value_type length_squared() const
    requires require::ArithNoBool_<value_type>
  {
    return x * x + y * y;
  }

  /// <@method> vec2::length
  /// <@requires> require::ArithNoBool_ value type.
  [[nodiscard]] constexpr inline value_type length() const
    requires require::ArithNoBool_<value_type>
  {
    return std::sqrt(x * x + y * y);
  }

  /// <@method> vec2::is_normalized
  ///	<@brief> True if the length_squared() is equal to 1 within epsilon
  /// range.
  [[nodiscard]] constexpr inline bool is_normalized() const {
    return is_approx(length_squared(), static_cast<value_type>(1));
  }

  /// <@method> vec2::ratio
  /// <@requires> FloatingSafe_ value type.
  /// <@brief> The ratio of x to y values. X is numerator, y is denominator.
  /// Always returns a float type.
  [[nodiscard]] constexpr inline float_type ratio() const
    requires require::ArithNoBool_<value_type>
  {
    __CXIF(require::FloatingPoint_<value_type>) { return x / y; }
    else {
      return static_cast<float_type>(x) / static_cast<float_type>(y);
    }
  }

  /// <@method> vec2::has_nan
  /// <@requires> the value type is a floating point that can represent quiet or
  /// signaling NaNs
  ///	<@brief> True if this vector contains a NaN value.
  [[nodiscard]] inline bool has_nan() const
    requires((std::numeric_limits<T>::has_quiet_NaN ||
              std::numeric_limits<T>::has_signaling_NaN) ||
             (std::numeric_limits<T>::has_quiet_NaN &&
              std::numeric_limits<T>::has_signaling_NaN))
  {
    return std::isnan(x) | std::isnan(y);
  }

  /// <@method> vec2::is_finite
  /// <@requires> the value type is a floating point that can represent infinity
  ///	<@brief> True if all values in vector are finite.
  [[nodiscard]] inline bool is_finite() const
    requires std::numeric_limits<value_type>::has_infinity
  {
    return std::isfinite(x) && std::isfinite(y);
  }

  /// <@section> Modification methods.

  /// <@method> vec2::flip
  /// <@requires> ArithSigned_ or boolean value type.
  ///	<@brief> Negate vector values, equivalent to unary - operator; or ! for
  /// booleans.
  constexpr inline void flip()
    requires std::same_as<bool, value_type> || ArithSigned_<value_type>
  {
    __CXIF(std::same_as<bool, value_type>) {
      x = !x;
      y = !y;
    }
    else {
      x = -x;
      y = -y;
    }
  }

  /// <@method> vec2::flip_x
  /// <@requires> Signed arithmetic or boolean value type.
  ///	<@brief> Negate x value.
  constexpr inline void flip_x()
    requires std::same_as<bool, value_type> || ArithSigned_<value_type>
  {__CXIF(std::same_as<bool, value_type>){x = !x;
} else {
  x = -x;
}
};  // namespace graphics

/// <@method> vec2::flip_y
/// <@requires> Signed arithmetic or boolean value type.
///	<@brief> Negate y value.
constexpr inline void flip_y()
  requires std::same_as<bool, value_type> || ArithSigned_<value_type>
{__CXIF(std::same_as<bool, value_type>){y = !y;
}
else {
  y = -y;
}
}
;

/// <@method> vec2::clamp
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Clamp this vector's values to length() = passed value.
constexpr inline const vec2<value_type>& clamp(value_type max_length)
  requires require::ArithNoBool_<value_type>
{
  auto this_length = length();
  if (this_length > value_type() && max_length < this_length) {
    operator/=(this_length);
    operator*=(max_length);
  }
  return *this;
};

/// <@method> vec2::stretch
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Set this vector's values to fit into length() = passed value.
constexpr inline const vec2<value_type>& stretch(value_type new_length)
  requires require::ArithNoBool_<value_type>
{
  auto this_length = length();
  if (this_length != value_type() && new_length != value_type()) {
    operator/=(this_length);
    operator*=(new_length);
    return *this;
  }
  return *this;
};

/// <@method> vec2::normalize
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Stretch this vector's values to length() = 1.
constexpr inline const vec2<value_type>& normalize()
  requires FloatingPoint_<value_type>
{
  if (length_squared() != value_type{}) {
    operator/=(length());
    return *this;
  }
  return *this;
};

/// <@method> vec2::step_to
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Step this vector with magnitude of passed length toward a
/// point.
/// <!in:vec2> Point on the 2d euclidean plane which to step towards
/// <!in:value_type> The maximum length of the step. Step length may be lower
/// when the distance is
///					 less than epsilon of value_type, or
/// less than or equal to the passed magnitude.
constexpr const vec2<value_type>& step_to(vec2<value_type> point,
                                          value_type magnitude)
  requires require::ArithNoBool_<value_type>
{
  auto& this_vec = *this;
  auto diff = point - this_vec;
  auto diff_length = diff.length();
  if (diff_length < std::numeric_limits<value_type>::epsilon() ||
      diff_length <= magnitude) {
    this_vec = point;
    return this_vec;
  } else {
    this_vec += diff / diff_length * magnitude;
    return this_vec;
  }
}

/// <@method> vec2::step
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Step in a direction with magnitude of passed length.
/// <!in:vec2> A normalized vector representing the direction in which to step
/// in.
/// <!in:value_type> The length of the step.
/// !TODO: add concept constraint to require a normalized vector
constexpr inline const vec2<value_type>& step(vec2<value_type> direction_normal,
                                              value_type magnitude)
  requires require::FloatingPoint_<value_type>
{
#ifdef __DEBUG_ARITHMETIC_LOGIC_ASSERT
  assert(direction_normal.is_normalized());
#endif
  operator+=(direction_normal* magnitude);
  return *this;
}

/// <@section> Comparison methods.

/// <@method> vec2::dot
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Dot product of this vector to another.
[[nodiscard]] constexpr inline value_type dot(
    const vec2<value_type>& other) const
  requires require::ArithNoBool_<value_type>
{
  return x * other.x + y * other.y;
}

/// <@method> vec2::cross
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Cross product of this vector to another.
[[nodiscard]] constexpr inline value_type cross(
    const vec2<value_type>& other) const
  requires require::ArithNoBool_<value_type>
{
  return x * other.y - y * other.x;
}

/// <@method> vec2::angle_to
/// <@requires> require::FloatingPoint_ value type
///	<@brief> The directed angle from this vector to another.
[[nodiscard]] constexpr inline value_type angle_to(
    const vec2<value_type>& other) const
  requires require::FloatingPoint_<value_type>
{
  return std::atan2(cross(other), dot(other));
}

/// <@method> vec2::angle_to_point
/// <@requires> require::FloatingPoint_ value type
///	<@brief> The angle required to rotate this vector towards the passed
/// point.
/// <!in:vec2> The point which will form the difference vector. Equivalent to
/// *this - other.
/// <!out:float_type> Angle between the difference vector and the x-axis.
[[nodiscard]] constexpr inline value_type angle_to_point(
    const vec2<value_type>& other) const
  requires require::FloatingPoint_<value_type>
{
  return std::atan2(y - other.y, x - other.x);
}

/// <@method> vec2::length_to_squared
/// <@requires> require::ArithNoBool_ value type
///	<@brief> The scalar distance squared between this vector and other.
[[nodiscard]] constexpr inline value_type length_to_squared(
    const vec2<value_type>& other) const
  requires require::ArithNoBool_<value_type>
{
  return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

/// <@method> vec2::length_to
/// <@requires> require::ArithNoBool_ value type
///	<@brief> The scalar distance between this vector and other.
/// <@note> Prefer length_to_squared when possible to avoid square root
/// operation.
[[nodiscard]] constexpr inline value_type length_to(
    const vec2<value_type>& other) const
  requires require::ArithNoBool_<value_type>
{
  return std::sqrt(length_to_squared(other));
}

/// <@section> Analog and related vectors.

/// <@method> vec2::normalized
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get a vector with this vector's values, stretched to length()
///= 1.
[[nodiscard]] constexpr inline vec2<value_type> normalized() const
  requires gtl::require::FloatingPoint_<value_type>
{
  if (auto this_length = length_squared() != value_type()) {
    this_length = std::sqrt(this_length);
    return vec2<value_type>(x / this_length, y / this_length);
  } else {
    return vec2<value_type>(value_type(), value_type());
  }
}

/// <@method> vec2::direction_to
/// <@requires> require::FloatingPoint_ value type
///	<@brief> The normalized difference vector from this vector to other.
[[nodiscard]] constexpr inline vec2<value_type> direction_to(
    const vec2<value_type>& other) const
  requires require::FloatingPoint_<value_type>
{
  return vec2<value_type>(other.x - x, other.y - y).normalized();
}

/// <@method> vec2::clamped
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Get a vector with this vector's values, clamped to length() =
/// new_length.
[[nodiscard]] constexpr inline vec2<value_type> clamped(
    value_type new_length) const
  requires require::ArithNoBool_<value_type>
{
  value_type this_length = length();
  if (this_length > value_type() && new_length < this_length) {
    auto ret_vec = *this;  // Create a temp copy
    ret_vec /= (this_length);
    ret_vec *= (new_length);
    return ret_vec;
  }
  return *this;
};

/// <@method> vec2::abs
/// <@requires> signed arithmetic value type
[[nodiscard]] constexpr inline vec2<value_type> abs() const
  requires std::numeric_limits<value_type>::is_signed
{
  __CXIF(require::FloatingPoint_<value_type>) {
    return vec2<value_type>(std::fabs(x), std::fabs(y));
  }
  else {
    return vec2<value_type>(std::abs(x), std::abs(y));
  }
}

/// <@method> vec2::ceil
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get a vector with this vector's values, rounded up to the
/// nearest integer.
[[nodiscard]] constexpr inline vec2<value_type> ceil() const
  requires require::FloatingPoint_<value_type>
{
  return vec2<value_type>(std::ceil(x), std::ceil(y));
}

/// <@method> vec2::floor
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get a vector with this vector's values, rounded down to the
/// nearest integer.
[[nodiscard]] constexpr inline vec2<value_type> floor() const
  requires require::FloatingPoint_<value_type>
{
  return vec2<value_type>(std::floor(x), std::floor(y));
}

/// <@method> vec2::mod
/// <@requires> require::ArithNoBool_ value type
///	<@brief> Get the remainder of this vector divided by the denominator as
/// a vector.
/// <!in:vec2> A vector with the respective x and y denominators
[[nodiscard]] constexpr inline vec2<value_type> mod(
    vec2<value_type> denominator) const
  requires require::ArithNoBool_<value_type>
{
  __CXIF(require::FloatingPoint_<value_type>) {
    return vec2<value_type>(std::fmod(x, denominator.x),
                            std::fmod(y, denominator.y));
  }
  else {
    return vec2<value_type>(x % denominator.x, y % denominator.y);
  }
}

/// <@method> vec2::slide
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get resulting vector of sliding this vector along a plane
/// normal.
[[nodiscard]] constexpr inline vec2<value_type> slide(
    vec2<value_type> plane_normal) const
  requires require::FloatingPoint_<value_type>
{
#ifdef __DEBUG_ARITHMETIC_LOGIC_ASSERT
  assert(plane_normal.is_normalized());
#endif
  return *this - plane_normal * dot(plane_normal);
}

/// <@method> vec2::reflect
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get resulting vector of reflecting this vector off of a plane
/// normal.
[[nodiscard]] constexpr inline vec2<value_type> reflect(
    vec2<value_type> plane_normal) const
  requires require::FloatingPoint_<value_type>
{
#ifdef __DEBUG_ARITHMETIC_LOGIC_ASSERT
  assert(plane_normal.is_normalized());
#endif
  return 2.0 - plane_normal * dot(plane_normal) - *this;
}

/// <@method> vec2::project
/// <@requires> require::FloatingPoint_ value type
///	<@brief> Get resulting vector of projecting this vector onto a plane
/// normal.
[[nodiscard]] constexpr inline vec2<value_type> project(
    vec2<value_type> other_normal) const
  requires require::FloatingPoint_<value_type>
{
#ifdef __DEBUG_ARITHMETIC_LOGIC_ASSERT
  assert(plane_normal.is_normalized());
#endif
  return other_normal * (dot(other_normal) / other_normal.length_squared());
}

/// <@method> vec2::sign
/// <@requires> signed arithmetic value type
///	<@brief> Get a boolean vector representing the signbit of this vector's
/// value. False is negative.
[[nodiscard]] constexpr inline vec2<bool> sign() const
  requires std::numeric_limits<value_type>::is_signed
{
  __CXIF(require::SignedIntegral_<value_type>) {  // For MSVC, std::signbit only
    // accepts float/double/long double
    return vec2<bool>(x > 0, y > 0);
  }
  else __CXIF(require::FloatingPoint_<value_type>) {
    return vec2<bool>(!std::signbit(x), !std::signbit(y));
  }
}

///\/////////////////////////////////////////////////////////////////////////////////////////////////
/// <@method> vec2::tangent
///	<@brief> Get the perpendicular vector of this vector.
///\/////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] constexpr inline vec2<value_type> tangent() const
  requires(require::ArithNoBool_<value_type> &&
           std::numeric_limits<value_type>::is_signed)
{
  return vec2<value_type>(y, -(x));
}
}
;  // end <@class:vec2> <@case:partial specialization for arithmetic types>

}  // end <@namespace:ppp::euclid>

namespace graphics {

template <typename T>
using vec2 = gfx::vec2<T>;

using Vec2b = vec2<bool>;
using Vec2i = vec2<int>;
using Vec2u = vec2<unsigned>;
using Vec2f = vec2<float>;
using Vec2d = vec2<double>;
using Size2 = vec2<std::size_t>;

}  // namespace graphics

#endif  // end PPP_VEC2_HPP