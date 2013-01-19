#ifndef storm_Rectangle_h
#define storm_Rectangle_h

#include "Noexcept.h"

namespace storm {

class Rectangle {
public:
    Rectangle() noexcept;
    Rectangle( int x, int y, unsigned int width, unsigned int height ) noexcept;

    int getX() const noexcept;
    int getY() const noexcept;

    void setX( int ) noexcept;
    void setY( int ) noexcept;

    unsigned int getWidth() const noexcept;
    unsigned int getHeight() const noexcept;

    void setWidth( unsigned int ) noexcept;
    void setHeight( unsigned int ) noexcept;

    int getRight() const noexcept;
    int getBottom() const noexcept;

private:
    int _x;
    int _y;
    unsigned int _width;
    unsigned int _height;
};

}

#endif