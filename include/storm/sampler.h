#pragma once

#include <array>
#include <memory>
#include <optional>

#include <storm/color.h>
#include <storm/condition.h>

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

        unsigned maximalAnisotropyDegree;

        std::array<WrapMode, 3> wrapModes;
        Color borderColor;

        std::optional<Condition> comparisonCondition;
    };

    static Sampler::Pointer create( const Description& );
    static Sampler::Pointer getDefault();
    static Sampler::Pointer getDefaultWithTiling();
    static Sampler::Pointer getDefaultWithMirroring();
    static Sampler::Pointer getDefaultWithNearestFilters();

    virtual ~Sampler() = default;

    virtual const Description& getDescription() const = 0;
};

}
