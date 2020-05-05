#include <storm/ogl/rendering_system_ogl.h>

#include <algorithm>
#include <string_view>

#include <storm/ogl/api_ogl.h>

#include <storm/ogl/backbuffer_ogl.h>
#include <storm/ogl/buffer_ogl.h>
#include <storm/ogl/check_result_ogl.h>
#include <storm/ogl/framebuffer_ogl.h>
#include <storm/ogl/mesh_ogl.h>
#include <storm/ogl/pipeline_state_ogl.h>
#include <storm/ogl/shader_ogl.h>

namespace storm {

namespace {

bool isSeamlessCubemapSupported() {
    // There's a bug in the official drivers for the following GPU.
    const std::string_view unacceptableRenderers[] = {
        "GeForce GTS 250/PCIe/SSE2/3DNOW!",
        "GeForce GTS 250/PCIe/SSE2"
    };

    const std::string_view renderer =
        reinterpret_cast<const char*>( ::glGetString(GL_RENDERER) );

    const auto iterator = std::find(
        std::begin(unacceptableRenderers),
        std::end(unacceptableRenderers),
        renderer
    );

    return iterator == std::end( unacceptableRenderers );
}

} // namespace

ProgramPipelineHandleOgl::ProgramPipelineHandleOgl() {
    ::glGenProgramPipelines( 1, &_handle );
    checkResult( "::glGenProgramPipelines" );
}

ProgramPipelineHandleOgl::~ProgramPipelineHandleOgl() {
    ::glDeleteProgramPipelines( 1, &_handle );
}

void RenderingSystemOgl::initialize() {
    loadOpenGlApi();

    const OpenGlSupportStatus &supportStatus = getOpenGlSupportStatus();

    if( supportStatus.version < OpenGlVersion(4, 3) ) {
        if( !supportStatus.ARB_separate_shader_objects ) {
            throw SystemRequirementsNotMet() << "Video driver doesn't support "
                "required 'ARB_separate_shader_objects' OpenGL extension.";
        }
    }

    setVsyncEnabled( true );

    // TODO: set output and clipping rectangles

    // Replace OpenGL defaults with library defaults
    _pipelineState = createDefaultOpenGlPipelineState();
    setPipelineState( PipelineStateBuilder().build() );

    _programPipeline = std::make_shared<ProgramPipelineHandleOgl>();
    _vertexArrayWithoutData = std::make_shared<VertexArrayHandleOgl>();

    ::glBindProgramPipeline( *_programPipeline );
    checkResult( "::glBindProgramPipeline" );

    _backbuffer = std::make_shared<BackbufferOgl>();

    ::glBindVertexArray( _vertexArray = *_vertexArrayWithoutData );
    checkResult( "::glBindVertexArray" );

    _primitiveRestartIndex = 0xffff;
    ::glPrimitiveRestartIndex( _primitiveRestartIndex );

    ::glFrontFace( GL_CW );
    checkResult( "::glFrontFace" );

    setBooleanOpenGlState(
        GL_PRIMITIVE_RESTART, true );
    setBooleanOpenGlState(
        GL_TEXTURE_CUBE_MAP_SEAMLESS, isSeamlessCubemapSupported() );
    setBooleanOpenGlState(
        GL_FRAMEBUFFER_SRGB, true );

    const size_t rootBufferSize = 128;
    _rootBufferData.resize( rootBufferSize );
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh, unsigned count ) {
    storm_assert( mesh );

    auto nativeMesh = std::static_pointer_cast< MeshOgl >( mesh );
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
        ::glPrimitiveRestartIndex( _primitiveRestartIndex );
    }

    const GLenum primitiveTopology = nativeMesh->getPrimitiveTopology();
    const GLsizei indexCount = static_cast<GLsizei>(
        mesh->getDescription().indexBuffer->getDescription().size / indexSize );
    const GLenum indexFormat = (indexSize == 2) ?
        GL_UNSIGNED_SHORT :
        GL_UNSIGNED_INT;
    const GLvoid *indexOffset = nullptr;

    if( count == 1 ) {
        ::glDrawElements(
            primitiveTopology, indexCount, indexFormat, indexOffset );
        checkResult( "::glDrawElements" );
    } else {
        ::glDrawElementsInstanced(
            primitiveTopology, indexCount, indexFormat, indexOffset, count );
        checkResult( "::glDrawElementsInstanced" );
    }
}

void RenderingSystemOgl::renderGenerated(
    unsigned int vertexCount, Mesh::PrimitiveTopology primitiveTopology )
{
    bindVertexArray( *_vertexArrayWithoutData );

    ::glDrawArrays(
        MeshOgl::convertPrimitiveTopology(primitiveTopology), 0, vertexCount );
    checkResult( "::glDrawArrays" );
}

