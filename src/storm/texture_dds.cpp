#include <storm/texture_dds.h>

#include <cmath>
#include <cstdint>
#include <vector>

#include <storm/exception.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

enum DXGI_FORMAT {
    DXGI_FORMAT_UNKNOWN                     = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS       = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT          = 2,
    DXGI_FORMAT_R32G32B32A32_UINT           = 3,
    DXGI_FORMAT_R32G32B32A32_SINT           = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS          = 5,
    DXGI_FORMAT_R32G32B32_FLOAT             = 6,
    DXGI_FORMAT_R32G32B32_UINT              = 7,
    DXGI_FORMAT_R32G32B32_SINT              = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS       = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT          = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM          = 11,
    DXGI_FORMAT_R16G16B16A16_UINT           = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM          = 13,
    DXGI_FORMAT_R16G16B16A16_SINT           = 14,
    DXGI_FORMAT_R32G32_TYPELESS             = 15,
    DXGI_FORMAT_R32G32_FLOAT                = 16,
    DXGI_FORMAT_R32G32_UINT                 = 17,
    DXGI_FORMAT_R32G32_SINT                 = 18,
    DXGI_FORMAT_R32G8X24_TYPELESS           = 19,
    DXGI_FORMAT_D32_FLOAT_S8X24_UINT        = 20,
    DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
    DXGI_FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
    DXGI_FORMAT_R10G10B10A2_TYPELESS        = 23,
    DXGI_FORMAT_R10G10B10A2_UNORM           = 24,
    DXGI_FORMAT_R10G10B10A2_UINT            = 25,
    DXGI_FORMAT_R11G11B10_FLOAT             = 26,
    DXGI_FORMAT_R8G8B8A8_TYPELESS           = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM              = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
    DXGI_FORMAT_R8G8B8A8_UINT               = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM              = 31,
    DXGI_FORMAT_R8G8B8A8_SINT               = 32,
    DXGI_FORMAT_R16G16_TYPELESS             = 33,
    DXGI_FORMAT_R16G16_FLOAT                = 34,
    DXGI_FORMAT_R16G16_UNORM                = 35,
    DXGI_FORMAT_R16G16_UINT                 = 36,
    DXGI_FORMAT_R16G16_SNORM                = 37,
    DXGI_FORMAT_R16G16_SINT                 = 38,
    DXGI_FORMAT_R32_TYPELESS                = 39,
    DXGI_FORMAT_D32_FLOAT                   = 40,
    DXGI_FORMAT_R32_FLOAT                   = 41,
    DXGI_FORMAT_R32_UINT                    = 42,
    DXGI_FORMAT_R32_SINT                    = 43,
    DXGI_FORMAT_R24G8_TYPELESS              = 44,
    DXGI_FORMAT_D24_UNORM_S8_UINT           = 45,
    DXGI_FORMAT_R24_UNORM_X8_TYPELESS       = 46,
    DXGI_FORMAT_X24_TYPELESS_G8_UINT        = 47,
    DXGI_FORMAT_R8G8_TYPELESS               = 48,
    DXGI_FORMAT_R8G8_UNORM                  = 49,
    DXGI_FORMAT_R8G8_UINT                   = 50,
    DXGI_FORMAT_R8G8_SNORM                  = 51,
    DXGI_FORMAT_R8G8_SINT                   = 52,
    DXGI_FORMAT_R16_TYPELESS                = 53,
    DXGI_FORMAT_R16_FLOAT                   = 54,
    DXGI_FORMAT_D16_UNORM                   = 55,
    DXGI_FORMAT_R16_UNORM                   = 56,
    DXGI_FORMAT_R16_UINT                    = 57,
    DXGI_FORMAT_R16_SNORM                   = 58,
    DXGI_FORMAT_R16_SINT                    = 59,
    DXGI_FORMAT_R8_TYPELESS                 = 60,
    DXGI_FORMAT_R8_UNORM                    = 61,
    DXGI_FORMAT_R8_UINT                     = 62,
    DXGI_FORMAT_R8_SNORM                    = 63,
    DXGI_FORMAT_R8_SINT                     = 64,
    DXGI_FORMAT_A8_UNORM                    = 65,
    DXGI_FORMAT_R1_UNORM                    = 66,
    DXGI_FORMAT_R9G9B9E5_SHAREDEXP          = 67,
    DXGI_FORMAT_R8G8_B8G8_UNORM             = 68,
    DXGI_FORMAT_G8R8_G8B8_UNORM             = 69,
    DXGI_FORMAT_BC1_TYPELESS                = 70,
    DXGI_FORMAT_BC1_UNORM                   = 71,
    DXGI_FORMAT_BC1_UNORM_SRGB              = 72,
    DXGI_FORMAT_BC2_TYPELESS                = 73,
    DXGI_FORMAT_BC2_UNORM                   = 74,
    DXGI_FORMAT_BC2_UNORM_SRGB              = 75,
    DXGI_FORMAT_BC3_TYPELESS                = 76,
    DXGI_FORMAT_BC3_UNORM                   = 77,
    DXGI_FORMAT_BC3_UNORM_SRGB              = 78,
    DXGI_FORMAT_BC4_TYPELESS                = 79,
    DXGI_FORMAT_BC4_UNORM                   = 80,
    DXGI_FORMAT_BC4_SNORM                   = 81,
    DXGI_FORMAT_BC5_TYPELESS                = 82,
    DXGI_FORMAT_BC5_UNORM                   = 83,
    DXGI_FORMAT_BC5_SNORM                   = 84,
    DXGI_FORMAT_B5G6R5_UNORM                = 85,
    DXGI_FORMAT_B5G5R5A1_UNORM              = 86,
    DXGI_FORMAT_B8G8R8A8_UNORM              = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM              = 88,
    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
    DXGI_FORMAT_B8G8R8A8_TYPELESS           = 90,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
    DXGI_FORMAT_B8G8R8X8_TYPELESS           = 92,
    DXGI_FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
    DXGI_FORMAT_BC6H_TYPELESS               = 94,
    DXGI_FORMAT_BC6H_UF16                   = 95,
    DXGI_FORMAT_BC6H_SF16                   = 96,
    DXGI_FORMAT_BC7_TYPELESS                = 97,
    DXGI_FORMAT_BC7_UNORM                   = 98,
    DXGI_FORMAT_BC7_UNORM_SRGB              = 99,
    DXGI_FORMAT_AYUV                        = 100,
    DXGI_FORMAT_Y410                        = 101,
    DXGI_FORMAT_Y416                        = 102,
    DXGI_FORMAT_NV12                        = 103,
    DXGI_FORMAT_P010                        = 104,
    DXGI_FORMAT_P016                        = 105,
    DXGI_FORMAT_420_OPAQUE                  = 106,
    DXGI_FORMAT_YUY2                        = 107,
    DXGI_FORMAT_Y210                        = 108,
    DXGI_FORMAT_Y216                        = 109,
    DXGI_FORMAT_NV11                        = 110,
    DXGI_FORMAT_AI44                        = 111,
    DXGI_FORMAT_IA44                        = 112,
    DXGI_FORMAT_P8                          = 113,
    DXGI_FORMAT_A8P8                        = 114,
    DXGI_FORMAT_B4G4R4A4_UNORM              = 115,
    DXGI_FORMAT_P208                        = 130,
    DXGI_FORMAT_V208                        = 131,
    DXGI_FORMAT_V408                        = 132,
    DXGI_FORMAT_FORCE_UINT                  = 0xffffffff
};

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

