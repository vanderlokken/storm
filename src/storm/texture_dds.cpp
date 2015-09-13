#include <storm/texture_dds.h>

#include <cstdint>
#include <vector>

#include <storm/exception.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

struct DdsPixelFormat {
    uint32_t size;
    uint32_t flags;
    uint32_t fourCC;
    uint32_t rgbBitCount;
    uint32_t rBitMask;
    uint32_t gBitMask;
    uint32_t bBitMask;
    uint32_t aBitMask;
};

struct DdsHeader {
    uint32_t size;
    uint32_t flags;
    uint32_t height;
    uint32_t width;
    uint32_t pitchOrLinearSize;
    uint32_t depth;
    uint32_t mipMapCount;
    uint32_t unused1[11];
    DdsPixelFormat pixelFormat;
    uint32_t complexityFlags;
    uint32_t surfaceFlags;
    uint32_t unused2;
    uint32_t unused3;
    uint32_t unused4;
};

struct DdsFlags {
    static const uint32_t Dds = 1 << 0;
    static const uint32_t Width = 1 << 1;
    static const uint32_t Height = 1 << 2;
    static const uint32_t Pitch = 1 << 3;
    static const uint32_t PixelFormat = 1 << 12;
    static const uint32_t MipMapCount = 1 << 17;
    static const uint32_t LinearSize = 1 << 19;
    static const uint32_t Depth = 1 << 23;
};

struct DdsComplexityFlags {
    static const uint32_t Complex = 1 << 3;
    static const uint32_t MipMap = 1 << 22;
    static const uint32_t Texture = 1 << 12;
};

struct DdsSurfaceFlags {
    static const uint32_t CubeMap = 1 << 9;
    static const uint32_t CubeMapFull =
        (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);
    static const uint32_t Volume = 1 << 21;
};

struct DdsPixelFormatFlags {
    static const uint32_t Alpha = 1 << 0;
    static const uint32_t AlphaOnly = 1 << 1;
    static const uint32_t FourCC = 1 << 2;
    static const uint32_t Rgb = 1 << 6;
    static const uint32_t Yuv = 1 << 9;
    static const uint32_t Luminiance = 1 << 17;

    static const uint32_t Rgba = Alpha | Rgb;
};

Texture::Format selectTextureFormat(
    const DdsPixelFormat &ddsPixelFormat, bool srgbDefault )
{
    if( ddsPixelFormat.flags & DdsPixelFormatFlags::FourCC ) {
        switch( ddsPixelFormat.fourCC ) {
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('1' << 24):
            return srgbDefault ?
                Texture::Format::SrgbaDxt1 : Texture::Format::RgbaDxt1;
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('3' << 24):
            return srgbDefault ?
                Texture::Format::SrgbaDxt3 : Texture::Format::RgbaDxt3;
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('5' << 24):
            return srgbDefault ?
                Texture::Format::SrgbaDxt5 : Texture::Format::RgbaDxt5;
        case 111:
            return Texture::Format::RedFloat16;
        case 112:
            return Texture::Format::RgFloat16;
        case 113:
            return Texture::Format::RgbaFloat16;
        case 114:
            return Texture::Format::RedFloat32;
        case 115:
            return Texture::Format::RgFloat32;
        case 116:
            return Texture::Format::RgbaFloat32;
        }
    }

    if( (ddsPixelFormat.flags & DdsPixelFormatFlags::Rgba) &&
        ddsPixelFormat.rgbBitCount == 32 &&
        ddsPixelFormat.rBitMask == 0x000000ff &&
        ddsPixelFormat.gBitMask == 0x0000ff00 &&
        ddsPixelFormat.bBitMask == 0x00ff0000 &&
        ddsPixelFormat.aBitMask == 0xff000000 )
    {
        return srgbDefault ?
            Texture::Format::SrgbaUint8 : Texture::Format::RgbaUint8;
    }

    throw ResourceLoadingError() << "Unsupported DDS texture";
}

