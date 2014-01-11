#include <storm/platform/ogl/rendering_system_ogl.h>

#include <storm/platform/ogl/api_ogl.h>

#include <storm/output_technique.h>
#include <storm/platform/ogl/blending_technique_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/index_buffer_ogl.h>
#include <storm/platform/ogl/mesh_ogl.h>
#include <storm/platform/ogl/rasterization_technique_ogl.h>
#include <storm/platform/ogl/shader_ogl.h>
#include <storm/platform/ogl/vertex_buffer_ogl.h>

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
    setRasterizationTechnique( RasterizationTechnique::getDefault() );
    setOutputTechnique( OutputTechnique::getDefault() );
    setBlendingTechnique( BlendingTechnique::getDefault() );

    _programPipeline.reset( new ProgramPipelineHandleOgl );

    ::glBindProgramPipeline( *_programPipeline );
    checkResult( "::glBindProgramPipeline" );
    return;
}

void RenderingSystemOgl::renderMesh( Mesh::Pointer mesh ) {
    const auto &description = mesh->getDescription();

    auto nativeMesh = std::static_pointer_cast< MeshOgl >( mesh );
    auto nativeIndexBuffer = std::static_pointer_cast< IndexBufferOgl >( description.indexBuffer );

    ::glBindVertexArray( nativeMesh->getHandle() );
    checkResult( "::glBindVertexArray" );

    const GLenum triangleTopology = nativeMesh->getTriangleTopology();
    const GLsizei indexCount = nativeIndexBuffer->getDescription().bufferSize / nativeIndexBuffer->getDescription().indexSize;
    const GLenum indexFormat = nativeIndexBuffer->getIndexFormat();
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

    nativeShader->bindSamplers();
}

RasterizationTechnique::Pointer RenderingSystemOgl::getRasterizationTechnique() const noexcept {
    return _rasterizationTechnique;
}

OutputTechnique::Pointer RenderingSystemOgl::getOutputTechnique() const noexcept {
    return _outputTechnique;
}

BlendingTechnique::Pointer RenderingSystemOgl::getBlendingTechnique() const noexcept {
    return _blendingTechnique;
}

void RenderingSystemOgl::setRasterizationTechnique(
    RasterizationTechnique::Pointer technique )
{
    if( _rasterizationTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< RasterizationTechniqueOgl >( technique );

    GLenum cullMode = nativeTechnique->getCullMode();
    GLenum fillMode = nativeTechnique->getFillMode();

    if( cullMode != GL_NONE ) {
        ::glEnable( GL_CULL_FACE );
        checkResult( "::glEnable" );

        ::glFrontFace( GL_CW );
        checkResult( "::glFrontFace" );

        ::glCullFace( cullMode );
        checkResult( "::glCullFace" );
    } else {
        ::glDisable( GL_CULL_FACE );
        checkResult( "::glDisable" );
    }

    ::glPolygonMode( GL_FRONT_AND_BACK, fillMode );
    checkResult( "::glPolygonMode" );

    const auto &description = nativeTechnique->getDescription();

    if( description.rectangleClippingEnabled ) {
        ::glEnable( GL_SCISSOR_TEST );
        checkResult( "::glEnable" );
    } else {
        ::glDisable( GL_SCISSOR_TEST );
        checkResult( "::glDisable" );
    }

    ::glPolygonOffset( description.slopeScaleDepthBias, description.depthBias );
    checkResult( "::glPolygonOffset" );

    _rasterizationTechnique = technique;
    return;
}

void RenderingSystemOgl::setOutputTechnique(
    OutputTechnique::Pointer technique )
{
    if( _outputTechnique == technique ) return;

    ::glEnable( GL_DEPTH_TEST );
    checkResult( "::glEnable" );

    _outputTechnique = technique;
    return;
}

void RenderingSystemOgl::setBlendingTechnique(
    BlendingTechnique::Pointer technique )
{
    if( _blendingTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< BlendingTechniqueOgl >( technique );

    if( nativeTechnique ) {
        ::glEnable( GL_BLEND );
        checkResult( "::glEnable" );

        GLenum operation = nativeTechnique->getOperation();
        GLenum sourceFactor = nativeTechnique->getSourceFactor();
        GLenum destinationFactor = nativeTechnique->getDestinationFactor();

        ::glBlendEquation( operation );
        checkResult( "::glBlendEquation" );

        ::glBlendFunc( sourceFactor, destinationFactor );
        checkResult( "::glBlendFunc" );
    } else {
        ::glDisable( GL_BLEND );
        checkResult( "::glDisable" );
    }

    _blendingTechnique = technique;
    return;
}

const Rectangle& RenderingSystemOgl::getClippingRectangle() const noexcept {
    throwRuntimeError( "Not implemented" );
    static const Rectangle rectangle;
    return rectangle;
}

const Rectangle& RenderingSystemOgl::getOutputRectangle() const noexcept {
    throwRuntimeError( "Not implemented" );
    static const Rectangle rectangle;
    return rectangle;
}

void RenderingSystemOgl::setClippingRectangle( const Rectangle &rectangle ) {
    ::glScissor(
        rectangle.getX(),
        rectangle.getY(),
        rectangle.getWidth(),
        rectangle.getHeight() );

    checkResult( "::glScissor" );
    return;
}

void RenderingSystemOgl::setOutputRectangle( const Rectangle &rectangle ) {
    ::glViewport(
        rectangle.getX(),
        rectangle.getY(),
        rectangle.getWidth(),
        rectangle.getHeight() );

    checkResult( "::glViewport" );
    return;
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

}
