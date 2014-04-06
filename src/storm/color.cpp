#include <storm/color.h>

namespace storm {

const Color Color::Black = Color( 0, 0, 0, 1 );
const Color Color::White = Color( 1, 1, 1, 1 );

const CompressedColor CompressedColor::Black = CompressedColor( 0xFF000000 );
const CompressedColor CompressedColor::White = CompressedColor( 0xFFFFFFFF );

}
