#ifndef storm_RenderingSystem_h
#define storm_RenderingSystem_h

#include <memory>

#include "Color.h"
#include "Noexcept.h"
#include "Rectangle.h"

namespace storm {

class BlendingTechnique;
class ElementBuffer;
class OutputTechnique;
class RasterizationTechnique;
class Shader;

class RenderingSystem {
public:
    enum ColorBufferFormat {
        ColorBufferFormatXrgbUint8
    };
    
    enum DepthBufferFormat {
        DepthBufferFormatUint24,
        DepthBufferFormatUint24Stencil8,
        DepthBufferFormatUint32
    };
    
    static std::shared_ptr<RenderingSystem> getInstance();
    
    virtual ~RenderingSystem() noexcept { }
    
    virtual void beginFrameRendering() = 0;
    virtual void endFrameRendering() = 0;
    
    virtual void renderElementBuffer( std::shared_ptr<ElementBuffer> ) = 0;
    
    virtual std::shared_ptr<Shader> getShader() const noexcept = 0;
    virtual void setShader( std::shared_ptr<Shader> ) = 0;
    
    virtual std::shared_ptr<RasterizationTechnique> getRasterizationTechnique() const noexcept = 0;
    virtual std::shared_ptr<OutputTechnique> getOutputTechnique() const noexcept = 0;
    virtual std::shared_ptr<BlendingTechnique> getBlendingTechnique() const noexcept = 0;
    
    virtual void setRasterizationTechnique( std::shared_ptr<RasterizationTechnique> ) = 0;
    virtual void setOutputTechnique( std::shared_ptr<OutputTechnique> ) = 0;
    virtual void setBlendingTechnique( std::shared_ptr<BlendingTechnique> ) = 0;
    
    virtual const Rectangle& getClippingRectangle() const noexcept = 0;
    virtual const Rectangle& getOutputRectangle() const noexcept = 0;
    
    virtual void setClippingRectangle( const Rectangle& ) = 0;
    virtual void setOutputRectangle( const Rectangle& ) = 0;
    
    virtual void clearColorBuffer( const Color &color = Color::Black ) = 0;
    virtual void clearDepthBuffer( float depth = 1.0f ) = 0;
    virtual void clearStencilBuffer( unsigned int stencil = 0 ) = 0;
    
    virtual void setColorBufferFormat( ColorBufferFormat ) = 0;
    virtual void setDepthBufferFormat( DepthBufferFormat ) = 0;
};

}

#endif