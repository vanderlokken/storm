#pragma once

#include <storm/framebuffer.h>
#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>

namespace storm {

using FramebufferHandleOgl = HandleOgl<GlGenFramebuffers, GlDeleteFramebuffers>;

class ScopeFramebufferBinding {
public:
    ScopeFramebufferBinding( const GpuContextOgl &gpuContext, GLuint binding );
    ~ScopeFramebufferBinding();

private:
    GLint _previousBinding;
    const GpuContextOgl &_gpuContext;
};

class FramebufferOgl : public Framebuffer {
public:
    FramebufferOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description );

    const Description& getDescription() const override;

    const FramebufferHandleOgl& getHandle() const;

private:
    Description _description;
    FramebufferHandleOgl _handle;
};

}
