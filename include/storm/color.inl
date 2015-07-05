namespace storm {

inline Color::Color() :
    r( 0 ), g( 0 ), b( 0 ), a( 1 )
{
}

inline Color::Color(
    float r, float g, float b, float a ) : r( r ), g( g ), b( b ), a( a )
{
}

namespace internal {

inline unsigned char fromNormalized( float normalizedValue ) {

    normalizedValue = normalizedValue < 0 ? 0 : normalizedValue;
    normalizedValue = normalizedValue > 1 ? 1 : normalizedValue;

    return static_cast< unsigned char >( normalizedValue * 255 );
}

} // namespace internal

inline CompressedColor::CompressedColor() :
    value( 0xFF000000 )
{
}

inline CompressedColor::CompressedColor(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a ) :
        value( (a << 24) | (b << 16) | (g << 8) | (r << 0) )
{
}

inline CompressedColor::CompressedColor( Color color ) :
    value(
        (internal::fromNormalized(color.a) << 24) |
        (internal::fromNormalized(color.b) << 16) |
        (internal::fromNormalized(color.g) <<  8) |
        (internal::fromNormalized(color.r) <<  0) )
{
}

inline CompressedColor::CompressedColor( uint32_t value ) :
    value( value )
{
}

inline unsigned char CompressedColor::getR() const {
    return static_cast<unsigned char>( value >> 0 );
}

inline unsigned char CompressedColor::getG() const {
    return static_cast<unsigned char>( value >> 8 );
}

inline unsigned char CompressedColor::getB() const {
    return static_cast<unsigned char>( value >> 16 );
}

inline unsigned char CompressedColor::getA() const {
    return static_cast<unsigned char>( value >> 24 );
}

inline void CompressedColor::setR( unsigned char r ) {
    value = (value & 0xFFFFFF00) | (static_cast<uint32_t>(r) << 0);
}

inline void CompressedColor::setG( unsigned char g ) {
    value = (value & 0xFFFF00FF) | (static_cast<uint32_t>(g) << 8);
}

inline void CompressedColor::setB( unsigned char b ) {
    value = (value & 0xFF00FFFF) | (static_cast<uint32_t>(b) << 16);
}

inline void CompressedColor::setA( unsigned char a ) {
    value = (value & 0x00FFFFFF) | (static_cast<uint32_t>(a) << 24);
}

inline float CompressedColor::getNormalizedR() const {
    return getR() / 255.0f;
}

inline float CompressedColor::getNormalizedG() const {
    return getG() / 255.0f;
}

inline float CompressedColor::getNormalizedB() const {
    return getB() / 255.0f;
}

inline float CompressedColor::getNormalizedA() const {
    return getA() / 255.0f;
}

inline void CompressedColor::setNormalizedR( float normalizedR ) {
    setR( internal::fromNormalized(normalizedR) );
}

inline void CompressedColor::setNormalizedG( float normalizedG ) {
    setG( internal::fromNormalized(normalizedG) );
}

inline void CompressedColor::setNormalizedB( float normalizedB ) {
    setB( internal::fromNormalized(normalizedB) );
}

inline void CompressedColor::setNormalizedA( float normalizedA ) {
    setA( internal::fromNormalized(normalizedA) );
}

inline CompressedColor::operator Color() const {
    return Color(
        getNormalizedR(),
        getNormalizedG(),
        getNormalizedB(),
        getNormalizedA() );
}

}
