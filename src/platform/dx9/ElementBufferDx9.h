#ifndef storm_ElementBufferDx9_h
#define storm_ElementBufferDx9_h

#include "CoreTypesDx9.h"
#include "ElementBuffer.h"

namespace storm {

class ElementBufferDx9 : public ElementBuffer {
public:
    ElementBufferDx9( const Description& );

    virtual const Description& getDescription() const noexcept;

    D3DPRIMITIVETYPE getElementTopology() const noexcept;
                UINT getElementCount() const noexcept;

private:
    static D3DPRIMITIVETYPE convertElementTopology( ElementTopology );

    Description _description;
    D3DPRIMITIVETYPE _elementTopology;
};

}

#endif