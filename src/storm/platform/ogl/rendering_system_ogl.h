#pragma once

#include <cstdint>
#include <vector>

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/rendering_system_common.h>

namespace storm {

class ProgramPipelineHandleOgl : public HandleOgl {
public:
    ProgramPipelineHandleOgl();
    ~ProgramPipelineHandleOgl();
};

class VertexArrayHandleOgl;

class RenderingSystemOgl : public RenderingSystemCommon {
public:
    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual void renderMesh( Mesh::Pointer mesh, unsigned count );
    virtual void renderGenerated(
        unsigned int vertexCount, Mesh::PrimitiveTopology );

    virtual void setShader( Shader::Pointer );
    virtual void resetShader( Shader::Type );

    virtual size_t getRootBufferSize() const;
    virtual void setRootBufferData(
        size_t offset, size_t size, const void *data );

    virtual RasterizationTechnique::Pointer getRasterizationTechnique() const;
    virtual OutputTechnique::Pointer getOutputTechnique() const;
    virtual BlendingTechnique::Pointer getBlendingTechnique() const;

    virtual void setRasterizationTechnique( RasterizationTechnique::Pointer );
    virtual void setOutputTechnique( OutputTechnique::Pointer );
    virtual void setBlendingTechnique( BlendingTechnique::Pointer );

    virtual const Rectangle& getClippingRectangle() const;
    virtual const Rectangle& getOutputRectangle() const;

    virtual void setClippingRectangle( const Rectangle& );
    virtual void setOutputRectangle( const Rectangle& );

    virtual Framebuffer::Pointer getFramebuffer() const;
    virtual void setFramebuffer(
        Framebuffer::Pointer, bool preserveOutputRectangle );

    virtual void clearColorBuffer( const Color &color = Color::Black );
    virtual void clearDepthBuffer( float depth = 1.0f );
    virtual void clearStencilBuffer( unsigned int stencil = 0 );

    virtual Backbuffer::Pointer getBackbuffer() const;

    virtual std::string getDebugMessageLog() const;

    // This method should be called to prevent situations when OpenGL API is
    // being accessed with no context being installed.
    static void installOpenGlContext();

protected:
    void initialize();

private:
    static void setBooleanGlState( GLenum state, bool value );
    static GLbitfield selectShaderStage( Shader::Type shaderType );

    void bindVertexArray( GLuint vertexArray );

    // These objects should be constructed after OpenGL context creation. To
    // ensure this we're using heap allocation instead of stack allocation.
    std::shared_ptr<ProgramPipelineHandleOgl> _programPipeline;
    std::shared_ptr<VertexArrayHandleOgl> _vertexArrayWithoutData;

    RasterizationTechnique::Pointer _rasterizationTechnique;
    OutputTechnique::Pointer _outputTechnique;
    BlendingTechnique::Pointer _blendingTechnique;

    Rectangle _clippingRectangle;
    Rectangle _outputRectangle;

    Framebuffer::Pointer _framebuffer;
    Backbuffer::Pointer _backbuffer;

    GLuint _vertexArray;
    GLuint _primitiveRestartIndex;

    std::vector<uint8_t> _rootBufferData;
};

}
