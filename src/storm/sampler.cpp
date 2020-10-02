#include <storm/sampler.h>

namespace storm {

SamplerBuilder::SamplerBuilder() {
    _description.minifyingFilter = Sampler::MinifyingFilter::Bilinear;
    _description.magnifyingFilter = Sampler::MagnifyingFilter::Linear;
    _description.maximalAnisotropyDegree = 1;
    _description.wrapModes = {
        Sampler::WrapMode::Clamped,
        Sampler::WrapMode::Clamped,
        Sampler::WrapMode::Clamped
    };
    _description.borderColor = Color::Black;
}

SamplerBuilder& SamplerBuilder::useTiling() {
    _description.wrapModes = {
        Sampler::WrapMode::Repeated,
        Sampler::WrapMode::Repeated,
        Sampler::WrapMode::Repeated
    };
    return *this;
}

SamplerBuilder& SamplerBuilder::useMirroring() {
    _description.wrapModes = {
        Sampler::WrapMode::Mirrored,
        Sampler::WrapMode::Mirrored,
        Sampler::WrapMode::Mirrored
    };
    return *this;
}

SamplerBuilder& SamplerBuilder::useNearestNeighbourFilters() {
    _description.minifyingFilter = Sampler::MinifyingFilter::Nearest;
    _description.magnifyingFilter = Sampler::MagnifyingFilter::Nearest;
    return *this;
}

SamplerBuilder& SamplerBuilder::useTrilinearFilter() {
    _description.minifyingFilter = Sampler::MinifyingFilter::Trilinear;
    return *this;
}

Sampler::Pointer SamplerBuilder::build( GpuContext::Pointer gpuContext ) const {
    return Sampler::create( gpuContext, _description );
}

const Sampler::Description& SamplerBuilder::getSamplerDescription() const {
    return _description;
}

}
