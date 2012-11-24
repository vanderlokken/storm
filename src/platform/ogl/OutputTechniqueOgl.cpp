#include "OutputTechniqueOgl.h"

namespace storm {

OutputTechniqueOgl::OutputTechniqueOgl( const Description &description )
    : _description( description )
{
    return;
}

const OutputTechnique::Description& OutputTechniqueOgl::getDescription() const noexcept {
    return _description;
}

std::shared_ptr<OutputTechnique> OutputTechnique::create( const Description &description ) {
    return std::make_shared< OutputTechniqueOgl >( description );
}

}
