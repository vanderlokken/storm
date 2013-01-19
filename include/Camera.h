#ifndef storm_Camera_h
#define storm_Camera_h

#include "Dimensions.h"
#include "Noexcept.h"
#include "Matrix.h"
#include "Vector.h"

namespace storm {

class Camera {
public:
    void activate() const;

    const Vector& getPosition() const noexcept;
    void setPosition( const Vector& ) noexcept;

    const Vector& getTarget() const noexcept;
    void setTarget( const Vector& ) noexcept;

    float getMinimalDepth() const noexcept;
    float getMaximalDepth() const noexcept;

    void setMinimalDepth( float ) noexcept;
    void setMaximalDepth( float ) noexcept;

    const Dimensions& getFrameDimensions() const noexcept;
    void setFrameDimensions( const Dimensions& ) noexcept;

    Matrix getViewTransformation() const noexcept;
    virtual Matrix getProjectionTransformation() const noexcept = 0;

protected:
    Camera() noexcept;

    Dimensions _frameDimensions;
    float _minimalDepth;
    float _maximalDepth;

private:
    Vector _position;
    Vector _target;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera() noexcept;

    float getFieldOfView() const noexcept;
    void setFieldOfView( float ) noexcept;

    virtual Matrix getProjectionTransformation() const noexcept;

private:
    float _fieldOfView;
};

class OrthographicCamera : public Camera {
public:
    OrthographicCamera() noexcept;

    virtual Matrix getProjectionTransformation() const noexcept;
};

}

#endif