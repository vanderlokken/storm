#include <iostream>

#include <storm/camera.h>
#include <storm/clock.h>
#include <storm/event_loop.h>
#include <storm/exception.h>
#include <storm/matrix.h>
#include <storm/quaternion.h>
#include <storm/rendering_system.h>
#include <storm/rendering_window.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "resources.h"

class Demo {
public:
    Demo() : _frameDimensions( 640, 480 ), _meshRotationAngle( 0 ) {
        storm::RenderingWindow::getInstance()->setWindowed( _frameDimensions );

        _mesh = createTexturedCubeMesh();
        _texture = createCheckboardPatternTexture();
        _sampler = createCheckboardPatternSampler();

        installFramebuffer();
        installShaders();
        installCamera();
    }

    void update() {
        storm::Clock *clock = storm::Clock::getInstance();

        clock->update();

        const float rotationSpeed = 0.001f;
        _meshRotationAngle += clock->getTimeChange() * rotationSpeed;

        const storm::Quaternion rotationQuaternion =
            storm::Quaternion::fromAxisAngle( {0, 1, 0}, _meshRotationAngle ) *
            storm::Quaternion::fromAxisAngle( {1, 0, 0}, _meshRotationAngle );

        _transformations.world = rotationQuaternion.toRotationMatrix();
        _constantBuffer->setData( &_transformations );
    }

    void render() const {
        storm::RenderingSystem *renderingSystem =
            storm::RenderingSystem::getInstance();

        renderingSystem->beginFrameRendering();

        renderingSystem->clearColorBuffer();
        renderingSystem->clearDepthBuffer();

        renderingSystem->renderMesh( _mesh );

        renderingSystem->endFrameRendering();

        renderingSystem->getBackbuffer()->renderTexture( _colorBufferTexture );
    }

private:
    void installFramebuffer() {
        const unsigned int texelSamples = 1;

        storm::Framebuffer::Pointer framebuffer = storm::Framebuffer::create(
            _frameDimensions, texelSamples, {
                storm::Texture::Format::ArgbUint8,
                storm::Texture::Format::DepthUint24
            });

        storm::RenderingSystem::getInstance()->setFramebuffer( framebuffer );

        _colorBufferTexture =
            framebuffer->getDescription().buffers[0].texture;
    }

    void installShaders() {
        const storm::Shader::Pointer vertexShader = storm::Shader::load(
            "vertex_shader.glsl", storm::Shader::Type::Vertex );
        const storm::Shader::Pointer pixelShader = storm::Shader::load(
            "pixel_shader.glsl", storm::Shader::Type::Pixel );

        _constantBuffer = storm::Buffer::create(
            {sizeof(Transformations), 1, storm::ResourceType::Dynamic} );

        vertexShader->setValue( "transformations", _constantBuffer );
        pixelShader->setValue( "colorTexture", _texture );
        pixelShader->setValue( "colorTexture", _sampler );

        storm::RenderingSystem::getInstance()->setShader( vertexShader );
        storm::RenderingSystem::getInstance()->setShader( pixelShader );
    }

    void installCamera() {
        const storm::Vector cameraPosition( 2.0, 1.5, 2.0 );
        const storm::Vector cameraTarget( 0, 0, 0 );

        storm::PerspectiveCamera camera;
        camera.setPosition( cameraPosition );
        camera.setTarget( cameraTarget );
        camera.setFrameDimensions( _frameDimensions );

        _transformations.viewProjection = camera.getViewTransformation() *
            camera.getProjectionTransformation();
    }

    struct Transformations {
        storm::Matrix viewProjection;
        storm::Matrix world;
    } _transformations;

    storm::Dimensions _frameDimensions;

    storm::Texture::Pointer _colorBufferTexture;

    storm::Mesh::Pointer _mesh;
    storm::Texture::Pointer _texture;
    storm::Sampler::Pointer _sampler;

    storm::Buffer::Pointer _constantBuffer;

    float _meshRotationAngle;
};

void demoMain() {
    Demo demo;

    storm::EventLoop *eventLoop = storm::EventLoop::getInstance();
    eventLoop->run( [&demo]() {
        demo.update();
        demo.render();
    });
}

#ifdef _WIN32

int CALLBACK WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
    try {
        demoMain();
    } catch( storm::Exception &exception ) {
        ::MessageBoxA( 0, exception.what(), "storm", MB_ICONERROR );
    }
}

#else

int main() {
    try {
        demoMain();
    } catch( storm::Exception &exception ) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}

#endif
