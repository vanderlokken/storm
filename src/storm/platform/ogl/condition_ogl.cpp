#include <storm/platform/ogl/condition_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

GLenum convertCondition( Condition condition ) {
    switch( condition ) {
    case Condition::False:
        return GL_NEVER;
    case Condition::True:
        return GL_ALWAYS;
    case Condition::Less:
        return GL_LESS;
    case Condition::LessOrEqual:
        return GL_LEQUAL;
    case Condition::Greater:
        return GL_GREATER;
    case Condition::GreaterOrEqual:
        return GL_GEQUAL;
    case Condition::Equal:
        return GL_EQUAL;
    case Condition::NotEqual:
        return GL_NOTEQUAL;
    default:
        storm_assert_unreachable( "Unexpected condition value" );
        return 0;
    }
}

}
