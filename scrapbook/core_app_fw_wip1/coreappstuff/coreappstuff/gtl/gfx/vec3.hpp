///\/////////////////////////////////////////////////////////////////////////////////////////////////
/// <@header> vec3.hpp
/// <@author> Anton Yashchenko
/// <@updated> 8/4/2020 10:10:53 PM
/// <@brief> Generic 2 dimensional vector
///\/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PPP_VEC3_HPP
#define PPP_VEC3_HPP

#include <utility>
#include <cmath>
#include <type_traits>
#include <limits>
#include <numbers>

#include "../core/shortcuts.hpp"
#include "../core/requires.hpp"
#include "../core/fmath.hpp" // is_approx

namespace gtl::gfx {

    ///\<@class> vec3
    /// <@case> invalid base
    /// <@brief> 3 dimensional euclidean vector.
    __CASET
        struct vec3 {
        __FALSE_TYPE_ERROR(T, "Vec3 : Invalid template parameter T specialization");
    };

    /// <@case> partial specialization for trivial objects
    /// <@requires> value_type is a TrivialObject_
    /// <@brief> 3 dimensional euclidean vector plain old data struct.
    __CASET requires req::TrivialObject_<T>
        struct vec3<T> {
        using value_type = T;
        using float_type = typename req::float_type_from_any_type<value_type>;
        value_type x;
        value_type y;
        value_type z;

        constexpr vec3() = default;

        constexpr vec3(value_type x, value_type y, value_type z = 0.f) : x(x), y(y), z(z) {}
    };

    /// <@case> partial specialization for arithmetic types
    /// <@requires> value_type is an arithmetic type
    /// <@brief> 3 dimensional euclidean vector struct with utility methods for arithmetic types.
    __CASET requires std::is_arithmetic_v<T>
        struct vec3<T> {
        using value_type = T;
        using size_type = T;
        using float_type = typename ppp::deduce::float_type_from_any_type<value_type>;

        value_type x;
        value_type y;
        value_type z;

        constexpr vec3() = default;

        constexpr vec3(value_type x, value_type y, value_type z = 0.f) : x(x), y(y), z(z) {}

        /// <@section> Static constant convenience vectors.

                /// <@method> vec3::epsilon
                /// <@brief> The smallest possible difference between two values of this type.
        __CXSIN vec3<value_type> epsilon() {
            return vec3<value_type>(std::numeric_limits<value_type>::epsilon(),
                std::numeric_limits<value_type>::epsilon(),
                std::numeric_limits<value_type>::epsilon());
        }

        /// <@method> vec3::zero
        /// <@brief> The euclidean 2-space point of origin, zero vector.
        __CXSIN vec3<value_type> zero() {
            return vec3<value_type>(value_type(), value_type(), value_type());
        }

        /// <@method> vec3::min
        /// <@brief> A vector with the lowest finite values x and y,such that there is no other
        ///    		 finite value z where z < x || z < y.
        __CXSIN vec3<value_type> min() {
            return vec3<value_type>(std::numeric_limits<value_type>::lowest(),
                std::numeric_limits<value_type>::lowest(),
                std::numeric_limits<value_type>::lowest()
                );
        }

        /// <@method> vec3::max
        /// <@brief> A vector with both values set to the largest finite values of the stored type.
        __CXSIN vec3<value_type> max() {
            return vec3<value_type>(std::numeric_limits<value_type>::max()
                , std::numeric_limits<value_type>::max()
                , std::numeric_limits<value_type>::max()
                );
        }

        /// <@method> vec3::inf
        /// <@requires> Floating_ value type.
        /// <@brief> A vector with both values set to positive infinity.
        __CXSIN vec3<value_type> inf() requires std::numeric_limits<T>::has_infinity{
            return vec3<value_type>(std::numeric_limits<value_type>::infinity(),
                                    std::numeric_limits<value_type>::infinity(),
                                    std::numeric_limits<value_type>::infinity()
            );
        }

            /// <@method> vec3::nan
            /// <@requires> FloatingSafe_ value type.
            /// <@brief> A vector with both values set to quiet NaN floating point numbers.
            __CXSIN vec3<value_type> nan() requires std::numeric_limits<T>::has_quiet_NaN{
                return vec3<value_type>(std::numeric_limits<value_type>::quiet_NaN(),
                                        std::numeric_limits<value_type>::quiet_NaN(),
                                        std::numeric_limits<value_type>::quiet_NaN()
                );
        }

