#include <array>
#include <cstdint>

#include <storm/camera.h>
#include <storm/clock.h>
#include <storm/exception.h>
#include <storm/framework.h>
#include <storm/matrix.h>
#include <storm/quaternion.h>
#include <storm/rendering_system.h>
#include <storm/rendering_window.h>

#include <windows.h>

#include "resources.h"

class Demo {
public:
    Demo() : _frameDimensions( 640, 480 ), _meshRotationAngle( 0 ) {
        storm::RenderingWindow::getInstance()->setWindowed( _frameDimensions );

        _mesh = createTexturedCubeMesh();
        _texture = createCheckboardPatternTexture();
        _sampler = createCheckboardPatternSampler();

        installRenderingBufferSet();
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
    void installRenderingBufferSet() {
        storm::Texture::Description textureDescription;
        textureDescription.layout = storm::Texture::Layout::Separate2d;
        textureDescription.width = _frameDimensions.width;
        textureDescription.height = _frameDimensions.height;
        textureDescription.depth = 1;
        textureDescription.mipLevels = 1;
        textureDescription.texelSamples = 1;
        textureDescription.resourceType = storm::ResourceType::Dynamic;

        textureDescription.format = storm::Texture::Format::ArgbUint8;
        _colorBufferTexture = storm::Texture::create( textureDescription );

        textureDescription.format = storm::Texture::Format::DepthUint24;
        _depthBufferTexture = storm::Texture::create( textureDescription );

        storm::RenderingBufferSet::Description description;
        description.colorBuffers.resize( 1 );
        description.colorBuffers.back().texture = _colorBufferTexture;
        description.colorBuffers.back().mipLevel = 0;
        description.colorBuffers.back().layer = 0;
        description.depthStencilBuffer.texture = _depthBufferTexture;
        description.depthStencilBuffer.mipLevel = 0;
        description.depthStencilBuffer.layer = 0;

        storm::RenderingSystem::getInstance()->setRenderingBufferSet(
            storm::RenderingBufferSet::create(description) );
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
    storm::Texture::Pointer _depthBufferTexture;

    storm::Mesh::Pointer _mesh;
    storm::Texture::Pointer _texture;
    storm::Sampler::Pointer _sampler;

    storm::Buffer::Pointer _constantBuffer;

    float _meshRotationAngle;
};

int CALLBACK WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
    try {
        Demo demo;

        storm::Framework *framework = storm::Framework::getInstance();
        framework->run( [&demo]() {
            demo.update();
            demo.render();
        });

    } catch( storm::Exception &exception ) {
        ::MessageBoxA( 0, exception.what(), "storm", MB_ICONERROR );
    }
}
