#pragma once

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/rendering_buffer_set.h>

namespace storm {

class FramebufferHandleOgl : public HandleOgl {
public:
    FramebufferHandleOgl();
    ~FramebufferHandleOgl();
};

class RenderingBufferSetOgl : public RenderingBufferSet {
public:
    RenderingBufferSetOgl( const Description& );

    virtual const Description& getDescription() const;

    const FramebufferHandleOgl& getHandle() const;

private:
    Description _description;
    FramebufferHandleOgl _handle;
};

}
