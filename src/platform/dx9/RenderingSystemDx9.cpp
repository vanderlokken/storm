#include "RenderingSystemDx9.h"

#include <d3d9.h>

#include <Cg/cgD3D9.h>

#include "BlendingTechniqueDx9.h"
#include "IndexBufferDx9.h"
#include "ElementBufferDx9.h"
#include "platform/win/CheckResult.h"
#include "OutputTechnique.h"
#include "RasterizationTechniqueDx9.h"
#include "RenderingSystem.h"
#include "platform/win/RenderingWindowWin.h"
#include "ShaderDx9.h"
#include "VertexBufferDx9.h"

namespace storm {

RenderingSystemDx9::RenderingSystemDx9() {
    FARPROC address = ::GetProcAddress( ::LoadLibrary(L"d3d9.dll"), "Direct3DCreate9" );

    typedef IDirect3D9* ( WINAPI *direct3dCreate9FunctionPointer )( UINT sdkVersion );

    direct3dCreate9FunctionPointer direct3dCreate9 =
        reinterpret_cast< direct3dCreate9FunctionPointer >( address );

    if( !direct3dCreate9 ) {
        throwRuntimeError( "d3d9.dll is not found" );
    }

    *(_direct3d.getAddress()) = direct3dCreate9( D3D_SDK_VERSION );

    if( !_direct3d ) {
        throwRuntimeError( "::Direct3dCreate9 has failed" );
    }

    const HWND renderingWindowHandle = RenderingWindowWin::getInstance()->getHandle();

    D3DPRESENT_PARAMETERS presentationParameters;
    presentationParameters.BackBufferWidth            = 0;
    presentationParameters.BackBufferHeight           = 0;
    presentationParameters.BackBufferFormat           = D3DFMT_UNKNOWN;
    presentationParameters.BackBufferCount            = 1;
    presentationParameters.MultiSampleType            = D3DMULTISAMPLE_NONE;
    presentationParameters.MultiSampleQuality         = 0;
    presentationParameters.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
    presentationParameters.hDeviceWindow              = renderingWindowHandle;
    presentationParameters.Windowed                   = TRUE;
    presentationParameters.EnableAutoDepthStencil     = FALSE;
    presentationParameters.Flags                      = D3DPRESENTFLAG_DEVICECLIP;
    presentationParameters.FullScreen_RefreshRateInHz = 0;
    presentationParameters.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;

    std::array< DWORD, 4 > behaviours = {
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        D3DCREATE_MIXED_VERTEXPROCESSING,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING
    };

    HRESULT result;

    for( auto behaviour = behaviours.cbegin(); behaviour != behaviours.cend(); ++behaviour ) {

        const UINT adapter = D3DADAPTER_DEFAULT;
        const D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
        const HWND windowHandle = renderingWindowHandle;
        const DWORD behaviourFlags = *behaviour;

        result = _direct3d->CreateDevice(
            adapter, deviceType, windowHandle, behaviourFlags, &presentationParameters, _device.getAddress() );

        if( result == D3D_OK ) break;
    }

    checkResult( result, "IDirect3D9::CreateDevice" );

    cacheDefaultRenderingStates();

    setRasterizationTechnique( RasterizationTechnique::getDefault() );
    setOutputTechnique( OutputTechnique::getDefault() );
    setBlendingTechnique( BlendingTechnique::getDefault() );

    const HRESULT deviceSet = ::cgD3D9SetDevice( _device.get() );
    checkResult( deviceSet, "::cgD3D9SetDevice" );

    return;
}

RenderingSystemDx9::~RenderingSystemDx9() noexcept {
    ::cgD3D9SetDevice( nullptr );
    return;
}

void RenderingSystemDx9::beginFrameRendering() {
    const HRESULT result = _device->BeginScene();
    checkResult( result, "IDirect3DDevice9::BeginScene" );
    return;
}

void RenderingSystemDx9::endFrameRendering() {
    const HRESULT result = _device->EndScene();
    checkResult( result, "IDirect3DDevice9::EndScene" );

    const HRESULT presentationResult = _device->Present( nullptr, nullptr, 0, nullptr );
    checkResult( presentationResult, "IDirect3DDevice9::Present" );
    return;
}

void RenderingSystemDx9::renderElementBuffer(
    std::shared_ptr<ElementBuffer> elementBuffer )
{
    const auto &description = elementBuffer->getDescription();

    auto nativeIndexBuffer = std::static_pointer_cast< IndexBufferDx9 >( description.indexBuffer );
    auto nativeVertexBuffer = std::static_pointer_cast< VertexBufferDx9 >( description.vertexBuffer );

    ComPointer< IDirect3DIndexBuffer9 > indexBuffer = nativeIndexBuffer->getBuffer();
    ComPointer< IDirect3DVertexBuffer9 > vertexBuffer = nativeVertexBuffer->getBuffer();
    ComPointer< IDirect3DVertexDeclaration9 > vertexDeclaration = nativeVertexBuffer->getVertexDeclaration();

    const auto &vertexBufferDescription = nativeVertexBuffer->getDescription();
    const size_t vertexSize = vertexBufferDescription.vertexSize;
    const size_t vertexCount = vertexBufferDescription.bufferSize / vertexSize;

    if( indexBuffer != _cachedIndexBuffer ) {
        const HRESULT result = _device->SetIndices( indexBuffer.get() );
        checkResult( result, "IDirect3DDevice9::SetIndices" );

        _cachedIndexBuffer = indexBuffer;
    }

    if( vertexBuffer != _cachedVertexBuffer ) {
        const UINT streamNumber = 0;
        const UINT offset = 0;
        const UINT stride = vertexSize;

        const HRESULT result = _device->SetStreamSource( streamNumber, vertexBuffer.get(), offset, stride );
        checkResult( result, "IDirect3DDevice9::SetStreamSource" );

        _cachedVertexBuffer = vertexBuffer;
    }

    if( vertexDeclaration != _cachedVertexDeclaration ) {
        const HRESULT result = _device->SetVertexDeclaration( vertexDeclaration.get() );
        checkResult( result, "IDirect3DDevice9::SetVertexDeclaration" );

        _cachedVertexDeclaration = vertexDeclaration;
    }

    auto nativeElementBuffer = std::static_pointer_cast< ElementBufferDx9 >( elementBuffer );

    const D3DPRIMITIVETYPE elementTopology = nativeElementBuffer->getElementTopology();
    const INT baseIndex = 0;
    const UINT minimalIndex = 0;
    const UINT usedVertexCount = vertexCount;
    const UINT startIndex = 0;
    const UINT elementCount = nativeElementBuffer->getElementCount();

    const HRESULT result = _device->DrawIndexedPrimitive(
        elementTopology, baseIndex, minimalIndex, usedVertexCount, startIndex, elementCount );
    checkResult( result, "IDirect3DDevice9::DrawIndexedPrimitive" );

    return;
}

std::shared_ptr<Shader> RenderingSystemDx9::getShader() const noexcept {
    return _shader;
}

void RenderingSystemDx9::setShader( std::shared_ptr<Shader> shader ) {

    auto nativeShader = std::static_pointer_cast< ShaderDx9 >( shader );

    const HRESULT result = ::cgD3D9BindProgram( nativeShader->getProgram() );
    checkResult( result, "::cgD3D9BindProgram" );

    return;
}

std::shared_ptr<RasterizationTechnique> RenderingSystemDx9::getRasterizationTechnique() const noexcept {
    return _rasterizationTechnique;
}

std::shared_ptr<OutputTechnique> RenderingSystemDx9::getOutputTechnique() const noexcept {
    return _outputTechnique;
}

std::shared_ptr<BlendingTechnique> RenderingSystemDx9::getBlendingTechnique() const noexcept {
    return _blendingTechnique;
}

void RenderingSystemDx9::setRasterizationTechnique(
    std::shared_ptr<RasterizationTechnique> technique )
{
    if( _rasterizationTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< RasterizationTechniqueDx9 >( technique );
    setRenderingState( D3DRS_CULLMODE, nativeTechnique->getCullMode() );
    setRenderingState( D3DRS_FILLMODE, nativeTechnique->getFillMode() );

    const auto &description = technique->getDescription();
    setRenderingState( D3DRS_SCISSORTESTENABLE,   description.rectangleClippingEnabled );
    setRenderingState( D3DRS_DEPTHBIAS,           description.depthBias );

    unsigned int value = *reinterpret_cast< const unsigned int* >( &description.slopeScaleDepthBias );
    setRenderingState( D3DRS_SLOPESCALEDEPTHBIAS, value );

    _rasterizationTechnique = technique;
    return;
}

void RenderingSystemDx9::setOutputTechnique(
    std::shared_ptr<OutputTechnique> technique )
{
    if( _outputTechnique == technique ) return;

    const auto &description = technique->getDescription();
    setRenderingState( D3DRS_ZENABLE, true );

    _outputTechnique = technique;
    return;
}

void RenderingSystemDx9::setBlendingTechnique(
    std::shared_ptr<BlendingTechnique> technique )
{
    if( _blendingTechnique == technique ) return;

    auto nativeTechnique = std::static_pointer_cast< BlendingTechniqueDx9 >( technique );

    if( nativeTechnique ) {
        setRenderingState( D3DRS_ALPHABLENDENABLE, true );
        setRenderingState( D3DRS_BLENDOP,   nativeTechnique->getOperation() );
        setRenderingState( D3DRS_SRCBLEND,  nativeTechnique->getSourceFactor() );
        setRenderingState( D3DRS_DESTBLEND, nativeTechnique->getDestinationFactor() );
    } else {
        setRenderingState( D3DRS_ALPHABLENDENABLE, false );
    }

    _blendingTechnique = technique;
    return;
}

const Rectangle& RenderingSystemDx9::getClippingRectangle() const noexcept {
    throwRuntimeError( "Not implemented" );
    static Rectangle rectangle;
    return rectangle;
}
const Rectangle& RenderingSystemDx9::getOutputRectangle() const noexcept {
    throwRuntimeError( "Not implemented" );
    static Rectangle rectangle;
    return rectangle;
}

void RenderingSystemDx9::setClippingRectangle( const Rectangle &rectangle ) {
    RECT clippingRectangle = {
        rectangle.getX(),
        rectangle.getY(),
        rectangle.getRight(),
        rectangle.getBottom() };

    const HRESULT result = _device->SetScissorRect( &clippingRectangle );
    checkResult( result, "IDirect3DDevice9::SetScissorRect" );
    return;
}

void RenderingSystemDx9::setOutputRectangle( const Rectangle &rectangle ) {
    D3DVIEWPORT9 viewport;
    viewport.X = rectangle.getX();
    viewport.Y = rectangle.getY();
    viewport.Width = rectangle.getWidth();
    viewport.Height = rectangle.getHeight();
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;

    const HRESULT result = _device->SetViewport( &viewport );
    checkResult( result, "IDirect3DDevice9::SetViewport" );
    return;
}

void RenderingSystemDx9::clearColorBuffer( const Color &color ) {
    const DWORD    rectangleCount = 0;
    const D3DRECT* rectangles     = nullptr;
    const DWORD    flags          = D3DCLEAR_TARGET;
    const D3DCOLOR colorValue     = color.get();
    const float    depthValue     = 0;
    const DWORD    stencilValue   = 0;

    const HRESULT result = _device->Clear(
        rectangleCount, rectangles, flags, colorValue, depthValue, stencilValue );
    checkResult( result, "IDirect3DDevice9::Clear" );
    return;
}

void RenderingSystemDx9::clearDepthBuffer( float depth ) {
    const DWORD    rectangleCount = 0;
    const D3DRECT* rectangles     = nullptr;
    const DWORD    flags          = D3DCLEAR_ZBUFFER;
    const D3DCOLOR colorValue     = 0;
    const float    depthValue     = depth;
    const DWORD    stencilValue   = 0;

    const HRESULT result = _device->Clear(
        rectangleCount, rectangles, flags, colorValue, depthValue, stencilValue );
    checkResult( result, "IDirect3DDevice9::Clear" );
    return;
}

void RenderingSystemDx9::clearStencilBuffer( unsigned int stencil ) {
    const DWORD    rectangleCount = 0;
    const D3DRECT* rectangles     = nullptr;
    const DWORD    flags          = D3DCLEAR_STENCIL;
    const D3DCOLOR colorValue     = 0;
    const float    depthValue     = 0;
    const DWORD    stencilValue   = stencil;

    const HRESULT result = _device->Clear(
        rectangleCount, rectangles, flags, colorValue, depthValue, stencilValue );
    checkResult( result, "IDirect3DDevice9::Clear" );
    return;
}

void RenderingSystemDx9::setColorBufferFormat( ColorBufferFormat ) {
    throwRuntimeError( "Not implemented" );
}

void RenderingSystemDx9::setDepthBufferFormat( DepthBufferFormat depthBufferFormat ) {
    ComPointer< IDirect3DSurface9 > surface;

    auto renderingWindow = RenderingWindow::getInstance();
    auto dimensions = renderingWindow->getDimensions();

    const UINT width = dimensions.getWidth();
    const UINT height = dimensions.getHeight();
    const D3DFORMAT format = convertDepthBufferFormat( depthBufferFormat );
    const D3DMULTISAMPLE_TYPE multisampleType = D3DMULTISAMPLE_NONE;
    const DWORD multisampleQuality = 0;
    const BOOL discard = FALSE;

    const HRESULT creationResult = _device->CreateDepthStencilSurface(
        width, height, format, multisampleType, multisampleQuality, discard, surface.getAddress(), nullptr );
    checkResult( creationResult, "IDirect3DDevice9::CreateDepthStencilSurface" );

    const HRESULT result = _device->SetDepthStencilSurface( surface.get() );
    checkResult( result, "IDirect3DDevice9::SetDepthStencilSurface" );
    return;
}

void RenderingSystemDx9::cacheDefaultRenderingStates() {
    // Rasterization technique related states
    _cachedRenderingStates[D3DRS_CULLMODE]            = D3DCULL_CCW;
    _cachedRenderingStates[D3DRS_FILLMODE]            = D3DFILL_SOLID;
    _cachedRenderingStates[D3DRS_SCISSORTESTENABLE]   = FALSE;
    _cachedRenderingStates[D3DRS_DEPTHBIAS]           = 0;
    _cachedRenderingStates[D3DRS_SLOPESCALEDEPTHBIAS] = 0;

    // Blending technique related states
    _cachedRenderingStates[D3DRS_ALPHABLENDENABLE]    = FALSE;
    _cachedRenderingStates[D3DRS_BLENDOP]             = D3DBLENDOP_ADD;
    _cachedRenderingStates[D3DRS_SRCBLEND]            = D3DBLEND_ONE;
    _cachedRenderingStates[D3DRS_DESTBLEND]           = D3DBLEND_ZERO;

    // Output technique related states
    _cachedRenderingStates[D3DRS_ZENABLE]             = D3DZB_FALSE;
    _cachedRenderingStates[D3DRS_ZFUNC]               = D3DCMP_LESSEQUAL;

    _cachedRenderingStates[D3DRS_STENCILENABLE]       = FALSE;
    _cachedRenderingStates[D3DRS_STENCILFAIL]         = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_STENCILZFAIL]        = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_STENCILPASS]         = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_STENCILFUNC]         = D3DCMP_ALWAYS;
    _cachedRenderingStates[D3DRS_STENCILREF]          = 0;
    _cachedRenderingStates[D3DRS_STENCILMASK]         = ~0U;
    _cachedRenderingStates[D3DRS_STENCILWRITEMASK]    = ~0U;
    _cachedRenderingStates[D3DRS_TWOSIDEDSTENCILMODE] = FALSE;
    _cachedRenderingStates[D3DRS_CCW_STENCILFAIL]     = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_CCW_STENCILZFAIL]    = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_CCW_STENCILPASS]     = D3DSTENCILOP_KEEP;
    _cachedRenderingStates[D3DRS_CCW_STENCILFUNC]     = D3DCMP_ALWAYS;

    _cachedRenderingStates[D3DRS_ZWRITEENABLE]        = TRUE;

    return;
}

