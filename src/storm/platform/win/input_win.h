#pragma once

#include <storm/platform/win/api_win.h>

namespace storm {

    void registerInputDevice( USHORT usagePage, USHORT usage, DWORD flags = 0 );
RAWINPUT receiveInputData( HRAWINPUT handle );

}
