#include <storm/platform/win/framework_win.h>

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/exception.h>

namespace storm {

FrameworkWin::FrameworkWin() noexcept {
    return;
}

void FrameworkWin::run( const Callback &callback ) {
    if( !callback )
        throwInvalidArgument( "'callback' is invalid" );

    bool processing = true;

    while( processing ) {

        MSG message;

        while( ::PeekMessage(&message, 0, 0, 0, PM_REMOVE) ) {
            if( message.message == WM_QUIT ) {
                processing = false;
            }
            ::TranslateMessage( &message );
            ::DispatchMessage( &message );
        }

        if( !processing )
            break;

        callback();
    }

    return;
}

void FrameworkWin::stop() {
    ::PostQuitMessage( 0 );
    return;
}

std::shared_ptr<FrameworkWin> FrameworkWin::getInstance() {
    static std::shared_ptr<FrameworkWin> instance( new FrameworkWin );
    return instance;
}

std::shared_ptr<Framework> Framework::getInstance() {
    return FrameworkWin::getInstance();
}

}
