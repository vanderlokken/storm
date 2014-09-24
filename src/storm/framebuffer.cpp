#include <storm/framebuffer.h>

namespace storm {

Framebuffer::Pointer Framebuffer::create( Dimensions dimensions,
    unsigned int texelSamples, const std::vector<Texture::Format> &bufferFormats )
{
    Texture::Description textureDescription;
    textureDescription.layout = (texelSamples == 1) ?
        Texture::Layout::Separate2d : Texture::Layout::Separate2dMsaa;
    textureDescription.width = dimensions.width;
    textureDescription.height = dimensions.height;
    textureDescription.depth = 1;
    textureDescription.mipLevels = 1;
    textureDescription.texelSamples = texelSamples;
    textureDescription.resourceType = ResourceType::Dynamic;

    Framebuffer::Description description;

    for( Texture::Format bufferFormat : bufferFormats ) {
        textureDescription.format = bufferFormat;
        description.buffers.emplace_back(
            Buffer{Texture::create(textureDescription), 0, 0} );
    }

    return Framebuffer::create( description );
}

}
