#include <storm/ogl/rendering_system_ogl.h>

#include <algorithm>
#include <string_view>

#include <storm/ogl/backbuffer_ogl.h>
#include <storm/ogl/buffer_ogl.h>
#include <storm/ogl/framebuffer_ogl.h>
#include <storm/ogl/mesh_ogl.h>
#include <storm/ogl/pipeline_state_ogl.h>
#include <storm/ogl/shader_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

bool isSeamlessCubemapSupported( const GpuContextOgl &gpuContext ) {
    // There's a bug in the official drivers for the following GPU.
    const std::string_view unacceptableRenderers[] = {
        "GeForce GTS 250/PCIe/SSE2/3DNOW!",
        "GeForce GTS 250/PCIe/SSE2"
    };

    const std::string_view renderer = reinterpret_cast<const char*>(
        gpuContext.callUnchecked<GlGetString>(GL_RENDERER) );

    const auto iterator = std::find(
        std::begin(unacceptableRenderers),
        std::end(unacceptableRenderers),
        renderer
    );

    return iterator == std::end( unacceptableRenderers );
}

} // namespace

RenderingSystemOgl::RenderingSystemOgl() :
    _gpuContext(
        std::dynamic_pointer_cast<GpuContextOgl>(GpuContext::create()) )
{
    if( _gpuContext->getApiVersion() < GpuContextOgl::ApiVersion(4, 3) &&
        !_gpuContext->getExtensionSupportStatus().arbSeparateShaderObjects )
    {
        throw SystemRequirementsNotMet() << "Video driver doesn't support "
            "required 'ARB_separate_shader_objects' OpenGL extension.";
    }
}

void RenderingSystemOgl::initialize() {
    setVsyncEnabled( true );

    // TODO: set output and clipping rectangles

    // Replace OpenGL defaults with library defaults
    _pipelineState = createDefaultOpenGlPipelineState();
    setPipelineState( PipelineStateBuilder().build() );

    _programPipeline =
        std::make_shared<ProgramPipelineHandleOgl>( _gpuContext );
    _vertexArrayWithoutData =
        std::make_shared<VertexArrayHandleOgl>( _gpuContext );
    _backbuffer = std::make_shared<BackbufferOgl>( _gpuContext );

    _gpuContext->call<GlBindProgramPipeline>( *_programPipeline );
    _gpuContext->call<GlBindVertexArray>(
        _vertexArray = *_vertexArrayWithoutData );

    _primitiveRestartIndex = 0xffff;
    _gpuContext->callUnchecked<GlPrimitiveRestartIndex>(
        _primitiveRestartIndex );

    _gpuContext->call<GlFrontFace>( GL_CW );

    setBooleanOpenGlState(
        *_gpuContext, GL_PRIMITIVE_RESTART, true );
    setBooleanOpenGlState(
        *_gpuContext, GL_TEXTURE_CUBE_MAP_SEAMLESS,
        isSeamlessCubemapSupported(*_gpuContext) );
    setBooleanOpenGlState(
        *_gpuContext, GL_FRAMEBUFFER_SRGB, true );

    _rootBufferData.resize( RootBufferSize );
}

GpuContext::Pointer RenderingSystemOgl::getGpuContext() const {
    return _gpuContext;
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh, unsigned count ) {
    storm_assert( mesh );

    auto nativeMesh = std::dynamic_pointer_cast< MeshOgl >( mesh );
    bindVertexArray( nativeMesh->getHandle() );

    const size_t indexSize = mesh->getDescription().indexSize;

    storm_assert(
        indexSize == 2 ||
        indexSize == 4 );

    const GLuint primitiveRestartIndex = (indexSize == 2) ?
        0xffff :
        0xffffffff;

    if( _primitiveRestartIndex != primitiveRestartIndex ) {
        _primitiveRestartIndex = primitiveRestartIndex;
        _gpuContext->callUnchecked<GlPrimitiveRestartIndex>(
            _primitiveRestartIndex );
    }

    const GLenum primitiveTopology = nativeMesh->getPrimitiveTopology();
    const GLsizei indexCount = static_cast<GLsizei>(
        mesh->getDescription().indexBuffer->getDescription().size / indexSize );
    const GLenum indexFormat = (indexSize == 2) ?
        GL_UNSIGNED_SHORT :
        GL_UNSIGNED_INT;
    const GLvoid *indexOffset = nullptr;

    updateShaderBindings();

    if( count == 1 ) {
        _gpuContext->call<GlDrawElements>(
            primitiveTopology, indexCount, indexFormat, indexOffset );
    } else {
        _gpuContext->call<GlDrawElementsInstanced>(
            primitiveTopology, indexCount, indexFormat, indexOffset, count );
    }
}

