#include <storm/ogl/shader_ogl.h>

#include <algorithm>
#include <numeric>
#include <set>

#include <storm/ogl/buffer_ogl.h>
#include <storm/ogl/rendering_system_ogl.h>
#include <storm/ogl/sampler_ogl.h>
#include <storm/ogl/texture_ogl.h>
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

void bindTexture(
    const GpuContextOgl &gpuContext,
    const Texture *texture,
    size_t textureUnit )
{
    const auto nativeTexture = static_cast<const TextureOgl*>( texture );

    storm_assert(
        !nativeTexture ||
        nativeTexture->getHandle().getGpuContext().get() == &gpuContext );

    gpuContext.call<GlActiveTexture>(
        static_cast<GLuint>(GL_TEXTURE0 + textureUnit) );

    if( nativeTexture ) {
        gpuContext.call<GlBindTexture>(
            nativeTexture->getTarget(), nativeTexture->getHandle() );
    } else {
        gpuContext.call<GlBindTexture>( GL_TEXTURE_2D, 0 );
    }
}

void bindSampler(
    const GpuContextOgl &gpuContext,
    const Sampler *sampler,
    size_t textureUnit )
{
    const auto nativeSampler = static_cast<const SamplerOgl*>( sampler );

    storm_assert( nativeSampler, "Shader texture sampler is not set" );
    storm_assert(
        nativeSampler->getHandle().getGpuContext().get() == &gpuContext );

    gpuContext.call<GlBindSampler>(
        static_cast<GLuint>(textureUnit), nativeSampler->getHandle() );
}

