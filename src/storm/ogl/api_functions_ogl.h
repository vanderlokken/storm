#pragma once

#include <string_view>

#ifdef _WIN32
#include <storm/win/api_win.h>
#endif

// Unpacked from contrib/glcorearb-*.tar.gz
#include <GL/glcorearb.h>

#ifdef _WIN32
// Unpacked from contrib/wglext-*.tar.gz
#include <GL/wglext.h>
#endif

#ifdef __linux__
// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>

// They come from the 'X11/Xlib.h' header
#undef True
#undef False
#endif

namespace storm {

template <class ApiFunctionType>
struct ApiFunctionOgl {
    using Type = ApiFunctionType;

    ApiFunctionType value = nullptr;
};

struct GlCullFace :
    ApiFunctionOgl<PFNGLCULLFACEPROC>
{
    static constexpr std::string_view Name =
        "glCullFace";
};

struct GlFrontFace :
    ApiFunctionOgl<PFNGLFRONTFACEPROC>
{
    static constexpr std::string_view Name =
        "glFrontFace";
};

struct GlHint :
    ApiFunctionOgl<PFNGLHINTPROC>
{
    static constexpr std::string_view Name =
        "glHint";
};

struct GlLineWidth :
    ApiFunctionOgl<PFNGLLINEWIDTHPROC>
{
    static constexpr std::string_view Name =
        "glLineWidth";
};

struct GlPointSize :
    ApiFunctionOgl<PFNGLPOINTSIZEPROC>
{
    static constexpr std::string_view Name =
        "glPointSize";
};

struct GlPolygonMode :
    ApiFunctionOgl<PFNGLPOLYGONMODEPROC>
{
    static constexpr std::string_view Name =
        "glPolygonMode";
};

struct GlScissor :
    ApiFunctionOgl<PFNGLSCISSORPROC>
{
    static constexpr std::string_view Name =
        "glScissor";
};

struct GlTexParameterf :
    ApiFunctionOgl<PFNGLTEXPARAMETERFPROC>
{
    static constexpr std::string_view Name =
        "glTexParameterf";
};

struct GlTexParameterfv :
    ApiFunctionOgl<PFNGLTEXPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glTexParameterfv";
};

struct GlTexParameteri :
    ApiFunctionOgl<PFNGLTEXPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glTexParameteri";
};

struct GlTexParameteriv :
    ApiFunctionOgl<PFNGLTEXPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glTexParameteriv";
};

struct GlTexImage1D :
    ApiFunctionOgl<PFNGLTEXIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glTexImage1D";
};

struct GlTexImage2D :
    ApiFunctionOgl<PFNGLTEXIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glTexImage2D";
};

struct GlDrawBuffer :
    ApiFunctionOgl<PFNGLDRAWBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glDrawBuffer";
};

struct GlClear :
    ApiFunctionOgl<PFNGLCLEARPROC>
{
    static constexpr std::string_view Name =
        "glClear";
};

struct GlClearColor :
    ApiFunctionOgl<PFNGLCLEARCOLORPROC>
{
    static constexpr std::string_view Name =
        "glClearColor";
};

struct GlClearStencil :
    ApiFunctionOgl<PFNGLCLEARSTENCILPROC>
{
    static constexpr std::string_view Name =
        "glClearStencil";
};

struct GlClearDepth :
    ApiFunctionOgl<PFNGLCLEARDEPTHPROC>
{
    static constexpr std::string_view Name =
        "glClearDepth";
};

struct GlStencilMask :
    ApiFunctionOgl<PFNGLSTENCILMASKPROC>
{
    static constexpr std::string_view Name =
        "glStencilMask";
};

struct GlColorMask :
    ApiFunctionOgl<PFNGLCOLORMASKPROC>
{
    static constexpr std::string_view Name =
        "glColorMask";
};

struct GlDepthMask :
    ApiFunctionOgl<PFNGLDEPTHMASKPROC>
{
    static constexpr std::string_view Name =
        "glDepthMask";
};

struct GlDisable :
    ApiFunctionOgl<PFNGLDISABLEPROC>
{
    static constexpr std::string_view Name =
        "glDisable";
};

struct GlEnable :
    ApiFunctionOgl<PFNGLENABLEPROC>
{
    static constexpr std::string_view Name =
        "glEnable";
};

struct GlFinish :
    ApiFunctionOgl<PFNGLFINISHPROC>
{
    static constexpr std::string_view Name =
        "glFinish";
};

struct GlFlush :
    ApiFunctionOgl<PFNGLFLUSHPROC>
{
    static constexpr std::string_view Name =
        "glFlush";
};

struct GlBlendFunc :
    ApiFunctionOgl<PFNGLBLENDFUNCPROC>
{
    static constexpr std::string_view Name =
        "glBlendFunc";
};

struct GlLogicOp :
    ApiFunctionOgl<PFNGLLOGICOPPROC>
{
    static constexpr std::string_view Name =
        "glLogicOp";
};

struct GlStencilFunc :
    ApiFunctionOgl<PFNGLSTENCILFUNCPROC>
{
    static constexpr std::string_view Name =
        "glStencilFunc";
};

struct GlStencilOp :
    ApiFunctionOgl<PFNGLSTENCILOPPROC>
{
    static constexpr std::string_view Name =
        "glStencilOp";
};

struct GlDepthFunc :
    ApiFunctionOgl<PFNGLDEPTHFUNCPROC>
{
    static constexpr std::string_view Name =
        "glDepthFunc";
};

struct GlPixelStoref :
    ApiFunctionOgl<PFNGLPIXELSTOREFPROC>
{
    static constexpr std::string_view Name =
        "glPixelStoref";
};

struct GlPixelStorei :
    ApiFunctionOgl<PFNGLPIXELSTOREIPROC>
{
    static constexpr std::string_view Name =
        "glPixelStorei";
};

struct GlReadBuffer :
    ApiFunctionOgl<PFNGLREADBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glReadBuffer";
};

struct GlReadPixels :
    ApiFunctionOgl<PFNGLREADPIXELSPROC>
{
    static constexpr std::string_view Name =
        "glReadPixels";
};

struct GlGetBooleanv :
    ApiFunctionOgl<PFNGLGETBOOLEANVPROC>
{
    static constexpr std::string_view Name =
        "glGetBooleanv";
};

struct GlGetDoublev :
    ApiFunctionOgl<PFNGLGETDOUBLEVPROC>
{
    static constexpr std::string_view Name =
        "glGetDoublev";
};

struct GlGetError :
    ApiFunctionOgl<PFNGLGETERRORPROC>
{
    static constexpr std::string_view Name =
        "glGetError";
};

struct GlGetFloatv :
    ApiFunctionOgl<PFNGLGETFLOATVPROC>
{
    static constexpr std::string_view Name =
        "glGetFloatv";
};

struct GlGetIntegerv :
    ApiFunctionOgl<PFNGLGETINTEGERVPROC>
{
    static constexpr std::string_view Name =
        "glGetIntegerv";
};

struct GlGetString :
    ApiFunctionOgl<PFNGLGETSTRINGPROC>
{
    static constexpr std::string_view Name =
        "glGetString";
};

struct GlGetTexImage :
    ApiFunctionOgl<PFNGLGETTEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetTexImage";
};

struct GlGetTexParameterfv :
    ApiFunctionOgl<PFNGLGETTEXPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexParameterfv";
};

struct GlGetTexParameteriv :
    ApiFunctionOgl<PFNGLGETTEXPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexParameteriv";
};

struct GlGetTexLevelParameterfv :
    ApiFunctionOgl<PFNGLGETTEXLEVELPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexLevelParameterfv";
};

struct GlGetTexLevelParameteriv :
    ApiFunctionOgl<PFNGLGETTEXLEVELPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexLevelParameteriv";
};

struct GlIsEnabled :
    ApiFunctionOgl<PFNGLISENABLEDPROC>
{
    static constexpr std::string_view Name =
        "glIsEnabled";
};

struct GlDepthRange :
    ApiFunctionOgl<PFNGLDEPTHRANGEPROC>
{
    static constexpr std::string_view Name =
        "glDepthRange";
};

struct GlViewport :
    ApiFunctionOgl<PFNGLVIEWPORTPROC>
{
    static constexpr std::string_view Name =
        "glViewport";
};

struct GlDrawArrays :
    ApiFunctionOgl<PFNGLDRAWARRAYSPROC>
{
    static constexpr std::string_view Name =
        "glDrawArrays";
};

struct GlDrawElements :
    ApiFunctionOgl<PFNGLDRAWELEMENTSPROC>
{
    static constexpr std::string_view Name =
        "glDrawElements";
};

struct GlGetPointerv :
    ApiFunctionOgl<PFNGLGETPOINTERVPROC>
{
    static constexpr std::string_view Name =
        "glGetPointerv";
};

struct GlPolygonOffset :
    ApiFunctionOgl<PFNGLPOLYGONOFFSETPROC>
{
    static constexpr std::string_view Name =
        "glPolygonOffset";
};

struct GlCopyTexImage1D :
    ApiFunctionOgl<PFNGLCOPYTEXIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTexImage1D";
};

struct GlCopyTexImage2D :
    ApiFunctionOgl<PFNGLCOPYTEXIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTexImage2D";
};

struct GlCopyTexSubImage1D :
    ApiFunctionOgl<PFNGLCOPYTEXSUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTexSubImage1D";
};

struct GlCopyTexSubImage2D :
    ApiFunctionOgl<PFNGLCOPYTEXSUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTexSubImage2D";
};

struct GlTexSubImage1D :
    ApiFunctionOgl<PFNGLTEXSUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glTexSubImage1D";
};

struct GlTexSubImage2D :
    ApiFunctionOgl<PFNGLTEXSUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glTexSubImage2D";
};

struct GlBindTexture :
    ApiFunctionOgl<PFNGLBINDTEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glBindTexture";
};

struct GlDeleteTextures :
    ApiFunctionOgl<PFNGLDELETETEXTURESPROC>
{
    static constexpr std::string_view Name =
        "glDeleteTextures";
};

struct GlGenTextures :
    ApiFunctionOgl<PFNGLGENTEXTURESPROC>
{
    static constexpr std::string_view Name =
        "glGenTextures";
};

struct GlIsTexture :
    ApiFunctionOgl<PFNGLISTEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glIsTexture";
};

struct GlDrawRangeElements :
    ApiFunctionOgl<PFNGLDRAWRANGEELEMENTSPROC>
{
    static constexpr std::string_view Name =
        "glDrawRangeElements";
};

struct GlTexImage3D :
    ApiFunctionOgl<PFNGLTEXIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glTexImage3D";
};

struct GlTexSubImage3D :
    ApiFunctionOgl<PFNGLTEXSUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glTexSubImage3D";
};

struct GlCopyTexSubImage3D :
    ApiFunctionOgl<PFNGLCOPYTEXSUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTexSubImage3D";
};

struct GlActiveTexture :
    ApiFunctionOgl<PFNGLACTIVETEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glActiveTexture";
};

struct GlSampleCoverage :
    ApiFunctionOgl<PFNGLSAMPLECOVERAGEPROC>
{
    static constexpr std::string_view Name =
        "glSampleCoverage";
};

struct GlCompressedTexImage3D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexImage3D";
};

struct GlCompressedTexImage2D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexImage2D";
};

struct GlCompressedTexImage1D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexImage1D";
};

struct GlCompressedTexSubImage3D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexSubImage3D";
};

struct GlCompressedTexSubImage2D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexSubImage2D";
};

struct GlCompressedTexSubImage1D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTexSubImage1D";
};

struct GlGetCompressedTexImage :
    ApiFunctionOgl<PFNGLGETCOMPRESSEDTEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetCompressedTexImage";
};

struct GlBlendFuncSeparate :
    ApiFunctionOgl<PFNGLBLENDFUNCSEPARATEPROC>
{
    static constexpr std::string_view Name =
        "glBlendFuncSeparate";
};

struct GlMultiDrawArrays :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArrays";
};

struct GlMultiDrawElements :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElements";
};

struct GlPointParameterf :
    ApiFunctionOgl<PFNGLPOINTPARAMETERFPROC>
{
    static constexpr std::string_view Name =
        "glPointParameterf";
};

struct GlPointParameterfv :
    ApiFunctionOgl<PFNGLPOINTPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glPointParameterfv";
};

struct GlPointParameteri :
    ApiFunctionOgl<PFNGLPOINTPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glPointParameteri";
};

struct GlPointParameteriv :
    ApiFunctionOgl<PFNGLPOINTPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glPointParameteriv";
};

struct GlBlendColor :
    ApiFunctionOgl<PFNGLBLENDCOLORPROC>
{
    static constexpr std::string_view Name =
        "glBlendColor";
};

struct GlBlendEquation :
    ApiFunctionOgl<PFNGLBLENDEQUATIONPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquation";
};

struct GlGenQueries :
    ApiFunctionOgl<PFNGLGENQUERIESPROC>
{
    static constexpr std::string_view Name =
        "glGenQueries";
};

struct GlDeleteQueries :
    ApiFunctionOgl<PFNGLDELETEQUERIESPROC>
{
    static constexpr std::string_view Name =
        "glDeleteQueries";
};

struct GlIsQuery :
    ApiFunctionOgl<PFNGLISQUERYPROC>
{
    static constexpr std::string_view Name =
        "glIsQuery";
};

struct GlBeginQuery :
    ApiFunctionOgl<PFNGLBEGINQUERYPROC>
{
    static constexpr std::string_view Name =
        "glBeginQuery";
};

struct GlEndQuery :
    ApiFunctionOgl<PFNGLENDQUERYPROC>
{
    static constexpr std::string_view Name =
        "glEndQuery";
};

struct GlGetQueryiv :
    ApiFunctionOgl<PFNGLGETQUERYIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryiv";
};

struct GlGetQueryObjectiv :
    ApiFunctionOgl<PFNGLGETQUERYOBJECTIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryObjectiv";
};

struct GlGetQueryObjectuiv :
    ApiFunctionOgl<PFNGLGETQUERYOBJECTUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryObjectuiv";
};

struct GlBindBuffer :
    ApiFunctionOgl<PFNGLBINDBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBindBuffer";
};

struct GlDeleteBuffers :
    ApiFunctionOgl<PFNGLDELETEBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteBuffers";
};

struct GlGenBuffers :
    ApiFunctionOgl<PFNGLGENBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glGenBuffers";
};

struct GlIsBuffer :
    ApiFunctionOgl<PFNGLISBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glIsBuffer";
};

struct GlBufferData :
    ApiFunctionOgl<PFNGLBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glBufferData";
};

struct GlBufferSubData :
    ApiFunctionOgl<PFNGLBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glBufferSubData";
};

struct GlGetBufferSubData :
    ApiFunctionOgl<PFNGLGETBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glGetBufferSubData";
};

struct GlMapBuffer :
    ApiFunctionOgl<PFNGLMAPBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glMapBuffer";
};

struct GlUnmapBuffer :
    ApiFunctionOgl<PFNGLUNMAPBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glUnmapBuffer";
};

struct GlGetBufferParameteriv :
    ApiFunctionOgl<PFNGLGETBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetBufferParameteriv";
};

struct GlGetBufferPointerv :
    ApiFunctionOgl<PFNGLGETBUFFERPOINTERVPROC>
{
    static constexpr std::string_view Name =
        "glGetBufferPointerv";
};

struct GlBlendEquationSeparate :
    ApiFunctionOgl<PFNGLBLENDEQUATIONSEPARATEPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquationSeparate";
};

struct GlDrawBuffers :
    ApiFunctionOgl<PFNGLDRAWBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glDrawBuffers";
};

struct GlStencilOpSeparate :
    ApiFunctionOgl<PFNGLSTENCILOPSEPARATEPROC>
{
    static constexpr std::string_view Name =
        "glStencilOpSeparate";
};

struct GlStencilFuncSeparate :
    ApiFunctionOgl<PFNGLSTENCILFUNCSEPARATEPROC>
{
    static constexpr std::string_view Name =
        "glStencilFuncSeparate";
};

struct GlStencilMaskSeparate :
    ApiFunctionOgl<PFNGLSTENCILMASKSEPARATEPROC>
{
    static constexpr std::string_view Name =
        "glStencilMaskSeparate";
};

struct GlAttachShader :
    ApiFunctionOgl<PFNGLATTACHSHADERPROC>
{
    static constexpr std::string_view Name =
        "glAttachShader";
};

struct GlBindAttribLocation :
    ApiFunctionOgl<PFNGLBINDATTRIBLOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glBindAttribLocation";
};

struct GlCompileShader :
    ApiFunctionOgl<PFNGLCOMPILESHADERPROC>
{
    static constexpr std::string_view Name =
        "glCompileShader";
};

struct GlCreateProgram :
    ApiFunctionOgl<PFNGLCREATEPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glCreateProgram";
};

struct GlCreateShader :
    ApiFunctionOgl<PFNGLCREATESHADERPROC>
{
    static constexpr std::string_view Name =
        "glCreateShader";
};

struct GlDeleteProgram :
    ApiFunctionOgl<PFNGLDELETEPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glDeleteProgram";
};

struct GlDeleteShader :
    ApiFunctionOgl<PFNGLDELETESHADERPROC>
{
    static constexpr std::string_view Name =
        "glDeleteShader";
};

struct GlDetachShader :
    ApiFunctionOgl<PFNGLDETACHSHADERPROC>
{
    static constexpr std::string_view Name =
        "glDetachShader";
};

struct GlDisableVertexAttribArray :
    ApiFunctionOgl<PFNGLDISABLEVERTEXATTRIBARRAYPROC>
{
    static constexpr std::string_view Name =
        "glDisableVertexAttribArray";
};

struct GlEnableVertexAttribArray :
    ApiFunctionOgl<PFNGLENABLEVERTEXATTRIBARRAYPROC>
{
    static constexpr std::string_view Name =
        "glEnableVertexAttribArray";
};

struct GlGetActiveAttrib :
    ApiFunctionOgl<PFNGLGETACTIVEATTRIBPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveAttrib";
};

struct GlGetActiveUniform :
    ApiFunctionOgl<PFNGLGETACTIVEUNIFORMPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveUniform";
};

struct GlGetAttachedShaders :
    ApiFunctionOgl<PFNGLGETATTACHEDSHADERSPROC>
{
    static constexpr std::string_view Name =
        "glGetAttachedShaders";
};

struct GlGetAttribLocation :
    ApiFunctionOgl<PFNGLGETATTRIBLOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glGetAttribLocation";
};

struct GlGetProgramiv :
    ApiFunctionOgl<PFNGLGETPROGRAMIVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramiv";
};

struct GlGetProgramInfoLog :
    ApiFunctionOgl<PFNGLGETPROGRAMINFOLOGPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramInfoLog";
};

struct GlGetShaderiv :
    ApiFunctionOgl<PFNGLGETSHADERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetShaderiv";
};

struct GlGetShaderInfoLog :
    ApiFunctionOgl<PFNGLGETSHADERINFOLOGPROC>
{
    static constexpr std::string_view Name =
        "glGetShaderInfoLog";
};

struct GlGetShaderSource :
    ApiFunctionOgl<PFNGLGETSHADERSOURCEPROC>
{
    static constexpr std::string_view Name =
        "glGetShaderSource";
};

struct GlGetUniformLocation :
    ApiFunctionOgl<PFNGLGETUNIFORMLOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformLocation";
};

struct GlGetUniformfv :
    ApiFunctionOgl<PFNGLGETUNIFORMFVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformfv";
};

struct GlGetUniformiv :
    ApiFunctionOgl<PFNGLGETUNIFORMIVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformiv";
};

struct GlGetVertexAttribdv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBDVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribdv";
};

struct GlGetVertexAttribfv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBFVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribfv";
};

struct GlGetVertexAttribiv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBIVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribiv";
};

struct GlGetVertexAttribPointerv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBPOINTERVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribPointerv";
};

struct GlIsProgram :
    ApiFunctionOgl<PFNGLISPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glIsProgram";
};

struct GlIsShader :
    ApiFunctionOgl<PFNGLISSHADERPROC>
{
    static constexpr std::string_view Name =
        "glIsShader";
};

struct GlLinkProgram :
    ApiFunctionOgl<PFNGLLINKPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glLinkProgram";
};

struct GlShaderSource :
    ApiFunctionOgl<PFNGLSHADERSOURCEPROC>
{
    static constexpr std::string_view Name =
        "glShaderSource";
};

struct GlUseProgram :
    ApiFunctionOgl<PFNGLUSEPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glUseProgram";
};

