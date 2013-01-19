#include "ShaderOgl.h"

#include <Cg/cgGL.h>

#include "Exception.h"

namespace storm {

ShaderOgl::ShaderOgl( const std::string &sourceCode, Type type )
    : ShaderCg( type, selectProfile(type), sourceCode, selectCompilerOptions(type) )
{
    ::cgGLLoadProgram( _program );
    checkCgError( "::cgGLLoadProgram" );

    return;
}

CGprofile ShaderOgl::selectProfile( Type type ) {
    CGprofile result;

    switch( type ) {
    case TypeVertex:
        result = ::cgGLGetLatestProfile( CG_GL_VERTEX );
        break;

    case TypePixel:
        result = ::cgGLGetLatestProfile( CG_GL_FRAGMENT );
        break;

    default:
        throwInvalidArgument( "'type' is invalid" );
    }

    return result;
}

const char** ShaderOgl::selectCompilerOptions( Type type ) {
    return ::cgGLGetContextOptimalOptions( getCgContext(), selectProfile(type) );
}

std::shared_ptr< Shader > Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
