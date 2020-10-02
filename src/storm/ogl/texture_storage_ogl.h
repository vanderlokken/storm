#pragma once

#include <storm/ogl/gpu_context_ogl.h>

// The following functions handle cases when the 'ARB_texture_storage' and
// 'ARB_texture_storage_multisample' extensions are not available. When these
// extensions are available these functions act as a proxy.

namespace storm {

void glTexStorage1D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width );

void glTexStorage2D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height );

void glTexStorage3D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth );

void glTexStorage2DMultisample(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLboolean fixedSampleLocations );

void glTexStorage3DMultisample(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLboolean fixedSampleLocations );

}
