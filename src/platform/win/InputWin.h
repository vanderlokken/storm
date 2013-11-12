#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

namespace storm {

    void registerInputDevice( USHORT usagePage, USHORT usage, DWORD flags = 0 );
RAWINPUT receiveInputData( HRAWINPUT handle );

}
