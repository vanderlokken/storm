#pragma once

#include <memory>

#include <storm/texture.h>

namespace storm {

class Backbuffer {
public:
    typedef std::shared_ptr<Backbuffer> Pointer;

    virtual ~Backbuffer() { }

    // Texture requirements:
    //   * layout must be "Separate2d", "Separate2dMsaa", "Layered2d" or "Layered2dMsaa"
    //   * format must be "ArgbUint8" or "AsrgbUint8"
    // Also dimensions of the specified mipmap level must be equal to the backbuffer dimensions.
    virtual void renderTexture(
        Texture::Pointer, unsigned int mipLevel = 0, unsigned int layer = 0 ) = 0;
};

}
