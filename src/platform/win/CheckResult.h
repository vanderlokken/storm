#pragma once

#include "Exception.h"

#define checkResult( result, call ) \
    if( result < 0 ) throwRuntimeError( call " has failed" );
