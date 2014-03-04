#pragma once

#include <storm/noexcept.h>

namespace storm {

struct Rectangle {
    Rectangle() noexcept
        : x( 0 ), y( 0 ), width( 0 ), height( 0 )
    {
    }

    Rectangle( int x, int y, unsigned int width, unsigned int height ) noexcept
        : x( x ), y( y ), width( width ), height( height )
    {
    }

    int getRight() const noexcept { return x + width; }
    int getBottom() const noexcept { return y + height; }

    int x;
    int y;
    unsigned int width;
    unsigned int height;
};

}
