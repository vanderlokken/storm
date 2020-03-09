#pragma once

#include <storm/ogl/api_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/sampler.h>

namespace storm {

class SamplerHandleOgl : public HandleOgl {
public:
    SamplerHandleOgl();
    ~SamplerHandleOgl();
};

class SamplerOgl : public Sampler {
public:
    SamplerOgl( const Description& );

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