void RenderingSystemDx9::setRenderingState( D3DRENDERSTATETYPE state, unsigned int value ) {
    if( _cachedRenderingStates[state] != value ) {
        const HRESULT result = _device->SetRenderState( state, value );
        checkResult( result, "IDirect3DDevice9::SetRenderState" );

        _cachedRenderingStates[state] = value;
    }
    return;
}

D3DFORMAT RenderingSystemDx9::convertColorBufferFormat( ColorBufferFormat format ) {
    D3DFORMAT result;

    switch( format ) {
    case ColorBufferFormatXrgbUint8:
        result = D3DFMT_X8R8G8B8;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }
    return result;
}

D3DFORMAT RenderingSystemDx9::convertDepthBufferFormat( DepthBufferFormat format ) {
    D3DFORMAT result;

    switch( format ) {
    case DepthBufferFormatUint24:
        result = D3DFMT_D24X8;
        break;

    case DepthBufferFormatUint24Stencil8:
        result = D3DFMT_D24S8;
        break;

    case DepthBufferFormatUint32:
        result = D3DFMT_D32;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }
    return result;
}

ComPointer< IDirect3DDevice9 > RenderingSystemDx9::getDevice() {
    return getInstance()->_device;
}

std::shared_ptr<RenderingSystemDx9> RenderingSystemDx9::getInstance() {
    static std::shared_ptr<RenderingSystemDx9> instance( new RenderingSystemDx9 );
    return instance;
}

std::shared_ptr<RenderingSystem> RenderingSystem::getInstance() {
    return RenderingSystemDx9::getInstance();
}

}