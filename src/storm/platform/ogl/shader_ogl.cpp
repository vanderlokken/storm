#include <storm/platform/ogl/shader_ogl.h>

#include <algorithm>
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

class ShaderBinaryLoadingError : public Exception {};

struct ValueHandleImplementation {
    enum class Type {
        UniformBlock,
        Sampler
    };

    const ShaderOgl *shader;
    Type type;
    size_t index;
};

void bindTexture( const Texture *texture, size_t textureUnit ) {
    const auto nativeTexture = static_cast<const TextureOgl*>( texture );

    ::glActiveTexture( static_cast<GLuint>(GL_TEXTURE0 + textureUnit) );
    checkResult( "::glActiveTexture" );

    if( nativeTexture ) {
        ::glBindTexture(
            nativeTexture->getTarget(), nativeTexture->getHandle() );
    } else {
        ::glBindTexture( GL_TEXTURE_2D, 0 );
    }
    checkResult( "::glBindTexture" );
}

void bindSampler( const Sampler *sampler, size_t textureUnit ) {
    const auto nativeSampler = static_cast<const SamplerOgl*>( sampler );

    storm_assert( nativeSampler, "Shader texture sampler is not set" );

    ::glBindSampler(
        static_cast<GLuint>(textureUnit), nativeSampler->getHandle() );
    checkResult( "::glBindSampler" );
}

void bindUniformBuffer( const Buffer *buffer, size_t bindingPoint ) {
    const auto nativeBuffer = static_cast<const BufferOgl*>( buffer );

    storm_assert( nativeBuffer, "Shader uniform buffer is not set" );

    ::glBindBufferBase( GL_UNIFORM_BUFFER, static_cast<GLuint>(bindingPoint),
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

// The following values are taken form the OpenGL specification and they
// specify the minimal number of binding points available in a shader.
// See the "State Tables" section.
const size_t shaderTextureUnits = 16;
const size_t shaderUniformBlocks = 12;

const size_t rootUniformDataSize = 16;

} // namespace

// ProgramHandleOgl

ProgramHandleOgl::ProgramHandleOgl() {
    _handle = ::glCreateProgram();
    checkResult( "::glCreateProgram" );
}

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

ShaderOgl::ShaderOgl( std::string_view sourceCode, Type type ) :
    _type( type ),
    _handle( convertType(type), sourceCode.data() )
{
    if( getProgramParameter(GL_LINK_STATUS) == GL_FALSE ) {
        std::string log( getProgramParameter(GL_INFO_LOG_LENGTH), 0 );

        ::glGetProgramInfoLog(
            _handle, static_cast<GLsizei>(log.size()), nullptr, &log[0] );
        checkResult( "::glGetProgramInfoLog" );

        throw ShaderCompilationError() << "Shader compilation failed:\n" << log;
    }

    setupBindings();
}

ShaderOgl::ShaderOgl( const std::vector<unsigned char> &binary, Type type ) :
    _type( type )
{
    const size_t headerSize = 2 * sizeof( GLenum );

    if( binary.size() > headerSize &&
            getOpenGlSupportStatus().ARB_get_program_binary ) {
        const GLenum shaderType =
            *reinterpret_cast<const GLenum*>( binary.data() );
        const GLenum binaryFormat =
            *reinterpret_cast<const GLenum*>( binary.data() + sizeof(GLenum) );

        if( shaderType != convertType(_type) ) {
            throw ShaderBinaryLoadingError();
        }

        const GLvoid *binaryData = binary.data() + headerSize;
        const GLsizei binaryRepresentationLength =
            static_cast<GLsizei>( binary.size() - headerSize );

        ::glProgramBinary(
            _handle,
            binaryFormat,
            binaryData,
            binaryRepresentationLength );

#ifndef NDEBUG
        // We intentionally ignore shader binary loading errors and set the
        // error flag to the 'GL_NO_ERROR' value. We will detect loading result
        // using the 'GL_LINK_STATUS' value.
        ::glGetError();
#endif
    }

    if( getProgramParameter(GL_LINK_STATUS) == GL_FALSE ) {
        throw ShaderBinaryLoadingError();
    }

    setupBindings();
}

Shader::Type ShaderOgl::getType() const {
    return _type;
}

std::vector<unsigned char> ShaderOgl::getBinaryRepresentation() const {
    std::vector<unsigned char> result;

    if( getOpenGlSupportStatus().ARB_get_program_binary ) {
        const GLint binaryRepresentationLength =
            getProgramParameter( GL_PROGRAM_BINARY_LENGTH );

        const size_t headerSize = 2 * sizeof( GLenum );
        result.resize( headerSize + binaryRepresentationLength );

        GLenum *shaderType =
            reinterpret_cast<GLenum*>( result.data() );
        GLenum *binaryFormat =
            reinterpret_cast<GLenum*>( result.data() + sizeof(GLenum) );
        void *binaryData = result.data() + headerSize;

        *shaderType = convertType( _type );

        ::glGetProgramBinary(
            _handle,
            binaryRepresentationLength, nullptr,
            binaryFormat,
            binaryData );
        checkResult( "::glGetProgramBinary" );
    }

    return result;
}

Shader::ValueHandle ShaderOgl::getValueHandle( Identifier identifier ) const {
    if( const auto iterator = _valueHandles.find(identifier);
            iterator != _valueHandles.end() ) {
        return iterator->second;
    }

    return nullptr;
}

void ShaderOgl::setValue( ValueHandle handle, Buffer::Pointer buffer ) {
    validateValueHandle( handle );

    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::UniformBlock );

    const size_t index = handleImplementation->index;

    if( _buffers.at(index) != buffer ) {
        _buffers.at( index ) = buffer;

        if( isInstalled() ) {
            bindUniformBuffer( buffer.get(), _baseBufferBinding + index );
        }
    }
}

