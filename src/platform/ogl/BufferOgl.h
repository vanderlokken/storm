#pragma once

#include "CoreTypesOgl.h"
#include "HandleOgl.h"
#include "ResourceType.h"

namespace storm {

class BufferHandleOgl : public HandleOgl {
public:
    BufferHandleOgl();
    ~BufferHandleOgl();
};

class BufferOgl {
    NONCOPYABLE( BufferOgl );
public:
    BufferOgl( size_t size, const void *data, ResourceType resourceType );

    void getData( size_t offset, size_t size, void *data ) const;
    void setData( size_t offset, size_t size, const void *data );

    const BufferHandleOgl& getHandle() const noexcept;

private:
    BufferHandleOgl _handle;
    size_t _size;
};

}
