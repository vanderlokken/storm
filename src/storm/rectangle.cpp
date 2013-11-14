#include <storm/rectangle.h>

namespace storm {

Rectangle::Rectangle() noexcept : _x( 0 ), _y( 0 ), _width( 0 ), _height( 0 ) { }

Rectangle::Rectangle( int x, int y, unsigned int width, unsigned int height ) noexcept
    : _x( x ), _y( y ), _width( width ), _height( height ) { }

int Rectangle::getX() const noexcept {
    return _x;
}

int Rectangle::getY() const noexcept {
    return _y;
}

void Rectangle::setX( int x ) noexcept {
    _x = x;
    return;
}

void Rectangle::setY( int y ) noexcept {
    _y = y;
    return;
}

unsigned int Rectangle::getWidth() const noexcept {
    return _width;
}

unsigned int Rectangle::getHeight() const noexcept {
    return _height;
}

void Rectangle::setWidth( unsigned int width ) noexcept {
    _width = width;
    return;
}

void Rectangle::setHeight( unsigned int height ) noexcept {
    _height = height;
    return;
}

int Rectangle::getRight() const noexcept {
    return _x + _width;
}

int Rectangle::getBottom() const noexcept {
    return _y + _height;
}

}