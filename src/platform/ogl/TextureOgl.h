#ifndef storm_TextureOgl_h
#define storm_TextureOgl_h

#include "CoreTypesOgl.h"
#include "Noncopyable.h"
#include "Texture.h"

namespace storm {

class TextureOgl : public Texture {
    NONCOPYABLE( TextureOgl );
public:
    TextureOgl( const Description&, const void *texels = nullptr );
    ~TextureOgl() noexcept;

    virtual void getTexels( unsigned int lodIndex, void *texels ) const;
    virtual void setTexels( unsigned int lodIndex, const void *texels );

    virtual const Description& getDescription() const noexcept;
    
private:
    Description _description;
    GLuint _texture;
};

}

#endif