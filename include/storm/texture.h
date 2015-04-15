#pragma once

#include <istream>
#include <memory>
#include <string>

#include <storm/resource_type.h>

namespace storm {

// This class represents an arbitrary texture which is a combination of some
// binary data and information how to interpret it.
class Texture {
public:
    typedef std::shared_ptr<Texture> Pointer;

    enum class FileFormat {
        Dds,
        DdsStrict
    };

    enum class Format {
        RgbUint8,
        ArgbUint8,
        SrgbUint8,
        AsrgbUint8,
        // 16-bit floating point formats.
        RedFloat16,
        RgFloat16,
        RgbFloat16,
        RgbaFloat16,
        // 32-bit floating point formats.
        RedFloat32,
        RgFloat32,
        RgbFloat32,
        RgbaFloat32,
        // Depth texture formats.
        DepthUint16,
        DepthUint24,
        DepthUint32,
        DepthUint24StencilUint8,
        DepthFloat32,
        // DXT-compressed texture formats. Requirements: "layout" must be
        // "Layout::Separate2d".
        RgbDxt1,
        ArgbDxt1,
        ArgbDxt3,
        ArgbDxt5,
        SrgbDxt1,
        AsrgbDxt1,
        AsrgbDxt3,
        AsrgbDxt5
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
    // as a value for "mipLevels". After texture creation the "mipLevels" value
    // will contain an actual number of created mipmap levels.
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
    static Pointer load( std::istream &stream, FileFormat fileFormat );
    static Pointer load( const std::string &filename, FileFormat fileFormat );

    virtual ~Texture() { }

    // Requirements for DXT-compressed textures: "texels" buffer size must be
    // at least ceil( width / 4 ) * ceil( height / 4 ) * blockSize;
    // "region.x", "region.y", "region.width" and "region.height" must be
    // multiples of four unless the specified region describes entire mip-level.
    virtual void getTexels( unsigned int mipLevel, void *texels ) const = 0;
     inline void setTexels( unsigned int mipLevel, const void *texels );
    virtual void setTexels( const Region &region, const void *texels ) = 0;

    // Note: there's no "getTexels" method overload with a "region" parameter
    // since OpenGL doesn't have an appropriate function.

    virtual void generateMipMap() = 0;

    virtual const Description& getDescription() const = 0;
};

inline void Texture::setTexels( unsigned int mipLevel, const void *texels ) {
    const Description &description = getDescription();

    Region region = { 0 };
    region.width = description.width >> mipLevel;
    region.height = description.height >> mipLevel;
    region.depth = description.depth >> mipLevel;

    if( !region.width ) region.width = 1;
    if( !region.height ) region.height = 1;
    if( !region.depth ) region.depth = 1;

    setTexels( region, texels );
}

}
