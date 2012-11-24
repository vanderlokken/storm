#ifndef storm_FunctionsOgl_h
#define storm_FunctionsOgl_h

/*
** Copyright (c) 2007-2010 The Khronos Group Inc.
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
** 
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
** 
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#include "CoreTypesOgl.h"

#define __gl_h_

#ifndef GL_VERSION_1_0
#define GL_VERSION_1_0 1
void glCullFace( GLenum mode );
void glFrontFace( GLenum mode );
void glHint( GLenum target, GLenum mode );
void glLineWidth( GLfloat width );
void glPointSize( GLfloat size );
void glPolygonMode( GLenum face, GLenum mode );
void glScissor( GLint x, GLint y, GLsizei width, GLsizei height );
void glTexParameterf( GLenum target, GLenum pname, GLfloat param );
void glTexParameterfv( GLenum target, GLenum pname, const GLfloat *params );
void glTexParameteri( GLenum target, GLenum pname, GLint param );
void glTexParameteriv( GLenum target, GLenum pname, const GLint *params );
void glTexImage1D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
void glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
void glDrawBuffer( GLenum mode );
void glClear( GLbitfield mask );
void glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
void glClearStencil( GLint s );
void glClearDepth( GLclampd depth );
void glStencilMask( GLuint mask );
void glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
void glDepthMask( GLboolean flag );
void glDisable( GLenum cap );
void glEnable( GLenum cap );
void glFinish( void );
void glFlush( void );
void glBlendFunc( GLenum sfactor, GLenum dfactor );
void glLogicOp( GLenum opcode );
void glStencilFunc( GLenum func, GLint ref, GLuint mask );
void glStencilOp( GLenum fail, GLenum zfail, GLenum zpass );
void glDepthFunc( GLenum func );
void glPixelStoref( GLenum pname, GLfloat param );
void glPixelStorei( GLenum pname, GLint param );
void glReadBuffer( GLenum mode );
void glReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels );
void glGetBooleanv( GLenum pname, GLboolean *params );
void glGetDoublev( GLenum pname, GLdouble *params );
GLenum glGetError( void );
void glGetFloatv( GLenum pname, GLfloat *params );
void glGetIntegerv( GLenum pname, GLint *params );
const GLubyte * glGetString( GLenum name );
void glGetTexImage( GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels );
void glGetTexParameterfv( GLenum target, GLenum pname, GLfloat *params );
void glGetTexParameteriv( GLenum target, GLenum pname, GLint *params );
void glGetTexLevelParameterfv( GLenum target, GLint level, GLenum pname, GLfloat *params );
void glGetTexLevelParameteriv( GLenum target, GLint level, GLenum pname, GLint *params );
GLboolean glIsEnabled( GLenum cap );
void glDepthRange( GLclampd near, GLclampd far );
void glViewport( GLint x, GLint y, GLsizei width, GLsizei height );
#endif

#ifndef GL_VERSION_1_1
#define GL_VERSION_1_1 1
void glDrawArrays( GLenum mode, GLint first, GLsizei count );
void glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices );
void glGetPointerv( GLenum pname, GLvoid* *params );
void glPolygonOffset( GLfloat factor, GLfloat units );
void glCopyTexImage1D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border );
void glCopyTexImage2D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border );
void glCopyTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width );
void glCopyTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height );
void glTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels );
void glTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels );
void glBindTexture( GLenum target, GLuint texture );
void glDeleteTextures( GLsizei n, const GLuint *textures );
void glGenTextures( GLsizei n, GLuint *textures );
GLboolean glIsTexture( GLuint texture );
#endif

#ifndef GL_VERSION_1_2
#define GL_VERSION_1_2 1
void glBlendColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
void glBlendEquation( GLenum mode );
void glDrawRangeElements( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices );
void glTexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels );
void glTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels );
void glCopyTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );
#endif

#ifndef GL_VERSION_1_3
#define GL_VERSION_1_3 1
void glActiveTexture( GLenum texture );
void glSampleCoverage( GLclampf value, GLboolean invert );
void glCompressedTexImage3D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data );
void glCompressedTexImage2D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data );
void glCompressedTexImage1D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data );
void glCompressedTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data );
void glCompressedTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data );
void glCompressedTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data );
void glGetCompressedTexImage( GLenum target, GLint level, GLvoid *img );
#endif

#ifndef GL_VERSION_1_4
#define GL_VERSION_1_4 1
void glBlendFuncSeparate( GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha );
void glMultiDrawArrays( GLenum mode, GLint *first, GLsizei *count, GLsizei primcount );
void glMultiDrawElements( GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount );
void glPointParameterf( GLenum pname, GLfloat param );
void glPointParameterfv( GLenum pname, const GLfloat *params );
void glPointParameteri( GLenum pname, GLint param );
void glPointParameteriv( GLenum pname, const GLint *params );
#endif

#ifndef GL_VERSION_1_5
#define GL_VERSION_1_5 1
void glGenQueries( GLsizei n, GLuint *ids );
void glDeleteQueries( GLsizei n, const GLuint *ids );
GLboolean glIsQuery( GLuint id );
void glBeginQuery( GLenum target, GLuint id );
void glEndQuery( GLenum target );
void glGetQueryiv( GLenum target, GLenum pname, GLint *params );
void glGetQueryObjectiv( GLuint id, GLenum pname, GLint *params );
void glGetQueryObjectuiv( GLuint id, GLenum pname, GLuint *params );
void glBindBuffer( GLenum target, GLuint buffer );
void glDeleteBuffers( GLsizei n, const GLuint *buffers );
void glGenBuffers( GLsizei n, GLuint *buffers );
GLboolean glIsBuffer( GLuint buffer );
void glBufferData( GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage );
void glBufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data );
void glGetBufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data );
GLvoid* glMapBuffer( GLenum target, GLenum access );
GLboolean glUnmapBuffer( GLenum target );
void glGetBufferParameteriv( GLenum target, GLenum pname, GLint *params );
void glGetBufferPointerv( GLenum target, GLenum pname, GLvoid* *params );
#endif

#ifndef GL_VERSION_2_0
#define GL_VERSION_2_0 1
void glBlendEquationSeparate( GLenum modeRGB, GLenum modeAlpha );
void glDrawBuffers( GLsizei n, const GLenum *bufs );
void glStencilOpSeparate( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass );
void glStencilFuncSeparate( GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask );
void glStencilMaskSeparate( GLenum face, GLuint mask );
void glAttachShader( GLuint program, GLuint shader );
void glBindAttribLocation( GLuint program, GLuint index, const GLchar *name );
void glCompileShader( GLuint shader );
GLuint glCreateProgram( void );
GLuint glCreateShader( GLenum type );
void glDeleteProgram( GLuint program );
void glDeleteShader( GLuint shader );
void glDetachShader( GLuint program, GLuint shader );
void glDisableVertexAttribArray( GLuint index );
void glEnableVertexAttribArray( GLuint index );
void glGetActiveAttrib( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name );
void glGetActiveUniform( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name );
void glGetAttachedShaders( GLuint program, GLsizei maxCount, GLsizei *count, GLuint *obj );
GLint glGetAttribLocation( GLuint program, const GLchar *name );
void glGetProgramiv( GLuint program, GLenum pname, GLint *params );
void glGetProgramInfoLog( GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog );
void glGetShaderiv( GLuint shader, GLenum pname, GLint *params );
void glGetShaderInfoLog( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog );
void glGetShaderSource( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source );
GLint glGetUniformLocation( GLuint program, const GLchar *name );
void glGetUniformfv( GLuint program, GLint location, GLfloat *params );
void glGetUniformiv( GLuint program, GLint location, GLint *params );
void glGetVertexAttribdv( GLuint index, GLenum pname, GLdouble *params );
void glGetVertexAttribfv( GLuint index, GLenum pname, GLfloat *params );
void glGetVertexAttribiv( GLuint index, GLenum pname, GLint *params );
void glGetVertexAttribPointerv( GLuint index, GLenum pname, GLvoid* *pointer );
GLboolean glIsProgram( GLuint program );
GLboolean glIsShader( GLuint shader );
void glLinkProgram( GLuint program );
void glShaderSource( GLuint shader, GLsizei count, const GLchar* *string, const GLint *length );
void glUseProgram( GLuint program );
void glUniform1f( GLint location, GLfloat v0 );
void glUniform2f( GLint location, GLfloat v0, GLfloat v1 );
void glUniform3f( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
void glUniform4f( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
void glUniform1i( GLint location, GLint v0 );
void glUniform2i( GLint location, GLint v0, GLint v1 );
void glUniform3i( GLint location, GLint v0, GLint v1, GLint v2 );
void glUniform4i( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
void glUniform1fv( GLint location, GLsizei count, const GLfloat *value );
void glUniform2fv( GLint location, GLsizei count, const GLfloat *value );
void glUniform3fv( GLint location, GLsizei count, const GLfloat *value );
void glUniform4fv( GLint location, GLsizei count, const GLfloat *value );
void glUniform1iv( GLint location, GLsizei count, const GLint *value );
void glUniform2iv( GLint location, GLsizei count, const GLint *value );
void glUniform3iv( GLint location, GLsizei count, const GLint *value );
void glUniform4iv( GLint location, GLsizei count, const GLint *value );
void glUniformMatrix2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glValidateProgram( GLuint program );
void glVertexAttrib1d( GLuint index, GLdouble x );
void glVertexAttrib1dv( GLuint index, const GLdouble *v );
void glVertexAttrib1f( GLuint index, GLfloat x );
void glVertexAttrib1fv( GLuint index, const GLfloat *v );
void glVertexAttrib1s( GLuint index, GLshort x );
void glVertexAttrib1sv( GLuint index, const GLshort *v );
void glVertexAttrib2d( GLuint index, GLdouble x, GLdouble y );
void glVertexAttrib2dv( GLuint index, const GLdouble *v );
void glVertexAttrib2f( GLuint index, GLfloat x, GLfloat y );
void glVertexAttrib2fv( GLuint index, const GLfloat *v );
void glVertexAttrib2s( GLuint index, GLshort x, GLshort y );
void glVertexAttrib2sv( GLuint index, const GLshort *v );
void glVertexAttrib3d( GLuint index, GLdouble x, GLdouble y, GLdouble z );
void glVertexAttrib3dv( GLuint index, const GLdouble *v );
void glVertexAttrib3f( GLuint index, GLfloat x, GLfloat y, GLfloat z );
void glVertexAttrib3fv( GLuint index, const GLfloat *v );
void glVertexAttrib3s( GLuint index, GLshort x, GLshort y, GLshort z );
void glVertexAttrib3sv( GLuint index, const GLshort *v );
void glVertexAttrib4Nbv( GLuint index, const GLbyte *v );
void glVertexAttrib4Niv( GLuint index, const GLint *v );
void glVertexAttrib4Nsv( GLuint index, const GLshort *v );
void glVertexAttrib4Nub( GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w );
void glVertexAttrib4Nubv( GLuint index, const GLubyte *v );
void glVertexAttrib4Nuiv( GLuint index, const GLuint *v );
void glVertexAttrib4Nusv( GLuint index, const GLushort *v );
void glVertexAttrib4bv( GLuint index, const GLbyte *v );
void glVertexAttrib4d( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
void glVertexAttrib4dv( GLuint index, const GLdouble *v );
void glVertexAttrib4f( GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
void glVertexAttrib4fv( GLuint index, const GLfloat *v );
void glVertexAttrib4iv( GLuint index, const GLint *v );
void glVertexAttrib4s( GLuint index, GLshort x, GLshort y, GLshort z, GLshort w );
void glVertexAttrib4sv( GLuint index, const GLshort *v );
void glVertexAttrib4ubv( GLuint index, const GLubyte *v );
void glVertexAttrib4uiv( GLuint index, const GLuint *v );
void glVertexAttrib4usv( GLuint index, const GLushort *v );
void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer );
#endif

#ifndef GL_VERSION_2_1
#define GL_VERSION_2_1 1
void glUniformMatrix2x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix3x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix2x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix4x2fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix3x4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
void glUniformMatrix4x3fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
#endif

#ifndef GL_VERSION_3_0
#define GL_VERSION_3_0 1
/* OpenGL 3.0 also reuses entry points from these extensions: */
/* ARB_framebuffer_object */
/* ARB_map_buffer_range */
/* ARB_vertex_array_object */
void glColorMaski( GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a );
void glGetBooleani_v( GLenum target, GLuint index, GLboolean *data );
void glGetIntegeri_v( GLenum target, GLuint index, GLint *data );
void glEnablei( GLenum target, GLuint index );
void glDisablei( GLenum target, GLuint index );
GLboolean glIsEnabledi( GLenum target, GLuint index );
void glBeginTransformFeedback( GLenum primitiveMode );
void glEndTransformFeedback( void );
void glBindBufferRange( GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size );
void glBindBufferBase( GLenum target, GLuint index, GLuint buffer );
void glTransformFeedbackVaryings( GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode );
void glGetTransformFeedbackVarying( GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name );
void glClampColor( GLenum target, GLenum clamp );
void glBeginConditionalRender( GLuint id, GLenum mode );
void glEndConditionalRender( void );
void glVertexAttribIPointer( GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
void glGetVertexAttribIiv( GLuint index, GLenum pname, GLint *params );
void glGetVertexAttribIuiv( GLuint index, GLenum pname, GLuint *params );
void glVertexAttribI1i( GLuint index, GLint x );
void glVertexAttribI2i( GLuint index, GLint x, GLint y );
void glVertexAttribI3i( GLuint index, GLint x, GLint y, GLint z );
void glVertexAttribI4i( GLuint index, GLint x, GLint y, GLint z, GLint w );
void glVertexAttribI1ui( GLuint index, GLuint x );
void glVertexAttribI2ui( GLuint index, GLuint x, GLuint y );
void glVertexAttribI3ui( GLuint index, GLuint x, GLuint y, GLuint z );
void glVertexAttribI4ui( GLuint index, GLuint x, GLuint y, GLuint z, GLuint w );
void glVertexAttribI1iv( GLuint index, const GLint *v );
void glVertexAttribI2iv( GLuint index, const GLint *v );
void glVertexAttribI3iv( GLuint index, const GLint *v );
void glVertexAttribI4iv( GLuint index, const GLint *v );
void glVertexAttribI1uiv( GLuint index, const GLuint *v );
void glVertexAttribI2uiv( GLuint index, const GLuint *v );
void glVertexAttribI3uiv( GLuint index, const GLuint *v );
void glVertexAttribI4uiv( GLuint index, const GLuint *v );
void glVertexAttribI4bv( GLuint index, const GLbyte *v );
void glVertexAttribI4sv( GLuint index, const GLshort *v );
void glVertexAttribI4ubv( GLuint index, const GLubyte *v );
void glVertexAttribI4usv( GLuint index, const GLushort *v );
void glGetUniformuiv( GLuint program, GLint location, GLuint *params );
void glBindFragDataLocation( GLuint program, GLuint color, const GLchar *name );
GLint glGetFragDataLocation( GLuint program, const GLchar *name );
void glUniform1ui( GLint location, GLuint v0 );
void glUniform2ui( GLint location, GLuint v0, GLuint v1 );
void glUniform3ui( GLint location, GLuint v0, GLuint v1, GLuint v2 );
void glUniform4ui( GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 );
void glUniform1uiv( GLint location, GLsizei count, const GLuint *value );
void glUniform2uiv( GLint location, GLsizei count, const GLuint *value );
void glUniform3uiv( GLint location, GLsizei count, const GLuint *value );
void glUniform4uiv( GLint location, GLsizei count, const GLuint *value );
void glTexParameterIiv( GLenum target, GLenum pname, const GLint *params );
void glTexParameterIuiv( GLenum target, GLenum pname, const GLuint *params );
void glGetTexParameterIiv( GLenum target, GLenum pname, GLint *params );
void glGetTexParameterIuiv( GLenum target, GLenum pname, GLuint *params );
void glClearBufferiv( GLenum buffer, GLint drawbuffer, const GLint *value );
void glClearBufferuiv( GLenum buffer, GLint drawbuffer, const GLuint *value );
void glClearBufferfv( GLenum buffer, GLint drawbuffer, const GLfloat *value );
void glClearBufferfi( GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil );
const GLubyte * glGetStringi( GLenum name, GLuint index );
#endif

#ifndef GL_VERSION_3_1
#define GL_VERSION_3_1 1
/* OpenGL 3.1 also reuses entry points from these extensions: */
/* ARB_copy_buffer */
/* ARB_uniform_buffer_object */
void glDrawArraysInstanced( GLenum mode, GLint first, GLsizei count, GLsizei primcount );
void glDrawElementsInstanced( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount );
void glTexBuffer( GLenum target, GLenum internalformat, GLuint buffer );
void glPrimitiveRestartIndex( GLuint index );
#endif

#ifndef GL_VERSION_3_2
#define GL_VERSION_3_2 1
/* OpenGL 3.2 also reuses entry points from these extensions: */
/* ARB_draw_elements_base_vertex */
/* ARB_provoking_vertex */
/* ARB_sync */
/* ARB_texture_multisample */
void glGetInteger64i_v( GLenum target, GLuint index, GLint64 *data );
void glGetBufferParameteri64v( GLenum target, GLenum pname, GLint64 *params );
void glProgramParameteri( GLuint program, GLenum pname, GLint value );
void glFramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level );
#endif

