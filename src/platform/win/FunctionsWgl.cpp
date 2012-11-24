#include "platform/ogl/FunctionsOgl.h"

#include "Exception.h"
#include "RenderingSystemWgl.h"

PROC getCoreFunctionAddress( const char *functionName ) {
    static const HMODULE library = ::GetModuleHandle( L"opengl32.dll" );
    
    PROC address = ::GetProcAddress( library, functionName );
    return address;
}

PROC getExtensionFunctionAddress( const char *functionName ) {
    // This call is required to be sure that the OpenGL rendering context is created
    storm::RenderingSystemWgl::getInstance();
    
    PROC address = ::wglGetProcAddress( functionName );
    return address;
}

PROC getFunctionAddress( const char *functionName ) {
    PROC coreFunctionAddress = getCoreFunctionAddress( functionName );
    
    if( coreFunctionAddress )
        return coreFunctionAddress;
    
    return getExtensionFunctionAddress( functionName );
}

#define DECLARE( functionName ) \
    static const Pointer pointer = reinterpret_cast< Pointer >( getFunctionAddress(functionName) ); \
    if( !pointer ) storm::throwRuntimeError( "Function is unavailable" );

void glCullFace( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glCullFace" );
    return pointer( mode );
}

void glFrontFace( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glFrontFace" );
    return pointer( mode );
}

void glHint( GLenum target, GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glHint" );
    return pointer( target, mode );
}

void glLineWidth( GLfloat width ) {
    typedef void (__stdcall * Pointer)( GLfloat );
    DECLARE( "glLineWidth" );
    return pointer( width );
}

void glPointSize( GLfloat size ) {
    typedef void (__stdcall * Pointer)( GLfloat );
    DECLARE( "glPointSize" );
    return pointer( size );
}

void glPolygonMode( GLenum face, GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glPolygonMode" );
    return pointer( face, mode );
}

void glScissor( GLint x, GLint y, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLsizei, GLsizei );
    DECLARE( "glScissor" );
    return pointer( x, y, width, height );
}

void glTexParameterf( GLenum target, GLenum pname, GLfloat param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLfloat );
    DECLARE( "glTexParameterf" );
    return pointer( target, pname, param );
}

void glTexParameterfv( GLenum target, GLenum pname, const GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLfloat* );
    DECLARE( "glTexParameterfv" );
    return pointer( target, pname, params );
}

void glTexParameteri( GLenum target, GLenum pname, GLint param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint );
    DECLARE( "glTexParameteri" );
    return pointer( target, pname, param );
}

void glTexParameteriv( GLenum target, GLenum pname, const GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLint* );
    DECLARE( "glTexParameteriv" );
    return pointer( target, pname, params );
}

void glTexImage1D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexImage1D" );
    return pointer( target, level, internalformat, width, border, format, type, pixels );
}

void glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexImage2D" );
    return pointer( target, level, internalformat, width, height, border, format, type, pixels );
}

void glDrawBuffer( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glDrawBuffer" );
    return pointer( mode );
}

void glClear( GLbitfield mask ) {
    typedef void (__stdcall * Pointer)( GLbitfield );
    DECLARE( "glClear" );
    return pointer( mask );
}

void glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) {
    typedef void (__stdcall * Pointer)( GLclampf, GLclampf, GLclampf, GLclampf );
    DECLARE( "glClearColor" );
    return pointer( red, green, blue, alpha );
}

void glClearStencil( GLint s ) {
    typedef void (__stdcall * Pointer)( GLint );
    DECLARE( "glClearStencil" );
    return pointer( s );
}

void glClearDepth( GLclampd depth ) {
    typedef void (__stdcall * Pointer)( GLclampd );
    DECLARE( "glClearDepth" );
    return pointer( depth );
}

void glStencilMask( GLuint mask ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glStencilMask" );
    return pointer( mask );
}

void glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha ) {
    typedef void (__stdcall * Pointer)( GLboolean, GLboolean, GLboolean, GLboolean );
    DECLARE( "glColorMask" );
    return pointer( red, green, blue, alpha );
}

void glDepthMask( GLboolean flag ) {
    typedef void (__stdcall * Pointer)( GLboolean );
    DECLARE( "glDepthMask" );
    return pointer( flag );
}

void glDisable( GLenum cap ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glDisable" );
    return pointer( cap );
}

void glEnable( GLenum cap ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glEnable" );
    return pointer( cap );
}

void glFinish( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glFinish" );
    return pointer( );
}

void glFlush( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glFlush" );
    return pointer( );
}

void glBlendFunc( GLenum sfactor, GLenum dfactor ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glBlendFunc" );
    return pointer( sfactor, dfactor );
}

void glLogicOp( GLenum opcode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glLogicOp" );
    return pointer( opcode );
}

void glStencilFunc( GLenum func, GLint ref, GLuint mask ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLuint );
    DECLARE( "glStencilFunc" );
    return pointer( func, ref, mask );
}

void glStencilOp( GLenum fail, GLenum zfail, GLenum zpass ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum );
    DECLARE( "glStencilOp" );
    return pointer( fail, zfail, zpass );
}

void glDepthFunc( GLenum func ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glDepthFunc" );
    return pointer( func );
}

void glPixelStoref( GLenum pname, GLfloat param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLfloat );
    DECLARE( "glPixelStoref" );
    return pointer( pname, param );
}

void glPixelStorei( GLenum pname, GLint param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint );
    DECLARE( "glPixelStorei" );
    return pointer( pname, param );
}

void glReadBuffer( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glReadBuffer" );
    return pointer( mode );
}

void glReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid* );
    DECLARE( "glReadPixels" );
    return pointer( x, y, width, height, format, type, pixels );
}

void glGetBooleanv( GLenum pname, GLboolean *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLboolean* );
    DECLARE( "glGetBooleanv" );
    return pointer( pname, params );
}

void glGetDoublev( GLenum pname, GLdouble *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLdouble* );
    DECLARE( "glGetDoublev" );
    return pointer( pname, params );
}

GLenum glGetError( void ) {
    typedef GLenum (__stdcall * Pointer)( void );
    DECLARE( "glGetError" );
    return pointer( );
}

void glGetFloatv( GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLfloat* );
    DECLARE( "glGetFloatv" );
    return pointer( pname, params );
}

void glGetIntegerv( GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint* );
    DECLARE( "glGetIntegerv" );
    return pointer( pname, params );
}

const GLubyte* glGetString( GLenum name ) {
    typedef const GLubyte* (__stdcall * Pointer)( GLenum );
    DECLARE( "GLubyte * glGetString" );
    return pointer( name );
}

void glGetTexImage( GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLenum, GLvoid* );
    DECLARE( "glGetTexImage" );
    return pointer( target, level, format, type, pixels );
}

void glGetTexParameterfv( GLenum target, GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLfloat* );
    DECLARE( "glGetTexParameterfv" );
    return pointer( target, pname, params );
}

void glGetTexParameteriv( GLenum target, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint* );
    DECLARE( "glGetTexParameteriv" );
    return pointer( target, pname, params );
}

void glGetTexLevelParameterfv( GLenum target, GLint level, GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLfloat* );
    DECLARE( "glGetTexLevelParameterfv" );
    return pointer( target, level, pname, params );
}

void glGetTexLevelParameteriv( GLenum target, GLint level, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLint* );
    DECLARE( "glGetTexLevelParameteriv" );
    return pointer( target, level, pname, params );
}

GLboolean glIsEnabled( GLenum cap ) {
    typedef GLboolean (__stdcall * Pointer)( GLenum );
    DECLARE( "glIsEnabled" );
    return pointer( cap );
}

void glDepthRange( GLclampd nearZ, GLclampd farZ ) {
    typedef void (__stdcall * Pointer)( GLclampd, GLclampd );
    DECLARE( "glDepthRange" );
    return pointer( nearZ, farZ );
}

void glViewport( GLint x, GLint y, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLsizei, GLsizei );
    DECLARE( "glViewport" );
    return pointer( x, y, width, height );
}

void glDrawArrays( GLenum mode, GLint first, GLsizei count ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLsizei );
    DECLARE( "glDrawArrays" );
    return pointer( mode, first, count );
}

void glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLenum, const GLvoid* );
    DECLARE( "glDrawElements" );
    return pointer( mode, count, type, indices );
}

void glGetPointerv( GLenum pname, GLvoid* *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLvoid** );
    DECLARE( "glGetPointerv" );
    return pointer( pname, params );
}

void glPolygonOffset( GLfloat factor, GLfloat units ) {
    typedef void (__stdcall * Pointer)( GLfloat, GLfloat );
    DECLARE( "glPolygonOffset" );
    return pointer( factor, units );
}

