#pragma once

#include <memory>

#include <storm/texture.h>

namespace storm {

class Backbuffer {
public:
    using Pointer = std::shared_ptr<Backbuffer>;

    virtual ~Backbuffer() = default;

    // Texture requirements:
    //   * layout must be "Separate2d", "Separate2dMsaa", "Layered2d" or "Layered2dMsaa"
    //   * format must be "RgbaNormUint8" or "SrgbaNormUint8"
    // Also dimensions of the specified mipmap level must be equal to the backbuffer dimensions.
    virtual void renderTexture(
        Texture::Pointer, unsigned int mipLevel = 0, unsigned int layer = 0 ) = 0;
};

}
