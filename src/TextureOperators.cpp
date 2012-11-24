#include "TextureOperators.h"

#include <cstdint>

#include "Exception.h"
#include "Texture.h"

namespace storm {

std::istream& operator >> (
    std::istream &stream, std::shared_ptr<Texture> &result )
{
    if( !stream )
        throwInvalidArgument( "'stream' is invalid" );
    
    return stream;
}

}