#include "ShaderOgl.h"

#include "CheckResultOgl.h"

namespace storm {

class ScopeProgram {
    NONCOPYABLE( ScopeProgram );
public:
    ScopeProgram( GLuint program )
        : _program( program ),
          _originalProgram( 0 )
    {
        ::glGetIntegerv( GL_CURRENT_PROGRAM, reinterpret_cast<GLint*>(&_originalProgram) );
        checkResult( "::glGetIntegerv" );
        
        if( _program != _originalProgram ) {
            ::glUseProgram( _program );
            checkResult( "::glUseProgram" );
        }
        return;
    }
    
    ~ScopeProgram() noexcept {
        if( _program != _originalProgram ) {
            ::glUseProgram( _originalProgram );
        }
        return;
    }
    
private:
    GLuint _program;
    GLuint _originalProgram;
};

ShaderOgl::ShaderOgl( const std::string &sourceCode )
    : _program( 0 ), _vertexShader( 0 ), _pixelShader( 0 )
{
    try {
        _vertexShader = ::glCreateShader( GL_VERTEX_SHADER );
        checkResult( "::glCreateShader" );
        _pixelShader = ::glCreateShader( GL_FRAGMENT_SHADER );
        checkResult( "::glCreateShader" );

        const size_t delimiterPosition = sourceCode.find( "@" );
        
        const GLchar *vertexShaderSource = sourceCode.c_str();
        const GLint vertexShaderSourceLength = delimiterPosition;

        const GLchar *pixelShaderSource = sourceCode.c_str() + delimiterPosition + 1;
        const GLint pixelShaderSourceLength = sourceCode.size() - delimiterPosition - 1;
        
        ::glShaderSource( _vertexShader, 1, &vertexShaderSource, &vertexShaderSourceLength );
        checkResult( "::glShaderSource" );
        ::glShaderSource( _pixelShader, 1, &pixelShaderSource, &pixelShaderSourceLength );
        checkResult( "::glShaderSource" );
        
        ::glCompileShader( _vertexShader );
        checkResult( "::glCompileShader" );
        ::glCompileShader( _pixelShader );
        checkResult( "::glCompileShader" );
        
        GLint vertexShaderCompiled = GL_FALSE;
        GLint pixelShaderCompiled = GL_FALSE;

        ::glGetShaderiv( _vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled );
        ::glGetShaderiv( _pixelShader, GL_COMPILE_STATUS, &pixelShaderCompiled );

        if( vertexShaderCompiled == GL_FALSE ) {
            const GLsizei bannerSize = 35;
            const GLsizei bufferSize = 512;
            GLchar buffer[bufferSize] = "GLSL shader compilation has failed\n";

            GLsizei outputSize = 0;

            ::glGetShaderInfoLog( _vertexShader, bufferSize - bannerSize, &outputSize, buffer + bannerSize );

            throwRuntimeError( buffer );
        }

        if( pixelShaderCompiled == GL_FALSE ) {
            const GLsizei bannerSize = 35;
            const GLsizei bufferSize = 512;
            GLchar buffer[bufferSize] = "GLSL shader compilation has failed\n";

            GLsizei outputSize = 0;

            ::glGetShaderInfoLog( _pixelShader, bufferSize - bannerSize, &outputSize, buffer + bannerSize );

            throwRuntimeError( buffer );
        }

        _program = ::glCreateProgram();
        
        ::glAttachShader( _program, _vertexShader );
        checkResult( "::glAttachShader" );
        ::glAttachShader( _program, _pixelShader );
        checkResult( "::glAttachShader" );
        
        ::glLinkProgram( _program );
        checkResult( "::glLinkProgram" );
        
        GLint linkingSuccessful = GL_TRUE;

        ::glGetProgramiv( _program, GL_LINK_STATUS, &linkingSuccessful );
        checkResult( "::glGetProgramiv" );

        if( !linkingSuccessful ) {
            const GLsizei bannerSize = 31;
            const GLsizei bufferSize = 512;
            GLchar buffer[bufferSize] = "GLSL shader linking has failed\n";
           
            GLsizei outputSize = 0;

            ::glGetProgramInfoLog( _program, bufferSize - bannerSize, &outputSize, buffer + bannerSize );

            throwRuntimeError( buffer );
        }

    } catch( ... ) {
        ::glDeleteProgram( _program );
        ::glDeleteShader( _vertexShader );
        ::glDeleteShader( _pixelShader );
        throw;
    }
    return;
}

ShaderOgl::~ShaderOgl() noexcept {
    ::glDeleteProgram( _program );
    ::glDeleteShader( _vertexShader );
    ::glDeleteShader( _pixelShader );
    return;
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, float value ) {
    ScopeProgram scopeProgram( _program );
    
    ::glUniform1f( getUniformLocation(identifier), value );
    checkResult( "::glUniform1f" );
    return;
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, const Color &color ) {
    ScopeProgram scopeProgram( _program );
    
    ::glUniform4f(
        getUniformLocation(identifier),
        color.getNormalizedR(),
        color.getNormalizedG(),
        color.getNormalizedB(),
        color.getNormalizedA() );
    checkResult( "::glUniform4f" );
    return;
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, const Vector &vector ) {
    ScopeProgram scopeProgram( _program );
    
    ::glUniform3f(
        getUniformLocation(identifier),
        vector.getX(),
        vector.getY(),
        vector.getZ() );
    checkResult( "::glUniform3f" );
    return;
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, const Matrix &matrix ) {
    ScopeProgram scopeProgram( _program );
    
    const GLint location = getUniformLocation( identifier );
    const GLsizei count = 1;
    const GLboolean transpose = false;
    const GLfloat *value = matrix.getValues();
    
    ::glUniformMatrix4fv( location, count, transpose, value );
    checkResult( "::glUniform3f" );
    return;
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, std::shared_ptr<Sampler> value ) {
    throwRuntimeError( "Not implemented" );
}

void ShaderOgl::setUniformValue( UniformIdentifier identifier, std::shared_ptr<Texture> value ) {
    throwRuntimeError( "Not implemented" );
}

GLuint ShaderOgl::getProgram() const noexcept {
    return _program;
}

GLint ShaderOgl::getUniformLocation( UniformIdentifier identifier ) {
    auto location = _locations.find( identifier );
    
    if( location == _locations.end() ) {
        const GLint uniformLocation =
            ::glGetUniformLocation( _program, identifier.getName().c_str() );
        checkResult( "::glGetUniformLocation" );
        
        location = _locations.insert( std::make_pair(identifier, uniformLocation) ).first;
    }
    
    return location->second;
}

std::shared_ptr< Shader > Shader::create( const std::string &sourceCode ) {
    return std::make_shared< ShaderOgl >( sourceCode );
}

}
