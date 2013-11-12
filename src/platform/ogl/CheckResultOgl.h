#pragma once

#include "ConstantsOgl.h"
#include "Exception.h"
#include "FunctionsOgl.h"

#define checkResult( call ) \
    if( ::glGetError() != GL_NO_ERROR ) throwRuntimeError( call " has failed" );