DdsHeader parseDdsHeader( BinaryInputStream &stream, bool strict ) {
    const uint32_t formatId = stream.read<uint32_t>();

    DdsHeader ddsHeader;
    ddsHeader.size                    = stream.read<uint32_t>();
    ddsHeader.flags                   = stream.read<uint32_t>();
    ddsHeader.height                  = stream.read<uint32_t>();
    ddsHeader.width                   = stream.read<uint32_t>();
    ddsHeader.pitchOrLinearSize       = stream.read<uint32_t>();
    ddsHeader.depth                   = stream.read<uint32_t>();
    ddsHeader.mipMapCount             = stream.read<uint32_t>();
    stream.read( reinterpret_cast<char*>(ddsHeader.unused1),
        sizeof(ddsHeader.unused1) );
    ddsHeader.pixelFormat.size        = stream.read<uint32_t>();
    ddsHeader.pixelFormat.flags       = stream.read<uint32_t>();
    ddsHeader.pixelFormat.fourCC      = stream.read<uint32_t>();
    ddsHeader.pixelFormat.rgbBitCount = stream.read<uint32_t>();
    ddsHeader.pixelFormat.rBitMask    = stream.read<uint32_t>();
    ddsHeader.pixelFormat.gBitMask    = stream.read<uint32_t>();
    ddsHeader.pixelFormat.bBitMask    = stream.read<uint32_t>();
    ddsHeader.pixelFormat.aBitMask    = stream.read<uint32_t>();
    ddsHeader.complexityFlags         = stream.read<uint32_t>();
    ddsHeader.surfaceFlags            = stream.read<uint32_t>();
    ddsHeader.unused2                 = stream.read<uint32_t>();
    ddsHeader.unused3                 = stream.read<uint32_t>();
    ddsHeader.unused4                 = stream.read<uint32_t>();

    if( strict ) {
        auto check = []( uint32_t value ) {
            if( !value )
                throw ResourceLoadingError() << "Invalid DDS texture data";
        };

        check( formatId == 0x20534444 );

        const uint32_t requiredFlags =
            DdsFlags::Dds |
            DdsFlags::Width |
            DdsFlags::Height |
            DdsFlags::PixelFormat;

        check( ddsHeader.size == 124 );
        check( ddsHeader.flags & requiredFlags );
        check( ddsHeader.height );
        check( ddsHeader.width );
        check( ddsHeader.complexityFlags & DdsComplexityFlags::Texture );

        if( ddsHeader.complexityFlags & DdsComplexityFlags::MipMap ) {
            check( ddsHeader.flags & DdsFlags::MipMapCount );
            check( ddsHeader.complexityFlags & DdsComplexityFlags::Complex );
        }

        if( ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMap ) {
            check( ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMapFull );
            check( !(ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume) );
            check( ddsHeader.complexityFlags & DdsComplexityFlags::Complex );

            check( ddsHeader.width == ddsHeader.height );
        }

        if( ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
            check( ddsHeader.flags & DdsFlags::Depth );
            check( !(ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMap) );
        }

        check( ddsHeader.pixelFormat.size == 32 );
    }

    return ddsHeader;
}

Texture::Pointer createTexture(
    const DdsHeader &ddsHeader, const Texture::LoadingParameters &parameters )
{
    const bool srgbDefault =
        parameters.defaultColorSpace == Texture::ColorSpace::sRGB;
    const Texture::Format format =
        selectTextureFormat( ddsHeader.pixelFormat, srgbDefault );

    unsigned int mipLevels = 1;

    if( (ddsHeader.complexityFlags & DdsComplexityFlags::MipMap) &&
            (ddsHeader.flags & DdsFlags::MipMapCount) )
        mipLevels = ddsHeader.mipMapCount;

    if( ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
        Texture::Separate3dDescription description;

        description.format = format;
        description.width = ddsHeader.width;
        description.height = ddsHeader.height;
        description.depth = ddsHeader.depth;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );

    } else if( ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMap ) {
        Texture::CubeMapDescription description;

        description.format = format;
        description.dimension = ddsHeader.width;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );

    } else {
        Texture::Separate2dDescription description;

        description.format = format;
        description.width = ddsHeader.width;
        description.height = ddsHeader.height;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    }
}