struct GlUniform1f :
    ApiFunctionOgl<PFNGLUNIFORM1FPROC>
{
    static constexpr std::string_view Name =
        "glUniform1f";
};

struct GlUniform2f :
    ApiFunctionOgl<PFNGLUNIFORM2FPROC>
{
    static constexpr std::string_view Name =
        "glUniform2f";
};

struct GlUniform3f :
    ApiFunctionOgl<PFNGLUNIFORM3FPROC>
{
    static constexpr std::string_view Name =
        "glUniform3f";
};

struct GlUniform4f :
    ApiFunctionOgl<PFNGLUNIFORM4FPROC>
{
    static constexpr std::string_view Name =
        "glUniform4f";
};

struct GlUniform1i :
    ApiFunctionOgl<PFNGLUNIFORM1IPROC>
{
    static constexpr std::string_view Name =
        "glUniform1i";
};

struct GlUniform2i :
    ApiFunctionOgl<PFNGLUNIFORM2IPROC>
{
    static constexpr std::string_view Name =
        "glUniform2i";
};

struct GlUniform3i :
    ApiFunctionOgl<PFNGLUNIFORM3IPROC>
{
    static constexpr std::string_view Name =
        "glUniform3i";
};

struct GlUniform4i :
    ApiFunctionOgl<PFNGLUNIFORM4IPROC>
{
    static constexpr std::string_view Name =
        "glUniform4i";
};

struct GlUniform1fv :
    ApiFunctionOgl<PFNGLUNIFORM1FVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1fv";
};

struct GlUniform2fv :
    ApiFunctionOgl<PFNGLUNIFORM2FVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2fv";
};

struct GlUniform3fv :
    ApiFunctionOgl<PFNGLUNIFORM3FVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3fv";
};

struct GlUniform4fv :
    ApiFunctionOgl<PFNGLUNIFORM4FVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4fv";
};

struct GlUniform1iv :
    ApiFunctionOgl<PFNGLUNIFORM1IVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1iv";
};

struct GlUniform2iv :
    ApiFunctionOgl<PFNGLUNIFORM2IVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2iv";
};

struct GlUniform3iv :
    ApiFunctionOgl<PFNGLUNIFORM3IVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3iv";
};

struct GlUniform4iv :
    ApiFunctionOgl<PFNGLUNIFORM4IVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4iv";
};

struct GlUniformMatrix2fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2fv";
};

struct GlUniformMatrix3fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3fv";
};

struct GlUniformMatrix4fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4fv";
};

struct GlValidateProgram :
    ApiFunctionOgl<PFNGLVALIDATEPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glValidateProgram";
};

struct GlVertexAttrib1d :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1d";
};

struct GlVertexAttrib1dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1dv";
};

struct GlVertexAttrib1f :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1FPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1f";
};

struct GlVertexAttrib1fv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1FVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1fv";
};

struct GlVertexAttrib1s :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1SPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1s";
};

struct GlVertexAttrib1sv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB1SVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib1sv";
};

struct GlVertexAttrib2d :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2d";
};

struct GlVertexAttrib2dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2dv";
};

struct GlVertexAttrib2f :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2FPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2f";
};

struct GlVertexAttrib2fv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2FVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2fv";
};

struct GlVertexAttrib2s :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2SPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2s";
};

struct GlVertexAttrib2sv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB2SVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib2sv";
};

struct GlVertexAttrib3d :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3d";
};

struct GlVertexAttrib3dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3dv";
};

struct GlVertexAttrib3f :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3FPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3f";
};

struct GlVertexAttrib3fv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3FVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3fv";
};

struct GlVertexAttrib3s :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3SPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3s";
};

struct GlVertexAttrib3sv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB3SVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib3sv";
};

struct GlVertexAttrib4Nbv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NBVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nbv";
};

struct GlVertexAttrib4Niv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Niv";
};

struct GlVertexAttrib4Nsv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NSVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nsv";
};

struct GlVertexAttrib4Nub :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NUBPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nub";
};

struct GlVertexAttrib4Nubv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NUBVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nubv";
};

struct GlVertexAttrib4Nuiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NUIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nuiv";
};

struct GlVertexAttrib4Nusv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4NUSVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4Nusv";
};

struct GlVertexAttrib4bv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4BVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4bv";
};

struct GlVertexAttrib4d :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4d";
};

struct GlVertexAttrib4dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4dv";
};

struct GlVertexAttrib4f :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4FPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4f";
};

struct GlVertexAttrib4fv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4FVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4fv";
};

struct GlVertexAttrib4iv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4IVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4iv";
};

struct GlVertexAttrib4s :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4SPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4s";
};

struct GlVertexAttrib4sv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4SVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4sv";
};

struct GlVertexAttrib4ubv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4UBVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4ubv";
};

struct GlVertexAttrib4uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4uiv";
};

struct GlVertexAttrib4usv :
    ApiFunctionOgl<PFNGLVERTEXATTRIB4USVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttrib4usv";
};

struct GlVertexAttribPointer :
    ApiFunctionOgl<PFNGLVERTEXATTRIBPOINTERPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribPointer";
};

struct GlUniformMatrix2x3fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2X3FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2x3fv";
};

struct GlUniformMatrix3x2fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3X2FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3x2fv";
};

struct GlUniformMatrix2x4fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2X4FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2x4fv";
};

struct GlUniformMatrix4x2fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4X2FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4x2fv";
};

struct GlUniformMatrix3x4fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3X4FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3x4fv";
};

struct GlUniformMatrix4x3fv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4X3FVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4x3fv";
};

struct GlColorMaski :
    ApiFunctionOgl<PFNGLCOLORMASKIPROC>
{
    static constexpr std::string_view Name =
        "glColorMaski";
};

struct GlGetBooleani_v :
    ApiFunctionOgl<PFNGLGETBOOLEANI_VPROC>
{
    static constexpr std::string_view Name =
        "glGetBooleani_v";
};

struct GlGetIntegeri_v :
    ApiFunctionOgl<PFNGLGETINTEGERI_VPROC>
{
    static constexpr std::string_view Name =
        "glGetIntegeri_v";
};

struct GlEnablei :
    ApiFunctionOgl<PFNGLENABLEIPROC>
{
    static constexpr std::string_view Name =
        "glEnablei";
};

struct GlDisablei :
    ApiFunctionOgl<PFNGLDISABLEIPROC>
{
    static constexpr std::string_view Name =
        "glDisablei";
};

struct GlIsEnabledi :
    ApiFunctionOgl<PFNGLISENABLEDIPROC>
{
    static constexpr std::string_view Name =
        "glIsEnabledi";
};

struct GlBeginTransformFeedback :
    ApiFunctionOgl<PFNGLBEGINTRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glBeginTransformFeedback";
};

struct GlEndTransformFeedback :
    ApiFunctionOgl<PFNGLENDTRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glEndTransformFeedback";
};

struct GlBindBufferRange :
    ApiFunctionOgl<PFNGLBINDBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glBindBufferRange";
};

struct GlBindBufferBase :
    ApiFunctionOgl<PFNGLBINDBUFFERBASEPROC>
{
    static constexpr std::string_view Name =
        "glBindBufferBase";
};

struct GlTransformFeedbackVaryings :
    ApiFunctionOgl<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>
{
    static constexpr std::string_view Name =
        "glTransformFeedbackVaryings";
};

struct GlGetTransformFeedbackVarying :
    ApiFunctionOgl<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>
{
    static constexpr std::string_view Name =
        "glGetTransformFeedbackVarying";
};

struct GlClampColor :
    ApiFunctionOgl<PFNGLCLAMPCOLORPROC>
{
    static constexpr std::string_view Name =
        "glClampColor";
};

struct GlBeginConditionalRender :
    ApiFunctionOgl<PFNGLBEGINCONDITIONALRENDERPROC>
{
    static constexpr std::string_view Name =
        "glBeginConditionalRender";
};

struct GlEndConditionalRender :
    ApiFunctionOgl<PFNGLENDCONDITIONALRENDERPROC>
{
    static constexpr std::string_view Name =
        "glEndConditionalRender";
};

struct GlVertexAttribIPointer :
    ApiFunctionOgl<PFNGLVERTEXATTRIBIPOINTERPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribIPointer";
};

struct GlGetVertexAttribIiv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBIIVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribIiv";
};

struct GlGetVertexAttribIuiv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBIUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribIuiv";
};

struct GlVertexAttribI1i :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI1IPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI1i";
};

struct GlVertexAttribI2i :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI2IPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI2i";
};

struct GlVertexAttribI3i :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI3IPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI3i";
};

struct GlVertexAttribI4i :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4IPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4i";
};

struct GlVertexAttribI1ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI1UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI1ui";
};

struct GlVertexAttribI2ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI2UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI2ui";
};

struct GlVertexAttribI3ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI3UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI3ui";
};

struct GlVertexAttribI4ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4ui";
};

struct GlVertexAttribI1iv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI1IVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI1iv";
};

struct GlVertexAttribI2iv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI2IVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI2iv";
};

struct GlVertexAttribI3iv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI3IVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI3iv";
};

struct GlVertexAttribI4iv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4IVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4iv";
};

struct GlVertexAttribI1uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI1UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI1uiv";
};

struct GlVertexAttribI2uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI2UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI2uiv";
};

struct GlVertexAttribI3uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI3UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI3uiv";
};

struct GlVertexAttribI4uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4uiv";
};

struct GlVertexAttribI4bv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4BVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4bv";
};

struct GlVertexAttribI4sv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4SVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4sv";
};

struct GlVertexAttribI4ubv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4UBVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4ubv";
};

struct GlVertexAttribI4usv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBI4USVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribI4usv";
};

struct GlGetUniformuiv :
    ApiFunctionOgl<PFNGLGETUNIFORMUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformuiv";
};

struct GlBindFragDataLocation :
    ApiFunctionOgl<PFNGLBINDFRAGDATALOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glBindFragDataLocation";
};

struct GlGetFragDataLocation :
    ApiFunctionOgl<PFNGLGETFRAGDATALOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glGetFragDataLocation";
};

struct GlUniform1ui :
    ApiFunctionOgl<PFNGLUNIFORM1UIPROC>
{
    static constexpr std::string_view Name =
        "glUniform1ui";
};

struct GlUniform2ui :
    ApiFunctionOgl<PFNGLUNIFORM2UIPROC>
{
    static constexpr std::string_view Name =
        "glUniform2ui";
};

struct GlUniform3ui :
    ApiFunctionOgl<PFNGLUNIFORM3UIPROC>
{
    static constexpr std::string_view Name =
        "glUniform3ui";
};

struct GlUniform4ui :
    ApiFunctionOgl<PFNGLUNIFORM4UIPROC>
{
    static constexpr std::string_view Name =
        "glUniform4ui";
};

struct GlUniform1uiv :
    ApiFunctionOgl<PFNGLUNIFORM1UIVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1uiv";
};

struct GlUniform2uiv :
    ApiFunctionOgl<PFNGLUNIFORM2UIVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2uiv";
};

struct GlUniform3uiv :
    ApiFunctionOgl<PFNGLUNIFORM3UIVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3uiv";
};

struct GlUniform4uiv :
    ApiFunctionOgl<PFNGLUNIFORM4UIVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4uiv";
};

struct GlTexParameterIiv :
    ApiFunctionOgl<PFNGLTEXPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glTexParameterIiv";
};

struct GlTexParameterIuiv :
    ApiFunctionOgl<PFNGLTEXPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glTexParameterIuiv";
};

struct GlGetTexParameterIiv :
    ApiFunctionOgl<PFNGLGETTEXPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexParameterIiv";
};

struct GlGetTexParameterIuiv :
    ApiFunctionOgl<PFNGLGETTEXPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTexParameterIuiv";
};

struct GlClearBufferiv :
    ApiFunctionOgl<PFNGLCLEARBUFFERIVPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferiv";
};

struct GlClearBufferuiv :
    ApiFunctionOgl<PFNGLCLEARBUFFERUIVPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferuiv";
};

struct GlClearBufferfv :
    ApiFunctionOgl<PFNGLCLEARBUFFERFVPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferfv";
};

struct GlClearBufferfi :
    ApiFunctionOgl<PFNGLCLEARBUFFERFIPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferfi";
};

struct GlGetStringi :
    ApiFunctionOgl<PFNGLGETSTRINGIPROC>
{
    static constexpr std::string_view Name =
        "glGetStringi";
};

struct GlIsRenderbuffer :
    ApiFunctionOgl<PFNGLISRENDERBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glIsRenderbuffer";
};

struct GlBindRenderbuffer :
    ApiFunctionOgl<PFNGLBINDRENDERBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBindRenderbuffer";
};

struct GlDeleteRenderbuffers :
    ApiFunctionOgl<PFNGLDELETERENDERBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteRenderbuffers";
};

struct GlGenRenderbuffers :
    ApiFunctionOgl<PFNGLGENRENDERBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glGenRenderbuffers";
};

struct GlRenderbufferStorage :
    ApiFunctionOgl<PFNGLRENDERBUFFERSTORAGEPROC>
{
    static constexpr std::string_view Name =
        "glRenderbufferStorage";
};

struct GlGetRenderbufferParameteriv :
    ApiFunctionOgl<PFNGLGETRENDERBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetRenderbufferParameteriv";
};

struct GlIsFramebuffer :
    ApiFunctionOgl<PFNGLISFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glIsFramebuffer";
};

struct GlBindFramebuffer :
    ApiFunctionOgl<PFNGLBINDFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBindFramebuffer";
};

struct GlDeleteFramebuffers :
    ApiFunctionOgl<PFNGLDELETEFRAMEBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteFramebuffers";
};

struct GlGenFramebuffers :
    ApiFunctionOgl<PFNGLGENFRAMEBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glGenFramebuffers";
};

struct GlCheckFramebufferStatus :
    ApiFunctionOgl<PFNGLCHECKFRAMEBUFFERSTATUSPROC>
{
    static constexpr std::string_view Name =
        "glCheckFramebufferStatus";
};

struct GlFramebufferTexture1D :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTURE1DPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTexture1D";
};

struct GlFramebufferTexture2D :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTURE2DPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTexture2D";
};

struct GlFramebufferTexture3D :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTURE3DPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTexture3D";
};

struct GlFramebufferRenderbuffer :
    ApiFunctionOgl<PFNGLFRAMEBUFFERRENDERBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferRenderbuffer";
};

struct GlGetFramebufferAttachmentParameteriv :
    ApiFunctionOgl<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetFramebufferAttachmentParameteriv";
};

struct GlGenerateMipmap :
    ApiFunctionOgl<PFNGLGENERATEMIPMAPPROC>
{
    static constexpr std::string_view Name =
        "glGenerateMipmap";
};

struct GlBlitFramebuffer :
    ApiFunctionOgl<PFNGLBLITFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBlitFramebuffer";
};

struct GlRenderbufferStorageMultisample :
    ApiFunctionOgl<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glRenderbufferStorageMultisample";
};

struct GlFramebufferTextureLayer :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTURELAYERPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTextureLayer";
};

struct GlMapBufferRange :
    ApiFunctionOgl<PFNGLMAPBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glMapBufferRange";
};

struct GlFlushMappedBufferRange :
    ApiFunctionOgl<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glFlushMappedBufferRange";
};

struct GlBindVertexArray :
    ApiFunctionOgl<PFNGLBINDVERTEXARRAYPROC>
{
    static constexpr std::string_view Name =
        "glBindVertexArray";
};

struct GlDeleteVertexArrays :
    ApiFunctionOgl<PFNGLDELETEVERTEXARRAYSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteVertexArrays";
};

struct GlGenVertexArrays :
    ApiFunctionOgl<PFNGLGENVERTEXARRAYSPROC>
{
    static constexpr std::string_view Name =
        "glGenVertexArrays";
};

struct GlIsVertexArray :
    ApiFunctionOgl<PFNGLISVERTEXARRAYPROC>
{
    static constexpr std::string_view Name =
        "glIsVertexArray";
};

struct GlDrawArraysInstanced :
    ApiFunctionOgl<PFNGLDRAWARRAYSINSTANCEDPROC>
{
    static constexpr std::string_view Name =
        "glDrawArraysInstanced";
};

struct GlDrawElementsInstanced :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstanced";
};

struct GlTexBuffer :
    ApiFunctionOgl<PFNGLTEXBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glTexBuffer";
};

struct GlPrimitiveRestartIndex :
    ApiFunctionOgl<PFNGLPRIMITIVERESTARTINDEXPROC>
{
    static constexpr std::string_view Name =
        "glPrimitiveRestartIndex";
};

struct GlCopyBufferSubData :
    ApiFunctionOgl<PFNGLCOPYBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glCopyBufferSubData";
};

struct GlGetUniformIndices :
    ApiFunctionOgl<PFNGLGETUNIFORMINDICESPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformIndices";
};

struct GlGetActiveUniformsiv :
    ApiFunctionOgl<PFNGLGETACTIVEUNIFORMSIVPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveUniformsiv";
};

struct GlGetActiveUniformName :
    ApiFunctionOgl<PFNGLGETACTIVEUNIFORMNAMEPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveUniformName";
};

struct GlGetUniformBlockIndex :
    ApiFunctionOgl<PFNGLGETUNIFORMBLOCKINDEXPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformBlockIndex";
};

struct GlGetActiveUniformBlockiv :
    ApiFunctionOgl<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveUniformBlockiv";
};

struct GlGetActiveUniformBlockName :
    ApiFunctionOgl<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveUniformBlockName";
};

struct GlUniformBlockBinding :
    ApiFunctionOgl<PFNGLUNIFORMBLOCKBINDINGPROC>
{
    static constexpr std::string_view Name =
        "glUniformBlockBinding";
};

struct GlDrawElementsBaseVertex :
    ApiFunctionOgl<PFNGLDRAWELEMENTSBASEVERTEXPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsBaseVertex";
};

struct GlDrawRangeElementsBaseVertex :
    ApiFunctionOgl<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>
{
    static constexpr std::string_view Name =
        "glDrawRangeElementsBaseVertex";
};

struct GlDrawElementsInstancedBaseVertex :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstancedBaseVertex";
};

struct GlMultiDrawElementsBaseVertex :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsBaseVertex";
};

struct GlProvokingVertex :
    ApiFunctionOgl<PFNGLPROVOKINGVERTEXPROC>
{
    static constexpr std::string_view Name =
        "glProvokingVertex";
};

struct GlFenceSync :
    ApiFunctionOgl<PFNGLFENCESYNCPROC>
{
    static constexpr std::string_view Name =
        "glFenceSync";
};

struct GlIsSync :
    ApiFunctionOgl<PFNGLISSYNCPROC>
{
    static constexpr std::string_view Name =
        "glIsSync";
};

struct GlDeleteSync :
    ApiFunctionOgl<PFNGLDELETESYNCPROC>
{
    static constexpr std::string_view Name =
        "glDeleteSync";
};

struct GlClientWaitSync :
    ApiFunctionOgl<PFNGLCLIENTWAITSYNCPROC>
{
    static constexpr std::string_view Name =
        "glClientWaitSync";
};

struct GlWaitSync :
    ApiFunctionOgl<PFNGLWAITSYNCPROC>
{
    static constexpr std::string_view Name =
        "glWaitSync";
};

struct GlGetInteger64v :
    ApiFunctionOgl<PFNGLGETINTEGER64VPROC>
{
    static constexpr std::string_view Name =
        "glGetInteger64v";
};

struct GlGetSynciv :
    ApiFunctionOgl<PFNGLGETSYNCIVPROC>
{
    static constexpr std::string_view Name =
        "glGetSynciv";
};

struct GlGetInteger64i_v :
    ApiFunctionOgl<PFNGLGETINTEGER64I_VPROC>
{
    static constexpr std::string_view Name =
        "glGetInteger64i_v";
};

struct GlGetBufferParameteri64v :
    ApiFunctionOgl<PFNGLGETBUFFERPARAMETERI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetBufferParameteri64v";
};

struct GlFramebufferTexture :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTexture";
};

struct GlTexImage2DMultisample :
    ApiFunctionOgl<PFNGLTEXIMAGE2DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTexImage2DMultisample";
};

struct GlTexImage3DMultisample :
    ApiFunctionOgl<PFNGLTEXIMAGE3DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTexImage3DMultisample";
};

struct GlGetMultisamplefv :
    ApiFunctionOgl<PFNGLGETMULTISAMPLEFVPROC>
{
    static constexpr std::string_view Name =
        "glGetMultisamplefv";
};

struct GlSampleMaski :
    ApiFunctionOgl<PFNGLSAMPLEMASKIPROC>
{
    static constexpr std::string_view Name =
        "glSampleMaski";
};

