#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/keyboard_common.h>

namespace storm {

class KeyboardWin : public KeyboardCommon {
public:
    static KeyboardWin* getInstance();

    virtual ~KeyboardWin();

private:
    KeyboardWin();

    void onEvent( const RAWKEYBOARD& );

    WNDPROC _originalWindowProcedure;

    static LRESULT CALLBACK handleMessage( HWND, UINT, WPARAM, LPARAM );

    LRESULT handleInputMessage( WPARAM, LPARAM );
    LRESULT handleCharacterInputMessage( WPARAM, LPARAM );
    LRESULT handleActivationMessage( WPARAM, LPARAM );
};

}