#ifndef GL_VERSION_3_3
#define GL_VERSION_3_3 1
/* OpenGL 3.3 also reuses entry points from these extensions: */
/* ARB_blend_func_extended */
/* ARB_sampler_objects */
/* ARB_explicit_attrib_location, but it has none */
/* ARB_occlusion_query2 (no entry points) */
/* ARB_shader_bit_encoding (no entry points) */
/* ARB_texture_rgb10_a2ui (no entry points) */
/* ARB_texture_swizzle (no entry points) */
/* ARB_timer_query */
/* ARB_vertex_type_2_10_10_10_rev */
#endif

#ifndef GL_VERSION_4_0
#define GL_VERSION_4_0 1
/* OpenGL 4.0 also reuses entry points from these extensions: */
/* ARB_gpu_shader5 (no entry points) */
/* ARB_gpu_shader_fp64 */
/* ARB_shader_subroutine */
/* ARB_tessellation_shader */
/* ARB_texture_buffer_object_rgb32 (no entry points) */
/* ARB_transform_feedback2 */
/* ARB_transform_feedback3 */
#endif

#ifndef GL_ARB_depth_buffer_float
#define GL_ARB_depth_buffer_float 1
#endif

#ifndef GL_ARB_framebuffer_object
#define GL_ARB_framebuffer_object 1
GLboolean glIsRenderbuffer( GLuint renderbuffer );
void glBindRenderbuffer( GLenum target, GLuint renderbuffer );
void glDeleteRenderbuffers( GLsizei n, const GLuint *renderbuffers );
void glGenRenderbuffers( GLsizei n, GLuint *renderbuffers );
void glRenderbufferStorage( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
void glGetRenderbufferParameteriv( GLenum target, GLenum pname, GLint *params );
GLboolean glIsFramebuffer( GLuint framebuffer );
void glBindFramebuffer( GLenum target, GLuint framebuffer );
void glDeleteFramebuffers( GLsizei n, const GLuint *framebuffers );
void glGenFramebuffers( GLsizei n, GLuint *framebuffers );
GLenum glCheckFramebufferStatus( GLenum target );
void glFramebufferTexture1D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
void glFramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
void glFramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset );
void glFramebufferRenderbuffer( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
void glGetFramebufferAttachmentParameteriv( GLenum target, GLenum attachment, GLenum pname, GLint *params );
void glGenerateMipmap( GLenum target );
void glBlitFramebuffer( GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter );
void glRenderbufferStorageMultisample( GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height );
void glFramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer );
#endif

