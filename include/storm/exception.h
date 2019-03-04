#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <type_traits>

namespace storm {

class Exception : public std::exception {
public:
    Exception() = default;
    Exception(
        const char *fileName, long line, const char *functionName,
        const std::string &description );

    explicit Exception( const std::string &description );

    void appendMessage( std::string_view message ) {
        _message += message;
    }

    virtual const char* what() const noexcept( true );

private:
    std::string _message;
};

class SystemRequirementsNotMet : public Exception {};
class ResourceLoadingError : public Exception {};

// Usage example:
//     throw ResourceLoadingError() << "Couldn't load file";
template<class ExceptionType>
typename std::enable_if<
        std::is_base_of<Exception, ExceptionType>::value, ExceptionType>::type
    operator << ( ExceptionType exception, std::string_view message )
{
    exception.appendMessage( message );
    return std::move( exception );
}

}
