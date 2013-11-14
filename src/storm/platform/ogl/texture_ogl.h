#pragma once

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/texture.h>

namespace storm {

class TextureHandleOgl : public HandleOgl {
public:
    TextureHandleOgl();
    ~TextureHandleOgl();
};

class TextureOgl : public Texture {
    NONCOPYABLE( TextureOgl );
public:
    TextureOgl( const Description&, const void *texels = nullptr );

    virtual void getTexels( unsigned int lodIndex, void *texels ) const;
    virtual void setTexels( unsigned int lodIndex, const void *texels );

    virtual const Description& getDescription() const noexcept;

    const TextureHandleOgl& getHandle() const noexcept;

private:
    static GLenum convertFormat( Format );
    static GLint selectInternalFormat( Format );

    Description _description;
    TextureHandleOgl _texture;
};

}
