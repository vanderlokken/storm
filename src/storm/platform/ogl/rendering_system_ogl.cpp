#include <storm/platform/ogl/rendering_system_ogl.h>

#include <storm/platform/ogl/api_ogl.h>

#include <storm/platform/ogl/blending_technique_ogl.h>
#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/mesh_ogl.h>
#include <storm/platform/ogl/output_technique_ogl.h>
#include <storm/platform/ogl/rasterization_technique_ogl.h>
#include <storm/platform/ogl/rendering_buffer_set_ogl.h>
#include <storm/platform/ogl/shader_ogl.h>

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
        if( !supportStatus.ARB_separate_shader_objects ||
            !supportStatus.ARB_texture_storage ||
            !supportStatus.ARB_texture_storage_multisample )
        {
            throw SystemRequirementsNotMet(
                "Video driver doesn't support required OpenGL extension" );
        }
    }

    setRasterizationTechnique( RasterizationTechnique::getDefault() );
    setOutputTechnique( OutputTechnique::getDefault() );
    setBlendingTechnique( BlendingTechnique::getDefault() );

    _programPipeline.reset( new ProgramPipelineHandleOgl );

    ::glBindProgramPipeline( *_programPipeline );
    checkResult( "::glBindProgramPipeline" );
}

void RenderingSystemOgl::beginFrameRendering() {
    return;
}

void RenderingSystemOgl::endFrameRendering() {
    return;
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh ) {
    auto nativeMesh = std::static_pointer_cast< MeshOgl >( mesh );

    ::glBindVertexArray( nativeMesh->getHandle() );
    checkResult( "::glBindVertexArray" );

    const auto &indexBufferDescription =
        mesh->getDescription().indexBuffer->getDescription();

    storm_assert(
        indexBufferDescription.elementSize == 2 ||
        indexBufferDescription.elementSize == 4 );

    const GLenum triangleTopology = nativeMesh->getTriangleTopology();
    const GLsizei indexCount =
        indexBufferDescription.size / indexBufferDescription.elementSize;
    const GLenum indexFormat = (indexBufferDescription.elementSize == 2) ?
        GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    const GLvoid *indexOffset = nullptr;

    ::glDrawElements( triangleTopology, indexCount, indexFormat, indexOffset );
    checkResult( "::glDrawElements" );
    return;
}

void RenderingSystemOgl::setShader( Shader::Pointer shader ) {
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
    if( _blendingTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< BlendingTechniqueOgl >( technique );

    const bool blendingEnabled = static_cast< bool >( nativeTechnique );
    setBooleanGlState( GL_BLEND, blendingEnabled );

    if( blendingEnabled ) {
        GLenum operation = nativeTechnique->getOperation();
        GLenum sourceFactor = nativeTechnique->getSourceFactor();
        GLenum destinationFactor = nativeTechnique->getDestinationFactor();

        ::glBlendEquation( operation );
        checkResult( "::glBlendEquation" );

        ::glBlendFunc( sourceFactor, destinationFactor );
        checkResult( "::glBlendFunc" );
    }

    _blendingTechnique = technique;
    return;
}

const Rectangle& RenderingSystemOgl::getClippingRectangle() const {
    throwRuntimeError( "Not implemented" );
    static const Rectangle rectangle;
    return rectangle;
}

const Rectangle& RenderingSystemOgl::getOutputRectangle() const {
    throwRuntimeError( "Not implemented" );
    static const Rectangle rectangle;
    return rectangle;
}

void RenderingSystemOgl::setClippingRectangle( const Rectangle &rectangle ) {
    ::glScissor(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    checkResult( "::glScissor" );
}

void RenderingSystemOgl::setOutputRectangle( const Rectangle &rectangle ) {
    ::glViewport(
        rectangle.x,
        rectangle.y,
        rectangle.width,
        rectangle.height );
    checkResult( "::glViewport" );
}

void RenderingSystemOgl::setRenderingBufferSet(
    RenderingBufferSet::Pointer renderingBufferSet )
{
    if( _renderingBufferSet == renderingBufferSet )
        return;

    auto nativeBufferSet =
        std::static_pointer_cast< RenderingBufferSetOgl >( renderingBufferSet );

    const GLint framebufferHandle =
        nativeBufferSet ? nativeBufferSet->getHandle() : 0;

    ::glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    checkResult( "::glBindFramebuffer" );

    _renderingBufferSet = renderingBufferSet;
}

void RenderingSystemOgl::clearColorBuffer( const Color &color ) {
    const GLclampf r = color.getNormalizedR();
    const GLclampf g = color.getNormalizedG();
    const GLclampf b = color.getNormalizedB();
    const GLclampf a = color.getNormalizedA();

    ::glClearColor( r, g, b, a );
    checkResult( "::glClearColor" );

    ::glClear( GL_COLOR_BUFFER_BIT );
    checkResult( "::glClear" );
    return;
}

void RenderingSystemOgl::clearDepthBuffer( float depth ) {
    ::glClearDepth( depth );
    checkResult( "::glClearDepth" );

    ::glClear( GL_DEPTH_BUFFER_BIT );
    checkResult( "::glClear" );
    return;
}

void RenderingSystemOgl::clearStencilBuffer( unsigned int stencil ) {
    ::glClearStencil( stencil );
    checkResult( "::glClearStencil" );

    ::glClear( GL_STENCIL_BUFFER_BIT );
    checkResult( "::glClear" );
    return;
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
