#pragma once

#include <memory>

#include <storm/gpu_context.h>
#include <storm/resource_type.h>

namespace storm {

class Buffer {
public:
    using Pointer = std::shared_ptr<Buffer>;

    struct Description {
        size_t size;
        ResourceType resourceType;
    };

    static Pointer create(
        GpuContext::Pointer gpuContext,
        const Description &description,
        const void *data = nullptr );

    template <class Container>
    static Pointer create(
        GpuContext::Pointer gpuContext,
        const Container &container );

    virtual ~Buffer() = default;

    virtual void getData( size_t offset, size_t size, void *data ) const = 0;
    virtual void setData( size_t offset, size_t size, const void *data ) = 0;

    void getData( void *data ) const {
        getData( 0, getDescription().size, data );
    }

    void setData( const void *data ) {
        setData( 0, getDescription().size, data );
    }

    virtual const Description& getDescription() const = 0;
};

template <class Container>
Buffer::Pointer Buffer::create(
    GpuContext::Pointer gpuContext, const Container &container )
{
    Description description;
    description.size =
        sizeof( typename Container::value_type ) * container.size();
    description.resourceType = ResourceType::Static;

    return create( gpuContext, description, container.data() );
}

}
