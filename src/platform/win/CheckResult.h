#ifndef storm_CheckResult_h
#define storm_CheckResult_h

#include "Exception.h"

#define checkResult( result, call ) \
    if( result < 0 ) throwRuntimeError( call " has failed" );

#endif
