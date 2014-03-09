#pragma once

#include <storm/exception.h>

#define throwRuntimeError( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwNotImplemented() \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, "Not implemented" )

namespace {

#ifndef NDEBUG
    bool isDebug() { return true; }
#else
    bool isDebug() { return false; }
#endif

}

#ifndef NDEBUG
    #define storm_assert_default_message( expression ) \
        if( expression ) { } else { \
            throwRuntimeError( "Assertion failed: " #expression ); }

    #define storm_assert_custom_message( expression, message ) \
        if( expression ) { } else { \
            throwRuntimeError( "Assertion failed: " message ); }

    #define storm_assert_select_macro( ignored1, ignored2, macro, ... ) macro

    #define storm_expand( argument ) argument // For compatibility with Visual C++

    #define storm_assert( ... ) storm_expand( storm_assert_select_macro(__VA_ARGS__, storm_assert_custom_message, storm_assert_default_message)(__VA_ARGS__) )

#else
    #define storm_assert( ... )
#endif

// The following macro uses "isDebug" function to supress a warning about
// constant conditional expressions
#define storm_assert_unreachable( message ) storm_assert( isDebug(), message )
