#pragma once

#include <storm/platform/win/api_win.h>

namespace storm {

WNDPROC replaceWindowProcedure( HWND windowHandle, WNDPROC windowProcedure );

}