void parseDdsTextureLayer(
    BinaryInputStream &stream, Texture::Pointer texture,
    unsigned int layer = 0 )
{
    const Texture::Description &textureDescription = texture->getDescription();

    for( unsigned int mipLevel = 0;
            mipLevel < textureDescription.mipLevels; ++mipLevel )
    {
        const Texture::MipLevelDimensions dimensions =
            texture->getMipLevelDimensions( mipLevel );

        size_t texelSize = 0;

        switch( textureDescription.format ) {
        case Texture::Format::RedFloat16:
            texelSize = 2;
            break;
        case Texture::Format::RgbaUint8:
        case Texture::Format::SrgbaUint8:
        case Texture::Format::RgFloat16:
        case Texture::Format::RedFloat32:
            texelSize = 4;
            break;
        case Texture::Format::RgbaFloat16:
        case Texture::Format::RgFloat32:
            texelSize = 8;
            break;
        case Texture::Format::RgbaFloat32:
            texelSize = 16;
            break;
        }

        std::vector<char> texels(
            dimensions.width *
            dimensions.height *
            dimensions.depth *
            texelSize );

        switch( textureDescription.format ) {
        case Texture::Format::RgbaDxt1:
        case Texture::Format::SrgbaDxt1:
            texels.resize(
                static_cast<size_t>(ceil(dimensions.width / 4.0f)) *
                static_cast<size_t>(ceil(dimensions.height / 4.0f)) * 8 );
            break;
        case Texture::Format::RgbaDxt3:
        case Texture::Format::RgbaDxt5:
        case Texture::Format::SrgbaDxt3:
        case Texture::Format::SrgbaDxt5:
            texels.resize(
                static_cast<size_t>(ceil(dimensions.width / 4.0f)) *
                static_cast<size_t>(ceil(dimensions.height / 4.0f)) * 16 );
            break;
        }

        storm_assert( texels.size() != 0 );
        stream.read( texels.data(), texels.size() );

        switch( textureDescription.layout ) {
        case Texture::Layout::Separate2d:
            {
                Texture::Separate2dRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.width = dimensions.width;
                region.height = dimensions.height;

                texture->setTexels( region, texels.data() );
            }
            break;
        case Texture::Layout::Separate3d:
            {
                Texture::Separate3dRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.width = dimensions.width;
                region.height = dimensions.height;
                region.depth = dimensions.depth;

                texture->setTexels( region, texels.data() );
            }
            break;
        case Texture::Layout::CubeMap:
            {
                Texture::CubeMapRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.face = layer;
                region.width = dimensions.width;
                region.height = dimensions.height;

                texture->setTexels( region, texels.data() );
            }
            break;
        default:
            throwNotImplemented();
        }
    }
}

} // namespace

Texture::Pointer parseDds(
    BinaryInputStream &stream, const Texture::LoadingParameters &parameters )
{
    try {
        const bool strict =
            parameters.fileFormat == Texture::FileFormat::DdsStrict;

        const DdsHeader ddsHeader = parseDdsHeader( stream, strict );

        const Texture::Pointer texture = createTexture( ddsHeader, parameters );

        if( texture->getDescription().layout != Texture::Layout::CubeMap ) {
            parseDdsTextureLayer( stream, texture );
        } else {
            const unsigned int faces[] = {
                Texture::CubeMapFace::PositiveX,
                Texture::CubeMapFace::NegativeX,
                Texture::CubeMapFace::PositiveY,
                Texture::CubeMapFace::NegativeY,
                Texture::CubeMapFace::PositiveZ,
                Texture::CubeMapFace::NegativeZ
            };
            for( unsigned int face : faces )
                parseDdsTextureLayer( stream, texture, face );
        }

        return texture;

    } catch( std::ios_base::failure& ) {
        throw ResourceLoadingError() << "Invalid DDS texture data";
    }
}

}