void glCopyTexImage1D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint );
    DECLARE( "glCopyTexImage1D" );
    return pointer( target, level, internalformat, x, y, width, border );
}

void glCopyTexImage2D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint );
    DECLARE( "glCopyTexImage2D" );
    return pointer( target, level, internalformat, x, y, width, height, border );
}

void glCopyTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLint, GLsizei );
    DECLARE( "glCopyTexSubImage1D" );
    return pointer( target, level, xoffset, x, y, width );
}

void glCopyTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei );
    DECLARE( "glCopyTexSubImage2D" );
    return pointer( target, level, xoffset, yoffset, x, y, width, height );
}

void glTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexSubImage1D" );
    return pointer( target, level, xoffset, width, format, type, pixels );
}

void glTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexSubImage2D" );
    return pointer( target, level, xoffset, yoffset, width, height, format, type, pixels );
}

void glBindTexture( GLenum target, GLuint texture ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindTexture" );
    return pointer( target, texture );
}

void glDeleteTextures( GLsizei n, const GLuint *textures ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteTextures" );
    return pointer( n, textures );
}

void glGenTextures( GLsizei n, GLuint *textures ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenTextures" );
    return pointer( n, textures );
}

GLboolean glIsTexture( GLuint texture ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsTexture" );
    return pointer( texture );
}

void glBlendColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) {
    typedef void (__stdcall * Pointer)( GLclampf, GLclampf, GLclampf, GLclampf );
    DECLARE( "glBlendColor" );
    return pointer( red, green, blue, alpha );
}

void glBlendEquation( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glBlendEquation" );
    return pointer( mode );
}

void glDrawRangeElements( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid* );
    DECLARE( "glDrawRangeElements" );
    return pointer( mode, start, end, count, type, indices );
}

void glTexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexImage3D" );
    return pointer( target, level, internalformat, width, height, depth, border, format, type, pixels );
}

void glTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid* );
    DECLARE( "glTexSubImage3D" );
    return pointer( target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels );
}

void glCopyTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei );
    DECLARE( "glCopyTexSubImage3D" );
    return pointer( target, level, xoffset, yoffset, zoffset, x, y, width, height );
}

void glActiveTexture( GLenum texture ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glActiveTexture" );
    return pointer( texture );
}

void glSampleCoverage( GLclampf value, GLboolean invert ) {
    typedef void (__stdcall * Pointer)( GLclampf, GLboolean );
    DECLARE( "glSampleCoverage" );
    return pointer( value, invert );
}

void glCompressedTexImage3D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexImage3D" );
    return pointer( target, level, internalformat, width, height, depth, border, imageSize, data );
}

void glCompressedTexImage2D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexImage2D" );
    return pointer( target, level, internalformat, width, height, border, imageSize, data );
}

void glCompressedTexImage1D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexImage1D" );
    return pointer( target, level, internalformat, width, border, imageSize, data );
}

void glCompressedTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexSubImage3D" );
    return pointer( target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data );
}

void glCompressedTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexSubImage2D" );
    return pointer( target, level, xoffset, yoffset, width, height, format, imageSize, data );
}

void glCompressedTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const GLvoid* );
    DECLARE( "glCompressedTexSubImage1D" );
    return pointer( target, level, xoffset, width, format, imageSize, data );
}

void glGetCompressedTexImage( GLenum target, GLint level, GLvoid *img ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLvoid* );
    DECLARE( "glGetCompressedTexImage" );
    return pointer( target, level, img );
}

void glBlendFuncSeparate( GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLenum );
    DECLARE( "glBlendFuncSeparate" );
    return pointer( sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha );
}

void glMultiDrawArrays( GLenum mode, GLint *first, GLsizei *count, GLsizei primcount ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint*, GLsizei*, GLsizei );
    DECLARE( "glMultiDrawArrays" );
    return pointer( mode, first, count, primcount );
}

void glMultiDrawElements( GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLsizei*, GLenum, const GLvoid**, GLsizei );
    DECLARE( "glMultiDrawElements" );
    return pointer( mode, count, type, indices, primcount );
}

void glPointParameterf( GLenum pname, GLfloat param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLfloat );
    DECLARE( "glPointParameterf" );
    return pointer( pname, param );
}

void glPointParameterfv( GLenum pname, const GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLfloat* );
    DECLARE( "glPointParameterfv" );
    return pointer( pname, params );
}

void glPointParameteri( GLenum pname, GLint param ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint );
    DECLARE( "glPointParameteri" );
    return pointer( pname, param );
}

void glPointParameteriv( GLenum pname, const GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLint* );
    DECLARE( "glPointParameteriv" );
    return pointer( pname, params );
}

void glGenQueries( GLsizei n, GLuint *ids ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenQueries" );
    return pointer( n, ids );
}

void glDeleteQueries( GLsizei n, const GLuint *ids ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteQueries" );
    return pointer( n, ids );
}

GLboolean glIsQuery( GLuint id ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsQuery" );
    return pointer( id );
}

void glBeginQuery( GLenum target, GLuint id ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBeginQuery" );
    return pointer( target, id );
}

void glEndQuery( GLenum target ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glEndQuery" );
    return pointer( target );
}

void glGetQueryiv( GLenum target, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint* );
    DECLARE( "glGetQueryiv" );
    return pointer( target, pname, params );
}

void glGetQueryObjectiv( GLuint id, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetQueryObjectiv" );
    return pointer( id, pname, params );
}

void glGetQueryObjectuiv( GLuint id, GLenum pname, GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint* );
    DECLARE( "glGetQueryObjectuiv" );
    return pointer( id, pname, params );
}

void glBindBuffer( GLenum target, GLuint buffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindBuffer" );
    return pointer( target, buffer );
}

void glDeleteBuffers( GLsizei n, const GLuint *buffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteBuffers" );
    return pointer( n, buffers );
}

void glGenBuffers( GLsizei n, GLuint *buffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenBuffers" );
    return pointer( n, buffers );
}

GLboolean glIsBuffer( GLuint buffer ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsBuffer" );
    return pointer( buffer );
}

void glBufferData( GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizeiptr, const GLvoid*, GLenum );
    DECLARE( "glBufferData" );
    return pointer( target, size, data, usage );
}

void glBufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLintptr, GLsizeiptr, const GLvoid* );
    DECLARE( "glBufferSubData" );
    return pointer( target, offset, size, data );
}

void glGetBufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLintptr, GLsizeiptr, GLvoid* );
    DECLARE( "glGetBufferSubData" );
    return pointer( target, offset, size, data );
}

GLvoid* glMapBuffer( GLenum target, GLenum access ) {
    typedef GLvoid* (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glMapBuffer" );
    return pointer( target, access );
}

GLboolean glUnmapBuffer( GLenum target ) {
    typedef GLboolean (__stdcall * Pointer)( GLenum );
    DECLARE( "glUnmapBuffer" );
    return pointer( target );
}

void glGetBufferParameteriv( GLenum target, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint* );
    DECLARE( "glGetBufferParameteriv" );
    return pointer( target, pname, params );
}

void glGetBufferPointerv( GLenum target, GLenum pname, GLvoid* *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLvoid** );
    DECLARE( "glGetBufferPointerv" );
    return pointer( target, pname, params );
}

void glBlendEquationSeparate( GLenum modeRGB, GLenum modeAlpha ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glBlendEquationSeparate" );
    return pointer( modeRGB, modeAlpha );
}

void glDrawBuffers( GLsizei n, const GLenum *bufs ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLenum* );
    DECLARE( "glDrawBuffers" );
    return pointer( n, bufs );
}

void glStencilOpSeparate( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLenum );
    DECLARE( "glStencilOpSeparate" );
    return pointer( face, sfail, dpfail, dppass );
}

void glStencilFuncSeparate( GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint, GLuint );
    DECLARE( "glStencilFuncSeparate" );
    return pointer( frontfunc, backfunc, ref, mask );
}

void glStencilMaskSeparate( GLenum face, GLuint mask ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glStencilMaskSeparate" );
    return pointer( face, mask );
}

void glAttachShader( GLuint program, GLuint shader ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint );
    DECLARE( "glAttachShader" );
    return pointer( program, shader );
}

void glBindAttribLocation( GLuint program, GLuint index, const GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, const GLchar* );
    DECLARE( "glBindAttribLocation" );
    return pointer( program, index, name );
}

void glCompileShader( GLuint shader ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glCompileShader" );
    return pointer( shader );
}

GLuint glCreateProgram( void ) {
    typedef GLuint (__stdcall * Pointer)( void );
    DECLARE( "glCreateProgram" );
    return pointer( );
}

