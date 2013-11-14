#include <storm/platform/win/input_win.h>

#include <storm/exception.h>
#include <storm/platform/win/rendering_window_win.h>

namespace storm {

void registerInputDevice( USHORT usagePage, USHORT usage, DWORD flags ) {

    RAWINPUTDEVICE device;
    device.usUsagePage = usagePage;
    device.usUsage     = usage;
    device.dwFlags     = flags;
    device.hwndTarget  = RenderingWindowWin::getInstance()->getHandle();

    const UINT deviceCount = 1;
    const UINT deviceSize = sizeof( RAWINPUTDEVICE );

    const BOOL succeeded = ::RegisterRawInputDevices( &device, deviceCount, deviceSize );

    if( !succeeded )
        throwRuntimeError( "::RegisterRawInputDevices has failed" );

    return;

}

RAWINPUT receiveInputData( HRAWINPUT handle ) {

    const UINT command    = RID_INPUT;
      RAWINPUT data;
          UINT dataSize   = sizeof( data );
    const UINT headerSize = sizeof( data.header );

    const UINT result = ::GetRawInputData( handle, command, &data, &dataSize, headerSize );
    const UINT error = ~0U;

    if( result == error )
        throwRuntimeError( "::GetRawInputData has failed" );

    return data;

}

}