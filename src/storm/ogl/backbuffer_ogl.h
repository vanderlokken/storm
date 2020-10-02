#pragma once

#include <storm/backbuffer.h>
#include <storm/ogl/framebuffer_ogl.h>
#include <storm/ogl/gpu_context_ogl.h>

namespace storm {

class BackbufferOgl : public Backbuffer {
public:
    explicit BackbufferOgl( GpuContextOgl::Pointer gpuContext );

    void renderTexture(
        Texture::Pointer, unsigned int mipLevel, unsigned int layer ) override;

private:
    FramebufferHandleOgl _copyFramebuffer;
};

}
