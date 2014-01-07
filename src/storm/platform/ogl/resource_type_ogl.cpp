#include <storm/platform/ogl/resource_type_ogl.h>

#include <storm/exception.h>

namespace storm {

GLenum getResourceUsage( ResourceType resourceType ) {
    switch( resourceType ) {
    case ResourceType::Static:
        return GL_STATIC_DRAW;
    case ResourceType::Dynamic:
    case ResourceType::Output:
        return GL_DYNAMIC_DRAW;
    default:
        throwInvalidArgument( "'resourceType' is invalid" );
    }
}

}