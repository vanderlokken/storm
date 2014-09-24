#pragma once

#include <vector>

#include <storm/dimensions.h>
#include <storm/texture.h>

namespace storm {

class Framebuffer {
public:
    typedef std::shared_ptr<Framebuffer> Pointer;

    struct Buffer {
        Texture::Pointer texture;
        unsigned int mipLevel;
        unsigned int layer;
    };

    struct Description {
        std::vector<Buffer> buffers;
    };

    static Pointer create( const Description& );

    static Pointer create( Dimensions dimensions, unsigned int texelSamples,
        const std::vector<Texture::Format> &bufferFormats );

    virtual ~Framebuffer() { }

    virtual const Description& getDescription() const = 0;
};

}
