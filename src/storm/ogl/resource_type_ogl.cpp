#include <storm/ogl/resource_type_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

GLenum getResourceUsage( ResourceType resourceType ) {
    switch( resourceType ) {
    case ResourceType::Static:
        return GL_STATIC_DRAW;
    case ResourceType::Dynamic:
    case ResourceType::Output:
        return GL_DYNAMIC_DRAW;
    default:
        storm_assert_unreachable( "Unexpected resource type value" );
        return 0;
    }
}

}
