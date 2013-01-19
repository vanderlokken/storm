#ifndef storm_ElementBufferOperators_h
#define storm_ElementBufferOperators_h

#include <istream>
#include <memory>

namespace storm {

class ElementBuffer;

std::istream& operator >> (
    std::istream &stream, std::shared_ptr<ElementBuffer> &result );

}

#endif