#ifndef GL_ARB_framebuffer_sRGB
#define GL_ARB_framebuffer_sRGB 1
#endif

#ifndef GL_ARB_half_float_vertex
#define GL_ARB_half_float_vertex 1
#endif

#ifndef GL_ARB_map_buffer_range
#define GL_ARB_map_buffer_range 1
GLvoid* glMapBufferRange( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access );
void glFlushMappedBufferRange( GLenum target, GLintptr offset, GLsizeiptr length );
#endif

#ifndef GL_ARB_texture_compression_rgtc
#define GL_ARB_texture_compression_rgtc 1
#endif

#ifndef GL_ARB_texture_rg
#define GL_ARB_texture_rg 1
#endif

#ifndef GL_ARB_vertex_array_object
#define GL_ARB_vertex_array_object 1
void glBindVertexArray( GLuint array );
void glDeleteVertexArrays( GLsizei n, const GLuint *arrays );
void glGenVertexArrays( GLsizei n, GLuint *arrays );
GLboolean glIsVertexArray( GLuint array );
#endif

#ifndef GL_ARB_uniform_buffer_object
#define GL_ARB_uniform_buffer_object 1
void glGetUniformIndices( GLuint program, GLsizei uniformCount, const GLchar* *uniformNames, GLuint *uniformIndices );
void glGetActiveUniformsiv( GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params );
void glGetActiveUniformName( GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName );
GLuint glGetUniformBlockIndex( GLuint program, const GLchar *uniformBlockName );
void glGetActiveUniformBlockiv( GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params );
void glGetActiveUniformBlockName( GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName );
void glUniformBlockBinding( GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding );
#endif

