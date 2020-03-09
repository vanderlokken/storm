#pragma once

#include <storm/backbuffer.h>
#include <storm/ogl/framebuffer_ogl.h>

namespace storm {

class BackbufferOgl : public Backbuffer {
public:
    void renderTexture(
        Texture::Pointer, unsigned int mipLevel, unsigned int layer ) override;

private:
    FramebufferHandleOgl _copyFramebuffer;
};

}
