#pragma once

#include <storm/framebuffer.h>
#include <storm/platform/ogl/handle_ogl.h>

namespace storm {

class FramebufferHandleOgl : public HandleOgl {
public:
    FramebufferHandleOgl();
    ~FramebufferHandleOgl();
};

class ScopeFramebufferBinding {
public:
    ScopeFramebufferBinding( GLuint binding );
    ~ScopeFramebufferBinding();

private:
    GLint _previousBinding;
};

class FramebufferOgl : public Framebuffer {
public:
    FramebufferOgl( const Description& );

    const Description& getDescription() const override;

    const FramebufferHandleOgl& getHandle() const;

private:
    Description _description;
    FramebufferHandleOgl _handle;
};

}
