#include <storm/platform/ogl/shader_ogl.h>

#include <numeric>
#include <set>

#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/sampler_ogl.h>
#include <storm/platform/ogl/texture_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

struct ValueHandleImplementation {
    enum class Type {
        UniformBlock,
        Sampler
    };

    const ShaderOgl *shader;
    Type type;
    GLint index;
};

void bindTexture( Texture::Pointer texture, GLuint textureUnit ) {
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

void bindSampler( Sampler::Pointer sampler, GLuint textureUnit ) {
    const auto nativeSampler =
        std::static_pointer_cast< SamplerOgl >( sampler );

    storm_assert( nativeSampler, "Shader texture sampler is not set" );

    ::glBindSampler( textureUnit, nativeSampler->getHandle() );
    checkResult( "::glBindSampler" );
}

void bindUniformBuffer( Buffer::Pointer buffer, GLuint bindingPoint ) {
    const auto nativeBuffer = std::static_pointer_cast<BufferOgl>( buffer );

    storm_assert( nativeBuffer, "Shader uniform buffer is not set" );

    ::glBindBufferBase( GL_UNIFORM_BUFFER, bindingPoint,
        nativeBuffer->getHandle() );
    checkResult( "::glBindBufferBase" );
}

bool isSupportedSamplerType( GLenum uniformType ) {
    static const std::set<GLenum> supportedTypes = {
        GL_SAMPLER_1D,
        GL_SAMPLER_2D,
        GL_SAMPLER_3D,
        GL_SAMPLER_CUBE,
        GL_SAMPLER_1D_SHADOW,
        GL_SAMPLER_2D_SHADOW,
        GL_SAMPLER_1D_ARRAY,
        GL_SAMPLER_2D_ARRAY,
        GL_SAMPLER_1D_ARRAY_SHADOW,
        GL_SAMPLER_2D_ARRAY_SHADOW,
        GL_SAMPLER_2D_MULTISAMPLE,
        GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
        GL_SAMPLER_CUBE_SHADOW,
        GL_INT_SAMPLER_1D,
        GL_INT_SAMPLER_2D,
        GL_INT_SAMPLER_3D,
        GL_INT_SAMPLER_CUBE,
        GL_INT_SAMPLER_1D_ARRAY,
        GL_INT_SAMPLER_2D_ARRAY,
        GL_INT_SAMPLER_2D_MULTISAMPLE,
        GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
        GL_UNSIGNED_INT_SAMPLER_1D,
        GL_UNSIGNED_INT_SAMPLER_2D,
        GL_UNSIGNED_INT_SAMPLER_3D,
        GL_UNSIGNED_INT_SAMPLER_CUBE,
        GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
        GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
        GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
        GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
    };
    return supportedTypes.count( uniformType ) != 0;
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

        throw ShaderCompilationError() << "Shader compilation failed:\n" << log;
    }

    createSamplersMapping();
    createUniformBlocksMapping();
}

Shader::Type ShaderOgl::getType() const {
    return _type;
}

Shader::ValueHandle ShaderOgl::getValueHandle(
    const std::string &identifier ) const
{
    const GLint location =
        ::glGetUniformLocation( _handle, identifier.c_str() );
    checkResult( "::glGetUniformLocation" );

    if( location != -1 ) {
        storm_assert( _samplersMapping.count(location) );

        const auto valueHandle = std::make_shared<ValueHandleImplementation>();
        valueHandle->shader = this;
        valueHandle->type = ValueHandleImplementation::Type::Sampler;
        valueHandle->index = location;
        return valueHandle;
    }

    const GLuint blockIndex =
        ::glGetUniformBlockIndex( _handle, identifier.c_str() );
    checkResult( "::glGetUniformBlockIndex" );

    if( blockIndex == GL_INVALID_INDEX )
        throw ShaderValueLookupError() << "Invalid uniform identifier";

    const auto valueHandle = std::make_shared<ValueHandleImplementation>();
    valueHandle->shader = this;
    valueHandle->type = ValueHandleImplementation::Type::UniformBlock;
    valueHandle->index = blockIndex;
    return valueHandle;
}

