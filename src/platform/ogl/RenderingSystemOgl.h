#ifndef storm_RenderingSystemOgl_h
#define storm_RenderingSystemOgl_h

#include "RenderingSystemCommon.h"

namespace storm {

class RenderingSystemOgl : public RenderingSystemCommon {
public:
    virtual ~RenderingSystemOgl() noexcept { }

    virtual void beginFrameRendering() = 0;
    virtual void endFrameRendering() = 0;

    virtual void renderElementBuffer( std::shared_ptr<ElementBuffer> );

    virtual void setShader( std::shared_ptr<Shader> );

    virtual std::shared_ptr<RasterizationTechnique> getRasterizationTechnique() const noexcept;
    virtual std::shared_ptr<OutputTechnique> getOutputTechnique() const noexcept;
    virtual std::shared_ptr<BlendingTechnique> getBlendingTechnique() const noexcept;

    virtual void setRasterizationTechnique( std::shared_ptr<RasterizationTechnique> );
    virtual void setOutputTechnique( std::shared_ptr<OutputTechnique> );
    virtual void setBlendingTechnique( std::shared_ptr<BlendingTechnique> );

    virtual const Rectangle& getClippingRectangle() const noexcept;
    virtual const Rectangle& getOutputRectangle() const noexcept;

    virtual void setClippingRectangle( const Rectangle& );
    virtual void setOutputRectangle( const Rectangle& );

    virtual void clearColorBuffer( const Color &color = Color::Black );
    virtual void clearDepthBuffer( float depth = 1.0f );
    virtual void clearStencilBuffer( unsigned int stencil = 0 );

    virtual void setColorBufferFormat( ColorBufferFormat ) = 0;
    virtual void setDepthBufferFormat( DepthBufferFormat ) = 0;

protected:
    RenderingSystemOgl() noexcept { }

    void initialize();

private:
    std::shared_ptr<RasterizationTechnique> _rasterizationTechnique;
    std::shared_ptr<OutputTechnique> _outputTechnique;
    std::shared_ptr<BlendingTechnique> _blendingTechnique;
};

}

#endif
