#include <storm/platform/ogl/rendering_system_ogl.h>

#include <algorithm>

#include <storm/platform/ogl/api_ogl.h>

#include <storm/platform/ogl/backbuffer_ogl.h>
#include <storm/platform/ogl/blending_technique_ogl.h>
#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/framebuffer_ogl.h>
#include <storm/platform/ogl/mesh_ogl.h>
#include <storm/platform/ogl/output_technique_ogl.h>
#include <storm/platform/ogl/rasterization_technique_ogl.h>
#include <storm/platform/ogl/shader_ogl.h>

#include <storm/rendering_window.h>

namespace storm {

namespace {

bool isSeamlessCubemapSupported() {
    // There's a bug in the official drivers for the following GPU.
    const std::string unacceptableRenderers[] = {
        "GeForce GTS 250/PCIe/SSE2/3DNOW!",
        "GeForce GTS 250/PCIe/SSE2"
    };

    const std::string renderer =
        reinterpret_cast<const char*>( ::glGetString(GL_RENDERER) );

    const auto iterator = std::find(
        std::begin(
            unacceptableRenderers),
        std::end(
            unacceptableRenderers),
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

    setRasterizationTechnique( RasterizationTechnique::getDefault() );
    setOutputTechnique( OutputTechnique::getDefault() );
    setBlendingTechnique( BlendingTechnique::getDefault() );

    const Dimensions dimensions =
        RenderingWindow::getInstance()->getDimensions();
    _clippingRectangle.width = _outputRectangle.width = dimensions.width;
    _clippingRectangle.height = _outputRectangle.height = dimensions.height;

    _programPipeline = std::make_shared<ProgramPipelineHandleOgl>();
    _vertexArrayWithoutData = std::make_shared<VertexArrayHandleOgl>();

    ::glBindProgramPipeline( *_programPipeline );
    checkResult( "::glBindProgramPipeline" );

    _backbuffer = std::make_shared<BackbufferOgl>();

    ::glBindVertexArray( _vertexArray = *_vertexArrayWithoutData );
    checkResult( "::glBindVertexArray" );

    _primitiveRestartIndex = 0xffff;
    ::glPrimitiveRestartIndex( _primitiveRestartIndex );

    setBooleanGlState(
        GL_PRIMITIVE_RESTART, true );
    setBooleanGlState(
        GL_TEXTURE_CUBE_MAP_SEAMLESS, isSeamlessCubemapSupported() );
    setBooleanGlState(
        GL_FRAMEBUFFER_SRGB, true );

    const size_t rootBufferSize = 128;
    _rootBufferData.resize( rootBufferSize );
}

void RenderingSystemOgl::beginFrameRendering() {
    return;
}

void RenderingSystemOgl::endFrameRendering() {
    return;
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh, unsigned count ) {
    storm_assert( mesh );

    auto nativeMesh = std::static_pointer_cast< MeshOgl >( mesh );
    bindVertexArray( nativeMesh->getHandle() );

    const auto &indexBufferDescription =
        mesh->getDescription().indexBuffer->getDescription();

    storm_assert(
        indexBufferDescription.elementSize == 2 ||
        indexBufferDescription.elementSize == 4 );

    const GLuint primitiveRestartIndex =
        (indexBufferDescription.elementSize == 2) ? 0xffff : 0xffffffff;

    if( _primitiveRestartIndex != primitiveRestartIndex ) {
        _primitiveRestartIndex = primitiveRestartIndex;
        ::glPrimitiveRestartIndex( _primitiveRestartIndex );
    }

    const GLenum primitiveTopology = nativeMesh->getPrimitiveTopology();
    const GLsizei indexCount =
        indexBufferDescription.size / indexBufferDescription.elementSize;
    const GLenum indexFormat = (indexBufferDescription.elementSize == 2) ?
        GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
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

    if( getShader(shaderType) == shader )
        return;

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
    if( getShader(shaderType) == nullptr )
        return;

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

RasterizationTechnique::Pointer RenderingSystemOgl::getRasterizationTechnique() const {
    return _rasterizationTechnique;
}

OutputTechnique::Pointer RenderingSystemOgl::getOutputTechnique() const {
    return _outputTechnique;
}

BlendingTechnique::Pointer RenderingSystemOgl::getBlendingTechnique() const {
    return _blendingTechnique;
}

void RenderingSystemOgl::setRasterizationTechnique(
    RasterizationTechnique::Pointer technique )
{
    storm_assert( technique );
    if( _rasterizationTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< RasterizationTechniqueOgl >( technique );

    GLenum cullMode = nativeTechnique->getCullMode();
    GLenum fillMode = nativeTechnique->getFillMode();

    const bool cullingEnabled = (cullMode != GL_NONE);
    setBooleanGlState( GL_CULL_FACE, cullingEnabled );

    if( cullingEnabled ) {
        ::glFrontFace( GL_CW );
        checkResult( "::glFrontFace" );

        ::glCullFace( cullMode );
        checkResult( "::glCullFace" );
    }

    ::glPolygonMode( GL_FRONT_AND_BACK, fillMode );
    checkResult( "::glPolygonMode" );

    const auto &description = nativeTechnique->getDescription();

    setBooleanGlState( GL_SCISSOR_TEST, description.rectangleClippingEnabled );
    setBooleanGlState( GL_DEPTH_CLAMP, !description.depthClippingEnabled );

    ::glPolygonOffset( description.slopeScaleDepthBias, description.depthBias );
    checkResult( "::glPolygonOffset" );

    _rasterizationTechnique = technique;
    return;
}

void RenderingSystemOgl::setOutputTechnique(
    OutputTechnique::Pointer technique )
{
    storm_assert( technique );
    if( _outputTechnique == technique ) return;

    auto nativeTechnique =
        std::static_pointer_cast< OutputTechniqueOgl >( technique );

    const auto &description = nativeTechnique->getNativeDescription();

    const auto &depthTest = description.depthTest;
    const auto &stencilTest = description.stencilTest;

    setBooleanGlState( GL_DEPTH_TEST, depthTest.enabled );
    setBooleanGlState( GL_STENCIL_TEST, stencilTest.enabled );

    if( depthTest.enabled ) {
        ::glDepthFunc( depthTest.passCondition );
        checkResult( "::glDepthFunc" );
    }

    if( stencilTest.enabled ) {
        ::glStencilOpSeparate(
            GL_FRONT,
            stencilTest.algorithmForFrontFaces.operationOnStencilTestFail,
            stencilTest.algorithmForFrontFaces.operationOnDepthTestFail,
            stencilTest.algorithmForFrontFaces.operationOnDepthTestPass );
        checkResult( "::glStencilOpSeparate" );

        ::glStencilOpSeparate(
            GL_BACK,
            stencilTest.algorithmForBackFaces.operationOnStencilTestFail,
            stencilTest.algorithmForBackFaces.operationOnDepthTestFail,
            stencilTest.algorithmForBackFaces.operationOnDepthTestPass );
        checkResult( "::glStencilOpSeparate" );

        ::glStencilFuncSeparate(
            GL_FRONT,
            stencilTest.algorithmForFrontFaces.passCondition,
            stencilTest.referenceValue,
            stencilTest.mask );
        checkResult( "::glStencilFuncSeparate" );

        ::glStencilFuncSeparate(
            GL_BACK,
            stencilTest.algorithmForBackFaces.passCondition,
            stencilTest.referenceValue,
            stencilTest.mask );
        checkResult( "::glStencilFuncSeparate" );
    }

    ::glDepthMask( description.writeDepthValues );
    checkResult( "::glDepthMask" );

    _outputTechnique = technique;
    return;
}

void RenderingSystemOgl::setBlendingTechnique(
    BlendingTechnique::Pointer technique )
{
    storm_assert( technique );
    if( _blendingTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< BlendingTechniqueOgl >( technique );

    const BlendingTechniqueOgl::EquationOgl colorEquation =
        nativeTechnique->getColorEquation();
    const BlendingTechniqueOgl::EquationOgl alphaEquation =
        nativeTechnique->getAlphaEquation();

    const bool blendingDisabled =
        colorEquation.operation == GL_FUNC_ADD &&
        alphaEquation.operation == GL_FUNC_ADD &&
        colorEquation.sourceFactor == GL_ONE &&
        alphaEquation.sourceFactor == GL_ONE &&
        colorEquation.destinationFactor == GL_ZERO &&
        alphaEquation.destinationFactor == GL_ZERO;
    const bool blendingEnabled = !blendingDisabled;

    setBooleanGlState( GL_BLEND, blendingEnabled );

    if( blendingEnabled ) {
        if( colorEquation.operation == alphaEquation.operation ) {
            ::glBlendEquation( colorEquation.operation );
            checkResult( "::glBlendEquation" );
        } else {
            ::glBlendEquationSeparate(
                colorEquation.operation,
                alphaEquation.operation );
            checkResult( "::glBlendEquationSeparate" );
        }

        if( colorEquation.sourceFactor == alphaEquation.sourceFactor &&
            colorEquation.destinationFactor == alphaEquation.destinationFactor )
        {
            ::glBlendFunc(
                colorEquation.sourceFactor,
                colorEquation.destinationFactor );
            checkResult( "::glBlendFunc" );
        } else {
            ::glBlendFuncSeparate(
                colorEquation.sourceFactor,
                colorEquation.destinationFactor,
                alphaEquation.sourceFactor,
                alphaEquation.destinationFactor );
            checkResult( "::glBlendFuncSeparate" );
        }
    }

    _blendingTechnique = technique;
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
    if( _framebuffer == framebuffer )
        return;

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
            const Dimensions windowDimensions =
                RenderingWindow::getInstance()->getDimensions();
            width = windowDimensions.width;
            height = windowDimensions.height;
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
    return;
}

void RenderingSystemOgl::clearDepthBuffer( float depth ) {
    const bool depthWritingEnabled =
        _outputTechnique->getDescription().writeDepthValues;

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
    return;
}

void RenderingSystemOgl::clearStencilBuffer( unsigned int stencil ) {
    ::glClearStencil( stencil );
    checkResult( "::glClearStencil" );

    ::glClear( GL_STENCIL_BUFFER_BIT );
    checkResult( "::glClear" );
    return;
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
                message.size(),
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

void RenderingSystemOgl::setBooleanGlState( GLenum state, bool value ) {
    if( value ) {
        ::glEnable( state );
        checkResult( "::glEnable" );
    } else {
        ::glDisable( state );
        checkResult( "::glDisable" );
    }
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