void ShaderOgl::setValue( ValueHandle handle, Buffer::Pointer buffer ) {
    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->shader == this );
    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::UniformBlock );

    GlslUniformBlock &glslUniformBlock =
        _uniformBlocksMapping[handleImplementation->index];
    glslUniformBlock.buffer = buffer;

    if( RenderingSystemOgl::getInstance()->getShader(_type).get() == this )
         bindUniformBuffer( buffer, glslUniformBlock.bindingPoint );
}

void ShaderOgl::setValue( ValueHandle handle, Texture::Pointer texture ) {
    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->shader == this );
    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    GlslSampler &glslSampler = _samplersMapping[handleImplementation->index];
    glslSampler.texture = texture;

    if( RenderingSystemOgl::getInstance()->getShader(_type).get() == this )
         bindTexture( texture, glslSampler.textureUnit );
}

void ShaderOgl::setValue( ValueHandle handle, Sampler::Pointer sampler ) {
    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->shader == this );
    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    GlslSampler &glslSampler = _samplersMapping[handleImplementation->index];
    glslSampler.sampler = sampler;

    if( RenderingSystemOgl::getInstance()->getShader(_type).get() == this )
        bindSampler( sampler, glslSampler.textureUnit );
}

const ProgramHandleOgl& ShaderOgl::getHandle() const {
    return _handle;
}

void ShaderOgl::install() const {
    for( const auto &key: _samplersMapping ) {
        bindTexture( key.second.texture, key.second.textureUnit );
        bindSampler( key.second.sampler, key.second.textureUnit );
    }
    for( const auto &key: _uniformBlocksMapping ) {
        bindUniformBuffer( key.second.buffer, key.second.bindingPoint );
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

    // The following value is taken form OpenGL specification and it specifies
    // the minimal number of texture image units available in a shader. See the
    // "State Tables" section.
    const GLuint shaderTextureUnits = 16;

    // Shaders of different types use different texture image unit ranges.
    GLuint textureUnit = shaderTextureUnits * static_cast<GLuint>( _type );

    auto mapUniform = [this, &textureUnit]( const std::string &identifier ) {
        const GLint location =
            ::glGetUniformLocation( _handle, identifier.c_str() );
        checkResult( "::glGetUniformLocation" );

        ::glProgramUniform1i( _handle, location, textureUnit );
        checkResult( "::glProgramUniform1i" );

        const GlslSampler sampler = {
            textureUnit, nullptr, Sampler::getDefault() };
        _samplersMapping.insert( std::make_pair(location, sampler) );

        ++textureUnit;
    };

    std::string identifier(
        getProgramParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH), 0 );

    for( GLsizei index = 0; index < activeUniforms; ++index ) {
        if( !isSupportedSamplerType(types[index]) )
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

void ShaderOgl::createUniformBlocksMapping() {
    const GLsizei activeUniformBlocks =
        getProgramParameter( GL_ACTIVE_UNIFORM_BLOCKS );

    // The following value is taken form OpenGL specification and it specifies
    // the minimal number of uniform blocks available in a shader. See the
    // "State Tables" section.
    const GLuint shaderUniformBlocks = 14;

    // Shaders of different types use different binding point ranges.
    const GLuint initialBindingPoint =
        shaderUniformBlocks * static_cast<GLuint>( _type );

    for( GLsizei index = 0; index < activeUniformBlocks; ++index ) {
        const GLuint bindingPoint = initialBindingPoint + index;

        GlslUniformBlock glslUniformBlock;
        glslUniformBlock.bindingPoint = bindingPoint;
        glslUniformBlock.buffer = nullptr;
        _uniformBlocksMapping.insert( {index, glslUniformBlock} );

        ::glUniformBlockBinding( _handle, index, bindingPoint );
        checkResult( "::glUniformBlockBinding" );
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
        storm_assert_unreachable( "Unexpected type value" );
        return 0;
    }
}

Shader::Pointer Shader::create( const std::string &sourceCode, Type type ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
