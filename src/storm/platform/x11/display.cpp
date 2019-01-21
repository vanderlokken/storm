#include <storm/display.h>

#include <algorithm>
#include <cmath>
#include <memory>
#include <tuple>

#include <xcb/randr.h>

#include <storm/exception.h>
#include <storm/platform/x11/xcb_connection.h>
#include <storm/platform/x11/xcb_pointer.h>

namespace storm {

namespace {

class DisplayImplementation : public Display {
public:
    DisplayImplementation() :
        _connection( XcbConnection::create() ),
        _screenResources( nullptr ),
        _connectedOutput( nullptr )
    {
        queryExtension();

        const xcb_randr_get_screen_resources_cookie_t request =
            xcb_randr_get_screen_resources_unchecked(
                _connection, _connection.getDefaultScreen()->root );

        if( _screenResources = xcb_randr_get_screen_resources_reply(
                _connection, request, nullptr) ) {
            findConnectedOutput();
        }

        if( !_connectedOutput ) {
            throw Exception() << "Couldn't find a connected output device";
        }
    }

    Mode getDefaultMode() const override {
        const xcb_randr_get_crtc_info_cookie_t request =
            xcb_randr_get_crtc_info_unchecked(
                _connection,
                _connectedOutput->crtc,
                _screenResources->config_timestamp );

        const XcbPointer<xcb_randr_get_crtc_info_reply_t> reply =
            xcb_randr_get_crtc_info_reply( _connection, request, nullptr );

        for( xcb_randr_mode_info_iterator_t iterator =
                xcb_randr_get_screen_resources_modes_iterator(_screenResources);
                iterator.rem;
                xcb_randr_mode_info_next(&iterator) ) {
            if( reply && iterator.data->id == reply->mode ) {
                Mode mode;
                mode.width = iterator.data->width;
                mode.height = iterator.data->height;
                mode.refreshRate = getRefreshRate( *iterator.data );
                return mode;
            }
        }

        return {};
    }

    std::vector<Mode> getSupportedModes() const override {
        const std::vector<xcb_randr_mode_t> availableModes(
            xcb_randr_get_output_info_modes(_connectedOutput),
            xcb_randr_get_output_info_modes(_connectedOutput) +
                xcb_randr_get_output_info_modes_length(_connectedOutput) );

        std::vector<Mode> result;

        for( xcb_randr_mode_info_iterator_t iterator =
                xcb_randr_get_screen_resources_modes_iterator(_screenResources);
                iterator.rem;
                xcb_randr_mode_info_next(&iterator) ) {
            const bool isAvailable = std::find(
                availableModes.begin(),
                availableModes.end(),
                iterator.data->id ) != availableModes.end();

            if( isAvailable ) {
                Mode mode;
                mode.width = iterator.data->width;
                mode.height = iterator.data->height;
                mode.refreshRate = getRefreshRate( *iterator.data );
                result.push_back( mode );
            }
        }

        return result;
    }

private:
    static unsigned int getRefreshRate( const xcb_randr_mode_info_t &mode ) {
        // The following code is adapted from this source:
        // http://cgit.freedesktop.org/xorg/app/xrandr/tree/xrandr.c

        double vtotal = mode.vtotal;

        if( mode.mode_flags & XCB_RANDR_MODE_FLAG_DOUBLE_SCAN ) {
            vtotal *= 2;
        }
        if( mode.mode_flags &  XCB_RANDR_MODE_FLAG_INTERLACE ) {
            vtotal /= 2;
        }

        if( mode.htotal && vtotal ) {
            return floor( mode.dot_clock / (mode.htotal * vtotal) + 0.5 );
        }

        return 0;
    }

    void queryExtension() {
        const std::tuple requiredVersion( 1, 2 );

        const xcb_randr_query_version_cookie_t request =
            xcb_randr_query_version_unchecked(
                _connection,
                std::get<0>(requiredVersion),
                std::get<1>(requiredVersion) );

        const XcbPointer<xcb_randr_query_version_reply_t> reply =
            xcb_randr_query_version_reply( _connection, request, nullptr );

        if( !reply || requiredVersion >
                std::make_tuple(reply->major_version, reply->minor_version) ) {
            throw SystemRequirementsNotMet() <<
                "The display server doesn't support version 1.2 of the "
                "'XRandr' extension";
        }
    }

    void findConnectedOutput() {
        const xcb_randr_output_t *startOutput =
            xcb_randr_get_screen_resources_outputs( _screenResources );
        const xcb_randr_output_t *endOutput = startOutput +
            xcb_randr_get_screen_resources_outputs_length( _screenResources );

        for( const xcb_randr_output_t *output = startOutput;
                output != endOutput; ++output ) {
            const xcb_randr_get_output_info_cookie_t request =
                xcb_randr_get_output_info_unchecked(
                    _connection,
                    *output,
                    _screenResources->config_timestamp );

            XcbPointer<xcb_randr_get_output_info_reply_t> reply =
                xcb_randr_get_output_info_reply(
                    _connection, request, nullptr );

            if( reply && reply->connection == XCB_RANDR_CONNECTION_CONNECTED ) {
                _connectedOutput = std::move( reply );
                break;
            }
        }
    }

    XcbConnection _connection;

    XcbPointer<xcb_randr_get_screen_resources_reply_t> _screenResources;
    XcbPointer<xcb_randr_get_output_info_reply_t> _connectedOutput;
};

} // namespace

std::unique_ptr<Display> Display::create() {
    return std::make_unique<DisplayImplementation>();
}

}
