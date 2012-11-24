#include "Dimensions.h"

namespace storm {

Dimensions::Dimensions() noexcept : _width( 0 ), _height( 0 ) { }

Dimensions::Dimensions( unsigned int width, unsigned int height ) noexcept
    : _width( width ), _height( height ) { }

unsigned int Dimensions::getWidth() const noexcept {
    return _width;
}

unsigned int Dimensions::getHeight() const noexcept {
    return _height;
}

void Dimensions::setWidth( unsigned int width ) noexcept {
    _width = width;
    return;
}

void Dimensions::setHeight( unsigned int height ) noexcept {
    _height = height;
    return;
}

bool Dimensions::operator == ( const Dimensions &dimensions ) const noexcept {
    return
        _width == dimensions._width &&
        _height == dimensions._height;
}

bool Dimensions::operator != ( const Dimensions &dimensions ) const noexcept {
    return
        _width != dimensions._width ||
        _height != dimensions._height;
}

}