GLuint glCreateShader( GLenum type ) {
    typedef GLuint (__stdcall * Pointer)( GLenum );
    DECLARE( "glCreateShader" );
    return pointer( type );
}

void glDeleteProgram( GLuint program ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glDeleteProgram" );
    return pointer( program );
}

void glDeleteShader( GLuint shader ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glDeleteShader" );
    return pointer( shader );
}

void glDetachShader( GLuint program, GLuint shader ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint );
    DECLARE( "glDetachShader" );
    return pointer( program, shader );
}

void glDisableVertexAttribArray( GLuint index ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glDisableVertexAttribArray" );
    return pointer( index );
}

void glEnableVertexAttribArray( GLuint index ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glEnableVertexAttribArray" );
    return pointer( index );
}

void glGetActiveAttrib( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar* );
    DECLARE( "glGetActiveAttrib" );
    return pointer( program, index, bufSize, length, size, type, name );
}

void glGetActiveUniform( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar* );
    DECLARE( "glGetActiveUniform" );
    return pointer( program, index, bufSize, length, size, type, name );
}

void glGetAttachedShaders( GLuint program, GLsizei maxCount, GLsizei *count, GLuint *obj ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, GLsizei*, GLuint* );
    DECLARE( "glGetAttachedShaders" );
    return pointer( program, maxCount, count, obj );
}

GLint glGetAttribLocation( GLuint program, const GLchar *name ) {
    typedef GLint (__stdcall * Pointer)( GLuint, const GLchar* );
    DECLARE( "glGetAttribLocation" );
    return pointer( program, name );
}

void glGetProgramiv( GLuint program, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetProgramiv" );
    return pointer( program, pname, params );
}

void glGetProgramInfoLog( GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetProgramInfoLog" );
    return pointer( program, bufSize, length, infoLog );
}

void glGetShaderiv( GLuint shader, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetShaderiv" );
    return pointer( shader, pname, params );
}

void glGetShaderInfoLog( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetShaderInfoLog" );
    return pointer( shader, bufSize, length, infoLog );
}

void glGetShaderSource( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetShaderSource" );
    return pointer( shader, bufSize, length, source );
}

GLint glGetUniformLocation( GLuint program, const GLchar *name ) {
    typedef GLint (__stdcall * Pointer)( GLuint, const GLchar* );
    DECLARE( "glGetUniformLocation" );
    return pointer( program, name );
}

void glGetUniformfv( GLuint program, GLint location, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLfloat* );
    DECLARE( "glGetUniformfv" );
    return pointer( program, location, params );
}

void glGetUniformiv( GLuint program, GLint location, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLint* );
    DECLARE( "glGetUniformiv" );
    return pointer( program, location, params );
}

void glGetVertexAttribdv( GLuint index, GLenum pname, GLdouble *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLdouble* );
    DECLARE( "glGetVertexAttribdv" );
    return pointer( index, pname, params );
}

void glGetVertexAttribfv( GLuint index, GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLfloat* );
    DECLARE( "glGetVertexAttribfv" );
    return pointer( index, pname, params );
}

void glGetVertexAttribiv( GLuint index, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetVertexAttribiv" );
    return pointer( index, pname, params );
}

void glGetVertexAttribPointerv( GLuint index, GLenum pname, GLvoid* *ptr ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLvoid** );
    DECLARE( "glGetVertexAttribPointerv" );
    return pointer( index, pname, ptr );
}

GLboolean glIsProgram( GLuint program ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsProgram" );
    return pointer( program );
}

GLboolean glIsShader( GLuint shader ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsShader" );
    return pointer( shader );
}

void glLinkProgram( GLuint program ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glLinkProgram" );
    return pointer( program );
}

void glShaderSource( GLuint shader, GLsizei count, const GLchar* *string, const GLint *length ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, const GLchar**, const GLint* );
    DECLARE( "glShaderSource" );
    return pointer( shader, count, string, length );
}

void glUseProgram( GLuint program ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glUseProgram" );
    return pointer( program );
}

void glUniform1f( GLint location, GLfloat v0 ) {
    typedef void (__stdcall * Pointer)( GLint, GLfloat );
    DECLARE( "glUniform1f" );
    return pointer( location, v0 );
}

void glUniform2f( GLint location, GLfloat v0, GLfloat v1 ) {
    typedef void (__stdcall * Pointer)( GLint, GLfloat, GLfloat );
    DECLARE( "glUniform2f" );
    return pointer( location, v0, v1 );
}

void glUniform3f( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 ) {
    typedef void (__stdcall * Pointer)( GLint, GLfloat, GLfloat, GLfloat );
    DECLARE( "glUniform3f" );
    return pointer( location, v0, v1, v2 );
}

void glUniform4f( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 ) {
    typedef void (__stdcall * Pointer)( GLint, GLfloat, GLfloat, GLfloat, GLfloat );
    DECLARE( "glUniform4f" );
    return pointer( location, v0, v1, v2, v3 );
}

void glUniform1i( GLint location, GLint v0 ) {
    typedef void (__stdcall * Pointer)( GLint, GLint );
    DECLARE( "glUniform1i" );
    return pointer( location, v0 );
}

void glUniform2i( GLint location, GLint v0, GLint v1 ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLint );
    DECLARE( "glUniform2i" );
    return pointer( location, v0, v1 );
}

void glUniform3i( GLint location, GLint v0, GLint v1, GLint v2 ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLint, GLint );
    DECLARE( "glUniform3i" );
    return pointer( location, v0, v1, v2 );
}

void glUniform4i( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLint, GLint, GLint );
    DECLARE( "glUniform4i" );
    return pointer( location, v0, v1, v2, v3 );
}

void glUniform1fv( GLint location, GLsizei count, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLfloat* );
    DECLARE( "glUniform1fv" );
    return pointer( location, count, value );
}

void glUniform2fv( GLint location, GLsizei count, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLfloat* );
    DECLARE( "glUniform2fv" );
    return pointer( location, count, value );
}

void glUniform3fv( GLint location, GLsizei count, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLfloat* );
    DECLARE( "glUniform3fv" );
    return pointer( location, count, value );
}

void glUniform4fv( GLint location, GLsizei count, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLfloat* );
    DECLARE( "glUniform4fv" );
    return pointer( location, count, value );
}

void glUniform1iv( GLint location, GLsizei count, const GLint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLint* );
    DECLARE( "glUniform1iv" );
    return pointer( location, count, value );
}

void glUniform2iv( GLint location, GLsizei count, const GLint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLint* );
    DECLARE( "glUniform2iv" );
    return pointer( location, count, value );
}

void glUniform3iv( GLint location, GLsizei count, const GLint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLint* );
    DECLARE( "glUniform3iv" );
    return pointer( location, count, value );
}

void glUniform4iv( GLint location, GLsizei count, const GLint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLint* );
    DECLARE( "glUniform4iv" );
    return pointer( location, count, value );
}

void glUniformMatrix2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix2fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix3fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix4fv" );
    return pointer( location, count, transpose, value );
}

void glValidateProgram( GLuint program ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glValidateProgram" );
    return pointer( program );
}

void glVertexAttrib1d( GLuint index, GLdouble x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLdouble );
    DECLARE( "glVertexAttrib1d" );
    return pointer( index, x );
}

void glVertexAttrib1dv( GLuint index, const GLdouble *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLdouble* );
    DECLARE( "glVertexAttrib1dv" );
    return pointer( index, v );
}

void glVertexAttrib1f( GLuint index, GLfloat x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLfloat );
    DECLARE( "glVertexAttrib1f" );
    return pointer( index, x );
}

void glVertexAttrib1fv( GLuint index, const GLfloat *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLfloat* );
    DECLARE( "glVertexAttrib1fv" );
    return pointer( index, v );
}

void glVertexAttrib1s( GLuint index, GLshort x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLshort );
    DECLARE( "glVertexAttrib1s" );
    return pointer( index, x );
}

void glVertexAttrib1sv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttrib1sv" );
    return pointer( index, v );
}

void glVertexAttrib2d( GLuint index, GLdouble x, GLdouble y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLdouble, GLdouble );
    DECLARE( "glVertexAttrib2d" );
    return pointer( index, x, y );
}

void glVertexAttrib2dv( GLuint index, const GLdouble *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLdouble* );
    DECLARE( "glVertexAttrib2dv" );
    return pointer( index, v );
}

void glVertexAttrib2f( GLuint index, GLfloat x, GLfloat y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLfloat, GLfloat );
    DECLARE( "glVertexAttrib2f" );
    return pointer( index, x, y );
}

void glVertexAttrib2fv( GLuint index, const GLfloat *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLfloat* );
    DECLARE( "glVertexAttrib2fv" );
    return pointer( index, v );
}

