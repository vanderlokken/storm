#pragma once

#include <storm/exception.h>

#define throwRuntimeError( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwLogicError( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwInvalidArgument( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwNotImplemented() \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, "Not implemented" )
