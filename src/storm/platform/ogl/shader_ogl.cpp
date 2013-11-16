#include <storm/platform/ogl/shader_ogl.h>

#include <Cg/cgGL.h>

#include <storm/exception.h>

namespace storm {

ShaderOgl::ShaderOgl( const std::string &sourceCode, Type type )
    : ShaderCg( selectCompilerArguments(sourceCode, type), type )
{
    ::cgGLLoadProgram( _program );
    checkCgError( "::cgGLLoadProgram" );
}

ShaderCg::CompilerArguments ShaderOgl::selectCompilerArguments(
    const std::string &sourceCode, Type type )
{
    CompilerArguments compilerArguments;
    compilerArguments.sourceCode = sourceCode.c_str();
    compilerArguments.profile = selectProfile( type );
    compilerArguments.compilerOptions =
        ::cgGLGetOptimalOptions( compilerArguments.profile );
    return compilerArguments;
}

CGprofile ShaderOgl::selectProfile( Type type ) {
    switch( type ) {
    case Type::Vertex:
        return ::cgGLGetLatestProfile( CG_GL_VERTEX );
    case Type::Pixel:
        return ::cgGLGetLatestProfile( CG_GL_FRAGMENT );
    default:
        throwInvalidArgument( "'type' is invalid" );
    }
}

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