void glVertexAttrib2s( GLuint index, GLshort x, GLshort y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLshort, GLshort );
    DECLARE( "glVertexAttrib2s" );
    return pointer( index, x, y );
}

void glVertexAttrib2sv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttrib2sv" );
    return pointer( index, v );
}

void glVertexAttrib3d( GLuint index, GLdouble x, GLdouble y, GLdouble z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLdouble, GLdouble, GLdouble );
    DECLARE( "glVertexAttrib3d" );
    return pointer( index, x, y, z );
}

void glVertexAttrib3dv( GLuint index, const GLdouble *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLdouble* );
    DECLARE( "glVertexAttrib3dv" );
    return pointer( index, v );
}

void glVertexAttrib3f( GLuint index, GLfloat x, GLfloat y, GLfloat z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLfloat, GLfloat, GLfloat );
    DECLARE( "glVertexAttrib3f" );
    return pointer( index, x, y, z );
}

void glVertexAttrib3fv( GLuint index, const GLfloat *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLfloat* );
    DECLARE( "glVertexAttrib3fv" );
    return pointer( index, v );
}

void glVertexAttrib3s( GLuint index, GLshort x, GLshort y, GLshort z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLshort, GLshort, GLshort );
    DECLARE( "glVertexAttrib3s" );
    return pointer( index, x, y, z );
}

void glVertexAttrib3sv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttrib3sv" );
    return pointer( index, v );
}

void glVertexAttrib4Nbv( GLuint index, const GLbyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLbyte* );
    DECLARE( "glVertexAttrib4Nbv" );
    return pointer( index, v );
}

void glVertexAttrib4Niv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttrib4Niv" );
    return pointer( index, v );
}

void glVertexAttrib4Nsv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttrib4Nsv" );
    return pointer( index, v );
}

void glVertexAttrib4Nub( GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLubyte, GLubyte, GLubyte, GLubyte );
    DECLARE( "glVertexAttrib4Nub" );
    return pointer( index, x, y, z, w );
}

void glVertexAttrib4Nubv( GLuint index, const GLubyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLubyte* );
    DECLARE( "glVertexAttrib4Nubv" );
    return pointer( index, v );
}

void glVertexAttrib4Nuiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttrib4Nuiv" );
    return pointer( index, v );
}

void glVertexAttrib4Nusv( GLuint index, const GLushort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLushort* );
    DECLARE( "glVertexAttrib4Nusv" );
    return pointer( index, v );
}

void glVertexAttrib4bv( GLuint index, const GLbyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLbyte* );
    DECLARE( "glVertexAttrib4bv" );
    return pointer( index, v );
}

void glVertexAttrib4d( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLdouble, GLdouble, GLdouble, GLdouble );
    DECLARE( "glVertexAttrib4d" );
    return pointer( index, x, y, z, w );
}

void glVertexAttrib4dv( GLuint index, const GLdouble *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLdouble* );
    DECLARE( "glVertexAttrib4dv" );
    return pointer( index, v );
}

void glVertexAttrib4f( GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLfloat, GLfloat, GLfloat, GLfloat );
    DECLARE( "glVertexAttrib4f" );
    return pointer( index, x, y, z, w );
}

void glVertexAttrib4fv( GLuint index, const GLfloat *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLfloat* );
    DECLARE( "glVertexAttrib4fv" );
    return pointer( index, v );
}

void glVertexAttrib4iv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttrib4iv" );
    return pointer( index, v );
}

void glVertexAttrib4s( GLuint index, GLshort x, GLshort y, GLshort z, GLshort w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLshort, GLshort, GLshort, GLshort );
    DECLARE( "glVertexAttrib4s" );
    return pointer( index, x, y, z, w );
}

void glVertexAttrib4sv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttrib4sv" );
    return pointer( index, v );
}

void glVertexAttrib4ubv( GLuint index, const GLubyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLubyte* );
    DECLARE( "glVertexAttrib4ubv" );
    return pointer( index, v );
}

void glVertexAttrib4uiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttrib4uiv" );
    return pointer( index, v );
}

void glVertexAttrib4usv( GLuint index, const GLushort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLushort* );
    DECLARE( "glVertexAttrib4usv" );
    return pointer( index, v );
}

void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *ptr ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid* );
    DECLARE( "glVertexAttribPointer" );
    return pointer( index, size, type, normalized, stride, ptr );
}

void glUniformMatrix2x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix2x3fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix3x2fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix2x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix2x4fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix4x2fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix3x4fv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLfloat* );
    DECLARE( "glUniformMatrix4x3fv" );
    return pointer( location, count, transpose, value );
}

void glColorMaski( GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a ) {
    typedef void (__stdcall * Pointer)( GLuint, GLboolean, GLboolean, GLboolean, GLboolean );
    DECLARE( "glColorMaski" );
    return pointer( index, r, g, b, a );
}

void glGetBooleani_v( GLenum target, GLuint index, GLboolean *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLboolean* );
    DECLARE( "glGetBooleani_v" );
    return pointer( target, index, data );
}

void glGetIntegeri_v( GLenum target, GLuint index, GLint *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLint* );
    DECLARE( "glGetIntegeri_v" );
    return pointer( target, index, data );
}

void glEnablei( GLenum target, GLuint index ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glEnablei" );
    return pointer( target, index );
}

void glDisablei( GLenum target, GLuint index ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glDisablei" );
    return pointer( target, index );
}

GLboolean glIsEnabledi( GLenum target, GLuint index ) {
    typedef GLboolean (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glIsEnabledi" );
    return pointer( target, index );
}

void glBeginTransformFeedback( GLenum primitiveMode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glBeginTransformFeedback" );
    return pointer( primitiveMode );
}

void glEndTransformFeedback( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glEndTransformFeedback" );
    return pointer( );
}

void glBindBufferRange( GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint, GLintptr, GLsizeiptr );
    DECLARE( "glBindBufferRange" );
    return pointer( target, index, buffer, offset, size );
}

void glBindBufferBase( GLenum target, GLuint index, GLuint buffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint );
    DECLARE( "glBindBufferBase" );
    return pointer( target, index, buffer );
}

void glTransformFeedbackVaryings( GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, const GLchar**, GLenum );
    DECLARE( "glTransformFeedbackVaryings" );
    return pointer( program, count, varyings, bufferMode );
}

void glGetTransformFeedbackVarying( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar* );
    DECLARE( "glGetTransformFeedbackVarying" );
    return pointer( program, index, bufSize, length, size, type, name );
}

void glClampColor( GLenum target, GLenum clamp ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum );
    DECLARE( "glClampColor" );
    return pointer( target, clamp );
}

void glBeginConditionalRender( GLuint id, GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum );
    DECLARE( "glBeginConditionalRender" );
    return pointer( id, mode );
}

void glEndConditionalRender( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glEndConditionalRender" );
    return pointer( );
}

void glVertexAttribIPointer( GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *ptr ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLenum, GLsizei, const GLvoid* );
    DECLARE( "glVertexAttribIPointer" );
    return pointer( index, size, type, stride, ptr );
}

void glGetVertexAttribIiv( GLuint index, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetVertexAttribIiv" );
    return pointer( index, pname, params );
}

void glGetVertexAttribIuiv( GLuint index, GLenum pname, GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint* );
    DECLARE( "glGetVertexAttribIuiv" );
    return pointer( index, pname, params );
}

void glVertexAttribI1i( GLuint index, GLint x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint );
    DECLARE( "glVertexAttribI1i" );
    return pointer( index, x );
}

void glVertexAttribI2i( GLuint index, GLint x, GLint y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLint );
    DECLARE( "glVertexAttribI2i" );
    return pointer( index, x, y );
}

void glVertexAttribI3i( GLuint index, GLint x, GLint y, GLint z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLint, GLint );
    DECLARE( "glVertexAttribI3i" );
    return pointer( index, x, y, z );
}

void glVertexAttribI4i( GLuint index, GLint x, GLint y, GLint z, GLint w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLint, GLint, GLint );
    DECLARE( "glVertexAttribI4i" );
    return pointer( index, x, y, z, w );
}

void glVertexAttribI1ui( GLuint index, GLuint x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint );
    DECLARE( "glVertexAttribI1ui" );
    return pointer( index, x );
}

void glVertexAttribI2ui( GLuint index, GLuint x, GLuint y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLuint );
    DECLARE( "glVertexAttribI2ui" );
    return pointer( index, x, y );
}

void glVertexAttribI3ui( GLuint index, GLuint x, GLuint y, GLuint z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLuint, GLuint );
    DECLARE( "glVertexAttribI3ui" );
    return pointer( index, x, y, z );
}

