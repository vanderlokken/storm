#ifndef storm_ElementBufferOgl_h
#define storm_ElementBufferOgl_h

#include "CoreTypesOgl.h"
#include "ElementBuffer.h"
#include "Vertex.h"

namespace storm {

class ElementBufferOgl : public ElementBuffer {
public:
    ElementBufferOgl( const Description& );

    virtual ~ElementBufferOgl() noexcept;

    virtual const Description& getDescription() const noexcept;

    GLenum getElementTopology() const noexcept;
    GLuint getHandle() const noexcept;

private:
    void setVertexAttributes();

    static GLenum convertElementTopology( ElementTopology );

    struct VertexAttributeFormat {
        GLint componentCount;
        GLenum componentType;
        GLboolean componentNormalized;
    };

    static VertexAttributeFormat convertVertexAttributeFormat( Vertex::Attribute::Format );

    Description _description;
    GLenum _elementTopology;
    GLuint _handle;
};

}

#endif
