#pragma once

#include <cstdint>

namespace storm {

struct Color {
    Color();
    Color(
        float r,
        float g,
        float b,
        float a = 1.0f );

    static const Color Black;
    static const Color White;

    float r;
    float g;
    float b;
    float a;
};

class CompressedColor {
public:
    CompressedColor();
    CompressedColor(
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned char a = 255 );
    explicit CompressedColor( Color );
    explicit CompressedColor( uint32_t );

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

    static const CompressedColor Black;
    static const CompressedColor White;

    operator Color() const;

    uint32_t value;
};

}

#include <storm/color.inl>
