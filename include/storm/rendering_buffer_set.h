#pragma once

#include <vector>

#include <storm/texture.h>

namespace storm {

class RenderingBufferSet {
public:
    typedef std::shared_ptr<RenderingBufferSet> Pointer;

    struct Buffer {
        Texture::Pointer texture;
        unsigned int mipLevel;
        unsigned int layer;
    };

    struct Description {
        std::vector<Buffer> colorBuffers;
        Buffer depthStencilBuffer;
    };

    static Pointer create( const Description& );

    virtual ~RenderingBufferSet() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