struct GlBindFragDataLocationIndexed :
    ApiFunctionOgl<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>
{
    static constexpr std::string_view Name =
        "glBindFragDataLocationIndexed";
};

struct GlGetFragDataIndex :
    ApiFunctionOgl<PFNGLGETFRAGDATAINDEXPROC>
{
    static constexpr std::string_view Name =
        "glGetFragDataIndex";
};

struct GlGenSamplers :
    ApiFunctionOgl<PFNGLGENSAMPLERSPROC>
{
    static constexpr std::string_view Name =
        "glGenSamplers";
};

struct GlDeleteSamplers :
    ApiFunctionOgl<PFNGLDELETESAMPLERSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteSamplers";
};

struct GlIsSampler :
    ApiFunctionOgl<PFNGLISSAMPLERPROC>
{
    static constexpr std::string_view Name =
        "glIsSampler";
};

struct GlBindSampler :
    ApiFunctionOgl<PFNGLBINDSAMPLERPROC>
{
    static constexpr std::string_view Name =
        "glBindSampler";
};

struct GlSamplerParameteri :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameteri";
};

struct GlSamplerParameteriv :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameteriv";
};

struct GlSamplerParameterf :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERFPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameterf";
};

struct GlSamplerParameterfv :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameterfv";
};

struct GlSamplerParameterIiv :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameterIiv";
};

struct GlSamplerParameterIuiv :
    ApiFunctionOgl<PFNGLSAMPLERPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glSamplerParameterIuiv";
};

struct GlGetSamplerParameteriv :
    ApiFunctionOgl<PFNGLGETSAMPLERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetSamplerParameteriv";
};

struct GlGetSamplerParameterIiv :
    ApiFunctionOgl<PFNGLGETSAMPLERPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glGetSamplerParameterIiv";
};

struct GlGetSamplerParameterfv :
    ApiFunctionOgl<PFNGLGETSAMPLERPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glGetSamplerParameterfv";
};

struct GlGetSamplerParameterIuiv :
    ApiFunctionOgl<PFNGLGETSAMPLERPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetSamplerParameterIuiv";
};

struct GlQueryCounter :
    ApiFunctionOgl<PFNGLQUERYCOUNTERPROC>
{
    static constexpr std::string_view Name =
        "glQueryCounter";
};

struct GlGetQueryObjecti64v :
    ApiFunctionOgl<PFNGLGETQUERYOBJECTI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryObjecti64v";
};

struct GlGetQueryObjectui64v :
    ApiFunctionOgl<PFNGLGETQUERYOBJECTUI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryObjectui64v";
};

struct GlVertexAttribDivisor :
    ApiFunctionOgl<PFNGLVERTEXATTRIBDIVISORPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribDivisor";
};

struct GlVertexAttribP1ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP1UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP1ui";
};

struct GlVertexAttribP1uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP1UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP1uiv";
};

struct GlVertexAttribP2ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP2UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP2ui";
};

struct GlVertexAttribP2uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP2UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP2uiv";
};

struct GlVertexAttribP3ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP3UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP3ui";
};

struct GlVertexAttribP3uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP3UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP3uiv";
};

struct GlVertexAttribP4ui :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP4UIPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP4ui";
};

struct GlVertexAttribP4uiv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBP4UIVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribP4uiv";
};

struct GlMinSampleShading :
    ApiFunctionOgl<PFNGLMINSAMPLESHADINGPROC>
{
    static constexpr std::string_view Name =
        "glMinSampleShading";
};

struct GlBlendEquationi :
    ApiFunctionOgl<PFNGLBLENDEQUATIONIPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquationi";
};

struct GlBlendEquationSeparatei :
    ApiFunctionOgl<PFNGLBLENDEQUATIONSEPARATEIPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquationSeparatei";
};

struct GlBlendFunci :
    ApiFunctionOgl<PFNGLBLENDFUNCIPROC>
{
    static constexpr std::string_view Name =
        "glBlendFunci";
};

struct GlBlendFuncSeparatei :
    ApiFunctionOgl<PFNGLBLENDFUNCSEPARATEIPROC>
{
    static constexpr std::string_view Name =
        "glBlendFuncSeparatei";
};

struct GlDrawArraysIndirect :
    ApiFunctionOgl<PFNGLDRAWARRAYSINDIRECTPROC>
{
    static constexpr std::string_view Name =
        "glDrawArraysIndirect";
};

struct GlDrawElementsIndirect :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINDIRECTPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsIndirect";
};

struct GlUniform1d :
    ApiFunctionOgl<PFNGLUNIFORM1DPROC>
{
    static constexpr std::string_view Name =
        "glUniform1d";
};

struct GlUniform2d :
    ApiFunctionOgl<PFNGLUNIFORM2DPROC>
{
    static constexpr std::string_view Name =
        "glUniform2d";
};

struct GlUniform3d :
    ApiFunctionOgl<PFNGLUNIFORM3DPROC>
{
    static constexpr std::string_view Name =
        "glUniform3d";
};

struct GlUniform4d :
    ApiFunctionOgl<PFNGLUNIFORM4DPROC>
{
    static constexpr std::string_view Name =
        "glUniform4d";
};

struct GlUniform1dv :
    ApiFunctionOgl<PFNGLUNIFORM1DVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1dv";
};

struct GlUniform2dv :
    ApiFunctionOgl<PFNGLUNIFORM2DVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2dv";
};

struct GlUniform3dv :
    ApiFunctionOgl<PFNGLUNIFORM3DVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3dv";
};

struct GlUniform4dv :
    ApiFunctionOgl<PFNGLUNIFORM4DVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4dv";
};

struct GlUniformMatrix2dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2dv";
};

struct GlUniformMatrix3dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3dv";
};

struct GlUniformMatrix4dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4dv";
};

struct GlUniformMatrix2x3dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2X3DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2x3dv";
};

struct GlUniformMatrix2x4dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX2X4DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix2x4dv";
};

struct GlUniformMatrix3x2dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3X2DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3x2dv";
};

struct GlUniformMatrix3x4dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX3X4DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix3x4dv";
};

struct GlUniformMatrix4x2dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4X2DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4x2dv";
};

struct GlUniformMatrix4x3dv :
    ApiFunctionOgl<PFNGLUNIFORMMATRIX4X3DVPROC>
{
    static constexpr std::string_view Name =
        "glUniformMatrix4x3dv";
};

struct GlGetUniformdv :
    ApiFunctionOgl<PFNGLGETUNIFORMDVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformdv";
};

struct GlGetSubroutineUniformLocation :
    ApiFunctionOgl<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glGetSubroutineUniformLocation";
};

struct GlGetSubroutineIndex :
    ApiFunctionOgl<PFNGLGETSUBROUTINEINDEXPROC>
{
    static constexpr std::string_view Name =
        "glGetSubroutineIndex";
};

struct GlGetActiveSubroutineUniformiv :
    ApiFunctionOgl<PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveSubroutineUniformiv";
};

struct GlGetActiveSubroutineUniformName :
    ApiFunctionOgl<PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveSubroutineUniformName";
};

struct GlGetActiveSubroutineName :
    ApiFunctionOgl<PFNGLGETACTIVESUBROUTINENAMEPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveSubroutineName";
};

struct GlUniformSubroutinesuiv :
    ApiFunctionOgl<PFNGLUNIFORMSUBROUTINESUIVPROC>
{
    static constexpr std::string_view Name =
        "glUniformSubroutinesuiv";
};

struct GlGetUniformSubroutineuiv :
    ApiFunctionOgl<PFNGLGETUNIFORMSUBROUTINEUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformSubroutineuiv";
};

struct GlGetProgramStageiv :
    ApiFunctionOgl<PFNGLGETPROGRAMSTAGEIVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramStageiv";
};

struct GlPatchParameteri :
    ApiFunctionOgl<PFNGLPATCHPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glPatchParameteri";
};

struct GlPatchParameterfv :
    ApiFunctionOgl<PFNGLPATCHPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glPatchParameterfv";
};

struct GlBindTransformFeedback :
    ApiFunctionOgl<PFNGLBINDTRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glBindTransformFeedback";
};

struct GlDeleteTransformFeedbacks :
    ApiFunctionOgl<PFNGLDELETETRANSFORMFEEDBACKSPROC>
{
    static constexpr std::string_view Name =
        "glDeleteTransformFeedbacks";
};

struct GlGenTransformFeedbacks :
    ApiFunctionOgl<PFNGLGENTRANSFORMFEEDBACKSPROC>
{
    static constexpr std::string_view Name =
        "glGenTransformFeedbacks";
};

struct GlIsTransformFeedback :
    ApiFunctionOgl<PFNGLISTRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glIsTransformFeedback";
};

struct GlPauseTransformFeedback :
    ApiFunctionOgl<PFNGLPAUSETRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glPauseTransformFeedback";
};

struct GlResumeTransformFeedback :
    ApiFunctionOgl<PFNGLRESUMETRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glResumeTransformFeedback";
};

struct GlDrawTransformFeedback :
    ApiFunctionOgl<PFNGLDRAWTRANSFORMFEEDBACKPROC>
{
    static constexpr std::string_view Name =
        "glDrawTransformFeedback";
};

struct GlDrawTransformFeedbackStream :
    ApiFunctionOgl<PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC>
{
    static constexpr std::string_view Name =
        "glDrawTransformFeedbackStream";
};

struct GlBeginQueryIndexed :
    ApiFunctionOgl<PFNGLBEGINQUERYINDEXEDPROC>
{
    static constexpr std::string_view Name =
        "glBeginQueryIndexed";
};

struct GlEndQueryIndexed :
    ApiFunctionOgl<PFNGLENDQUERYINDEXEDPROC>
{
    static constexpr std::string_view Name =
        "glEndQueryIndexed";
};

struct GlGetQueryIndexediv :
    ApiFunctionOgl<PFNGLGETQUERYINDEXEDIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryIndexediv";
};

struct GlReleaseShaderCompiler :
    ApiFunctionOgl<PFNGLRELEASESHADERCOMPILERPROC>
{
    static constexpr std::string_view Name =
        "glReleaseShaderCompiler";
};

struct GlShaderBinary :
    ApiFunctionOgl<PFNGLSHADERBINARYPROC>
{
    static constexpr std::string_view Name =
        "glShaderBinary";
};

struct GlGetShaderPrecisionFormat :
    ApiFunctionOgl<PFNGLGETSHADERPRECISIONFORMATPROC>
{
    static constexpr std::string_view Name =
        "glGetShaderPrecisionFormat";
};

struct GlDepthRangef :
    ApiFunctionOgl<PFNGLDEPTHRANGEFPROC>
{
    static constexpr std::string_view Name =
        "glDepthRangef";
};

struct GlClearDepthf :
    ApiFunctionOgl<PFNGLCLEARDEPTHFPROC>
{
    static constexpr std::string_view Name =
        "glClearDepthf";
};

struct GlGetProgramBinary :
    ApiFunctionOgl<PFNGLGETPROGRAMBINARYPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramBinary";
};

struct GlProgramBinary :
    ApiFunctionOgl<PFNGLPROGRAMBINARYPROC>
{
    static constexpr std::string_view Name =
        "glProgramBinary";
};

struct GlProgramParameteri :
    ApiFunctionOgl<PFNGLPROGRAMPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glProgramParameteri";
};

struct GlUseProgramStages :
    ApiFunctionOgl<PFNGLUSEPROGRAMSTAGESPROC>
{
    static constexpr std::string_view Name =
        "glUseProgramStages";
};

struct GlActiveShaderProgram :
    ApiFunctionOgl<PFNGLACTIVESHADERPROGRAMPROC>
{
    static constexpr std::string_view Name =
        "glActiveShaderProgram";
};

struct GlCreateShaderProgramv :
    ApiFunctionOgl<PFNGLCREATESHADERPROGRAMVPROC>
{
    static constexpr std::string_view Name =
        "glCreateShaderProgramv";
};

struct GlBindProgramPipeline :
    ApiFunctionOgl<PFNGLBINDPROGRAMPIPELINEPROC>
{
    static constexpr std::string_view Name =
        "glBindProgramPipeline";
};

struct GlDeleteProgramPipelines :
    ApiFunctionOgl<PFNGLDELETEPROGRAMPIPELINESPROC>
{
    static constexpr std::string_view Name =
        "glDeleteProgramPipelines";
};

struct GlGenProgramPipelines :
    ApiFunctionOgl<PFNGLGENPROGRAMPIPELINESPROC>
{
    static constexpr std::string_view Name =
        "glGenProgramPipelines";
};

struct GlIsProgramPipeline :
    ApiFunctionOgl<PFNGLISPROGRAMPIPELINEPROC>
{
    static constexpr std::string_view Name =
        "glIsProgramPipeline";
};

struct GlGetProgramPipelineiv :
    ApiFunctionOgl<PFNGLGETPROGRAMPIPELINEIVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramPipelineiv";
};

struct GlProgramUniform1i :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1IPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1i";
};

struct GlProgramUniform1iv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1IVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1iv";
};

struct GlProgramUniform1f :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1FPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1f";
};

struct GlProgramUniform1fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1fv";
};

struct GlProgramUniform1d :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1DPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1d";
};

struct GlProgramUniform1dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1dv";
};

struct GlProgramUniform1ui :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UIPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ui";
};

struct GlProgramUniform1uiv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UIVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1uiv";
};

struct GlProgramUniform2i :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2IPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2i";
};

struct GlProgramUniform2iv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2IVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2iv";
};

struct GlProgramUniform2f :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2FPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2f";
};

struct GlProgramUniform2fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2fv";
};

struct GlProgramUniform2d :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2DPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2d";
};

struct GlProgramUniform2dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2dv";
};

struct GlProgramUniform2ui :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UIPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ui";
};

struct GlProgramUniform2uiv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UIVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2uiv";
};

struct GlProgramUniform3i :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3IPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3i";
};

struct GlProgramUniform3iv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3IVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3iv";
};

struct GlProgramUniform3f :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3FPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3f";
};

struct GlProgramUniform3fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3fv";
};

struct GlProgramUniform3d :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3DPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3d";
};

struct GlProgramUniform3dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3dv";
};

struct GlProgramUniform3ui :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UIPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ui";
};

struct GlProgramUniform3uiv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UIVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3uiv";
};

struct GlProgramUniform4i :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4IPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4i";
};

struct GlProgramUniform4iv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4IVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4iv";
};

struct GlProgramUniform4f :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4FPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4f";
};

struct GlProgramUniform4fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4fv";
};

struct GlProgramUniform4d :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4DPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4d";
};

struct GlProgramUniform4dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4dv";
};

struct GlProgramUniform4ui :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UIPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ui";
};

struct GlProgramUniform4uiv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UIVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4uiv";
};

struct GlProgramUniformMatrix2fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2fv";
};

struct GlProgramUniformMatrix3fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3fv";
};

struct GlProgramUniformMatrix4fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4fv";
};

struct GlProgramUniformMatrix2dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2dv";
};

struct GlProgramUniformMatrix3dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3dv";
};

struct GlProgramUniformMatrix4dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4dv";
};

struct GlProgramUniformMatrix2x3fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x3fv";
};

struct GlProgramUniformMatrix3x2fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x2fv";
};

struct GlProgramUniformMatrix2x4fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x4fv";
};

struct GlProgramUniformMatrix4x2fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x2fv";
};

struct GlProgramUniformMatrix3x4fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x4fv";
};

struct GlProgramUniformMatrix4x3fv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x3fv";
};

struct GlProgramUniformMatrix2x3dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x3dv";
};

struct GlProgramUniformMatrix3x2dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x2dv";
};

struct GlProgramUniformMatrix2x4dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x4dv";
};

struct GlProgramUniformMatrix4x2dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x2dv";
};

struct GlProgramUniformMatrix3x4dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x4dv";
};

struct GlProgramUniformMatrix4x3dv :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x3dv";
};

struct GlValidateProgramPipeline :
    ApiFunctionOgl<PFNGLVALIDATEPROGRAMPIPELINEPROC>
{
    static constexpr std::string_view Name =
        "glValidateProgramPipeline";
};

struct GlGetProgramPipelineInfoLog :
    ApiFunctionOgl<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramPipelineInfoLog";
};

struct GlVertexAttribL1d :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1d";
};

struct GlVertexAttribL2d :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2d";
};

struct GlVertexAttribL3d :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3d";
};

struct GlVertexAttribL4d :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4DPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4d";
};

struct GlVertexAttribL1dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1dv";
};

struct GlVertexAttribL2dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2dv";
};

struct GlVertexAttribL3dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3dv";
};

struct GlVertexAttribL4dv :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4DVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4dv";
};

struct GlVertexAttribLPointer :
    ApiFunctionOgl<PFNGLVERTEXATTRIBLPOINTERPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribLPointer";
};

struct GlGetVertexAttribLdv :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBLDVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribLdv";
};

struct GlViewportArrayv :
    ApiFunctionOgl<PFNGLVIEWPORTARRAYVPROC>
{
    static constexpr std::string_view Name =
        "glViewportArrayv";
};

struct GlViewportIndexedf :
    ApiFunctionOgl<PFNGLVIEWPORTINDEXEDFPROC>
{
    static constexpr std::string_view Name =
        "glViewportIndexedf";
};

struct GlViewportIndexedfv :
    ApiFunctionOgl<PFNGLVIEWPORTINDEXEDFVPROC>
{
    static constexpr std::string_view Name =
        "glViewportIndexedfv";
};

struct GlScissorArrayv :
    ApiFunctionOgl<PFNGLSCISSORARRAYVPROC>
{
    static constexpr std::string_view Name =
        "glScissorArrayv";
};

struct GlScissorIndexed :
    ApiFunctionOgl<PFNGLSCISSORINDEXEDPROC>
{
    static constexpr std::string_view Name =
        "glScissorIndexed";
};

struct GlScissorIndexedv :
    ApiFunctionOgl<PFNGLSCISSORINDEXEDVPROC>
{
    static constexpr std::string_view Name =
        "glScissorIndexedv";
};

struct GlDepthRangeArrayv :
    ApiFunctionOgl<PFNGLDEPTHRANGEARRAYVPROC>
{
    static constexpr std::string_view Name =
        "glDepthRangeArrayv";
};

struct GlDepthRangeIndexed :
    ApiFunctionOgl<PFNGLDEPTHRANGEINDEXEDPROC>
{
    static constexpr std::string_view Name =
        "glDepthRangeIndexed";
};

struct GlGetFloati_v :
    ApiFunctionOgl<PFNGLGETFLOATI_VPROC>
{
    static constexpr std::string_view Name =
        "glGetFloati_v";
};

struct GlGetDoublei_v :
    ApiFunctionOgl<PFNGLGETDOUBLEI_VPROC>
{
    static constexpr std::string_view Name =
        "glGetDoublei_v";
};

struct GlDrawArraysInstancedBaseInstance :
    ApiFunctionOgl<PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC>
{
    static constexpr std::string_view Name =
        "glDrawArraysInstancedBaseInstance";
};

struct GlDrawElementsInstancedBaseInstance :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstancedBaseInstance";
};

struct GlDrawElementsInstancedBaseVertexBaseInstance :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstancedBaseVertexBaseInstance";
};

struct GlGetInternalformativ :
    ApiFunctionOgl<PFNGLGETINTERNALFORMATIVPROC>
{
    static constexpr std::string_view Name =
        "glGetInternalformativ";
};

struct GlGetActiveAtomicCounterBufferiv :
    ApiFunctionOgl<PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetActiveAtomicCounterBufferiv";
};

struct GlBindImageTexture :
    ApiFunctionOgl<PFNGLBINDIMAGETEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glBindImageTexture";
};

struct GlMemoryBarrier :
    ApiFunctionOgl<PFNGLMEMORYBARRIERPROC>
{
    static constexpr std::string_view Name =
        "glMemoryBarrier";
};

struct GlTexStorage1D :
    ApiFunctionOgl<PFNGLTEXSTORAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glTexStorage1D";
};

struct GlTexStorage2D :
    ApiFunctionOgl<PFNGLTEXSTORAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glTexStorage2D";
};

struct GlTexStorage3D :
    ApiFunctionOgl<PFNGLTEXSTORAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glTexStorage3D";
};

struct GlDrawTransformFeedbackInstanced :
    ApiFunctionOgl<PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC>
{
    static constexpr std::string_view Name =
        "glDrawTransformFeedbackInstanced";
};

