#pragma once

#include <storm/rendering_system_common.h>

namespace storm {

class RenderingSystemOgl : public RenderingSystemCommon {
public:
    virtual void beginFrameRendering() = 0;
    virtual void endFrameRendering() = 0;

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

    virtual void clearColorBuffer( const Color &color = Color::Black );
    virtual void clearDepthBuffer( float depth = 1.0f );
    virtual void clearStencilBuffer( unsigned int stencil = 0 );

    virtual void setColorBufferFormat( ColorBufferFormat ) = 0;
    virtual void setDepthBufferFormat( DepthBufferFormat ) = 0;

    // This method should be called to prevent situations when OpenGL API is
    // being accessed with no context being installed.
    static void installOpenGlContext();

protected:
    void initialize();

private:
    RasterizationTechnique::Pointer _rasterizationTechnique;
    OutputTechnique::Pointer _outputTechnique;
    BlendingTechnique::Pointer _blendingTechnique;
};

}
