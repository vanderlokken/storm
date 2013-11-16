#pragma once

#include <memory>
#include <string>
#include <vector>

#include <storm/color.h>
#include <storm/matrix.h>
#include <storm/vector.h>

namespace storm {

class Sampler;
class Texture;

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
        Uniform( void* );

        void setValue( int value );
        void setValue( float value );

        void setValue( const Color &value );
        void setValue( const Vector &value );
        void setValue( const Matrix &value );
        void setValue( const std::vector<Matrix> &matrices );

    private:
        void *_identifier;
    };

    static Shader::Pointer create( const std::string &sourceCode, Type type );
    static Shader::Pointer load( const std::string &filename, Type type );

    virtual ~Shader() { }

    virtual Type getType() const noexcept = 0;
    virtual Uniform getUniform( const std::string &identifier ) const = 0;
};

}
