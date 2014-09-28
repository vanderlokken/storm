#pragma once

#include <storm/platform/ogl/api_ogl.h>

// Replacement functions for the 'ARB_texture_storage' and
// 'ARB_texture_storage_multisample' extensions.

namespace storm {

void APIENTRY glTexStorage1D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width );

void APIENTRY glTexStorage2D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width, GLsizei height );

void APIENTRY glTexStorage3D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth );

void APIENTRY glTexStorage2DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLboolean fixedSampleLocations );

void APIENTRY glTexStorage3DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLboolean fixedSampleLocations );

}