#ifndef GL_ARB_copy_buffer
#define GL_ARB_copy_buffer 1
void glCopyBufferSubData( GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size );
#endif

#ifndef GL_ARB_depth_clamp
#define GL_ARB_depth_clamp 1
#endif

#ifndef GL_ARB_draw_elements_base_vertex
#define GL_ARB_draw_elements_base_vertex 1
void glDrawElementsBaseVertex( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex );
void glDrawRangeElementsBaseVertex( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex );
void glDrawElementsInstancedBaseVertex( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex );
void glMultiDrawElementsBaseVertex( GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount, const GLint *basevertex );
#endif

#ifndef GL_ARB_fragment_coord_conventions
#define GL_ARB_fragment_coord_conventions 1
#endif

#ifndef GL_ARB_provoking_vertex
#define GL_ARB_provoking_vertex 1
void glProvokingVertex( GLenum mode );
#endif

#ifndef GL_ARB_seamless_cube_map
#define GL_ARB_seamless_cube_map 1
#endif

#ifndef GL_ARB_sync
#define GL_ARB_sync 1
GLsync glFenceSync( GLenum condition, GLbitfield flags );
GLboolean glIsSync( GLsync sync );
void glDeleteSync( GLsync sync );
GLenum glClientWaitSync( GLsync sync, GLbitfield flags, GLuint64 timeout );
void glWaitSync( GLsync sync, GLbitfield flags, GLuint64 timeout );
void glGetInteger64v( GLenum pname, GLint64 *params );
void glGetSynciv( GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values );
#endif

