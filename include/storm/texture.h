#pragma once

#include <memory>
#include <string>

#include <storm/dimensions.h>
#include <storm/noexcept.h>
#include <storm/resource_type.h>

namespace storm {

class Texture {
public:
    typedef std::shared_ptr<Texture> Pointer;

    enum class Format {
        XrgbUint8,
        ArgbUint8
    };

    enum class LodGenerationMode {
        Automatic,
        Custom
    };

    struct Description {
        Format format;
        Dimensions dimensions;
        LodGenerationMode lodGenerationMode;
        unsigned int customLodCount;
        ResourceType resourceType;
    };

    static Texture::Pointer create( const Description&, const void *texels = nullptr );
    static Texture::Pointer load( const std::string &filename );
    static Texture::Pointer getDefault();

    virtual ~Texture() { }

    virtual void getTexels( unsigned int lodIndex, void *texels ) const = 0;
    virtual void setTexels( unsigned int lodIndex, const void *texels ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

}