void RenderingSystemOgl::renderGenerated(
    unsigned int vertexCount, Mesh::PrimitiveTopology primitiveTopology )
{
    bindVertexArray( *_vertexArrayWithoutData );

    updateShaderBindings();

    _gpuContext->call<GlDrawArrays>(
        MeshOgl::convertPrimitiveTopology(primitiveTopology), 0, vertexCount );
}

void RenderingSystemOgl::setShader( Shader::Pointer shader ) {
    storm_assert( shader );

    const Shader::Type shaderType = shader->getType();

    if( getShader(shaderType) == shader ) {
        return;
    }

    RenderingSystemCommon::setShader( shader );

    const auto nativeShader = std::dynamic_pointer_cast< ShaderOgl >( shader );

    const GLbitfield stage = selectShaderStage( shaderType );

    _gpuContext->call<GlUseProgramStages>(
        *_programPipeline, stage, nativeShader->getHandle() );

    nativeShader->markAllBindingsChanged();
    nativeShader->handleRootBufferUpdate(
        _rootBufferData, /* offset */ 0, _rootBufferData.size() );
}

void RenderingSystemOgl::resetShader( Shader::Type shaderType ) {
    if( getShader(shaderType) == nullptr ) {
        return;
    }

    _gpuContext->call<GlUseProgramStages>(
        *_programPipeline, selectShaderStage(shaderType), 0 );

    RenderingSystemCommon::resetShader( shaderType );
}

size_t RenderingSystemOgl::getRootBufferSize() const {
    return _rootBufferData.size();
}

void RenderingSystemOgl::setRootBufferData(
    size_t offset, size_t size, const void *data )
{
    storm_assert( _rootBufferData.size() >= offset + size );
    std::copy(
        static_cast<const uint8_t*>(data),
        static_cast<const uint8_t*>(data) + size,
        _rootBufferData.begin() + offset );

    Shader *shaders[] = {
        _geometryShader.get(),
        _vertexShader.get(),
        _pixelShader.get()
    };

    for( Shader *shader : shaders ) {
        if( shader ) {
            static_cast<ShaderOgl*>( shader )->handleRootBufferUpdate(
                _rootBufferData, offset, size );
        }
    }
}

PipelineState::Pointer RenderingSystemOgl::getPipelineState() const {
    return _pipelineState;
}

void RenderingSystemOgl::setPipelineState(
    PipelineState::Pointer pipelineState )
{
    storm_assert( pipelineState );

    if( _pipelineState != pipelineState ) {
        switchOpenGlPipelineState(
            *_gpuContext, *_pipelineState, *pipelineState );
        _pipelineState = std::move( pipelineState );
    }
}

const Rectangle& RenderingSystemOgl::getClippingRectangle() const {
    return _clippingRectangle;
}

const Rectangle& RenderingSystemOgl::getOutputRectangle() const {
    return _outputRectangle;
}

