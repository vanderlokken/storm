#pragma once

#include <storm/platform/ogl/api_ogl.h>
#include <storm/vertex_format.h>

namespace storm {

class VertexFormatOgl : public VertexFormat {
public:
    VertexFormatOgl( const Description& );

    virtual const Description& getDescription() const;

    size_t getVertexSize() const;

    void install() const;

private:
    struct AttributeFormatDescription {
        GLsizei size;
        GLint componentCount;
        GLenum componentType;
        GLboolean componentNormalized;
    };

    static AttributeFormatDescription getAttributeFormatDescription(
        Attribute::Format );

    Description _description;
};

}
