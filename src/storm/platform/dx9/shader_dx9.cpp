#include <storm/platform/dx9/shader_dx9.h>

#include <Cg/cgD3D9.h>

#include <storm/exception.h>

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
    switch( type ) {
    case Type::Vertex:
        return ::cgD3D9GetLatestVertexProfile();
    case Type::Pixel:
        return ::cgD3D9GetLatestPixelProfile();
    default:
        throwInvalidArgument( "'type' is invalid" );
    }
}

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderDx9 >( sourceCode, type );
}

}