struct DdsBasicHeader {
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

struct DdsExtendedHeader {
    DXGI_FORMAT pixelFormatDxGI;
    uint32_t resourceDimension;
    uint32_t resourceFlags;
    uint32_t arraySize;
    uint32_t extendedFlags;
};

static_assert(
    sizeof(DdsPixelFormat) == 32, "Unexpected DdsPixelFormat size" );
static_assert(
    sizeof(DdsBasicHeader) == 124, "Unexpected DdsBasicHeader size" );
static_assert(
    sizeof(DdsExtendedHeader) == 20, "Unexpected DdsExtendedHeader size" );

struct DdsHeader {
    uint32_t formatId;
    DdsBasicHeader basicHeader;
    bool hasExtendedHeader;
    DdsExtendedHeader extendedHeader;
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

constexpr uint32_t createFourCC(
    char first, char second, char third, char fourth )
{
    return (first << 0) | (second << 8) | (third << 16) | (fourth << 24);
}

struct DdsFourCC {
    static const uint32_t Dds = createFourCC( 'D', 'D', 'S', ' ' );
    static const uint32_t Dxt1 = createFourCC( 'D', 'X', 'T', '1' );
    static const uint32_t Dxt3 = createFourCC( 'D', 'X', 'T', '3' );
    static const uint32_t Dxt5 = createFourCC( 'D', 'X', 'T', '5' );
    static const uint32_t Dx10 = createFourCC( 'D', 'X', '1', '0' );
};

struct DdsResourceDimension {
    static const uint32_t _1d = 2;
    static const uint32_t _2d = 3;
    static const uint32_t _3d = 4;
};

struct DdsResourceFlags {
    static const uint32_t CubeMap = 1 << 2;
};

Texture::Format convertPixelFormatDxGI( DXGI_FORMAT pixelFormatDxGI ) {
    switch( pixelFormatDxGI ) {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        return Texture::Format::RgbaUint8;
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        return Texture::Format::SrgbaUint8;

    case DXGI_FORMAT_R16_FLOAT:
        return Texture::Format::RedFloat16;
    case DXGI_FORMAT_R16G16_FLOAT:
        return Texture::Format::RgFloat16;
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return Texture::Format::RgbaFloat16;

    case DXGI_FORMAT_R32_FLOAT:
        return Texture::Format::RedFloat32;
    case DXGI_FORMAT_R32G32_FLOAT:
        return Texture::Format::RgFloat32;
    case DXGI_FORMAT_R32G32B32_FLOAT:
        return Texture::Format::RgbFloat32;
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return Texture::Format::RgbaFloat32;

    case DXGI_FORMAT_BC1_UNORM:
        return Texture::Format::RgbaDxt1;
    case DXGI_FORMAT_BC2_UNORM:
        return Texture::Format::RgbaDxt3;
    case DXGI_FORMAT_BC3_UNORM:
        return Texture::Format::RgbaDxt5;

    case DXGI_FORMAT_BC1_UNORM_SRGB:
        return Texture::Format::SrgbaDxt1;
    case DXGI_FORMAT_BC2_UNORM_SRGB:
        return Texture::Format::SrgbaDxt3;
    case DXGI_FORMAT_BC3_UNORM_SRGB:
        return Texture::Format::SrgbaDxt5;

    default:
        throw ResourceLoadingError() << "Unsupported DDS texture";
    }
}

Texture::Format selectTextureFormat(
    const DdsHeader &ddsHeader, Texture::ColorSpace defaultColorSpace )
{
    if( ddsHeader.hasExtendedHeader ) {
        return convertPixelFormatDxGI(
            ddsHeader.extendedHeader.pixelFormatDxGI );
    }

    const DdsPixelFormat &ddsPixelFormat = ddsHeader.basicHeader.pixelFormat;

    if( ddsPixelFormat.flags & DdsPixelFormatFlags::FourCC ) {
        switch( ddsPixelFormat.fourCC ) {
        case DdsFourCC::Dxt1:
            return defaultColorSpace == Texture::ColorSpace::sRGB ?
                Texture::Format::SrgbaDxt1 : Texture::Format::RgbaDxt1;
        case DdsFourCC::Dxt3:
            return defaultColorSpace == Texture::ColorSpace::sRGB ?
                Texture::Format::SrgbaDxt3 : Texture::Format::RgbaDxt3;
        case DdsFourCC::Dxt5:
            return defaultColorSpace == Texture::ColorSpace::sRGB ?
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
        return defaultColorSpace == Texture::ColorSpace::sRGB ?
            Texture::Format::SrgbaUint8 : Texture::Format::RgbaUint8;
    }

    throw ResourceLoadingError() << "Unsupported DDS texture";
}

void validateDdsHeader( const DdsHeader &header ) {
    auto check = []( uint32_t value ) {
        if( !value )
            throw ResourceLoadingError() << "Invalid DDS texture data";
    };

    check( header.formatId == DdsFourCC::Dds );

    const DdsBasicHeader &basicHeader = header.basicHeader;

    // DDS documentation reference:
    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb943982%28v=vs.85%29.aspx
    const uint32_t requiredFlags =
        DdsFlags::Dds |
        DdsFlags::Width |
        DdsFlags::Height |
        DdsFlags::PixelFormat;

    check( basicHeader.size == sizeof(DdsBasicHeader) );
    check( basicHeader.flags & requiredFlags );
    check( basicHeader.height );
    check( basicHeader.width );
    check( basicHeader.complexityFlags & DdsComplexityFlags::Texture );

    if( basicHeader.complexityFlags & DdsComplexityFlags::MipMap ) {
        check( basicHeader.flags & DdsFlags::MipMapCount );
        check( basicHeader.complexityFlags & DdsComplexityFlags::Complex );
    }

    if( basicHeader.surfaceFlags & DdsSurfaceFlags::CubeMap ) {
        check( basicHeader.surfaceFlags & DdsSurfaceFlags::CubeMapFull );
        check( !(basicHeader.surfaceFlags & DdsSurfaceFlags::Volume) );
        check( basicHeader.complexityFlags & DdsComplexityFlags::Complex );

        check( basicHeader.width == basicHeader.height );
    }

    if( basicHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
        check( basicHeader.flags & DdsFlags::Depth );
        check( !(basicHeader.surfaceFlags & DdsSurfaceFlags::CubeMap) );
    }

    check( basicHeader.pixelFormat.size == sizeof(DdsPixelFormat) );

    if( header.hasExtendedHeader ) {
        const DdsExtendedHeader &extendedHeader = header.extendedHeader;

        // TODO: check that for 1D/2D textures higher dimensions are set to 1

        check(
            extendedHeader.resourceDimension == DdsResourceDimension::_1d ||
            extendedHeader.resourceDimension == DdsResourceDimension::_2d ||
            extendedHeader.resourceDimension == DdsResourceDimension::_3d );

        if( basicHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
            check(
                extendedHeader.resourceDimension == DdsResourceDimension::_3d );
        } else {
            check(
                extendedHeader.resourceDimension != DdsResourceDimension::_3d );
        }

        if( basicHeader.surfaceFlags & DdsSurfaceFlags::CubeMap ) {
            check(
                extendedHeader.resourceDimension == DdsResourceDimension::_2d );
            check( extendedHeader.resourceFlags & DdsResourceFlags::CubeMap );
        } else {
            check(
                !(extendedHeader.resourceFlags & DdsResourceFlags::CubeMap) );
        }

        if( extendedHeader.resourceDimension != DdsResourceDimension::_3d ) {
            check( extendedHeader.arraySize );
        } else {
            check( extendedHeader.arraySize == 1 );
        }
    }
}

DdsHeader parseDdsHeader( BinaryInputStream &stream, bool strict ) {
    DdsHeader header;

    if( getHostByteOrder() != ByteOrder::LittleEndian ) {
        throwNotImplemented();
    }

    stream.read( &header.formatId, sizeof(header.formatId) );
    stream.read( &header.basicHeader, sizeof(header.basicHeader) );

    header.hasExtendedHeader =
        header.basicHeader.pixelFormat.flags & DdsPixelFormatFlags::FourCC &&
        header.basicHeader.pixelFormat.fourCC == DdsFourCC::Dx10;

    if( header.hasExtendedHeader ) {
        stream.read( &header.extendedHeader, sizeof(header.extendedHeader) );
    }

    if( strict ) {
        validateDdsHeader( header );
    }

    return header;
}

Texture::Pointer createTexture(
    const DdsHeader &ddsHeader, const Texture::LoadingParameters &parameters )
{
    const DdsBasicHeader &basicHeader = ddsHeader.basicHeader;

    const Texture::Format format =
        selectTextureFormat( ddsHeader, parameters.defaultColorSpace );

    unsigned int mipLevels = 1;

    if( (basicHeader.complexityFlags & DdsComplexityFlags::MipMap) &&
            (basicHeader.flags & DdsFlags::MipMapCount) )
        mipLevels = basicHeader.mipMapCount;

    auto createSeparate1dTexture = [&] {
        Texture::Separate1dDescription description;

        description.format = format;
        description.width = basicHeader.width;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    auto createLayered1dTexture = [&] {
        Texture::Layered1dDescription description;

        description.format = format;
        description.width = basicHeader.width;
        description.mipLevels = mipLevels;
        description.layers = ddsHeader.extendedHeader.arraySize;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    auto createSeparate2dTexture = [&] {
        Texture::Separate2dDescription description;

        description.format = format;
        description.width = basicHeader.width;
        description.height = basicHeader.height;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    auto createLayered2dTexture = [&] {
        Texture::Layered2dDescription description;

        description.format = format;
        description.width = basicHeader.width;
        description.height = basicHeader.height;
        description.mipLevels = mipLevels;
        description.layers = ddsHeader.extendedHeader.arraySize;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    auto createSeparate3dTexture = [&] {
        Texture::Separate3dDescription description;

        description.format = format;
        description.width = basicHeader.width;
        description.height = basicHeader.height;
        description.depth = basicHeader.depth;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    auto createCubeMapTexture = [&] {
        Texture::CubeMapDescription description;

        description.format = format;
        description.dimension = basicHeader.width;
        description.mipLevels = mipLevels;
        description.resourceType = ResourceType::Static;

        return Texture::create( description );
    };

    if( ddsHeader.hasExtendedHeader ) {
        const DdsExtendedHeader &extendedHeader = ddsHeader.extendedHeader;

        if( extendedHeader.resourceDimension == DdsResourceDimension::_1d ) {
            if( extendedHeader.arraySize > 1 ) {
                return createLayered1dTexture();
            } else {
                return createSeparate1dTexture();
            }
        }

        if( extendedHeader.resourceDimension == DdsResourceDimension::_2d &&
                extendedHeader.resourceFlags & DdsResourceFlags::CubeMap ) {
            if( extendedHeader.arraySize > 1 ) {
                throw "Unsupported DDS texture "
                    "(libstorm doesn't support cubemap arrays)";
            }

            return createCubeMapTexture();
        }

        if( extendedHeader.resourceDimension == DdsResourceDimension::_2d ) {
            if( extendedHeader.arraySize > 1 ) {
                return createLayered2dTexture();
            } else {
                return createSeparate2dTexture();
            }
        }

        if( extendedHeader.resourceDimension == DdsResourceDimension::_3d ) {
            return createSeparate3dTexture();
        }
    }

    if( basicHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
        return createSeparate3dTexture();
    }

    if( basicHeader.surfaceFlags & DdsSurfaceFlags::CubeMap ) {
        return createCubeMapTexture();
    }

    return createSeparate2dTexture();
}

void parseDdsTextureLayer(
    BinaryInputStream &stream, Texture::Pointer texture, unsigned int layer )
{
    const Texture::Description &textureDescription = texture->getDescription();

    for( unsigned int mipLevel = 0;
            mipLevel < textureDescription.mipLevels; ++mipLevel )
    {
        const Texture::MipLevelDimensions dimensions =
            texture->getMipLevelDimensions( mipLevel );

        size_t texelSize;

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
        case Texture::Format::RgbFloat32:
            texelSize = 12;
            break;
        case Texture::Format::RgbaFloat32:
            texelSize = 16;
            break;
        default:
            texelSize = 0;
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
        default:
            // Ignore GCC warnings 'enumeration value not handled in switch'
            break;
        }

        storm_assert( texels.size() != 0 );
        stream.read( texels.data(), texels.size() );

        switch( textureDescription.layout ) {
        case Texture::Layout::Separate1d:
            {
                Texture::Separate1dRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.width = dimensions.width;

                texture->setTexels( region, texels.data() );
            }
            break;
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
        case Texture::Layout::Layered1d:
            {
                Texture::Layered1dRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.layer = layer;
                region.width = dimensions.width;

                texture->setTexels( region, texels.data() );
            }
            break;
        case Texture::Layout::Layered2d:
            {
                Texture::Layered2dRegion region = { 0 };

                region.mipLevel = mipLevel;
                region.layer = layer;
                region.width = dimensions.width;
                region.height = dimensions.height;

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
            for( unsigned int layer = 0;
                    layer < texture->getDescription().layers; ++layer ) {
                parseDdsTextureLayer( stream, texture, layer );
            }
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
