#pragma once

#include <storm/platform/ogl/core_types_ogl.h>
#include <storm/sampler.h>

namespace storm {

class SamplerOgl : public Sampler {
public:
    SamplerOgl( const Description& );

    virtual const Description& getDescription() const noexcept;

private:
    static GLenum convertMinifyingFilter( MinifyingFilter );
    static GLenum convertMagnifyingFilter( MagnifyingFilter );
    static GLenum convertWrapMode( WrapMode );

    Description _description;
    GLenum _minifyingFilter;
    GLenum _magnifyingFilter;
    std::array<GLenum, 3> _wrapModes;
    GLuint _borderColor;
};

}
