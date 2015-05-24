#include <storm/shader.h>

#include <fstream>

#include <storm/throw_exception.h>

namespace storm {

Shader::Pointer Shader::load(
    std::istream &stream, Type type, Format format )
{
    std::istreambuf_iterator<char> begin( stream );
    std::istreambuf_iterator<char> end;

    switch( format ) {
    case Format::Source:
        return Shader::create( std::string(begin, end), type );
    case Format::Binary:
        return Shader::create( std::vector<unsigned char>(begin, end), type );
    default:
        throwNotImplemented();
    }
}

Shader::Pointer Shader::load(
    const std::string &filename, Type type, Format format )
{
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throw ResourceLoadingError() << "Couldn't open " << filename;

    return Shader::load( stream, type, format );
}

}
