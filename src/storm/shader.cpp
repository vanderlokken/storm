#include <storm/shader.h>

#include <fstream>

#include <storm/exception.h>

namespace storm {

Shader::Pointer Shader::load(
    std::istream &stream, Shader::Type shaderType )
{
    std::istreambuf_iterator<char> begin( stream );
    std::istreambuf_iterator<char> end;

    return Shader::create( std::string(begin, end), shaderType );
}

Shader::Pointer Shader::load(
    const std::string &filename, Shader::Type shaderType )
{
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throw ResourceLoadingError() << "Couldn't open " << filename;

    return Shader::load( stream, shaderType );
}

}
