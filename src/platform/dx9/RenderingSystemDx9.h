#ifndef storm_RenderingSystemDx9_h
#define storm_RenderingSystemDx9_h

#include <array>

#include "CoreTypesDx9.h"
#include "Noncopyable.h"
#include "platform/win/ComPointer.h"
#include "RenderingSystemCommon.h"

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DIndexBuffer9;
struct IDirect3DPixelShader9;
struct IDirect3DVertexBuffer9;
struct IDirect3DVertexDeclaration9;
struct IDirect3DVertexShader9;

namespace storm {

class RenderingSystemDx9 : public RenderingSystemCommon {
    NONCOPYABLE( RenderingSystemDx9 );
public:
    static std::shared_ptr<RenderingSystemDx9> getInstance();

    virtual ~RenderingSystemDx9() noexcept;

    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual void renderMesh( std::shared_ptr<Mesh> );

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

    virtual void clearColorBuffer( const Color &color );
    virtual void clearDepthBuffer( float depth );
    virtual void clearStencilBuffer( unsigned int stencil );

    virtual void setColorBufferFormat( ColorBufferFormat );
    virtual void setDepthBufferFormat( DepthBufferFormat );

    static ComPointer< IDirect3DDevice9 > getDevice();

private:
    RenderingSystemDx9();

    void cacheDefaultRenderingStates();

    void setRenderingState( D3DRENDERSTATETYPE state, unsigned int value );

    static D3DFORMAT convertColorBufferFormat( ColorBufferFormat );
    static D3DFORMAT convertDepthBufferFormat( DepthBufferFormat );

    ComPointer< IDirect3D9 > _direct3d;
    ComPointer< IDirect3DDevice9 > _device;

    ComPointer< IDirect3DIndexBuffer9 > _cachedIndexBuffer;
    ComPointer< IDirect3DVertexBuffer9 > _cachedVertexBuffer;
    ComPointer< IDirect3DVertexDeclaration9 > _cachedVertexDeclaration;

    static const size_t RenderingStateCount = 256;
    std::array< unsigned int, RenderingStateCount > _cachedRenderingStates;

    std::shared_ptr< RasterizationTechnique > _rasterizationTechnique;
    std::shared_ptr< OutputTechnique > _outputTechnique;
    std::shared_ptr< BlendingTechnique > _blendingTechnique;
};

}

#endif