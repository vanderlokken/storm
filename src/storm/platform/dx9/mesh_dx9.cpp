#include <storm/platform/dx9/mesh_dx9.h>

#include <storm/exception.h>
#include <storm/index_buffer.h>

namespace storm {

MeshDx9::MeshDx9( const Description &description )
    : _description( description ),
      _triangleTopology( convertTriangleTopology(description.triangleTopology) )
{
    return;
}

const Mesh::Description& MeshDx9::getDescription() const noexcept {
    return _description;
}

D3DPRIMITIVETYPE MeshDx9::getTriangleTopology() const noexcept {
    return _triangleTopology;
}

UINT MeshDx9::getTriangleCount() const noexcept {
    UINT result = 0;

    const auto &indexBufferDescription = _description.indexBuffer->getDescription();
    const size_t indexCount = indexBufferDescription.bufferSize / indexBufferDescription.indexSize;

    switch( _triangleTopology ) {
    case D3DPT_TRIANGLELIST:
        result = indexCount / 3;
        break;

    case D3DPT_TRIANGLESTRIP:
        result = indexCount - 2;
        break;
    }
    return result;
}

D3DPRIMITIVETYPE MeshDx9::convertTriangleTopology( TriangleTopology triangleTopology ) {
    D3DPRIMITIVETYPE result;

    switch( triangleTopology ) {
    case TriangleTopologyList:
        result = D3DPT_TRIANGLELIST;
        break;

    case TriangleTopologyStrip:
        result = D3DPT_TRIANGLESTRIP;
        break;

    default:
        throwInvalidArgument( "'triangleTopology' is invalid" );
    }
    return result;
}

std::shared_ptr< Mesh > Mesh::create( const Description &description ) {
    return std::make_shared< MeshDx9 >( description );
}

}
