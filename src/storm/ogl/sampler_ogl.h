#pragma once

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/sampler.h>

namespace storm {

using SamplerHandleOgl = HandleOgl<GlGenSamplers, GlDeleteSamplers>;

class SamplerOgl : public Sampler {
public:
    SamplerOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description );

    const Description& getDescription() const override;

    const SamplerHandleOgl& getHandle() const;

protected:
    static GLenum convertMinifyingFilter( MinifyingFilter );
    static GLenum convertMagnifyingFilter( MagnifyingFilter );
    static GLenum convertWrapMode( WrapMode );

    Description _description;
    SamplerHandleOgl _handle;
};

}
