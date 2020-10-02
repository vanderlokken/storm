#pragma once

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/vertex_format.h>

namespace storm {

class VertexFormatOgl : public VertexFormat {
public:
    VertexFormatOgl( const Description& );

    const Description& getDescription() const override;

    void install( const GpuContextOgl &gpuContext ) const;

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
