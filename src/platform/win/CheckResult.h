#ifndef storm_CheckResult_h
#define storm_CheckResult_h

#include "Exception.h"

#define checkResult( result, call )                                 \
    if( result < 0 ) {                                              \
        throwException< std::runtime_error >(                       \
            __FILE__, __LINE__, __FUNCTION__, call " has failed" ); \
    }


#endif