void glVertexAttribI4ui( GLuint index, GLuint x, GLuint y, GLuint z, GLuint w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLuint, GLuint, GLuint );
    DECLARE( "glVertexAttribI4ui" );
    return pointer( index, x, y, z, w );
}

void glVertexAttribI1iv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttribI1iv" );
    return pointer( index, v );
}

void glVertexAttribI2iv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttribI2iv" );
    return pointer( index, v );
}

void glVertexAttribI3iv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttribI3iv" );
    return pointer( index, v );
}

void glVertexAttribI4iv( GLuint index, const GLint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLint* );
    DECLARE( "glVertexAttribI4iv" );
    return pointer( index, v );
}

void glVertexAttribI1uiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttribI1uiv" );
    return pointer( index, v );
}

void glVertexAttribI2uiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttribI2uiv" );
    return pointer( index, v );
}

void glVertexAttribI3uiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttribI3uiv" );
    return pointer( index, v );
}

void glVertexAttribI4uiv( GLuint index, const GLuint *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLuint* );
    DECLARE( "glVertexAttribI4uiv" );
    return pointer( index, v );
}

void glVertexAttribI4bv( GLuint index, const GLbyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLbyte* );
    DECLARE( "glVertexAttribI4bv" );
    return pointer( index, v );
}

void glVertexAttribI4sv( GLuint index, const GLshort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLshort* );
    DECLARE( "glVertexAttribI4sv" );
    return pointer( index, v );
}

void glVertexAttribI4ubv( GLuint index, const GLubyte *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLubyte* );
    DECLARE( "glVertexAttribI4ubv" );
    return pointer( index, v );
}

void glVertexAttribI4usv( GLuint index, const GLushort *v ) {
    typedef void (__stdcall * Pointer)( GLuint, const GLushort* );
    DECLARE( "glVertexAttribI4usv" );
    return pointer( index, v );
}

void glGetUniformuiv( GLuint program, GLint location, GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLuint* );
    DECLARE( "glGetUniformuiv" );
    return pointer( program, location, params );
}

void glBindFragDataLocation( GLuint program, GLuint color, const GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, const GLchar* );
    DECLARE( "glBindFragDataLocation" );
    return pointer( program, color, name );
}

GLint glGetFragDataLocation( GLuint program, const GLchar *name ) {
    typedef GLint (__stdcall * Pointer)( GLuint, const GLchar* );
    DECLARE( "glGetFragDataLocation" );
    return pointer( program, name );
}

void glUniform1ui( GLint location, GLuint v0 ) {
    typedef void (__stdcall * Pointer)( GLint, GLuint );
    DECLARE( "glUniform1ui" );
    return pointer( location, v0 );
}

void glUniform2ui( GLint location, GLuint v0, GLuint v1 ) {
    typedef void (__stdcall * Pointer)( GLint, GLuint, GLuint );
    DECLARE( "glUniform2ui" );
    return pointer( location, v0, v1 );
}

void glUniform3ui( GLint location, GLuint v0, GLuint v1, GLuint v2 ) {
    typedef void (__stdcall * Pointer)( GLint, GLuint, GLuint, GLuint );
    DECLARE( "glUniform3ui" );
    return pointer( location, v0, v1, v2 );
}

void glUniform4ui( GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 ) {
    typedef void (__stdcall * Pointer)( GLint, GLuint, GLuint, GLuint, GLuint );
    DECLARE( "glUniform4ui" );
    return pointer( location, v0, v1, v2, v3 );
}

void glUniform1uiv( GLint location, GLsizei count, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLuint* );
    DECLARE( "glUniform1uiv" );
    return pointer( location, count, value );
}

void glUniform2uiv( GLint location, GLsizei count, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLuint* );
    DECLARE( "glUniform2uiv" );
    return pointer( location, count, value );
}

void glUniform3uiv( GLint location, GLsizei count, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLuint* );
    DECLARE( "glUniform3uiv" );
    return pointer( location, count, value );
}

void glUniform4uiv( GLint location, GLsizei count, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLuint* );
    DECLARE( "glUniform4uiv" );
    return pointer( location, count, value );
}

void glTexParameterIiv( GLenum target, GLenum pname, const GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLint* );
    DECLARE( "glTexParameterIiv" );
    return pointer( target, pname, params );
}

void glTexParameterIuiv( GLenum target, GLenum pname, const GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLuint* );
    DECLARE( "glTexParameterIuiv" );
    return pointer( target, pname, params );
}

void glGetTexParameterIiv( GLenum target, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint* );
    DECLARE( "glGetTexParameterIiv" );
    return pointer( target, pname, params );
}

void glGetTexParameterIuiv( GLenum target, GLenum pname, GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint* );
    DECLARE( "glGetTexParameterIuiv" );
    return pointer( target, pname, params );
}

void glClearBufferiv( GLenum buffer, GLint drawbuffer, const GLint *value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, const GLint* );
    DECLARE( "glClearBufferiv" );
    return pointer( buffer, drawbuffer, value );
}

void glClearBufferuiv( GLenum buffer, GLint drawbuffer, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, const GLuint* );
    DECLARE( "glClearBufferuiv" );
    return pointer( buffer, drawbuffer, value );
}

void glClearBufferfv( GLenum buffer, GLint drawbuffer, const GLfloat *value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, const GLfloat* );
    DECLARE( "glClearBufferfv" );
    return pointer( buffer, drawbuffer, value );
}

void glClearBufferfi( GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLfloat, GLint );
    DECLARE( "glClearBufferfi" );
    return pointer( buffer, drawbuffer, depth, stencil );
}

const GLubyte* glGetStringi( GLenum name, GLuint index ) {
    typedef const GLubyte* (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "GLubyte * glGetStringi" );
    return pointer( name, index );
}

void glDrawArraysInstanced( GLenum mode, GLint first, GLsizei count, GLsizei primcount ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLsizei, GLsizei );
    DECLARE( "glDrawArraysInstanced" );
    return pointer( mode, first, count, primcount );
}

void glDrawElementsInstanced( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLenum, const GLvoid*, GLsizei );
    DECLARE( "glDrawElementsInstanced" );
    return pointer( mode, count, type, indices, primcount );
}

void glTexBuffer( GLenum target, GLenum internalformat, GLuint buffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint );
    DECLARE( "glTexBuffer" );
    return pointer( target, internalformat, buffer );
}

void glPrimitiveRestartIndex( GLuint index ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glPrimitiveRestartIndex" );
    return pointer( index );
}

void glGetInteger64i_v( GLenum target, GLuint index, GLint64 *data ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLint64* );
    DECLARE( "glGetInteger64i_v" );
    return pointer( target, index, data );
}

void glGetBufferParameteri64v( GLenum target, GLenum pname, GLint64 *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint64* );
    DECLARE( "glGetBufferParameteri64v" );
    return pointer( target, pname, params );
}

void glProgramParameteri( GLuint program, GLenum pname, GLint value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint );
    DECLARE( "glProgramParameteri" );
    return pointer( program, pname, value );
}

void glFramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint, GLint );
    DECLARE( "glFramebufferTexture" );
    return pointer( target, attachment, texture, level );
}

GLboolean glIsRenderbuffer( GLuint renderbuffer ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsRenderbuffer" );
    return pointer( renderbuffer );
}

void glBindRenderbuffer( GLenum target, GLuint renderbuffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindRenderbuffer" );
    return pointer( target, renderbuffer );
}

void glDeleteRenderbuffers( GLsizei n, const GLuint *renderbuffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteRenderbuffers" );
    return pointer( n, renderbuffers );
}

void glGenRenderbuffers( GLsizei n, GLuint *renderbuffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenRenderbuffers" );
    return pointer( n, renderbuffers );
}

void glRenderbufferStorage( GLenum target, GLenum internalformat, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLsizei, GLsizei );
    DECLARE( "glRenderbufferStorage" );
    return pointer( target, internalformat, width, height );
}

void glGetRenderbufferParameteriv( GLenum target, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLint* );
    DECLARE( "glGetRenderbufferParameteriv" );
    return pointer( target, pname, params );
}

GLboolean glIsFramebuffer( GLuint framebuffer ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsFramebuffer" );
    return pointer( framebuffer );
}

void glBindFramebuffer( GLenum target, GLuint framebuffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindFramebuffer" );
    return pointer( target, framebuffer );
}

void glDeleteFramebuffers( GLsizei n, const GLuint *framebuffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteFramebuffers" );
    return pointer( n, framebuffers );
}

void glGenFramebuffers( GLsizei n, GLuint *framebuffers ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenFramebuffers" );
    return pointer( n, framebuffers );
}

