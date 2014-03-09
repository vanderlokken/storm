#include <storm/mesh.h>

#include <cstdint>
#include <fstream>
#include <numeric>
#include <vector>

#include <storm/throw_exception.h>

namespace storm {

typedef VertexFormat::Attribute VertexAttribute;

Mesh::Pointer Mesh::load( const std::string &filename ) {
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throw Exception( "Couldn't open " + filename );

    uint32_t attributeCount = 0;
    stream.read( reinterpret_cast<char*>(&attributeCount), sizeof(attributeCount) );

    std::vector< VertexAttribute > attributes( attributeCount );
    for( auto &attribute : attributes ) {
        uint32_t semantics = 0;
        uint32_t format = 0;

        stream.read( reinterpret_cast<char*>(&semantics), sizeof(semantics) );
        stream.read( reinterpret_cast<char*>(&format), sizeof(format) );

        attribute.semantics = static_cast< VertexAttribute::Semantics >( semantics );
        attribute.format = static_cast< VertexAttribute::Format >( format );
    }

    uint32_t vertexDataSize = 0;
    stream.read( reinterpret_cast<char*>(&vertexDataSize), sizeof(vertexDataSize) );

    std::vector< char > vertexData( vertexDataSize );
    stream.read( vertexData.data(), vertexDataSize );

    uint32_t indexDataSize = 0;
    stream.read( reinterpret_cast<char*>(&indexDataSize), sizeof(indexDataSize) );

    std::vector< char > indexData( indexDataSize );
    stream.read( indexData.data(), indexDataSize );

    VertexFormat::Pointer vertexFormat = VertexFormat::create( {attributes} );

    Buffer::Description vertexBufferDescription;
    vertexBufferDescription.size = vertexDataSize;
    vertexBufferDescription.elementSize = vertexFormat->getVertexSize();
    vertexBufferDescription.resourceType = ResourceType::Static;

    const size_t indexSize = 2;

    Buffer::Description indexBufferDescription;
    indexBufferDescription.size = indexDataSize;
    indexBufferDescription.elementSize = indexSize;
    indexBufferDescription.resourceType = ResourceType::Static;

    Description meshDescription;
    meshDescription.vertexFormat = vertexFormat;
    meshDescription.vertexBuffer = Buffer::create( vertexBufferDescription, vertexData.data() );
    meshDescription.indexBuffer = Buffer::create( indexBufferDescription, indexData.data() );
    meshDescription.triangleTopology = TriangleTopology::List;

    return create( meshDescription );
}

}
