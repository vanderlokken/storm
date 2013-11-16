#include <storm/platform/dx9/resource_type_dx9.h>

#include <storm/exception.h>

namespace storm {

DWORD selectResourceUsage( ResourceType resourceType ) {
    switch( resourceType ) {
    case ResourceType::Static:
        return 0;
    case ResourceType::Dynamic:
        return D3DUSAGE_DYNAMIC;
    case ResourceType::Output:
        return D3DUSAGE_DYNAMIC | D3DUSAGE_RENDERTARGET;
    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
}

D3DPOOL selectResourcePool( ResourceType resourceType ) {
    switch( resourceType ) {
    case ResourceType::Static:
        return D3DPOOL_MANAGED;
    case ResourceType::Dynamic:
    case ResourceType::Output:
        return D3DPOOL_DEFAULT;
    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
}

}