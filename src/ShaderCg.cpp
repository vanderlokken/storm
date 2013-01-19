#include "ShaderCg.h"

#include "Exception.h"

namespace storm {

// ----------------------------------------------------------------------------
//  ShaderCg
// ----------------------------------------------------------------------------

ShaderCg::ShaderCg( Type type, CGprofile cgProfile,
    const std::string &sourceCode, const char **compilerOptions )
        : _type( type ), _program( nullptr )
{
    _program = ::cgCreateProgram( getCgContext(), CG_SOURCE, sourceCode.c_str(),
        cgProfile, nullptr, compilerOptions );
    checkCgError( "::cgCreateProgram" );
    return;
}

ShaderCg::~ShaderCg() noexcept {
    ::cgDestroyProgram( _program );
    return;
}

Shader::Type ShaderCg::getType() const noexcept {
    return _type;
}

Shader::Uniform ShaderCg::getUniform( const std::string &identifier ) const {

    CGparameter uniform = ::cgGetNamedParameter( _program, identifier.c_str() );
    checkCgError( "::cgGetNamedParameter" );

    if( !uniform )
        throwInvalidArgument( "'identifier' is invalid" );

    return Uniform( uniform );
}

CGprogram ShaderCg::getProgram() const noexcept {
    return _program;
}

void ShaderCg::updateUniformValues() {
    ::cgUpdateProgramParameters( _program );
    checkCgError( "::cgUpdateProgramParameters" );
}

// ----------------------------------------------------------------------------
//  Shader::Uniform
// ----------------------------------------------------------------------------

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
    ::cgSetMatrixParameterfr( static_cast<CGparameter>(_identifier), matrix[0] );
    return;
}

// ----------------------------------------------------------------------------
//  Utilities
// ----------------------------------------------------------------------------

void checkCgError( const std::string &call ) {

    CGerror error;
    const char *errorString = ::cgGetLastErrorString( &error );

    if( error == CG_NO_ERROR )
        return;

    std::string description = call + " has failed.\n" + errorString;
    if( error == CG_COMPILER_ERROR ) {
        description += "\n";
        description += ::cgGetLastListing( getCgContext() );
    }
    throwRuntimeError( description.c_str() );
}

CGcontext getCgContext() {

    class ContextHandle {
        NONCOPYABLE( ContextHandle );
    public:
        ContextHandle() : value( ::cgCreateContext() ) {
            checkCgError( "::cgContext" );
        }
        ~ContextHandle() {
            ::cgDestroyContext( value );
        }
        CGcontext value;
    };

    class ContextInstance {
    public:
        ContextInstance() {
            ::cgSetParameterSettingMode(
                contextHandle.value, CG_DEFERRED_PARAMETER_SETTING );
            checkCgError( "::cgSetParameterSettingMode" );
        }
        ContextHandle contextHandle;
    };

    static const ContextInstance contextInstance;
    return contextInstance.contextHandle.value;
}

}
