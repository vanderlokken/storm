#pragma once

#include <storm/texture.h>

namespace storm {

class RenderingTarget {
public:
    typedef std::shared_ptr<RenderingTarget> Pointer;

    struct Description {
        Texture::Pointer texture;
        unsigned int lodIndex;
        unsigned int layerIndex;
    };

    static Pointer create( const Description& );

    virtual ~RenderingTarget() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
