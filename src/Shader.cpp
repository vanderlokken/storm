#include "Shader.h"

#include <fstream>

#include "Exception.h"
#include "Shader.h"

namespace storm {

std::shared_ptr<Shader> Shader::load(
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
