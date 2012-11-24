#include "ResourceTypeOgl.h"

#include "ConstantsOgl.h"
#include "Exception.h"

namespace storm {

GLenum getResourceUsage( ResourceType resourceType ) {
    GLenum result;
    
    switch( resourceType ) {
    case ResourceTypeStatic:
        result = GL_STATIC_DRAW;
        break;
        
    case ResourceTypeDynamic:
    case ResourceTypeOutput:
        result = GL_DYNAMIC_DRAW;
        break;
        
    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
    return result;
}

}