#ifndef storm_Texture_h
#define storm_Texture_h

#include <memory>

#include "Dimensions.h"
#include "Noexcept.h"
#include "ResourceType.h"

namespace storm {

class Texture {
public:
    enum Format {
        FormatXrgbUint8,
        FormatArgbUint8,
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
    static std::shared_ptr<Texture> getDefault();

    virtual ~Texture() noexcept { }

    virtual void getTexels( unsigned int lodIndex, void *texels ) const = 0;
    virtual void setTexels( unsigned int lodIndex, const void *texels ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

}

#endif