struct GlDrawTransformFeedbackStreamInstanced :
    ApiFunctionOgl<PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC>
{
    static constexpr std::string_view Name =
        "glDrawTransformFeedbackStreamInstanced";
};

struct GlClearBufferData :
    ApiFunctionOgl<PFNGLCLEARBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferData";
};

struct GlClearBufferSubData :
    ApiFunctionOgl<PFNGLCLEARBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glClearBufferSubData";
};

struct GlDispatchCompute :
    ApiFunctionOgl<PFNGLDISPATCHCOMPUTEPROC>
{
    static constexpr std::string_view Name =
        "glDispatchCompute";
};

struct GlDispatchComputeIndirect :
    ApiFunctionOgl<PFNGLDISPATCHCOMPUTEINDIRECTPROC>
{
    static constexpr std::string_view Name =
        "glDispatchComputeIndirect";
};

struct GlCopyImageSubData :
    ApiFunctionOgl<PFNGLCOPYIMAGESUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glCopyImageSubData";
};

struct GlFramebufferParameteri :
    ApiFunctionOgl<PFNGLFRAMEBUFFERPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferParameteri";
};

struct GlGetFramebufferParameteriv :
    ApiFunctionOgl<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetFramebufferParameteriv";
};

struct GlGetInternalformati64v :
    ApiFunctionOgl<PFNGLGETINTERNALFORMATI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetInternalformati64v";
};

struct GlInvalidateTexSubImage :
    ApiFunctionOgl<PFNGLINVALIDATETEXSUBIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateTexSubImage";
};

struct GlInvalidateTexImage :
    ApiFunctionOgl<PFNGLINVALIDATETEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateTexImage";
};

struct GlInvalidateBufferSubData :
    ApiFunctionOgl<PFNGLINVALIDATEBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateBufferSubData";
};

struct GlInvalidateBufferData :
    ApiFunctionOgl<PFNGLINVALIDATEBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateBufferData";
};

struct GlInvalidateFramebuffer :
    ApiFunctionOgl<PFNGLINVALIDATEFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateFramebuffer";
};

struct GlInvalidateSubFramebuffer :
    ApiFunctionOgl<PFNGLINVALIDATESUBFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateSubFramebuffer";
};

struct GlMultiDrawArraysIndirect :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSINDIRECTPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArraysIndirect";
};

struct GlMultiDrawElementsIndirect :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSINDIRECTPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsIndirect";
};

struct GlGetProgramInterfaceiv :
    ApiFunctionOgl<PFNGLGETPROGRAMINTERFACEIVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramInterfaceiv";
};

struct GlGetProgramResourceIndex :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCEINDEXPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourceIndex";
};

struct GlGetProgramResourceName :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCENAMEPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourceName";
};

struct GlGetProgramResourceiv :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCEIVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourceiv";
};

struct GlGetProgramResourceLocation :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCELOCATIONPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourceLocation";
};

struct GlGetProgramResourceLocationIndex :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourceLocationIndex";
};

struct GlShaderStorageBlockBinding :
    ApiFunctionOgl<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>
{
    static constexpr std::string_view Name =
        "glShaderStorageBlockBinding";
};

struct GlTexBufferRange :
    ApiFunctionOgl<PFNGLTEXBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glTexBufferRange";
};

struct GlTexStorage2DMultisample :
    ApiFunctionOgl<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTexStorage2DMultisample";
};

struct GlTexStorage3DMultisample :
    ApiFunctionOgl<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTexStorage3DMultisample";
};

struct GlTextureView :
    ApiFunctionOgl<PFNGLTEXTUREVIEWPROC>
{
    static constexpr std::string_view Name =
        "glTextureView";
};

struct GlBindVertexBuffer :
    ApiFunctionOgl<PFNGLBINDVERTEXBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBindVertexBuffer";
};

struct GlVertexAttribFormat :
    ApiFunctionOgl<PFNGLVERTEXATTRIBFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribFormat";
};

struct GlVertexAttribIFormat :
    ApiFunctionOgl<PFNGLVERTEXATTRIBIFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribIFormat";
};

struct GlVertexAttribLFormat :
    ApiFunctionOgl<PFNGLVERTEXATTRIBLFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribLFormat";
};

struct GlVertexAttribBinding :
    ApiFunctionOgl<PFNGLVERTEXATTRIBBINDINGPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribBinding";
};

struct GlVertexBindingDivisor :
    ApiFunctionOgl<PFNGLVERTEXBINDINGDIVISORPROC>
{
    static constexpr std::string_view Name =
        "glVertexBindingDivisor";
};

struct GlDebugMessageControl :
    ApiFunctionOgl<PFNGLDEBUGMESSAGECONTROLPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageControl";
};

struct GlDebugMessageInsert :
    ApiFunctionOgl<PFNGLDEBUGMESSAGEINSERTPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageInsert";
};

struct GlDebugMessageCallback :
    ApiFunctionOgl<PFNGLDEBUGMESSAGECALLBACKPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageCallback";
};

struct GlGetDebugMessageLog :
    ApiFunctionOgl<PFNGLGETDEBUGMESSAGELOGPROC>
{
    static constexpr std::string_view Name =
        "glGetDebugMessageLog";
};

struct GlPushDebugGroup :
    ApiFunctionOgl<PFNGLPUSHDEBUGGROUPPROC>
{
    static constexpr std::string_view Name =
        "glPushDebugGroup";
};

struct GlPopDebugGroup :
    ApiFunctionOgl<PFNGLPOPDEBUGGROUPPROC>
{
    static constexpr std::string_view Name =
        "glPopDebugGroup";
};

struct GlObjectLabel :
    ApiFunctionOgl<PFNGLOBJECTLABELPROC>
{
    static constexpr std::string_view Name =
        "glObjectLabel";
};

struct GlGetObjectLabel :
    ApiFunctionOgl<PFNGLGETOBJECTLABELPROC>
{
    static constexpr std::string_view Name =
        "glGetObjectLabel";
};

struct GlObjectPtrLabel :
    ApiFunctionOgl<PFNGLOBJECTPTRLABELPROC>
{
    static constexpr std::string_view Name =
        "glObjectPtrLabel";
};

struct GlGetObjectPtrLabel :
    ApiFunctionOgl<PFNGLGETOBJECTPTRLABELPROC>
{
    static constexpr std::string_view Name =
        "glGetObjectPtrLabel";
};

struct GlBufferStorage :
    ApiFunctionOgl<PFNGLBUFFERSTORAGEPROC>
{
    static constexpr std::string_view Name =
        "glBufferStorage";
};

struct GlClearTexImage :
    ApiFunctionOgl<PFNGLCLEARTEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glClearTexImage";
};

struct GlClearTexSubImage :
    ApiFunctionOgl<PFNGLCLEARTEXSUBIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glClearTexSubImage";
};

struct GlBindBuffersBase :
    ApiFunctionOgl<PFNGLBINDBUFFERSBASEPROC>
{
    static constexpr std::string_view Name =
        "glBindBuffersBase";
};

struct GlBindBuffersRange :
    ApiFunctionOgl<PFNGLBINDBUFFERSRANGEPROC>
{
    static constexpr std::string_view Name =
        "glBindBuffersRange";
};

struct GlBindTextures :
    ApiFunctionOgl<PFNGLBINDTEXTURESPROC>
{
    static constexpr std::string_view Name =
        "glBindTextures";
};

struct GlBindSamplers :
    ApiFunctionOgl<PFNGLBINDSAMPLERSPROC>
{
    static constexpr std::string_view Name =
        "glBindSamplers";
};

struct GlBindImageTextures :
    ApiFunctionOgl<PFNGLBINDIMAGETEXTURESPROC>
{
    static constexpr std::string_view Name =
        "glBindImageTextures";
};

struct GlBindVertexBuffers :
    ApiFunctionOgl<PFNGLBINDVERTEXBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glBindVertexBuffers";
};

struct GlClipControl :
    ApiFunctionOgl<PFNGLCLIPCONTROLPROC>
{
    static constexpr std::string_view Name =
        "glClipControl";
};

struct GlCreateTransformFeedbacks :
    ApiFunctionOgl<PFNGLCREATETRANSFORMFEEDBACKSPROC>
{
    static constexpr std::string_view Name =
        "glCreateTransformFeedbacks";
};

struct GlTransformFeedbackBufferBase :
    ApiFunctionOgl<PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC>
{
    static constexpr std::string_view Name =
        "glTransformFeedbackBufferBase";
};

struct GlTransformFeedbackBufferRange :
    ApiFunctionOgl<PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glTransformFeedbackBufferRange";
};

struct GlGetTransformFeedbackiv :
    ApiFunctionOgl<PFNGLGETTRANSFORMFEEDBACKIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTransformFeedbackiv";
};

struct GlGetTransformFeedbacki_v :
    ApiFunctionOgl<PFNGLGETTRANSFORMFEEDBACKI_VPROC>
{
    static constexpr std::string_view Name =
        "glGetTransformFeedbacki_v";
};

struct GlGetTransformFeedbacki64_v :
    ApiFunctionOgl<PFNGLGETTRANSFORMFEEDBACKI64_VPROC>
{
    static constexpr std::string_view Name =
        "glGetTransformFeedbacki64_v";
};

struct GlCreateBuffers :
    ApiFunctionOgl<PFNGLCREATEBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glCreateBuffers";
};

struct GlNamedBufferStorage :
    ApiFunctionOgl<PFNGLNAMEDBUFFERSTORAGEPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferStorage";
};

struct GlNamedBufferData :
    ApiFunctionOgl<PFNGLNAMEDBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferData";
};

struct GlNamedBufferSubData :
    ApiFunctionOgl<PFNGLNAMEDBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferSubData";
};

struct GlCopyNamedBufferSubData :
    ApiFunctionOgl<PFNGLCOPYNAMEDBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glCopyNamedBufferSubData";
};

struct GlClearNamedBufferData :
    ApiFunctionOgl<PFNGLCLEARNAMEDBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedBufferData";
};

struct GlClearNamedBufferSubData :
    ApiFunctionOgl<PFNGLCLEARNAMEDBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedBufferSubData";
};

struct GlMapNamedBuffer :
    ApiFunctionOgl<PFNGLMAPNAMEDBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glMapNamedBuffer";
};

struct GlMapNamedBufferRange :
    ApiFunctionOgl<PFNGLMAPNAMEDBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glMapNamedBufferRange";
};

struct GlUnmapNamedBuffer :
    ApiFunctionOgl<PFNGLUNMAPNAMEDBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glUnmapNamedBuffer";
};

struct GlFlushMappedNamedBufferRange :
    ApiFunctionOgl<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glFlushMappedNamedBufferRange";
};

struct GlGetNamedBufferParameteriv :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferParameteriv";
};

struct GlGetNamedBufferParameteri64v :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPARAMETERI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferParameteri64v";
};

struct GlGetNamedBufferPointerv :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPOINTERVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferPointerv";
};

struct GlGetNamedBufferSubData :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferSubData";
};

struct GlCreateFramebuffers :
    ApiFunctionOgl<PFNGLCREATEFRAMEBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glCreateFramebuffers";
};

struct GlNamedFramebufferRenderbuffer :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferRenderbuffer";
};

struct GlNamedFramebufferParameteri :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferParameteri";
};

struct GlNamedFramebufferTexture :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTUREPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTexture";
};

struct GlNamedFramebufferTextureLayer :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTextureLayer";
};

struct GlNamedFramebufferDrawBuffer :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferDrawBuffer";
};

struct GlNamedFramebufferDrawBuffers :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferDrawBuffers";
};

struct GlNamedFramebufferReadBuffer :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferReadBuffer";
};

struct GlInvalidateNamedFramebufferData :
    ApiFunctionOgl<PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateNamedFramebufferData";
};

struct GlInvalidateNamedFramebufferSubData :
    ApiFunctionOgl<PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC>
{
    static constexpr std::string_view Name =
        "glInvalidateNamedFramebufferSubData";
};

struct GlClearNamedFramebufferiv :
    ApiFunctionOgl<PFNGLCLEARNAMEDFRAMEBUFFERIVPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedFramebufferiv";
};

struct GlClearNamedFramebufferuiv :
    ApiFunctionOgl<PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedFramebufferuiv";
};

struct GlClearNamedFramebufferfv :
    ApiFunctionOgl<PFNGLCLEARNAMEDFRAMEBUFFERFVPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedFramebufferfv";
};

struct GlClearNamedFramebufferfi :
    ApiFunctionOgl<PFNGLCLEARNAMEDFRAMEBUFFERFIPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedFramebufferfi";
};

struct GlBlitNamedFramebuffer :
    ApiFunctionOgl<PFNGLBLITNAMEDFRAMEBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glBlitNamedFramebuffer";
};

struct GlCheckNamedFramebufferStatus :
    ApiFunctionOgl<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC>
{
    static constexpr std::string_view Name =
        "glCheckNamedFramebufferStatus";
};

struct GlGetNamedFramebufferParameteriv :
    ApiFunctionOgl<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedFramebufferParameteriv";
};

struct GlGetNamedFramebufferAttachmentParameteriv :
    ApiFunctionOgl<PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedFramebufferAttachmentParameteriv";
};

struct GlCreateRenderbuffers :
    ApiFunctionOgl<PFNGLCREATERENDERBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glCreateRenderbuffers";
};

struct GlNamedRenderbufferStorage :
    ApiFunctionOgl<PFNGLNAMEDRENDERBUFFERSTORAGEPROC>
{
    static constexpr std::string_view Name =
        "glNamedRenderbufferStorage";
};

struct GlNamedRenderbufferStorageMultisample :
    ApiFunctionOgl<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glNamedRenderbufferStorageMultisample";
};

struct GlGetNamedRenderbufferParameteriv :
    ApiFunctionOgl<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedRenderbufferParameteriv";
};

struct GlCreateTextures :
    ApiFunctionOgl<PFNGLCREATETEXTURESPROC>
{
    static constexpr std::string_view Name =
        "glCreateTextures";
};

struct GlTextureBuffer :
    ApiFunctionOgl<PFNGLTEXTUREBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glTextureBuffer";
};

struct GlTextureBufferRange :
    ApiFunctionOgl<PFNGLTEXTUREBUFFERRANGEPROC>
{
    static constexpr std::string_view Name =
        "glTextureBufferRange";
};

struct GlTextureStorage1D :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage1D";
};

struct GlTextureStorage2D :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage2D";
};

struct GlTextureStorage3D :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage3D";
};

struct GlTextureStorage2DMultisample :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage2DMultisample";
};

struct GlTextureStorage3DMultisample :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage3DMultisample";
};

struct GlTextureSubImage1D :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage1D";
};

struct GlTextureSubImage2D :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage2D";
};

struct GlTextureSubImage3D :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage3D";
};

struct GlCompressedTextureSubImage1D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage1D";
};

struct GlCompressedTextureSubImage2D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage2D";
};

struct GlCompressedTextureSubImage3D :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage3D";
};

struct GlCopyTextureSubImage1D :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE1DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage1D";
};

struct GlCopyTextureSubImage2D :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE2DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage2D";
};

struct GlCopyTextureSubImage3D :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE3DPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage3D";
};

struct GlTextureParameterf :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERFPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterf";
};

struct GlTextureParameterfv :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterfv";
};

struct GlTextureParameteri :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameteri";
};

struct GlTextureParameterIiv :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterIiv";
};

struct GlTextureParameterIuiv :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterIuiv";
};

struct GlTextureParameteriv :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameteriv";
};

struct GlGenerateTextureMipmap :
    ApiFunctionOgl<PFNGLGENERATETEXTUREMIPMAPPROC>
{
    static constexpr std::string_view Name =
        "glGenerateTextureMipmap";
};

struct GlBindTextureUnit :
    ApiFunctionOgl<PFNGLBINDTEXTUREUNITPROC>
{
    static constexpr std::string_view Name =
        "glBindTextureUnit";
};

struct GlGetTextureImage :
    ApiFunctionOgl<PFNGLGETTEXTUREIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureImage";
};

struct GlGetCompressedTextureImage :
    ApiFunctionOgl<PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetCompressedTextureImage";
};

struct GlGetTextureLevelParameterfv :
    ApiFunctionOgl<PFNGLGETTEXTURELEVELPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureLevelParameterfv";
};

struct GlGetTextureLevelParameteriv :
    ApiFunctionOgl<PFNGLGETTEXTURELEVELPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureLevelParameteriv";
};

struct GlGetTextureParameterfv :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERFVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterfv";
};

struct GlGetTextureParameterIiv :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterIiv";
};

struct GlGetTextureParameterIuiv :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterIuiv";
};

struct GlGetTextureParameteriv :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameteriv";
};

struct GlCreateVertexArrays :
    ApiFunctionOgl<PFNGLCREATEVERTEXARRAYSPROC>
{
    static constexpr std::string_view Name =
        "glCreateVertexArrays";
};

struct GlDisableVertexArrayAttrib :
    ApiFunctionOgl<PFNGLDISABLEVERTEXARRAYATTRIBPROC>
{
    static constexpr std::string_view Name =
        "glDisableVertexArrayAttrib";
};

struct GlEnableVertexArrayAttrib :
    ApiFunctionOgl<PFNGLENABLEVERTEXARRAYATTRIBPROC>
{
    static constexpr std::string_view Name =
        "glEnableVertexArrayAttrib";
};

struct GlVertexArrayElementBuffer :
    ApiFunctionOgl<PFNGLVERTEXARRAYELEMENTBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayElementBuffer";
};

struct GlVertexArrayVertexBuffer :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXBUFFERPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexBuffer";
};

struct GlVertexArrayVertexBuffers :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXBUFFERSPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexBuffers";
};

struct GlVertexArrayAttribBinding :
    ApiFunctionOgl<PFNGLVERTEXARRAYATTRIBBINDINGPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayAttribBinding";
};

struct GlVertexArrayAttribFormat :
    ApiFunctionOgl<PFNGLVERTEXARRAYATTRIBFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayAttribFormat";
};

struct GlVertexArrayAttribIFormat :
    ApiFunctionOgl<PFNGLVERTEXARRAYATTRIBIFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayAttribIFormat";
};

struct GlVertexArrayAttribLFormat :
    ApiFunctionOgl<PFNGLVERTEXARRAYATTRIBLFORMATPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayAttribLFormat";
};

struct GlVertexArrayBindingDivisor :
    ApiFunctionOgl<PFNGLVERTEXARRAYBINDINGDIVISORPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayBindingDivisor";
};

struct GlGetVertexArrayiv :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYIVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayiv";
};

struct GlGetVertexArrayIndexediv :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYINDEXEDIVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayIndexediv";
};

struct GlGetVertexArrayIndexed64iv :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYINDEXED64IVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayIndexed64iv";
};

struct GlCreateSamplers :
    ApiFunctionOgl<PFNGLCREATESAMPLERSPROC>
{
    static constexpr std::string_view Name =
        "glCreateSamplers";
};

struct GlCreateProgramPipelines :
    ApiFunctionOgl<PFNGLCREATEPROGRAMPIPELINESPROC>
{
    static constexpr std::string_view Name =
        "glCreateProgramPipelines";
};

struct GlCreateQueries :
    ApiFunctionOgl<PFNGLCREATEQUERIESPROC>
{
    static constexpr std::string_view Name =
        "glCreateQueries";
};

struct GlGetQueryBufferObjecti64v :
    ApiFunctionOgl<PFNGLGETQUERYBUFFEROBJECTI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryBufferObjecti64v";
};

struct GlGetQueryBufferObjectiv :
    ApiFunctionOgl<PFNGLGETQUERYBUFFEROBJECTIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryBufferObjectiv";
};

struct GlGetQueryBufferObjectui64v :
    ApiFunctionOgl<PFNGLGETQUERYBUFFEROBJECTUI64VPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryBufferObjectui64v";
};

struct GlGetQueryBufferObjectuiv :
    ApiFunctionOgl<PFNGLGETQUERYBUFFEROBJECTUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetQueryBufferObjectuiv";
};

struct GlMemoryBarrierByRegion :
    ApiFunctionOgl<PFNGLMEMORYBARRIERBYREGIONPROC>
{
    static constexpr std::string_view Name =
        "glMemoryBarrierByRegion";
};

struct GlGetTextureSubImage :
    ApiFunctionOgl<PFNGLGETTEXTURESUBIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureSubImage";
};

struct GlGetCompressedTextureSubImage :
    ApiFunctionOgl<PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetCompressedTextureSubImage";
};

