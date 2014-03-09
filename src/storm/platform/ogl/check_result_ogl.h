#pragma once

#include <storm/platform/ogl/api_ogl.h>
#include <storm/throw_exception.h>

#ifndef NDEBUG
#define checkResult( call ) \
    if( ::glGetError() != GL_NO_ERROR ) throwRuntimeError( call " has failed" );
#else
#define checkResult( call )
#endif
