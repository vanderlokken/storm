#include "ShaderOgl.h"

#include "Exception.h"
#include "FunctionsOgl.h"

#include <Cg/cgGL.h>

namespace storm {

ShaderOgl::ShaderOgl( const std::string &sourceCode, Type type )
    : _program( nullptr )
{
    static CGcontext context = ::cgCreateContext();

    const CGprofile profile = selectProfile( type );
    ::cgGLSetContextOptimalOptions( context, profile );
    
    _program = cgCreateProgram(
        context, CG_SOURCE, sourceCode.c_str(), profile, nullptr, nullptr );

    const CGerror error = ::cgGetError();
    if( error )
        throwRuntimeError( ::cgGetErrorString(error) );
    
    ::cgGLLoadProgram( _program );

    return;
}

ShaderOgl::~ShaderOgl() noexcept {
    ::cgDestroyProgram( _program );
    return;
}

Shader::Uniform ShaderOgl::getUniform( const std::string &identifier ) const {

    CGparameter uniform = ::cgGetNamedParameter( _program, identifier.c_str() );
    
    if( !uniform )
        throwInvalidArgument( "'identifier' is invalid" );
    
    return Uniform( uniform );
    
}

CGprogram ShaderOgl::getProgram() const noexcept {
    return _program;
}

CGprofile ShaderOgl::selectProfile( Type type ) {
    CGprofile result;
    
    switch( type ) {
    case TypeVertex:
        result = ::cgGLGetLatestProfile( CG_GL_VERTEX );
        break;
        
    case TypePixel:
        result = ::cgGLGetLatestProfile( CG_GL_FRAGMENT );
        break;
        
    default:
        throwInvalidArgument( "'type' is invalid" );
    }
    
    return result;
}


std::shared_ptr< Shader > Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderOgl >( sourceCode, type );
}

}
