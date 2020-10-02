#include <chrono>
#include <iostream>

#include <storm/camera.h>
#include <storm/exception.h>
#include <storm/matrix.h>
#include <storm/quaternion.h>
#include <storm/rendering_system.h>
#include <storm/window.h>

#include "../example_base.h"
#include "resources.h"

const char *vertexShaderSource = R"(
#version 330 core

layout(row_major) uniform transformations {
    mat4 viewProjection;
    mat4 world;
} Transformations;

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTextureCoordinates;

out vec4 position;
out vec3 normal;
out vec2 textureCoordinates;

void main() {
    position = vertexPosition * Transformations.world;
    normal = vertexNormal * mat3( Transformations.world );
    textureCoordinates = vertexTextureCoordinates;

    gl_Position = position * Transformations.viewProjection;
}
)";

const char *pixelShaderSource = R"(
#version 330 core

uniform sampler2D colorTexture;

in vec4 position;
in vec3 normal;
in vec2 textureCoordinates;

out vec4 color;

const float ambientBrightness = 0.6;
const float lightBrightness = 0.6;
const vec3 lightPosition = vec3( 20, 20, 20 );

const float textureRepetitionsNumber = 3;

void main() {
    vec3 directionToLight = normalize( lightPosition - position.xyz );
    float brightness = ambientBrightness +
        lightBrightness * clamp( dot(normal, directionToLight), 0, 1 );

    color = brightness * texture(
        colorTexture, textureCoordinates * textureRepetitionsNumber );
}
)";

class Example : public ExampleBase {
public:
    explicit Example( storm::Window::Pointer window ) :
        _observer( std::make_shared<storm::WindowObserver>() ),
        _renderingSystem( storm::RenderingSystem::create() )
    {
        window->setWindowedMode( _frameDimensions );
        window->addObserver( _observer );

        _observer->onKeyboardKeyPressed = [this]( storm::KeyboardKey key ) {
            if( key == storm::KeyboardKey::V ) {
                _renderingSystem->setVsyncEnabled(
                    !_renderingSystem->isVsyncEnabled() );
                std::cout << "Vsync enabled: " <<
                    _renderingSystem->isVsyncEnabled() << std::endl;
            }
        };

        _renderingSystem->setOutputWindow( std::move(window) );

        storm::GpuContext::Pointer gpuContext =
            _renderingSystem->getGpuContext();

        _mesh = createTexturedCubeMesh( gpuContext );
        _texture = createCheckboardPatternTexture( gpuContext );
        _sampler = createCheckboardPatternSampler( gpuContext );

        installFramebuffer();
        installShaders();
        installCamera();
    }

    void update() override {
        const std::chrono::steady_clock::time_point timePoint =
            std::chrono::steady_clock::now();
        const std::chrono::duration<float> timeDelta( timePoint - _timePoint );

        _timePoint = timePoint;

        const float rotationSpeed = 1.f;
        _meshRotationAngle += timeDelta.count() * rotationSpeed;

        const storm::Quaternion rotationQuaternion =
            storm::Quaternion::fromAxisAngle(
                storm::Vector::AxisY, _meshRotationAngle ) *
            storm::Quaternion::fromAxisAngle(
                storm::Vector::AxisX, _meshRotationAngle );

        _transformations.world = rotationQuaternion.toRotationMatrix();
        _constantBuffer->setData( &_transformations );
    }

    void render() override {
        _renderingSystem->clearColorBuffer();
        _renderingSystem->clearDepthBuffer();

        _renderingSystem->renderMesh( _mesh );

        _renderingSystem->getBackbuffer()->renderTexture( _colorBufferTexture );
        _renderingSystem->presentBackbuffer();
    }

private:
    void installFramebuffer() {
        const unsigned int texelSamples = 1;

        storm::Framebuffer::Pointer framebuffer = storm::Framebuffer::create(
            _renderingSystem->getGpuContext(),
            _frameDimensions,
            texelSamples,
            {
                storm::Texture::Format::RgbaNormUint8,
                storm::Texture::Format::DepthNormUint24
            });

        _renderingSystem->setFramebuffer( framebuffer );

        _colorBufferTexture =
            framebuffer->getDescription().buffers[0].texture;
    }

    void installShaders() {
        const storm::GpuContext::Pointer gpuContext =
            _renderingSystem->getGpuContext();

        const storm::Shader::Pointer vertexShader = storm::Shader::create(
            gpuContext, vertexShaderSource, storm::Shader::Type::Vertex );
        const storm::Shader::Pointer pixelShader = storm::Shader::create(
            gpuContext, pixelShaderSource, storm::Shader::Type::Pixel );

        _constantBuffer = storm::Buffer::create(
            gpuContext,
            {
                sizeof(Transformations),
                storm::ResourceType::Dynamic
            });

        vertexShader->setValue( "transformations", _constantBuffer );
        pixelShader->setValue( "colorTexture", _texture );
        pixelShader->setValue( "colorTexture", _sampler );

        _renderingSystem->setShader( vertexShader );
        _renderingSystem->setShader( pixelShader );
    }

    void installCamera() {
        const storm::Vector cameraPosition( 2.0f, 1.5f, 2.0f );
        const storm::Vector cameraTarget( 0.f, 0.f, 0.f );

        storm::PerspectiveCamera camera;
        camera.setFrameAspectRatio( _frameDimensions.getAspectRatio() );
        camera.move( cameraPosition );
        camera.pointAt( cameraTarget );

        _transformations.viewProjection =
            camera.getViewTransformation() *
            camera.getProjectionTransformation();
    }

    storm::RenderingSystem::Pointer _renderingSystem;

    struct Transformations {
        storm::Matrix viewProjection;
        storm::Matrix world;
    } _transformations;

    storm::Dimensions _frameDimensions = {640, 480};

    storm::Texture::Pointer _colorBufferTexture;

    storm::Mesh::Pointer _mesh;
    storm::Texture::Pointer _texture;
    storm::Sampler::Pointer _sampler;

    storm::Buffer::Pointer _constantBuffer;

    std::chrono::steady_clock::time_point _timePoint;

    float _meshRotationAngle = 0;

    std::shared_ptr<storm::WindowObserver> _observer;
};

std::unique_ptr<ExampleBase> createExample( storm::Window::Pointer window ) {
    return std::make_unique<Example>( std::move(window) );
}
