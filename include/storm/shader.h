#pragma once

#include <iosfwd>
#include <memory>
#include <string_view>
#include <vector>

#include <storm/buffer.h>
#include <storm/exception.h>
#include <storm/identifier.h>
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

    static Shader::Pointer create( std::string_view sourceCode, Type type );

    // This method can create a shader from binary representation, returned by
    // the 'getBinaryRepresentation' method. A change in hardware or software
    // configuration can make binary representation invalid. In such cases this
    // method returns 'nullptr'.
    static Shader::Pointer create(
        const std::vector<unsigned char> &binaryRepresentation, Type type );

    static Shader::Pointer load( std::istream &stream, Type type,
        Format format = Format::Source );
    static Shader::Pointer load( std::string_view filename, Type type,
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
    //
    // This method doesn't return handles for GLSL standalone uniform values.
    // Standalone GLSL uniforms of the 'vec4' type, which have reserved names
    // '_root_0', '_root_1', '_root_2', etc., are bound to the root buffer with
    // offsets 0, 16, 32, etc. Use the 'RenderingSystem::setRootBufferData'
    // method to set their values.
    virtual ValueHandle getValueHandle( Identifier identifier ) const = 0;

    // The following methods throw 'ShaderValueLookupError'-typed exceptions
    // when the specified value handle is invalid.
    virtual void setValue( ValueHandle handle, Buffer::Pointer ) = 0;
    virtual void setValue( ValueHandle handle, Sampler::Pointer ) = 0;
    virtual void setValue( ValueHandle handle, Texture::Pointer ) = 0;

    ValueHandle getValueHandle( std::string_view identifier ) const {
        return getValueHandle( Identifier::fromStringView(identifier) );
    }

    void setValue( std::string_view identifier, Buffer::Pointer buffer ) {
        setValue( getValueHandle(identifier), buffer );
    }

    void setValue( std::string_view identifier, Sampler::Pointer sampler ) {
        setValue( getValueHandle(identifier), sampler );
    }

    void setValue( std::string_view identifier, Texture::Pointer texture ) {
        setValue( getValueHandle(identifier), texture );
    }
};

class ShaderCompilationError : public Exception {};
class ShaderValueLookupError : public Exception {};

}