void ShaderOgl::setValue( ValueHandle handle, Texture::Pointer texture ) {
    validateValueHandle( handle );

    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    const size_t index = handleImplementation->index;

    if( _textures.at(index) != texture ) {
        _textures.at( index ) = texture;

        if( isInstalled() ) {
            bindTexture( texture.get(), _baseSamplerBinding + index );
        }
    }
}

void ShaderOgl::setValue( ValueHandle handle, Sampler::Pointer sampler ) {
    validateValueHandle( handle );

    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    const size_t index = handleImplementation->index;

    if( _samplers.at(index) != sampler ) {
        _samplers.at( index ) = sampler;

        if( isInstalled() ) {
            bindSampler( sampler.get(), _baseSamplerBinding + index );
        }
    }
}

const ProgramHandleOgl& ShaderOgl::getHandle() const {
    return _handle;
}

void ShaderOgl::install() const {
    for( size_t index = 0; index < _textures.size(); ++index ) {
        bindTexture( _textures[index].get(), _baseSamplerBinding + index );
        bindSampler( _samplers[index].get(), _baseSamplerBinding + index );
    }
    for( size_t index = 0; index < _buffers.size(); ++index ) {
        bindUniformBuffer( _buffers[index].get(), _baseBufferBinding + index );
    }
}

void ShaderOgl::handleRootBufferUpdate(
    const std::vector<uint8_t> &rootBuffer, size_t offset, size_t size )
{
    for( size_t rootUniformIndex = offset / rootUniformDataSize;
            rootUniformIndex * rootUniformDataSize < offset + size;
            ++rootUniformIndex ) {
        const GLint uniformLocation =
            _rootUniformLocations.at( rootUniformIndex );

        if( uniformLocation != -1 ) {
            const GLsizei count = 1;
            const GLfloat *value = reinterpret_cast<const GLfloat*>(
                rootBuffer.data() + rootUniformIndex * rootUniformDataSize );
            ::glProgramUniform4fv( _handle, uniformLocation, count, value );
#ifndef NDEBUG
            // We intentionally ignore type mismatch errors and set the error
            // flag to the 'GL_NO_ERROR' value.
            ::glGetError();
#endif
        }
    }
}

GLint ShaderOgl::getProgramParameter( GLenum parameter ) const {
    GLint value = 0;

    ::glGetProgramiv( _handle, parameter, &value );
    checkResult( "::glGetProgramiv" );

    return value;
}

void ShaderOgl::setupBindings() {
    // Shaders of different types use different binding point ranges. Note:
    // MAX_COMBINED_TEXTURE_IMAGE_UNITS = 3 * MAX_<stage>_TEXTURE_IMAGE_UNITS
    // MAX_COMBINED_UNIFORM_BLOCKS      = 3 * MAX_<stage>_UNIFORM_BLOCKS
    _baseSamplerBinding = shaderTextureUnits * static_cast<GLuint>( _type );
    _baseBufferBinding = shaderUniformBlocks * static_cast<GLuint>( _type );

    setupSamplersBinding();
    setupUniformBlocksBinding();
    setupRootUniformsBinding();
}

