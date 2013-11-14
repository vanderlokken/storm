#pragma once

#include <array>
#include <memory>

#include <storm/color.h>

namespace storm {

class Sampler {
public:
    enum MinifyingFilter {
        MinifyingFilterNearest,
        MinifyingFilterLinear,
        MinifyingFilterBilinear,
        MinifyingFilterTrilinear
    };

    enum MagnifyingFilter {
        MagnifyingFilterNearest,
        MagnifyingFilterLinear
    };

    enum WrapMode {
        WrapClamped,
        WrapRepeated,
        WrapMirrored,
        WrapWithBorderColor
    };

    struct Description {
        MinifyingFilter minifyingFilter;
        MagnifyingFilter magnifyingFilter;
        unsigned int maximalAnisotropyDegree;
        std::array<WrapMode, 3> wrapModes;
        Color borderColor;
    };

    static std::shared_ptr<Sampler> create( const Description& );

    virtual ~Sampler() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
