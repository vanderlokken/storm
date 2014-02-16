#pragma once

#include <memory>

#include <storm/noexcept.h>
#include <storm/resource_type.h>

namespace storm {

// This class represents an arbitrary texture which is a combination of some
// binary data and information how to interpret it.
class Texture {
public:
    typedef std::shared_ptr<Texture> Pointer;

    enum class Format {
        RgbUint8,
        ArgbUint8,
        DepthUint16,
        DepthUint24,
        DepthUint32,
        DepthUint24StencilUint8
    };

    enum class Layout {
        // One-dimensional texture. Requirements: "height", "depth" and
        // "texelSamples" must be 1.
        Separate1d,
        // Two-dimensional texture. Requirements: "depth" and "texelSamples"
        // must be 1.
        Separate2d,
        // Two-dimensional texture which supports multisampling. Textures of
        // this type do not support mipmapping. Also it's not possible to
        // retrieve or assign texel values for Separate2dMsaa textures
        // (an attempt to call "getTexels" or "setTexels" will fail). The only
        // way to change contents of a Separate2dMsaa texture is to use it as
        // rendering target. Requirements: "depth" and "mipLevels" must be 1,
        // "resourceType" must be "ResourceType::Dynamic".
        Separate2dMsaa,
        // Three-dimensional texture. Requirements: "texelSamples" must be 1.
        Separate3d,
        // Layered one-dimensional texture. Requirements: "height" and
        // "texelSamples" must be 1.
        Layered1d,
        // Layered two-dimensional texture. Requirements: "texelSamples" must be
        // 1.
        Layered2d,
        // Layered two-dimensional texture which supports multisampling.
        // Textures of this type have the same restrictions as Separate2dMsaa
        // textures. Requirements: "mipLevels" must be 1, "resourceType" must be
        // "ResourceType::Dynamic".
        Layered2dMsaa,
        // TBD
        CubeMap,
        // One-dimensional buffer texture. Textures of this type do not support
        // mipmapping. Requirements: "height", "depth", "mipLevels" and
        // "texelSamples" must be 1.
        Buffer
    };

    struct Description {
        Layout layout;
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int mipLevels;
        unsigned int texelSamples;
        ResourceType resourceType;
    };

    // To create a texture with all possible mipmap levels specify this constant
    // as a value for "mipLevels".
    static const unsigned int CompleteMipMap = ~0u;

    struct Region {
        unsigned int mipLevel;
        unsigned int x;
        unsigned int y;
        unsigned int z;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    static Pointer create( const Description&, const void *texels = nullptr );

    virtual ~Texture() { }

    virtual void getTexels( const Region &region, void *texels ) const = 0;
    virtual void setTexels( const Region &region, const void *texels ) = 0;

    void setBaseLevelTexels( const void *texels ) {
        const Description &description = getDescription();

        Region region = { 0 };
        region.width = description.width;
        region.height = description.height;
        region.depth = description.depth;

        setTexels( region, texels );
    }

    virtual void generateMipMap() = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

}
