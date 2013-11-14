#include <storm/platform/ogl/output_technique_ogl.h>

namespace storm {

OutputTechniqueOgl::OutputTechniqueOgl( const Description &description )
    : _description( description )
{
    return;
}

const OutputTechnique::Description& OutputTechniqueOgl::getDescription() const noexcept {
    return _description;
}

OutputTechnique::Pointer OutputTechnique::create( const Description &description ) {
    return std::make_shared< OutputTechniqueOgl >( description );
}

}
