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

const char* Exception::what() const {
    return _message.c_str();
}

}
