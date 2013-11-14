#include <storm/platform/ogl/resource_type_ogl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/constants_ogl.h>

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