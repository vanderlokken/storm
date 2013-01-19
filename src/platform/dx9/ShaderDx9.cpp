#include "ShaderDx9.h"

#include <Cg/cgD3D9.h>

#include "platform/win/CheckResult.h"

namespace storm {

ShaderDx9::ShaderDx9( const std::string &sourceCode, Type type )
    : _program( nullptr )
{
    static CGcontext context = ::cgCreateContext();

    _program = cgCreateProgram(
        context, CG_SOURCE, sourceCode.c_str(), selectProfile(type), nullptr, nullptr );

    const CGerror error = ::cgGetError();
    if( error )
        throwRuntimeError( ::cgGetErrorString(error) );

    const HRESULT loaded = ::cgD3D9LoadProgram( _program, CG_TRUE, 0 );
    checkResult( loaded, "::cgD3D9LoadProgram" );

    return;
}

ShaderDx9::~ShaderDx9() noexcept {
    ::cgD3D9UnloadProgram( _program );
    ::cgDestroyProgram( _program );
    return;
}

Shader::Uniform ShaderDx9::getUniform( const std::string &identifier ) const {

    CGparameter uniform = ::cgGetNamedParameter( _program, identifier.c_str() );

    if( !uniform )
        throwInvalidArgument( "'identifier' is invalid" );

    return Uniform( uniform );

}

CGprogram ShaderDx9::getProgram() const noexcept {
    return _program;
}

CGprofile ShaderDx9::selectProfile( Type type ) {
    CGprofile result;

    switch( type ) {
    case TypeVertex:
        result = ::cgD3D9GetLatestVertexProfile();
        break;

    case TypePixel:
        result = ::cgD3D9GetLatestPixelProfile();
        break;

    default:
        throwInvalidArgument( "'type' is invalid" );
    }

    return result;
}

std::shared_ptr< Shader > Shader::create( const std::string &sourceCode, Type type ) {
    return std::make_shared< ShaderDx9 >( sourceCode, type );
}

}