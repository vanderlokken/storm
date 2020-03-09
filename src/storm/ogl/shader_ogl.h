#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <storm/ogl/handle_ogl.h>
#include <storm/shader.h>

namespace storm {

class ProgramHandleOgl : public HandleOgl {
public:
    ProgramHandleOgl();
    ProgramHandleOgl( GLenum shaderType, const char *sourceCode );
    ~ProgramHandleOgl();
};

class ShaderOgl : public Shader {
public:
    ShaderOgl( std::string_view sourceCode, Type type );
    ShaderOgl( const std::vector<unsigned char> &binary, Type type );

    Type getType() const override;

    std::vector<unsigned char> getBinaryRepresentation() const override;

    ValueHandle getValueHandle( Identifier identifier ) const override;

    void setValue( ValueHandle handle, Buffer::Pointer ) override;
    void setValue( ValueHandle handle, Sampler::Pointer ) override;
    void setValue( ValueHandle handle, Texture::Pointer ) override;

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

    bool isInstalled() const;

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

    std::unordered_map<Identifier, ValueHandle> _valueHandles;
};

}
