#include <storm/texture_png.h>

#include <sstream>
#include <vector>

#include <storm/throw_exception.h>

#ifdef storm_enable_png_support
#  include <png.h>
#endif

namespace storm {

Texture::Pointer parsePng(
    BinaryInputStream &stream, const Texture::LoadingParameters &parameters )
{
#ifdef storm_enable_png_support
    std::ostringstream bufferStream;

    if( !(bufferStream << (*stream).rdbuf()) )
        throw ResourceLoadingError() << "Couldn't read texture";

    const std::string buffer = bufferStream.str();

    png_image image = {};

    image.version = PNG_IMAGE_VERSION;

    if( !png_image_begin_read_from_memory(
            &image,
            buffer.data(),
            buffer.size()) )
        throw ResourceLoadingError() << "Invalid PNG texture data";

    image.format = PNG_FORMAT_RGBA;

    std::vector<uint8_t> texels( PNG_IMAGE_SIZE(image) );

    if( !png_image_finish_read(
            &image,
            nullptr /*background*/, texels.data(), 0 /*stride*/,
            nullptr /*colormap*/) )
        throw ResourceLoadingError() << "Invalid PNG texture data";

    Texture::Separate2dDescription description;
    if( parameters.defaultColorSpace == Texture::ColorSpace::sRGB )
        description.format = Texture::Format::SrgbaUint8;
    else
        description.format = Texture::Format::RgbaUint8;
    description.width = image.width;
    description.height = image.height;
    description.mipLevels = 1;
    description.resourceType = ResourceType::Static;

    Texture::Pointer texture = Texture::create( description );

    Texture::Separate2dRegion region;
    region.mipLevel = 0;
    region.x = 0;
    region.y = 0;
    region.width = image.width;
    region.height = image.height;

    texture->setTexels( region, texels.data() );

    return texture;
#else
    throwNotImplemented();
#endif
}

}
