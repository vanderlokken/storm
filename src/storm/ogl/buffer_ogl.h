#pragma once

#include <storm/buffer.h>
#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>

namespace storm {

using BufferHandleOgl = HandleOgl<GlGenBuffers, GlDeleteBuffers>;

class BufferOgl : public Buffer {
public:
    BufferOgl(
        GpuContextOgl::Pointer gpuContext,
        const Description &description,
        const void *data );

    void getData( size_t offset, size_t size, void *data ) const override;
    void setData( size_t offset, size_t size, const void *data ) override;

    const Description& getDescription() const override;

    const BufferHandleOgl& getHandle() const;

private:
    Description _description;
    BufferHandleOgl _handle;
};

}