void RenderingSystemOgl::setClippingRectangle( const Rectangle &rectangle ) {
    _gpuContext->call<GlScissor>(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    _clippingRectangle = rectangle;
}

void RenderingSystemOgl::setOutputRectangle( const Rectangle &rectangle ) {
    _gpuContext->call<GlViewport>(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    _outputRectangle = rectangle;
}

Framebuffer::Pointer RenderingSystemOgl::getFramebuffer() const {
    return _framebuffer;
}

void RenderingSystemOgl::setFramebuffer(
    Framebuffer::Pointer framebuffer, bool preserveOutputRectangle )
{
    if( _framebuffer == framebuffer ) {
        return;
    }

    auto nativeFramebuffer =
        std::dynamic_pointer_cast< FramebufferOgl >( framebuffer );

    const GLint framebufferHandle =
        nativeFramebuffer ? nativeFramebuffer->getHandle() : 0;

    _gpuContext->call<GlBindFramebuffer>( GL_FRAMEBUFFER, framebufferHandle );

    if( !preserveOutputRectangle ) {
        unsigned int width;
        unsigned int height;

        if( framebuffer ) {
            const Framebuffer::Buffer &buffer =
                framebuffer->getDescription().buffers.front();

            const Texture::MipLevelDimensions mipLevelDimensions =
                buffer.texture->getMipLevelDimensions( buffer.mipLevel );
            width = mipLevelDimensions.width;
            height = mipLevelDimensions.height;
        } else {
            if( const Window::Pointer window = getOutputWindow() ) {
                const Dimensions windowDimensions = window->getDimensions();

                width = windowDimensions.width;
                height = windowDimensions.height;
            } else {
                width = 0;
                height = 0;
            }
        }

        setOutputRectangle( {0, 0, width, height} );
    }

    _framebuffer = framebuffer;
}

void RenderingSystemOgl::clearColorBuffer( const Color &color ) {
    _gpuContext->call<GlClearColor>( color.r, color.g, color.b, color.a );
    _gpuContext->call<GlClear>( GL_COLOR_BUFFER_BIT );
}

void RenderingSystemOgl::clearDepthBuffer( float depth ) {
    const bool depthWritingEnabled =
        _pipelineState->getDescription().writeDepthValues;

    if( !depthWritingEnabled ) {
        // Depth buffer writing must be temporarily enabled
        _gpuContext->call<GlDepthMask>( static_cast<GLboolean>(GL_TRUE) );
    }

    _gpuContext->call<GlClearDepth>( depth );
    _gpuContext->call<GlClear>( GL_DEPTH_BUFFER_BIT );

    if( !depthWritingEnabled ) {
        // Restore previous value
        _gpuContext->call<GlDepthMask>( static_cast<GLboolean>(GL_FALSE) );
    }
}

void RenderingSystemOgl::clearStencilBuffer( unsigned int stencil ) {
    _gpuContext->call<GlClearStencil>( stencil );
    _gpuContext->call<GlClear>( GL_STENCIL_BUFFER_BIT );
}

Backbuffer::Pointer RenderingSystemOgl::getBackbuffer() const {
    return _backbuffer;
}

std::string RenderingSystemOgl::getDebugMessageLog() const {
    std::string log;

    auto getIntegerParameter = [&]( GLenum parameter ) {
        GLint parameterValue = 0;
        _gpuContext->call<GlGetIntegerv>( parameter, &parameterValue );
        return parameterValue;
    };

    if( _gpuContext->getExtensionSupportStatus().khrDebug ) {
        GLint messageCount = getIntegerParameter( GL_DEBUG_LOGGED_MESSAGES );
        while( messageCount-- ) {
            std::string message(
                getIntegerParameter(GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH), 0 );

            GLenum severity = 0;
            _gpuContext->call<GlGetDebugMessageLog>(
                /* messageCount = */ 1,
                static_cast<GLsizei>(message.size()),
                nullptr,
                nullptr,
                nullptr,
                &severity,
                nullptr,
                &message[0] );

            // Replace the null character.
            message.back() = '\n';

            if( severity != GL_DEBUG_SEVERITY_NOTIFICATION ) {
                log += message;
            }
        }
    }
    return log;
}

void RenderingSystemOgl::bindVertexArray( GLuint vertexArray ) {
    if( _vertexArray != vertexArray ) {
        _vertexArray = vertexArray;

        _gpuContext->call<GlBindVertexArray>( vertexArray );
    }
}

void RenderingSystemOgl::updateShaderBindings() {
    for( Shader::Pointer shader : {
            getShader(Shader::Type::Vertex),
            getShader(Shader::Type::Pixel),
            getShader(Shader::Type::Geometry)} ) {
        if( shader ) {
            std::dynamic_pointer_cast<ShaderOgl>( shader )
                ->updateChangedBindings();
        }
    }
}

PipelineState::Pointer RenderingSystemOgl::createDefaultOpenGlPipelineState() {
    PipelineState::Description description = {};
    description.writeDepthValues = true;

    return PipelineState::create( description );
}

GLbitfield RenderingSystemOgl::selectShaderStage( Shader::Type shaderType ) {
    switch( shaderType ) {
    case Shader::Type::Vertex:
        return GL_VERTEX_SHADER_BIT;
    case Shader::Type::Pixel:
        return GL_FRAGMENT_SHADER_BIT;
    case Shader::Type::Geometry:
        return GL_GEOMETRY_SHADER_BIT;
    }
    storm_assert_unreachable( "Unexpected shader type value" );
    return 0;
}

}
