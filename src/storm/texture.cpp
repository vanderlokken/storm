#include <storm/texture.h>

#include <algorithm>
#include <vector>

#include <storm/binary_input_stream.h>
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
};

Texture::Format selectTextureFormat( const DdsPixelFormat &ddsPixelFormat ) {
    if( ddsPixelFormat.flags & DdsPixelFormatFlags::FourCC ) {
        switch( ddsPixelFormat.fourCC ) {
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('1' << 24):
            return Texture::Format::ArgbDxt1;
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('3' << 24):
            return Texture::Format::ArgbDxt3;
        case ('D' << 0) | ('X' << 8) | ('T' << 16) | ('5' << 24):
            return Texture::Format::ArgbDxt5;
        }
    }

    throw ResourceLoadingError() << "Unsupported DDS texture";
}

Texture::Pointer parseDds( BinaryInputStream &stream, bool strict ) {
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
        }

        if( ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume ) {
            check( ddsHeader.flags & DdsFlags::Depth );
            check( !(ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMap) );
        }

        check( ddsHeader.pixelFormat.size == 32 );
    }

    Texture::Description description;

    if( ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume )
        description.layout = Texture::Layout::Separate3d;
    else if( ddsHeader.surfaceFlags & DdsSurfaceFlags::CubeMap )
        description.layout = Texture::Layout::CubeMap;
    else
        description.layout = Texture::Layout::Separate2d;

    description.format = selectTextureFormat( ddsHeader.pixelFormat );
    description.width = ddsHeader.width;
    description.height = ddsHeader.height;

    if( (ddsHeader.surfaceFlags & DdsSurfaceFlags::Volume) &&
            (ddsHeader.flags & DdsFlags::Depth) )
        description.depth = ddsHeader.depth;
    else
        description.depth = 1;

    if( (ddsHeader.complexityFlags & DdsComplexityFlags::MipMap) &&
            (ddsHeader.flags & DdsFlags::MipMapCount) )
        description.mipLevels = ddsHeader.mipMapCount;
    else
        description.mipLevels = 1;

    description.texelSamples = 1;
    description.resourceType = ResourceType::Static;

    Texture::Pointer texture = Texture::create( description );

    std::vector<char> texels;
    switch( description.format ) {
    case Texture::Format::ArgbDxt1:
        texels.resize(
            static_cast<size_t>(ceil(description.width / 4.0f)) *
            static_cast<size_t>(ceil(description.height / 4.0f)) * 8 );
        break;
    case Texture::Format::ArgbDxt3:
    case Texture::Format::ArgbDxt5:
        texels.resize(
            static_cast<size_t>(ceil(description.width / 4.0f)) *
            static_cast<size_t>(ceil(description.height / 4.0f)) * 16 );
        break;
    default:
        throwNotImplemented();
    }

    stream.read( texels.data(), texels.size() );

    texture->setTexels( 0, texels.data() );
    return texture;
}

} // namespace

Texture::Pointer Texture::load( std::istream &stream, FileFormat fileFormat ) {
    try {
        BinaryInputStream binaryInputStream( stream );
        switch( fileFormat ) {
        case FileFormat::Dds:
            return parseDds( binaryInputStream, /* strict = */ false );
        case FileFormat::DdsStrict:
            return parseDds( binaryInputStream, /* strict = */ true );
        }
        throw ResourceLoadingError() << "Unexpected file format value";
    } catch( std::ios_base::failure& ) {
        throw ResourceLoadingError() << "Invalid DDS texture data";
    }
}

Texture::Pointer Texture::load(
    const std::string &filename, FileFormat fileFormat )
{
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throw ResourceLoadingError() << "Couldn't open " << filename;

    return Texture::load( stream, fileFormat );
}

}
