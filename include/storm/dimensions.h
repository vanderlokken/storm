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

    float getAspectRatio() const {
        return (
            static_cast<float>(width) /
            static_cast<float>(height)
        );
    }

    unsigned int width;
    unsigned int height;
};

}
