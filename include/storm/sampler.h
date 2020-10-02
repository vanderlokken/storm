#pragma once

#include <array>
#include <memory>
#include <optional>

#include <storm/color.h>
#include <storm/condition.h>
#include <storm/gpu_context.h>

namespace storm {

class Sampler {
public:
    using Pointer = std::shared_ptr<Sampler>;

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

    static Sampler::Pointer create(
        GpuContext::Pointer gpuContext, const Description &description );

    virtual ~Sampler() = default;

    virtual const Description& getDescription() const = 0;
};

class SamplerBuilder {
public:
    SamplerBuilder();

    SamplerBuilder& useTiling();
    SamplerBuilder& useMirroring();

    SamplerBuilder& useNearestNeighbourFilters();
    SamplerBuilder& useTrilinearFilter();

    Sampler::Pointer build( GpuContext::Pointer gpuContext ) const;

    const Sampler::Description& getSamplerDescription() const;

private:
    Sampler::Description _description = {};
};

}