GLenum glCheckFramebufferStatus( GLenum target ) {
    typedef GLenum (__stdcall * Pointer)( GLenum );
    DECLARE( "glCheckFramebufferStatus" );
    return pointer( target );
}

void glFramebufferTexture1D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLuint, GLint );
    DECLARE( "glFramebufferTexture1D" );
    return pointer( target, attachment, textarget, texture, level );
}

void glFramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLuint, GLint );
    DECLARE( "glFramebufferTexture2D" );
    return pointer( target, attachment, textarget, texture, level );
}

void glFramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLuint, GLint, GLint );
    DECLARE( "glFramebufferTexture3D" );
    return pointer( target, attachment, textarget, texture, level, zoffset );
}

void glFramebufferRenderbuffer( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLuint );
    DECLARE( "glFramebufferRenderbuffer" );
    return pointer( target, attachment, renderbuffertarget, renderbuffer );
}

void glGetFramebufferAttachmentParameteriv( GLenum target, GLenum attachment, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLenum, GLint* );
    DECLARE( "glGetFramebufferAttachmentParameteriv" );
    return pointer( target, attachment, pname, params );
}

void glGenerateMipmap( GLenum target ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glGenerateMipmap" );
    return pointer( target );
}

void glBlitFramebuffer( GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter ) {
    typedef void (__stdcall * Pointer)( GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum );
    DECLARE( "glBlitFramebuffer" );
    return pointer( srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter );
}

void glRenderbufferStorageMultisample( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLenum, GLsizei, GLsizei );
    DECLARE( "glRenderbufferStorageMultisample" );
    return pointer( target, samples, internalformat, width, height );
}

void glFramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint, GLint, GLint );
    DECLARE( "glFramebufferTextureLayer" );
    return pointer( target, attachment, texture, level, layer );
}

GLvoid* glMapBufferRange( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access ) {
    typedef GLvoid* (__stdcall * Pointer)( GLenum, GLintptr, GLsizeiptr, GLbitfield );
    DECLARE( "glMapBufferRange" );
    return pointer( target, offset, length, access );
}

void glFlushMappedBufferRange( GLenum target, GLintptr offset, GLsizeiptr length ) {
    typedef void (__stdcall * Pointer)( GLenum, GLintptr, GLsizeiptr );
    DECLARE( "glFlushMappedBufferRange" );
    return pointer( target, offset, length );
}

void glBindVertexArray( GLuint array ) {
    typedef void (__stdcall * Pointer)( GLuint );
    DECLARE( "glBindVertexArray" );
    return pointer( array );
}

void glDeleteVertexArrays( GLsizei n, const GLuint *arrays ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteVertexArrays" );
    return pointer( n, arrays );
}

void glGenVertexArrays( GLsizei n, GLuint *arrays ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenVertexArrays" );
    return pointer( n, arrays );
}

GLboolean glIsVertexArray( GLuint array ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsVertexArray" );
    return pointer( array );
}

void glGetUniformIndices( GLuint program, GLsizei uniformCount, const GLchar* *uniformNames, GLuint *uniformIndices ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, const GLchar**, GLuint* );
    DECLARE( "glGetUniformIndices" );
    return pointer( program, uniformCount, uniformNames, uniformIndices );
}

void glGetActiveUniformsiv( GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLsizei, const GLuint*, GLenum, GLint* );
    DECLARE( "glGetActiveUniformsiv" );
    return pointer( program, uniformCount, uniformIndices, pname, params );
}

void glGetActiveUniformName( GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetActiveUniformName" );
    return pointer( program, uniformIndex, bufSize, length, uniformName );
}

GLuint glGetUniformBlockIndex( GLuint program, const GLchar *uniformBlockName ) {
    typedef GLuint (__stdcall * Pointer)( GLuint, const GLchar* );
    DECLARE( "glGetUniformBlockIndex" );
    return pointer( program, uniformBlockName );
}

void glGetActiveUniformBlockiv( GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLenum, GLint* );
    DECLARE( "glGetActiveUniformBlockiv" );
    return pointer( program, uniformBlockIndex, pname, params );
}

void glGetActiveUniformBlockName( GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetActiveUniformBlockName" );
    return pointer( program, uniformBlockIndex, bufSize, length, uniformBlockName );
}

void glUniformBlockBinding( GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLuint );
    DECLARE( "glUniformBlockBinding" );
    return pointer( program, uniformBlockIndex, uniformBlockBinding );
}

void glCopyBufferSubData( GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr );
    DECLARE( "glCopyBufferSubData" );
    return pointer( readTarget, writeTarget, readOffset, writeOffset, size );
}

void glDrawElementsBaseVertex( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLenum, const GLvoid*, GLint );
    DECLARE( "glDrawElementsBaseVertex" );
    return pointer( mode, count, type, indices, basevertex );
}

void glDrawRangeElementsBaseVertex( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid*, GLint );
    DECLARE( "glDrawRangeElementsBaseVertex" );
    return pointer( mode, start, end, count, type, indices, basevertex );
}

void glDrawElementsInstancedBaseVertex( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLenum, const GLvoid*, GLsizei, GLint );
    DECLARE( "glDrawElementsInstancedBaseVertex" );
    return pointer( mode, count, type, indices, primcount, basevertex );
}

void glMultiDrawElementsBaseVertex( GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount, const GLint *basevertex ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLsizei*, GLenum, const GLvoid**, GLsizei, const GLint* );
    DECLARE( "glMultiDrawElementsBaseVertex" );
    return pointer( mode, count, type, indices, primcount, basevertex );
}

void glProvokingVertex( GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLenum );
    DECLARE( "glProvokingVertex" );
    return pointer( mode );
}

GLsync glFenceSync( GLenum condition, GLbitfield flags ) {
    typedef GLsync (__stdcall * Pointer)( GLenum, GLbitfield );
    DECLARE( "glFenceSync" );
    return pointer( condition, flags );
}

GLboolean glIsSync( GLsync sync ) {
    typedef GLboolean (__stdcall * Pointer)( GLsync );
    DECLARE( "glIsSync" );
    return pointer( sync );
}

void glDeleteSync( GLsync sync ) {
    typedef void (__stdcall * Pointer)( GLsync );
    DECLARE( "glDeleteSync" );
    return pointer( sync );
}

GLenum glClientWaitSync( GLsync sync, GLbitfield flags, GLuint64 timeout ) {
    typedef GLenum (__stdcall * Pointer)( GLsync, GLbitfield, GLuint64 );
    DECLARE( "glClientWaitSync" );
    return pointer( sync, flags, timeout );
}

void glWaitSync( GLsync sync, GLbitfield flags, GLuint64 timeout ) {
    typedef void (__stdcall * Pointer)( GLsync, GLbitfield, GLuint64 );
    DECLARE( "glWaitSync" );
    return pointer( sync, flags, timeout );
}

void glGetInteger64v( GLenum pname, GLint64 *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint64* );
    DECLARE( "glGetInteger64v" );
    return pointer( pname, params );
}

void glGetSynciv( GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values ) {
    typedef void (__stdcall * Pointer)( GLsync, GLenum, GLsizei, GLsizei*, GLint* );
    DECLARE( "glGetSynciv" );
    return pointer( sync, pname, bufSize, length, values );
}

void glTexImage2DMultisample( GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLint, GLsizei, GLsizei, GLboolean );
    DECLARE( "glTexImage2DMultisample" );
    return pointer( target, samples, internalformat, width, height, fixedsamplelocations );
}

void glTexImage3DMultisample( GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, GLint, GLsizei, GLsizei, GLsizei, GLboolean );
    DECLARE( "glTexImage3DMultisample" );
    return pointer( target, samples, internalformat, width, height, depth, fixedsamplelocations );
}

void glGetMultisamplefv( GLenum pname, GLuint index, GLfloat *val ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLfloat* );
    DECLARE( "glGetMultisamplefv" );
    return pointer( pname, index, val );
}

void glSampleMaski( GLuint index, GLbitfield mask ) {
    typedef void (__stdcall * Pointer)( GLuint, GLbitfield );
    DECLARE( "glSampleMaski" );
    return pointer( index, mask );
}

void glBlendEquationi( GLuint buf, GLenum mode ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum );
    DECLARE( "glBlendEquationi" );
    return pointer( buf, mode );
}

void glBlendEquationSeparatei( GLuint buf, GLenum modeRGB, GLenum modeAlpha ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLenum );
    DECLARE( "glBlendEquationSeparatei" );
    return pointer( buf, modeRGB, modeAlpha );
}

void glBlendFunci( GLuint buf, GLenum src, GLenum dst ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLenum );
    DECLARE( "glBlendFunci" );
    return pointer( buf, src, dst );
}