struct GlGetGraphicsResetStatus :
    ApiFunctionOgl<PFNGLGETGRAPHICSRESETSTATUSPROC>
{
    static constexpr std::string_view Name =
        "glGetGraphicsResetStatus";
};

struct GlGetnCompressedTexImage :
    ApiFunctionOgl<PFNGLGETNCOMPRESSEDTEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetnCompressedTexImage";
};

struct GlGetnTexImage :
    ApiFunctionOgl<PFNGLGETNTEXIMAGEPROC>
{
    static constexpr std::string_view Name =
        "glGetnTexImage";
};

struct GlGetnUniformdv :
    ApiFunctionOgl<PFNGLGETNUNIFORMDVPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformdv";
};

struct GlGetnUniformfv :
    ApiFunctionOgl<PFNGLGETNUNIFORMFVPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformfv";
};

struct GlGetnUniformiv :
    ApiFunctionOgl<PFNGLGETNUNIFORMIVPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformiv";
};

struct GlGetnUniformuiv :
    ApiFunctionOgl<PFNGLGETNUNIFORMUIVPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformuiv";
};

struct GlReadnPixels :
    ApiFunctionOgl<PFNGLREADNPIXELSPROC>
{
    static constexpr std::string_view Name =
        "glReadnPixels";
};

struct GlTextureBarrier :
    ApiFunctionOgl<PFNGLTEXTUREBARRIERPROC>
{
    static constexpr std::string_view Name =
        "glTextureBarrier";
};

struct GlSpecializeShader :
    ApiFunctionOgl<PFNGLSPECIALIZESHADERPROC>
{
    static constexpr std::string_view Name =
        "glSpecializeShader";
};

struct GlMultiDrawArraysIndirectCount :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArraysIndirectCount";
};

struct GlMultiDrawElementsIndirectCount :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsIndirectCount";
};

struct GlPolygonOffsetClamp :
    ApiFunctionOgl<PFNGLPOLYGONOFFSETCLAMPPROC>
{
    static constexpr std::string_view Name =
        "glPolygonOffsetClamp";
};

struct GlPrimitiveBoundingBoxARB :
    ApiFunctionOgl<PFNGLPRIMITIVEBOUNDINGBOXARBPROC>
{
    static constexpr std::string_view Name =
        "glPrimitiveBoundingBoxARB";
};

struct GlGetTextureHandleARB :
    ApiFunctionOgl<PFNGLGETTEXTUREHANDLEARBPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureHandleARB";
};

struct GlGetTextureSamplerHandleARB :
    ApiFunctionOgl<PFNGLGETTEXTURESAMPLERHANDLEARBPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureSamplerHandleARB";
};

struct GlMakeTextureHandleResidentARB :
    ApiFunctionOgl<PFNGLMAKETEXTUREHANDLERESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glMakeTextureHandleResidentARB";
};

struct GlMakeTextureHandleNonResidentARB :
    ApiFunctionOgl<PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glMakeTextureHandleNonResidentARB";
};

struct GlGetImageHandleARB :
    ApiFunctionOgl<PFNGLGETIMAGEHANDLEARBPROC>
{
    static constexpr std::string_view Name =
        "glGetImageHandleARB";
};

struct GlMakeImageHandleResidentARB :
    ApiFunctionOgl<PFNGLMAKEIMAGEHANDLERESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glMakeImageHandleResidentARB";
};

struct GlMakeImageHandleNonResidentARB :
    ApiFunctionOgl<PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glMakeImageHandleNonResidentARB";
};

struct GlUniformHandleui64ARB :
    ApiFunctionOgl<PFNGLUNIFORMHANDLEUI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniformHandleui64ARB";
};

struct GlUniformHandleui64vARB :
    ApiFunctionOgl<PFNGLUNIFORMHANDLEUI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniformHandleui64vARB";
};

struct GlProgramUniformHandleui64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformHandleui64ARB";
};

struct GlProgramUniformHandleui64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformHandleui64vARB";
};

struct GlIsTextureHandleResidentARB :
    ApiFunctionOgl<PFNGLISTEXTUREHANDLERESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glIsTextureHandleResidentARB";
};

struct GlIsImageHandleResidentARB :
    ApiFunctionOgl<PFNGLISIMAGEHANDLERESIDENTARBPROC>
{
    static constexpr std::string_view Name =
        "glIsImageHandleResidentARB";
};

struct GlVertexAttribL1ui64ARB :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1ui64ARB";
};

struct GlVertexAttribL1ui64vARB :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1ui64vARB";
};

struct GlGetVertexAttribLui64vARB :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBLUI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribLui64vARB";
};

struct GlCreateSyncFromCLeventARB :
    ApiFunctionOgl<PFNGLCREATESYNCFROMCLEVENTARBPROC>
{
    static constexpr std::string_view Name =
        "glCreateSyncFromCLeventARB";
};

struct GlDispatchComputeGroupSizeARB :
    ApiFunctionOgl<PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC>
{
    static constexpr std::string_view Name =
        "glDispatchComputeGroupSizeARB";
};

struct GlDebugMessageControlARB :
    ApiFunctionOgl<PFNGLDEBUGMESSAGECONTROLARBPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageControlARB";
};

struct GlDebugMessageInsertARB :
    ApiFunctionOgl<PFNGLDEBUGMESSAGEINSERTARBPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageInsertARB";
};

struct GlDebugMessageCallbackARB :
    ApiFunctionOgl<PFNGLDEBUGMESSAGECALLBACKARBPROC>
{
    static constexpr std::string_view Name =
        "glDebugMessageCallbackARB";
};

struct GlGetDebugMessageLogARB :
    ApiFunctionOgl<PFNGLGETDEBUGMESSAGELOGARBPROC>
{
    static constexpr std::string_view Name =
        "glGetDebugMessageLogARB";
};

struct GlBlendEquationiARB :
    ApiFunctionOgl<PFNGLBLENDEQUATIONIARBPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquationiARB";
};

struct GlBlendEquationSeparateiARB :
    ApiFunctionOgl<PFNGLBLENDEQUATIONSEPARATEIARBPROC>
{
    static constexpr std::string_view Name =
        "glBlendEquationSeparateiARB";
};

struct GlBlendFunciARB :
    ApiFunctionOgl<PFNGLBLENDFUNCIARBPROC>
{
    static constexpr std::string_view Name =
        "glBlendFunciARB";
};

struct GlBlendFuncSeparateiARB :
    ApiFunctionOgl<PFNGLBLENDFUNCSEPARATEIARBPROC>
{
    static constexpr std::string_view Name =
        "glBlendFuncSeparateiARB";
};

struct GlDrawArraysInstancedARB :
    ApiFunctionOgl<PFNGLDRAWARRAYSINSTANCEDARBPROC>
{
    static constexpr std::string_view Name =
        "glDrawArraysInstancedARB";
};

struct GlDrawElementsInstancedARB :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDARBPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstancedARB";
};

struct GlProgramParameteriARB :
    ApiFunctionOgl<PFNGLPROGRAMPARAMETERIARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramParameteriARB";
};

struct GlFramebufferTextureARB :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTUREARBPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTextureARB";
};

struct GlFramebufferTextureLayerARB :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTURELAYERARBPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTextureLayerARB";
};

struct GlFramebufferTextureFaceARB :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTUREFACEARBPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTextureFaceARB";
};

struct GlSpecializeShaderARB :
    ApiFunctionOgl<PFNGLSPECIALIZESHADERARBPROC>
{
    static constexpr std::string_view Name =
        "glSpecializeShaderARB";
};

struct GlUniform1i64ARB :
    ApiFunctionOgl<PFNGLUNIFORM1I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform1i64ARB";
};

struct GlUniform2i64ARB :
    ApiFunctionOgl<PFNGLUNIFORM2I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform2i64ARB";
};

struct GlUniform3i64ARB :
    ApiFunctionOgl<PFNGLUNIFORM3I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform3i64ARB";
};

struct GlUniform4i64ARB :
    ApiFunctionOgl<PFNGLUNIFORM4I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform4i64ARB";
};

struct GlUniform1i64vARB :
    ApiFunctionOgl<PFNGLUNIFORM1I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform1i64vARB";
};

struct GlUniform2i64vARB :
    ApiFunctionOgl<PFNGLUNIFORM2I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform2i64vARB";
};

struct GlUniform3i64vARB :
    ApiFunctionOgl<PFNGLUNIFORM3I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform3i64vARB";
};

struct GlUniform4i64vARB :
    ApiFunctionOgl<PFNGLUNIFORM4I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform4i64vARB";
};

struct GlUniform1ui64ARB :
    ApiFunctionOgl<PFNGLUNIFORM1UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform1ui64ARB";
};

struct GlUniform2ui64ARB :
    ApiFunctionOgl<PFNGLUNIFORM2UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform2ui64ARB";
};

struct GlUniform3ui64ARB :
    ApiFunctionOgl<PFNGLUNIFORM3UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform3ui64ARB";
};

struct GlUniform4ui64ARB :
    ApiFunctionOgl<PFNGLUNIFORM4UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform4ui64ARB";
};

struct GlUniform1ui64vARB :
    ApiFunctionOgl<PFNGLUNIFORM1UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform1ui64vARB";
};

struct GlUniform2ui64vARB :
    ApiFunctionOgl<PFNGLUNIFORM2UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform2ui64vARB";
};

struct GlUniform3ui64vARB :
    ApiFunctionOgl<PFNGLUNIFORM3UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform3ui64vARB";
};

struct GlUniform4ui64vARB :
    ApiFunctionOgl<PFNGLUNIFORM4UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glUniform4ui64vARB";
};

struct GlGetUniformi64vARB :
    ApiFunctionOgl<PFNGLGETUNIFORMI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformi64vARB";
};

struct GlGetUniformui64vARB :
    ApiFunctionOgl<PFNGLGETUNIFORMUI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformui64vARB";
};

struct GlGetnUniformi64vARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformi64vARB";
};

struct GlGetnUniformui64vARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMUI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformui64vARB";
};

struct GlProgramUniform1i64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1i64ARB";
};

struct GlProgramUniform2i64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2i64ARB";
};

struct GlProgramUniform3i64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3i64ARB";
};

struct GlProgramUniform4i64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4I64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4i64ARB";
};

struct GlProgramUniform1i64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1i64vARB";
};

struct GlProgramUniform2i64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2i64vARB";
};

struct GlProgramUniform3i64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3i64vARB";
};

struct GlProgramUniform4i64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4I64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4i64vARB";
};

struct GlProgramUniform1ui64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ui64ARB";
};

struct GlProgramUniform2ui64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ui64ARB";
};

struct GlProgramUniform3ui64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ui64ARB";
};

struct GlProgramUniform4ui64ARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UI64ARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ui64ARB";
};

struct GlProgramUniform1ui64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ui64vARB";
};

struct GlProgramUniform2ui64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ui64vARB";
};

struct GlProgramUniform3ui64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ui64vARB";
};

struct GlProgramUniform4ui64vARB :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UI64VARBPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ui64vARB";
};

struct GlMultiDrawArraysIndirectCountARB :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArraysIndirectCountARB";
};

struct GlMultiDrawElementsIndirectCountARB :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsIndirectCountARB";
};

struct GlVertexAttribDivisorARB :
    ApiFunctionOgl<PFNGLVERTEXATTRIBDIVISORARBPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribDivisorARB";
};

struct GlMaxShaderCompilerThreadsARB :
    ApiFunctionOgl<PFNGLMAXSHADERCOMPILERTHREADSARBPROC>
{
    static constexpr std::string_view Name =
        "glMaxShaderCompilerThreadsARB";
};

struct GlGetGraphicsResetStatusARB :
    ApiFunctionOgl<PFNGLGETGRAPHICSRESETSTATUSARBPROC>
{
    static constexpr std::string_view Name =
        "glGetGraphicsResetStatusARB";
};

struct GlGetnTexImageARB :
    ApiFunctionOgl<PFNGLGETNTEXIMAGEARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnTexImageARB";
};

struct GlReadnPixelsARB :
    ApiFunctionOgl<PFNGLREADNPIXELSARBPROC>
{
    static constexpr std::string_view Name =
        "glReadnPixelsARB";
};

struct GlGetnCompressedTexImageARB :
    ApiFunctionOgl<PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnCompressedTexImageARB";
};

struct GlGetnUniformfvARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMFVARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformfvARB";
};

struct GlGetnUniformivARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMIVARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformivARB";
};

struct GlGetnUniformuivARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMUIVARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformuivARB";
};

struct GlGetnUniformdvARB :
    ApiFunctionOgl<PFNGLGETNUNIFORMDVARBPROC>
{
    static constexpr std::string_view Name =
        "glGetnUniformdvARB";
};

struct GlFramebufferSampleLocationsfvARB :
    ApiFunctionOgl<PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferSampleLocationsfvARB";
};

struct GlNamedFramebufferSampleLocationsfvARB :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferSampleLocationsfvARB";
};

struct GlEvaluateDepthValuesARB :
    ApiFunctionOgl<PFNGLEVALUATEDEPTHVALUESARBPROC>
{
    static constexpr std::string_view Name =
        "glEvaluateDepthValuesARB";
};

struct GlMinSampleShadingARB :
    ApiFunctionOgl<PFNGLMINSAMPLESHADINGARBPROC>
{
    static constexpr std::string_view Name =
        "glMinSampleShadingARB";
};

struct GlNamedStringARB :
    ApiFunctionOgl<PFNGLNAMEDSTRINGARBPROC>
{
    static constexpr std::string_view Name =
        "glNamedStringARB";
};

struct GlDeleteNamedStringARB :
    ApiFunctionOgl<PFNGLDELETENAMEDSTRINGARBPROC>
{
    static constexpr std::string_view Name =
        "glDeleteNamedStringARB";
};

struct GlCompileShaderIncludeARB :
    ApiFunctionOgl<PFNGLCOMPILESHADERINCLUDEARBPROC>
{
    static constexpr std::string_view Name =
        "glCompileShaderIncludeARB";
};

struct GlIsNamedStringARB :
    ApiFunctionOgl<PFNGLISNAMEDSTRINGARBPROC>
{
    static constexpr std::string_view Name =
        "glIsNamedStringARB";
};

struct GlGetNamedStringARB :
    ApiFunctionOgl<PFNGLGETNAMEDSTRINGARBPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedStringARB";
};

struct GlGetNamedStringivARB :
    ApiFunctionOgl<PFNGLGETNAMEDSTRINGIVARBPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedStringivARB";
};

struct GlBufferPageCommitmentARB :
    ApiFunctionOgl<PFNGLBUFFERPAGECOMMITMENTARBPROC>
{
    static constexpr std::string_view Name =
        "glBufferPageCommitmentARB";
};

struct GlNamedBufferPageCommitmentEXT :
    ApiFunctionOgl<PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferPageCommitmentEXT";
};

struct GlNamedBufferPageCommitmentARB :
    ApiFunctionOgl<PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferPageCommitmentARB";
};

struct GlTexPageCommitmentARB :
    ApiFunctionOgl<PFNGLTEXPAGECOMMITMENTARBPROC>
{
    static constexpr std::string_view Name =
        "glTexPageCommitmentARB";
};

struct GlTexBufferARB :
    ApiFunctionOgl<PFNGLTEXBUFFERARBPROC>
{
    static constexpr std::string_view Name =
        "glTexBufferARB";
};

struct GlBlendBarrierKHR :
    ApiFunctionOgl<PFNGLBLENDBARRIERKHRPROC>
{
    static constexpr std::string_view Name =
        "glBlendBarrierKHR";
};

struct GlMaxShaderCompilerThreadsKHR :
    ApiFunctionOgl<PFNGLMAXSHADERCOMPILERTHREADSKHRPROC>
{
    static constexpr std::string_view Name =
        "glMaxShaderCompilerThreadsKHR";
};

struct GlGetPerfMonitorGroupsAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORGROUPSAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorGroupsAMD";
};

struct GlGetPerfMonitorCountersAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORCOUNTERSAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorCountersAMD";
};

struct GlGetPerfMonitorGroupStringAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORGROUPSTRINGAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorGroupStringAMD";
};

struct GlGetPerfMonitorCounterStringAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorCounterStringAMD";
};

struct GlGetPerfMonitorCounterInfoAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORCOUNTERINFOAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorCounterInfoAMD";
};

struct GlGenPerfMonitorsAMD :
    ApiFunctionOgl<PFNGLGENPERFMONITORSAMDPROC>
{
    static constexpr std::string_view Name =
        "glGenPerfMonitorsAMD";
};

struct GlDeletePerfMonitorsAMD :
    ApiFunctionOgl<PFNGLDELETEPERFMONITORSAMDPROC>
{
    static constexpr std::string_view Name =
        "glDeletePerfMonitorsAMD";
};

struct GlSelectPerfMonitorCountersAMD :
    ApiFunctionOgl<PFNGLSELECTPERFMONITORCOUNTERSAMDPROC>
{
    static constexpr std::string_view Name =
        "glSelectPerfMonitorCountersAMD";
};

struct GlBeginPerfMonitorAMD :
    ApiFunctionOgl<PFNGLBEGINPERFMONITORAMDPROC>
{
    static constexpr std::string_view Name =
        "glBeginPerfMonitorAMD";
};

struct GlEndPerfMonitorAMD :
    ApiFunctionOgl<PFNGLENDPERFMONITORAMDPROC>
{
    static constexpr std::string_view Name =
        "glEndPerfMonitorAMD";
};

struct GlGetPerfMonitorCounterDataAMD :
    ApiFunctionOgl<PFNGLGETPERFMONITORCOUNTERDATAAMDPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfMonitorCounterDataAMD";
};

struct GlEGLImageTargetTexStorageEXT :
    ApiFunctionOgl<PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glEGLImageTargetTexStorageEXT";
};

struct GlEGLImageTargetTextureStorageEXT :
    ApiFunctionOgl<PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glEGLImageTargetTextureStorageEXT";
};

struct GlLabelObjectEXT :
    ApiFunctionOgl<PFNGLLABELOBJECTEXTPROC>
{
    static constexpr std::string_view Name =
        "glLabelObjectEXT";
};

struct GlGetObjectLabelEXT :
    ApiFunctionOgl<PFNGLGETOBJECTLABELEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetObjectLabelEXT";
};

struct GlInsertEventMarkerEXT :
    ApiFunctionOgl<PFNGLINSERTEVENTMARKEREXTPROC>
{
    static constexpr std::string_view Name =
        "glInsertEventMarkerEXT";
};

struct GlPushGroupMarkerEXT :
    ApiFunctionOgl<PFNGLPUSHGROUPMARKEREXTPROC>
{
    static constexpr std::string_view Name =
        "glPushGroupMarkerEXT";
};

struct GlPopGroupMarkerEXT :
    ApiFunctionOgl<PFNGLPOPGROUPMARKEREXTPROC>
{
    static constexpr std::string_view Name =
        "glPopGroupMarkerEXT";
};

struct GlMatrixLoadfEXT :
    ApiFunctionOgl<PFNGLMATRIXLOADFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoadfEXT";
};

struct GlMatrixLoaddEXT :
    ApiFunctionOgl<PFNGLMATRIXLOADDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoaddEXT";
};

struct GlMatrixMultfEXT :
    ApiFunctionOgl<PFNGLMATRIXMULTFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMultfEXT";
};

struct GlMatrixMultdEXT :
    ApiFunctionOgl<PFNGLMATRIXMULTDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMultdEXT";
};

struct GlMatrixLoadIdentityEXT :
    ApiFunctionOgl<PFNGLMATRIXLOADIDENTITYEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoadIdentityEXT";
};

struct GlMatrixRotatefEXT :
    ApiFunctionOgl<PFNGLMATRIXROTATEFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixRotatefEXT";
};

struct GlMatrixRotatedEXT :
    ApiFunctionOgl<PFNGLMATRIXROTATEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixRotatedEXT";
};

struct GlMatrixScalefEXT :
    ApiFunctionOgl<PFNGLMATRIXSCALEFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixScalefEXT";
};

struct GlMatrixScaledEXT :
    ApiFunctionOgl<PFNGLMATRIXSCALEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixScaledEXT";
};

struct GlMatrixTranslatefEXT :
    ApiFunctionOgl<PFNGLMATRIXTRANSLATEFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixTranslatefEXT";
};

struct GlMatrixTranslatedEXT :
    ApiFunctionOgl<PFNGLMATRIXTRANSLATEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixTranslatedEXT";
};

struct GlMatrixFrustumEXT :
    ApiFunctionOgl<PFNGLMATRIXFRUSTUMEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixFrustumEXT";
};

