#include "Exception.h"

#if defined( _MSC_VER ) && ( _MSC_VER <= 1700 )
#   define snprintf sprintf_s
#endif

namespace storm {

const char* formatExceptionMessage(
    const char *fileName, long line, const char *functionName, const char *description )
{
    const size_t size = 1024;
    static char message[ size ];

    ::snprintf( message, size, "%s(%ld): %s\n%s", fileName, line, functionName, description );

    return message;
}

}