void RenderingSystemOgl::setShader( Shader::Pointer shader ) {
    storm_assert( shader );

    const Shader::Type shaderType = shader->getType();

    if( getShader(shaderType) == shader ) {
        return;
    }

    RenderingSystemCommon::setShader( shader );

    const auto nativeShader = std::static_pointer_cast< ShaderOgl >( shader );

    const GLbitfield stage = selectShaderStage( shaderType );

    ::glUseProgramStages( *_programPipeline, stage, nativeShader->getHandle() );
    checkResult( "::glUseProgramStages" );

    nativeShader->install();
    nativeShader->handleRootBufferUpdate(
        _rootBufferData, /* offset */ 0, _rootBufferData.size() );
}

void RenderingSystemOgl::resetShader( Shader::Type shaderType ) {
    if( getShader(shaderType) == nullptr ) {
        return;
    }

    ::glUseProgramStages( *_programPipeline, selectShaderStage(shaderType), 0 );
    checkResult( "::glUseProgramStages" );

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
        switchOpenGlPipelineState( *_pipelineState, *pipelineState );
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
    ::glScissor(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    checkResult( "::glScissor" );
    _clippingRectangle = rectangle;
}

void RenderingSystemOgl::setOutputRectangle( const Rectangle &rectangle ) {
    ::glViewport(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    checkResult( "::glViewport" );
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
        std::static_pointer_cast< FramebufferOgl >( framebuffer );

    const GLint framebufferHandle =
        nativeFramebuffer ? nativeFramebuffer->getHandle() : 0;

    ::glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    checkResult( "::glBindFramebuffer" );

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
    ::glClearColor( color.r, color.g, color.b, color.a );
    checkResult( "::glClearColor" );

    ::glClear( GL_COLOR_BUFFER_BIT );
    checkResult( "::glClear" );
}

void RenderingSystemOgl::clearDepthBuffer( float depth ) {
    const bool depthWritingEnabled =
        _pipelineState->getDescription().writeDepthValues;

    if( !depthWritingEnabled ) {
        // Depth buffer writing must be temporarily enabled

        ::glDepthMask( GL_TRUE );
        checkResult( "::glDepthMask" );
    }

    ::glClearDepth( depth );
    checkResult( "::glClearDepth" );

    ::glClear( GL_DEPTH_BUFFER_BIT );
    checkResult( "::glClear" );

    if( !depthWritingEnabled ) {
        // Restore previous value

        ::glDepthMask( GL_FALSE );
        checkResult( "::glDepthMask" );
    }
}

void RenderingSystemOgl::clearStencilBuffer( unsigned int stencil ) {
    ::glClearStencil( stencil );
    checkResult( "::glClearStencil" );

    ::glClear( GL_STENCIL_BUFFER_BIT );
    checkResult( "::glClear" );
}

Backbuffer::Pointer RenderingSystemOgl::getBackbuffer() const {
    return _backbuffer;
}

std::string RenderingSystemOgl::getDebugMessageLog() const {
    std::string log;

    auto getIntegerParameter = []( GLenum parameter ) {
        GLint parameterValue = 0;
        ::glGetIntegerv( parameter, &parameterValue );
        checkResult( "::glGetIntegerv" );
        return parameterValue;
    };

    if( getOpenGlSupportStatus().KHR_debug ) {
        GLint messageCount = getIntegerParameter( GL_DEBUG_LOGGED_MESSAGES );
        while( messageCount-- ) {
            std::string message(
                getIntegerParameter(GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH), 0 );

            GLenum severity = 0;
            ::glGetDebugMessageLog(
                /* messageCount = */ 1,
                static_cast<GLsizei>(message.size()),
                nullptr,
                nullptr,
                nullptr,
                &severity,
                nullptr,
                &message[0] );
            checkResult( "::glGetDebugMessageLog" );

            // Replace the null character.
            message.back() = '\n';

            if( severity != GL_DEBUG_SEVERITY_NOTIFICATION ) {
                log += message;
            }
        }
    }
    return log;
}

void RenderingSystemOgl::installOpenGlContext() {
    // OpenGL context is installed when the rendering system is being created
    RenderingSystem::getInstance();
}

void RenderingSystemOgl::bindVertexArray( GLuint vertexArray ) {
    if( _vertexArray != vertexArray ) {
        _vertexArray = vertexArray;

        ::glBindVertexArray( vertexArray );
        checkResult( "::glBindVertexArray" );
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

void setBooleanOpenGlState( GLenum state, bool value ) {
    if( value ) {
        ::glEnable( state );
        checkResult( "::glEnable" );
    } else {
        ::glDisable( state );
        checkResult( "::glDisable" );
    }
}

}