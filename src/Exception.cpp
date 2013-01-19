#include "Exception.h"

#if defined( _MSC_VER ) && ( _MSC_VER <= 1700 )
#   define snprintf sprintf_s
#endif

namespace storm {

template< class ExceptionType > void throwException(
    const char *fileName, long line, const char *functionName, const char *description )
{
    const size_t size = 1024;
    char information[ size ];

    ::snprintf( information, size, "%s(%ld): %s\n%s", fileName, line, functionName, description );

    throw ExceptionType( information );
}

template void throwException< std::runtime_error >(
    const char *fileName, long line, const char *functionName, const char *description );

template void throwException< std::logic_error >(
    const char *fileName, long line, const char *functionName, const char *description );

template void throwException< std::invalid_argument >(
    const char *fileName, long line, const char *functionName, const char *description );

}
