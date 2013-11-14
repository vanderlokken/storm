#pragma once

#include <memory>
#include <string>

#include <storm/dimensions.h>
#include <storm/noexcept.h>
#include <storm/resource_type.h>

namespace storm {

class Texture {
public:
    enum Format {
        FormatXrgbUint8,
        FormatArgbUint8
    };

    enum LodGenerationMode {
        LodGenerationAutomatic,
        LodGenerationCustom
    };

    struct Description {
        Format format;
        Dimensions dimensions;
        LodGenerationMode lodGenerationMode;
        unsigned int customLodCount;
        ResourceType resourceType;
    };

    static std::shared_ptr<Texture> create( const Description&, const void *texels = nullptr );
    static std::shared_ptr<Texture> load( const std::string &filename );
    static std::shared_ptr<Texture> getDefault();

    virtual ~Texture() { }

    virtual void getTexels( unsigned int lodIndex, void *texels ) const = 0;
    virtual void setTexels( unsigned int lodIndex, const void *texels ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

}
