#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/shader.h>

namespace storm {

class ProgramHandleOgl {
public:
    explicit ProgramHandleOgl( const GpuContextOgl::Pointer &gpuContext );

    ProgramHandleOgl(
        const GpuContextOgl::Pointer &gpuContext,
        GLenum shaderType,
        std::string_view sourceCode );

    ProgramHandleOgl(
        const ProgramHandleOgl& ) = delete;
    ProgramHandleOgl& operator = (
        const ProgramHandleOgl& ) = delete;

    ~ProgramHandleOgl();

    GpuContextOgl::Pointer getGpuContext() const {
        return _gpuContext.locked();
    }

    operator GLuint () const {
        return _handle;
    }

private:
    WeakGpuContextOgl _gpuContext;
    GLuint _handle = 0;
};

class ShaderOgl : public Shader {
public:
    ShaderOgl(
        GpuContextOgl::Pointer gpuContext,
        std::string_view sourceCode,
        Type type );

    ShaderOgl(
        GpuContextOgl::Pointer gpuContext,
        const std::vector<unsigned char> &binary,
        Type type );

    Type getType() const override;

    std::vector<unsigned char> getBinaryRepresentation() const override;

    ValueHandle getValueHandle( Identifier identifier ) const override;

    void setValue( ValueHandle handle, Buffer::Pointer ) override;
    void setValue( ValueHandle handle, Sampler::Pointer ) override;
    void setValue( ValueHandle handle, Texture::Pointer ) override;

    const ProgramHandleOgl& getHandle() const;

    void updateChangedBindings();
    void markAllBindingsChanged();

    void handleRootBufferUpdate(
        const std::vector<uint8_t> &rootBuffer, size_t offset, size_t size );

private:
    template <class T>
    struct Binding {
        T value;
        bool isChanged = true;
    };

    GLint getProgramParameter(
        const GpuContextOgl &gpuContext, GLenum parameter ) const;

    void setupBindings( const GpuContextOgl &gpuContext );

    void setupSamplersBinding( const GpuContextOgl &gpuContext );
    void setupUniformBlocksBinding( const GpuContextOgl &gpuContext );
    void setupRootUniformsBinding( const GpuContextOgl &gpuContext );

    void validateValueHandle( ValueHandle handle ) const;

    static GLenum convertType( Type );

    Type _type;
    ProgramHandleOgl _handle;

    GLuint _baseSamplerBinding;
    GLuint _baseBufferBinding;

    std::vector<GLint> _samplerUniformLocations;

    std::vector<Binding<Texture::Pointer>> _textures;
    std::vector<Binding<Sampler::Pointer>> _samplers;
    std::vector<Binding<Buffer::Pointer>> _buffers;

    std::vector<GLint> _rootUniformLocations;

    std::unordered_map<Identifier, ValueHandle> _valueHandles;
};

}