void glBlendFuncSeparatei( GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLenum, GLenum, GLenum );
    DECLARE( "glBlendFuncSeparatei" );
    return pointer( buf, srcRGB, dstRGB, srcAlpha, dstAlpha );
}

void glMinSampleShading( GLclampf value ) {
    typedef void (__stdcall * Pointer)( GLclampf );
    DECLARE( "glMinSampleShading" );
    return pointer( value );
}

void glBindFragDataLocationIndexed( GLuint program, GLuint colorNumber, GLuint index, const GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLuint, GLuint, const GLchar* );
    DECLARE( "glBindFragDataLocationIndexed" );
    return pointer( program, colorNumber, index, name );
}

GLint glGetFragDataIndex( GLuint program, const GLchar *name ) {
    typedef GLint (__stdcall * Pointer)( GLuint, const GLchar* );
    DECLARE( "glGetFragDataIndex" );
    return pointer( program, name );
}

void glGenSamplers( GLsizei count, GLuint *samplers ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenSamplers" );
    return pointer( count, samplers );
}

void glDeleteSamplers( GLsizei count, const GLuint *samplers ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteSamplers" );
    return pointer( count, samplers );
}

GLboolean glIsSampler( GLuint sampler ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsSampler" );
    return pointer( sampler );
}

void glBindSampler( GLenum unit, GLuint sampler ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindSampler" );
    return pointer( unit, sampler );
}

void glSamplerParameteri( GLuint sampler, GLenum pname, GLint param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint );
    DECLARE( "glSamplerParameteri" );
    return pointer( sampler, pname, param );
}

void glSamplerParameteriv( GLuint sampler, GLenum pname, const GLint *param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, const GLint* );
    DECLARE( "glSamplerParameteriv" );
    return pointer( sampler, pname, param );
}

void glSamplerParameterf( GLuint sampler, GLenum pname, GLfloat param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLfloat );
    DECLARE( "glSamplerParameterf" );
    return pointer( sampler, pname, param );
}

void glSamplerParameterfv( GLuint sampler, GLenum pname, const GLfloat *param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, const GLfloat* );
    DECLARE( "glSamplerParameterfv" );
    return pointer( sampler, pname, param );
}

void glSamplerParameterIiv( GLuint sampler, GLenum pname, const GLint *param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, const GLint* );
    DECLARE( "glSamplerParameterIiv" );
    return pointer( sampler, pname, param );
}

void glSamplerParameterIuiv( GLuint sampler, GLenum pname, const GLuint *param ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, const GLuint* );
    DECLARE( "glSamplerParameterIuiv" );
    return pointer( sampler, pname, param );
}

void glGetSamplerParameteriv( GLuint sampler, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetSamplerParameteriv" );
    return pointer( sampler, pname, params );
}

void glGetSamplerParameterIiv( GLuint sampler, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint* );
    DECLARE( "glGetSamplerParameterIiv" );
    return pointer( sampler, pname, params );
}

void glGetSamplerParameterfv( GLuint sampler, GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLfloat* );
    DECLARE( "glGetSamplerParameterfv" );
    return pointer( sampler, pname, params );
}

void glGetSamplerParameterIfv( GLuint sampler, GLenum pname, GLfloat *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLfloat* );
    DECLARE( "glGetSamplerParameterIfv" );
    return pointer( sampler, pname, params );
}

void glQueryCounter( GLuint id, GLenum target ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum );
    DECLARE( "glQueryCounter" );
    return pointer( id, target );
}

void glGetQueryObjecti64v( GLuint id, GLenum pname, GLint64 *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLint64* );
    DECLARE( "glGetQueryObjecti64v" );
    return pointer( id, pname, params );
}

void glGetQueryObjectui64v( GLuint id, GLenum pname, GLuint64 *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint64* );
    DECLARE( "glGetQueryObjectui64v" );
    return pointer( id, pname, params );
}

void glVertexP2ui( GLenum type, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glVertexP2ui" );
    return pointer( type, value );
}

void glVertexP2uiv( GLenum type, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glVertexP2uiv" );
    return pointer( type, value );
}

void glVertexP3ui( GLenum type, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glVertexP3ui" );
    return pointer( type, value );
}

void glVertexP3uiv( GLenum type, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glVertexP3uiv" );
    return pointer( type, value );
}

void glVertexP4ui( GLenum type, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glVertexP4ui" );
    return pointer( type, value );
}

void glVertexP4uiv( GLenum type, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glVertexP4uiv" );
    return pointer( type, value );
}

void glTexCoordP1ui( GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glTexCoordP1ui" );
    return pointer( type, coords );
}

void glTexCoordP1uiv( GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glTexCoordP1uiv" );
    return pointer( type, coords );
}

void glTexCoordP2ui( GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glTexCoordP2ui" );
    return pointer( type, coords );
}

void glTexCoordP2uiv( GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glTexCoordP2uiv" );
    return pointer( type, coords );
}

void glTexCoordP3ui( GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glTexCoordP3ui" );
    return pointer( type, coords );
}

void glTexCoordP3uiv( GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glTexCoordP3uiv" );
    return pointer( type, coords );
}

void glTexCoordP4ui( GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glTexCoordP4ui" );
    return pointer( type, coords );
}

void glTexCoordP4uiv( GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glTexCoordP4uiv" );
    return pointer( type, coords );
}

void glMultiTexCoordP1ui( GLenum texture, GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint );
    DECLARE( "glMultiTexCoordP1ui" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP1uiv( GLenum texture, GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLuint* );
    DECLARE( "glMultiTexCoordP1uiv" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP2ui( GLenum texture, GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint );
    DECLARE( "glMultiTexCoordP2ui" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP2uiv( GLenum texture, GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLuint* );
    DECLARE( "glMultiTexCoordP2uiv" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP3ui( GLenum texture, GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint );
    DECLARE( "glMultiTexCoordP3ui" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP3uiv( GLenum texture, GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLuint* );
    DECLARE( "glMultiTexCoordP3uiv" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP4ui( GLenum texture, GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, GLuint );
    DECLARE( "glMultiTexCoordP4ui" );
    return pointer( texture, type, coords );
}

void glMultiTexCoordP4uiv( GLenum texture, GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLuint* );
    DECLARE( "glMultiTexCoordP4uiv" );
    return pointer( texture, type, coords );
}

void glNormalP3ui( GLenum type, GLuint coords ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glNormalP3ui" );
    return pointer( type, coords );
}

void glNormalP3uiv( GLenum type, const GLuint *coords ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glNormalP3uiv" );
    return pointer( type, coords );
}

void glColorP3ui( GLenum type, GLuint color ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glColorP3ui" );
    return pointer( type, color );
}

void glColorP3uiv( GLenum type, const GLuint *color ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glColorP3uiv" );
    return pointer( type, color );
}

void glColorP4ui( GLenum type, GLuint color ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glColorP4ui" );
    return pointer( type, color );
}

void glColorP4uiv( GLenum type, const GLuint *color ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glColorP4uiv" );
    return pointer( type, color );
}

void glSecondaryColorP3ui( GLenum type, GLuint color ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glSecondaryColorP3ui" );
    return pointer( type, color );
}

void glSecondaryColorP3uiv( GLenum type, const GLuint *color ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLuint* );
    DECLARE( "glSecondaryColorP3uiv" );
    return pointer( type, color );
}

void glVertexAttribP1ui( GLuint index, GLenum type, GLboolean normalized, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, GLuint );
    DECLARE( "glVertexAttribP1ui" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP1uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, const GLuint* );
    DECLARE( "glVertexAttribP1uiv" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP2ui( GLuint index, GLenum type, GLboolean normalized, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, GLuint );
    DECLARE( "glVertexAttribP2ui" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP2uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, const GLuint* );
    DECLARE( "glVertexAttribP2uiv" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP3ui( GLuint index, GLenum type, GLboolean normalized, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, GLuint );
    DECLARE( "glVertexAttribP3ui" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP3uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, const GLuint* );
    DECLARE( "glVertexAttribP3uiv" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP4ui( GLuint index, GLenum type, GLboolean normalized, GLuint value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, GLuint );
    DECLARE( "glVertexAttribP4ui" );
    return pointer( index, type, normalized, value );
}

void glVertexAttribP4uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLboolean, const GLuint* );
    DECLARE( "glVertexAttribP4uiv" );
    return pointer( index, type, normalized, value );
}

void glDrawArraysIndirect( GLenum mode, const GLvoid *indirect ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLvoid* );
    DECLARE( "glDrawArraysIndirect" );
    return pointer( mode, indirect );
}

void glDrawElementsIndirect( GLenum mode, GLenum type, const GLvoid *indirect ) {
    typedef void (__stdcall * Pointer)( GLenum, GLenum, const GLvoid* );
    DECLARE( "glDrawElementsIndirect" );
    return pointer( mode, type, indirect );
}

void glUniform1d( GLint location, GLdouble x ) {
    typedef void (__stdcall * Pointer)( GLint, GLdouble );
    DECLARE( "glUniform1d" );
    return pointer( location, x );
}

void glUniform2d( GLint location, GLdouble x, GLdouble y ) {
    typedef void (__stdcall * Pointer)( GLint, GLdouble, GLdouble );
    DECLARE( "glUniform2d" );
    return pointer( location, x, y );
}

void glUniform3d( GLint location, GLdouble x, GLdouble y, GLdouble z ) {
    typedef void (__stdcall * Pointer)( GLint, GLdouble, GLdouble, GLdouble );
    DECLARE( "glUniform3d" );
    return pointer( location, x, y, z );
}

void glUniform4d( GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
    typedef void (__stdcall * Pointer)( GLint, GLdouble, GLdouble, GLdouble, GLdouble );
    DECLARE( "glUniform4d" );
    return pointer( location, x, y, z, w );
}

void glUniform1dv( GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLdouble* );
    DECLARE( "glUniform1dv" );
    return pointer( location, count, value );
}

void glUniform2dv( GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLdouble* );
    DECLARE( "glUniform2dv" );
    return pointer( location, count, value );
}

