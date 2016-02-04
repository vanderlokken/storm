#include <storm/platform/win/event_loop_win.h>

#include <memory>

namespace storm {

EventLoopWin::EventLoopWin() :
    _acceleratorTableHandle( 0 )
{
    ACCEL accelerator;
    accelerator.fVirt = FALT | FVIRTKEY;
    accelerator.key = VK_RETURN;
    accelerator.cmd = ToggleFullscreenModeCommand;

    _acceleratorTableHandle = ::CreateAcceleratorTable( &accelerator, 1 );
}

EventLoopWin::~EventLoopWin() {
    ::DestroyAcceleratorTable( _acceleratorTableHandle );
}

void EventLoopWin::processEvents() {
    MSG message;

    while( ::PeekMessage(&message, 0, 0, 0, PM_REMOVE) ) {
        if( !::TranslateAccelerator(
                message.hwnd, _acceleratorTableHandle, &message) ) {
            ::TranslateMessage( &message );
            ::DispatchMessage( &message );
        }
    }

    _eventsProcessed = true;
}

EventLoop* EventLoop::getInstance() {
    static const std::unique_ptr<EventLoopWin> instance( new EventLoopWin );
    return instance.get();
}

}
