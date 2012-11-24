#include "WindowProcedureWin.h"

namespace storm {

LONG_PTR convertToAddress( WNDPROC windowProcedure ) noexcept {
    return reinterpret_cast< LONG_PTR >( windowProcedure );
}

WNDPROC convertToPointer( LONG_PTR address ) noexcept {
    return reinterpret_cast< WNDPROC >( address );
}

WNDPROC replaceWindowProcedure( HWND windowHandle, WNDPROC windowProcedure ) noexcept {
    const LONG_PTR newAddress = convertToAddress( windowProcedure );
    const LONG_PTR oldAddress = ::SetWindowLongPtr( windowHandle, GWLP_WNDPROC, newAddress );
    return convertToPointer( oldAddress );
}

}