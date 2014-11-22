#define _USE_MATH_DEFINES
#include <storm/camera.h>

#include <cmath>

#include <storm/throw_exception.h>

namespace storm {

Camera::Camera() :
    _minimalDepth( 0.1f ),
    _maximalDepth( 1000.0f ),
    _target( 0, 0, 1 )
{
}

const Vector& Camera::getPosition() const {
    return _position;
}

void Camera::setPosition( const Vector &position ) {
    _position = position;
}

const Vector& Camera::getTarget() const {
    return _target;
}

void Camera::setTarget( const Vector &target ) {
    _target = target;
}

float Camera::getMinimalDepth() const {
    return _minimalDepth;
}

float Camera::getMaximalDepth() const {
    return _maximalDepth;
}

void Camera::setMinimalDepth( float depth ) {
    _minimalDepth = depth;

    if( _maximalDepth < _minimalDepth )
        _maximalDepth = _minimalDepth;
}

void Camera::setMaximalDepth( float depth ) {
    _maximalDepth = depth;

    if( _minimalDepth > _maximalDepth )
        _minimalDepth = _maximalDepth;
}

const Dimensions& Camera::getFrameDimensions() const {
    return _frameDimensions;
}

void Camera::setFrameDimensions( const Dimensions &frameDimensions ) {
    _frameDimensions = frameDimensions;
}

Matrix Camera::getViewTransformation() const {
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

PerspectiveCamera::PerspectiveCamera() :
    _fieldOfView( static_cast<float>(M_PI / 2) )
{
}

float PerspectiveCamera::getFieldOfView() const {
    return _fieldOfView;
}

void PerspectiveCamera::setFieldOfView( float fieldOfView ) {
    _fieldOfView = fieldOfView;
}

Matrix PerspectiveCamera::getProjectionTransformation() const {
    storm_assert( _frameDimensions.width && _frameDimensions.height );

    const float aspectRatio =
         _frameDimensions.width / static_cast<float>( _frameDimensions.height );
    const float depthRange = _maximalDepth - _minimalDepth;

    const float scale = static_cast<float>( tan((M_PI - _fieldOfView) / 2) );

    Matrix result;

    result[0][0] = scale;
    result[1][1] = scale * aspectRatio;
    result[2][2] = _maximalDepth / depthRange;
    result[2][3] = 1.0f;
    result[3][2] = -_minimalDepth * _maximalDepth / depthRange;

    return result;
}

OrthographicCamera::OrthographicCamera() { }

Matrix OrthographicCamera::getProjectionTransformation() const {
    const float depthRange = _maximalDepth - _minimalDepth;

    Matrix result;

    result[0][0] =  2.0f / _frameDimensions.width;
    result[1][1] =  2.0f / _frameDimensions.height;
    result[2][2] =  1.0f / depthRange;
    result[3][2] = -_minimalDepth / depthRange;
    result[3][3] =  1.0f;

    return result;
}

}
