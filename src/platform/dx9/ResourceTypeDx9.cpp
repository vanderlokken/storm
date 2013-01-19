#include "ResourceTypeDx9.h"

#include "Exception.h"

namespace storm {

DWORD selectResourceUsage( ResourceType resourceType ) {
    DWORD result;

    switch( resourceType ) {
    case ResourceTypeStatic:
        result = 0;
        break;

    case ResourceTypeDynamic:
        result = D3DUSAGE_DYNAMIC;
        break;

    case ResourceTypeOutput:
        result = D3DUSAGE_DYNAMIC | D3DUSAGE_RENDERTARGET;
        break;

    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
    return result;
}

D3DPOOL selectResourcePool( ResourceType resourceType ) {
    D3DPOOL result;

    switch( resourceType ) {
    case ResourceTypeStatic:
        result = D3DPOOL_MANAGED;
        break;

    case ResourceTypeDynamic:
    case ResourceTypeOutput:
        result = D3DPOOL_DEFAULT;
        break;

    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
    return result;
}

}