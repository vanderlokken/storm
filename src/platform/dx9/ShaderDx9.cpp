#include "ShaderDx9.h"

#include <Cg/cgD3D9.h>

#include "Exception.h"

namespace storm {

ShaderDx9::ShaderDx9( const std::string &sourceCode, Type type )
    : ShaderCg( selectCompilerArguments(sourceCode, type), type )
{
    const CGbool parameterShadowing = CG_FALSE;
    const DWORD assemblerFlags = 0;

    ::cgD3D9LoadProgram( _program, parameterShadowing, assemblerFlags );
    checkCgError( "::cgD3D9LoadProgram" );
}

ShaderCg::CompilerArguments ShaderDx9::selectCompilerArguments(
    const std::string &sourceCode, Type type )
{
    CompilerArguments compilerArguments;
    compilerArguments.sourceCode = sourceCode.c_str();
    compilerArguments.profile = selectProfile( type );
    compilerArguments.compilerOptions =
        ::cgD3D9GetOptimalOptions( compilerArguments.profile );
    return compilerArguments;
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

std::shared_ptr< Shader > Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderDx9 >( sourceCode, type );
}

}