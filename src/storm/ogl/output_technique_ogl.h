#pragma once

#include <storm/output_technique.h>
#include <storm/ogl/api_ogl.h>

namespace storm {

class OutputTechniqueOgl : public OutputTechnique {
public:
    struct DepthTest {
        GLenum passCondition;
    };

    struct StencilTest {
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
        std::optional<DepthTest> depthTest;
        std::optional<StencilTest> stencilTest;
        bool writeDepthValues;
    };

    OutputTechniqueOgl( const OutputTechnique::Description& );

    const OutputTechnique::Description& getDescription() const override;
    const Description& getNativeDescription() const;

private:
    static GLenum convertStencilOperation( StencilOperation );

    static DepthTest convertDepthTestDescription(
        const OutputTechnique::DepthTest& );
    static StencilTest convertStencilTestDescription(
        const OutputTechnique::StencilTest& );

    OutputTechnique::Description _description;
    Description _nativeDescription;
};

}
