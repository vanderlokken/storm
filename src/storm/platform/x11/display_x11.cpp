#include "display_x11.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>

#include <X11/extensions/Xrandr.h>

#include <storm/noncopyable.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

template<class Resource>
class ScopedXRandrResource {
    NONCOPYABLE( ScopedXRandrResource )
public:
    typedef std::function<void (Resource*)> Deleter;

    ScopedXRandrResource( Resource *resource, Deleter deleter ) :
        _resource( resource ),
        _deleter( deleter )
    {
    }

    ScopedXRandrResource( ScopedXRandrResource&& ) = default;
    ScopedXRandrResource& operator = ( ScopedXRandrResource&& ) = default;

    ~ScopedXRandrResource() {
        if( _deleter )
            _deleter( _resource );
    }

    operator Resource* () {
        return _resource;
    }
    Resource* operator -> () {
        return _resource;
    }

private:
    Resource *_resource;
    Deleter _deleter;
};

ScopedXRandrResource<XRRScreenResources> getXRandrScreenResources(
    XDisplay *display )
{
    XRRScreenResources *screenResources =
        ::XRRGetScreenResources( display, ::XDefaultRootWindow(display) );
    if( !screenResources )
        throwRuntimeError( "::XRRGetScreenResources has failed" );
    return ScopedXRandrResource<XRRScreenResources>(
        screenResources, []( XRRScreenResources *screenResources ) {
            ::XRRFreeScreenResources( screenResources );
        });
}

ScopedXRandrResource<XRROutputInfo> getXRandrOutputInfo(
    XDisplay *display, XRRScreenResources *screenResources, RROutput output )
{
    XRROutputInfo *outputInfo =
        ::XRRGetOutputInfo( display, screenResources, output );
    if( !outputInfo )
        throwRuntimeError( "::XRRGetOutputInfo has failed" );
    return ScopedXRandrResource<XRROutputInfo>(
        outputInfo, []( XRROutputInfo *outputInfo ) {
            ::XRRFreeOutputInfo( outputInfo );
        });
}

ScopedXRandrResource<XRRCrtcInfo> getXRandrCrtcInfo(
    XDisplay *display, XRRScreenResources *screenResources, RRCrtc crtc )
{
    XRRCrtcInfo *crtcInfo = ::XRRGetCrtcInfo( display, screenResources, crtc );
    if( !crtcInfo )
        throwRuntimeError( "::XRRGetCrtcInfo has failed" );
    return ScopedXRandrResource<XRRCrtcInfo>(
        crtcInfo, []( XRRCrtcInfo *crtcInfo ) {
            ::XRRFreeCrtcInfo( crtcInfo );
        });
}

ScopedXRandrResource<XRROutputInfo> getFirstConnectedOutput(
    XDisplay *display, XRRScreenResources *screenResources )
{
    for( int outputIndex = 0;
            outputIndex < screenResources->noutput; ++outputIndex )
    {
        auto outputInfo = getXRandrOutputInfo(
            display, screenResources, screenResources->outputs[outputIndex] );

        if( outputInfo->connection == RR_Connected )
            return outputInfo;
    }

    throwRuntimeError( "No video output device is available" );
}

unsigned int getRefreshRate( const XRRModeInfo &mode ) {
    // The following code is adapted from this source:
    // http://cgit.freedesktop.org/xorg/app/xrandr/tree/xrandr.c

    double vTotal = mode.vTotal;

    if( mode.modeFlags & RR_DoubleScan )
        vTotal *= 2;
    if( mode.modeFlags & RR_Interlace )
        vTotal /= 2;

    if( mode.hTotal && vTotal )
        return floor( mode.dotClock / (mode.hTotal * vTotal) + 0.5 );
    else
        return 0;
}

} // namespace

DisplayX11::DisplayX11( XDisplay *display ) :
    _display( display )
{
    int majorVersion = 0;
    int minorVersion = 0;
    const Status supported =
        ::XRRQueryVersion( _display, &majorVersion, &minorVersion );
    if( !supported || (majorVersion <= 1 && minorVersion < 2) )
        throw SystemRequirementsNotMet() <<
            "XRandr 1.2 is not supported by X server";
}

Display::Mode DisplayX11::getDefaultMode() const {
    auto resources = getXRandrScreenResources( _display );
    auto outputInfo = getFirstConnectedOutput( _display, resources );

    auto crtcInfo = getXRandrCrtcInfo( _display, resources, outputInfo->crtc );

    for( int modeIndex = 0; modeIndex < resources->nmode; ++modeIndex ) {
        if( resources->modes[modeIndex].id == crtcInfo->mode ) {
            Mode mode;
            mode.width = resources->modes[modeIndex].width;
            mode.height = resources->modes[modeIndex].height;
            mode.refreshRate =
                getRefreshRate( resources->modes[modeIndex] );
            return mode;
        }
    }

    throwRuntimeError( "Unexpected XRandr data" );
}

std::vector<Display::Mode> DisplayX11::getSupportedModes() const {
    auto resources = getXRandrScreenResources( _display );
    auto outputInfo = getFirstConnectedOutput( _display, resources );

    const std::vector<RRMode> availableModes(
        outputInfo->modes,
        outputInfo->modes + outputInfo->nmode );

    std::vector<Mode> modes;
    for( int modeIndex = 0; modeIndex < resources->nmode; ++modeIndex ) {
        const bool isAvailable = std::find(
            availableModes.begin(),
            availableModes.end(),
            resources->modes[modeIndex].id ) != availableModes.end();
        if( isAvailable ) {
            Mode mode;
            mode.width = resources->modes[modeIndex].width;
            mode.height = resources->modes[modeIndex].height;
            mode.refreshRate = getRefreshRate( resources->modes[modeIndex] );
            modes.push_back( mode );
        }
    }

    return modes;
}

Display* Display::getInstance() {
    static const std::unique_ptr<DisplayX11> instance(
        new DisplayX11(getDisplayHandleX11()) );
    return instance.get();
}

}
