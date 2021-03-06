#include <storm/framebuffer.h>

namespace storm {

Framebuffer::Pointer Framebuffer::create(
    GpuContext::Pointer gpuContext, Texture::Pointer texture )
{
    Framebuffer::Buffer buffer;
    buffer.texture = texture;
    buffer.mipLevel = 0;
    buffer.layer = 0;

    Framebuffer::Description description;
    description.buffers = {buffer};

    return Framebuffer::create( gpuContext, description );
}

Framebuffer::Pointer Framebuffer::create(
    GpuContext::Pointer gpuContext,
    Dimensions dimensions,
    unsigned int texelSamples,
    const std::vector<Texture::Format> &bufferFormats )
{
    Framebuffer::Description description;

    for( Texture::Format bufferFormat : bufferFormats ) {
        Texture::Pointer texture;

        if( texelSamples == 1 ) {
            Texture::Separate2dDescription textureDescription;
            textureDescription.format = bufferFormat;
            textureDescription.width = dimensions.width;
            textureDescription.height = dimensions.height;
            textureDescription.mipLevels = 1;
            textureDescription.resourceType = ResourceType::Dynamic;

            texture = Texture::create( gpuContext, textureDescription );
        } else {
            Texture::Separate2dMsaaDescription textureDescription;
            textureDescription.format = bufferFormat;
            textureDescription.width = dimensions.width;
            textureDescription.height = dimensions.height;
            textureDescription.texelSamples = texelSamples;

            texture = Texture::create( gpuContext, textureDescription );
        }

        Buffer buffer;
        buffer.texture = texture;
        buffer.mipLevel = 0;
        buffer.layer = 0;

        description.buffers.push_back( buffer );
    }

    return Framebuffer::create( gpuContext, description );
}

}