#ifndef GL_ARB_texture_multisample
#define GL_ARB_texture_multisample 1
void glTexImage2DMultisample( GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations );
void glTexImage3DMultisample( GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations );
void glGetMultisamplefv( GLenum pname, GLuint index, GLfloat *val );
void glSampleMaski( GLuint index, GLbitfield mask );
#endif

#ifndef GL_ARB_vertex_array_bgra
#define GL_ARB_vertex_array_bgra 1
#endif

#ifndef GL_ARB_draw_buffers_blend
#define GL_ARB_draw_buffers_blend 1
void glBlendEquationi( GLuint buf, GLenum mode );
void glBlendEquationSeparatei( GLuint buf, GLenum modeRGB, GLenum modeAlpha );
void glBlendFunci( GLuint buf, GLenum src, GLenum dst );
void glBlendFuncSeparatei( GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha );
#endif

#ifndef GL_ARB_sample_shading
#define GL_ARB_sample_shading 1
void glMinSampleShading( GLclampf value );
#endif

#ifndef GL_ARB_texture_cube_map_array
#define GL_ARB_texture_cube_map_array 1
#endif

#ifndef GL_ARB_texture_gather
#define GL_ARB_texture_gather 1
#endif

#ifndef GL_ARB_texture_query_lod
#define GL_ARB_texture_query_lod 1
#endif

