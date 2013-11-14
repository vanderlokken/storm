#pragma once

#include <memory>
#include <vector>

#include <storm/noexcept.h>
#include <storm/resource_type.h>
#include <storm/vertex.h>

namespace storm {

class VertexBuffer {
public:
    typedef std::shared_ptr<VertexBuffer> Pointer;

    struct Description {
        std::vector< Vertex::Attribute > vertexAttributes;
        size_t vertexSize;
        size_t bufferSize;
        ResourceType resourceType;
    };

    static VertexBuffer::Pointer create( const Description&, const void *vertices = nullptr );

    template<class Container>
        static VertexBuffer::Pointer create( const Container &vertices );

    virtual ~VertexBuffer() { }

    virtual void getVertices( size_t offset, size_t size, void *vertices ) const = 0;
    virtual void setVertices( size_t offset, size_t size, const void *vertices ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

template<class Container> VertexBuffer::Pointer VertexBuffer::create( const Container &vertices ) {
    typedef typename Container::value_type VertexType;

    Description description;
    description.vertexAttributes =
        std::vector< Vertex::Attribute >( std::begin(VertexType::attributes), std::end(VertexType::attributes) );
    description.vertexSize = sizeof( VertexType );
    description.bufferSize = sizeof( VertexType ) * vertices.size();
    description.resourceType = ResourceTypeStatic;

    return create( description, vertices.data() );
}

}
