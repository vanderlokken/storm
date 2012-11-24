#ifndef storm_TextureOperators_h
#define storm_TextureOperators_h

#include <istream>
#include <memory>

namespace storm {

class Texture;

std::istream& operator >> (
    std::istream &stream, std::shared_ptr<Texture> &result );
    
}

#endif