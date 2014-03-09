#pragma once

#include <storm/noncopyable.h>
#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/ogl/handle_ogl.h>
#include <storm/sampler.h>

namespace storm {

class SamplerHandleOgl : public HandleOgl {
public:
    SamplerHandleOgl();
    ~SamplerHandleOgl();
};

class SamplerOgl : public Sampler {
    NONCOPYABLE( SamplerOgl );
public:
    SamplerOgl( const Description& );

    virtual const Description& getDescription() const;

    const SamplerHandleOgl& getHandle() const;

protected:
    static GLenum convertMinifyingFilter( MinifyingFilter );
    static GLenum convertMagnifyingFilter( MagnifyingFilter );
    static GLenum convertWrapMode( WrapMode );

    Description _description;
    SamplerHandleOgl _handle;
};

}
