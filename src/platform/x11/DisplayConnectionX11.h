#ifndef storm_DisplayConnectionX11_h
#define storm_DisplayConnectionX11_h

#include <memory>

#include <X11/Xlib.h>

namespace storm {

class DisplayConnectionX11 {
public:
    static std::shared_ptr<DisplayConnectionX11> getInstance();
    
    ~DisplayConnectionX11() noexcept;
    
    Display* getHandle() const noexcept;
    
private:
    DisplayConnectionX11();
    
    Display *_handle;
};

}

#endif