#pragma once

#include <memory>

#include "Noexcept.h"
#include "ResourceType.h"

namespace storm {

class IndexBuffer {
public:
    struct Description {
        size_t indexSize;
        size_t bufferSize;
        ResourceType resourceType;
    };

    static std::shared_ptr<IndexBuffer> create( const Description&, const void *indices = nullptr );

    template<class Container>
        static std::shared_ptr<IndexBuffer> create( const Container &indices );

    virtual ~IndexBuffer() { }

    virtual void getIndices( size_t offset, size_t size, void *indices ) const = 0;
    virtual void setIndices( size_t offset, size_t size, const void *indices ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

template<class Container> std::shared_ptr<IndexBuffer> IndexBuffer::create( const Container &indices ) {
    typedef typename Container::value_type IndexType;

    static_assert( sizeof(IndexType) == 2 || sizeof(IndexType) == 4, "Inappropriate index type" );

    Description description;
    description.indexSize = sizeof( IndexType );
    description.bufferSize = sizeof( IndexType ) * indices.size();
    description.resourceType = ResourceTypeStatic;

    return create( description, indices.data() );
}

}
