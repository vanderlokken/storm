#include <storm/shader.h>

#include <cstdint>
#include <fstream>
#include <sstream>

#include <storm/throw_exception.h>

namespace storm {

Shader::Pointer Shader::load(
    std::istream &stream, Type type, Format format )
{
    std::ostringstream bufferStream;

    if( !(bufferStream << stream.rdbuf()) )
        throw ResourceLoadingError() << "Couldn't read shader";

    const std::string buffer = bufferStream.str();

    switch( format ) {
    case Format::Source:
        return Shader::create( buffer, type );
    case Format::Binary:
        return Shader::create(
            std::vector<uint8_t>(
                reinterpret_cast<const uint8_t*>(buffer.data()),
                reinterpret_cast<const uint8_t*>(buffer.data()) + buffer.size()
            ), type );
    default:
        throwNotImplemented();
    }
}

Shader::Pointer Shader::load(
    std::string_view filename, Type type, Format format )
{
    std::ifstream stream( filename.data(), std::ios::in | std::ios::binary );

    if( !stream ) {
        throw ResourceLoadingError() << "Couldn't open " << filename;
    }

    return Shader::load( stream, type, format );
}

}
