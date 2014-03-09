#pragma once

namespace storm {

struct Dimensions {
    Dimensions()
        : width( 0 ), height( 0 )
    {
    }

    Dimensions( unsigned int width, unsigned int height )
        : width( width ), height( height )
    {
    }

    unsigned int width;
    unsigned int height;
};

}
