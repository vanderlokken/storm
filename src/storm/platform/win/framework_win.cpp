#include <storm/platform/win/framework_win.h>

#include <memory>

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/throw_exception.h>

namespace storm {

FrameworkWin::FrameworkWin() :
    _running( true ), _eventsProcessed( false )
{
}

void FrameworkWin::run( const Callback &callback ) {
    storm_assert( callback );

    while( _running ) {
        _eventsProcessed = false;

        callback();

        if( !_eventsProcessed )
            processInputEvents();
    }
}

void FrameworkWin::stop() {
    ::PostQuitMessage( 0 );
}

void FrameworkWin::processInputEvents() {
    if( _eventsProcessed )
        return;

    MSG message;

    while( ::PeekMessage(&message, 0, 0, 0, PM_REMOVE) ) {
        if( message.message == WM_QUIT ) {
            _running = false;
        }
        ::TranslateMessage( &message );
        ::DispatchMessage( &message );
    }

    _eventsProcessed = true;
}

FrameworkWin* FrameworkWin::getInstance() {
    static const std::unique_ptr<FrameworkWin> instance( new FrameworkWin );
    return instance.get();
}

Framework* Framework::getInstance() {
    return FrameworkWin::getInstance();
}

}
