#pragma once

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/rendering_system_common.h>

namespace storm {

class ProgramPipelineHandleOgl : public HandleOgl {
public:
    ProgramPipelineHandleOgl();
    ~ProgramPipelineHandleOgl();
};

class RenderingSystemOgl : public RenderingSystemCommon {
public:
    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual void renderMesh( Mesh::Pointer );

    virtual void setShader( Shader::Pointer );

    virtual RasterizationTechnique::Pointer getRasterizationTechnique() const noexcept;
    virtual OutputTechnique::Pointer getOutputTechnique() const noexcept;
    virtual BlendingTechnique::Pointer getBlendingTechnique() const noexcept;

    virtual void setRasterizationTechnique( RasterizationTechnique::Pointer );
    virtual void setOutputTechnique( OutputTechnique::Pointer );
    virtual void setBlendingTechnique( BlendingTechnique::Pointer );

    virtual const Rectangle& getClippingRectangle() const noexcept;
    virtual const Rectangle& getOutputRectangle() const noexcept;

    virtual void setClippingRectangle( const Rectangle& );
    virtual void setOutputRectangle( const Rectangle& );

    virtual void setRenderingBufferSet( RenderingBufferSet::Pointer );

    virtual void clearColorBuffer( const Color &color = Color::Black );
    virtual void clearDepthBuffer( float depth = 1.0f );
    virtual void clearStencilBuffer( unsigned int stencil = 0 );

    // This method should be called to prevent situations when OpenGL API is
    // being accessed with no context being installed.
    static void installOpenGlContext();

protected:
    void initialize();

private:
    static void setBooleanGlState( GLenum state, bool value );

    // This object should be constructed after OpenGL context creation. To
    // ensure this we're using heap allocation instead of stack allocation.
    std::unique_ptr<ProgramPipelineHandleOgl> _programPipeline;

    RasterizationTechnique::Pointer _rasterizationTechnique;
    OutputTechnique::Pointer _outputTechnique;
    BlendingTechnique::Pointer _blendingTechnique;

    RenderingBufferSet::Pointer _renderingBufferSet;
};

}
