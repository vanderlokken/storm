#include "Shader.h"

#include <Cg/cg.h>

namespace storm {

Shader::Uniform::Uniform( void *identifier ) : _identifier(identifier) {}

void Shader::Uniform::setValue( float value ) {
    ::cgSetParameter1f( static_cast<CGparameter>(_identifier), value );
    return;
}

void Shader::Uniform::setValue( const Color &color ) {
    ::cgSetParameter4f( static_cast<CGparameter>(_identifier),
        color.getNormalizedR(),
        color.getNormalizedG(),
        color.getNormalizedB(),
        color.getNormalizedA() );
    return;
}

void Shader::Uniform::setValue( const Vector &vector ) {
    ::cgSetParameter3f( static_cast<CGparameter>(_identifier),
        vector.getX(),
        vector.getY(),
        vector.getZ() );
    return;
}

void Shader::Uniform::setValue( const Matrix &matrix ) {
    ::cgSetParameterValuefr( static_cast<CGparameter>(_identifier), 16, matrix[0] );
    return;
}

}