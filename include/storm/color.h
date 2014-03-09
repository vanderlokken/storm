#pragma once

#include <cstdint>

namespace storm {

class Color {
public:
    Color();

    Color(
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned char a = 255 );

    explicit Color( uint32_t argb );

    uint32_t get() const;

    unsigned char getR() const;
    unsigned char getG() const;
    unsigned char getB() const;
    unsigned char getA() const;

    void setR( unsigned char );
    void setG( unsigned char );
    void setB( unsigned char );
    void setA( unsigned char );

    float getNormalizedR() const;
    float getNormalizedG() const;
    float getNormalizedB() const;
    float getNormalizedA() const;

    void setNormalizedR( float );
    void setNormalizedG( float );
    void setNormalizedB( float );
    void setNormalizedA( float );

    static Color fromNormalized(
        float normalizedR,
        float normalizedG,
        float normalizedB,
        float normalizedA = 1.0f );

    static const Color Black;
    static const Color White;

private:
    static unsigned char convertNormalizedValue( float );

    uint32_t _value;
};

}
