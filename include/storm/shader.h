#pragma once

#include <memory>
#include <string>
#include <vector>

#include <storm/color.h>
#include <storm/matrix.h>
#include <storm/sampler.h>
#include <storm/texture.h>
#include <storm/vector.h>

namespace storm {

class Shader {
public:
    typedef std::shared_ptr<Shader> Pointer;

    enum class Type {
        Vertex,
        Pixel,
        Geometry
    };

    class Uniform {
    public:
        Uniform( void*, Shader::Pointer );

        void setValue( int value );
        void setValue( float value );

        void setValue( const Color &value );
        void setValue( const Vector &value );
        void setValue( const Matrix &value );
        void setValue( const std::vector<Matrix> &matrices );

        void setValue( Texture::Pointer texture );
        void setValue( Sampler::Pointer sampler );

    private:
        void *_identifier;
        Shader::Pointer _shader;
    };

    static Shader::Pointer create( const std::string &sourceCode, Type type );
    static Shader::Pointer load( const std::string &filename, Type type );

    virtual ~Shader() { }

    virtual Type getType() const noexcept = 0;
    virtual Uniform getUniform( const std::string &identifier ) const = 0;
};

}
