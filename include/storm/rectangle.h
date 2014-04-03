#pragma once

namespace storm {

struct Rectangle {
    Rectangle()
        : x( 0 ), y( 0 ), width( 0 ), height( 0 )
    {
    }

    Rectangle( int x, int y, unsigned int width, unsigned int height )
        : x( x ), y( y ), width( width ), height( height )
    {
    }

    int getRight() const { return x + width; }
    int getBottom() const { return y + height; }

    bool contains( int x_, int y_ ) const {
        return x <= x_ && y <= y_ && getRight() >= x_ && getBottom() >= y_;
    }

    int x;
    int y;
    unsigned int width;
    unsigned int height;
};

}
