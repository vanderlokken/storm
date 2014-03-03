#pragma once

#include <memory>
#include <string>

#include <storm/buffer.h>
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

    typedef std::shared_ptr<void> ValueHandle;

    static Shader::Pointer create( const std::string &sourceCode, Type type );
    static Shader::Pointer load( const std::string &filename, Type type );

    virtual ~Shader() { }

    virtual Type getType() const noexcept = 0;

    virtual ValueHandle getValueHandle(
        const std::string &identifier ) const = 0;

    virtual void setValue( ValueHandle handle, Buffer::Pointer ) = 0;
    virtual void setValue( ValueHandle handle, Sampler::Pointer ) = 0;
    virtual void setValue( ValueHandle handle, Texture::Pointer ) = 0;

    void setValue( const std::string &identifier, Buffer::Pointer buffer ) {
        setValue( getValueHandle(identifier), buffer );
    }

    void setValue( const std::string &identifier, Sampler::Pointer sampler ) {
        setValue( getValueHandle(identifier), sampler );
    }

    void setValue( const std::string &identifier, Texture::Pointer texture ) {
        setValue( getValueHandle(identifier), texture );
    }
};

}
