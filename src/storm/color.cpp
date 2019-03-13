#include <storm/color.h>

namespace storm {

const Color Color::Black( 0, 0, 0, 1 );
const Color Color::White( 1, 1, 1, 1 );

const Color Color::BlackTransparent( 0, 0, 0, 0 );
const Color Color::WhiteTransparent( 1, 1, 1, 0 );

const CompressedColor CompressedColor::Black( 0xFF000000 );
const CompressedColor CompressedColor::White( 0xFFFFFFFF );

const CompressedColor CompressedColor::BlackTransparent( 0x00000000 );
const CompressedColor CompressedColor::WhiteTransparent( 0x00FFFFFF );

}
