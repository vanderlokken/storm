#include <storm/platform/ogl/shader_ogl.h>

#include <numeric>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/sampler_ogl.h>
#include <storm/platform/ogl/texture_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

void bindTexture( Texture::Pointer texture, GLint textureUnit ) {
    const auto nativeTexture =
        std::static_pointer_cast< TextureOgl >( texture );

    ::glActiveTexture( GL_TEXTURE0 + textureUnit );
    checkResult( "::glActiveTexture" );

    if( nativeTexture )
        ::glBindTexture(
            nativeTexture->getTarget(), nativeTexture->getHandle() );
    else
        ::glBindTexture( GL_TEXTURE_2D, 0 );
    checkResult( "::glBindTexture" );
}

void bindSampler( Sampler::Pointer sampler, GLint textureUnit ) {
    const auto nativeSampler =
        std::static_pointer_cast< SamplerOgl >( sampler );

    ::glBindSampler( textureUnit, nativeSampler->getHandle() );
    checkResult( "::glBindSampler" );
}

} // namespace

// ProgramHandleOgl

ProgramHandleOgl::ProgramHandleOgl(
    GLenum shaderType, const char *sourceCode )
{
    _handle = ::glCreateShaderProgramv( shaderType, 1, &sourceCode );
    checkResult( "::glCreateShaderProgramv" );
}

ProgramHandleOgl::~ProgramHandleOgl() {
    ::glDeleteProgram( _handle );
}

// ShaderOgl

ShaderOgl::ShaderOgl( const std::string &sourceCode, Type type )
    : _type( type ), _handle( convertType(type), sourceCode.c_str() )
{
    if( getProgramParameter(GL_LINK_STATUS) == GL_FALSE ) {
        std::string log( getProgramParameter(GL_INFO_LOG_LENGTH), 0 );

        ::glGetProgramInfoLog( _handle, log.size(), nullptr, &log[0] );
        checkResult( "::glGetProgramInfoLog" );

        throwRuntimeError( "Shader compilation failed:\n" + log );
    }

    createSamplersMapping();
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

void ShaderOgl::bindSamplers() const {
    for( const auto &key: _samplersMapping ) {
        bindTexture( key.second.texture, key.second.textureUnit );
        bindSampler( key.second.sampler, key.second.textureUnit );
    }
}

GLint ShaderOgl::getProgramParameter( GLenum parameter ) const {
    GLint value = 0;

    ::glGetProgramiv( _handle, parameter, &value );
    checkResult( "::glGetProgramiv" );

    return value;
}

void ShaderOgl::createSamplersMapping() {
    const GLsizei activeUniforms = getProgramParameter( GL_ACTIVE_UNIFORMS );

    if( !activeUniforms )
        return;

    std::vector<GLuint> indices( activeUniforms );
    std::iota( indices.begin(), indices.end(), 0 );

    std::vector<GLint> types( activeUniforms );
    std::vector<GLint> sizes( activeUniforms );

    ::glGetActiveUniformsiv(
        _handle, activeUniforms, indices.data(), GL_UNIFORM_TYPE, &types[0] );
    checkResult( "::glGetActiveUniformsiv" );

    ::glGetActiveUniformsiv(
        _handle, activeUniforms, indices.data(), GL_UNIFORM_SIZE, &sizes[0] );
    checkResult( "::glGetActiveUniformsiv" );

    GLint textureUnit;
    GLint textureUnitIncrement;

    switch( _type ) {
    case Type::Pixel:
        textureUnit = 0;
        textureUnitIncrement = 1;
        break;
    case Type::Vertex:
        ::glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnit );
        checkResult( "::glGetIntegerv" );

        --textureUnit;
        textureUnitIncrement = -1;
        break;
    default:
        throwNotImplemented();
    }

    auto mapUniform = [
        this,
        &textureUnit,
        textureUnitIncrement]( const std::string &identifier )
    {
        const GLint location =
            ::glGetUniformLocation( _handle, identifier.c_str() );
        checkResult( "::glGetUniformLocation" );

        ::glProgramUniform1i( _handle, location, textureUnit );
        checkResult( "::glProgramUniform1i" );

        const GlslSampler sampler = {
            textureUnit, nullptr, Sampler::getDefault() };
        _samplersMapping.insert( std::make_pair(location, sampler) );

        textureUnit += textureUnitIncrement;
    };

    std::string identifier(
        getProgramParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH), 0 );

    for( GLsizei index = 0; index < activeUniforms; ++index ) {
        if( types[index] != GL_SAMPLER_2D )
            continue;

        ::glGetActiveUniformName(
            _handle, index, identifier.size(), nullptr, &identifier[0] );
        checkResult( "::glGetActiveUniformName" );

        if( sizes[index] == 1 )
            mapUniform( identifier );
        else
            for( GLint element = 0; element < sizes[index]; ++element ) {
                // For a GLSL array only the first element identifier is
                // returned

                // Copy identifier characters before the first '\0' occurrence
                std::string elementIdentifier( identifier.c_str() );

                // Replace zero in "identifier[0]" with an actual element index
                elementIdentifier.replace(
                    elementIdentifier.size() - 2, 1, std::to_string(element) );

                mapUniform( elementIdentifier );
            }
    }
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

void Shader::Uniform::setValue( Texture::Pointer texture ) {
    const auto nativeShader = std::static_pointer_cast< ShaderOgl >( _shader );
    auto &mappingValue = nativeShader->_samplersMapping[_location];

    mappingValue.texture = texture;

    if( RenderingSystemOgl::getInstance()->getShader(nativeShader->_type) ==
            nativeShader )
        bindTexture( texture, mappingValue.textureUnit );
}

void Shader::Uniform::setValue( Sampler::Pointer sampler ) {
    const auto nativeShader = std::static_pointer_cast< ShaderOgl >( _shader );
    auto &mappingValue = nativeShader->_samplersMapping[_location];

    mappingValue.sampler = sampler;

    if( RenderingSystemOgl::getInstance()->getShader(nativeShader->_type) ==
            nativeShader )
        bindSampler( sampler, mappingValue.textureUnit );
}

#undef _program
#undef _location

// Shader

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
