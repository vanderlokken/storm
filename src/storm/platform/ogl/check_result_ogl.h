#pragma once

#include <storm/exception.h>
#include <storm/platform/ogl/constants_ogl.h>
#include <storm/platform/ogl/functions_ogl.h>

#define checkResult( call ) \
    if( ::glGetError() != GL_NO_ERROR ) throwRuntimeError( call " has failed" );
