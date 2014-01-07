#pragma once

#if defined( _MSC_VER ) && ( _MSC_VER <= 1800 )
#   define _ALLOW_KEYWORD_MACROS
#endif

#define noexcept

#if defined( __clang__ )
#   undef noexcept
#endif

#if defined( __GNUC__ ) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || (__GNUC__ > 4))
#   undef noexcept
#endif