            /// <@method> vec3::denorm_min
            /// <@brief> A vector with both values set to the smallest positive subnormal value.
            __CXSIN vec3<value_type> denorm_min() requires (std::numeric_limits<T>::has_denorm == std::denorm_present) {
            return vec3<value_type>(std::numeric_limits<value_type>::denorm_min(),
                std::numeric_limits<value_type>::denorm_min(),
                std::numeric_limits<value_type>::denorm_min()
                );
        }

        /// <@section> Equality operators.

                /// <@operator> ==(vec3)
                /// <@brief> True if x, y and z values are equal to their respective value in the passed vector.
        __CXIN bool operator==(const vec3<value_type>& rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        /// <@operator> !=(vec3)
        /// <@brief> True if any of x or y  or z values are not equal to their respective
        ///			 value in the passed vector.
        __CXIN bool operator!=(const vec3<value_type>& rhs) const {
            return x != rhs.x || y != rhs.y || z != rhs.z;
        }

        /// <@operator> ==(value_type)
        /// <@brief> True if both the x, y and z values are equal to the passed value.
        __CXIN bool operator==(const value_type& rhs) const {
            return x == rhs && y == rhs && z == rhs;
        }

        /// <@operator> !=(value_type)
        /// <@brief> True if either the x, y or z value is not equal to the passed value.
        __CXIN bool operator!=(const value_type& rhs) const {
            return x != rhs.x || y != rhs.y || z != rhs.z;
        }

        /// <@section> Binary operators.

        __CXIN vec3<value_type> operator*(vec3<value_type>&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x * std::move(rhs.x), y * std::move(rhs.y), z * std::move(rhs.z));
        }

        __CXIN vec3<value_type> operator/(vec3<value_type>&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x / std::move(rhs.x), y / std::move(rhs.y), z / std::move(rhs.z));
        }

