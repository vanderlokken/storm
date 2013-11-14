#pragma once

#include <array>

#include <storm/noncopyable.h>
#include <storm/platform/dx9/core_types_dx9.h>
#include <storm/platform/win/com_pointer.h>
#include <storm/rendering_system_common.h>

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
    static RenderingSystemDx9* getInstance();

    virtual ~RenderingSystemDx9();

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

    RasterizationTechnique::Pointer _rasterizationTechnique;
    OutputTechnique::Pointer _outputTechnique;
    BlendingTechnique::Pointer _blendingTechnique;
};

}
