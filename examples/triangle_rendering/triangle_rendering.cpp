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
    explicit Example( storm::Window::Pointer window ) {
        window->setWindowedMode( {640, 480} );

        storm::RenderingSystem::getInstance()->setOutputWindow(
            std::move(window) );

        _vertexShader = storm::Shader::create(
            vertexShaderSource, storm::Shader::Type::Vertex );
        _pixelShader = storm::Shader::create(
            pixelShaderSource, storm::Shader::Type::Pixel );

        createMesh();
    }

    virtual void update() {}

    virtual void render() {
        storm::RenderingSystem *renderingSystem =
            storm::RenderingSystem::getInstance();

        renderingSystem->setShader( _vertexShader );
        renderingSystem->setShader( _pixelShader );
        renderingSystem->renderMesh( _mesh );

        renderingSystem->presentBackbuffer();
    }

private:
    void createMesh() {
        const std::array<storm::PositionedVertex, 3> vertices = {
            storm::Vector(-0.5f, -0.5f, 0.0f),
            storm::Vector( 0.0f,  0.5f, 0.0f),
            storm::Vector( 0.5f, -0.5f, 0.0f)
        };
        const std::array<uint16_t, 3> indices = { 0, 1, 2 };

        storm::Mesh::Description meshDescription;
        meshDescription.vertexBuffer = storm::Buffer::create( vertices );
        meshDescription.indexBuffer = storm::Buffer::create( indices );
        meshDescription.vertexFormat = storm::PositionedVertex::getFormat();
        meshDescription.primitiveTopology =
            storm::Mesh::PrimitiveTopology::TriangleStrip;

        _mesh = storm::Mesh::create( meshDescription );
    }

    storm::Mesh::Pointer _mesh;
    storm::Shader::Pointer _vertexShader;
    storm::Shader::Pointer _pixelShader;
};

std::unique_ptr<ExampleBase> createExample( storm::Window::Pointer window ) {
    return std::make_unique<Example>( std::move(window) );
}
