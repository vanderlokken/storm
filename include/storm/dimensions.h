#pragma once

namespace storm {

struct Dimensions {
    Dimensions() = default;

    Dimensions( unsigned int width, unsigned int height ) :
        width( width ),
        height( height )
    {
    }

    float getAspectRatio() const {
        return (
            static_cast<float>(width) /
            static_cast<float>(height)
        );
    }

    unsigned int width = 0;
    unsigned int height = 0;
};

}
