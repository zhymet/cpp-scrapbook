#pragma once
//
// Created by zbook15 on 8/5/2020.
//

#ifndef PPP_TRANSFORM2_HPP
#define PPP_TRANSFORM2_HPP

#include <array>
#include <cmath> // std::sin , std::cos
#include <numbers> //

#include "requires.hpp"
#include "vec2.hpp"

//namespace gtl {
//     ///<@class> transform2f
//     ///<@brief> A 3x3 float matrix to be used for transformations in euclidean 2-space.
//    template<req::FloatingPoint_ FloatT>
//    struct transform2f {
//        using value_type = vec2<FloatT>;
//        using data_size = std::integral_constant<std::size_t, 3u>;
//
//        std::array<value_type, data_size::value> data_;
//
//        __CXIN vec2<value_type> get_origin() { return vec2<value_type>(data_[Z1],data_[Z2]);}
//        __CXIN vec2<value_type> get_scale() { return vec2<value_type>(data_[X1],data_[Y2]);}
//
//        __CX vec2<value_type> apply(vec2<value_type> point){
//
//        }
//
//        transform2f() {
//            data_[X1] = static_cast<value_type>(1);
//            data_[Y2] = static_cast<value_type>(1);
//            data_[Z3] = static_cast<value_type>(1);
//        }
//
//        // Add to current translation, return ref to this transform
//        __CXIN transform2f &translate(value_type x, value_type y) {
//            data_[Z1] += x;
//            data_[Z2] += y;
//            return *this;
//        }
//
//        // Create a copy and add to current translation, return copy by value
//        __CXIN transform2f translated(value_type x, value_type y) {
//            auto ret_val = *this;
//            ret_val.data_[Z1] += x;
//            ret_val.data_[Z2] += y;
//            return ret_val;
//        }
//
//        // Set current translation, return ref to this transform
//        __CXIN transform2f &set_translate(value_type x, value_type y) {
//            data_[Z1] = x;
//            data_[Z2] = y;
//            return *this;
//        }
//
//        // Create a copy and set current translation, return copy by value
//        __CXIN transform2f &set_translated(value_type x, value_type y) {
//            auto ret_val = *this;
//            data_[Z1] = x;
//            data_[Z2] = y;
//            return ret_val;
//        }
//
//
//        // Add to current translation, return ref to this transform
//        __CXIN transform2f & scale(value_type x, value_type y) {
//            data_[X1] *= x;
//            data_[Y2] *= y;
//            return *this;
//        }
//
//        __CXIN transform2f scaled(value_type x, value_type y) {
//            auto ret_val = *this;
//            ret_val.data_[X1] += x;
//            ret_val.data_[Y2] += y;
//            return *this;
//        }
//
//        __CXIN transform2f &set_scale(value_type x, value_type y) {
//            data_[X1] = x;
//            data_[Y2] = y;
//            return *this;
//        }
//
//        __CXIN transform2f set_scaled(value_type x, value_type y) {
//            auto ret_val = *this;
//            ret_val.data_[X1] = x;
//            ret_val.data_[Y2] = y;
//            return *this;
//        }
//
//        // Add to current rotation, return ref to this transform
//        __CX transform2f &rotate(value_type angle_rad) {
//            value_type cos_theta = std::cos(angle_rad);
//            value_type sin_theta = std::cos(angle_rad);
//
//            data_[X1] += cos_theta;
//            data_[Y1] += sin_theta;
//            data_[X2] += (-sin_theta);
//            data_[Y2] += cos_theta;
//
//            return *this;
//        }
//
//        __CXIN transform2f & shear(value_type x, value_type y) {
//            data_[1u] += x;
//            data_[3u] += y;
//            return *this;
//        }
//
//        __CXIN transform2f & reflect_origin(){
//            data_[0u] = (-data_[0u]);
//            data_[4u] = (-data_[0u]);
//        }
//
//        __CXIN transform2f & reflect_x(){
//            data_[4u] = (-data_[0u]);
//        }
//
//        __CXIN transform2f & reflect_y(){
//            data_[0u] = (-data_[0u]);
//        }
//
//    };
//}

#endif //PPP_TRANSFORM2_HPP
