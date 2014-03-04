#pragma once

#include <storm/noexcept.h>

namespace storm {

struct Dimensions {
    Dimensions() noexcept
        : width( 0 ), height( 0 )
    {
    }

    Dimensions( unsigned int width, unsigned int height ) noexcept
        : width( width ), height( height )
    {
    }

    unsigned int width;
    unsigned int height;
};

}
