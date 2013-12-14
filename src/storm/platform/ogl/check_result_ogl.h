#pragma once

#include <storm/exception.h>
#include <storm/platform/ogl/api_ogl.h>

#define checkResult( call ) \
    if( ::glGetError() != GL_NO_ERROR ) throwRuntimeError( call " has failed" );
