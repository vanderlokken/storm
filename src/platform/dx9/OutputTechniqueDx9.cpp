#include "OutputTechniqueDx9.h"

namespace storm {

OutputTechniqueDx9::OutputTechniqueDx9( const Description &description ) noexcept
    : _description( description ) { }

const OutputTechnique::Description& OutputTechniqueDx9::getDescription() const noexcept {
    return _description;
}

std::shared_ptr<OutputTechnique> OutputTechnique::create( const Description &description ) {
    return std::make_shared< OutputTechniqueDx9 >( description );
}

}