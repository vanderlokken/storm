#include "ShaderCg.h"

#include "Exception.h"

namespace storm {

// ----------------------------------------------------------------------------
//  CGContextInstance
// ----------------------------------------------------------------------------

CGContextInstance::CGContextInstance()
    : _handle( ::cgCreateContext(), [](CGcontext context) {
        ::cgDestroyContext( context );
    })
{
    checkCgError( "::cgCreateContext" );
    ::cgSetParameterSettingMode( *this, CG_DEFERRED_PARAMETER_SETTING );
    checkCgError( "::cgSetParameterSettingMode" );
}

CGContextInstance::operator CGcontext () const {
    return _handle.get();
}

CGContextInstance CGContextInstance::getInstance() {
    static const CGContextInstance instance;
    return instance;
}

// ----------------------------------------------------------------------------
//  ShaderCg
// ----------------------------------------------------------------------------

ShaderCg::ShaderCg( CompilerArguments compilerArguments, Type type )
    : _type( type ),
      _program( nullptr ),
      _context( CGContextInstance::getInstance() )
{
    _program = ::cgCreateProgram(
        _context, CG_SOURCE,
        compilerArguments.sourceCode,
        compilerArguments.profile,
        nullptr,
        compilerArguments.compilerOptions );
    checkCgError( "::cgCreateProgram" );
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

void Shader::Uniform::setValue( int value ) {
    ::cgSetParameter1i( static_cast<CGparameter>(_identifier), value );
    return;
}

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

void Shader::Uniform::setValue( const std::vector<Matrix> &matrices ) {
    ::cgSetParameterValuefr(
        static_cast<CGparameter>(_identifier), matrices.size() * 4 * 4,
        reinterpret_cast<const float*>(matrices.data()) );
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
        description += ::cgGetLastListing( CGContextInstance::getInstance() );
    }
    throwRuntimeError( description.c_str() );
}

}
