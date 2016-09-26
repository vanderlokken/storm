#pragma once

#include <map>

#include <storm/noncopyable.h>
#include <storm/platform/ogl/handle_ogl.h>
#include <storm/shader.h>

namespace storm {

class ProgramHandleOgl : public HandleOgl {
public:
    ProgramHandleOgl();
    ProgramHandleOgl( GLenum shaderType, const char *sourceCode );
    ~ProgramHandleOgl();
};

class ShaderOgl : public Shader {
    NONCOPYABLE( ShaderOgl );
public:
    ShaderOgl( const std::string &sourceCode, Type type );
    ShaderOgl( const std::vector<unsigned char> &binary, Type type );

    virtual Type getType() const;

    virtual std::vector<unsigned char> getBinaryRepresentation() const;

    virtual ValueHandle getValueHandle( const std::string &identifier ) const;

    virtual void setValue(
        ValueHandle handle, Buffer::Pointer, size_t offset, size_t size );
    virtual void setValue( ValueHandle handle, Buffer::Pointer );
    virtual void setValue( ValueHandle handle, Sampler::Pointer );
    virtual void setValue( ValueHandle handle, Texture::Pointer );

    const ProgramHandleOgl& getHandle() const;

    void install() const;

private:
    GLint getProgramParameter( GLenum parameter ) const;

    void createSamplersMapping();
    void createUniformBlocksMapping();

    void validateValueHandle( ValueHandle handle ) const;

    static GLenum convertType( Type );

    struct GlslSampler {
        GLuint textureUnit;
        Texture::Pointer texture;
        Sampler::Pointer sampler;
    };

    struct GlslUniformBlock {
        GLuint bindingPoint;
        GLintptr offset;
        GLsizeiptr size;
        Buffer::Pointer buffer;
    };

    Type _type;
    ProgramHandleOgl _handle;
    std::map<GLint, GlslSampler> _samplersMapping;
    std::map<GLint, GlslUniformBlock> _uniformBlocksMapping;
};

}