void glUniform3dv( GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLdouble* );
    DECLARE( "glUniform3dv" );
    return pointer( location, count, value );
}

void glUniform4dv( GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, const GLdouble* );
    DECLARE( "glUniform4dv" );
    return pointer( location, count, value );
}

void glUniformMatrix2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix2dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix3dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix4dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix2x3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix2x3dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix2x4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix2x4dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3x2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix3x2dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix3x4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix3x4dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4x2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix4x2dv" );
    return pointer( location, count, transpose, value );
}

void glUniformMatrix4x3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glUniformMatrix4x3dv" );
    return pointer( location, count, transpose, value );
}

void glGetUniformdv( GLuint program, GLint location, GLdouble *params ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLdouble* );
    DECLARE( "glGetUniformdv" );
    return pointer( program, location, params );
}

void glProgramUniform1dEXT( GLuint program, GLint location, GLdouble x ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLdouble );
    DECLARE( "glProgramUniform1dEXT" );
    return pointer( program, location, x );
}

void glProgramUniform2dEXT( GLuint program, GLint location, GLdouble x, GLdouble y ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLdouble, GLdouble );
    DECLARE( "glProgramUniform2dEXT" );
    return pointer( program, location, x, y );
}

void glProgramUniform3dEXT( GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLdouble, GLdouble, GLdouble );
    DECLARE( "glProgramUniform3dEXT" );
    return pointer( program, location, x, y, z );
}

void glProgramUniform4dEXT( GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble );
    DECLARE( "glProgramUniform4dEXT" );
    return pointer( program, location, x, y, z, w );
}

void glProgramUniform1dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, const GLdouble* );
    DECLARE( "glProgramUniform1dvEXT" );
    return pointer( program, location, count, value );
}

void glProgramUniform2dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, const GLdouble* );
    DECLARE( "glProgramUniform2dvEXT" );
    return pointer( program, location, count, value );
}

void glProgramUniform3dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, const GLdouble* );
    DECLARE( "glProgramUniform3dvEXT" );
    return pointer( program, location, count, value );
}

void glProgramUniform4dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, const GLdouble* );
    DECLARE( "glProgramUniform4dvEXT" );
    return pointer( program, location, count, value );
}

void glProgramUniformMatrix2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix2dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix3dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix4dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix2x3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix2x3dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix2x4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix2x4dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix3x2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix3x2dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix3x4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix3x4dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix4x2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix4x2dvEXT" );
    return pointer( program, location, count, transpose, value );
}

void glProgramUniformMatrix4x3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value ) {
    typedef void (__stdcall * Pointer)( GLuint, GLint, GLsizei, GLboolean, const GLdouble* );
    DECLARE( "glProgramUniformMatrix4x3dvEXT" );
    return pointer( program, location, count, transpose, value );
}

GLint glGetSubroutineUniformLocation( GLuint program, GLenum shadertype, const GLchar *name ) {
    typedef GLint (__stdcall * Pointer)( GLuint, GLenum, const GLchar* );
    DECLARE( "glGetSubroutineUniformLocation" );
    return pointer( program, shadertype, name );
}

GLuint glGetSubroutineIndex( GLuint program, GLenum shadertype, const GLchar *name ) {
    typedef GLuint (__stdcall * Pointer)( GLuint, GLenum, const GLchar* );
    DECLARE( "glGetSubroutineIndex" );
    return pointer( program, shadertype, name );
}

void glGetActiveSubroutineUniformiv( GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint, GLenum, GLint* );
    DECLARE( "glGetActiveSubroutineUniformiv" );
    return pointer( program, shadertype, index, pname, values );
}

void glGetActiveSubroutineUniformName( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetActiveSubroutineUniformName" );
    return pointer( program, shadertype, index, bufsize, length, name );
}

void glGetActiveSubroutineName( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar* );
    DECLARE( "glGetActiveSubroutineName" );
    return pointer( program, shadertype, index, bufsize, length, name );
}

void glUniformSubroutinesuiv( GLenum shadertype, GLsizei count, const GLuint *indices ) {
    typedef void (__stdcall * Pointer)( GLenum, GLsizei, const GLuint* );
    DECLARE( "glUniformSubroutinesuiv" );
    return pointer( shadertype, count, indices );
}

void glGetUniformSubroutineuiv( GLenum shadertype, GLint location, GLuint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint, GLuint* );
    DECLARE( "glGetUniformSubroutineuiv" );
    return pointer( shadertype, location, params );
}

void glGetProgramStageiv( GLuint program, GLenum shadertype, GLenum pname, GLint *values ) {
    typedef void (__stdcall * Pointer)( GLuint, GLenum, GLenum, GLint* );
    DECLARE( "glGetProgramStageiv" );
    return pointer( program, shadertype, pname, values );
}

void glPatchParameteri( GLenum pname, GLint value ) {
    typedef void (__stdcall * Pointer)( GLenum, GLint );
    DECLARE( "glPatchParameteri" );
    return pointer( pname, value );
}

void glPatchParameterfv( GLenum pname, const GLfloat *values ) {
    typedef void (__stdcall * Pointer)( GLenum, const GLfloat* );
    DECLARE( "glPatchParameterfv" );
    return pointer( pname, values );
}

void glBindTransformFeedback( GLenum target, GLuint id ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glBindTransformFeedback" );
    return pointer( target, id );
}

void glDeleteTransformFeedbacks( GLsizei n, const GLuint *ids ) {
    typedef void (__stdcall * Pointer)( GLsizei, const GLuint* );
    DECLARE( "glDeleteTransformFeedbacks" );
    return pointer( n, ids );
}

void glGenTransformFeedbacks( GLsizei n, GLuint *ids ) {
    typedef void (__stdcall * Pointer)( GLsizei, GLuint* );
    DECLARE( "glGenTransformFeedbacks" );
    return pointer( n, ids );
}

GLboolean glIsTransformFeedback( GLuint id ) {
    typedef GLboolean (__stdcall * Pointer)( GLuint );
    DECLARE( "glIsTransformFeedback" );
    return pointer( id );
}

void glPauseTransformFeedback( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glPauseTransformFeedback" );
    return pointer( );
}

void glResumeTransformFeedback( void ) {
    typedef void (__stdcall * Pointer)( void );
    DECLARE( "glResumeTransformFeedback" );
    return pointer( );
}

void glDrawTransformFeedback( GLenum mode, GLuint id ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glDrawTransformFeedback" );
    return pointer( mode, id );
}

void glDrawTransformFeedbackStream( GLenum mode, GLuint id, GLuint stream ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint );
    DECLARE( "glDrawTransformFeedbackStream" );
    return pointer( mode, id, stream );
}

void glBeginQueryIndexed( GLenum target, GLuint index, GLuint id ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLuint );
    DECLARE( "glBeginQueryIndexed" );
    return pointer( target, index, id );
}

void glEndQueryIndexed( GLenum target, GLuint index ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint );
    DECLARE( "glEndQueryIndexed" );
    return pointer( target, index );
}

void glGetQueryIndexediv( GLenum target, GLuint index, GLenum pname, GLint *params ) {
    typedef void (__stdcall * Pointer)( GLenum, GLuint, GLenum, GLint* );
    DECLARE( "glGetQueryIndexediv" );
    return pointer( target, index, pname, params );
}