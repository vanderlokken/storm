#include <storm/platform/ogl/shader_ogl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

ProgramHandleOgl::ProgramHandleOgl(
    GLenum shaderType, const char *sourceCode )
{
    _handle = ::glCreateShaderProgramv( shaderType, 1, &sourceCode );
    checkResult( "::glCreateShaderProgramv" );
}

ProgramHandleOgl::~ProgramHandleOgl() {
    ::glDeleteProgram( _handle );
}

ShaderOgl::ShaderOgl( const std::string &sourceCode, Type type )
    : _type( type ), _handle( convertType(type), sourceCode.c_str() )
{
    auto getParameter = [this]( GLenum parameter ) {
        GLint value = 0;

        ::glGetProgramiv( _handle, parameter, &value );
        checkResult( "::glGetProgramiv" );

        return value;
    };

    if( getParameter(GL_LINK_STATUS) == GL_FALSE ) {
        std::string log( getParameter(GL_INFO_LOG_LENGTH), 0 );

        ::glGetProgramInfoLog( _handle, log.size(), nullptr, &log[0] );
        checkResult( "::glGetProgramInfoLog" );

        throwRuntimeError( "Shader compilation failed:\n" + log );
    }
}

Shader::Type ShaderOgl::getType() const noexcept {
    return _type;
}

Shader::Uniform ShaderOgl::getUniform( const std::string &identifier ) const {
    const GLint location =
        ::glGetUniformLocation( _handle, identifier.c_str() );
    checkResult( "::glGetUniformLocation" );

    if( location == -1 )
        throwRuntimeError( "Invalid uniform identifier" );

    return Uniform( reinterpret_cast<void*>(location),
        std::const_pointer_cast<ShaderOgl>(shared_from_this()) );
}

const ProgramHandleOgl& ShaderOgl::getHandle() const {
    return _handle;
}

GLenum ShaderOgl::convertType( Type type ) {
    switch( type ) {
    case Type::Vertex:
        return GL_VERTEX_SHADER;
    case Type::Pixel:
        return GL_FRAGMENT_SHADER;
    case Type::Geometry:
        return GL_GEOMETRY_SHADER;
    default:
        throwInvalidArgument( "'type' is invalid" );
    }
}

//  Shader::Uniform

Shader::Uniform::Uniform( void *identifier, Shader::Pointer shader )
    : _identifier( identifier ), _shader( shader )
{
}

#define _program std::static_pointer_cast< ShaderOgl >( _shader )->getHandle()
#define _location reinterpret_cast< GLint >( _identifier )

void Shader::Uniform::setValue( int value ) {
    ::glProgramUniform1i( _program, _location, value );
    checkResult( "::glProgramUniform1i" );
}

void Shader::Uniform::setValue( float value ) {
    ::glProgramUniform1f( _program, _location, value );
    checkResult( "::glProgramUniform1f" );
}

void Shader::Uniform::setValue( const Color &value ) {
    ::glProgramUniform4f(
        _program,
        _location,
        value.getNormalizedR(),
        value.getNormalizedG(),
        value.getNormalizedB(),
        value.getNormalizedA() );
    checkResult( "::glProgramUniform4f" );
}

void Shader::Uniform::setValue( const Vector &value ) {
    ::glProgramUniform3f(
        _program, _location, value.getX(), value.getY(), value.getZ() );
    checkResult( "::glProgramUniform3f" );
}

void Shader::Uniform::setValue( const Matrix &value ) {
    const GLsizei count = 1;
    const GLboolean transpose = true;

    ::glProgramUniformMatrix4fv(
        _program, _location, count, transpose, value[0] );
    checkResult( "::glProgramUniformMatrix4fv" );
}

void Shader::Uniform::setValue( const std::vector<Matrix> &matrices ) {
    const GLsizei count = matrices.size();
    const GLboolean transpose = true;

    ::glProgramUniformMatrix4fv(
        _program, _location, count, transpose, matrices.front()[0] );
    checkResult( "::glProgramUniformMatrix4fv" );
}

#undef _program
#undef _location

void Shader::Uniform::setValue( Texture::Pointer texture ) {
    throwNotImplemented();
}

void Shader::Uniform::setValue( Sampler::Pointer sampler ) {
    throwNotImplemented();
}

// Shader

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