#ifndef GL_ARB_blend_func_extended
#define GL_ARB_blend_func_extended 1
void glBindFragDataLocationIndexed( GLuint program, GLuint colorNumber, GLuint index, const GLchar *name );
GLint glGetFragDataIndex( GLuint program, const GLchar *name );
#endif

#ifndef GL_ARB_sampler_objects
#define GL_ARB_sampler_objects 1
void glGenSamplers( GLsizei count, GLuint *samplers );
void glDeleteSamplers( GLsizei count, const GLuint *samplers );
GLboolean glIsSampler( GLuint sampler );
void glBindSampler( GLenum unit, GLuint sampler );
void glSamplerParameteri( GLuint sampler, GLenum pname, GLint param );
void glSamplerParameteriv( GLuint sampler, GLenum pname, const GLint *param );
void glSamplerParameterf( GLuint sampler, GLenum pname, GLfloat param );
void glSamplerParameterfv( GLuint sampler, GLenum pname, const GLfloat *param );
void glSamplerParameterIiv( GLuint sampler, GLenum pname, const GLint *param );
void glSamplerParameterIuiv( GLuint sampler, GLenum pname, const GLuint *param );
void glGetSamplerParameteriv( GLuint sampler, GLenum pname, GLint *params );
void glGetSamplerParameterIiv( GLuint sampler, GLenum pname, GLint *params );
void glGetSamplerParameterfv( GLuint sampler, GLenum pname, GLfloat *params );
void glGetSamplerParameterIfv( GLuint sampler, GLenum pname, GLfloat *params );
#endif

