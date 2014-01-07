#include <storm/platform/dx9/output_technique_dx9.h>

namespace storm {

OutputTechniqueDx9::OutputTechniqueDx9( const Description &description ) noexcept
    : _description( description ) { }

const OutputTechnique::Description& OutputTechniqueDx9::getDescription() const noexcept {
    return _description;
}

OutputTechnique::Pointer OutputTechnique::create( const Description &description ) {
    return std::make_shared< OutputTechniqueDx9 >( description );
}

}