#pragma once

#include <cstdint>
#include <vector>

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/rendering_system_common.h>

namespace storm {

constexpr size_t RootBufferSize = 128;

using ProgramPipelineHandleOgl =
    HandleOgl<GlGenProgramPipelines, GlDeleteProgramPipelines>;

using VertexArrayHandleOgl =
    HandleOgl<GlGenVertexArrays, GlDeleteVertexArrays>;

class RenderingSystemOgl : public RenderingSystemCommon {
public:
    RenderingSystemOgl();

    GpuContext::Pointer getGpuContext() const override;

    void renderMesh( Mesh::Pointer mesh, unsigned count ) override;
    void renderGenerated(
        unsigned int vertexCount, Mesh::PrimitiveTopology ) override;

    void setShader( Shader::Pointer ) override;
    void resetShader( Shader::Type ) override;

    size_t getRootBufferSize() const override;
    void setRootBufferData(
        size_t offset, size_t size, const void *data ) override;

    PipelineState::Pointer getPipelineState() const override;
    void setPipelineState( PipelineState::Pointer ) override;

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

protected:
    void initialize();

private:
    static PipelineState::Pointer createDefaultOpenGlPipelineState();
    static GLbitfield selectShaderStage( Shader::Type shaderType );

    void bindVertexArray( GLuint vertexArray );
    void updateShaderBindings();

    GpuContextOgl::Pointer _gpuContext;

    // These objects should be constructed after OpenGL context creation. To
    // ensure this we're using heap allocation instead of stack allocation.
    std::shared_ptr<ProgramPipelineHandleOgl> _programPipeline;
    std::shared_ptr<VertexArrayHandleOgl> _vertexArrayWithoutData;

    PipelineState::Pointer _pipelineState;

    Rectangle _clippingRectangle;
    Rectangle _outputRectangle;

    Framebuffer::Pointer _framebuffer;
    Backbuffer::Pointer _backbuffer;

    GLuint _vertexArray;
    GLuint _primitiveRestartIndex;

    std::vector<uint8_t> _rootBufferData;
};

}
