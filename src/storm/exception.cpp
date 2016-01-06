#include <storm/exception.h>

#include <sstream>

namespace storm {

Exception::Exception(
    const char *fileName, long line, const char *functionName,
    const std::string &description )
{
    std::stringstream messageStream;

    messageStream << fileName << "(" << line << "): " << functionName <<
        std::endl << description;

    _message = messageStream.str();
}

Exception::Exception( const std::string &description )
    : _message( description )
{
}

#ifndef _MSC_VER
    const char* Exception::what() const noexcept( true ) {
        return _message.c_str();
    }
#else
    const char* Exception::what() const {
        return _message.c_str();
    }
#endif

}
