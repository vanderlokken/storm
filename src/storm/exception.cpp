#include <storm/exception.h>

#include <sstream>

namespace storm {

Exception::Exception(
    const char *fileName, long line, const char *functionName,
    std::string_view description )
{
    std::stringstream messageStream;

    messageStream << fileName << "(" << line << "): " << functionName <<
        std::endl << description;

    _message = messageStream.str();
}

Exception::Exception( std::string_view description ) :
    _message( description )
{
}

const char* Exception::what() const noexcept( true ) {
    return _message.c_str();
}

}
