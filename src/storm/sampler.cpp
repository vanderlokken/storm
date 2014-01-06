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

}
