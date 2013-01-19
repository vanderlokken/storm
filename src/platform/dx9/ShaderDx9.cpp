#include "ShaderDx9.h"

#include <Cg/cgD3D9.h>

#include "Exception.h"

namespace storm {

ShaderDx9::ShaderDx9( const std::string &sourceCode, Type type )
    : ShaderCg( type, selectProfile(type), sourceCode, selectCompilerOptions(type) )
{
    const CGbool parameterShadowing = CG_FALSE;
    const DWORD assemblerFlags = 0;

    ::cgD3D9LoadProgram( _program, parameterShadowing, assemblerFlags );
    checkCgError( "::cgD3D9LoadProgram" );

    return;
}

CGprofile ShaderDx9::selectProfile( Type type ) {
    CGprofile result;

    switch( type ) {
    case TypeVertex:
        result = ::cgD3D9GetLatestVertexProfile();
        break;

    case TypePixel:
        result = ::cgD3D9GetLatestPixelProfile();
        break;

    default:
        throwInvalidArgument( "'type' is invalid" );
    }

    return result;
}

const char** ShaderDx9::selectCompilerOptions( Type type ) {
    return ::cgD3D9GetOptimalOptions( selectProfile(type) );
}

std::shared_ptr< Shader > Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderDx9 >( sourceCode, type );
}

}