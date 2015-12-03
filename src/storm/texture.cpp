#include <storm/texture.h>

#include <algorithm>

#include <storm/binary_input_stream.h>
#include <storm/exception.h>
#include <storm/texture_dds.h>
#include <storm/texture_png.h>
#include <storm/throw_exception.h>

namespace storm {

Texture::Pointer Texture::load(
    std::istream &stream, const LoadingParameters &parameters )
{
    BinaryInputStream binaryInputStream( stream );
    switch( parameters.fileFormat ) {
    case FileFormat::Dds:
    case FileFormat::DdsStrict:
        return parseDds( binaryInputStream, parameters );
    case FileFormat::Png:
        return parsePng( binaryInputStream, parameters );
    default:
        storm_assert_unreachable( "Unexpected file format value" );
        return nullptr;
    }
}

Texture::Pointer Texture::load(
    const std::string &filename, const LoadingParameters &parameters )
{
    std::ifstream stream( filename, std::ios::in | std::ios::binary );

    if( !stream )
        throw ResourceLoadingError() << "Couldn't open " << filename;

    return Texture::load( stream, parameters );
}

Texture::MipLevelDimensions
Texture::getMipLevelDimensions( unsigned int mipLevel ) const {
    const Description &description = getDescription();

    storm_assert( mipLevel < description.mipLevels );

    Texture::MipLevelDimensions dimensions;
    dimensions.width = std::max( description.width >> mipLevel, 1u );
    dimensions.height = std::max( description.height >> mipLevel, 1u );
    dimensions.depth = std::max( description.depth >> mipLevel, 1u );
    return dimensions;
}

}
