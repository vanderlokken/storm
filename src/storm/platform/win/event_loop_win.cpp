#include <storm/platform/win/event_loop_win.h>

#include <memory>

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

namespace storm {

void EventLoopWin::processEvents() {
    MSG message;

    while( ::PeekMessage(&message, 0, 0, 0, PM_REMOVE) ) {
        ::TranslateMessage( &message );
        ::DispatchMessage( &message );
    }

    _eventsProcessed = true;
}

EventLoop* EventLoop::getInstance() {
    static const std::unique_ptr<EventLoopWin> instance( new EventLoopWin );
    return instance.get();
}

}
