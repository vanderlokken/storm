#pragma once

#include <storm/dimensions.h>
#include <storm/matrix.h>
#include <storm/vector.h>

namespace storm {

// Note: camera uses left-handed coordinate system
class Camera {
public:
    const Vector& getPosition() const;
    void setPosition( const Vector& );

    const Vector& getTarget() const;
    void setTarget( const Vector& );

    float getMinimalDepth() const;
    float getMaximalDepth() const;

    void setMinimalDepth( float );
    void setMaximalDepth( float );

    const Dimensions& getFrameDimensions() const;
    void setFrameDimensions( const Dimensions& );

    Matrix getViewTransformation() const;
    virtual Matrix getProjectionTransformation() const = 0;

protected:
    Camera();

    Dimensions _frameDimensions;
    float _minimalDepth;
    float _maximalDepth;

private:
    Vector _position;
    Vector _target;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera();

    float getFieldOfView() const;
    void setFieldOfView( float );

    virtual Matrix getProjectionTransformation() const;

private:
    float _fieldOfView;
};

class OrthographicCamera : public Camera {
public:
    OrthographicCamera();

    virtual Matrix getProjectionTransformation() const;
};

Vector unprojectScreenCoordinates(
    IntVector2d screenCoordinates, const Camera &camera );

}
