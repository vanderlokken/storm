#ifndef storm_CheckResultOgl_h
#define storm_CheckResultOgl_h

#include "ConstantsOgl.h"
#include "Exception.h"
#include "FunctionsOgl.h"

#define checkResult( call ) \
    if( ::glGetError() != GL_NO_ERROR ) throwRuntimeError( call " has failed" );

#endif
