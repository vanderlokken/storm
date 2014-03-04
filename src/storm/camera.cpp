#include <storm/camera.h>

#include <cmath>

#include <storm/math.h>

namespace storm {

Camera::Camera() noexcept
    : _minimalDepth( 0.1f ), _maximalDepth( 1000.0f ), _target( 0, 0, 1 ) { }

const Vector& Camera::getPosition() const noexcept {
    return _position;
}

void Camera::setPosition( const Vector &position ) noexcept {
    _position = position;
    return;
}

const Vector& Camera::getTarget() const noexcept {
    return _target;
}

void Camera::setTarget( const Vector &target ) noexcept {
    _target = target;
    return;
}

float Camera::getMinimalDepth() const noexcept {
    return _minimalDepth;
}

float Camera::getMaximalDepth() const noexcept {
    return _maximalDepth;
}

void Camera::setMinimalDepth( float depth ) noexcept {
    _minimalDepth = depth;

    if( _maximalDepth < _minimalDepth )
        _maximalDepth = _minimalDepth;
    return;
}

void Camera::setMaximalDepth( float depth ) noexcept {
    _maximalDepth = depth;

    if( _minimalDepth > _maximalDepth )
        _minimalDepth = _maximalDepth;
    return;
}

const Dimensions& Camera::getFrameDimensions() const noexcept {
    return _frameDimensions;
}

void Camera::setFrameDimensions( const Dimensions &frameDimensions ) noexcept {
    _frameDimensions = frameDimensions;
    return;
}

Matrix Camera::getViewTransformation() const noexcept {
    const Vector directionUp( 0, 1, 0 );

    Vector zAxis = _target - _position;
    zAxis.normalize();

    Vector xAxis = Vector::getCrossProduct( directionUp, zAxis );
    xAxis.normalize();

    Vector yAxis = Vector::getCrossProduct( zAxis, xAxis );

    return Matrix(
        xAxis.x, yAxis.x, zAxis.x, 0,
        xAxis.y, yAxis.y, zAxis.y, 0,
        xAxis.z, yAxis.z, zAxis.z, 0,
        -Vector::getDotProduct( xAxis, _position ),
        -Vector::getDotProduct( yAxis, _position ),
        -Vector::getDotProduct( zAxis, _position ), 1 );
}

PerspectiveCamera::PerspectiveCamera() noexcept : _fieldOfView( Pi / 2 ) { }

float PerspectiveCamera::getFieldOfView() const noexcept {
    return _fieldOfView;
}

void PerspectiveCamera::setFieldOfView( float fieldOfView ) noexcept {
    _fieldOfView = fieldOfView;
    return;
}

Matrix PerspectiveCamera::getProjectionTransformation() const noexcept {
    const float frameWidth = static_cast< float >( _frameDimensions.width );
    const float frameHeight = static_cast< float >( _frameDimensions.height );
    const float aspectRatio = frameWidth / frameHeight;
    const float depthRange = _maximalDepth - _minimalDepth;

    Matrix result;

    result[0][0] = tan( Pi / 2 - _fieldOfView / 2 );
    result[1][1] = tan( Pi / 2 - _fieldOfView / 2 ) * aspectRatio;
    result[2][2] = _maximalDepth / depthRange;
    result[2][3] = 1;
    result[3][2] = -_minimalDepth * _maximalDepth / depthRange;

    return result;
}

OrthographicCamera::OrthographicCamera() noexcept { }

Matrix OrthographicCamera::getProjectionTransformation() const noexcept {
    const float frameWidth = static_cast< float >( _frameDimensions.width );
    const float frameHeight = static_cast< float >( _frameDimensions.height );
    const float depthRange = _maximalDepth - _minimalDepth;

    Matrix result;

    result[0][0] =  2 / frameWidth;
    result[1][1] =  2 / frameHeight;
    result[2][2] =  1 / depthRange;
    result[3][2] = -_minimalDepth / depthRange;
    result[3][3] =  1;

    return result;
}

}