void ShaderOgl::setupSamplersBinding() {
    const GLsizei activeUniforms = getProgramParameter( GL_ACTIVE_UNIFORMS );

    if( !activeUniforms ) {
        return;
    }

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

    auto mapUniform = [this]( std::string identifier ) {
        const GLint location =
            ::glGetUniformLocation( _handle, identifier.data() );
        checkResult( "::glGetUniformLocation" );

        const size_t textureUnit = _textures.size();

        ::glProgramUniform1i(
            _handle,
            location,
            static_cast<GLint>(_baseSamplerBinding + textureUnit) );
        checkResult( "::glProgramUniform1i" );

        _samplerUniformLocations.push_back( location );

        _textures.push_back( nullptr );
        _samplers.push_back( Sampler::getDefault() );

        auto valueHandle = std::make_shared<ValueHandleImplementation>();
        valueHandle->shader = this;
        valueHandle->type = ValueHandleImplementation::Type::Sampler;
        valueHandle->index = textureUnit;

        _valueHandles.emplace(
            Identifier::fromString(std::move(identifier)),
            std::move(valueHandle) );
    };

    std::string identifier(
        getProgramParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH), 0 );

    for( GLsizei index = 0; index < activeUniforms; ++index ) {
        if( !isSupportedSamplerType(types[index]) ) {
            continue;
        }

        GLsizei identifierSize = 0;
        ::glGetActiveUniformName(
            _handle,
            index,
            static_cast<GLsizei>(identifier.size()),
            &identifierSize,
            identifier.data() );
        checkResult( "::glGetActiveUniformName" );

        if( sizes[index] == 1 ) {
            mapUniform( identifier.substr(0, identifierSize) );
        } else {
            for( GLint element = 0; element < sizes[index]; ++element ) {
                // For a GLSL array only the first element identifier is
                // returned

                // Copy identifier characters before the first '\0' occurrence
                std::string elementIdentifier =
                    identifier.substr( 0, identifierSize );

                // Replace zero in "identifier[0]" with an actual element index
                elementIdentifier.replace(
                    elementIdentifier.size() - 2, 1, std::to_string(element) );

                mapUniform( std::move(elementIdentifier) );
            }
        }

        storm_assert( _samplers.size() <= shaderTextureUnits );
    }
}

void ShaderOgl::setupUniformBlocksBinding() {
    const GLsizei activeUniformBlocks = getProgramParameter(
        GL_ACTIVE_UNIFORM_BLOCKS );

    const GLsizei maxNameLength = getProgramParameter(
        GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH );

    std::string name( maxNameLength, 0 );

    for( GLsizei index = 0; index < activeUniformBlocks; ++index ) {
        const GLuint bindingPoint = _baseBufferBinding + index;

        ::glUniformBlockBinding( _handle, index, bindingPoint );
        checkResult( "::glUniformBlockBinding" );

        GLsizei nameLength = 0;
        ::glGetActiveUniformBlockName(
            _handle, index, maxNameLength, &nameLength, name.data() );
        checkResult( "::glGetActiveUniformBlockName" );

        auto valueHandle = std::make_shared<ValueHandleImplementation>();
        valueHandle->shader = this;
        valueHandle->type = ValueHandleImplementation::Type::UniformBlock;
        valueHandle->index = index;

        _valueHandles.emplace(
            Identifier::fromString(name.substr(0, nameLength)),
            std::move(valueHandle) );
    }

    _buffers.resize( activeUniformBlocks );
    storm_assert( _buffers.size() <= shaderUniformBlocks );
}

void ShaderOgl::setupRootUniformsBinding() {
    const size_t rootBufferSize =
        RenderingSystem::getInstance()->getRootBufferSize();
    _rootUniformLocations.resize( rootBufferSize / rootUniformDataSize, -1 );

    for( size_t rootUniformIndex = 0;
            rootUniformIndex < _rootUniformLocations.size();
            ++rootUniformIndex ) {
        const std::string identifier =
            "_root_" + std::to_string( rootUniformIndex );
        _rootUniformLocations[rootUniformIndex] =
            ::glGetUniformLocation( _handle, identifier.data() );
        checkResult( "::glGetUniformLocation" );
    }
}

void ShaderOgl::validateValueHandle( ValueHandle handle ) const {
    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    if( !handleImplementation ||
         handleImplementation->shader != this )
    {
        throw ShaderValueLookupError() << "Invalid value handle";
    }
}

bool ShaderOgl::isInstalled() const {
    return RenderingSystemOgl::getInstance()->getShader( _type ).get() == this;
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

Shader::Pointer Shader::create( std::string_view sourceCode, Type type ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< ShaderOgl >( sourceCode, type );
}

Shader::Pointer Shader::create(
    const std::vector<unsigned char> &binaryRepresentation, Type type )
{
    RenderingSystemOgl::installOpenGlContext();

    try {
        return std::make_shared< ShaderOgl >( binaryRepresentation, type );
    } catch( const ShaderBinaryLoadingError& ) {
        return nullptr;
    }
}

}
