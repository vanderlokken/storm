#pragma once

#include <memory>

#include <storm/noexcept.h>
#include <storm/resource_type.h>

namespace storm {

class Buffer {
public:
    typedef std::shared_ptr<Buffer> Pointer;

    struct Description {
        size_t size;
        size_t elementSize;
        ResourceType resourceType;
    };

    static Pointer create( const Description&, const void *data = nullptr );

    template<class Container>
        static Pointer create( const Container &vertices );

    virtual ~Buffer() { }

    virtual void getData( size_t offset, size_t size, void *data ) const = 0;
    virtual void setData( size_t offset, size_t size, const void *data ) = 0;

    virtual const Description& getDescription() const noexcept = 0;
};

template<class Container> Buffer::Pointer Buffer::create(
    const Container &container )
{
    Description description;
    description.size = sizeof( Container::value_type ) * container.size();
    description.elementSize = sizeof( Container::value_type );
    description.resourceType = ResourceType::Static;

    return create( description, container.data() );
}

}
