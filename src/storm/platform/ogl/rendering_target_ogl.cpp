#include <storm/platform/ogl/rendering_target_ogl.h>

namespace storm {

RenderingTargetOgl::RenderingTargetOgl( const Description &description )
    : _description( description )
{
}

const RenderingTarget::Description&
    RenderingTargetOgl::getDescription() const noexcept
{
    return _description;
}

RenderingTarget::Pointer RenderingTarget::create(
    const Description &description )
{
    return std::make_shared< RenderingTargetOgl >( description );
}

}
