#include <storm/platform/ogl/shader_ogl.h>

#include <storm/platform/ogl/api_ogl.h>

#define CGGL_NO_OPENGL
#include <Cg/cgGL.h>

#include <storm/exception.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/texture_ogl.h>

namespace storm {

// ----------------------------------------------------------------------------
//  ShaderOgl
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
//  Shader::Uniform
// ----------------------------------------------------------------------------

void Shader::Uniform::setValue( Texture::Pointer texture ) {
    ::cgGLSetTextureParameter( static_cast<CGparameter>(_identifier),
        std::static_pointer_cast<TextureOgl>(texture)->getHandle() );
    return;
}

// ----------------------------------------------------------------------------
//  Shader
// ----------------------------------------------------------------------------

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
