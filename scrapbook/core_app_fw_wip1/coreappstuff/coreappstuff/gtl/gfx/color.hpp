#pragma once
#ifndef PPP_COLOR_HPP
#define PPP_COLOR_HPP
///\/////////////////////////////////////////////////////////////////////////////////////////////////
/// <@header> color
/// <@author> Anton Yashchenko
/// <@updated> 7/24/2020 2:43:03 AM
/// <@brief>
///\/////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath> // std::signbit
#include <algorithm> // std::min , std::max
#include <string>
#include <iomanip>
#include <sstream>
#include <cassert>

#include "../core/shortcuts.hpp"

namespace gtl::gfx {

    struct color_limits {
        using value_type = size_t;
        using type = color_limits;
        __CXS value_type max = 16777216u; // maximum number of colors on a computer screen
    };

    // fwd declaration
    struct Rgb;
    struct Rgb8;
    struct Hsl;
    struct Hex;

    /// <@class> Rgb
    /// <@brief> Color with red, green and blue values stored as floats ranging from 0.f to 1.f.
    struct Rgb {
        float r;
        float g;
        float b;

        __CX Rgb() : r(0.f), g(0.f), b(0.f) {}

        __CX Rgb(float r, float g, float b) : r(r), g(g), b(b) {
            assert((r <= 1.f) && (r >= 0.f)
                && "Rgb::Rgb(float,float,float) : r value must be less-equal than one and greater-equal than zero"
            );
            assert((g <= 1.f) && (g >= 0.f)
                && "Rgb::Rgb(float,float,float) : g value must be less-equal than one and greater-equal than zero"
            );
            assert((b <= 1.f) && (b >= 0.f)
                && "Rgb::Rgb(float,float,float) : b value must be less-equal than one and greater-equal than zero"
            );
        }

        __CXIN Rgb8 to_rgb8();
        __CX Hsl to_hsl();
        std::string hex_str();
        __CXIN int hex_val();

    };

    /// <@class> Rgb8
    /// <@brief> Color with red, green and blue values stored as unsigned char ranging from 0 to 255.
    struct  Rgb8 {
        unsigned char r;
        unsigned char g;
        unsigned char b;

        __CX Rgb8() : r(0u), g(0u), b(0u) {}
        __CX Rgb8(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

        __CXIN Rgb to_rgb();
        __CX Hsl to_hsl();
        std::string hex_str();
        __CXIN int hex_val();
    };


    /// <@class> Hsl
    /// <@brief> Color with values stored as hue saturation and luminosity
    struct  Hsl {
        float hue;
        float saturation;
        float luminosity;

        __CX Hsl() : hue(0.f), saturation(0.f), luminosity(0.f) {}
        __CX Hsl(float h /* 0 -> 360 */, float s/* 0.f -> 1.0f */, float l/* 0.f -> 1.0f */)
            : hue(h), saturation(s), luminosity(l) {
            assert((h <= 360.f) && (h >= 0.f)
                && "Rgb::Rgb(float,float,float) : hue value must be less-equal than 360 and greater-equal than zero"
            );
            assert((s <= 1.f) && (s >= 0.f)
                && "Rgb::Rgb(float,float,float) : saturation value must be less-equal than one and greater-equal than zero"
            );
            assert((l <= 1.f) && (l >= 0.f)
                && "Rgb::Rgb(float,float,float) : luminosity value must be less-equal than one and greater-equal than zero"
            );
        }

        __CX Rgb to_rgb();
        __CX Rgb8 to_rgb8();
    };

    /// <@class> Hex
    /// <@brief> Color with values stored size ranging from 0 color_limits::max
    struct Hex {
        int value;

        __CX Hex() : value(0) {}
        __CX explicit Hex(int value) : value(value) {
            assert((value <= static_cast<int>(color_limits::max))
                && (value >= 0)
                && "Hex::Hex(int) : passed value must be less-equal than color_limits::max and greater-equal than zero"
            );
        }
        __CXIN Rgb to_rgb();
        __CXIN Rgb8 to_rgb8();
        __CX Hsl to_hsl();
        std::string to_str();
    };


} // end namespace ppp::color

#endif //PPP_COLOR_HPP