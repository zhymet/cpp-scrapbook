#pragma once
#include <type_traits>
#include <limits>
#include <cmath>

#include "shortcuts.hpp"

///< @method: is_approx
///< @brief: Determines whether two arithmetic values are equal within an error range defined by a
///<		 maximum and relative epsilon value.
__CASET requires std::is_arithmetic_v<T>
__CXSIN bool is_approx(T first, T second, T max_epsilon = std::numeric_limits<T>::epsilon()) {
    auto difference = std::fabs(first - second);
    if (difference <= max_epsilon)
        return true; // numbers near zero or wider error range
    return difference <= (std::fabs(first) < std::fabs(second) ? second : first) * std::numeric_limits<T>::epsilon();
}