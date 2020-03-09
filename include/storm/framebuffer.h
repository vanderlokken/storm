#pragma once

#include <memory>
#include <vector>

#include <storm/dimensions.h>
#include <storm/texture.h>

namespace storm {

class Framebuffer {
public:
    using Pointer = std::shared_ptr<Framebuffer>;

    struct Buffer {
        Texture::Pointer texture;
        unsigned int mipLevel;
        unsigned int layer;
    };

    struct Description {
        std::vector<Buffer> buffers;
    };

    static Pointer create( const Description &description );
    static Pointer create( Texture::Pointer texture );

    static Pointer create( Dimensions dimensions, unsigned int texelSamples,
        const std::vector<Texture::Format> &bufferFormats );

    virtual ~Framebuffer() = default;

    virtual const Description& getDescription() const = 0;
};

}
