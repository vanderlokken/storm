#ifndef storm_Display_h
#define storm_Display_h

#include <memory>
#include <vector>

#include "Noexcept.h"

namespace storm {

class Display {
public:
    class Mode {
    public:
        Mode( unsigned int width, unsigned int height, unsigned int refreshRate, unsigned int colorDepth ) noexcept;

        unsigned int getWidth() const noexcept;
        void setWidth( unsigned int ) noexcept;

        unsigned int getHeight() const noexcept;
        void setHeight( unsigned int ) noexcept;

        unsigned int getRefreshRate() const noexcept;
        void setRefreshRate( unsigned int ) noexcept;

        unsigned int getColorDepth() const noexcept;
        void setColorDepth( unsigned int ) noexcept;

        bool operator == ( const Mode& ) const noexcept;
        bool operator != ( const Mode& ) const noexcept;

    private:
        int _width;
        int _height;
        int _refreshRate;
        int _colorDepth;
    };

    static std::shared_ptr<Display> getInstance();

    virtual ~Display() noexcept { }

    virtual std::vector<Mode> getSupportedModes() const noexcept = 0;

    virtual const Mode& getCurrentMode() const noexcept = 0;
    virtual void setCurrentMode( const Mode& ) = 0;
};

}

#endif