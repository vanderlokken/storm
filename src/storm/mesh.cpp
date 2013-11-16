#include <storm/mesh.h>

#include <cstdint>
#include <fstream>
#include <numeric>
#include <vector>

#include <storm/exception.h>
#include <storm/index_buffer.h>
#include <storm/vertex_buffer.h>

namespace storm {

Mesh::Pointer Mesh::load( const std::string &filename ) {
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throwInvalidArgument( "'stream' is invalid" );

    uint32_t attributeCount = 0;
    stream.read( reinterpret_cast<char*>(&attributeCount), sizeof(attributeCount) );

    std::vector< Vertex::Attribute > attributes( attributeCount );
    for( auto attribute = attributes.begin(); attribute != attributes.end(); ++attribute ) {
        uint32_t semantics = 0;
        uint32_t format = 0;

        stream.read( reinterpret_cast<char*>(&semantics), sizeof(semantics) );
        stream.read( reinterpret_cast<char*>(&format), sizeof(format) );

        attribute->semantics = static_cast< Vertex::Attribute::Semantics >( semantics );
        attribute->format = static_cast< Vertex::Attribute::Format >( format );
    }

    uint32_t vertexDataSize = 0;
    stream.read( reinterpret_cast<char*>(&vertexDataSize), sizeof(vertexDataSize) );

    std::vector< char > vertexData( vertexDataSize );
    stream.read( vertexData.data(), vertexDataSize );

    uint32_t indexDataSize = 0;
    stream.read( reinterpret_cast<char*>(&indexDataSize), sizeof(indexDataSize) );

    std::vector< char > indexData( indexDataSize );
    stream.read( indexData.data(), indexDataSize );

    const size_t vertexSize = std::accumulate( attributes.cbegin(), attributes.cend(), 0,
        [](size_t size, Vertex::Attribute attribute) { return size + attribute.getSize(); } );

    VertexBuffer::Description vertexBufferDescription;
    vertexBufferDescription.vertexAttributes = attributes;
    vertexBufferDescription.vertexSize = vertexSize;
    vertexBufferDescription.bufferSize = vertexDataSize;
    vertexBufferDescription.resourceType = ResourceType::Static;

    const size_t indexSize = 2;

    IndexBuffer::Description indexBufferDescription;
    indexBufferDescription.indexSize = indexSize;
    indexBufferDescription.bufferSize = indexDataSize;
    indexBufferDescription.resourceType = ResourceType::Static;

    Description meshDescription;
    meshDescription.vertexBuffer = VertexBuffer::create( vertexBufferDescription, vertexData.data() );
    meshDescription.indexBuffer = IndexBuffer::create( indexBufferDescription, indexData.data() );
    meshDescription.triangleTopology = TriangleTopology::List;

    return create( meshDescription );
}

}
