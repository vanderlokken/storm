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
    void renderMesh( Mesh::Pointer mesh, unsigned count ) override;
    void renderGenerated(
        unsigned int vertexCount, Mesh::PrimitiveTopology ) override;

    void setShader( Shader::Pointer ) override;
    void resetShader( Shader::Type ) override;

    size_t getRootBufferSize() const override;
    void setRootBufferData(
        size_t offset, size_t size, const void *data ) override;

    RasterizationTechnique::Pointer getRasterizationTechnique() const override;
    OutputTechnique::Pointer getOutputTechnique() const override;
    BlendingTechnique::Pointer getBlendingTechnique() const override;

    void setRasterizationTechnique( RasterizationTechnique::Pointer ) override;
    void setOutputTechnique( OutputTechnique::Pointer ) override;
    void setBlendingTechnique( BlendingTechnique::Pointer ) override;

    const Rectangle& getClippingRectangle() const override;
    const Rectangle& getOutputRectangle() const override;

    void setClippingRectangle( const Rectangle& ) override;
    void setOutputRectangle( const Rectangle& ) override;

    Framebuffer::Pointer getFramebuffer() const override;
    void setFramebuffer(
        Framebuffer::Pointer, bool preserveOutputRectangle ) override;

    void clearColorBuffer( const Color &color = Color::Black ) override;
    void clearDepthBuffer( float depth = 1.0f ) override;
    void clearStencilBuffer( unsigned int stencil = 0 ) override;

    Backbuffer::Pointer getBackbuffer() const override;

    std::string getDebugMessageLog() const override;

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
