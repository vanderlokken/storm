#ifndef storm_Color_h
#define storm_Color_h

#include <cstdint>

#include "Noexcept.h"

namespace storm {

class Color {
public:
    Color() noexcept;
    Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 ) noexcept;
    Color( float normalizedR, float normalizedG, float normalizedB, float normalizedA = 1.0f ) noexcept;
    
    explicit Color( uint32_t argb ) noexcept;
    
    uint32_t get() const noexcept;
    
    unsigned char getR() const noexcept;
    unsigned char getG() const noexcept;
    unsigned char getB() const noexcept;
    unsigned char getA() const noexcept;
    
    void setR( unsigned char ) noexcept;
    void setG( unsigned char ) noexcept;
    void setB( unsigned char ) noexcept;
    void setA( unsigned char ) noexcept;
        
    float getNormalizedR() const noexcept;
    float getNormalizedG() const noexcept;
    float getNormalizedB() const noexcept;
    float getNormalizedA() const noexcept;

    void setNormalizedR( float ) noexcept;
    void setNormalizedG( float ) noexcept;
    void setNormalizedB( float ) noexcept;
    void setNormalizedA( float ) noexcept;
    
    static const Color Black;
    static const Color White;
    
private:
    static unsigned char convertNormalizedValue( float ) noexcept;
    
    uint32_t _value;
};

}

#endif