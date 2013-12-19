#include <storm/color.h>

namespace storm {

Color::Color() noexcept
    : _value( 0xFF000000 ) { }

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) noexcept
    : _value( (a << 24) | (r << 16) | (g << 8) | (b << 0) ) { }

Color::Color( uint32_t argb ) noexcept
    : _value( argb ) { }

uint32_t Color::get() const noexcept {
    return _value;
}

unsigned char Color::getR() const noexcept {
    return static_cast< unsigned char >( _value >> 16 );
}

unsigned char Color::getG() const noexcept {
    return static_cast< unsigned char >( _value >> 8 );
}

unsigned char Color::getB() const noexcept {
    return static_cast< unsigned char >( _value >> 0 );
}

unsigned char Color::getA() const noexcept {
    return static_cast< unsigned char >( _value >> 24 );
}

void Color::setR( unsigned char r ) noexcept {
    _value = (_value & 0xFF00FFFF) | (static_cast<uint32_t>(r) << 16);
    return;
}

void Color::setG( unsigned char g ) noexcept {
    _value = (_value & 0xFFFF00FF) | (static_cast<uint32_t>(g) << 8);
    return;
}

void Color::setB( unsigned char b ) noexcept {
    _value = (_value & 0xFFFFFF00) | (static_cast<uint32_t>(b) << 0);
    return;
}

void Color::setA( unsigned char a ) noexcept {
    _value = (_value & 0x00FFFFFF) | (static_cast<uint32_t>(a) << 24);
    return;
}

float Color::getNormalizedR() const noexcept {
    return getR() / 255.0f;
}

float Color::getNormalizedG() const noexcept {
    return getG() / 255.0f;
}

float Color::getNormalizedB() const noexcept {
    return getB() / 255.0f;
}

float Color::getNormalizedA() const noexcept {
    return getA() / 255.0f;
}

void Color::setNormalizedR( float normalizedR ) noexcept {
    setR( convertNormalizedValue(normalizedR) );
    return;
}

void Color::setNormalizedG( float normalizedG ) noexcept {
    setG( convertNormalizedValue(normalizedG) );
    return;
}

void Color::setNormalizedB( float normalizedB ) noexcept {
    setB( convertNormalizedValue(normalizedB) );
    return;
}

void Color::setNormalizedA( float normalizedA ) noexcept {
    setA( convertNormalizedValue(normalizedA) );
    return;
}

Color Color::fromNormalized(
    float normalizedR,
    float normalizedG,
    float normalizedB,
    float normalizedA ) noexcept
{
    return Color(
        (convertNormalizedValue(normalizedA) << 24) |
        (convertNormalizedValue(normalizedR) << 16) |
        (convertNormalizedValue(normalizedG) << 8) |
        (convertNormalizedValue(normalizedB) << 0)
    );
}

unsigned char Color::convertNormalizedValue( float normalizedValue ) noexcept {

    normalizedValue = normalizedValue < 0 ? 0 : normalizedValue;
    normalizedValue = normalizedValue > 1 ? 1 : normalizedValue;

    return static_cast< unsigned char >( normalizedValue * 255 );
}

const Color Color::Black( 0.0f, 0.0f, 0.0f );
const Color Color::White( 1.0f, 1.0f, 1.0f );

}