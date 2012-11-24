#ifndef storm_Noexcept_h
#define storm_Noexcept_h

#if defined( __clang__ )
#   define STORM_NOEXCEPT_SUPPORT
#endif

#if defined( __GNUC__ ) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || (__GNUC__ > 4))
#   define STORM_NOEXCEPT_SUPPORT
#endif

#if !defined( STORM_NOEXCEPT_SUPPORT )
#   define noexcept throw()
#endif

#endif