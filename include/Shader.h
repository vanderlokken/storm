#ifndef storm_Shader_h
#define storm_Shader_h

#include <memory>
#include <string>
#include <vector>

#include "Color.h"
#include "Matrix.h"
#include "Vector.h"

namespace storm {

class Sampler;
class Texture;

class Shader {
public:

    enum Type {
        TypeVertex,
        TypePixel,
        TypeGeometry
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

    static std::shared_ptr<Shader> create( const std::string &sourceCode, Type type );
    static std::shared_ptr<Shader> load( const std::string &filename, Type type );

    virtual ~Shader() { }

    virtual Type getType() const noexcept = 0;
    virtual Uniform getUniform( const std::string &identifier ) const = 0;
};

}

#endif
