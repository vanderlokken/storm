#pragma once

#include <storm/platform/ogl/api_ogl.h>

// Replacement functions for the 'ARB_texture_storage' and
// 'ARB_texture_storage_multisample' extensions.

namespace storm {

void glTexStorage1D( GLenum target, GLsizei levels, GLenum internalFormat,
    GLsizei width );

void glTexStorage2D( GLenum target, GLsizei levels, GLenum internalFormat,
    GLsizei width, GLsizei height );

void glTexStorage3D( GLenum target, GLsizei levels, GLenum internalFormat,
    GLsizei width, GLsizei height, GLsizei depth );

void glTexStorage2DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLboolean fixedSampleLocations );

void glTexStorage3DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLboolean fixedSampleLocations );

}
