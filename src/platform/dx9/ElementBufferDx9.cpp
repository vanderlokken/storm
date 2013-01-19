#include "ElementBufferDx9.h"

#include "Exception.h"
#include "IndexBuffer.h"

namespace storm {

ElementBufferDx9::ElementBufferDx9( const Description &description )
    : _description( description ),
      _elementTopology( convertElementTopology(description.elementTopology) )
{
    return;
}

const ElementBuffer::Description& ElementBufferDx9::getDescription() const noexcept {
    return _description;
}

D3DPRIMITIVETYPE ElementBufferDx9::getElementTopology() const noexcept {
    return _elementTopology;
}

UINT ElementBufferDx9::getElementCount() const noexcept {
    UINT result = 0;

    const auto &indexBufferDescription = _description.indexBuffer->getDescription();
    const size_t indexCount = indexBufferDescription.bufferSize / indexBufferDescription.indexSize;

    switch( _elementTopology ) {
    case D3DPT_TRIANGLELIST:
        result = indexCount / 3;
        break;

    case D3DPT_TRIANGLESTRIP:
        result = indexCount - 2;
        break;
    }
    return result;
}

D3DPRIMITIVETYPE ElementBufferDx9::convertElementTopology( ElementTopology elementTopology ) {
    D3DPRIMITIVETYPE result;

    switch( elementTopology ) {
    case ElementTopologyList:
        result = D3DPT_TRIANGLELIST;
        break;

    case ElementTopologyStrip:
        result = D3DPT_TRIANGLESTRIP;
        break;

    default:
        throwInvalidArgument( "'elementTopology' is invalid" );
    }
    return result;
}

std::shared_ptr< ElementBuffer > ElementBuffer::create( const Description &description ) {
    return std::make_shared< ElementBufferDx9 >( description );
}

}