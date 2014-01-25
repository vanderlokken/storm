#pragma once

#include <storm/output_technique.h>
#include <storm/platform/ogl/api_ogl.h>

namespace storm {

class OutputTechniqueOgl : public OutputTechnique {
public:

    // The following structures store values adapted for OpenGL

    struct DepthTest {
        bool enabled;
        GLenum passCondition;
    };

    struct StencilTest {
        bool enabled;

        unsigned int referenceValue;
        unsigned int mask;

        struct Algorithm {
            GLenum passCondition;
            GLenum operationOnStencilTestFail;
            GLenum operationOnDepthTestFail;
            GLenum operationOnDepthTestPass;
        };

        Algorithm algorithmForFrontFaces;
        Algorithm algorithmForBackFaces;
    };

    struct Description {
          DepthTest depthTest;
        StencilTest stencilTest;
               bool writeDepthValues;
    };

    OutputTechniqueOgl( const OutputTechnique::Description& );

    virtual const OutputTechnique::Description& getDescription() const noexcept;
    virtual const Description& getNativeDescription() const noexcept;

private:
    static GLenum convertCondition( Condition );
    static GLenum convertStencilOperation( StencilOperation );

    static DepthTest convertDepthTestDescription(
        const OutputTechnique::DepthTest& );
    static StencilTest convertStencilTestDescription(
        const OutputTechnique::StencilTest& );

    OutputTechnique::Description _description;
    Description _nativeDescription;
};

}
