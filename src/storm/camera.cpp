#define _USE_MATH_DEFINES
#include <storm/camera.h>

#include <cmath>

#include <storm/rectangle.h>
#include <storm/throw_exception.h>

namespace storm {

Camera::Camera() :
    _depthRange( DepthRange {0.1f, 1000.0f} ),
    _direction( Vector::AxisZ )
{
}

const Vector& Camera::getPosition() const {
    return _position;
}

void Camera::setPosition( const Vector &position ) {
    _position = position;
}

const Vector& Camera::getDirection() const {
    return _direction;
}

void Camera::setDirection( const Vector &direction ) {
    _direction = direction.getNormalized();
}

Camera::DepthRange Camera::getDepthRange() const {
    return _depthRange;
}

void Camera::setDepthRange( DepthRange depthRange ) {
    storm_assert(
        depthRange.maximum - depthRange.minimum > 0 &&
        depthRange.minimum >= 0 );
    _depthRange = depthRange;
}

Matrix Camera::getViewTransformation() const {
    const Vector directionUp = Vector::AxisY;

    const Vector zAxis = _direction;
    const Vector xAxis = crossProduct( directionUp, zAxis ).getNormalized();
    const Vector yAxis = crossProduct( zAxis, xAxis );

    return Matrix(
        xAxis.x, yAxis.x, zAxis.x, 0,
        xAxis.y, yAxis.y, zAxis.y, 0,
        xAxis.z, yAxis.z, zAxis.z, 0,
        -dotProduct( xAxis, _position ),
        -dotProduct( yAxis, _position ),
        -dotProduct( zAxis, _position ), 1 );
}

void Camera::move( const Vector &offset ) {
    _position += offset;
}

void Camera::pointAt( const Vector &target ) {
    _direction = (target - _position).getNormalized();
}

PerspectiveCamera::PerspectiveCamera() :
    _frameAspectRatio( 1.0f ),
    _fieldOfView( static_cast<float>(M_PI / 2) )
{
}

float PerspectiveCamera::getFrameAspectRatio() const {
    return _frameAspectRatio;
}

void PerspectiveCamera::setFrameAspectRatio( float frameAspectRatio ) {
    storm_assert( frameAspectRatio > 0 );
    _frameAspectRatio = frameAspectRatio;
}

float PerspectiveCamera::getFieldOfView() const {
    return _fieldOfView;
}

void PerspectiveCamera::setFieldOfView( float fieldOfView ) {
    storm_assert( fieldOfView > 0 );
    _fieldOfView = fieldOfView;
}

float PerspectiveCamera::getVerticalFieldOfView() const {
    return 2 * std::atan(
        std::tan(_fieldOfView / 2) / _frameAspectRatio );
}

Matrix PerspectiveCamera::getProjectionTransformation() const {
    const float depthRange = _depthRange.maximum - _depthRange.minimum;
    const float scale =
        static_cast<float>( std::tan((M_PI - _fieldOfView) / 2) );

    Matrix result;

    result[0][0] = scale;
    result[1][1] = scale * _frameAspectRatio;
    result[2][2] = (_depthRange.minimum + _depthRange.maximum) / depthRange;
    result[2][3] = 1.0f;
    result[3][2] = -2 * _depthRange.minimum * _depthRange.maximum / depthRange;

    return result;
}

OrthographicCamera::OrthographicCamera() :
    _frameDimensions( 1.0f, 1.0f )
{
}

Vector2d OrthographicCamera::getFrameDimensions() const {
    return _frameDimensions;
}

void OrthographicCamera::setFrameDimensions( Vector2d frameDimensions ) {
    storm_assert(
        frameDimensions.x > 0 &&
        frameDimensions.y > 0 );
    _frameDimensions = frameDimensions;
}

Matrix OrthographicCamera::getProjectionTransformation() const {
    const float depthRange = _depthRange.maximum - _depthRange.minimum;

    Matrix result;

    result[0][0] =  2.0f / _frameDimensions.x;
    result[1][1] =  2.0f / _frameDimensions.y;
    result[2][2] =  2.0f / depthRange;
    result[3][2] = -(_depthRange.minimum + _depthRange.maximum) / depthRange;
    result[3][3] =  1.0f;

    return result;
}

Vector unprojectNDC(
    const Vector &normalizedDeviceCoordinates,
    const Camera &camera )
{
    return normalizedDeviceCoordinates * (
        camera.getViewTransformation() *
        camera.getProjectionTransformation()
    ).getInverted();
}

Vector unprojectDirectionNDC(
    const Vector2d &normalizedDeviceCoordinates,
    const Camera &camera )
{
    const Vector completeNormalizedDeviceCoordinates {
        normalizedDeviceCoordinates.x,
        normalizedDeviceCoordinates.y,
        0.0f
    };

    return (
        unprojectNDC(
            completeNormalizedDeviceCoordinates, camera) - camera.getPosition()
    ).getNormalized();
}

Vector windowCoordinatesToNDC(
    const Vector &windowCoordinates,
    const Rectangle &outputRectangle )
{
    const float x = -1.0f + 2.0f *
        (windowCoordinates.x - outputRectangle.x) / outputRectangle.width;
    const float y = 1.0f - 2.0f *
        (windowCoordinates.y - outputRectangle.y) / outputRectangle.height;
    const float z = -1.0f + 2.0f * windowCoordinates.z;
    return Vector {x, y, z};
}

Vector2d windowCoordinatesToNDC(
    const IntVector2d &windowCoordinates,
    const Rectangle &outputRectangle )
{
    const Vector completeWindowCoordinats = {
        static_cast<float>(windowCoordinates.x),
        static_cast<float>(windowCoordinates.y),
        0.0f
    };
    const Vector completeNormalizedDeviceCoordinates =
        windowCoordinatesToNDC( completeWindowCoordinats, outputRectangle );
    return Vector2d {
        completeNormalizedDeviceCoordinates.x,
        completeNormalizedDeviceCoordinates.y
    };
}

}
