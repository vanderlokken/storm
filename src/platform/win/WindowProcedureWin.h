#ifndef storm_WindowProcedureWin_h
#define storm_WindowProcedureWin_h

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include "Noexcept.h"

namespace storm {

WNDPROC replaceWindowProcedure( HWND windowHandle, WNDPROC windowProcedure ) noexcept;

}

#endif