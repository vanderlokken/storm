#pragma once

#include <storm/matrix.h>
#include <storm/quaternion.h>
#include <storm/vector.h>

namespace storm {

struct Rectangle;

// Note: camera uses left-handed coordinate system
class Camera {
public:
    struct DepthRange {
        // The [minimum, maximum] z coordinate range in the view space will be
        // mapped to the [-1, 1] z coordinate range in the NDC space.
        float minimum;
        float maximum;
    };

    const Vector& getPosition() const;
    void setPosition( const Vector& );

    const Quaternion& getRotation() const;
    void setRotation( const Quaternion& );

    Vector getDirection() const;

    DepthRange getDepthRange() const;
    void setDepthRange( DepthRange );

    // Returns transformation matrix, which maps world space coordinates to
    // the view space.
    Matrix getViewTransformation() const;

    // Returns transformation matrix, which maps view space coordinates to
    // the clip space.
    virtual Matrix getProjectionTransformation() const = 0;

    void move( const Vector &offset );
    void pointAt(
        const Vector &target,
        const Vector &directionUp = Vector::AxisY );

protected:
    Camera();

    DepthRange _depthRange;

private:
    Vector _position;
    Quaternion _rotation;
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
