#ifndef storm_VertexBuffer_h
#define storm_VertexBuffer_h

#include <memory>
#include <vector>

#include "Noexcept.h"
#include "ResourceType.h"
#include "Vertex.h"

namespace storm {

class VertexBuffer {
public:
    struct Description {
        std::vector< Vertex::Attribute > vertexAttributes;
        size_t vertexSize;
        size_t bufferSize;
        ResourceType resourceType;
    };

    static std::shared_ptr<VertexBuffer> create( const Description&, const void *vertices = nullptr );

    template<class Container>
        static std::shared_ptr<VertexBuffer> create( const Container &vertices );

    virtual ~VertexBuffer() noexcept { }

    virtual void getVertices( size_t offset, size_t size, void *vertices ) const = 0;
    virtual void setVertices( size_t offset, size_t size, const void *vertices ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

template<class Container> std::shared_ptr<VertexBuffer> VertexBuffer::create( const Container &vertices ) {
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

#endif
