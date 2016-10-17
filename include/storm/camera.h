#pragma once

#include <storm/matrix.h>
#include <storm/vector.h>

namespace storm {

struct Rectangle;

// Note: camera uses left-handed coordinate system
class Camera {
public:
    struct DepthRange {
        float minimum;
        float maximum;
    };

    const Vector& getPosition() const;
    void setPosition( const Vector& );

    // The returned direction is normalized.
    const Vector& getDirection() const;
    void setDirection( const Vector& );

    DepthRange getDepthRange() const;
    void setDepthRange( DepthRange );

    Matrix getViewTransformation() const;
    virtual Matrix getProjectionTransformation() const = 0;

    void move( const Vector& );
    void pointAt( const Vector& );

protected:
    Camera();

    DepthRange _depthRange;

private:
    Vector _position;
    Vector _direction;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera();

    float getFrameAspectRatio() const;
    void setFrameAspectRatio( float );

    float getFieldOfView() const;
    void setFieldOfView( float );

    float getVerticalFieldOfView() const;

    virtual Matrix getProjectionTransformation() const;

private:
    float _frameAspectRatio;
    float _fieldOfView;
};

class OrthographicCamera : public Camera {
public:
    OrthographicCamera();

    Vector2d getFrameDimensions() const;
    void setFrameDimensions( Vector2d );

    virtual Matrix getProjectionTransformation() const;

private:
    Vector2d _frameDimensions;
};

Vector unprojectNDC(
    const Vector &normalizedDeviceCoordinates,
    const Camera &camera );

Vector unprojectDirectionNDC(
    const Vector2d &normalizedDeviceCoordinates,
    const Camera &camera );

Vector windowCoordinatesToNDC(
    const Vector &windowCoordinates,
    const Rectangle &outputRectangle );

Vector2d windowCoordinatesToNDC(
    const IntVector2d &windowCoordinates,
    const Rectangle &outputRectangle );

}
