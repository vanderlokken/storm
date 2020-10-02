#include <array>

#include <storm/storm.h>

#include "../example_base.h"

const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec4 position;
void main() {
    gl_Position = position;
}
)";

const char *pixelShaderSource = R"(
#version 330 core
out vec4 color;
void main() {
    color = vec4( 1.0 );
}
)";

class Example : public ExampleBase {
public:
    explicit Example( storm::Window::Pointer window ) :
        _renderingSystem( storm::RenderingSystem::create() )
    {
        const storm::Dimensions outputWindowDimensions( 640, 480 );

        window->setWindowedMode( outputWindowDimensions );

        _renderingSystem->setOutputWindow( std::move(window) );
        _renderingSystem->setOutputRectangle(
            storm::Rectangle(
                0,
                0,
                outputWindowDimensions.width,
                outputWindowDimensions.height) );

        const storm::GpuContext::Pointer gpuContext =
            _renderingSystem->getGpuContext();

        _vertexShader = storm::Shader::create(
            gpuContext, vertexShaderSource, storm::Shader::Type::Vertex );
        _pixelShader = storm::Shader::create(
            gpuContext, pixelShaderSource, storm::Shader::Type::Pixel );

        createMesh( gpuContext );
    }

    void update() override {}

    void render() override {
        _renderingSystem->setShader( _vertexShader );
        _renderingSystem->setShader( _pixelShader );
        _renderingSystem->renderMesh( _mesh );

        _renderingSystem->presentBackbuffer();
    }

private:
    void createMesh( storm::GpuContext::Pointer gpuContext ) {
        const std::array<storm::PositionedVertex, 3> vertices = {
            storm::Vector(-0.5f, -0.5f, 0.0f),
            storm::Vector( 0.0f,  0.5f, 0.0f),
            storm::Vector( 0.5f, -0.5f, 0.0f)
        };
        const std::array<uint16_t, 3> indices = { 0, 1, 2 };

        storm::Mesh::Description meshDescription;
        meshDescription.vertexBuffer =
            storm::Buffer::create( gpuContext, vertices );
        meshDescription.indexBuffer =
            storm::Buffer::create( gpuContext, indices );
        meshDescription.vertexFormat =
            storm::PositionedVertex::getFormat();
        meshDescription.primitiveTopology =
            storm::Mesh::PrimitiveTopology::TriangleStrip;
        meshDescription.indexSize = sizeof( indices.front() );

        _mesh = storm::Mesh::create( gpuContext, meshDescription );
    }

    storm::RenderingSystem::Pointer _renderingSystem;

    storm::Mesh::Pointer _mesh;
    storm::Shader::Pointer _vertexShader;
    storm::Shader::Pointer _pixelShader;
};

std::unique_ptr<ExampleBase> createExample( storm::Window::Pointer window ) {
    return std::make_unique<Example>( std::move(window) );
}
