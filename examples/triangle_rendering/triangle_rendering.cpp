#include <array>
#include <iostream>

#include <storm/storm.h>

#ifdef _WIN32
    #include <windows.h>
#endif

class Demo {
public:
    Demo() {
        storm::RenderingWindow *renderingWindow =
            storm::RenderingWindow::getInstance();
        renderingWindow->setWindowed( {640, 480} );

        _vertexShader = storm::Shader::load(
            "vertex_shader.glsl", storm::Shader::Type::Vertex );
        _pixelShader = storm::Shader::load(
            "pixel_shader.glsl", storm::Shader::Type::Pixel );

        createMesh();
    }

    void render() const {
        storm::RenderingSystem *renderingSystem =
            storm::RenderingSystem::getInstance();

        renderingSystem->beginFrameRendering();

        renderingSystem->setShader( _vertexShader );
        renderingSystem->setShader( _pixelShader );
        renderingSystem->renderMesh( _mesh );

        renderingSystem->endFrameRendering();
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

void demoMain() {
    Demo demo;

    storm::Framework *framework = storm::Framework::getInstance();
    framework->run( [&demo]() {
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
