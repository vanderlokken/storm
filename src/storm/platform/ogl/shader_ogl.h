#pragma once

#include <cstdint>
#include <vector>

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

    virtual void setValue( ValueHandle handle, Buffer::Pointer );
    virtual void setValue( ValueHandle handle, Sampler::Pointer );
    virtual void setValue( ValueHandle handle, Texture::Pointer );

    const ProgramHandleOgl& getHandle() const;

    void install() const;

    void handleRootBufferUpdate(
        const std::vector<uint8_t> &rootBuffer, size_t offset, size_t size );

private:
    GLint getProgramParameter( GLenum parameter ) const;

    void setupBindings();

    void setupSamplersBinding();
    void setupUniformBlocksBinding();
    void setupRootUniformsBinding();

    void validateValueHandle( ValueHandle handle ) const;

    static GLenum convertType( Type );

    Type _type;
    ProgramHandleOgl _handle;

    GLuint _baseSamplerBinding;
    GLuint _baseBufferBinding;

    std::vector<GLint> _samplerUniformLocations;

    std::vector<Texture::Pointer> _textures;
    std::vector<Sampler::Pointer> _samplers;
    std::vector<Buffer::Pointer> _buffers;

    std::vector<GLint> _rootUniformLocations;
};

}
