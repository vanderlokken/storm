#pragma once

#include <iosfwd>
#include <memory>
#include <string_view>

#include <storm/resource_type.h>

namespace storm {

// This class represents an arbitrary texture which is a combination of some
// binary data and information how to interpret it.
class Texture {
public:
    typedef std::shared_ptr<Texture> Pointer;

    enum class Layout {
        // One-dimensional texture.
        Separate1d,
        // Two-dimensional texture.
        Separate2d,
        // Three-dimensional texture.
        Separate3d,
        // Layered one-dimensional texture.
        Layered1d,
        // Layered two-dimensional texture.
        Layered2d,
        // Cube map texture.
        CubeMap,
        // Two-dimensional texture which supports multisampling. Textures of
        // this type do not support mipmapping. Also it's not possible to
        // retrieve or assign texel values for Separate2dMsaa textures. The only
        // way to change contents of a Separate2dMsaa texture is to use it as a
        // rendering target.
        Separate2dMsaa,
        // Layered two-dimensional texture which supports multisampling.
        Layered2dMsaa
    };

    enum class Format {
        // 8-bit normalized unsigned integer formats.
        RgbNormUint8,
        RgbaNormUint8,
        SrgbNormUint8,
        SrgbaNormUint8,

        // 16-bit floating point formats.
        RedFloat16,
        RgFloat16,
        RgbFloat16,
        RgbaFloat16,

        // 16-bit integer formats.
        RedInt16,
        RgInt16,
        RgbInt16,
        RgbaInt16,

        // 16-bit unsigned integer formats.
        RedUint16,
        RgUint16,
        RgbUint16,
        RgbaUint16,

        // 32-bit floating point formats.
        RedFloat32,
        RgFloat32,
        RgbFloat32,
        RgbaFloat32,

        // 32-bit integer formats.
        RedInt32,
        RgInt32,
        RgbInt32,
        RgbaInt32,

        // 32-bit unsigned integer formats.
        RedUint32,
        RgUint32,
        RgbUint32,
        RgbaUint32,

        // Depth texture formats.
        DepthNormUint16,
        DepthNormUint24,
        DepthNormUint32,
        DepthNormUint24StencilUint8,
        DepthFloat32,

        // DXT-compressed texture formats.
        // Can be used only with "Separate2d" and "CubeMap" texture layouts.
        RgbDxt1,
        RgbaDxt1,
        RgbaDxt3,
        RgbaDxt5,
        SrgbDxt1,
        SrgbaDxt1,
        SrgbaDxt3,
        SrgbaDxt5
    };

    struct Description {
        Layout layout;
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int mipLevels;
        unsigned int layers;
        unsigned int texelSamples;
        ResourceType resourceType;
    };

    struct Separate1dDescription {
        Format format;
        unsigned int width;
        unsigned int mipLevels;
        ResourceType resourceType;
    };

    struct Separate2dDescription {
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int mipLevels;
        ResourceType resourceType;
    };

    struct Separate3dDescription {
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int mipLevels;
        ResourceType resourceType;
    };

    struct Layered1dDescription {
        Format format;
        unsigned int width;
        unsigned int mipLevels;
        unsigned int layers;
        ResourceType resourceType;
    };

    struct Layered2dDescription {
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int mipLevels;
        unsigned int layers;
        ResourceType resourceType;
    };

    struct CubeMapDescription {
        Format format;
        unsigned int dimension;
        unsigned int mipLevels;
        ResourceType resourceType;
    };

    struct Separate2dMsaaDescription {
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int texelSamples;
    };

    struct Layered2dMsaaDescription {
        Format format;
        unsigned int width;
        unsigned int height;
        unsigned int layers;
        unsigned int texelSamples;
    };

    // To create a texture with all possible mipmap levels specify this
    // constant as a value for "mipLevels". After texture creation the
    // "Description::mipLevels" value will contain an actual number of
    // created mipmap levels.
    static const unsigned int CompleteMipMap = ~0u;

    static Pointer create( const Separate1dDescription &description );
    static Pointer create( const Separate2dDescription &description );
    static Pointer create( const Separate3dDescription &description );

    static Pointer create( const Layered1dDescription &description );
    static Pointer create( const Layered2dDescription &description );

    static Pointer create( const CubeMapDescription &description );

    static Pointer create( const Separate2dMsaaDescription &description );
    static Pointer create( const Layered2dMsaaDescription &description );

    enum class FileFormat {
        DdsStrict,
        Dds,
        Png
    };

    enum class ColorSpace {
        Linear,
        sRGB
    };

    struct LoadingParameters {
        FileFormat fileFormat;
        // This parameter is used only when file doesn't contain any color
        // space information and color values are stored in 8-bit format.
        ColorSpace defaultColorSpace;
    };

    static Pointer load(
        std::istream &stream, const LoadingParameters &parameters );
    static Pointer load(
        std::string_view filename, const LoadingParameters &parameters );

    virtual ~Texture() {}

    // The following structure defines cube map face order. To use specific
    // cube map face as a rendering target assign corresponding value to the
    // "Framebuffer::Buffer::layer".
    struct CubeMapFace {
        static const unsigned int PositiveX = 0;
        static const unsigned int NegativeX = 1;
        static const unsigned int PositiveY = 2;
        static const unsigned int NegativeY = 3;
        static const unsigned int PositiveZ = 4;
        static const unsigned int NegativeZ = 5;
    };

    struct Separate1dRegion {
        unsigned int mipLevel;
        unsigned int x;
        unsigned int width;
    };

    struct Separate2dRegion {
        unsigned int mipLevel;
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    };

    struct Separate3dRegion {
        unsigned int mipLevel;
        unsigned int x;
        unsigned int y;
        unsigned int z;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    struct Layered1dRegion {
        unsigned int mipLevel;
        unsigned int layer;
        unsigned int x;
        unsigned int width;
    };

    struct Layered2dRegion {
        unsigned int mipLevel;
        unsigned int layer;
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    };

    struct CubeMapRegion {
        unsigned int mipLevel;
        unsigned int face;
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    };

    // Note: there's no "getTexels" method overload with a "region" parameter
    // since OpenGL doesn't support an appropriate operation.

    virtual void getTexels(
        unsigned int mipLevel, size_t size, void *texels ) const = 0;

    // Requirements for DXT-compressed textures:
    // 1. "texels" buffer size must be greater or equal to
    //    ceil( width / 4 ) * ceil( height / 4 ) * blockSize.
    // 2. "region.x", "region.y", "region.width" and "region.height" must be
    //    multiples of four unless the specified region describes an entire
    //    mip-level.

    virtual void setTexels(
        const Separate1dRegion &region, const void *texels ) = 0;

    virtual void setTexels(
        const Separate2dRegion &region, const void *texels ) = 0;

    virtual void setTexels(
        const Separate3dRegion &region, const void *texels ) = 0;

    virtual void setTexels(
        const Layered1dRegion &region, const void *texels ) = 0;

    virtual void setTexels(
        const Layered2dRegion &region, const void *texels ) = 0;

    virtual void setTexels(
        const CubeMapRegion &region, const void *texels ) = 0;

    // Warning: the filtering algorithm, which is used to generate mip map, is
    // implementation dependent. On NVidia drivers the result can be affected
    // by bound sampler objects.
    virtual void generateMipMap() = 0;

    virtual const Description& getDescription() const = 0;

    struct MipLevelDimensions {
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    MipLevelDimensions getMipLevelDimensions( unsigned int mipLevel ) const;
};

}
