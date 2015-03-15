#include <storm/platform/ogl/rendering_system_ogl.h>

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

    _programPipeline.reset( new ProgramPipelineHandleOgl );

    ::glBindProgramPipeline( *_programPipeline );
    checkResult( "::glBindProgramPipeline" );

    _backbuffer.reset( new BackbufferOgl );

    _primitiveRestartIndex = 0xffff;
    ::glPrimitiveRestartIndex( _primitiveRestartIndex );

    setBooleanGlState( GL_PRIMITIVE_RESTART, true );
}

void RenderingSystemOgl::beginFrameRendering() {
    return;
}

void RenderingSystemOgl::endFrameRendering() {
    return;
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh ) {
    storm_assert( mesh );

    auto nativeMesh = std::static_pointer_cast< MeshOgl >( mesh );

    ::glBindVertexArray( nativeMesh->getHandle() );
    checkResult( "::glBindVertexArray" );

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

    ::glDrawElements( primitiveTopology, indexCount, indexFormat, indexOffset );
    checkResult( "::glDrawElements" );
    return;
}

void RenderingSystemOgl::setShader( Shader::Pointer shader ) {
    storm_assert( shader );

    const Shader::Type shaderType = shader->getType();

    if( getShader(shaderType) == shader )
        return;

    RenderingSystemCommon::setShader( shader );

    const auto nativeShader = std::static_pointer_cast< ShaderOgl >( shader );

    GLbitfield stage = 0;
    if( shaderType == Shader::Type::Vertex )
        stage = GL_VERTEX_SHADER_BIT;
    else if( shaderType == Shader::Type::Pixel )
        stage = GL_FRAGMENT_SHADER_BIT;
    else if( shaderType == Shader::Type::Geometry )
        stage = GL_GEOMETRY_SHADER_BIT;

    ::glUseProgramStages( *_programPipeline, stage, nativeShader->getHandle() );
    checkResult( "::glUseProgramStages" );

    nativeShader->install();
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
        ::glBlendEquationSeparate(
            colorEquation.operation,
            alphaEquation.operation );
        checkResult( "::glBlendEquationSeparate" );

        ::glBlendFuncSeparate(
            colorEquation.sourceFactor,
            colorEquation.destinationFactor,
            alphaEquation.sourceFactor,
            alphaEquation.destinationFactor );
        checkResult( "::glBlendFuncSeparate" );
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

void RenderingSystemOgl::setFramebuffer( Framebuffer::Pointer framebuffer ) {
    if( _framebuffer == framebuffer )
        return;

    auto nativeFramebuffer =
        std::static_pointer_cast< FramebufferOgl >( framebuffer );

    const GLint framebufferHandle =
        nativeFramebuffer ? nativeFramebuffer->getHandle() : 0;

    ::glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    checkResult( "::glBindFramebuffer" );

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

            ::glGetDebugMessageLog(
                /* messageCount = */ 1,
                message.size(),
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                &message[0] );
            checkResult( "::glGetDebugMessageLog" );

            // Remove null character.
            message.erase( message.size() - 1 );

            log += message + '\n';
        }
    }
    return log;
}

void RenderingSystemOgl::installOpenGlContext() {
    // OpenGL context is installed when the rendering system is being created
    RenderingSystem::getInstance();
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

}
