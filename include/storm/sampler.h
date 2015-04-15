#pragma once

#include <array>
#include <memory>

#include <storm/color.h>

namespace storm {

class Sampler {
public:
    typedef std::shared_ptr<Sampler> Pointer;

    enum class MinifyingFilter {
        Nearest,
        Linear,
        Bilinear,
        Trilinear
    };

    enum class MagnifyingFilter {
        Nearest,
        Linear
    };

    enum class WrapMode {
        Clamped,
        Repeated,
        Mirrored,
        WithBorderColor
    };

    struct Description {
        MinifyingFilter minifyingFilter;
        MagnifyingFilter magnifyingFilter;
        unsigned int maximalAnisotropyDegree;
        std::array<WrapMode, 3> wrapModes;
        Color borderColor;
    };

    static Sampler::Pointer create( const Description& );
    static Sampler::Pointer getDefault();
    static Sampler::Pointer getDefaultWithTiling();
    static Sampler::Pointer getDefaultWithNearestFilters();

    virtual ~Sampler() { }

    virtual const Description& getDescription() const = 0;
};

}