        __CXIN vec3<value_type> operator+(vec3<value_type>&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x + std::move(rhs.x), y + std::move(rhs.y), z + std::move(rhs.z));
        }

        __CXIN vec3<value_type> operator-(vec3<value_type>&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x - std::move(rhs.x), y - std::move(rhs.y), z - std::move(rhs.z));
        }


        __CXIN vec3<value_type> operator*(value_type&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x * rhs, y * rhs, z * std::move(rhs));
        }

        __CXIN vec3<value_type> operator/(value_type&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x / rhs, y / rhs, z / std::move(rhs));
        }

        __CXIN vec3<value_type> operator+(value_type&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x + rhs, y + rhs, z + std::move(rhs));
        }

        __CXIN vec3<value_type> operator-(value_type&& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x - rhs, y - rhs, z - std::move(rhs));
        }


        __CXIN void operator*=(vec3<value_type>&& rhs) requires ArithNoBool_<value_type> {
            x *= std::move(rhs.x);
            y *= std::move(rhs.y);
            z *= std::move(rhs.z);
        }

        __CXIN void operator/=(vec3<value_type>&& rhs) requires ArithNoBool_<value_type> {
            x /= std::move(rhs.x);
            y /= std::move(rhs.y);
            z /= std::move(rhs.z);
        }

        __CXIN void operator+=(vec3<value_type>&& rhs) requires ArithNoBool_<value_type> {
            x += std::move(rhs.x);
            y += std::move(rhs.y);
            z += std::move(rhs.z);
        }

        __CXIN void operator-=(vec3<value_type>&& rhs) requires ArithNoBool_<value_type> {
            x -= std::move(rhs.x);
            y -= std::move(rhs.y);
            z -= std::move(rhs.z);
        }


        __CXIN void operator*=(value_type&& rhs) requires ArithNoBool_<value_type> {
            x *= rhs;
            y *= rhs;
            z *= std::move(rhs);
        }

        __CXIN void operator/=(value_type&& rhs) requires ArithNoBool_<value_type> {
            x *= rhs;
            y *= rhs;
            z *= std::move(rhs);
        }

        __CXIN void operator+=(value_type&& rhs) requires ArithNoBool_<value_type> {
            x += rhs;
            y += rhs;
            z *= std::move(rhs);
        }

        __CXIN void operator-=(value_type&& rhs) requires ArithNoBool_<value_type> {
            x -= rhs;
            y -= rhs;
            z *= std::move(rhs);
        }

        /// <@section> Copy operators.

        __CXIN vec3<value_type> operator*(const vec3<value_type>& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x * rhs.x, y * rhs.y, z * rhs.z);
        }

        __CXIN vec3<value_type> operator/(const vec3<value_type>& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x / rhs.x, y / rhs.y, z / rhs.z);
        }

        __CXIN vec3<value_type> operator+(const vec3<value_type>& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        __CXIN vec3<value_type> operator-(const vec3<value_type>& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x - rhs.x, y - rhs.y, z - rhs.z);
        }


        __CXIN vec3<value_type> operator*(const value_type& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x * rhs, y * rhs, z * rhs);
        }

        __CXIN vec3<value_type> operator/(const value_type& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x / rhs, y / rhs, z / rhs);
        }

        __CXIN vec3<value_type> operator+(const value_type& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x + rhs, y + rhs, z + rhs);
        }

        __CXIN vec3<value_type> operator-(const value_type& rhs) const requires ArithNoBool_<value_type> {
            return vec3<value_type>(x - rhs, y - rhs, z - rhs);
        }


        __CXIN void operator*=(const vec3<value_type>& rhs) requires ArithNoBool_<value_type> {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
        }

        __CXIN void operator/=(const vec3<value_type>& rhs) requires ArithNoBool_<value_type> {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
        }

        __CXIN void operator+=(const vec3<value_type>& rhs) requires ArithNoBool_<value_type> {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
        }

        __CXIN void operator-=(const vec3<value_type>& rhs) requires ArithNoBool_<value_type> {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
        }


        __CXIN void operator*=(const value_type& rhs) requires ArithNoBool_<value_type> {
            x *= rhs;
            y *= rhs;
            z *= rhs;
        }

        __CXIN void operator/=(const value_type& rhs) requires ArithNoBool_<value_type> {
            x *= rhs;
            y *= rhs;
            z *= rhs;
        }

        __CXIN void operator+=(const value_type& rhs) requires ArithNoBool_<value_type> {
            x += rhs;
            y += rhs;
            z *= rhs;
        }

        __CXIN void operator-=(const value_type& rhs) requires ArithNoBool_<value_type> {
            x -= rhs;
            y -= rhs;
            z *= rhs;
        }

        /// <@section> Unary operators.

        __CXIN vec3<value_type> operator-() const {
            __CXIF(std::same_as<bool, value_type>) {
                return vec3<value_type>((!x), (!y), (!z));
            }
 else {
 return vec3<value_type>(-(x), -(y), -(z));
            }
        }

        /// <@section> Vector properties.

                /// <@method> vec3::length_squared
                /// <@requires> ArithNoBool_ value type.
        [[nodiscard]] __CXIN value_type length_squared() const requires ArithNoBool_<value_type> {
            return x * x + y * y + z * z;
        }

        /// <@method> vec3::length
        /// <@requires> ArithNoBool_ value type.
        [[nodiscard]] __CXIN value_type length() const requires ArithNoBool_<value_type> {
            return static_cast<value_type>(std::sqrt(x * x + y * y + z * z));
        }

        /// <@method> vec3::is_normalized
        ///	<@brief> True if the length_squared() is equal to 1 within epsilon range.
        [[nodiscard]] __CXIN bool is_normalized() const {
            return is_approx(length_squared(), static_cast<value_type>(1));
        }

        /// <@method> vec3::dot
        /// <@requires> ArithNoBool_ value type
        ///	<@brief> Dot product of this vector to another.
        [[nodiscard]] __CXIN value_type dot(const vec3<value_type>& other) const requires ArithNoBool_<value_type> {
            return x * other.x + y * other.y + z * other.z;
        }

        /// <@method> vec2::cross
        /// <@requires> ArithNoBool_ value type
        ///	<@brief> Cross product of this vector to another.
        [[nodiscard]] __CXIN vec3<value_type> cross(const vec3<value_type>& other) const
            requires ArithNoBool_<value_type> {
            /// <@source> https://www.mathsisfun.com/algebra/vectors-cross-product.html
            return vec3<value_type>(y * other.z - z * other.y
                , z * other.x - x * other.z
                , x * other.y - y * other.x
                );
        }

    }; // end class vec3

} // end namespace ppp::euclid

namespace gtl {

    template<typename T>
    using vec3 = gfx::vec3<T>;

    using Vec3b = vec3<bool>;
    using Vec3i = vec3<int>;
    using Vec3u = vec3<unsigned>;
    using Vec3f = vec3<float>;
    using Vec3d = vec3<double>;

} // end namespace ppp

#endif // end PPP_VEC3_HPP
