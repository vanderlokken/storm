#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/noexcept.h>

namespace storm {

WNDPROC replaceWindowProcedure( HWND windowHandle, WNDPROC windowProcedure ) noexcept;

}
