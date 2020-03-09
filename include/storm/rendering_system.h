#pragma once

#include <string>

#include <storm/backbuffer.h>
#include <storm/color.h>
#include <storm/framebuffer.h>
#include <storm/mesh.h>
#include <storm/pipeline_state.h>
#include <storm/rectangle.h>
#include <storm/shader.h>
#include <storm/window.h>

namespace storm {

class RenderingSystem {
public:
    static RenderingSystem* getInstance();

    virtual ~RenderingSystem() = default;

    virtual Window::Pointer getOutputWindow() const = 0;
    virtual void setOutputWindow( Window::Pointer window ) = 0;

    // By default V-sync is enabled unless video driver overrides application
    // settings.
    virtual bool isVsyncEnabled() const = 0;
    virtual void setVsyncEnabled( bool enabled ) = 0;

    virtual void renderMesh( Mesh::Pointer mesh, unsigned count = 1 ) = 0;
    virtual void renderGenerated(
        unsigned int vertexCount, Mesh::PrimitiveTopology ) = 0;

    virtual Shader::Pointer getShader( Shader::Type ) const = 0;
    virtual void setShader( Shader::Pointer ) = 0;
    virtual void resetShader( Shader::Type ) = 0;

    virtual size_t getRootBufferSize() const = 0;
    virtual void setRootBufferData( size_t offset, size_t size, const void *data ) = 0;

    virtual PipelineState::Pointer getPipelineState() const = 0;
    virtual void setPipelineState( PipelineState::Pointer ) = 0;

    virtual const Rectangle& getClippingRectangle() const = 0;
    virtual const Rectangle& getOutputRectangle() const = 0;

    virtual void setClippingRectangle( const Rectangle& ) = 0;
    virtual void setOutputRectangle( const Rectangle& ) = 0;

    virtual Framebuffer::Pointer getFramebuffer() const = 0;
    virtual void setFramebuffer( Framebuffer::Pointer, bool preserveOutputRectangle = false ) = 0;

    virtual void clearColorBuffer( const Color &color = Color::Black ) = 0;
    virtual void clearDepthBuffer( float depth = 1.0f ) = 0;
    virtual void clearStencilBuffer( unsigned int stencil = 0 ) = 0;

    virtual Backbuffer::Pointer getBackbuffer() const = 0;
    virtual void presentBackbuffer() = 0;

    virtual std::string getDebugMessageLog() const = 0;
};

}
