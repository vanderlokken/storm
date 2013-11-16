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
    const auto &indexBufferDescription = _description.indexBuffer->getDescription();
    const size_t indexCount = indexBufferDescription.bufferSize / indexBufferDescription.indexSize;

    switch( _triangleTopology ) {
    case D3DPT_TRIANGLELIST:
        return indexCount / 3;
    case D3DPT_TRIANGLESTRIP:
        return indexCount - 2;
    default:
        throwNotImplemented();
    }
}

D3DPRIMITIVETYPE MeshDx9::convertTriangleTopology( TriangleTopology triangleTopology ) {
    switch( triangleTopology ) {
    case TriangleTopology::List:
        return D3DPT_TRIANGLELIST;
    case TriangleTopology::Strip:
        return D3DPT_TRIANGLESTRIP;
    default:
        throwInvalidArgument( "'triangleTopology' is invalid" );
    }
}

Mesh::Pointer Mesh::create( const Description &description ) {
    return std::make_shared< MeshDx9 >( description );
}

}