#ifndef GL_ARB_timer_query
#define GL_ARB_timer_query 1
void glQueryCounter( GLuint id, GLenum target );
void glGetQueryObjecti64v( GLuint id, GLenum pname, GLint64 *params );
void glGetQueryObjectui64v( GLuint id, GLenum pname, GLuint64 *params );
#endif

#ifndef GL_ARB_vertex_type_2_10_10_10_rev
#define GL_ARB_vertex_type_2_10_10_10_rev 1
void glVertexP2ui( GLenum type, GLuint value );
void glVertexP2uiv( GLenum type, const GLuint *value );
void glVertexP3ui( GLenum type, GLuint value );
void glVertexP3uiv( GLenum type, const GLuint *value );
void glVertexP4ui( GLenum type, GLuint value );
void glVertexP4uiv( GLenum type, const GLuint *value );
void glTexCoordP1ui( GLenum type, GLuint coords );
void glTexCoordP1uiv( GLenum type, const GLuint *coords );
void glTexCoordP2ui( GLenum type, GLuint coords );
void glTexCoordP2uiv( GLenum type, const GLuint *coords );
void glTexCoordP3ui( GLenum type, GLuint coords );
void glTexCoordP3uiv( GLenum type, const GLuint *coords );
void glTexCoordP4ui( GLenum type, GLuint coords );
void glTexCoordP4uiv( GLenum type, const GLuint *coords );
void glMultiTexCoordP1ui( GLenum texture, GLenum type, GLuint coords );
void glMultiTexCoordP1uiv( GLenum texture, GLenum type, const GLuint *coords );
void glMultiTexCoordP2ui( GLenum texture, GLenum type, GLuint coords );
void glMultiTexCoordP2uiv( GLenum texture, GLenum type, const GLuint *coords );
void glMultiTexCoordP3ui( GLenum texture, GLenum type, GLuint coords );
void glMultiTexCoordP3uiv( GLenum texture, GLenum type, const GLuint *coords );
void glMultiTexCoordP4ui( GLenum texture, GLenum type, GLuint coords );
void glMultiTexCoordP4uiv( GLenum texture, GLenum type, const GLuint *coords );
void glNormalP3ui( GLenum type, GLuint coords );
void glNormalP3uiv( GLenum type, const GLuint *coords );
void glColorP3ui( GLenum type, GLuint color );
void glColorP3uiv( GLenum type, const GLuint *color );
void glColorP4ui( GLenum type, GLuint color );
void glColorP4uiv( GLenum type, const GLuint *color );
void glSecondaryColorP3ui( GLenum type, GLuint color );
void glSecondaryColorP3uiv( GLenum type, const GLuint *color );
void glVertexAttribP1ui( GLuint index, GLenum type, GLboolean normalized, GLuint value );
void glVertexAttribP1uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value );
void glVertexAttribP2ui( GLuint index, GLenum type, GLboolean normalized, GLuint value );
void glVertexAttribP2uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value );
void glVertexAttribP3ui( GLuint index, GLenum type, GLboolean normalized, GLuint value );
void glVertexAttribP3uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value );
void glVertexAttribP4ui( GLuint index, GLenum type, GLboolean normalized, GLuint value );
void glVertexAttribP4uiv( GLuint index, GLenum type, GLboolean normalized, const GLuint *value );
#endif

