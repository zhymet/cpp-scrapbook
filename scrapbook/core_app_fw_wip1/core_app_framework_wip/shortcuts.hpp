///
/// <@author> Anton Yashchenko (bigteeny.com)
/// <@date> 8/25/2020.
/// <@file> shurtcuts.hpp
/// <@module> gtl
/// <@brief> Preprocessor definitions for shorthand notations of basic C++ language keywords, all prefaces with a double underscore.


#ifndef GTL_HEADGUARD_shortcuts_hpp
#define GTL_HEADGUARD_shortcuts_hpp

#define __S static
#define __IN inline
#define __CX constexpr
#define __SIN static inline
#define __CXIN constexpr inline
#define __CXSIN constexpr static inline
#define __CXS constexpr static

//#define __CINIT constinit
#define __CEVAL consteval

#define __CXIF if constexpr

#define __T typename
#define __CASE template
#define __CASET template<typename T>
#define __CASEF template<>

#endif // GTL_HEADGUARD_define_shortcuts_hpp
