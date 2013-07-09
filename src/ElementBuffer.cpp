#include "ElementBuffer.h"

#include <cstdint>
#include <fstream>
#include <numeric>
#include <vector>

#include "ElementBuffer.h"
#include "Exception.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace storm {

std::shared_ptr<ElementBuffer> ElementBuffer::load(
    const std::string &filename )
{
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
    vertexBufferDescription.resourceType = ResourceTypeStatic;

    const size_t indexSize = 2;

    IndexBuffer::Description indexBufferDescription;
    indexBufferDescription.indexSize = indexSize;
    indexBufferDescription.bufferSize = indexDataSize;
    indexBufferDescription.resourceType = ResourceTypeStatic;

    ElementBuffer::Description elementBufferDescription;
    elementBufferDescription.vertexBuffer = VertexBuffer::create( vertexBufferDescription, vertexData.data() );
    elementBufferDescription.indexBuffer = IndexBuffer::create( indexBufferDescription, indexData.data() );
    elementBufferDescription.elementTopology = ElementBuffer::ElementTopologyList;

    return ElementBuffer::create( elementBufferDescription );
}

}