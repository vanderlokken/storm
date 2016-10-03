#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

#include <storm/buffer.h>
#include <storm/exception.h>
#include <storm/sampler.h>
#include <storm/texture.h>

namespace storm {

class Shader {
public:
    typedef std::shared_ptr<Shader> Pointer;

    enum class Type {
        Vertex,
        Pixel,
        Geometry
    };

    enum class Format {
        Source,
        Binary
    };

    typedef std::shared_ptr<void> ValueHandle;

    static Shader::Pointer create( const std::string &sourceCode, Type type );

    // This method can create a shader from binary representation, returned by
    // the 'getBinaryRepresentation' method. A change in hardware or software
    // configuration can make binary representation invalid. In such cases this
    // method returns 'nullptr'.
    static Shader::Pointer create(
        const std::vector<unsigned char> &binaryRepresentation, Type type );

    static Shader::Pointer load( std::istream &stream, Type type,
        Format format = Format::Source );
    static Shader::Pointer load( const std::string &filename, Type type,
        Format format = Format::Source );

    virtual ~Shader() { }

    virtual Type getType() const = 0;

    // The 'getBinaryRepresentation' method can return some binary data which
    // can be used to re-create the shader. When this functionality is
    // unavailable 'getBinaryRepresentation' returns zero-length result.
    virtual std::vector<unsigned char> getBinaryRepresentation() const = 0;

    // When a shader contains no value with the specified identifier, this
    // method returns a default-constructed 'ValueHandle' instance which
    // evaluates to 'false'.
    virtual ValueHandle getValueHandle(
        const std::string &identifier ) const = 0;

    // The following methods throw exceptions.
    // 1. 'ShaderValueLookupError', if the specified value handle was not
    // obtained, using the 'getValueHandle' method of the same object.
    // 2. 'ShaderValueTypeError', if the specified value is of a different
    // type.

    // Binds an entire constant buffer to the specified value.
    virtual void setValue( ValueHandle handle, Buffer::Pointer buffer ) = 0;
    // Binds a constant buffer range to the specified value.
    // The range offset must be a multiple of the 'BufferOffsetAlignment' value.
    virtual void setValue( ValueHandle handle, BufferRange bufferRange ) = 0;
    // Binds a sampler to the specified value.
    virtual void setValue( ValueHandle handle, Sampler::Pointer sampler ) = 0;
    // Binds a texture to the specified value.
    virtual void setValue( ValueHandle handle, Texture::Pointer texture ) = 0;

    void setValue( const std::string &identifier, BufferRange bufferRange ) {
        setValue( getValueHandle(identifier), bufferRange );
    }

    void setValue( const std::string &identifier, Buffer::Pointer buffer ) {
        setValue( getValueHandle(identifier), buffer );
    }

    void setValue( const std::string &identifier, Sampler::Pointer sampler ) {
        setValue( getValueHandle(identifier), sampler );
    }

    void setValue( const std::string &identifier, Texture::Pointer texture ) {
        setValue( getValueHandle(identifier), texture );
    }

    static const size_t BufferOffsetAlignment = 256;
};

class ShaderCompilationError : public Exception {};
class ShaderValueLookupError : public Exception {};
class ShaderValueTypeError : public Exception {};

}
