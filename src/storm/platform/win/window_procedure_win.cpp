#include <storm/platform/win/window_procedure_win.h>

namespace storm {

LONG_PTR convertToAddress( WNDPROC windowProcedure ) {
    return reinterpret_cast< LONG_PTR >( windowProcedure );
}

WNDPROC convertToPointer( LONG_PTR address ) {
    return reinterpret_cast< WNDPROC >( address );
}

WNDPROC replaceWindowProcedure( HWND windowHandle, WNDPROC windowProcedure ) {
    const LONG_PTR newAddress = convertToAddress( windowProcedure );
    const LONG_PTR oldAddress = ::SetWindowLongPtr( windowHandle, GWLP_WNDPROC, newAddress );
    return convertToPointer( oldAddress );
}

}