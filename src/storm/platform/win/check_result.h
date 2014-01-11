#pragma once

#include <storm/throw_exception.h>

#define checkResult( result, call ) \
    if( result < 0 ) throwRuntimeError( call " has failed" );