struct GlMatrixOrthoEXT :
    ApiFunctionOgl<PFNGLMATRIXORTHOEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixOrthoEXT";
};

struct GlMatrixPopEXT :
    ApiFunctionOgl<PFNGLMATRIXPOPEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixPopEXT";
};

struct GlMatrixPushEXT :
    ApiFunctionOgl<PFNGLMATRIXPUSHEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixPushEXT";
};

struct GlClientAttribDefaultEXT :
    ApiFunctionOgl<PFNGLCLIENTATTRIBDEFAULTEXTPROC>
{
    static constexpr std::string_view Name =
        "glClientAttribDefaultEXT";
};

struct GlPushClientAttribDefaultEXT :
    ApiFunctionOgl<PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC>
{
    static constexpr std::string_view Name =
        "glPushClientAttribDefaultEXT";
};

struct GlTextureParameterfEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERFEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterfEXT";
};

struct GlTextureParameterfvEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterfvEXT";
};

struct GlTextureParameteriEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameteriEXT";
};

struct GlTextureParameterivEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterivEXT";
};

struct GlTextureImage1DEXT :
    ApiFunctionOgl<PFNGLTEXTUREIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureImage1DEXT";
};

struct GlTextureImage2DEXT :
    ApiFunctionOgl<PFNGLTEXTUREIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureImage2DEXT";
};

struct GlTextureSubImage1DEXT :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage1DEXT";
};

struct GlTextureSubImage2DEXT :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage2DEXT";
};

struct GlCopyTextureImage1DEXT :
    ApiFunctionOgl<PFNGLCOPYTEXTUREIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureImage1DEXT";
};

struct GlCopyTextureImage2DEXT :
    ApiFunctionOgl<PFNGLCOPYTEXTUREIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureImage2DEXT";
};

struct GlCopyTextureSubImage1DEXT :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage1DEXT";
};

struct GlCopyTextureSubImage2DEXT :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage2DEXT";
};

struct GlGetTextureImageEXT :
    ApiFunctionOgl<PFNGLGETTEXTUREIMAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureImageEXT";
};

struct GlGetTextureParameterfvEXT :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterfvEXT";
};

struct GlGetTextureParameterivEXT :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterivEXT";
};

struct GlGetTextureLevelParameterfvEXT :
    ApiFunctionOgl<PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureLevelParameterfvEXT";
};

struct GlGetTextureLevelParameterivEXT :
    ApiFunctionOgl<PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureLevelParameterivEXT";
};

struct GlTextureImage3DEXT :
    ApiFunctionOgl<PFNGLTEXTUREIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureImage3DEXT";
};

struct GlTextureSubImage3DEXT :
    ApiFunctionOgl<PFNGLTEXTURESUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureSubImage3DEXT";
};

struct GlCopyTextureSubImage3DEXT :
    ApiFunctionOgl<PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyTextureSubImage3DEXT";
};

struct GlBindMultiTextureEXT :
    ApiFunctionOgl<PFNGLBINDMULTITEXTUREEXTPROC>
{
    static constexpr std::string_view Name =
        "glBindMultiTextureEXT";
};

struct GlMultiTexCoordPointerEXT :
    ApiFunctionOgl<PFNGLMULTITEXCOORDPOINTEREXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexCoordPointerEXT";
};

struct GlMultiTexEnvfEXT :
    ApiFunctionOgl<PFNGLMULTITEXENVFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexEnvfEXT";
};

struct GlMultiTexEnvfvEXT :
    ApiFunctionOgl<PFNGLMULTITEXENVFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexEnvfvEXT";
};

struct GlMultiTexEnviEXT :
    ApiFunctionOgl<PFNGLMULTITEXENVIEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexEnviEXT";
};

struct GlMultiTexEnvivEXT :
    ApiFunctionOgl<PFNGLMULTITEXENVIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexEnvivEXT";
};

struct GlMultiTexGendEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGendEXT";
};

struct GlMultiTexGendvEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGendvEXT";
};

struct GlMultiTexGenfEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGenfEXT";
};

struct GlMultiTexGenfvEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGenfvEXT";
};

struct GlMultiTexGeniEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENIEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGeniEXT";
};

struct GlMultiTexGenivEXT :
    ApiFunctionOgl<PFNGLMULTITEXGENIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexGenivEXT";
};

struct GlGetMultiTexEnvfvEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXENVFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexEnvfvEXT";
};

struct GlGetMultiTexEnvivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXENVIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexEnvivEXT";
};

struct GlGetMultiTexGendvEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXGENDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexGendvEXT";
};

struct GlGetMultiTexGenfvEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXGENFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexGenfvEXT";
};

struct GlGetMultiTexGenivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXGENIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexGenivEXT";
};

struct GlMultiTexParameteriEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERIEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameteriEXT";
};

struct GlMultiTexParameterivEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameterivEXT";
};

struct GlMultiTexParameterfEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameterfEXT";
};

struct GlMultiTexParameterfvEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameterfvEXT";
};

struct GlMultiTexImage1DEXT :
    ApiFunctionOgl<PFNGLMULTITEXIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexImage1DEXT";
};

struct GlMultiTexImage2DEXT :
    ApiFunctionOgl<PFNGLMULTITEXIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexImage2DEXT";
};

struct GlMultiTexSubImage1DEXT :
    ApiFunctionOgl<PFNGLMULTITEXSUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexSubImage1DEXT";
};

struct GlMultiTexSubImage2DEXT :
    ApiFunctionOgl<PFNGLMULTITEXSUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexSubImage2DEXT";
};

struct GlCopyMultiTexImage1DEXT :
    ApiFunctionOgl<PFNGLCOPYMULTITEXIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyMultiTexImage1DEXT";
};

struct GlCopyMultiTexImage2DEXT :
    ApiFunctionOgl<PFNGLCOPYMULTITEXIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyMultiTexImage2DEXT";
};

struct GlCopyMultiTexSubImage1DEXT :
    ApiFunctionOgl<PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyMultiTexSubImage1DEXT";
};

struct GlCopyMultiTexSubImage2DEXT :
    ApiFunctionOgl<PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyMultiTexSubImage2DEXT";
};

struct GlGetMultiTexImageEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXIMAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexImageEXT";
};

struct GlGetMultiTexParameterfvEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexParameterfvEXT";
};

struct GlGetMultiTexParameterivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexParameterivEXT";
};

struct GlGetMultiTexLevelParameterfvEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexLevelParameterfvEXT";
};

struct GlGetMultiTexLevelParameterivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexLevelParameterivEXT";
};

struct GlMultiTexImage3DEXT :
    ApiFunctionOgl<PFNGLMULTITEXIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexImage3DEXT";
};

struct GlMultiTexSubImage3DEXT :
    ApiFunctionOgl<PFNGLMULTITEXSUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexSubImage3DEXT";
};

struct GlCopyMultiTexSubImage3DEXT :
    ApiFunctionOgl<PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCopyMultiTexSubImage3DEXT";
};

struct GlEnableClientStateIndexedEXT :
    ApiFunctionOgl<PFNGLENABLECLIENTSTATEINDEXEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glEnableClientStateIndexedEXT";
};

struct GlDisableClientStateIndexedEXT :
    ApiFunctionOgl<PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glDisableClientStateIndexedEXT";
};

struct GlGetFloatIndexedvEXT :
    ApiFunctionOgl<PFNGLGETFLOATINDEXEDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetFloatIndexedvEXT";
};

struct GlGetDoubleIndexedvEXT :
    ApiFunctionOgl<PFNGLGETDOUBLEINDEXEDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetDoubleIndexedvEXT";
};

struct GlGetPointerIndexedvEXT :
    ApiFunctionOgl<PFNGLGETPOINTERINDEXEDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetPointerIndexedvEXT";
};

struct GlEnableIndexedEXT :
    ApiFunctionOgl<PFNGLENABLEINDEXEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glEnableIndexedEXT";
};

struct GlDisableIndexedEXT :
    ApiFunctionOgl<PFNGLDISABLEINDEXEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glDisableIndexedEXT";
};

struct GlIsEnabledIndexedEXT :
    ApiFunctionOgl<PFNGLISENABLEDINDEXEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glIsEnabledIndexedEXT";
};

struct GlGetIntegerIndexedvEXT :
    ApiFunctionOgl<PFNGLGETINTEGERINDEXEDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetIntegerIndexedvEXT";
};

struct GlGetBooleanIndexedvEXT :
    ApiFunctionOgl<PFNGLGETBOOLEANINDEXEDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetBooleanIndexedvEXT";
};

struct GlCompressedTextureImage3DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureImage3DEXT";
};

struct GlCompressedTextureImage2DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureImage2DEXT";
};

struct GlCompressedTextureImage1DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureImage1DEXT";
};

struct GlCompressedTextureSubImage3DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage3DEXT";
};

struct GlCompressedTextureSubImage2DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage2DEXT";
};

struct GlCompressedTextureSubImage1DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedTextureSubImage1DEXT";
};

struct GlGetCompressedTextureImageEXT :
    ApiFunctionOgl<PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetCompressedTextureImageEXT";
};

struct GlCompressedMultiTexImage3DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexImage3DEXT";
};

struct GlCompressedMultiTexImage2DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexImage2DEXT";
};

struct GlCompressedMultiTexImage1DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexImage1DEXT";
};

struct GlCompressedMultiTexSubImage3DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexSubImage3DEXT";
};

struct GlCompressedMultiTexSubImage2DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexSubImage2DEXT";
};

struct GlCompressedMultiTexSubImage1DEXT :
    ApiFunctionOgl<PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glCompressedMultiTexSubImage1DEXT";
};

struct GlGetCompressedMultiTexImageEXT :
    ApiFunctionOgl<PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetCompressedMultiTexImageEXT";
};

struct GlMatrixLoadTransposefEXT :
    ApiFunctionOgl<PFNGLMATRIXLOADTRANSPOSEFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoadTransposefEXT";
};

struct GlMatrixLoadTransposedEXT :
    ApiFunctionOgl<PFNGLMATRIXLOADTRANSPOSEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoadTransposedEXT";
};

struct GlMatrixMultTransposefEXT :
    ApiFunctionOgl<PFNGLMATRIXMULTTRANSPOSEFEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMultTransposefEXT";
};

struct GlMatrixMultTransposedEXT :
    ApiFunctionOgl<PFNGLMATRIXMULTTRANSPOSEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMultTransposedEXT";
};

struct GlNamedBufferDataEXT :
    ApiFunctionOgl<PFNGLNAMEDBUFFERDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferDataEXT";
};

struct GlNamedBufferSubDataEXT :
    ApiFunctionOgl<PFNGLNAMEDBUFFERSUBDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferSubDataEXT";
};

struct GlMapNamedBufferEXT :
    ApiFunctionOgl<PFNGLMAPNAMEDBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glMapNamedBufferEXT";
};

struct GlUnmapNamedBufferEXT :
    ApiFunctionOgl<PFNGLUNMAPNAMEDBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glUnmapNamedBufferEXT";
};

struct GlGetNamedBufferParameterivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferParameterivEXT";
};

struct GlGetNamedBufferPointervEXT :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPOINTERVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferPointervEXT";
};

struct GlGetNamedBufferSubDataEXT :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERSUBDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferSubDataEXT";
};

struct GlProgramUniform1fEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1FEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1fEXT";
};

struct GlProgramUniform2fEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2FEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2fEXT";
};

struct GlProgramUniform3fEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3FEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3fEXT";
};

struct GlProgramUniform4fEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4FEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4fEXT";
};

struct GlProgramUniform1iEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1IEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1iEXT";
};

struct GlProgramUniform2iEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2IEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2iEXT";
};

struct GlProgramUniform3iEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3IEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3iEXT";
};

struct GlProgramUniform4iEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4IEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4iEXT";
};

struct GlProgramUniform1fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1fvEXT";
};

struct GlProgramUniform2fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2fvEXT";
};

struct GlProgramUniform3fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3fvEXT";
};

struct GlProgramUniform4fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4fvEXT";
};

struct GlProgramUniform1ivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ivEXT";
};

struct GlProgramUniform2ivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ivEXT";
};

struct GlProgramUniform3ivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ivEXT";
};

struct GlProgramUniform4ivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ivEXT";
};

struct GlProgramUniformMatrix2fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2fvEXT";
};

struct GlProgramUniformMatrix3fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3fvEXT";
};

struct GlProgramUniformMatrix4fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4fvEXT";
};

struct GlProgramUniformMatrix2x3fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x3fvEXT";
};

struct GlProgramUniformMatrix3x2fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x2fvEXT";
};

struct GlProgramUniformMatrix2x4fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x4fvEXT";
};

struct GlProgramUniformMatrix4x2fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x2fvEXT";
};

struct GlProgramUniformMatrix3x4fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x4fvEXT";
};

struct GlProgramUniformMatrix4x3fvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x3fvEXT";
};

struct GlTextureBufferEXT :
    ApiFunctionOgl<PFNGLTEXTUREBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureBufferEXT";
};

struct GlMultiTexBufferEXT :
    ApiFunctionOgl<PFNGLMULTITEXBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexBufferEXT";
};

struct GlTextureParameterIivEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterIivEXT";
};

struct GlTextureParameterIuivEXT :
    ApiFunctionOgl<PFNGLTEXTUREPARAMETERIUIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureParameterIuivEXT";
};

struct GlGetTextureParameterIivEXT :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterIivEXT";
};

struct GlGetTextureParameterIuivEXT :
    ApiFunctionOgl<PFNGLGETTEXTUREPARAMETERIUIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureParameterIuivEXT";
};

struct GlMultiTexParameterIivEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERIIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameterIivEXT";
};

struct GlMultiTexParameterIuivEXT :
    ApiFunctionOgl<PFNGLMULTITEXPARAMETERIUIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexParameterIuivEXT";
};

struct GlGetMultiTexParameterIivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXPARAMETERIIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexParameterIivEXT";
};

struct GlGetMultiTexParameterIuivEXT :
    ApiFunctionOgl<PFNGLGETMULTITEXPARAMETERIUIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetMultiTexParameterIuivEXT";
};

struct GlProgramUniform1uiEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UIEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1uiEXT";
};

struct GlProgramUniform2uiEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UIEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2uiEXT";
};

struct GlProgramUniform3uiEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UIEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3uiEXT";
};

struct GlProgramUniform4uiEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UIEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4uiEXT";
};

struct GlProgramUniform1uivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1uivEXT";
};

struct GlProgramUniform2uivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2uivEXT";
};

struct GlProgramUniform3uivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3uivEXT";
};

struct GlProgramUniform4uivEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4uivEXT";
};

struct GlNamedProgramLocalParameters4fvEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameters4fvEXT";
};

struct GlNamedProgramLocalParameterI4iEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameterI4iEXT";
};

struct GlNamedProgramLocalParameterI4ivEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameterI4ivEXT";
};

struct GlNamedProgramLocalParametersI4ivEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParametersI4ivEXT";
};

struct GlNamedProgramLocalParameterI4uiEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameterI4uiEXT";
};

struct GlNamedProgramLocalParameterI4uivEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameterI4uivEXT";
};

struct GlNamedProgramLocalParametersI4uivEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParametersI4uivEXT";
};

struct GlGetNamedProgramLocalParameterIivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramLocalParameterIivEXT";
};

struct GlGetNamedProgramLocalParameterIuivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramLocalParameterIuivEXT";
};

struct GlEnableClientStateiEXT :
    ApiFunctionOgl<PFNGLENABLECLIENTSTATEIEXTPROC>
{
    static constexpr std::string_view Name =
        "glEnableClientStateiEXT";
};

struct GlDisableClientStateiEXT :
    ApiFunctionOgl<PFNGLDISABLECLIENTSTATEIEXTPROC>
{
    static constexpr std::string_view Name =
        "glDisableClientStateiEXT";
};

struct GlGetFloati_vEXT :
    ApiFunctionOgl<PFNGLGETFLOATI_VEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetFloati_vEXT";
};

struct GlGetDoublei_vEXT :
    ApiFunctionOgl<PFNGLGETDOUBLEI_VEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetDoublei_vEXT";
};

struct GlGetPointeri_vEXT :
    ApiFunctionOgl<PFNGLGETPOINTERI_VEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetPointeri_vEXT";
};

struct GlNamedProgramStringEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMSTRINGEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramStringEXT";
};

struct GlNamedProgramLocalParameter4dEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameter4dEXT";
};

struct GlNamedProgramLocalParameter4dvEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameter4dvEXT";
};

struct GlNamedProgramLocalParameter4fEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameter4fEXT";
};

struct GlNamedProgramLocalParameter4fvEXT :
    ApiFunctionOgl<PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedProgramLocalParameter4fvEXT";
};

struct GlGetNamedProgramLocalParameterdvEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramLocalParameterdvEXT";
};

struct GlGetNamedProgramLocalParameterfvEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramLocalParameterfvEXT";
};

struct GlGetNamedProgramivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramivEXT";
};

struct GlGetNamedProgramStringEXT :
    ApiFunctionOgl<PFNGLGETNAMEDPROGRAMSTRINGEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedProgramStringEXT";
};

struct GlNamedRenderbufferStorageEXT :
    ApiFunctionOgl<PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedRenderbufferStorageEXT";
};

struct GlGetNamedRenderbufferParameterivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedRenderbufferParameterivEXT";
};

struct GlNamedRenderbufferStorageMultisampleEXT :
    ApiFunctionOgl<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedRenderbufferStorageMultisampleEXT";
};

struct GlNamedRenderbufferStorageMultisampleCoverageEXT :
    ApiFunctionOgl<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedRenderbufferStorageMultisampleCoverageEXT";
};

struct GlCheckNamedFramebufferStatusEXT :
    ApiFunctionOgl<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC>
{
    static constexpr std::string_view Name =
        "glCheckNamedFramebufferStatusEXT";
};

struct GlNamedFramebufferTexture1DEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTexture1DEXT";
};

struct GlNamedFramebufferTexture2DEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTexture2DEXT";
};

struct GlNamedFramebufferTexture3DEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTexture3DEXT";
};

struct GlNamedFramebufferRenderbufferEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferRenderbufferEXT";
};

struct GlGetNamedFramebufferAttachmentParameterivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedFramebufferAttachmentParameterivEXT";
};

struct GlGenerateTextureMipmapEXT :
    ApiFunctionOgl<PFNGLGENERATETEXTUREMIPMAPEXTPROC>
{
    static constexpr std::string_view Name =
        "glGenerateTextureMipmapEXT";
};

struct GlGenerateMultiTexMipmapEXT :
    ApiFunctionOgl<PFNGLGENERATEMULTITEXMIPMAPEXTPROC>
{
    static constexpr std::string_view Name =
        "glGenerateMultiTexMipmapEXT";
};

struct GlFramebufferDrawBufferEXT :
    ApiFunctionOgl<PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferDrawBufferEXT";
};

struct GlFramebufferDrawBuffersEXT :
    ApiFunctionOgl<PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferDrawBuffersEXT";
};

struct GlFramebufferReadBufferEXT :
    ApiFunctionOgl<PFNGLFRAMEBUFFERREADBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferReadBufferEXT";
};

struct GlGetFramebufferParameterivEXT :
    ApiFunctionOgl<PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetFramebufferParameterivEXT";
};

struct GlNamedCopyBufferSubDataEXT :
    ApiFunctionOgl<PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedCopyBufferSubDataEXT";
};

struct GlNamedFramebufferTextureEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTextureEXT";
};

struct GlNamedFramebufferTextureLayerEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTextureLayerEXT";
};

struct GlNamedFramebufferTextureFaceEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferTextureFaceEXT";
};

struct GlTextureRenderbufferEXT :
    ApiFunctionOgl<PFNGLTEXTURERENDERBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureRenderbufferEXT";
};

struct GlMultiTexRenderbufferEXT :
    ApiFunctionOgl<PFNGLMULTITEXRENDERBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glMultiTexRenderbufferEXT";
};

struct GlVertexArrayVertexOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexOffsetEXT";
};

struct GlVertexArrayColorOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYCOLOROFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayColorOffsetEXT";
};

struct GlVertexArrayEdgeFlagOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayEdgeFlagOffsetEXT";
};

struct GlVertexArrayIndexOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYINDEXOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayIndexOffsetEXT";
};

struct GlVertexArrayNormalOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYNORMALOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayNormalOffsetEXT";
};

struct GlVertexArrayTexCoordOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayTexCoordOffsetEXT";
};

struct GlVertexArrayMultiTexCoordOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayMultiTexCoordOffsetEXT";
};

struct GlVertexArrayFogCoordOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayFogCoordOffsetEXT";
};

struct GlVertexArraySecondaryColorOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArraySecondaryColorOffsetEXT";
};

struct GlVertexArrayVertexAttribOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribOffsetEXT";
};

struct GlVertexArrayVertexAttribIOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribIOffsetEXT";
};

struct GlEnableVertexArrayEXT :
    ApiFunctionOgl<PFNGLENABLEVERTEXARRAYEXTPROC>
{
    static constexpr std::string_view Name =
        "glEnableVertexArrayEXT";
};

struct GlDisableVertexArrayEXT :
    ApiFunctionOgl<PFNGLDISABLEVERTEXARRAYEXTPROC>
{
    static constexpr std::string_view Name =
        "glDisableVertexArrayEXT";
};

struct GlEnableVertexArrayAttribEXT :
    ApiFunctionOgl<PFNGLENABLEVERTEXARRAYATTRIBEXTPROC>
{
    static constexpr std::string_view Name =
        "glEnableVertexArrayAttribEXT";
};

struct GlDisableVertexArrayAttribEXT :
    ApiFunctionOgl<PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC>
{
    static constexpr std::string_view Name =
        "glDisableVertexArrayAttribEXT";
};

struct GlGetVertexArrayIntegervEXT :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYINTEGERVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayIntegervEXT";
};

struct GlGetVertexArrayPointervEXT :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYPOINTERVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayPointervEXT";
};

struct GlGetVertexArrayIntegeri_vEXT :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayIntegeri_vEXT";
};

struct GlGetVertexArrayPointeri_vEXT :
    ApiFunctionOgl<PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexArrayPointeri_vEXT";
};

struct GlMapNamedBufferRangeEXT :
    ApiFunctionOgl<PFNGLMAPNAMEDBUFFERRANGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glMapNamedBufferRangeEXT";
};

struct GlFlushMappedNamedBufferRangeEXT :
    ApiFunctionOgl<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glFlushMappedNamedBufferRangeEXT";
};

struct GlNamedBufferStorageEXT :
    ApiFunctionOgl<PFNGLNAMEDBUFFERSTORAGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedBufferStorageEXT";
};

struct GlClearNamedBufferDataEXT :
    ApiFunctionOgl<PFNGLCLEARNAMEDBUFFERDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedBufferDataEXT";
};

struct GlClearNamedBufferSubDataEXT :
    ApiFunctionOgl<PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC>
{
    static constexpr std::string_view Name =
        "glClearNamedBufferSubDataEXT";
};

struct GlNamedFramebufferParameteriEXT :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferParameteriEXT";
};

struct GlGetNamedFramebufferParameterivEXT :
    ApiFunctionOgl<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedFramebufferParameterivEXT";
};

struct GlProgramUniform1dEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1dEXT";
};

struct GlProgramUniform2dEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2dEXT";
};

struct GlProgramUniform3dEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3dEXT";
};

struct GlProgramUniform4dEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4DEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4dEXT";
};

struct GlProgramUniform1dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1dvEXT";
};

struct GlProgramUniform2dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2dvEXT";
};

struct GlProgramUniform3dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3dvEXT";
};

struct GlProgramUniform4dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4dvEXT";
};

struct GlProgramUniformMatrix2dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2dvEXT";
};

struct GlProgramUniformMatrix3dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3dvEXT";
};

struct GlProgramUniformMatrix4dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4dvEXT";
};

struct GlProgramUniformMatrix2x3dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x3dvEXT";
};

struct GlProgramUniformMatrix2x4dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix2x4dvEXT";
};

struct GlProgramUniformMatrix3x2dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x2dvEXT";
};

struct GlProgramUniformMatrix3x4dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix3x4dvEXT";
};

struct GlProgramUniformMatrix4x2dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x2dvEXT";
};

struct GlProgramUniformMatrix4x3dvEXT :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformMatrix4x3dvEXT";
};

struct GlTextureBufferRangeEXT :
    ApiFunctionOgl<PFNGLTEXTUREBUFFERRANGEEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureBufferRangeEXT";
};

struct GlTextureStorage1DEXT :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE1DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage1DEXT";
};

struct GlTextureStorage2DEXT :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE2DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage2DEXT";
};

struct GlTextureStorage3DEXT :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE3DEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage3DEXT";
};

struct GlTextureStorage2DMultisampleEXT :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage2DMultisampleEXT";
};

struct GlTextureStorage3DMultisampleEXT :
    ApiFunctionOgl<PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC>
{
    static constexpr std::string_view Name =
        "glTextureStorage3DMultisampleEXT";
};

struct GlVertexArrayBindVertexBufferEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayBindVertexBufferEXT";
};

struct GlVertexArrayVertexAttribFormatEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribFormatEXT";
};

struct GlVertexArrayVertexAttribIFormatEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribIFormatEXT";
};

struct GlVertexArrayVertexAttribLFormatEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribLFormatEXT";
};

struct GlVertexArrayVertexAttribBindingEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribBindingEXT";
};

struct GlVertexArrayVertexBindingDivisorEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexBindingDivisorEXT";
};

struct GlVertexArrayVertexAttribLOffsetEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribLOffsetEXT";
};

struct GlTexturePageCommitmentEXT :
    ApiFunctionOgl<PFNGLTEXTUREPAGECOMMITMENTEXTPROC>
{
    static constexpr std::string_view Name =
        "glTexturePageCommitmentEXT";
};

struct GlVertexArrayVertexAttribDivisorEXT :
    ApiFunctionOgl<PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC>
{
    static constexpr std::string_view Name =
        "glVertexArrayVertexAttribDivisorEXT";
};

struct GlDrawArraysInstancedEXT :
    ApiFunctionOgl<PFNGLDRAWARRAYSINSTANCEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glDrawArraysInstancedEXT";
};

struct GlDrawElementsInstancedEXT :
    ApiFunctionOgl<PFNGLDRAWELEMENTSINSTANCEDEXTPROC>
{
    static constexpr std::string_view Name =
        "glDrawElementsInstancedEXT";
};

struct GlPolygonOffsetClampEXT :
    ApiFunctionOgl<PFNGLPOLYGONOFFSETCLAMPEXTPROC>
{
    static constexpr std::string_view Name =
        "glPolygonOffsetClampEXT";
};

struct GlRasterSamplesEXT :
    ApiFunctionOgl<PFNGLRASTERSAMPLESEXTPROC>
{
    static constexpr std::string_view Name =
        "glRasterSamplesEXT";
};

struct GlUseShaderProgramEXT :
    ApiFunctionOgl<PFNGLUSESHADERPROGRAMEXTPROC>
{
    static constexpr std::string_view Name =
        "glUseShaderProgramEXT";
};

struct GlActiveProgramEXT :
    ApiFunctionOgl<PFNGLACTIVEPROGRAMEXTPROC>
{
    static constexpr std::string_view Name =
        "glActiveProgramEXT";
};

struct GlCreateShaderProgramEXT :
    ApiFunctionOgl<PFNGLCREATESHADERPROGRAMEXTPROC>
{
    static constexpr std::string_view Name =
        "glCreateShaderProgramEXT";
};

struct GlFramebufferFetchBarrierEXT :
    ApiFunctionOgl<PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferFetchBarrierEXT";
};

struct GlWindowRectanglesEXT :
    ApiFunctionOgl<PFNGLWINDOWRECTANGLESEXTPROC>
{
    static constexpr std::string_view Name =
        "glWindowRectanglesEXT";
};

struct GlApplyFramebufferAttachmentCMAAINTEL :
    ApiFunctionOgl<PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC>
{
    static constexpr std::string_view Name =
        "glApplyFramebufferAttachmentCMAAINTEL";
};

struct GlBeginPerfQueryINTEL :
    ApiFunctionOgl<PFNGLBEGINPERFQUERYINTELPROC>
{
    static constexpr std::string_view Name =
        "glBeginPerfQueryINTEL";
};

struct GlCreatePerfQueryINTEL :
    ApiFunctionOgl<PFNGLCREATEPERFQUERYINTELPROC>
{
    static constexpr std::string_view Name =
        "glCreatePerfQueryINTEL";
};

struct GlDeletePerfQueryINTEL :
    ApiFunctionOgl<PFNGLDELETEPERFQUERYINTELPROC>
{
    static constexpr std::string_view Name =
        "glDeletePerfQueryINTEL";
};

struct GlEndPerfQueryINTEL :
    ApiFunctionOgl<PFNGLENDPERFQUERYINTELPROC>
{
    static constexpr std::string_view Name =
        "glEndPerfQueryINTEL";
};

struct GlGetFirstPerfQueryIdINTEL :
    ApiFunctionOgl<PFNGLGETFIRSTPERFQUERYIDINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetFirstPerfQueryIdINTEL";
};

struct GlGetNextPerfQueryIdINTEL :
    ApiFunctionOgl<PFNGLGETNEXTPERFQUERYIDINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetNextPerfQueryIdINTEL";
};

struct GlGetPerfCounterInfoINTEL :
    ApiFunctionOgl<PFNGLGETPERFCOUNTERINFOINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfCounterInfoINTEL";
};

struct GlGetPerfQueryDataINTEL :
    ApiFunctionOgl<PFNGLGETPERFQUERYDATAINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfQueryDataINTEL";
};

struct GlGetPerfQueryIdByNameINTEL :
    ApiFunctionOgl<PFNGLGETPERFQUERYIDBYNAMEINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfQueryIdByNameINTEL";
};

struct GlGetPerfQueryInfoINTEL :
    ApiFunctionOgl<PFNGLGETPERFQUERYINFOINTELPROC>
{
    static constexpr std::string_view Name =
        "glGetPerfQueryInfoINTEL";
};

struct GlMultiDrawArraysIndirectBindlessNV :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArraysIndirectBindlessNV";
};

struct GlMultiDrawElementsIndirectBindlessNV :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsIndirectBindlessNV";
};

struct GlMultiDrawArraysIndirectBindlessCountNV :
    ApiFunctionOgl<PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawArraysIndirectBindlessCountNV";
};

struct GlMultiDrawElementsIndirectBindlessCountNV :
    ApiFunctionOgl<PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC>
{
    static constexpr std::string_view Name =
        "glMultiDrawElementsIndirectBindlessCountNV";
};

struct GlGetTextureHandleNV :
    ApiFunctionOgl<PFNGLGETTEXTUREHANDLENVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureHandleNV";
};

struct GlGetTextureSamplerHandleNV :
    ApiFunctionOgl<PFNGLGETTEXTURESAMPLERHANDLENVPROC>
{
    static constexpr std::string_view Name =
        "glGetTextureSamplerHandleNV";
};

struct GlMakeTextureHandleResidentNV :
    ApiFunctionOgl<PFNGLMAKETEXTUREHANDLERESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeTextureHandleResidentNV";
};

struct GlMakeTextureHandleNonResidentNV :
    ApiFunctionOgl<PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeTextureHandleNonResidentNV";
};

struct GlGetImageHandleNV :
    ApiFunctionOgl<PFNGLGETIMAGEHANDLENVPROC>
{
    static constexpr std::string_view Name =
        "glGetImageHandleNV";
};

struct GlMakeImageHandleResidentNV :
    ApiFunctionOgl<PFNGLMAKEIMAGEHANDLERESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeImageHandleResidentNV";
};

struct GlMakeImageHandleNonResidentNV :
    ApiFunctionOgl<PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeImageHandleNonResidentNV";
};

struct GlUniformHandleui64NV :
    ApiFunctionOgl<PFNGLUNIFORMHANDLEUI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniformHandleui64NV";
};

struct GlUniformHandleui64vNV :
    ApiFunctionOgl<PFNGLUNIFORMHANDLEUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniformHandleui64vNV";
};

struct GlProgramUniformHandleui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformHandleui64NV";
};

struct GlProgramUniformHandleui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformHandleui64vNV";
};

struct GlIsTextureHandleResidentNV :
    ApiFunctionOgl<PFNGLISTEXTUREHANDLERESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glIsTextureHandleResidentNV";
};

struct GlIsImageHandleResidentNV :
    ApiFunctionOgl<PFNGLISIMAGEHANDLERESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glIsImageHandleResidentNV";
};

struct GlBlendParameteriNV :
    ApiFunctionOgl<PFNGLBLENDPARAMETERINVPROC>
{
    static constexpr std::string_view Name =
        "glBlendParameteriNV";
};

struct GlBlendBarrierNV :
    ApiFunctionOgl<PFNGLBLENDBARRIERNVPROC>
{
    static constexpr std::string_view Name =
        "glBlendBarrierNV";
};

struct GlViewportPositionWScaleNV :
    ApiFunctionOgl<PFNGLVIEWPORTPOSITIONWSCALENVPROC>
{
    static constexpr std::string_view Name =
        "glViewportPositionWScaleNV";
};

struct GlCreateStatesNV :
    ApiFunctionOgl<PFNGLCREATESTATESNVPROC>
{
    static constexpr std::string_view Name =
        "glCreateStatesNV";
};

struct GlDeleteStatesNV :
    ApiFunctionOgl<PFNGLDELETESTATESNVPROC>
{
    static constexpr std::string_view Name =
        "glDeleteStatesNV";
};

struct GlIsStateNV :
    ApiFunctionOgl<PFNGLISSTATENVPROC>
{
    static constexpr std::string_view Name =
        "glIsStateNV";
};

struct GlStateCaptureNV :
    ApiFunctionOgl<PFNGLSTATECAPTURENVPROC>
{
    static constexpr std::string_view Name =
        "glStateCaptureNV";
};

struct GlGetCommandHeaderNV :
    ApiFunctionOgl<PFNGLGETCOMMANDHEADERNVPROC>
{
    static constexpr std::string_view Name =
        "glGetCommandHeaderNV";
};

struct GlGetStageIndexNV :
    ApiFunctionOgl<PFNGLGETSTAGEINDEXNVPROC>
{
    static constexpr std::string_view Name =
        "glGetStageIndexNV";
};

struct GlDrawCommandsNV :
    ApiFunctionOgl<PFNGLDRAWCOMMANDSNVPROC>
{
    static constexpr std::string_view Name =
        "glDrawCommandsNV";
};

struct GlDrawCommandsAddressNV :
    ApiFunctionOgl<PFNGLDRAWCOMMANDSADDRESSNVPROC>
{
    static constexpr std::string_view Name =
        "glDrawCommandsAddressNV";
};

struct GlDrawCommandsStatesNV :
    ApiFunctionOgl<PFNGLDRAWCOMMANDSSTATESNVPROC>
{
    static constexpr std::string_view Name =
        "glDrawCommandsStatesNV";
};

struct GlDrawCommandsStatesAddressNV :
    ApiFunctionOgl<PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC>
{
    static constexpr std::string_view Name =
        "glDrawCommandsStatesAddressNV";
};

struct GlCreateCommandListsNV :
    ApiFunctionOgl<PFNGLCREATECOMMANDLISTSNVPROC>
{
    static constexpr std::string_view Name =
        "glCreateCommandListsNV";
};

struct GlDeleteCommandListsNV :
    ApiFunctionOgl<PFNGLDELETECOMMANDLISTSNVPROC>
{
    static constexpr std::string_view Name =
        "glDeleteCommandListsNV";
};

struct GlIsCommandListNV :
    ApiFunctionOgl<PFNGLISCOMMANDLISTNVPROC>
{
    static constexpr std::string_view Name =
        "glIsCommandListNV";
};

struct GlListDrawCommandsStatesClientNV :
    ApiFunctionOgl<PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC>
{
    static constexpr std::string_view Name =
        "glListDrawCommandsStatesClientNV";
};

struct GlCommandListSegmentsNV :
    ApiFunctionOgl<PFNGLCOMMANDLISTSEGMENTSNVPROC>
{
    static constexpr std::string_view Name =
        "glCommandListSegmentsNV";
};

struct GlCompileCommandListNV :
    ApiFunctionOgl<PFNGLCOMPILECOMMANDLISTNVPROC>
{
    static constexpr std::string_view Name =
        "glCompileCommandListNV";
};

struct GlCallCommandListNV :
    ApiFunctionOgl<PFNGLCALLCOMMANDLISTNVPROC>
{
    static constexpr std::string_view Name =
        "glCallCommandListNV";
};

struct GlBeginConditionalRenderNV :
    ApiFunctionOgl<PFNGLBEGINCONDITIONALRENDERNVPROC>
{
    static constexpr std::string_view Name =
        "glBeginConditionalRenderNV";
};

struct GlEndConditionalRenderNV :
    ApiFunctionOgl<PFNGLENDCONDITIONALRENDERNVPROC>
{
    static constexpr std::string_view Name =
        "glEndConditionalRenderNV";
};

struct GlSubpixelPrecisionBiasNV :
    ApiFunctionOgl<PFNGLSUBPIXELPRECISIONBIASNVPROC>
{
    static constexpr std::string_view Name =
        "glSubpixelPrecisionBiasNV";
};

struct GlConservativeRasterParameterfNV :
    ApiFunctionOgl<PFNGLCONSERVATIVERASTERPARAMETERFNVPROC>
{
    static constexpr std::string_view Name =
        "glConservativeRasterParameterfNV";
};

struct GlConservativeRasterParameteriNV :
    ApiFunctionOgl<PFNGLCONSERVATIVERASTERPARAMETERINVPROC>
{
    static constexpr std::string_view Name =
        "glConservativeRasterParameteriNV";
};

struct GlDrawVkImageNV :
    ApiFunctionOgl<PFNGLDRAWVKIMAGENVPROC>
{
    static constexpr std::string_view Name =
        "glDrawVkImageNV";
};

struct GlGetVkProcAddrNV :
    ApiFunctionOgl<PFNGLGETVKPROCADDRNVPROC>
{
    static constexpr std::string_view Name =
        "glGetVkProcAddrNV";
};

struct GlWaitVkSemaphoreNV :
    ApiFunctionOgl<PFNGLWAITVKSEMAPHORENVPROC>
{
    static constexpr std::string_view Name =
        "glWaitVkSemaphoreNV";
};

struct GlSignalVkSemaphoreNV :
    ApiFunctionOgl<PFNGLSIGNALVKSEMAPHORENVPROC>
{
    static constexpr std::string_view Name =
        "glSignalVkSemaphoreNV";
};

struct GlSignalVkFenceNV :
    ApiFunctionOgl<PFNGLSIGNALVKFENCENVPROC>
{
    static constexpr std::string_view Name =
        "glSignalVkFenceNV";
};

struct GlFragmentCoverageColorNV :
    ApiFunctionOgl<PFNGLFRAGMENTCOVERAGECOLORNVPROC>
{
    static constexpr std::string_view Name =
        "glFragmentCoverageColorNV";
};

struct GlCoverageModulationTableNV :
    ApiFunctionOgl<PFNGLCOVERAGEMODULATIONTABLENVPROC>
{
    static constexpr std::string_view Name =
        "glCoverageModulationTableNV";
};

struct GlGetCoverageModulationTableNV :
    ApiFunctionOgl<PFNGLGETCOVERAGEMODULATIONTABLENVPROC>
{
    static constexpr std::string_view Name =
        "glGetCoverageModulationTableNV";
};

struct GlCoverageModulationNV :
    ApiFunctionOgl<PFNGLCOVERAGEMODULATIONNVPROC>
{
    static constexpr std::string_view Name =
        "glCoverageModulationNV";
};

struct GlRenderbufferStorageMultisampleCoverageNV :
    ApiFunctionOgl<PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC>
{
    static constexpr std::string_view Name =
        "glRenderbufferStorageMultisampleCoverageNV";
};

struct GlUniform1i64NV :
    ApiFunctionOgl<PFNGLUNIFORM1I64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1i64NV";
};

struct GlUniform2i64NV :
    ApiFunctionOgl<PFNGLUNIFORM2I64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2i64NV";
};

struct GlUniform3i64NV :
    ApiFunctionOgl<PFNGLUNIFORM3I64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3i64NV";
};

struct GlUniform4i64NV :
    ApiFunctionOgl<PFNGLUNIFORM4I64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4i64NV";
};

struct GlUniform1i64vNV :
    ApiFunctionOgl<PFNGLUNIFORM1I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1i64vNV";
};

struct GlUniform2i64vNV :
    ApiFunctionOgl<PFNGLUNIFORM2I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2i64vNV";
};

