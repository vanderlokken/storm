#pragma once

#include <X11/Xlib.h>

// Use an alias to avoid name clashes with storm::Display.
typedef Display XDisplay;

namespace storm {

XDisplay* getDisplayHandleX11();

}
