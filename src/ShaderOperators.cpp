#include "ShaderOperators.h"

#include "Exception.h"
#include "Shader.h"

namespace storm {

std::shared_ptr< Shader > readShader( std::istream &stream, Shader::Type shaderType ) {

    if( !stream )
        throwInvalidArgument( "'stream' is invalid" );

    std::istreambuf_iterator< char > begin( stream );
    std::istreambuf_iterator< char > end;

    return Shader::create( std::string(begin, end), shaderType );
}

}