struct GlUniform3i64vNV :
    ApiFunctionOgl<PFNGLUNIFORM3I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3i64vNV";
};

struct GlUniform4i64vNV :
    ApiFunctionOgl<PFNGLUNIFORM4I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4i64vNV";
};

struct GlUniform1ui64NV :
    ApiFunctionOgl<PFNGLUNIFORM1UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1ui64NV";
};

struct GlUniform2ui64NV :
    ApiFunctionOgl<PFNGLUNIFORM2UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2ui64NV";
};

struct GlUniform3ui64NV :
    ApiFunctionOgl<PFNGLUNIFORM3UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3ui64NV";
};

struct GlUniform4ui64NV :
    ApiFunctionOgl<PFNGLUNIFORM4UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4ui64NV";
};

struct GlUniform1ui64vNV :
    ApiFunctionOgl<PFNGLUNIFORM1UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform1ui64vNV";
};

struct GlUniform2ui64vNV :
    ApiFunctionOgl<PFNGLUNIFORM2UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform2ui64vNV";
};

struct GlUniform3ui64vNV :
    ApiFunctionOgl<PFNGLUNIFORM3UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform3ui64vNV";
};

struct GlUniform4ui64vNV :
    ApiFunctionOgl<PFNGLUNIFORM4UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniform4ui64vNV";
};

struct GlGetUniformi64vNV :
    ApiFunctionOgl<PFNGLGETUNIFORMI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformi64vNV";
};

struct GlProgramUniform1i64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1I64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1i64NV";
};

struct GlProgramUniform2i64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2I64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2i64NV";
};

struct GlProgramUniform3i64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3I64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3i64NV";
};

struct GlProgramUniform4i64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4I64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4i64NV";
};

struct GlProgramUniform1i64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1i64vNV";
};

struct GlProgramUniform2i64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2i64vNV";
};

struct GlProgramUniform3i64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3i64vNV";
};

struct GlProgramUniform4i64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4i64vNV";
};

struct GlProgramUniform1ui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ui64NV";
};

struct GlProgramUniform2ui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ui64NV";
};

struct GlProgramUniform3ui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ui64NV";
};

struct GlProgramUniform4ui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ui64NV";
};

struct GlProgramUniform1ui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM1UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform1ui64vNV";
};

struct GlProgramUniform2ui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM2UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform2ui64vNV";
};

struct GlProgramUniform3ui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM3UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform3ui64vNV";
};

struct GlProgramUniform4ui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORM4UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniform4ui64vNV";
};

struct GlGetInternalformatSampleivNV :
    ApiFunctionOgl<PFNGLGETINTERNALFORMATSAMPLEIVNVPROC>
{
    static constexpr std::string_view Name =
        "glGetInternalformatSampleivNV";
};

struct GlGenPathsNV :
    ApiFunctionOgl<PFNGLGENPATHSNVPROC>
{
    static constexpr std::string_view Name =
        "glGenPathsNV";
};

struct GlDeletePathsNV :
    ApiFunctionOgl<PFNGLDELETEPATHSNVPROC>
{
    static constexpr std::string_view Name =
        "glDeletePathsNV";
};

struct GlIsPathNV :
    ApiFunctionOgl<PFNGLISPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glIsPathNV";
};

struct GlPathCommandsNV :
    ApiFunctionOgl<PFNGLPATHCOMMANDSNVPROC>
{
    static constexpr std::string_view Name =
        "glPathCommandsNV";
};

struct GlPathCoordsNV :
    ApiFunctionOgl<PFNGLPATHCOORDSNVPROC>
{
    static constexpr std::string_view Name =
        "glPathCoordsNV";
};

struct GlPathSubCommandsNV :
    ApiFunctionOgl<PFNGLPATHSUBCOMMANDSNVPROC>
{
    static constexpr std::string_view Name =
        "glPathSubCommandsNV";
};

struct GlPathSubCoordsNV :
    ApiFunctionOgl<PFNGLPATHSUBCOORDSNVPROC>
{
    static constexpr std::string_view Name =
        "glPathSubCoordsNV";
};

struct GlPathStringNV :
    ApiFunctionOgl<PFNGLPATHSTRINGNVPROC>
{
    static constexpr std::string_view Name =
        "glPathStringNV";
};

struct GlPathGlyphsNV :
    ApiFunctionOgl<PFNGLPATHGLYPHSNVPROC>
{
    static constexpr std::string_view Name =
        "glPathGlyphsNV";
};

struct GlPathGlyphRangeNV :
    ApiFunctionOgl<PFNGLPATHGLYPHRANGENVPROC>
{
    static constexpr std::string_view Name =
        "glPathGlyphRangeNV";
};

struct GlWeightPathsNV :
    ApiFunctionOgl<PFNGLWEIGHTPATHSNVPROC>
{
    static constexpr std::string_view Name =
        "glWeightPathsNV";
};

struct GlCopyPathNV :
    ApiFunctionOgl<PFNGLCOPYPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glCopyPathNV";
};

struct GlInterpolatePathsNV :
    ApiFunctionOgl<PFNGLINTERPOLATEPATHSNVPROC>
{
    static constexpr std::string_view Name =
        "glInterpolatePathsNV";
};

struct GlTransformPathNV :
    ApiFunctionOgl<PFNGLTRANSFORMPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glTransformPathNV";
};

struct GlPathParameterivNV :
    ApiFunctionOgl<PFNGLPATHPARAMETERIVNVPROC>
{
    static constexpr std::string_view Name =
        "glPathParameterivNV";
};

struct GlPathParameteriNV :
    ApiFunctionOgl<PFNGLPATHPARAMETERINVPROC>
{
    static constexpr std::string_view Name =
        "glPathParameteriNV";
};

struct GlPathParameterfvNV :
    ApiFunctionOgl<PFNGLPATHPARAMETERFVNVPROC>
{
    static constexpr std::string_view Name =
        "glPathParameterfvNV";
};

struct GlPathParameterfNV :
    ApiFunctionOgl<PFNGLPATHPARAMETERFNVPROC>
{
    static constexpr std::string_view Name =
        "glPathParameterfNV";
};

struct GlPathDashArrayNV :
    ApiFunctionOgl<PFNGLPATHDASHARRAYNVPROC>
{
    static constexpr std::string_view Name =
        "glPathDashArrayNV";
};

struct GlPathStencilFuncNV :
    ApiFunctionOgl<PFNGLPATHSTENCILFUNCNVPROC>
{
    static constexpr std::string_view Name =
        "glPathStencilFuncNV";
};

struct GlPathStencilDepthOffsetNV :
    ApiFunctionOgl<PFNGLPATHSTENCILDEPTHOFFSETNVPROC>
{
    static constexpr std::string_view Name =
        "glPathStencilDepthOffsetNV";
};

struct GlStencilFillPathNV :
    ApiFunctionOgl<PFNGLSTENCILFILLPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilFillPathNV";
};

struct GlStencilStrokePathNV :
    ApiFunctionOgl<PFNGLSTENCILSTROKEPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilStrokePathNV";
};

struct GlStencilFillPathInstancedNV :
    ApiFunctionOgl<PFNGLSTENCILFILLPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilFillPathInstancedNV";
};

struct GlStencilStrokePathInstancedNV :
    ApiFunctionOgl<PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilStrokePathInstancedNV";
};

struct GlPathCoverDepthFuncNV :
    ApiFunctionOgl<PFNGLPATHCOVERDEPTHFUNCNVPROC>
{
    static constexpr std::string_view Name =
        "glPathCoverDepthFuncNV";
};

struct GlCoverFillPathNV :
    ApiFunctionOgl<PFNGLCOVERFILLPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glCoverFillPathNV";
};

struct GlCoverStrokePathNV :
    ApiFunctionOgl<PFNGLCOVERSTROKEPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glCoverStrokePathNV";
};

struct GlCoverFillPathInstancedNV :
    ApiFunctionOgl<PFNGLCOVERFILLPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glCoverFillPathInstancedNV";
};

struct GlCoverStrokePathInstancedNV :
    ApiFunctionOgl<PFNGLCOVERSTROKEPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glCoverStrokePathInstancedNV";
};

struct GlGetPathParameterivNV :
    ApiFunctionOgl<PFNGLGETPATHPARAMETERIVNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathParameterivNV";
};

struct GlGetPathParameterfvNV :
    ApiFunctionOgl<PFNGLGETPATHPARAMETERFVNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathParameterfvNV";
};

struct GlGetPathCommandsNV :
    ApiFunctionOgl<PFNGLGETPATHCOMMANDSNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathCommandsNV";
};

struct GlGetPathCoordsNV :
    ApiFunctionOgl<PFNGLGETPATHCOORDSNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathCoordsNV";
};

struct GlGetPathDashArrayNV :
    ApiFunctionOgl<PFNGLGETPATHDASHARRAYNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathDashArrayNV";
};

struct GlGetPathMetricsNV :
    ApiFunctionOgl<PFNGLGETPATHMETRICSNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathMetricsNV";
};

struct GlGetPathMetricRangeNV :
    ApiFunctionOgl<PFNGLGETPATHMETRICRANGENVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathMetricRangeNV";
};

struct GlGetPathSpacingNV :
    ApiFunctionOgl<PFNGLGETPATHSPACINGNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathSpacingNV";
};

struct GlIsPointInFillPathNV :
    ApiFunctionOgl<PFNGLISPOINTINFILLPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glIsPointInFillPathNV";
};

struct GlIsPointInStrokePathNV :
    ApiFunctionOgl<PFNGLISPOINTINSTROKEPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glIsPointInStrokePathNV";
};

struct GlGetPathLengthNV :
    ApiFunctionOgl<PFNGLGETPATHLENGTHNVPROC>
{
    static constexpr std::string_view Name =
        "glGetPathLengthNV";
};

struct GlPointAlongPathNV :
    ApiFunctionOgl<PFNGLPOINTALONGPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glPointAlongPathNV";
};

struct GlMatrixLoad3x2fNV :
    ApiFunctionOgl<PFNGLMATRIXLOAD3X2FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoad3x2fNV";
};

struct GlMatrixLoad3x3fNV :
    ApiFunctionOgl<PFNGLMATRIXLOAD3X3FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoad3x3fNV";
};

struct GlMatrixLoadTranspose3x3fNV :
    ApiFunctionOgl<PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixLoadTranspose3x3fNV";
};

struct GlMatrixMult3x2fNV :
    ApiFunctionOgl<PFNGLMATRIXMULT3X2FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMult3x2fNV";
};

struct GlMatrixMult3x3fNV :
    ApiFunctionOgl<PFNGLMATRIXMULT3X3FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMult3x3fNV";
};

struct GlMatrixMultTranspose3x3fNV :
    ApiFunctionOgl<PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC>
{
    static constexpr std::string_view Name =
        "glMatrixMultTranspose3x3fNV";
};

struct GlStencilThenCoverFillPathNV :
    ApiFunctionOgl<PFNGLSTENCILTHENCOVERFILLPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilThenCoverFillPathNV";
};

struct GlStencilThenCoverStrokePathNV :
    ApiFunctionOgl<PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilThenCoverStrokePathNV";
};

struct GlStencilThenCoverFillPathInstancedNV :
    ApiFunctionOgl<PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilThenCoverFillPathInstancedNV";
};

struct GlStencilThenCoverStrokePathInstancedNV :
    ApiFunctionOgl<PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC>
{
    static constexpr std::string_view Name =
        "glStencilThenCoverStrokePathInstancedNV";
};

struct GlPathGlyphIndexRangeNV :
    ApiFunctionOgl<PFNGLPATHGLYPHINDEXRANGENVPROC>
{
    static constexpr std::string_view Name =
        "glPathGlyphIndexRangeNV";
};

struct GlPathGlyphIndexArrayNV :
    ApiFunctionOgl<PFNGLPATHGLYPHINDEXARRAYNVPROC>
{
    static constexpr std::string_view Name =
        "glPathGlyphIndexArrayNV";
};

struct GlPathMemoryGlyphIndexArrayNV :
    ApiFunctionOgl<PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC>
{
    static constexpr std::string_view Name =
        "glPathMemoryGlyphIndexArrayNV";
};

struct GlProgramPathFragmentInputGenNV :
    ApiFunctionOgl<PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramPathFragmentInputGenNV";
};

struct GlGetProgramResourcefvNV :
    ApiFunctionOgl<PFNGLGETPROGRAMRESOURCEFVNVPROC>
{
    static constexpr std::string_view Name =
        "glGetProgramResourcefvNV";
};

struct GlFramebufferSampleLocationsfvNV :
    ApiFunctionOgl<PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferSampleLocationsfvNV";
};

struct GlNamedFramebufferSampleLocationsfvNV :
    ApiFunctionOgl<PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC>
{
    static constexpr std::string_view Name =
        "glNamedFramebufferSampleLocationsfvNV";
};

struct GlResolveDepthValuesNV :
    ApiFunctionOgl<PFNGLRESOLVEDEPTHVALUESNVPROC>
{
    static constexpr std::string_view Name =
        "glResolveDepthValuesNV";
};

struct GlMakeBufferResidentNV :
    ApiFunctionOgl<PFNGLMAKEBUFFERRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeBufferResidentNV";
};

struct GlMakeBufferNonResidentNV :
    ApiFunctionOgl<PFNGLMAKEBUFFERNONRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeBufferNonResidentNV";
};

struct GlIsBufferResidentNV :
    ApiFunctionOgl<PFNGLISBUFFERRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glIsBufferResidentNV";
};

struct GlMakeNamedBufferResidentNV :
    ApiFunctionOgl<PFNGLMAKENAMEDBUFFERRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeNamedBufferResidentNV";
};

struct GlMakeNamedBufferNonResidentNV :
    ApiFunctionOgl<PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glMakeNamedBufferNonResidentNV";
};

struct GlIsNamedBufferResidentNV :
    ApiFunctionOgl<PFNGLISNAMEDBUFFERRESIDENTNVPROC>
{
    static constexpr std::string_view Name =
        "glIsNamedBufferResidentNV";
};

struct GlGetBufferParameterui64vNV :
    ApiFunctionOgl<PFNGLGETBUFFERPARAMETERUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetBufferParameterui64vNV";
};

struct GlGetNamedBufferParameterui64vNV :
    ApiFunctionOgl<PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetNamedBufferParameterui64vNV";
};

struct GlGetIntegerui64vNV :
    ApiFunctionOgl<PFNGLGETINTEGERUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetIntegerui64vNV";
};

struct GlUniformui64NV :
    ApiFunctionOgl<PFNGLUNIFORMUI64NVPROC>
{
    static constexpr std::string_view Name =
        "glUniformui64NV";
};

struct GlUniformui64vNV :
    ApiFunctionOgl<PFNGLUNIFORMUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glUniformui64vNV";
};

struct GlGetUniformui64vNV :
    ApiFunctionOgl<PFNGLGETUNIFORMUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetUniformui64vNV";
};

struct GlProgramUniformui64NV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMUI64NVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformui64NV";
};

struct GlProgramUniformui64vNV :
    ApiFunctionOgl<PFNGLPROGRAMUNIFORMUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glProgramUniformui64vNV";
};

struct GlTextureBarrierNV :
    ApiFunctionOgl<PFNGLTEXTUREBARRIERNVPROC>
{
    static constexpr std::string_view Name =
        "glTextureBarrierNV";
};

struct GlVertexAttribL1i64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1I64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1i64NV";
};

struct GlVertexAttribL2i64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2I64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2i64NV";
};

struct GlVertexAttribL3i64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3I64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3i64NV";
};

struct GlVertexAttribL4i64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4I64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4i64NV";
};

struct GlVertexAttribL1i64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1i64vNV";
};

struct GlVertexAttribL2i64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2i64vNV";
};

struct GlVertexAttribL3i64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3i64vNV";
};

struct GlVertexAttribL4i64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4I64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4i64vNV";
};

struct GlVertexAttribL1ui64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1ui64NV";
};

struct GlVertexAttribL2ui64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2ui64NV";
};

struct GlVertexAttribL3ui64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3ui64NV";
};

struct GlVertexAttribL4ui64NV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4UI64NVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4ui64NV";
};

struct GlVertexAttribL1ui64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL1UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL1ui64vNV";
};

struct GlVertexAttribL2ui64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL2UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL2ui64vNV";
};

struct GlVertexAttribL3ui64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL3UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL3ui64vNV";
};

struct GlVertexAttribL4ui64vNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBL4UI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribL4ui64vNV";
};

struct GlGetVertexAttribLi64vNV :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBLI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribLi64vNV";
};

struct GlGetVertexAttribLui64vNV :
    ApiFunctionOgl<PFNGLGETVERTEXATTRIBLUI64VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetVertexAttribLui64vNV";
};

struct GlVertexAttribLFormatNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBLFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribLFormatNV";
};

struct GlBufferAddressRangeNV :
    ApiFunctionOgl<PFNGLBUFFERADDRESSRANGENVPROC>
{
    static constexpr std::string_view Name =
        "glBufferAddressRangeNV";
};

struct GlVertexFormatNV :
    ApiFunctionOgl<PFNGLVERTEXFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexFormatNV";
};

struct GlNormalFormatNV :
    ApiFunctionOgl<PFNGLNORMALFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glNormalFormatNV";
};

struct GlColorFormatNV :
    ApiFunctionOgl<PFNGLCOLORFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glColorFormatNV";
};

struct GlIndexFormatNV :
    ApiFunctionOgl<PFNGLINDEXFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glIndexFormatNV";
};

struct GlTexCoordFormatNV :
    ApiFunctionOgl<PFNGLTEXCOORDFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glTexCoordFormatNV";
};

struct GlEdgeFlagFormatNV :
    ApiFunctionOgl<PFNGLEDGEFLAGFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glEdgeFlagFormatNV";
};

struct GlSecondaryColorFormatNV :
    ApiFunctionOgl<PFNGLSECONDARYCOLORFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glSecondaryColorFormatNV";
};

struct GlFogCoordFormatNV :
    ApiFunctionOgl<PFNGLFOGCOORDFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glFogCoordFormatNV";
};

struct GlVertexAttribFormatNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribFormatNV";
};

struct GlVertexAttribIFormatNV :
    ApiFunctionOgl<PFNGLVERTEXATTRIBIFORMATNVPROC>
{
    static constexpr std::string_view Name =
        "glVertexAttribIFormatNV";
};

struct GlGetIntegerui64i_vNV :
    ApiFunctionOgl<PFNGLGETINTEGERUI64I_VNVPROC>
{
    static constexpr std::string_view Name =
        "glGetIntegerui64i_vNV";
};

struct GlViewportSwizzleNV :
    ApiFunctionOgl<PFNGLVIEWPORTSWIZZLENVPROC>
{
    static constexpr std::string_view Name =
        "glViewportSwizzleNV";
};

struct GlFramebufferTextureMultiviewOVR :
    ApiFunctionOgl<PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC>
{
    static constexpr std::string_view Name =
        "glFramebufferTextureMultiviewOVR";
};

#ifdef _WIN32

struct WglGetExtensionsStringEXT :
    ApiFunctionOgl<PFNWGLGETEXTENSIONSSTRINGEXTPROC>
{
    static constexpr std::string_view Name =
        "wglGetExtensionsStringEXT";
};

struct WglGetExtensionsStringARB :
    ApiFunctionOgl<PFNWGLGETEXTENSIONSSTRINGARBPROC>
{
    static constexpr std::string_view Name =
        "wglGetExtensionsStringARB";
};

struct WglCreateContextAttribsARB :
    ApiFunctionOgl<PFNWGLCREATECONTEXTATTRIBSARBPROC>
{
    static constexpr std::string_view Name =
        "wglCreateContextAttribsARB";
};

struct WglSwapIntervalEXT :
    ApiFunctionOgl<PFNWGLSWAPINTERVALEXTPROC>
{
    static constexpr std::string_view Name =
        "wglSwapIntervalEXT";
};

#endif

#ifdef __linux__

struct GlXCreateContextAttribsARB :
    ApiFunctionOgl<PFNGLXCREATECONTEXTATTRIBSARBPROC>
{
    static constexpr std::string_view Name =
        "glXCreateContextAttribsARB";
};

struct GlXSwapIntervalEXT :
    ApiFunctionOgl<PFNGLXSWAPINTERVALEXTPROC>
{
    static constexpr std::string_view Name =
        "glXSwapIntervalEXT";
};

struct GlXSwapIntervalMESA :
    ApiFunctionOgl<PFNGLXSWAPINTERVALMESAPROC>
{
    static constexpr std::string_view Name =
        "glXSwapIntervalMESA";
};

#endif

}
