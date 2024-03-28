/////\/////////////////////////////////////////////////////////////////////////////////////////////////
///// <@source> color
///// <@author> Anton Yashchenko
///// <@updated> 7/25/2020 3:45:05 PM
///// <@brief>
/////\/////////////////////////////////////////////////////////////////////////////////////////////////
//
//#include "color.hpp"
//
//namespace gtl::gfx {
//
//    __CXIN Rgb8 Rgb::to_rgb8() {
//        return Rgb8{ static_cast<unsigned char>(r * 255.f)
//                ,static_cast<unsigned char>(g * 255.f)
//                ,static_cast<unsigned char>(b * 255.f)
//        };
//    }
//
//    __CX Hsl Rgb::to_hsl() {
//        float h;
//        float s;
//        float l;
//        float max = std::max({ r, g, b });
//        float min = std::min({ r, g, b });
//
//        // Luminosity
//        l = (min + max) / 2.f;
//
//        // Saturation
//        if (max == min) {
//            s = 0.f;
//            h = 0.f;
//        }
//        else {
//            if (l < 0.5f) {
//                s = (max - min) / (max + min);
//            }
//            else if (l >= 0.5f) {
//                s = (max - min) / (2.f - max - min);
//            }
//        }
//
//        // Hue
//        if (max == r) {
//            h = (g - b) / (max - min);
//        }
//        else if (max == g) {
//            h = 2.f + (b - r) / (max - min);
//        }
//        else if (max == b) {
//            h = 4.f + (r - g) / (max - min);
//        }
//
//        h *= 60.f;
//
//        if (std::signbit(h))
//            h += 360.f;
//
//        return Hsl{ h, s, l };
//    } // end Rgb::to_hsl
//
//    std::string Rgb::hex_str() {
//        auto rgb = (static_cast<int>(r * 255) << 16)
//            | (static_cast<int>(g * 255) << 8)
//            | (static_cast<int>(b * 255));
//        std::ostringstream buffer;
//        buffer.flags(std::ios_base::hex | std::ios_base::left);
//        buffer << rgb;
//        return buffer.str();
//    }
//
//    __CXIN int Rgb::hex_val() {
//        return (static_cast<int>(r * 255) << 16)
//            | (static_cast<int>(g * 255) << 8)
//            | (static_cast<int>(b * 255));
//    }
//
//
//    __CXIN Rgb Rgb8::to_rgb() {
//        return Rgb{ static_cast<float>(r) / 255.f
//                ,static_cast<float>(g) / 255.f
//                ,static_cast<float>(b) / 255.f
//        };
//    }
//
//    __CX Hsl Rgb8::to_hsl() {
//        float r_f = static_cast<float>(r) / 255.f;
//        float g_f = static_cast<float>(g) / 255.f;
//        float b_f = static_cast<float>(b) / 255.f;
//
//        float h;
//        float s;
//        float l;
//        float max = std::max({ r_f, g_f, b_f });
//        float min = std::min({ r_f, g_f, b_f });
//
//        // Luminosity
//        l = (min + max) / 2.f;
//
//        // Saturation
//        if (max == min) {
//            s = 0.f;
//            h = 0.f;
//        }
//        else {
//            if (l < 0.5f) {
//                s = (max - min) / (max + min);
//            }
//            else if (l >= 0.5f) {
//                s = (max - min) / (2.f - max - min);
//            }
//        }
//
//        // Hue
//        if (max == r_f) {
//            h = (g_f - b_f) / (max - min);
//        }
//        else if (max == g_f) {
//            h = 2.f + (b_f - r_f) / (max - min);
//        }
//        else if (max == b_f) {
//            h = 4.f + (r_f - g_f) / (max - min);
//        }
//
//        h *= 60.f;
//
//        if (std::signbit(h))
//            h += 360.0;
//
//        return Hsl{ h, s, l };
//    } // end Rgb::to_hsl
//
//    std::string Rgb8::hex_str() {
//        auto rgb = (r << 16) | (g << 8) | b;
//        std::ostringstream buffer;
//        buffer.flags(std::ios_base::hex | std::ios_base::left);
//        buffer << rgb;
//        return buffer.str();
//    }
//
//    __CXIN int Rgb8::hex_val() {
//        return (r << 16) | (g << 8) | b;
//    }
//
//
//    __CX Rgb Hsl::to_rgb() {
//        //If there is no Saturation it means that it’s a shade of grey.
//        if (saturation == 0.f)
//        {
//            return { luminosity,luminosity,luminosity };
//        }
//
//        float t_1; // Intermediate Var 1
//        if (luminosity < 0.5f)
//            t_1 = luminosity * (1.f + saturation);
//        else if (luminosity >= 0.5f)
//            t_1 = luminosity + saturation - (luminosity * saturation);
//
//        float t_2 = (2.f * luminosity) - t_1;	// Intermediate Var 2
//        float t_h = hue / 360.f;				// 0.1 to 1.0 range Hue
//
//        float t_r = hue + (1.f / 3.f); //Red Temp
//        if (std::signbit(t_r))
//            t_r += 1.f;
//        if (t_r > 1.f)
//            t_r -= 1.f;
//
//        float t_g = hue; //Green Temp
//        if (std::signbit(t_g))
//            t_g += 1.f;
//        if (t_g > 1.f)
//            t_g -= 1.f;
//
//        float t_b = hue - (1.f / 3.f); //Blue Temp
//        if (std::signbit(t_b))
//            t_b += 1.f;
//        if (t_b > 1.f)
//            t_b -= 1.f;
//
//        float r; //Red Final
//        if ((t_r * 6.f) < 1.f)
//            r = t_2 + (t_1 - t_2) * 6 * t_r;
//        else if ((t_r * 2.f) < 1.f)
//            r = t_1;
//        else if ((t_r * 3.f) < 2.f)
//            r = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_r) * 6.f;
//        else
//            r = t_2;
//
//        float g; //Green Final
//        if ((t_g * 6.f) < 1.f)
//            g = t_2 + (t_1 - t_2) * 6 * t_g;
//        else if ((t_g * 2.f) < 1.f)
//            g = t_1;
//        else if ((t_g * 3.f) < 2.f)
//            g = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_g) * 6.f;
//        else
//            g = t_2;
//
//        float b;//Blue Final
//        if ((t_b * 6.f) < 1.f)
//            b = t_2 + (t_1 - t_2) * 6 * t_b;
//        else if ((t_b * 2.f) < 1.f)
//            b = t_1;
//        else if ((t_b * 3.f) < 2.f)
//            b = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_b) * 6.f;
//        else
//            b = t_2;
//
//        return Rgb{ r,g,b };
//    }
//
//    __CX Rgb8 Hsl::to_rgb8() {
//        //If there is no Saturation it means that it’s a shade of grey.
//        if (saturation == 0.f)
//        {
//            auto shade_val = static_cast<unsigned char>(luminosity * 255);
//            return { shade_val, shade_val, shade_val };
//        }
//
//        float t_1; // Intermediate Var 1
//        if (luminosity < 0.5f)
//            t_1 = luminosity * (1.f + saturation);
//        else if (luminosity >= 0.5f)
//            t_1 = luminosity + saturation - (luminosity * saturation);
//
//        float t_2 = (2.f * luminosity) - t_1;	// Intermediate Var 2
//        float t_h = hue / 360.f;				// 0.1 to 1.0 range Hue
//
//        float t_r = hue + (1.f / 3.f); //Red Temp
//        if (std::signbit(t_r))
//            t_r += 1.f;
//        if (t_r > 1.f)
//            t_r -= 1.f;
//
//        float t_g = hue; //Green Temp
//        if (std::signbit(t_g))
//            t_g += 1.f;
//        if (t_g > 1.f)
//            t_g -= 1.f;
//
//        float t_b = hue - (1.f / 3.f); //Blue Temp
//        if (std::signbit(t_b))
//            t_b += 1.f;
//        if (t_b > 1.f)
//            t_b -= 1.f;
//
//        float r; //Red Final
//        if ((t_r * 6.f) < 1.f)
//            r = t_2 + (t_1 - t_2) * 6 * t_r;
//        else if ((t_r * 2.f) < 1.f)
//            r = t_1;
//        else if ((t_r * 3.f) < 2.f)
//            r = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_r) * 6.f;
//        else
//            r = t_2;
//
//        float g; //Green Final
//        if ((t_g * 6.f) < 1.f)
//            g = t_2 + (t_1 - t_2) * 6 * t_g;
//        else if ((t_g * 2.f) < 1.f)
//            g = t_1;
//        else if ((t_g * 3.f) < 2.f)
//            g = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_g) * 6.f;
//        else
//            g = t_2;
//
//        float b;//Blue Final
//        if ((t_b * 6.f) < 1.f)
//            b = t_2 + (t_1 - t_2) * 6 * t_b;
//        else if ((t_b * 2.f) < 1.f)
//            b = t_1;
//        else if ((t_b * 3.f) < 2.f)
//            b = t_2 + (t_1 - t_2) * ((2.f / 3.f) - t_b) * 6.f;
//        else
//            b = t_2;
//
//
//        return Rgb8{ static_cast<unsigned char>(r * 255.f)
//                ,static_cast<unsigned char>(g * 255.f)
//                ,static_cast<unsigned char>(b * 255.f)
//        };
//    }
//
//
//    __CXIN Rgb Hex::to_rgb() {
//        return Rgb{ static_cast<float>(((value >> 16) & 0xFF)) / 255.f		// RR byte
//                , static_cast<float>(((value >> 8) & 0xFF)) / 255.f		// GG byte
//                , static_cast<float>(((value) & 0xFF)) / 255.f			// BB byte
//        };
//    };
//
//    __CXIN Rgb8 Hex::to_rgb8() {
//        return Rgb8{ static_cast<unsigned char>(((value >> 16) & 0xFF))  // RR byte
//                ,static_cast<unsigned char>(((value >> 8) & 0xFF))   // GG byte
//                ,static_cast<unsigned char>(((value) & 0xFF))        // BB byte
//        };
//    };
//
//    __CX Hsl Hex::to_hsl() {
//        float r_f = static_cast<float>(((value >> 16) & 0xFF)) / 255.f;
//        float g_f = static_cast<float>(((value >> 8) & 0xFF)) / 255.f;
//        float b_f = static_cast<float>(((value) & 0xFF)) / 255.f;
//
//        float h;
//        float s;
//        float l;
//        float max = std::max({ r_f, g_f, b_f });
//        float min = std::min({ r_f, g_f, b_f });
//
//        // Luminosity
//        l = (min + max) / 2.f;
//
//        // Saturation
//        if (max == min) {
//            s = 0.f;
//            h = 0.f;
//        }
//        else {
//            if (l < 0.5f) {
//                s = (max - min) / (max + min);
//            }
//            else if (l >= 0.5f) {
//                s = (max - min) / (2.f - max - min);
//            }
//        }
//
//        // Hue
//        if (max == r_f) {
//            h = (g_f - b_f) / (max - min);
//        }
//        else if (max == g_f) {
//            h = 2.f + (b_f - r_f) / (max - min);
//        }
//        else if (max == b_f) {
//            h = 4.f + (r_f - g_f) / (max - min);
//        }
//
//        h *= 60.f;
//
//        if (std::signbit(h))
//            h += 360.0;
//
//        return Hsl{ h, s, l };
//    };
//
//    std::string Hex::to_str() {
//        std::ostringstream buffer;
//        buffer.flags(std::ios_base::hex | std::ios_base::left);
//        buffer << value;
//        return buffer.str();
//    };
//
//}