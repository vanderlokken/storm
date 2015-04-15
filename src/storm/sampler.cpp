#include <storm/sampler.h>

namespace storm {

Sampler::Pointer Sampler::getDefault() {
    Description description;
    description.minifyingFilter = MinifyingFilter::Bilinear;
    description.magnifyingFilter = MagnifyingFilter::Linear;
    description.maximalAnisotropyDegree = 1;
    description.wrapModes = {
        WrapMode::Clamped, WrapMode::Clamped, WrapMode::Clamped };
    description.borderColor = Color::Black;

    static const Sampler::Pointer sampler = create( description );
    return sampler;
}

Sampler::Pointer Sampler::getDefaultWithTiling() {
    Description description = getDefault()->getDescription();
    description.wrapModes = {
        WrapMode::Repeated, WrapMode::Repeated, WrapMode::Repeated };

    static const Sampler::Pointer sampler = create( description );
    return sampler;
}

Sampler::Pointer Sampler::getDefaultWithNearestFilters() {
    Description description = getDefault()->getDescription();
    description.minifyingFilter = MinifyingFilter::Nearest;
    description.magnifyingFilter = MagnifyingFilter::Nearest;

    static const Sampler::Pointer sampler = create( description );
    return sampler;
}

}
