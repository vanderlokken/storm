#include <storm/color.h>

namespace storm {

Color::Color()
    : _value( 0xFF000000 ) { }

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
    : _value( (a << 24) | (r << 16) | (g << 8) | (b << 0) ) { }

Color::Color( uint32_t argb )
    : _value( argb ) { }

uint32_t Color::get() const {
    return _value;
}

unsigned char Color::getR() const {
    return static_cast< unsigned char >( _value >> 16 );
}

unsigned char Color::getG() const {
    return static_cast< unsigned char >( _value >> 8 );
}

unsigned char Color::getB() const {
    return static_cast< unsigned char >( _value >> 0 );
}

unsigned char Color::getA() const {
    return static_cast< unsigned char >( _value >> 24 );
}

void Color::setR( unsigned char r ) {
    _value = (_value & 0xFF00FFFF) | (static_cast<uint32_t>(r) << 16);
    return;
}

void Color::setG( unsigned char g ) {
    _value = (_value & 0xFFFF00FF) | (static_cast<uint32_t>(g) << 8);
    return;
}

void Color::setB( unsigned char b ) {
    _value = (_value & 0xFFFFFF00) | (static_cast<uint32_t>(b) << 0);
    return;
}

void Color::setA( unsigned char a ) {
    _value = (_value & 0x00FFFFFF) | (static_cast<uint32_t>(a) << 24);
    return;
}

float Color::getNormalizedR() const {
    return getR() / 255.0f;
}

float Color::getNormalizedG() const {
    return getG() / 255.0f;
}

float Color::getNormalizedB() const {
    return getB() / 255.0f;
}

float Color::getNormalizedA() const {
    return getA() / 255.0f;
}

void Color::setNormalizedR( float normalizedR ) {
    setR( convertNormalizedValue(normalizedR) );
    return;
}

void Color::setNormalizedG( float normalizedG ) {
    setG( convertNormalizedValue(normalizedG) );
    return;
}

void Color::setNormalizedB( float normalizedB ) {
    setB( convertNormalizedValue(normalizedB) );
    return;
}

void Color::setNormalizedA( float normalizedA ) {
    setA( convertNormalizedValue(normalizedA) );
    return;
}

Color Color::fromNormalized(
    float normalizedR,
    float normalizedG,
    float normalizedB,
    float normalizedA )
{
    return Color(
        (convertNormalizedValue(normalizedA) << 24) |
        (convertNormalizedValue(normalizedR) << 16) |
        (convertNormalizedValue(normalizedG) << 8) |
        (convertNormalizedValue(normalizedB) << 0)
    );
}

unsigned char Color::convertNormalizedValue( float normalizedValue ) {

    normalizedValue = normalizedValue < 0 ? 0 : normalizedValue;
    normalizedValue = normalizedValue > 1 ? 1 : normalizedValue;

    return static_cast< unsigned char >( normalizedValue * 255 );
}

const Color Color::Black( 0, 0, 0 );
const Color Color::White( 255, 255, 255 );

}
