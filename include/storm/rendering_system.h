#pragma once

#include <storm/blending_technique.h>
#include <storm/color.h>
#include <storm/mesh.h>
#include <storm/noexcept.h>
#include <storm/output_technique.h>
#include <storm/rasterization_technique.h>
#include <storm/rectangle.h>
#include <storm/shader.h>

namespace storm {

class RenderingSystem {
public:
    enum class ColorBufferFormat {
        XrgbUint8
    };

    enum class DepthBufferFormat {
        Uint24,
        Uint24Stencil8,
        Uint32
    };

    static RenderingSystem* getInstance();

    virtual ~RenderingSystem() { }

    virtual void beginFrameRendering() = 0;
    virtual void endFrameRendering() = 0;

    virtual void renderMesh( Mesh::Pointer ) = 0;

    virtual Shader::Pointer getShader( Shader::Type ) const noexcept = 0;
    virtual void setShader( Shader::Pointer ) = 0;

    virtual RasterizationTechnique::Pointer getRasterizationTechnique() const noexcept = 0;
    virtual OutputTechnique::Pointer getOutputTechnique() const noexcept = 0;
    virtual BlendingTechnique::Pointer getBlendingTechnique() const noexcept = 0;

    virtual void setRasterizationTechnique( RasterizationTechnique::Pointer ) = 0;
    virtual void setOutputTechnique( OutputTechnique::Pointer ) = 0;
    virtual void setBlendingTechnique( BlendingTechnique::Pointer ) = 0;

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
