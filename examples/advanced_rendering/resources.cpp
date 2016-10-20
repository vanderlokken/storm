#include "resources.h"

#include <array>
#include <cstdint>

#include <storm/color.h>
#include <storm/common_vertex_types.h>

storm::Texture::Pointer createCheckboardPatternTexture() {
    storm::Texture::Separate2dDescription description;
    description.format = storm::Texture::Format::RgbaNormUint8;
    description.width = 2;
    description.height = 2;
    description.mipLevels = 1;
    description.resourceType = storm::ResourceType::Static;

    const storm::Texture::Pointer texture =
        storm::Texture::create( description );

    storm::Texture::Separate2dRegion region;
    region.mipLevel = 0;
    region.x = 0;
    region.y = 0;
    region.width = description.width;
    region.height = description.height;

    const storm::CompressedColor texels[4] = {
        storm::CompressedColor(250, 250, 250),
        storm::CompressedColor(180, 180, 250),
        storm::CompressedColor(180, 180, 80),
        storm::CompressedColor(250, 250, 250)
    };

    texture->setTexels( region, texels );

    return texture;
}

storm::Sampler::Pointer createCheckboardPatternSampler() {
    storm::Sampler::Description description;
    description.minifyingFilter = storm::Sampler::MinifyingFilter::Nearest;
    description.magnifyingFilter = storm::Sampler::MagnifyingFilter::Nearest;
    description.maximalAnisotropyDegree = 1;
    description.wrapModes = {
        storm::Sampler::WrapMode::Repeated,
        storm::Sampler::WrapMode::Repeated,
        storm::Sampler::WrapMode::Repeated
    };
    description.borderColor = storm::Color::Black;
    description.comparison.enabled = false;
    description.comparison.condition = storm::Condition::False;
    return storm::Sampler::create( description );
}

storm::Mesh::Pointer createTexturedCubeMesh() {
    using storm::Vector2d;
    using storm::Vector;

    const std::array<storm::OrientedTexturedVertex, 24> vertices = {
        // Top
        Vector(-1.f,  1.f, -1.f), Vector(0.f, 1.f, 0.f), Vector2d(0.f, 0.f),
        Vector(-1.f,  1.f,  1.f), Vector(0.f, 1.f, 0.f), Vector2d(0.f, 1.f),
        Vector( 1.f,  1.f, -1.f), Vector(0.f, 1.f, 0.f), Vector2d(1.f, 0.f),
        Vector( 1.f,  1.f,  1.f), Vector(0.f, 1.f, 0.f), Vector2d(1.f, 1.f),
        // Bottom
        Vector(-1.f, -1.f,  1.f), Vector(0.f, -1.f, 0.f), Vector2d(0.f, 0.f),
        Vector(-1.f, -1.f, -1.f), Vector(0.f, -1.f, 0.f), Vector2d(0.f, 1.f),
        Vector( 1.f, -1.f,  1.f), Vector(0.f, -1.f, 0.f), Vector2d(1.f, 0.f),
        Vector( 1.f, -1.f, -1.f), Vector(0.f, -1.f, 0.f), Vector2d(1.f, 1.f),
        // Front
        Vector(-1.f, -1.f, -1.f), Vector(0.f, 0.f, -1.f), Vector2d(1.f, 0.f),
        Vector(-1.f,  1.f, -1.f), Vector(0.f, 0.f, -1.f), Vector2d(1.f, 1.f),
        Vector( 1.f, -1.f, -1.f), Vector(0.f, 0.f, -1.f), Vector2d(0.f, 0.f),
        Vector( 1.f,  1.f, -1.f), Vector(0.f, 0.f, -1.f), Vector2d(0.f, 1.f),
        // Back
        Vector( 1.f, -1.f,  1.f), Vector(0.f, 0.f, 1.f), Vector2d(1.f, 0.f),
        Vector( 1.f,  1.f,  1.f), Vector(0.f, 0.f, 1.f), Vector2d(1.f, 1.f),
        Vector(-1.f, -1.f,  1.f), Vector(0.f, 0.f, 1.f), Vector2d(0.f, 0.f),
        Vector(-1.f,  1.f,  1.f), Vector(0.f, 0.f, 1.f), Vector2d(0.f, 1.f),
        // Right
        Vector( 1.f, -1.f, -1.f), Vector(1.f, 0.f, 0.f), Vector2d(0.f, 0.f),
        Vector( 1.f,  1.f, -1.f), Vector(1.f, 0.f, 0.f), Vector2d(0.f, 1.f),
        Vector( 1.f, -1.f,  1.f), Vector(1.f, 0.f, 0.f), Vector2d(1.f, 0.f),
        Vector( 1.f,  1.f,  1.f), Vector(1.f, 0.f, 0.f), Vector2d(1.f, 1.f),
        // Left
        Vector(-1.f, -1.f,  1.f), Vector(-1.f, 0.f, 0.f), Vector2d(0.f, 0.f),
        Vector(-1.f,  1.f,  1.f), Vector(-1.f, 0.f, 0.f), Vector2d(0.f, 1.f),
        Vector(-1.f, -1.f, -1.f), Vector(-1.f, 0.f, 0.f), Vector2d(1.f, 0.f),
        Vector(-1.f,  1.f, -1.f), Vector(-1.f, 0.f, 0.f), Vector2d(1.f, 1.f)
    };

    // 0xffff is a primitive restart index.
    const std::array<uint16_t, 29> indices = {
        0,  1,  2,  3, 0xffff,
        4,  5,  6,  7, 0xffff,
        8,  9, 10, 11, 0xffff,
       12, 13, 14, 15, 0xffff,
       16, 17, 18, 19, 0xffff,
       20, 21, 22, 23
    };

    storm::Mesh::Description description;
    description.vertexBuffer = storm::Buffer::create( vertices );
    description.indexBuffer = storm::Buffer::create( indices );
    description.vertexFormat = storm::OrientedTexturedVertex::getFormat();
    description.primitiveTopology =
        storm::Mesh::PrimitiveTopology::TriangleStrip;
    return storm::Mesh::create( description );
}