void bindUniformBuffer(
    const GpuContextOgl &gpuContext,
    const Buffer *buffer,
    size_t bindingPoint )
{
    const auto nativeBuffer = static_cast<const BufferOgl*>( buffer );

    storm_assert(
        &gpuContext == nativeBuffer->getHandle().getGpuContext().get() );

    storm_assert( nativeBuffer, "Shader uniform buffer is not set" );

    gpuContext.call<GlBindBufferBase>(
        GL_UNIFORM_BUFFER,
        static_cast<GLuint>(bindingPoint),
        nativeBuffer->getHandle() );
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

ProgramHandleOgl::ProgramHandleOgl( const GpuContextOgl::Pointer &gpuContext ) :
    _gpuContext( gpuContext )
{
    _handle = gpuContext->call<GlCreateProgram>();
}

ProgramHandleOgl::ProgramHandleOgl(
        const GpuContextOgl::Pointer &gpuContext,
        GLenum shaderType,
        std::string_view sourceCode ) :
    _gpuContext( gpuContext )
{
    const char *sourceCodeData = sourceCode.data();

    _handle = gpuContext->call<GlCreateShaderProgramv>(
        shaderType, 1, &sourceCodeData );
}

ProgramHandleOgl::~ProgramHandleOgl() {
    if( const GpuContextOgl::Pointer gpuContext = _gpuContext.tryLock() ) {
        gpuContext->callUnchecked<GlDeleteProgram>( _handle );
    }
}

ShaderOgl::ShaderOgl(
        GpuContextOgl::Pointer gpuContext,
        std::string_view sourceCode,
        Type type ) :
    _type( type ),
    _handle( gpuContext, convertType(type), sourceCode )
{
    if( getProgramParameter(*gpuContext, GL_LINK_STATUS) == GL_FALSE ) {
        std::string log(
            getProgramParameter(*gpuContext, GL_INFO_LOG_LENGTH), 0 );

        gpuContext->call<GlGetProgramInfoLog>(
            _handle, static_cast<GLsizei>(log.size()), nullptr, &log[0] );

        throw ShaderCompilationError() << "Shader compilation failed:\n" << log;
    }

    setupBindings( *gpuContext );
}

ShaderOgl::ShaderOgl(
        GpuContextOgl::Pointer gpuContext,
        const std::vector<unsigned char> &binary,
        Type type ) :
    _type( type ),
    _handle( gpuContext )
{
    gpuContext->call<GlProgramParameteri>(
        _handle, GL_PROGRAM_SEPARABLE, GL_TRUE );

    const size_t headerSize = 2 * sizeof( GLenum );

    if( binary.size() > headerSize &&
            gpuContext->getExtensionSupportStatus().arbGetProgramBinary ) {
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

        gpuContext->callUnchecked<GlProgramBinary>(
            _handle,
            binaryFormat,
            binaryData,
            binaryRepresentationLength );

#ifndef NDEBUG
        // We intentionally ignore shader binary loading errors and set the
        // error flag to the 'GL_NO_ERROR' value. We will detect loading result
        // using the 'GL_LINK_STATUS' value.
        gpuContext->callUnchecked<GlGetError>();
#endif
    }

    if( getProgramParameter(*gpuContext, GL_LINK_STATUS) == GL_FALSE ) {
        throw ShaderBinaryLoadingError();
    }

    setupBindings( *gpuContext );
}

Shader::Type ShaderOgl::getType() const {
    return _type;
}

std::vector<unsigned char> ShaderOgl::getBinaryRepresentation() const {
    const GpuContextOgl::Pointer gpuContext = _handle.getGpuContext();

    std::vector<unsigned char> result;

    if( gpuContext->getExtensionSupportStatus().arbGetProgramBinary ) {
        const GLint binaryRepresentationLength =
            getProgramParameter( *gpuContext, GL_PROGRAM_BINARY_LENGTH );

        const size_t headerSize = 2 * sizeof( GLenum );
        result.resize( headerSize + binaryRepresentationLength );

        GLenum *shaderType =
            reinterpret_cast<GLenum*>( result.data() );
        GLenum *binaryFormat =
            reinterpret_cast<GLenum*>( result.data() + sizeof(GLenum) );
        void *binaryData = result.data() + headerSize;

        *shaderType = convertType( _type );

        gpuContext->call<GlGetProgramBinary>(
            _handle,
            binaryRepresentationLength, nullptr,
            binaryFormat,
            binaryData );
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

    Binding<Buffer::Pointer>& binding =
        _buffers.at( handleImplementation->index );

    if( binding.value != buffer ) {
        binding.value = buffer;
        binding.isChanged = true;
    }
}

void ShaderOgl::setValue( ValueHandle handle, Texture::Pointer texture ) {
    validateValueHandle( handle );

    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    Binding<Texture::Pointer>& binding =
        _textures.at( handleImplementation->index );

    if( binding.value != texture ) {
        binding.value = texture;
        binding.isChanged = true;
    }
}

void ShaderOgl::setValue( ValueHandle handle, Sampler::Pointer sampler ) {
    validateValueHandle( handle );

    const auto handleImplementation =
        std::static_pointer_cast<ValueHandleImplementation>( handle );

    storm_assert( handleImplementation->type ==
        ValueHandleImplementation::Type::Sampler );

    Binding<Sampler::Pointer>& binding =
        _samplers.at( handleImplementation->index );

    if( binding.value != sampler ) {
        binding.value = sampler;
        binding.isChanged = true;
    }
}

const ProgramHandleOgl& ShaderOgl::getHandle() const {
    return _handle;
}

void ShaderOgl::markAllBindingsChanged() {
    for( Binding<Texture::Pointer>& binding : _textures ) {
        binding.isChanged = true;
    }
    for( Binding<Sampler::Pointer>& binding : _samplers ) {
        binding.isChanged = true;
    }
    for( Binding<Buffer::Pointer>& binding : _buffers ) {
        binding.isChanged = true;
    }
}

void ShaderOgl::updateChangedBindings() {
    const GpuContextOgl& gpuContext = *_handle.getGpuContext();

    for( size_t index = 0; index < _textures.size(); ++index ) {
        Binding<Texture::Pointer>& binding = _textures[index];

        if( binding.isChanged ) {
            binding.isChanged = false;
            bindTexture(
                gpuContext, binding.value.get(), _baseSamplerBinding + index );
        }
    }

    for( size_t index = 0; index < _samplers.size(); ++index ) {
        Binding<Sampler::Pointer>& binding = _samplers[index];

        if( binding.isChanged ) {
            binding.isChanged = false;
            bindSampler(
                gpuContext, binding.value.get(), _baseSamplerBinding + index );
        }
    }

    for( size_t index = 0; index < _buffers.size(); ++index ) {
        Binding<Buffer::Pointer>& binding = _buffers[index];

        if( binding.isChanged ) {
            binding.isChanged = false;
            bindUniformBuffer(
                gpuContext, binding.value.get(), _baseBufferBinding + index );
        }
    }
}

void ShaderOgl::handleRootBufferUpdate(
    const std::vector<uint8_t> &rootBuffer, size_t offset, size_t size )
{
    const GpuContextOgl &gpuContext = *_handle.getGpuContext();

    for( size_t rootUniformIndex = offset / rootUniformDataSize;
            rootUniformIndex * rootUniformDataSize < offset + size;
            ++rootUniformIndex ) {
        const GLint uniformLocation =
            _rootUniformLocations.at( rootUniformIndex );

        if( uniformLocation != -1 ) {
            const GLsizei count = 1;
            const GLfloat *value = reinterpret_cast<const GLfloat*>(
                rootBuffer.data() + rootUniformIndex * rootUniformDataSize );
            gpuContext.callUnchecked<GlProgramUniform4fv>(
                _handle, uniformLocation, count, value );
#ifndef NDEBUG
            // We intentionally ignore type mismatch errors and set the error
            // flag to the 'GL_NO_ERROR' value.
            gpuContext.callUnchecked<GlGetError>();
#endif
        }
    }
}

GLint ShaderOgl::getProgramParameter(
    const GpuContextOgl &gpuContext, GLenum parameter ) const
{
    GLint value = 0;
    gpuContext.call<GlGetProgramiv>( _handle, parameter, &value );

    return value;
}

void ShaderOgl::setupBindings( const GpuContextOgl &gpuContext ) {
    // Shaders of different types use different binding point ranges. Note:
    // MAX_COMBINED_TEXTURE_IMAGE_UNITS = 3 * MAX_<stage>_TEXTURE_IMAGE_UNITS
    // MAX_COMBINED_UNIFORM_BLOCKS      = 3 * MAX_<stage>_UNIFORM_BLOCKS
    _baseSamplerBinding = shaderTextureUnits * static_cast<GLuint>( _type );
    _baseBufferBinding = shaderUniformBlocks * static_cast<GLuint>( _type );

    setupSamplersBinding( gpuContext );
    setupUniformBlocksBinding( gpuContext );
    setupRootUniformsBinding( gpuContext );
}

void ShaderOgl::setupSamplersBinding( const GpuContextOgl &gpuContext ) {
    const GLsizei activeUniforms =
        getProgramParameter( gpuContext, GL_ACTIVE_UNIFORMS );

    if( !activeUniforms ) {
        return;
    }

    std::vector<GLuint> indices( activeUniforms );
    std::iota( indices.begin(), indices.end(), 0 );

    std::vector<GLint> types( activeUniforms );
    std::vector<GLint> sizes( activeUniforms );

    gpuContext.call<GlGetActiveUniformsiv>(
        _handle, activeUniforms, indices.data(), GL_UNIFORM_TYPE, &types[0] );

    gpuContext.call<GlGetActiveUniformsiv>(
        _handle, activeUniforms, indices.data(), GL_UNIFORM_SIZE, &sizes[0] );

    auto mapUniform = [&]( std::string identifier ) {
        const GLint location =
            gpuContext.call<GlGetUniformLocation>( _handle, identifier.data() );

        const size_t textureUnit = _textures.size();

        gpuContext.call<GlProgramUniform1i>(
            _handle,
            location,
            static_cast<GLint>(_baseSamplerBinding + textureUnit) );

        _samplerUniformLocations.push_back( location );

        _textures.emplace_back();
        _samplers.emplace_back();
        _samplers.back().value =
            SamplerBuilder().build( _handle.getGpuContext() );

        auto valueHandle = std::make_shared<ValueHandleImplementation>();
        valueHandle->shader = this;
        valueHandle->type = ValueHandleImplementation::Type::Sampler;
        valueHandle->index = textureUnit;

        _valueHandles.emplace(
            Identifier::fromString(std::move(identifier)),
            std::move(valueHandle) );
    };

    std::string identifier(
        getProgramParameter(gpuContext, GL_ACTIVE_UNIFORM_MAX_LENGTH), 0 );

    for( GLsizei index = 0; index < activeUniforms; ++index ) {
        if( !isSupportedSamplerType(types[index]) ) {
            continue;
        }

        GLsizei identifierSize = 0;
        gpuContext.call<GlGetActiveUniformName>(
            _handle,
            index,
            static_cast<GLsizei>(identifier.size()),
            &identifierSize,
            identifier.data() );

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

void ShaderOgl::setupUniformBlocksBinding( const GpuContextOgl &gpuContext ) {
    const GLsizei activeUniformBlocks = getProgramParameter(
        gpuContext, GL_ACTIVE_UNIFORM_BLOCKS );

    const GLsizei maxNameLength = getProgramParameter(
        gpuContext, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH );

    std::string name( maxNameLength, 0 );

    for( GLsizei index = 0; index < activeUniformBlocks; ++index ) {
        const GLuint bindingPoint = _baseBufferBinding + index;

        gpuContext.call<GlUniformBlockBinding>( _handle, index, bindingPoint );

        GLsizei nameLength = 0;
        gpuContext.call<GlGetActiveUniformBlockName>(
            _handle, index, maxNameLength, &nameLength, name.data() );

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

void ShaderOgl::setupRootUniformsBinding( const GpuContextOgl &gpuContext ) {
    _rootUniformLocations.resize( RootBufferSize / rootUniformDataSize, -1 );

    for( size_t rootUniformIndex = 0;
            rootUniformIndex < _rootUniformLocations.size();
            ++rootUniformIndex ) {
        const std::string identifier =
            "_root_" + std::to_string( rootUniformIndex );
        _rootUniformLocations[rootUniformIndex] =
            gpuContext.call<GlGetUniformLocation>( _handle, identifier.data() );
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

Shader::Pointer Shader::create(
    GpuContext::Pointer gpuContext,
    std::string_view sourceCode,
    Type type )
{
    return std::make_shared<ShaderOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        sourceCode,
        type );
}

Shader::Pointer Shader::create(
    GpuContext::Pointer gpuContext,
    const std::vector<unsigned char> &binaryRepresentation,
    Type type )
{
    try {
        return std::make_shared<ShaderOgl>(
            std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
            binaryRepresentation,
            type );
    } catch( const ShaderBinaryLoadingError& ) {
        return nullptr;
    }
}

}
