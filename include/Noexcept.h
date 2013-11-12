#pragma once

#define _ALLOW_KEYWORD_MACROS
#define noexcept

#if defined( __clang__ )
#   undef noexcept
#endif

#if defined( __GNUC__ ) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || (__GNUC__ > 4))
#   undef noexcept
#endif
