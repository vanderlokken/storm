#include "resources.h"

#include <array>
#include <cstdint>

#include <storm/color.h>
#include <storm/common_vertex_types.h>

storm::Texture::Pointer createCheckboardPatternTexture() {
    storm::Texture::Description description;
    description.layout = storm::Texture::Layout::Separate2d;
    description.format = storm::Texture::Format::ArgbUint8;
    description.width = 2;
    description.height = 2;
    description.depth = 1;
    description.mipLevels = 1;
    description.texelSamples = 1;
    description.resourceType = storm::ResourceType::Static;

    const storm::CompressedColor texels[4] = {
        storm::CompressedColor(250, 250, 250),
        storm::CompressedColor(180, 180, 250),
        storm::CompressedColor(180, 180, 250),
        storm::CompressedColor(250, 250, 250)
    };

    const storm::Texture::Pointer texture =
        storm::Texture::create( description );
    texture->setTexels( 0, texels );
    return texture;
}

storm::Sampler::Pointer createCheckboardPatternSampler() {
    storm::Sampler::Description description;
    description.minifyingFilter = storm::Sampler::MinifyingFilter::Nearest;
    description.magnifyingFilter = storm::Sampler::MagnifyingFilter::Nearest;
    description.maximalAnisotropyDegree = 0;
    description.wrapModes = {
        storm::Sampler::WrapMode::Repeated,
        storm::Sampler::WrapMode::Repeated,
        storm::Sampler::WrapMode::Repeated
    };
    description.borderColor = storm::Color::Black;
    return storm::Sampler::create( description );
}

storm::Mesh::Pointer createTexturedCubeMesh() {
    using storm::FlatVector;
    using storm::Vector;

    const std::array<storm::OrientedTexturedVertex, 24> vertices = {
        // Top
        Vector(-1,  1, -1), Vector(0, 1, 0), FlatVector(0, 0),
        Vector(-1,  1,  1), Vector(0, 1, 0), FlatVector(0, 1),
        Vector( 1,  1, -1), Vector(0, 1, 0), FlatVector(1, 0),
        Vector( 1,  1,  1), Vector(0, 1, 0), FlatVector(1, 1),
        // Bottom
        Vector(-1, -1,  1), Vector(0, -1, 0), FlatVector(0, 0),
        Vector(-1, -1, -1), Vector(0, -1, 0), FlatVector(0, 1),
        Vector( 1, -1,  1), Vector(0, -1, 0), FlatVector(1, 0),
        Vector( 1, -1, -1), Vector(0, -1, 0), FlatVector(1, 1),
        // Front
        Vector(-1, -1, -1), Vector(0, 0, -1), FlatVector(1, 0),
        Vector(-1,  1, -1), Vector(0, 0, -1), FlatVector(1, 1),
        Vector( 1, -1, -1), Vector(0, 0, -1), FlatVector(0, 0),
        Vector( 1,  1, -1), Vector(0, 0, -1), FlatVector(0, 1),
        // Back
        Vector( 1, -1,  1), Vector(0, 0, 1), FlatVector(1, 0),
        Vector( 1,  1,  1), Vector(0, 0, 1), FlatVector(1, 1),
        Vector(-1, -1,  1), Vector(0, 0, 1), FlatVector(0, 0),
        Vector(-1,  1,  1), Vector(0, 0, 1), FlatVector(0, 1),
        // Right
        Vector( 1, -1, -1), Vector(1, 0, 0), FlatVector(0, 0),
        Vector( 1,  1, -1), Vector(1, 0, 0), FlatVector(0, 1),
        Vector( 1, -1,  1), Vector(1, 0, 0), FlatVector(1, 0),
        Vector( 1,  1,  1), Vector(1, 0, 0), FlatVector(1, 1),
        // Left
        Vector(-1, -1,  1), Vector(-1, 0, 0), FlatVector(0, 0),
        Vector(-1,  1,  1), Vector(-1, 0, 0), FlatVector(0, 1),
        Vector(-1, -1, -1), Vector(-1, 0, 0), FlatVector(1, 0),
        Vector(-1,  1, -1), Vector(-1, 0, 0), FlatVector(1, 1)
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