#ifndef GL_ARB_draw_indirect
#define GL_ARB_draw_indirect 1
void glDrawArraysIndirect( GLenum mode, const GLvoid *indirect );
void glDrawElementsIndirect( GLenum mode, GLenum type, const GLvoid *indirect );
#endif

#ifndef GL_ARB_gpu_shader_fp64
#define GL_ARB_gpu_shader_fp64 1
void glUniform1d( GLint location, GLdouble x );
void glUniform2d( GLint location, GLdouble x, GLdouble y );
void glUniform3d( GLint location, GLdouble x, GLdouble y, GLdouble z );
void glUniform4d( GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
void glUniform1dv( GLint location, GLsizei count, const GLdouble *value );
void glUniform2dv( GLint location, GLsizei count, const GLdouble *value );
void glUniform3dv( GLint location, GLsizei count, const GLdouble *value );
void glUniform4dv( GLint location, GLsizei count, const GLdouble *value );
void glUniformMatrix2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix2x3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix2x4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix3x2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix3x4dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix4x2dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glUniformMatrix4x3dv( GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glGetUniformdv( GLuint program, GLint location, GLdouble *params );
void glProgramUniform1dEXT( GLuint program, GLint location, GLdouble x );
void glProgramUniform2dEXT( GLuint program, GLint location, GLdouble x, GLdouble y );
void glProgramUniform3dEXT( GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z );
void glProgramUniform4dEXT( GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
void glProgramUniform1dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value );
void glProgramUniform2dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value );
void glProgramUniform3dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value );
void glProgramUniform4dvEXT( GLuint program, GLint location, GLsizei count, const GLdouble *value );
void glProgramUniformMatrix2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix2x3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix2x4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix3x2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix3x4dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix4x2dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
void glProgramUniformMatrix4x3dvEXT( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value );
#endif

#ifndef GL_ARB_shader_subroutine
#define GL_ARB_shader_subroutine 1
GLint glGetSubroutineUniformLocation( GLuint program, GLenum shadertype, const GLchar *name );
GLuint glGetSubroutineIndex( GLuint program, GLenum shadertype, const GLchar *name );
void glGetActiveSubroutineUniformiv( GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values );
void glGetActiveSubroutineUniformName( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name );
void glGetActiveSubroutineName( GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name );
void glUniformSubroutinesuiv( GLenum shadertype, GLsizei count, const GLuint *indices );
void glGetUniformSubroutineuiv( GLenum shadertype, GLint location, GLuint *params );
void glGetProgramStageiv( GLuint program, GLenum shadertype, GLenum pname, GLint *values );
#endif

#ifndef GL_ARB_tessellation_shader
#define GL_ARB_tessellation_shader 1
void glPatchParameteri( GLenum pname, GLint value );
void glPatchParameterfv( GLenum pname, const GLfloat *values );
#endif

#ifndef GL_ARB_transform_feedback2
#define GL_ARB_transform_feedback2 1
void glBindTransformFeedback( GLenum target, GLuint id );
void glDeleteTransformFeedbacks( GLsizei n, const GLuint *ids );
void glGenTransformFeedbacks( GLsizei n, GLuint *ids );
GLboolean glIsTransformFeedback( GLuint id );
void glPauseTransformFeedback( void );
void glResumeTransformFeedback( void );
void glDrawTransformFeedback( GLenum mode, GLuint id );
#endif

#ifndef GL_ARB_transform_feedback3
#define GL_ARB_transform_feedback3 1
void glDrawTransformFeedbackStream( GLenum mode, GLuint id, GLuint stream );
void glBeginQueryIndexed( GLenum target, GLuint index, GLuint id );
void glEndQueryIndexed( GLenum target, GLuint index );
void glGetQueryIndexediv( GLenum target, GLuint index, GLenum pname, GLint *params );
#endif

#endif