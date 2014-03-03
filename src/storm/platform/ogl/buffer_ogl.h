#pragma once

#include <storm/buffer.h>
#include <storm/platform/ogl/handle_ogl.h>

namespace storm {

class BufferHandleOgl : public HandleOgl {
public:
    BufferHandleOgl();
    ~BufferHandleOgl();
};

class BufferOgl : public Buffer {
    NONCOPYABLE( BufferOgl );
public:
    BufferOgl( const Description&, const void *data );

    virtual void getData( size_t offset, size_t size, void *data ) const;
    virtual void setData( size_t offset, size_t size, const void *data );

    virtual const Description& getDescription() const noexcept;

    const BufferHandleOgl& getHandle() const noexcept;

private:
    Description _description;
    BufferHandleOgl _handle;
};

}
