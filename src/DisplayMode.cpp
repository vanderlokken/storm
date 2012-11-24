#include "Display.h"

namespace storm {

Display::Mode::Mode(
    unsigned int width,
    unsigned int height,
    unsigned int refreshRate,
    unsigned int colorDepth ) noexcept
    
  : _width( width ),
    _height( height ),
    _refreshRate( refreshRate ),
    _colorDepth( colorDepth ) { }

unsigned int Display::Mode::getWidth() const noexcept {
    return _width;
}

unsigned int Display::Mode::getHeight() const noexcept {
    return _height;
}

unsigned int Display::Mode::getRefreshRate() const noexcept {
    return _refreshRate;
}

unsigned int Display::Mode::getColorDepth() const noexcept {
    return _colorDepth;
}

bool Display::Mode::operator == ( const Display::Mode &mode ) const noexcept {
    return
        _width == mode._width &&
        _height == mode._height &&
        _refreshRate == mode._refreshRate &&
        _colorDepth == mode._colorDepth;
}

bool Display::Mode::operator != ( const Display::Mode &mode ) const noexcept {
    return
        _width != mode._width ||
        _height != mode._height ||
        _refreshRate != mode._refreshRate ||
        _colorDepth != mode._colorDepth;
}

}