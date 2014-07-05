#pragma once

#include <storm/backbuffer.h>
#include <storm/platform/ogl/rendering_buffer_set_ogl.h>

namespace storm {

class BackbufferOgl : public Backbuffer {
public:
    virtual void renderTexture(
        Texture::Pointer, unsigned int mipLevel, unsigned int layer );

private:
    FramebufferHandleOgl _copyFramebuffer;
};

}
