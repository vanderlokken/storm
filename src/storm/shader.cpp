#include <storm/shader.h>

#include <fstream>

#include <storm/throw_exception.h>

namespace storm {

Shader::Pointer Shader::load(
    const std::string &filename, Shader::Type shaderType )
{
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throwInvalidArgument( "'stream' is invalid" );

    std::istreambuf_iterator< char > begin( stream );
    std::istreambuf_iterator< char > end;

    return Shader::create( std::string(begin, end), shaderType );
}

}
