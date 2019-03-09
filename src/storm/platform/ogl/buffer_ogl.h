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
public:
    BufferOgl( const Description&, const void *data );

    void getData( size_t offset, size_t size, void *data ) const override;
    void setData( size_t offset, size_t size, const void *data ) override;

    const Description& getDescription() const override;

    const BufferHandleOgl& getHandle() const;

private:
    Description _description;
    BufferHandleOgl _handle;
};

}
