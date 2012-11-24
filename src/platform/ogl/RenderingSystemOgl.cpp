#include "RenderingSystemOgl.h"

#include "BlendingTechniqueOgl.h"
#include "CheckResultOgl.h"
#include "ElementBufferOgl.h"
#include "IndexBufferOgl.h"
#include "OutputTechnique.h"
#include "RasterizationTechniqueOgl.h"
#include "ShaderOgl.h"
#include "VertexBufferOgl.h"

namespace storm {

void RenderingSystemOgl::initialize() {
    setRasterizationTechnique( RasterizationTechnique::getDefault() );
    setOutputTechnique( OutputTechnique::getDefault() );
    setBlendingTechnique( BlendingTechnique::getDefault() );
    return;
}

void RenderingSystemOgl::renderElementBuffer(
    std::shared_ptr<ElementBuffer> elementBuffer )
{
    const auto &description = elementBuffer->getDescription();
    
    auto nativeElementBuffer = std::static_pointer_cast< ElementBufferOgl >( elementBuffer );
    auto nativeIndexBuffer = std::static_pointer_cast< IndexBufferOgl >( description.indexBuffer );
    
    const GLuint handle = nativeElementBuffer->getHandle();
    
    ::glBindVertexArray( handle );
    checkResult( "::glBindVertexArray" );

    const GLenum elementTopology = nativeElementBuffer->getElementTopology();
    const GLsizei indexCount = nativeIndexBuffer->getDescription().bufferSize / nativeIndexBuffer->getDescription().indexSize;
    const GLenum indexFormat = nativeIndexBuffer->getIndexFormat();
    const GLvoid *indexOffset = nullptr;

    ::glDrawElements( elementTopology, indexCount, indexFormat, indexOffset );
    checkResult( "::glDrawElements" );
    return;
}

std::shared_ptr<Shader> RenderingSystemOgl::getShader() const noexcept {
    return _shader;
}

void RenderingSystemOgl::setShader( std::shared_ptr<Shader> shader ) {
    if( _shader == shader ) return;
    
    auto nativeShader = std::static_pointer_cast< ShaderOgl >( shader );
    
    ::glUseProgram( nativeShader->getProgram() );
    checkResult( "::glUseProgram" );
    
    _shader = shader;
    return;
}

std::shared_ptr<RasterizationTechnique> RenderingSystemOgl::getRasterizationTechnique() const noexcept {
    return _rasterizationTechnique;
}

std::shared_ptr<OutputTechnique> RenderingSystemOgl::getOutputTechnique() const noexcept {
    return _outputTechnique;
}

std::shared_ptr<BlendingTechnique> RenderingSystemOgl::getBlendingTechnique() const noexcept {
    return _blendingTechnique;
}

void RenderingSystemOgl::setRasterizationTechnique(
    std::shared_ptr<RasterizationTechnique> technique )
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
    std::shared_ptr<OutputTechnique> technique )
{
    if( _outputTechnique == technique ) return;
    
    ::glEnable( GL_DEPTH_TEST );
    checkResult( "::glEnable" );
    
    _outputTechnique = technique;
    return;
}

void RenderingSystemOgl::setBlendingTechnique(
    std::shared_ptr<BlendingTechnique> technique )
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

}
