#pragma once

#include <storm/noexcept.h>

namespace storm {

class Dimensions {
public:
    Dimensions() noexcept;
    Dimensions( unsigned int width, unsigned int height ) noexcept;

    Dimensions& operator -= ( const Dimensions& ) noexcept;

    unsigned int getWidth() const noexcept;
    void setWidth( unsigned int ) noexcept;

    unsigned int getHeight() const noexcept;
    void setHeight( unsigned int ) noexcept;

    bool operator == ( const Dimensions& ) const noexcept;
    bool operator != ( const Dimensions& ) const noexcept;

private:
    unsigned int _width;
    unsigned int _height;
};

}
