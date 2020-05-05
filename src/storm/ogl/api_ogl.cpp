#include <storm/ogl/api_ogl.h>

#include <string_view>
#include <unordered_map>

#include <storm/ogl/check_result_ogl.h>
#include <storm/ogl/texture_storage_ogl.h>

#ifdef _WIN32
// Unpacked from contrib/wglext-*.tar.gz
#include <GL/wglext.h>
#endif

#ifdef __linux__
// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>
#endif

namespace {

#ifdef _WIN32

using openGlFunction = PROC;

openGlFunction load( const char *functionName ) {
    static const HMODULE library = ::GetModuleHandle( L"opengl32.dll" );
    openGlFunction result = ::wglGetProcAddress( functionName );
    return result ? result : ::GetProcAddress( library, functionName );
}

#elif __linux__

using openGlFunction = void (*)();

openGlFunction load( const char *functionName ) {
    return ::glXGetProcAddress(
        reinterpret_cast<const unsigned char*>(functionName) );
}

#endif

void getSupportedExtensions(
    std::string_view extensions,
    const std::unordered_map<std::string_view, bool*> &extensionSupportFlags )
{
    while( !extensions.empty() ) {
        const std::string_view extension =
            extensions.substr( 0, extensions.find(" ") );

        if( const auto iterator = extensionSupportFlags.find(extension);
                iterator != extensionSupportFlags.end() ) {
            *(iterator->second) = true;
        }

        const bool hasSubsequentSpace =
            extension.size() != extensions.size();

        extensions = extensions.substr(
            extension.size() + (hasSubsequentSpace ? 1 : 0) );
    }
}

} // namespace

PFNGLCULLFACEPROC glCullFace = nullptr;
PFNGLFRONTFACEPROC glFrontFace = nullptr;
PFNGLHINTPROC glHint = nullptr;
PFNGLLINEWIDTHPROC glLineWidth = nullptr;
PFNGLPOINTSIZEPROC glPointSize = nullptr;
PFNGLPOLYGONMODEPROC glPolygonMode = nullptr;
PFNGLSCISSORPROC glScissor = nullptr;
PFNGLTEXPARAMETERFPROC glTexParameterf = nullptr;
PFNGLTEXPARAMETERFVPROC glTexParameterfv = nullptr;
PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;
PFNGLTEXPARAMETERIVPROC glTexParameteriv = nullptr;
PFNGLTEXIMAGE1DPROC glTexImage1D = nullptr;
PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
PFNGLDRAWBUFFERPROC glDrawBuffer = nullptr;
PFNGLCLEARPROC glClear = nullptr;
PFNGLCLEARCOLORPROC glClearColor = nullptr;
PFNGLCLEARSTENCILPROC glClearStencil = nullptr;
PFNGLCLEARDEPTHPROC glClearDepth = nullptr;
PFNGLSTENCILMASKPROC glStencilMask = nullptr;
PFNGLCOLORMASKPROC glColorMask = nullptr;
PFNGLDEPTHMASKPROC glDepthMask = nullptr;
PFNGLDISABLEPROC glDisable = nullptr;
PFNGLENABLEPROC glEnable = nullptr;
PFNGLFINISHPROC glFinish = nullptr;
PFNGLFLUSHPROC glFlush = nullptr;
PFNGLBLENDFUNCPROC glBlendFunc = nullptr;
PFNGLLOGICOPPROC glLogicOp = nullptr;
PFNGLSTENCILFUNCPROC glStencilFunc = nullptr;
PFNGLSTENCILOPPROC glStencilOp = nullptr;
PFNGLDEPTHFUNCPROC glDepthFunc = nullptr;
PFNGLPIXELSTOREFPROC glPixelStoref = nullptr;
PFNGLPIXELSTOREIPROC glPixelStorei = nullptr;
PFNGLREADBUFFERPROC glReadBuffer = nullptr;
PFNGLREADPIXELSPROC glReadPixels = nullptr;
PFNGLGETBOOLEANVPROC glGetBooleanv = nullptr;
PFNGLGETDOUBLEVPROC glGetDoublev = nullptr;
PFNGLGETERRORPROC glGetError = nullptr;
PFNGLGETFLOATVPROC glGetFloatv = nullptr;
PFNGLGETINTEGERVPROC glGetIntegerv = nullptr;
PFNGLGETSTRINGPROC glGetString = nullptr;
PFNGLGETTEXIMAGEPROC glGetTexImage = nullptr;
PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = nullptr;
PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = nullptr;
PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv = nullptr;
PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv = nullptr;
PFNGLISENABLEDPROC glIsEnabled = nullptr;
PFNGLDEPTHRANGEPROC glDepthRange = nullptr;
PFNGLVIEWPORTPROC glViewport = nullptr;
PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;
PFNGLGETPOINTERVPROC glGetPointerv = nullptr;
PFNGLPOLYGONOFFSETPROC glPolygonOffset = nullptr;
PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D = nullptr;
PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = nullptr;
PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D = nullptr;
PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = nullptr;
PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D = nullptr;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = nullptr;
PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
PFNGLGENTEXTURESPROC glGenTextures = nullptr;
PFNGLISTEXTUREPROC glIsTexture = nullptr;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = nullptr;
PFNGLTEXIMAGE3DPROC glTexImage3D = nullptr;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = nullptr;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = nullptr;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = nullptr;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = nullptr;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = nullptr;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = nullptr;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = nullptr;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = nullptr;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = nullptr;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = nullptr;
PFNGLPOINTPARAMETERFPROC glPointParameterf = nullptr;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = nullptr;
PFNGLPOINTPARAMETERIPROC glPointParameteri = nullptr;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = nullptr;
PFNGLBLENDCOLORPROC glBlendColor = nullptr;
PFNGLBLENDEQUATIONPROC glBlendEquation = nullptr;
PFNGLGENQUERIESPROC glGenQueries = nullptr;
PFNGLDELETEQUERIESPROC glDeleteQueries = nullptr;
PFNGLISQUERYPROC glIsQuery = nullptr;
PFNGLBEGINQUERYPROC glBeginQuery = nullptr;
PFNGLENDQUERYPROC glEndQuery = nullptr;
PFNGLGETQUERYIVPROC glGetQueryiv = nullptr;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = nullptr;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLISBUFFERPROC glIsBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = nullptr;
PFNGLMAPBUFFERPROC glMapBuffer = nullptr;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = nullptr;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = nullptr;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = nullptr;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = nullptr;
PFNGLDRAWBUFFERSPROC glDrawBuffers = nullptr;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = nullptr;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = nullptr;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = nullptr;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLGETUNIFORMFVPROC glGetUniformfv = nullptr;
PFNGLGETUNIFORMIVPROC glGetUniformiv = nullptr;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = nullptr;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = nullptr;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = nullptr;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;
PFNGLISPROGRAMPROC glIsProgram = nullptr;
PFNGLISSHADERPROC glIsShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM2FPROC glUniform2f = nullptr;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;
PFNGLUNIFORM4FPROC glUniform4f = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM2IPROC glUniform2i = nullptr;
PFNGLUNIFORM3IPROC glUniform3i = nullptr;
PFNGLUNIFORM4IPROC glUniform4i = nullptr;
PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;
PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;
PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = nullptr;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = nullptr;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = nullptr;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = nullptr;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = nullptr;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = nullptr;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = nullptr;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = nullptr;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = nullptr;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = nullptr;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = nullptr;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = nullptr;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = nullptr;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = nullptr;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = nullptr;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = nullptr;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = nullptr;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = nullptr;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = nullptr;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = nullptr;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = nullptr;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = nullptr;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = nullptr;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = nullptr;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = nullptr;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = nullptr;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = nullptr;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = nullptr;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = nullptr;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = nullptr;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = nullptr;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = nullptr;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = nullptr;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = nullptr;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = nullptr;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = nullptr;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = nullptr;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = nullptr;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = nullptr;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = nullptr;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = nullptr;
PFNGLCOLORMASKIPROC glColorMaski = nullptr;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = nullptr;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = nullptr;
PFNGLENABLEIPROC glEnablei = nullptr;
PFNGLDISABLEIPROC glDisablei = nullptr;
PFNGLISENABLEDIPROC glIsEnabledi = nullptr;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = nullptr;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = nullptr;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = nullptr;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = nullptr;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = nullptr;
PFNGLCLAMPCOLORPROC glClampColor = nullptr;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = nullptr;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = nullptr;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = nullptr;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = nullptr;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = nullptr;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = nullptr;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = nullptr;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = nullptr;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = nullptr;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = nullptr;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = nullptr;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = nullptr;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = nullptr;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = nullptr;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = nullptr;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = nullptr;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = nullptr;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = nullptr;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = nullptr;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = nullptr;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = nullptr;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = nullptr;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = nullptr;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = nullptr;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = nullptr;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = nullptr;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = nullptr;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = nullptr;
PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;
PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;
PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;
PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;
PFNGLUNIFORM1UIVPROC glUniform1uiv = nullptr;
PFNGLUNIFORM2UIVPROC glUniform2uiv = nullptr;
PFNGLUNIFORM3UIVPROC glUniform3uiv = nullptr;
PFNGLUNIFORM4UIVPROC glUniform4uiv = nullptr;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = nullptr;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = nullptr;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = nullptr;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = nullptr;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = nullptr;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = nullptr;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = nullptr;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = nullptr;
PFNGLGETSTRINGIPROC glGetStringi = nullptr;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = nullptr;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = nullptr;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = nullptr;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = nullptr;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = nullptr;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = nullptr;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = nullptr;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = nullptr;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = nullptr;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = nullptr;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = nullptr;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = nullptr;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLISVERTEXARRAYPROC glIsVertexArray = nullptr;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = nullptr;
PFNGLTEXBUFFERPROC glTexBuffer = nullptr;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = nullptr;
PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = nullptr;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = nullptr;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = nullptr;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = nullptr;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = nullptr;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = nullptr;
PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = nullptr;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex = nullptr;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex = nullptr;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex = nullptr;
PFNGLPROVOKINGVERTEXPROC glProvokingVertex = nullptr;
PFNGLFENCESYNCPROC glFenceSync = nullptr;
PFNGLISSYNCPROC glIsSync = nullptr;
PFNGLDELETESYNCPROC glDeleteSync = nullptr;
PFNGLCLIENTWAITSYNCPROC glClientWaitSync = nullptr;
PFNGLWAITSYNCPROC glWaitSync = nullptr;
PFNGLGETINTEGER64VPROC glGetInteger64v = nullptr;
PFNGLGETSYNCIVPROC glGetSynciv = nullptr;
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = nullptr;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = nullptr;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = nullptr;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample = nullptr;
PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample = nullptr;
PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv = nullptr;
PFNGLSAMPLEMASKIPROC glSampleMaski = nullptr;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed = nullptr;
PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex = nullptr;
PFNGLGENSAMPLERSPROC glGenSamplers = nullptr;
PFNGLDELETESAMPLERSPROC glDeleteSamplers = nullptr;
PFNGLISSAMPLERPROC glIsSampler = nullptr;
PFNGLBINDSAMPLERPROC glBindSampler = nullptr;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = nullptr;
PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = nullptr;
PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = nullptr;
PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = nullptr;
PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = nullptr;
PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = nullptr;
PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = nullptr;
PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = nullptr;
PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = nullptr;
PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv = nullptr;
PFNGLQUERYCOUNTERPROC glQueryCounter = nullptr;
PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = nullptr;
PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = nullptr;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = nullptr;
PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui = nullptr;
PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv = nullptr;
PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui = nullptr;
PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv = nullptr;
PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui = nullptr;
PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv = nullptr;
PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui = nullptr;
PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv = nullptr;
PFNGLMINSAMPLESHADINGPROC glMinSampleShading = nullptr;
PFNGLBLENDEQUATIONIPROC glBlendEquationi = nullptr;
PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei = nullptr;
PFNGLBLENDFUNCIPROC glBlendFunci = nullptr;
PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei = nullptr;
PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect = nullptr;
PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect = nullptr;
PFNGLUNIFORM1DPROC glUniform1d = nullptr;
PFNGLUNIFORM2DPROC glUniform2d = nullptr;
PFNGLUNIFORM3DPROC glUniform3d = nullptr;
PFNGLUNIFORM4DPROC glUniform4d = nullptr;
PFNGLUNIFORM1DVPROC glUniform1dv = nullptr;
PFNGLUNIFORM2DVPROC glUniform2dv = nullptr;
PFNGLUNIFORM3DVPROC glUniform3dv = nullptr;
PFNGLUNIFORM4DVPROC glUniform4dv = nullptr;
PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv = nullptr;
PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv = nullptr;
PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv = nullptr;
PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv = nullptr;
PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv = nullptr;
PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv = nullptr;
PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv = nullptr;
PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv = nullptr;
PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv = nullptr;
PFNGLGETUNIFORMDVPROC glGetUniformdv = nullptr;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation = nullptr;
PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex = nullptr;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv = nullptr;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName = nullptr;
PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName = nullptr;
PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv = nullptr;
PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv = nullptr;
PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = nullptr;
PFNGLPATCHPARAMETERIPROC glPatchParameteri = nullptr;
PFNGLPATCHPARAMETERFVPROC glPatchParameterfv = nullptr;
PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = nullptr;
PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = nullptr;
PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = nullptr;
PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = nullptr;
PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = nullptr;
PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = nullptr;
PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback = nullptr;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream = nullptr;
PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed = nullptr;
PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed = nullptr;
PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv = nullptr;
PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = nullptr;
PFNGLSHADERBINARYPROC glShaderBinary = nullptr;
PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = nullptr;
PFNGLDEPTHRANGEFPROC glDepthRangef = nullptr;
PFNGLCLEARDEPTHFPROC glClearDepthf = nullptr;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = nullptr;
PFNGLPROGRAMBINARYPROC glProgramBinary = nullptr;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = nullptr;
PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = nullptr;
PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram = nullptr;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = nullptr;
PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline = nullptr;
PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines = nullptr;
PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines = nullptr;
PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline = nullptr;
PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv = nullptr;
PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = nullptr;
PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = nullptr;
PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = nullptr;
PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = nullptr;
PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = nullptr;
PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = nullptr;
PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = nullptr;
PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = nullptr;
PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = nullptr;
PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = nullptr;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = nullptr;
PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = nullptr;
PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = nullptr;
PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = nullptr;
PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = nullptr;
PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = nullptr;
PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = nullptr;
PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = nullptr;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = nullptr;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = nullptr;
PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = nullptr;
PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = nullptr;
PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = nullptr;
PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = nullptr;
PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = nullptr;
PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = nullptr;
PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = nullptr;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = nullptr;
PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = nullptr;
PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = nullptr;
PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = nullptr;
PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = nullptr;
PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline = nullptr;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog = nullptr;
PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d = nullptr;
PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d = nullptr;
PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d = nullptr;
PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d = nullptr;
PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv = nullptr;
PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv = nullptr;
PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv = nullptr;
PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv = nullptr;
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = nullptr;
PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv = nullptr;
PFNGLVIEWPORTARRAYVPROC glViewportArrayv = nullptr;
PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf = nullptr;
PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv = nullptr;
PFNGLSCISSORARRAYVPROC glScissorArrayv = nullptr;
PFNGLSCISSORINDEXEDPROC glScissorIndexed = nullptr;
PFNGLSCISSORINDEXEDVPROC glScissorIndexedv = nullptr;
PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv = nullptr;
PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed = nullptr;
PFNGLGETFLOATI_VPROC glGetFloati_v = nullptr;
PFNGLGETDOUBLEI_VPROC glGetDoublei_v = nullptr;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance = nullptr;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance = nullptr;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance = nullptr;
PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = nullptr;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv = nullptr;
PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = nullptr;
PFNGLMEMORYBARRIERPROC glMemoryBarrier = nullptr;
PFNGLTEXSTORAGE1DPROC glTexStorage1D = nullptr;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = nullptr;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = nullptr;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced = nullptr;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced = nullptr;
PFNGLCLEARBUFFERDATAPROC glClearBufferData = nullptr;
PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData = nullptr;
PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = nullptr;
PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect = nullptr;
PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData = nullptr;
PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri = nullptr;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv = nullptr;
PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v = nullptr;
PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage = nullptr;
PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage = nullptr;
PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData = nullptr;
PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData = nullptr;
PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = nullptr;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = nullptr;
PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect = nullptr;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect = nullptr;
PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = nullptr;
PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex = nullptr;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = nullptr;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = nullptr;
PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation = nullptr;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex = nullptr;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding = nullptr;
PFNGLTEXBUFFERRANGEPROC glTexBufferRange = nullptr;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample = nullptr;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample = nullptr;
PFNGLTEXTUREVIEWPROC glTextureView = nullptr;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = nullptr;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat = nullptr;
PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat = nullptr;
PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat = nullptr;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding = nullptr;
PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor = nullptr;
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = nullptr;
PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert = nullptr;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog = nullptr;
PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup = nullptr;
PFNGLPOPDEBUGGROUPPROC glPopDebugGroup = nullptr;
PFNGLOBJECTLABELPROC glObjectLabel = nullptr;
PFNGLGETOBJECTLABELPROC glGetObjectLabel = nullptr;
PFNGLOBJECTPTRLABELPROC glObjectPtrLabel = nullptr;
PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel = nullptr;
PFNGLBUFFERSTORAGEPROC glBufferStorage = nullptr;
PFNGLCLEARTEXIMAGEPROC glClearTexImage = nullptr;
PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage = nullptr;
PFNGLBINDBUFFERSBASEPROC glBindBuffersBase = nullptr;
PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange = nullptr;
PFNGLBINDTEXTURESPROC glBindTextures = nullptr;
PFNGLBINDSAMPLERSPROC glBindSamplers = nullptr;
PFNGLBINDIMAGETEXTURESPROC glBindImageTextures = nullptr;
PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers = nullptr;
PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB = nullptr;
PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB = nullptr;
PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB = nullptr;
PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB = nullptr;
PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB = nullptr;
PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB = nullptr;
PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB = nullptr;
PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB = nullptr;
PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB = nullptr;
PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB = nullptr;
PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB = nullptr;
PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB = nullptr;
PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB = nullptr;
PFNGLVERTEXATTRIBL1UI64ARBPROC glVertexAttribL1ui64ARB = nullptr;
PFNGLVERTEXATTRIBL1UI64VARBPROC glVertexAttribL1ui64vARB = nullptr;
PFNGLGETVERTEXATTRIBLUI64VARBPROC glGetVertexAttribLui64vARB = nullptr;
PFNGLCREATESYNCFROMCLEVENTARBPROC glCreateSyncFromCLeventARB = nullptr;
PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC glDispatchComputeGroupSizeARB = nullptr;
PFNGLDEBUGMESSAGECONTROLARBPROC glDebugMessageControlARB = nullptr;
PFNGLDEBUGMESSAGEINSERTARBPROC glDebugMessageInsertARB = nullptr;
PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = nullptr;
PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageLogARB = nullptr;
PFNGLBLENDEQUATIONIARBPROC glBlendEquationiARB = nullptr;
PFNGLBLENDEQUATIONSEPARATEIARBPROC glBlendEquationSeparateiARB = nullptr;
PFNGLBLENDFUNCIARBPROC glBlendFunciARB = nullptr;
PFNGLBLENDFUNCSEPARATEIARBPROC glBlendFuncSeparateiARB = nullptr;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB = nullptr;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB = nullptr;
PFNGLGETGRAPHICSRESETSTATUSARBPROC glGetGraphicsResetStatusARB = nullptr;
PFNGLGETNTEXIMAGEARBPROC glGetnTexImageARB = nullptr;
PFNGLREADNPIXELSARBPROC glReadnPixelsARB = nullptr;
PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC glGetnCompressedTexImageARB = nullptr;
PFNGLGETNUNIFORMFVARBPROC glGetnUniformfvARB = nullptr;
PFNGLGETNUNIFORMIVARBPROC glGetnUniformivARB = nullptr;
PFNGLGETNUNIFORMUIVARBPROC glGetnUniformuivARB = nullptr;
PFNGLGETNUNIFORMDVARBPROC glGetnUniformdvARB = nullptr;
PFNGLMINSAMPLESHADINGARBPROC glMinSampleShadingARB = nullptr;
PFNGLNAMEDSTRINGARBPROC glNamedStringARB = nullptr;
PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB = nullptr;
PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB = nullptr;
PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB = nullptr;
PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB = nullptr;
PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB = nullptr;
PFNGLTEXPAGECOMMITMENTARBPROC glTexPageCommitmentARB = nullptr;

namespace storm {

void loadOpenGlApi() {
    ::glCullFace = reinterpret_cast<PFNGLCULLFACEPROC>( load("glCullFace") );
    ::glFrontFace = reinterpret_cast<PFNGLFRONTFACEPROC>( load("glFrontFace") );
    ::glHint = reinterpret_cast<PFNGLHINTPROC>( load("glHint") );
    ::glLineWidth = reinterpret_cast<PFNGLLINEWIDTHPROC>( load("glLineWidth") );
    ::glPointSize = reinterpret_cast<PFNGLPOINTSIZEPROC>( load("glPointSize") );
    ::glPolygonMode = reinterpret_cast<PFNGLPOLYGONMODEPROC>( load("glPolygonMode") );
    ::glScissor = reinterpret_cast<PFNGLSCISSORPROC>( load("glScissor") );
    ::glTexParameterf = reinterpret_cast<PFNGLTEXPARAMETERFPROC>( load("glTexParameterf") );
    ::glTexParameterfv = reinterpret_cast<PFNGLTEXPARAMETERFVPROC>( load("glTexParameterfv") );
    ::glTexParameteri = reinterpret_cast<PFNGLTEXPARAMETERIPROC>( load("glTexParameteri") );
    ::glTexParameteriv = reinterpret_cast<PFNGLTEXPARAMETERIVPROC>( load("glTexParameteriv") );
    ::glTexImage1D = reinterpret_cast<PFNGLTEXIMAGE1DPROC>( load("glTexImage1D") );
    ::glTexImage2D = reinterpret_cast<PFNGLTEXIMAGE2DPROC>( load("glTexImage2D") );
    ::glDrawBuffer = reinterpret_cast<PFNGLDRAWBUFFERPROC>( load("glDrawBuffer") );
    ::glClear = reinterpret_cast<PFNGLCLEARPROC>( load("glClear") );
    ::glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>( load("glClearColor") );
    ::glClearStencil = reinterpret_cast<PFNGLCLEARSTENCILPROC>( load("glClearStencil") );
    ::glClearDepth = reinterpret_cast<PFNGLCLEARDEPTHPROC>( load("glClearDepth") );
    ::glStencilMask = reinterpret_cast<PFNGLSTENCILMASKPROC>( load("glStencilMask") );
    ::glColorMask = reinterpret_cast<PFNGLCOLORMASKPROC>( load("glColorMask") );
    ::glDepthMask = reinterpret_cast<PFNGLDEPTHMASKPROC>( load("glDepthMask") );
    ::glDisable = reinterpret_cast<PFNGLDISABLEPROC>( load("glDisable") );
    ::glEnable = reinterpret_cast<PFNGLENABLEPROC>( load("glEnable") );
    ::glFinish = reinterpret_cast<PFNGLFINISHPROC>( load("glFinish") );
    ::glFlush = reinterpret_cast<PFNGLFLUSHPROC>( load("glFlush") );
    ::glBlendFunc = reinterpret_cast<PFNGLBLENDFUNCPROC>( load("glBlendFunc") );
    ::glLogicOp = reinterpret_cast<PFNGLLOGICOPPROC>( load("glLogicOp") );
    ::glStencilFunc = reinterpret_cast<PFNGLSTENCILFUNCPROC>( load("glStencilFunc") );
    ::glStencilOp = reinterpret_cast<PFNGLSTENCILOPPROC>( load("glStencilOp") );
    ::glDepthFunc = reinterpret_cast<PFNGLDEPTHFUNCPROC>( load("glDepthFunc") );
    ::glPixelStoref = reinterpret_cast<PFNGLPIXELSTOREFPROC>( load("glPixelStoref") );
    ::glPixelStorei = reinterpret_cast<PFNGLPIXELSTOREIPROC>( load("glPixelStorei") );
    ::glReadBuffer = reinterpret_cast<PFNGLREADBUFFERPROC>( load("glReadBuffer") );
    ::glReadPixels = reinterpret_cast<PFNGLREADPIXELSPROC>( load("glReadPixels") );
    ::glGetBooleanv = reinterpret_cast<PFNGLGETBOOLEANVPROC>( load("glGetBooleanv") );
    ::glGetDoublev = reinterpret_cast<PFNGLGETDOUBLEVPROC>( load("glGetDoublev") );
    ::glGetError = reinterpret_cast<PFNGLGETERRORPROC>( load("glGetError") );
    ::glGetFloatv = reinterpret_cast<PFNGLGETFLOATVPROC>( load("glGetFloatv") );
    ::glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>( load("glGetIntegerv") );
    ::glGetString = reinterpret_cast<PFNGLGETSTRINGPROC>( load("glGetString") );
    ::glGetTexImage = reinterpret_cast<PFNGLGETTEXIMAGEPROC>( load("glGetTexImage") );
    ::glGetTexParameterfv = reinterpret_cast<PFNGLGETTEXPARAMETERFVPROC>( load("glGetTexParameterfv") );
    ::glGetTexParameteriv = reinterpret_cast<PFNGLGETTEXPARAMETERIVPROC>( load("glGetTexParameteriv") );
    ::glGetTexLevelParameterfv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERFVPROC>( load("glGetTexLevelParameterfv") );
    ::glGetTexLevelParameteriv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>( load("glGetTexLevelParameteriv") );
    ::glIsEnabled = reinterpret_cast<PFNGLISENABLEDPROC>( load("glIsEnabled") );
    ::glDepthRange = reinterpret_cast<PFNGLDEPTHRANGEPROC>( load("glDepthRange") );
    ::glViewport = reinterpret_cast<PFNGLVIEWPORTPROC>( load("glViewport") );
    ::glDrawArrays = reinterpret_cast<PFNGLDRAWARRAYSPROC>( load("glDrawArrays") );
    ::glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>( load("glDrawElements") );
    ::glGetPointerv = reinterpret_cast<PFNGLGETPOINTERVPROC>( load("glGetPointerv") );
    ::glPolygonOffset = reinterpret_cast<PFNGLPOLYGONOFFSETPROC>( load("glPolygonOffset") );
    ::glCopyTexImage1D = reinterpret_cast<PFNGLCOPYTEXIMAGE1DPROC>( load("glCopyTexImage1D") );
    ::glCopyTexImage2D = reinterpret_cast<PFNGLCOPYTEXIMAGE2DPROC>( load("glCopyTexImage2D") );
    ::glCopyTexSubImage1D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>( load("glCopyTexSubImage1D") );
    ::glCopyTexSubImage2D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE2DPROC>( load("glCopyTexSubImage2D") );
    ::glTexSubImage1D = reinterpret_cast<PFNGLTEXSUBIMAGE1DPROC>( load("glTexSubImage1D") );
    ::glTexSubImage2D = reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>( load("glTexSubImage2D") );
    ::glBindTexture = reinterpret_cast<PFNGLBINDTEXTUREPROC>( load("glBindTexture") );
    ::glDeleteTextures = reinterpret_cast<PFNGLDELETETEXTURESPROC>( load("glDeleteTextures") );
    ::glGenTextures = reinterpret_cast<PFNGLGENTEXTURESPROC>( load("glGenTextures") );
    ::glIsTexture = reinterpret_cast<PFNGLISTEXTUREPROC>( load("glIsTexture") );
    ::glDrawRangeElements = reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>( load("glDrawRangeElements") );
    ::glTexImage3D = reinterpret_cast<PFNGLTEXIMAGE3DPROC>( load("glTexImage3D") );
    ::glTexSubImage3D = reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>( load("glTexSubImage3D") );
    ::glCopyTexSubImage3D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>( load("glCopyTexSubImage3D") );
    ::glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>( load("glActiveTexture") );
    ::glSampleCoverage = reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>( load("glSampleCoverage") );
    ::glCompressedTexImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>( load("glCompressedTexImage3D") );
    ::glCompressedTexImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>( load("glCompressedTexImage2D") );
    ::glCompressedTexImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>( load("glCompressedTexImage1D") );
    ::glCompressedTexSubImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>( load("glCompressedTexSubImage3D") );
    ::glCompressedTexSubImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>( load("glCompressedTexSubImage2D") );
    ::glCompressedTexSubImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>( load("glCompressedTexSubImage1D") );
    ::glGetCompressedTexImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>( load("glGetCompressedTexImage") );
    ::glBlendFuncSeparate = reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>( load("glBlendFuncSeparate") );
    ::glMultiDrawArrays = reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>( load("glMultiDrawArrays") );
    ::glMultiDrawElements = reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>( load("glMultiDrawElements") );
    ::glPointParameterf = reinterpret_cast<PFNGLPOINTPARAMETERFPROC>( load("glPointParameterf") );
    ::glPointParameterfv = reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>( load("glPointParameterfv") );
    ::glPointParameteri = reinterpret_cast<PFNGLPOINTPARAMETERIPROC>( load("glPointParameteri") );
    ::glPointParameteriv = reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>( load("glPointParameteriv") );
    ::glBlendColor = reinterpret_cast<PFNGLBLENDCOLORPROC>( load("glBlendColor") );
    ::glBlendEquation = reinterpret_cast<PFNGLBLENDEQUATIONPROC>( load("glBlendEquation") );
    ::glGenQueries = reinterpret_cast<PFNGLGENQUERIESPROC>( load("glGenQueries") );
    ::glDeleteQueries = reinterpret_cast<PFNGLDELETEQUERIESPROC>( load("glDeleteQueries") );
    ::glIsQuery = reinterpret_cast<PFNGLISQUERYPROC>( load("glIsQuery") );
    ::glBeginQuery = reinterpret_cast<PFNGLBEGINQUERYPROC>( load("glBeginQuery") );
    ::glEndQuery = reinterpret_cast<PFNGLENDQUERYPROC>( load("glEndQuery") );
    ::glGetQueryiv = reinterpret_cast<PFNGLGETQUERYIVPROC>( load("glGetQueryiv") );
    ::glGetQueryObjectiv = reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>( load("glGetQueryObjectiv") );
    ::glGetQueryObjectuiv = reinterpret_cast<PFNGLGETQUERYOBJECTUIVPROC>( load("glGetQueryObjectuiv") );
    ::glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>( load("glBindBuffer") );
    ::glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>( load("glDeleteBuffers") );
    ::glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>( load("glGenBuffers") );
    ::glIsBuffer = reinterpret_cast<PFNGLISBUFFERPROC>( load("glIsBuffer") );
    ::glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>( load("glBufferData") );
    ::glBufferSubData = reinterpret_cast<PFNGLBUFFERSUBDATAPROC>( load("glBufferSubData") );
    ::glGetBufferSubData = reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>( load("glGetBufferSubData") );
    ::glMapBuffer = reinterpret_cast<PFNGLMAPBUFFERPROC>( load("glMapBuffer") );
    ::glUnmapBuffer = reinterpret_cast<PFNGLUNMAPBUFFERPROC>( load("glUnmapBuffer") );
    ::glGetBufferParameteriv = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVPROC>( load("glGetBufferParameteriv") );
    ::glGetBufferPointerv = reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>( load("glGetBufferPointerv") );
    ::glBlendEquationSeparate = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>( load("glBlendEquationSeparate") );
    ::glDrawBuffers = reinterpret_cast<PFNGLDRAWBUFFERSPROC>( load("glDrawBuffers") );
    ::glStencilOpSeparate = reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>( load("glStencilOpSeparate") );
    ::glStencilFuncSeparate = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>( load("glStencilFuncSeparate") );
    ::glStencilMaskSeparate = reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>( load("glStencilMaskSeparate") );
    ::glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>( load("glAttachShader") );
    ::glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>( load("glBindAttribLocation") );
    ::glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>( load("glCompileShader") );
    ::glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>( load("glCreateProgram") );
    ::glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>( load("glCreateShader") );
    ::glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>( load("glDeleteProgram") );
    ::glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>( load("glDeleteShader") );
    ::glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>( load("glDetachShader") );
    ::glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>( load("glDisableVertexAttribArray") );
    ::glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>( load("glEnableVertexAttribArray") );
    ::glGetActiveAttrib = reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>( load("glGetActiveAttrib") );
    ::glGetActiveUniform = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>( load("glGetActiveUniform") );
    ::glGetAttachedShaders = reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>( load("glGetAttachedShaders") );
    ::glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>( load("glGetAttribLocation") );
    ::glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>( load("glGetProgramiv") );
    ::glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>( load("glGetProgramInfoLog") );
    ::glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>( load("glGetShaderiv") );
    ::glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>( load("glGetShaderInfoLog") );
    ::glGetShaderSource = reinterpret_cast<PFNGLGETSHADERSOURCEPROC>( load("glGetShaderSource") );
    ::glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>( load("glGetUniformLocation") );
    ::glGetUniformfv = reinterpret_cast<PFNGLGETUNIFORMFVPROC>( load("glGetUniformfv") );
    ::glGetUniformiv = reinterpret_cast<PFNGLGETUNIFORMIVPROC>( load("glGetUniformiv") );
    ::glGetVertexAttribdv = reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>( load("glGetVertexAttribdv") );
    ::glGetVertexAttribfv = reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>( load("glGetVertexAttribfv") );
    ::glGetVertexAttribiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIVPROC>( load("glGetVertexAttribiv") );
    ::glGetVertexAttribPointerv = reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>( load("glGetVertexAttribPointerv") );
    ::glIsProgram = reinterpret_cast<PFNGLISPROGRAMPROC>( load("glIsProgram") );
    ::glIsShader = reinterpret_cast<PFNGLISSHADERPROC>( load("glIsShader") );
    ::glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>( load("glLinkProgram") );
    ::glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>( load("glShaderSource") );
    ::glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>( load("glUseProgram") );
    ::glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>( load("glUniform1f") );
    ::glUniform2f = reinterpret_cast<PFNGLUNIFORM2FPROC>( load("glUniform2f") );
    ::glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>( load("glUniform3f") );
    ::glUniform4f = reinterpret_cast<PFNGLUNIFORM4FPROC>( load("glUniform4f") );
    ::glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>( load("glUniform1i") );
    ::glUniform2i = reinterpret_cast<PFNGLUNIFORM2IPROC>( load("glUniform2i") );
    ::glUniform3i = reinterpret_cast<PFNGLUNIFORM3IPROC>( load("glUniform3i") );
    ::glUniform4i = reinterpret_cast<PFNGLUNIFORM4IPROC>( load("glUniform4i") );
    ::glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>( load("glUniform1fv") );
    ::glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FVPROC>( load("glUniform2fv") );
    ::glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>( load("glUniform3fv") );
    ::glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>( load("glUniform4fv") );
    ::glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IVPROC>( load("glUniform1iv") );
    ::glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IVPROC>( load("glUniform2iv") );
    ::glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IVPROC>( load("glUniform3iv") );
    ::glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IVPROC>( load("glUniform4iv") );
    ::glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>( load("glUniformMatrix2fv") );
    ::glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>( load("glUniformMatrix3fv") );
    ::glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>( load("glUniformMatrix4fv") );
    ::glValidateProgram = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>( load("glValidateProgram") );
    ::glVertexAttrib1d = reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>( load("glVertexAttrib1d") );
    ::glVertexAttrib1dv = reinterpret_cast<PFNGLVERTEXATTRIB1DVPROC>( load("glVertexAttrib1dv") );
    ::glVertexAttrib1f = reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>( load("glVertexAttrib1f") );
    ::glVertexAttrib1fv = reinterpret_cast<PFNGLVERTEXATTRIB1FVPROC>( load("glVertexAttrib1fv") );
    ::glVertexAttrib1s = reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>( load("glVertexAttrib1s") );
    ::glVertexAttrib1sv = reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>( load("glVertexAttrib1sv") );
    ::glVertexAttrib2d = reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>( load("glVertexAttrib2d") );
    ::glVertexAttrib2dv = reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>( load("glVertexAttrib2dv") );
    ::glVertexAttrib2f = reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>( load("glVertexAttrib2f") );
    ::glVertexAttrib2fv = reinterpret_cast<PFNGLVERTEXATTRIB2FVPROC>( load("glVertexAttrib2fv") );
    ::glVertexAttrib2s = reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>( load("glVertexAttrib2s") );
    ::glVertexAttrib2sv = reinterpret_cast<PFNGLVERTEXATTRIB2SVPROC>( load("glVertexAttrib2sv") );
    ::glVertexAttrib3d = reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>( load("glVertexAttrib3d") );
    ::glVertexAttrib3dv = reinterpret_cast<PFNGLVERTEXATTRIB3DVPROC>( load("glVertexAttrib3dv") );
    ::glVertexAttrib3f = reinterpret_cast<PFNGLVERTEXATTRIB3FPROC>( load("glVertexAttrib3f") );
    ::glVertexAttrib3fv = reinterpret_cast<PFNGLVERTEXATTRIB3FVPROC>( load("glVertexAttrib3fv") );
    ::glVertexAttrib3s = reinterpret_cast<PFNGLVERTEXATTRIB3SPROC>( load("glVertexAttrib3s") );
    ::glVertexAttrib3sv = reinterpret_cast<PFNGLVERTEXATTRIB3SVPROC>( load("glVertexAttrib3sv") );
    ::glVertexAttrib4Nbv = reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>( load("glVertexAttrib4Nbv") );
    ::glVertexAttrib4Niv = reinterpret_cast<PFNGLVERTEXATTRIB4NIVPROC>( load("glVertexAttrib4Niv") );
    ::glVertexAttrib4Nsv = reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>( load("glVertexAttrib4Nsv") );
    ::glVertexAttrib4Nub = reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>( load("glVertexAttrib4Nub") );
    ::glVertexAttrib4Nubv = reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>( load("glVertexAttrib4Nubv") );
    ::glVertexAttrib4Nuiv = reinterpret_cast<PFNGLVERTEXATTRIB4NUIVPROC>( load("glVertexAttrib4Nuiv") );
    ::glVertexAttrib4Nusv = reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>( load("glVertexAttrib4Nusv") );
    ::glVertexAttrib4bv = reinterpret_cast<PFNGLVERTEXATTRIB4BVPROC>( load("glVertexAttrib4bv") );
    ::glVertexAttrib4d = reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>( load("glVertexAttrib4d") );
    ::glVertexAttrib4dv = reinterpret_cast<PFNGLVERTEXATTRIB4DVPROC>( load("glVertexAttrib4dv") );
    ::glVertexAttrib4f = reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>( load("glVertexAttrib4f") );
    ::glVertexAttrib4fv = reinterpret_cast<PFNGLVERTEXATTRIB4FVPROC>( load("glVertexAttrib4fv") );
    ::glVertexAttrib4iv = reinterpret_cast<PFNGLVERTEXATTRIB4IVPROC>( load("glVertexAttrib4iv") );
    ::glVertexAttrib4s = reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>( load("glVertexAttrib4s") );
    ::glVertexAttrib4sv = reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>( load("glVertexAttrib4sv") );
    ::glVertexAttrib4ubv = reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>( load("glVertexAttrib4ubv") );
    ::glVertexAttrib4uiv = reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>( load("glVertexAttrib4uiv") );
    ::glVertexAttrib4usv = reinterpret_cast<PFNGLVERTEXATTRIB4USVPROC>( load("glVertexAttrib4usv") );
    ::glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>( load("glVertexAttribPointer") );
    ::glUniformMatrix2x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FVPROC>( load("glUniformMatrix2x3fv") );
    ::glUniformMatrix3x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>( load("glUniformMatrix3x2fv") );
    ::glUniformMatrix2x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FVPROC>( load("glUniformMatrix2x4fv") );
    ::glUniformMatrix4x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FVPROC>( load("glUniformMatrix4x2fv") );
    ::glUniformMatrix3x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>( load("glUniformMatrix3x4fv") );
    ::glUniformMatrix4x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FVPROC>( load("glUniformMatrix4x3fv") );
    ::glColorMaski = reinterpret_cast<PFNGLCOLORMASKIPROC>( load("glColorMaski") );
    ::glGetBooleani_v = reinterpret_cast<PFNGLGETBOOLEANI_VPROC>( load("glGetBooleani_v") );
    ::glGetIntegeri_v = reinterpret_cast<PFNGLGETINTEGERI_VPROC>( load("glGetIntegeri_v") );
    ::glEnablei = reinterpret_cast<PFNGLENABLEIPROC>( load("glEnablei") );
    ::glDisablei = reinterpret_cast<PFNGLDISABLEIPROC>( load("glDisablei") );
    ::glIsEnabledi = reinterpret_cast<PFNGLISENABLEDIPROC>( load("glIsEnabledi") );
    ::glBeginTransformFeedback = reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>( load("glBeginTransformFeedback") );
    ::glEndTransformFeedback = reinterpret_cast<PFNGLENDTRANSFORMFEEDBACKPROC>( load("glEndTransformFeedback") );
    ::glBindBufferRange = reinterpret_cast<PFNGLBINDBUFFERRANGEPROC>( load("glBindBufferRange") );
    ::glBindBufferBase = reinterpret_cast<PFNGLBINDBUFFERBASEPROC>( load("glBindBufferBase") );
    ::glTransformFeedbackVaryings = reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>( load("glTransformFeedbackVaryings") );
    ::glGetTransformFeedbackVarying = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>( load("glGetTransformFeedbackVarying") );
    ::glClampColor = reinterpret_cast<PFNGLCLAMPCOLORPROC>( load("glClampColor") );
    ::glBeginConditionalRender = reinterpret_cast<PFNGLBEGINCONDITIONALRENDERPROC>( load("glBeginConditionalRender") );
    ::glEndConditionalRender = reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>( load("glEndConditionalRender") );
    ::glVertexAttribIPointer = reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>( load("glVertexAttribIPointer") );
    ::glGetVertexAttribIiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIIVPROC>( load("glGetVertexAttribIiv") );
    ::glGetVertexAttribIuiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>( load("glGetVertexAttribIuiv") );
    ::glVertexAttribI1i = reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>( load("glVertexAttribI1i") );
    ::glVertexAttribI2i = reinterpret_cast<PFNGLVERTEXATTRIBI2IPROC>( load("glVertexAttribI2i") );
    ::glVertexAttribI3i = reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>( load("glVertexAttribI3i") );
    ::glVertexAttribI4i = reinterpret_cast<PFNGLVERTEXATTRIBI4IPROC>( load("glVertexAttribI4i") );
    ::glVertexAttribI1ui = reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>( load("glVertexAttribI1ui") );
    ::glVertexAttribI2ui = reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>( load("glVertexAttribI2ui") );
    ::glVertexAttribI3ui = reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>( load("glVertexAttribI3ui") );
    ::glVertexAttribI4ui = reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>( load("glVertexAttribI4ui") );
    ::glVertexAttribI1iv = reinterpret_cast<PFNGLVERTEXATTRIBI1IVPROC>( load("glVertexAttribI1iv") );
    ::glVertexAttribI2iv = reinterpret_cast<PFNGLVERTEXATTRIBI2IVPROC>( load("glVertexAttribI2iv") );
    ::glVertexAttribI3iv = reinterpret_cast<PFNGLVERTEXATTRIBI3IVPROC>( load("glVertexAttribI3iv") );
    ::glVertexAttribI4iv = reinterpret_cast<PFNGLVERTEXATTRIBI4IVPROC>( load("glVertexAttribI4iv") );
    ::glVertexAttribI1uiv = reinterpret_cast<PFNGLVERTEXATTRIBI1UIVPROC>( load("glVertexAttribI1uiv") );
    ::glVertexAttribI2uiv = reinterpret_cast<PFNGLVERTEXATTRIBI2UIVPROC>( load("glVertexAttribI2uiv") );
    ::glVertexAttribI3uiv = reinterpret_cast<PFNGLVERTEXATTRIBI3UIVPROC>( load("glVertexAttribI3uiv") );
    ::glVertexAttribI4uiv = reinterpret_cast<PFNGLVERTEXATTRIBI4UIVPROC>( load("glVertexAttribI4uiv") );
    ::glVertexAttribI4bv = reinterpret_cast<PFNGLVERTEXATTRIBI4BVPROC>( load("glVertexAttribI4bv") );
    ::glVertexAttribI4sv = reinterpret_cast<PFNGLVERTEXATTRIBI4SVPROC>( load("glVertexAttribI4sv") );
    ::glVertexAttribI4ubv = reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>( load("glVertexAttribI4ubv") );
    ::glVertexAttribI4usv = reinterpret_cast<PFNGLVERTEXATTRIBI4USVPROC>( load("glVertexAttribI4usv") );
    ::glGetUniformuiv = reinterpret_cast<PFNGLGETUNIFORMUIVPROC>( load("glGetUniformuiv") );
    ::glBindFragDataLocation = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>( load("glBindFragDataLocation") );
    ::glGetFragDataLocation = reinterpret_cast<PFNGLGETFRAGDATALOCATIONPROC>( load("glGetFragDataLocation") );
    ::glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UIPROC>( load("glUniform1ui") );
    ::glUniform2ui = reinterpret_cast<PFNGLUNIFORM2UIPROC>( load("glUniform2ui") );
    ::glUniform3ui = reinterpret_cast<PFNGLUNIFORM3UIPROC>( load("glUniform3ui") );
    ::glUniform4ui = reinterpret_cast<PFNGLUNIFORM4UIPROC>( load("glUniform4ui") );
    ::glUniform1uiv = reinterpret_cast<PFNGLUNIFORM1UIVPROC>( load("glUniform1uiv") );
    ::glUniform2uiv = reinterpret_cast<PFNGLUNIFORM2UIVPROC>( load("glUniform2uiv") );
    ::glUniform3uiv = reinterpret_cast<PFNGLUNIFORM3UIVPROC>( load("glUniform3uiv") );
    ::glUniform4uiv = reinterpret_cast<PFNGLUNIFORM4UIVPROC>( load("glUniform4uiv") );
    ::glTexParameterIiv = reinterpret_cast<PFNGLTEXPARAMETERIIVPROC>( load("glTexParameterIiv") );
    ::glTexParameterIuiv = reinterpret_cast<PFNGLTEXPARAMETERIUIVPROC>( load("glTexParameterIuiv") );
    ::glGetTexParameterIiv = reinterpret_cast<PFNGLGETTEXPARAMETERIIVPROC>( load("glGetTexParameterIiv") );
    ::glGetTexParameterIuiv = reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>( load("glGetTexParameterIuiv") );
    ::glClearBufferiv = reinterpret_cast<PFNGLCLEARBUFFERIVPROC>( load("glClearBufferiv") );
    ::glClearBufferuiv = reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>( load("glClearBufferuiv") );
    ::glClearBufferfv = reinterpret_cast<PFNGLCLEARBUFFERFVPROC>( load("glClearBufferfv") );
    ::glClearBufferfi = reinterpret_cast<PFNGLCLEARBUFFERFIPROC>( load("glClearBufferfi") );
    ::glGetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>( load("glGetStringi") );
    ::glIsRenderbuffer = reinterpret_cast<PFNGLISRENDERBUFFERPROC>( load("glIsRenderbuffer") );
    ::glBindRenderbuffer = reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>( load("glBindRenderbuffer") );
    ::glDeleteRenderbuffers = reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>( load("glDeleteRenderbuffers") );
    ::glGenRenderbuffers = reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>( load("glGenRenderbuffers") );
    ::glRenderbufferStorage = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>( load("glRenderbufferStorage") );
    ::glGetRenderbufferParameteriv = reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVPROC>( load("glGetRenderbufferParameteriv") );
    ::glIsFramebuffer = reinterpret_cast<PFNGLISFRAMEBUFFERPROC>( load("glIsFramebuffer") );
    ::glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>( load("glBindFramebuffer") );
    ::glDeleteFramebuffers = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>( load("glDeleteFramebuffers") );
    ::glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>( load("glGenFramebuffers") );
    ::glCheckFramebufferStatus = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>( load("glCheckFramebufferStatus") );
    ::glFramebufferTexture1D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DPROC>( load("glFramebufferTexture1D") );
    ::glFramebufferTexture2D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>( load("glFramebufferTexture2D") );
    ::glFramebufferTexture3D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>( load("glFramebufferTexture3D") );
    ::glFramebufferRenderbuffer = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>( load("glFramebufferRenderbuffer") );
    ::glGetFramebufferAttachmentParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>( load("glGetFramebufferAttachmentParameteriv") );
    ::glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>( load("glGenerateMipmap") );
    ::glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>( load("glBlitFramebuffer") );
    ::glRenderbufferStorageMultisample = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>( load("glRenderbufferStorageMultisample") );
    ::glFramebufferTextureLayer = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>( load("glFramebufferTextureLayer") );
    ::glMapBufferRange = reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>( load("glMapBufferRange") );
    ::glFlushMappedBufferRange = reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>( load("glFlushMappedBufferRange") );
    ::glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>( load("glBindVertexArray") );
    ::glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>( load("glDeleteVertexArrays") );
    ::glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>( load("glGenVertexArrays") );
    ::glIsVertexArray = reinterpret_cast<PFNGLISVERTEXARRAYPROC>( load("glIsVertexArray") );
    ::glDrawArraysInstanced = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>( load("glDrawArraysInstanced") );
    ::glDrawElementsInstanced = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>( load("glDrawElementsInstanced") );
    ::glTexBuffer = reinterpret_cast<PFNGLTEXBUFFERPROC>( load("glTexBuffer") );
    ::glPrimitiveRestartIndex = reinterpret_cast<PFNGLPRIMITIVERESTARTINDEXPROC>( load("glPrimitiveRestartIndex") );
    ::glCopyBufferSubData = reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>( load("glCopyBufferSubData") );
    ::glGetUniformIndices = reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>( load("glGetUniformIndices") );
    ::glGetActiveUniformsiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>( load("glGetActiveUniformsiv") );
    ::glGetActiveUniformName = reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>( load("glGetActiveUniformName") );
    ::glGetUniformBlockIndex = reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>( load("glGetUniformBlockIndex") );
    ::glGetActiveUniformBlockiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>( load("glGetActiveUniformBlockiv") );
    ::glGetActiveUniformBlockName = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>( load("glGetActiveUniformBlockName") );
    ::glUniformBlockBinding = reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>( load("glUniformBlockBinding") );
    ::glDrawElementsBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSBASEVERTEXPROC>( load("glDrawElementsBaseVertex") );
    ::glDrawRangeElementsBaseVertex = reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>( load("glDrawRangeElementsBaseVertex") );
    ::glDrawElementsInstancedBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>( load("glDrawElementsInstancedBaseVertex") );
    ::glMultiDrawElementsBaseVertex = reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>( load("glMultiDrawElementsBaseVertex") );
    ::glProvokingVertex = reinterpret_cast<PFNGLPROVOKINGVERTEXPROC>( load("glProvokingVertex") );
    ::glFenceSync = reinterpret_cast<PFNGLFENCESYNCPROC>( load("glFenceSync") );
    ::glIsSync = reinterpret_cast<PFNGLISSYNCPROC>( load("glIsSync") );
    ::glDeleteSync = reinterpret_cast<PFNGLDELETESYNCPROC>( load("glDeleteSync") );
    ::glClientWaitSync = reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>( load("glClientWaitSync") );
    ::glWaitSync = reinterpret_cast<PFNGLWAITSYNCPROC>( load("glWaitSync") );
    ::glGetInteger64v = reinterpret_cast<PFNGLGETINTEGER64VPROC>( load("glGetInteger64v") );
    ::glGetSynciv = reinterpret_cast<PFNGLGETSYNCIVPROC>( load("glGetSynciv") );
    ::glGetInteger64i_v = reinterpret_cast<PFNGLGETINTEGER64I_VPROC>( load("glGetInteger64i_v") );
    ::glGetBufferParameteri64v = reinterpret_cast<PFNGLGETBUFFERPARAMETERI64VPROC>( load("glGetBufferParameteri64v") );
    ::glFramebufferTexture = reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>( load("glFramebufferTexture") );
    ::glTexImage2DMultisample = reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>( load("glTexImage2DMultisample") );
    ::glTexImage3DMultisample = reinterpret_cast<PFNGLTEXIMAGE3DMULTISAMPLEPROC>( load("glTexImage3DMultisample") );
    ::glGetMultisamplefv = reinterpret_cast<PFNGLGETMULTISAMPLEFVPROC>( load("glGetMultisamplefv") );
    ::glSampleMaski = reinterpret_cast<PFNGLSAMPLEMASKIPROC>( load("glSampleMaski") );
    ::glBindFragDataLocationIndexed = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>( load("glBindFragDataLocationIndexed") );
    ::glGetFragDataIndex = reinterpret_cast<PFNGLGETFRAGDATAINDEXPROC>( load("glGetFragDataIndex") );
    ::glGenSamplers = reinterpret_cast<PFNGLGENSAMPLERSPROC>( load("glGenSamplers") );
    ::glDeleteSamplers = reinterpret_cast<PFNGLDELETESAMPLERSPROC>( load("glDeleteSamplers") );
    ::glIsSampler = reinterpret_cast<PFNGLISSAMPLERPROC>( load("glIsSampler") );
    ::glBindSampler = reinterpret_cast<PFNGLBINDSAMPLERPROC>( load("glBindSampler") );
    ::glSamplerParameteri = reinterpret_cast<PFNGLSAMPLERPARAMETERIPROC>( load("glSamplerParameteri") );
    ::glSamplerParameteriv = reinterpret_cast<PFNGLSAMPLERPARAMETERIVPROC>( load("glSamplerParameteriv") );
    ::glSamplerParameterf = reinterpret_cast<PFNGLSAMPLERPARAMETERFPROC>( load("glSamplerParameterf") );
    ::glSamplerParameterfv = reinterpret_cast<PFNGLSAMPLERPARAMETERFVPROC>( load("glSamplerParameterfv") );
    ::glSamplerParameterIiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIIVPROC>( load("glSamplerParameterIiv") );
    ::glSamplerParameterIuiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIUIVPROC>( load("glSamplerParameterIuiv") );
    ::glGetSamplerParameteriv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIVPROC>( load("glGetSamplerParameteriv") );
    ::glGetSamplerParameterIiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIIVPROC>( load("glGetSamplerParameterIiv") );
    ::glGetSamplerParameterfv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERFVPROC>( load("glGetSamplerParameterfv") );
    ::glGetSamplerParameterIuiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIUIVPROC>( load("glGetSamplerParameterIuiv") );
    ::glQueryCounter = reinterpret_cast<PFNGLQUERYCOUNTERPROC>( load("glQueryCounter") );
    ::glGetQueryObjecti64v = reinterpret_cast<PFNGLGETQUERYOBJECTI64VPROC>( load("glGetQueryObjecti64v") );
    ::glGetQueryObjectui64v = reinterpret_cast<PFNGLGETQUERYOBJECTUI64VPROC>( load("glGetQueryObjectui64v") );
    ::glVertexAttribDivisor = reinterpret_cast<PFNGLVERTEXATTRIBDIVISORPROC>( load("glVertexAttribDivisor") );
    ::glVertexAttribP1ui = reinterpret_cast<PFNGLVERTEXATTRIBP1UIPROC>( load("glVertexAttribP1ui") );
    ::glVertexAttribP1uiv = reinterpret_cast<PFNGLVERTEXATTRIBP1UIVPROC>( load("glVertexAttribP1uiv") );
    ::glVertexAttribP2ui = reinterpret_cast<PFNGLVERTEXATTRIBP2UIPROC>( load("glVertexAttribP2ui") );
    ::glVertexAttribP2uiv = reinterpret_cast<PFNGLVERTEXATTRIBP2UIVPROC>( load("glVertexAttribP2uiv") );
    ::glVertexAttribP3ui = reinterpret_cast<PFNGLVERTEXATTRIBP3UIPROC>( load("glVertexAttribP3ui") );
    ::glVertexAttribP3uiv = reinterpret_cast<PFNGLVERTEXATTRIBP3UIVPROC>( load("glVertexAttribP3uiv") );
    ::glVertexAttribP4ui = reinterpret_cast<PFNGLVERTEXATTRIBP4UIPROC>( load("glVertexAttribP4ui") );
    ::glVertexAttribP4uiv = reinterpret_cast<PFNGLVERTEXATTRIBP4UIVPROC>( load("glVertexAttribP4uiv") );
    ::glMinSampleShading = reinterpret_cast<PFNGLMINSAMPLESHADINGPROC>( load("glMinSampleShading") );
    ::glBlendEquationi = reinterpret_cast<PFNGLBLENDEQUATIONIPROC>( load("glBlendEquationi") );
    ::glBlendEquationSeparatei = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIPROC>( load("glBlendEquationSeparatei") );
    ::glBlendFunci = reinterpret_cast<PFNGLBLENDFUNCIPROC>( load("glBlendFunci") );
    ::glBlendFuncSeparatei = reinterpret_cast<PFNGLBLENDFUNCSEPARATEIPROC>( load("glBlendFuncSeparatei") );
    ::glDrawArraysIndirect = reinterpret_cast<PFNGLDRAWARRAYSINDIRECTPROC>( load("glDrawArraysIndirect") );
    ::glDrawElementsIndirect = reinterpret_cast<PFNGLDRAWELEMENTSINDIRECTPROC>( load("glDrawElementsIndirect") );
    ::glUniform1d = reinterpret_cast<PFNGLUNIFORM1DPROC>( load("glUniform1d") );
    ::glUniform2d = reinterpret_cast<PFNGLUNIFORM2DPROC>( load("glUniform2d") );
    ::glUniform3d = reinterpret_cast<PFNGLUNIFORM3DPROC>( load("glUniform3d") );
    ::glUniform4d = reinterpret_cast<PFNGLUNIFORM4DPROC>( load("glUniform4d") );
    ::glUniform1dv = reinterpret_cast<PFNGLUNIFORM1DVPROC>( load("glUniform1dv") );
    ::glUniform2dv = reinterpret_cast<PFNGLUNIFORM2DVPROC>( load("glUniform2dv") );
    ::glUniform3dv = reinterpret_cast<PFNGLUNIFORM3DVPROC>( load("glUniform3dv") );
    ::glUniform4dv = reinterpret_cast<PFNGLUNIFORM4DVPROC>( load("glUniform4dv") );
    ::glUniformMatrix2dv = reinterpret_cast<PFNGLUNIFORMMATRIX2DVPROC>( load("glUniformMatrix2dv") );
    ::glUniformMatrix3dv = reinterpret_cast<PFNGLUNIFORMMATRIX3DVPROC>( load("glUniformMatrix3dv") );
    ::glUniformMatrix4dv = reinterpret_cast<PFNGLUNIFORMMATRIX4DVPROC>( load("glUniformMatrix4dv") );
    ::glUniformMatrix2x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3DVPROC>( load("glUniformMatrix2x3dv") );
    ::glUniformMatrix2x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4DVPROC>( load("glUniformMatrix2x4dv") );
    ::glUniformMatrix3x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2DVPROC>( load("glUniformMatrix3x2dv") );
    ::glUniformMatrix3x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4DVPROC>( load("glUniformMatrix3x4dv") );
    ::glUniformMatrix4x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2DVPROC>( load("glUniformMatrix4x2dv") );
    ::glUniformMatrix4x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3DVPROC>( load("glUniformMatrix4x3dv") );
    ::glGetUniformdv = reinterpret_cast<PFNGLGETUNIFORMDVPROC>( load("glGetUniformdv") );
    ::glGetSubroutineUniformLocation = reinterpret_cast<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>( load("glGetSubroutineUniformLocation") );
    ::glGetSubroutineIndex = reinterpret_cast<PFNGLGETSUBROUTINEINDEXPROC>( load("glGetSubroutineIndex") );
    ::glGetActiveSubroutineUniformiv = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC>( load("glGetActiveSubroutineUniformiv") );
    ::glGetActiveSubroutineUniformName = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC>( load("glGetActiveSubroutineUniformName") );
    ::glGetActiveSubroutineName = reinterpret_cast<PFNGLGETACTIVESUBROUTINENAMEPROC>( load("glGetActiveSubroutineName") );
    ::glUniformSubroutinesuiv = reinterpret_cast<PFNGLUNIFORMSUBROUTINESUIVPROC>( load("glUniformSubroutinesuiv") );
    ::glGetUniformSubroutineuiv = reinterpret_cast<PFNGLGETUNIFORMSUBROUTINEUIVPROC>( load("glGetUniformSubroutineuiv") );
    ::glGetProgramStageiv = reinterpret_cast<PFNGLGETPROGRAMSTAGEIVPROC>( load("glGetProgramStageiv") );
    ::glPatchParameteri = reinterpret_cast<PFNGLPATCHPARAMETERIPROC>( load("glPatchParameteri") );
    ::glPatchParameterfv = reinterpret_cast<PFNGLPATCHPARAMETERFVPROC>( load("glPatchParameterfv") );
    ::glBindTransformFeedback = reinterpret_cast<PFNGLBINDTRANSFORMFEEDBACKPROC>( load("glBindTransformFeedback") );
    ::glDeleteTransformFeedbacks = reinterpret_cast<PFNGLDELETETRANSFORMFEEDBACKSPROC>( load("glDeleteTransformFeedbacks") );
    ::glGenTransformFeedbacks = reinterpret_cast<PFNGLGENTRANSFORMFEEDBACKSPROC>( load("glGenTransformFeedbacks") );
    ::glIsTransformFeedback = reinterpret_cast<PFNGLISTRANSFORMFEEDBACKPROC>( load("glIsTransformFeedback") );
    ::glPauseTransformFeedback = reinterpret_cast<PFNGLPAUSETRANSFORMFEEDBACKPROC>( load("glPauseTransformFeedback") );
    ::glResumeTransformFeedback = reinterpret_cast<PFNGLRESUMETRANSFORMFEEDBACKPROC>( load("glResumeTransformFeedback") );
    ::glDrawTransformFeedback = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKPROC>( load("glDrawTransformFeedback") );
    ::glDrawTransformFeedbackStream = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC>( load("glDrawTransformFeedbackStream") );
    ::glBeginQueryIndexed = reinterpret_cast<PFNGLBEGINQUERYINDEXEDPROC>( load("glBeginQueryIndexed") );
    ::glEndQueryIndexed = reinterpret_cast<PFNGLENDQUERYINDEXEDPROC>( load("glEndQueryIndexed") );
    ::glGetQueryIndexediv = reinterpret_cast<PFNGLGETQUERYINDEXEDIVPROC>( load("glGetQueryIndexediv") );
    ::glReleaseShaderCompiler = reinterpret_cast<PFNGLRELEASESHADERCOMPILERPROC>( load("glReleaseShaderCompiler") );
    ::glShaderBinary = reinterpret_cast<PFNGLSHADERBINARYPROC>( load("glShaderBinary") );
    ::glGetShaderPrecisionFormat = reinterpret_cast<PFNGLGETSHADERPRECISIONFORMATPROC>( load("glGetShaderPrecisionFormat") );
    ::glDepthRangef = reinterpret_cast<PFNGLDEPTHRANGEFPROC>( load("glDepthRangef") );
    ::glClearDepthf = reinterpret_cast<PFNGLCLEARDEPTHFPROC>( load("glClearDepthf") );
    ::glGetProgramBinary = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC>( load("glGetProgramBinary") );
    ::glProgramBinary = reinterpret_cast<PFNGLPROGRAMBINARYPROC>( load("glProgramBinary") );
    ::glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>( load("glProgramParameteri") );
    ::glUseProgramStages = reinterpret_cast<PFNGLUSEPROGRAMSTAGESPROC>( load("glUseProgramStages") );
    ::glActiveShaderProgram = reinterpret_cast<PFNGLACTIVESHADERPROGRAMPROC>( load("glActiveShaderProgram") );
    ::glCreateShaderProgramv = reinterpret_cast<PFNGLCREATESHADERPROGRAMVPROC>( load("glCreateShaderProgramv") );
    ::glBindProgramPipeline = reinterpret_cast<PFNGLBINDPROGRAMPIPELINEPROC>( load("glBindProgramPipeline") );
    ::glDeleteProgramPipelines = reinterpret_cast<PFNGLDELETEPROGRAMPIPELINESPROC>( load("glDeleteProgramPipelines") );
    ::glGenProgramPipelines = reinterpret_cast<PFNGLGENPROGRAMPIPELINESPROC>( load("glGenProgramPipelines") );
    ::glIsProgramPipeline = reinterpret_cast<PFNGLISPROGRAMPIPELINEPROC>( load("glIsProgramPipeline") );
    ::glGetProgramPipelineiv = reinterpret_cast<PFNGLGETPROGRAMPIPELINEIVPROC>( load("glGetProgramPipelineiv") );
    ::glProgramUniform1i = reinterpret_cast<PFNGLPROGRAMUNIFORM1IPROC>( load("glProgramUniform1i") );
    ::glProgramUniform1iv = reinterpret_cast<PFNGLPROGRAMUNIFORM1IVPROC>( load("glProgramUniform1iv") );
    ::glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FPROC>( load("glProgramUniform1f") );
    ::glProgramUniform1fv = reinterpret_cast<PFNGLPROGRAMUNIFORM1FVPROC>( load("glProgramUniform1fv") );
    ::glProgramUniform1d = reinterpret_cast<PFNGLPROGRAMUNIFORM1DPROC>( load("glProgramUniform1d") );
    ::glProgramUniform1dv = reinterpret_cast<PFNGLPROGRAMUNIFORM1DVPROC>( load("glProgramUniform1dv") );
    ::glProgramUniform1ui = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIPROC>( load("glProgramUniform1ui") );
    ::glProgramUniform1uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIVPROC>( load("glProgramUniform1uiv") );
    ::glProgramUniform2i = reinterpret_cast<PFNGLPROGRAMUNIFORM2IPROC>( load("glProgramUniform2i") );
    ::glProgramUniform2iv = reinterpret_cast<PFNGLPROGRAMUNIFORM2IVPROC>( load("glProgramUniform2iv") );
    ::glProgramUniform2f = reinterpret_cast<PFNGLPROGRAMUNIFORM2FPROC>( load("glProgramUniform2f") );
    ::glProgramUniform2fv = reinterpret_cast<PFNGLPROGRAMUNIFORM2FVPROC>( load("glProgramUniform2fv") );
    ::glProgramUniform2d = reinterpret_cast<PFNGLPROGRAMUNIFORM2DPROC>( load("glProgramUniform2d") );
    ::glProgramUniform2dv = reinterpret_cast<PFNGLPROGRAMUNIFORM2DVPROC>( load("glProgramUniform2dv") );
    ::glProgramUniform2ui = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIPROC>( load("glProgramUniform2ui") );
    ::glProgramUniform2uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVPROC>( load("glProgramUniform2uiv") );
    ::glProgramUniform3i = reinterpret_cast<PFNGLPROGRAMUNIFORM3IPROC>( load("glProgramUniform3i") );
    ::glProgramUniform3iv = reinterpret_cast<PFNGLPROGRAMUNIFORM3IVPROC>( load("glProgramUniform3iv") );
    ::glProgramUniform3f = reinterpret_cast<PFNGLPROGRAMUNIFORM3FPROC>( load("glProgramUniform3f") );
    ::glProgramUniform3fv = reinterpret_cast<PFNGLPROGRAMUNIFORM3FVPROC>( load("glProgramUniform3fv") );
    ::glProgramUniform3d = reinterpret_cast<PFNGLPROGRAMUNIFORM3DPROC>( load("glProgramUniform3d") );
    ::glProgramUniform3dv = reinterpret_cast<PFNGLPROGRAMUNIFORM3DVPROC>( load("glProgramUniform3dv") );
    ::glProgramUniform3ui = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIPROC>( load("glProgramUniform3ui") );
    ::glProgramUniform3uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIVPROC>( load("glProgramUniform3uiv") );
    ::glProgramUniform4i = reinterpret_cast<PFNGLPROGRAMUNIFORM4IPROC>( load("glProgramUniform4i") );
    ::glProgramUniform4iv = reinterpret_cast<PFNGLPROGRAMUNIFORM4IVPROC>( load("glProgramUniform4iv") );
    ::glProgramUniform4f = reinterpret_cast<PFNGLPROGRAMUNIFORM4FPROC>( load("glProgramUniform4f") );
    ::glProgramUniform4fv = reinterpret_cast<PFNGLPROGRAMUNIFORM4FVPROC>( load("glProgramUniform4fv") );
    ::glProgramUniform4d = reinterpret_cast<PFNGLPROGRAMUNIFORM4DPROC>( load("glProgramUniform4d") );
    ::glProgramUniform4dv = reinterpret_cast<PFNGLPROGRAMUNIFORM4DVPROC>( load("glProgramUniform4dv") );
    ::glProgramUniform4ui = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIPROC>( load("glProgramUniform4ui") );
    ::glProgramUniform4uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIVPROC>( load("glProgramUniform4uiv") );
    ::glProgramUniformMatrix2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>( load("glProgramUniformMatrix2fv") );
    ::glProgramUniformMatrix3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>( load("glProgramUniformMatrix3fv") );
    ::glProgramUniformMatrix4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>( load("glProgramUniformMatrix4fv") );
    ::glProgramUniformMatrix2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2DVPROC>( load("glProgramUniformMatrix2dv") );
    ::glProgramUniformMatrix3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3DVPROC>( load("glProgramUniformMatrix3dv") );
    ::glProgramUniformMatrix4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4DVPROC>( load("glProgramUniformMatrix4dv") );
    ::glProgramUniformMatrix2x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>( load("glProgramUniformMatrix2x3fv") );
    ::glProgramUniformMatrix3x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>( load("glProgramUniformMatrix3x2fv") );
    ::glProgramUniformMatrix2x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>( load("glProgramUniformMatrix2x4fv") );
    ::glProgramUniformMatrix4x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>( load("glProgramUniformMatrix4x2fv") );
    ::glProgramUniformMatrix3x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>( load("glProgramUniformMatrix3x4fv") );
    ::glProgramUniformMatrix4x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>( load("glProgramUniformMatrix4x3fv") );
    ::glProgramUniformMatrix2x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC>( load("glProgramUniformMatrix2x3dv") );
    ::glProgramUniformMatrix3x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC>( load("glProgramUniformMatrix3x2dv") );
    ::glProgramUniformMatrix2x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC>( load("glProgramUniformMatrix2x4dv") );
    ::glProgramUniformMatrix4x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC>( load("glProgramUniformMatrix4x2dv") );
    ::glProgramUniformMatrix3x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC>( load("glProgramUniformMatrix3x4dv") );
    ::glProgramUniformMatrix4x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC>( load("glProgramUniformMatrix4x3dv") );
    ::glValidateProgramPipeline = reinterpret_cast<PFNGLVALIDATEPROGRAMPIPELINEPROC>( load("glValidateProgramPipeline") );
    ::glGetProgramPipelineInfoLog = reinterpret_cast<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>( load("glGetProgramPipelineInfoLog") );
    ::glVertexAttribL1d = reinterpret_cast<PFNGLVERTEXATTRIBL1DPROC>( load("glVertexAttribL1d") );
    ::glVertexAttribL2d = reinterpret_cast<PFNGLVERTEXATTRIBL2DPROC>( load("glVertexAttribL2d") );
    ::glVertexAttribL3d = reinterpret_cast<PFNGLVERTEXATTRIBL3DPROC>( load("glVertexAttribL3d") );
    ::glVertexAttribL4d = reinterpret_cast<PFNGLVERTEXATTRIBL4DPROC>( load("glVertexAttribL4d") );
    ::glVertexAttribL1dv = reinterpret_cast<PFNGLVERTEXATTRIBL1DVPROC>( load("glVertexAttribL1dv") );
    ::glVertexAttribL2dv = reinterpret_cast<PFNGLVERTEXATTRIBL2DVPROC>( load("glVertexAttribL2dv") );
    ::glVertexAttribL3dv = reinterpret_cast<PFNGLVERTEXATTRIBL3DVPROC>( load("glVertexAttribL3dv") );
    ::glVertexAttribL4dv = reinterpret_cast<PFNGLVERTEXATTRIBL4DVPROC>( load("glVertexAttribL4dv") );
    ::glVertexAttribLPointer = reinterpret_cast<PFNGLVERTEXATTRIBLPOINTERPROC>( load("glVertexAttribLPointer") );
    ::glGetVertexAttribLdv = reinterpret_cast<PFNGLGETVERTEXATTRIBLDVPROC>( load("glGetVertexAttribLdv") );
    ::glViewportArrayv = reinterpret_cast<PFNGLVIEWPORTARRAYVPROC>( load("glViewportArrayv") );
    ::glViewportIndexedf = reinterpret_cast<PFNGLVIEWPORTINDEXEDFPROC>( load("glViewportIndexedf") );
    ::glViewportIndexedfv = reinterpret_cast<PFNGLVIEWPORTINDEXEDFVPROC>( load("glViewportIndexedfv") );
    ::glScissorArrayv = reinterpret_cast<PFNGLSCISSORARRAYVPROC>( load("glScissorArrayv") );
    ::glScissorIndexed = reinterpret_cast<PFNGLSCISSORINDEXEDPROC>( load("glScissorIndexed") );
    ::glScissorIndexedv = reinterpret_cast<PFNGLSCISSORINDEXEDVPROC>( load("glScissorIndexedv") );
    ::glDepthRangeArrayv = reinterpret_cast<PFNGLDEPTHRANGEARRAYVPROC>( load("glDepthRangeArrayv") );
    ::glDepthRangeIndexed = reinterpret_cast<PFNGLDEPTHRANGEINDEXEDPROC>( load("glDepthRangeIndexed") );
    ::glGetFloati_v = reinterpret_cast<PFNGLGETFLOATI_VPROC>( load("glGetFloati_v") );
    ::glGetDoublei_v = reinterpret_cast<PFNGLGETDOUBLEI_VPROC>( load("glGetDoublei_v") );
    ::glDrawArraysInstancedBaseInstance = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC>( load("glDrawArraysInstancedBaseInstance") );
    ::glDrawElementsInstancedBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC>( load("glDrawElementsInstancedBaseInstance") );
    ::glDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>( load("glDrawElementsInstancedBaseVertexBaseInstance") );
    ::glGetInternalformativ = reinterpret_cast<PFNGLGETINTERNALFORMATIVPROC>( load("glGetInternalformativ") );
    ::glGetActiveAtomicCounterBufferiv = reinterpret_cast<PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC>( load("glGetActiveAtomicCounterBufferiv") );
    ::glBindImageTexture = reinterpret_cast<PFNGLBINDIMAGETEXTUREPROC>( load("glBindImageTexture") );
    ::glMemoryBarrier = reinterpret_cast<PFNGLMEMORYBARRIERPROC>( load("glMemoryBarrier") );
    ::glTexStorage1D = reinterpret_cast<PFNGLTEXSTORAGE1DPROC>( load("glTexStorage1D") );
    ::glTexStorage2D = reinterpret_cast<PFNGLTEXSTORAGE2DPROC>( load("glTexStorage2D") );
    ::glTexStorage3D = reinterpret_cast<PFNGLTEXSTORAGE3DPROC>( load("glTexStorage3D") );
    ::glDrawTransformFeedbackInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC>( load("glDrawTransformFeedbackInstanced") );
    ::glDrawTransformFeedbackStreamInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC>( load("glDrawTransformFeedbackStreamInstanced") );
    ::glClearBufferData = reinterpret_cast<PFNGLCLEARBUFFERDATAPROC>( load("glClearBufferData") );
    ::glClearBufferSubData = reinterpret_cast<PFNGLCLEARBUFFERSUBDATAPROC>( load("glClearBufferSubData") );
    ::glDispatchCompute = reinterpret_cast<PFNGLDISPATCHCOMPUTEPROC>( load("glDispatchCompute") );
    ::glDispatchComputeIndirect = reinterpret_cast<PFNGLDISPATCHCOMPUTEINDIRECTPROC>( load("glDispatchComputeIndirect") );
    ::glCopyImageSubData = reinterpret_cast<PFNGLCOPYIMAGESUBDATAPROC>( load("glCopyImageSubData") );
    ::glFramebufferParameteri = reinterpret_cast<PFNGLFRAMEBUFFERPARAMETERIPROC>( load("glFramebufferParameteri") );
    ::glGetFramebufferParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>( load("glGetFramebufferParameteriv") );
    ::glGetInternalformati64v = reinterpret_cast<PFNGLGETINTERNALFORMATI64VPROC>( load("glGetInternalformati64v") );
    ::glInvalidateTexSubImage = reinterpret_cast<PFNGLINVALIDATETEXSUBIMAGEPROC>( load("glInvalidateTexSubImage") );
    ::glInvalidateTexImage = reinterpret_cast<PFNGLINVALIDATETEXIMAGEPROC>( load("glInvalidateTexImage") );
    ::glInvalidateBufferSubData = reinterpret_cast<PFNGLINVALIDATEBUFFERSUBDATAPROC>( load("glInvalidateBufferSubData") );
    ::glInvalidateBufferData = reinterpret_cast<PFNGLINVALIDATEBUFFERDATAPROC>( load("glInvalidateBufferData") );
    ::glInvalidateFramebuffer = reinterpret_cast<PFNGLINVALIDATEFRAMEBUFFERPROC>( load("glInvalidateFramebuffer") );
    ::glInvalidateSubFramebuffer = reinterpret_cast<PFNGLINVALIDATESUBFRAMEBUFFERPROC>( load("glInvalidateSubFramebuffer") );
    ::glMultiDrawArraysIndirect = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTPROC>( load("glMultiDrawArraysIndirect") );
    ::glMultiDrawElementsIndirect = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTPROC>( load("glMultiDrawElementsIndirect") );
    ::glGetProgramInterfaceiv = reinterpret_cast<PFNGLGETPROGRAMINTERFACEIVPROC>( load("glGetProgramInterfaceiv") );
    ::glGetProgramResourceIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>( load("glGetProgramResourceIndex") );
    ::glGetProgramResourceName = reinterpret_cast<PFNGLGETPROGRAMRESOURCENAMEPROC>( load("glGetProgramResourceName") );
    ::glGetProgramResourceiv = reinterpret_cast<PFNGLGETPROGRAMRESOURCEIVPROC>( load("glGetProgramResourceiv") );
    ::glGetProgramResourceLocation = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONPROC>( load("glGetProgramResourceLocation") );
    ::glGetProgramResourceLocationIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC>( load("glGetProgramResourceLocationIndex") );
    ::glShaderStorageBlockBinding = reinterpret_cast<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>( load("glShaderStorageBlockBinding") );
    ::glTexBufferRange = reinterpret_cast<PFNGLTEXBUFFERRANGEPROC>( load("glTexBufferRange") );
    ::glTexStorage2DMultisample = reinterpret_cast<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>( load("glTexStorage2DMultisample") );
    ::glTexStorage3DMultisample = reinterpret_cast<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>( load("glTexStorage3DMultisample") );
    ::glTextureView = reinterpret_cast<PFNGLTEXTUREVIEWPROC>( load("glTextureView") );
    ::glBindVertexBuffer = reinterpret_cast<PFNGLBINDVERTEXBUFFERPROC>( load("glBindVertexBuffer") );
    ::glVertexAttribFormat = reinterpret_cast<PFNGLVERTEXATTRIBFORMATPROC>( load("glVertexAttribFormat") );
    ::glVertexAttribIFormat = reinterpret_cast<PFNGLVERTEXATTRIBIFORMATPROC>( load("glVertexAttribIFormat") );
    ::glVertexAttribLFormat = reinterpret_cast<PFNGLVERTEXATTRIBLFORMATPROC>( load("glVertexAttribLFormat") );
    ::glVertexAttribBinding = reinterpret_cast<PFNGLVERTEXATTRIBBINDINGPROC>( load("glVertexAttribBinding") );
    ::glVertexBindingDivisor = reinterpret_cast<PFNGLVERTEXBINDINGDIVISORPROC>( load("glVertexBindingDivisor") );
    ::glDebugMessageControl = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>( load("glDebugMessageControl") );
    ::glDebugMessageInsert = reinterpret_cast<PFNGLDEBUGMESSAGEINSERTPROC>( load("glDebugMessageInsert") );
    ::glDebugMessageCallback = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>( load("glDebugMessageCallback") );
    ::glGetDebugMessageLog = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGPROC>( load("glGetDebugMessageLog") );
    ::glPushDebugGroup = reinterpret_cast<PFNGLPUSHDEBUGGROUPPROC>( load("glPushDebugGroup") );
    ::glPopDebugGroup = reinterpret_cast<PFNGLPOPDEBUGGROUPPROC>( load("glPopDebugGroup") );
    ::glObjectLabel = reinterpret_cast<PFNGLOBJECTLABELPROC>( load("glObjectLabel") );
    ::glGetObjectLabel = reinterpret_cast<PFNGLGETOBJECTLABELPROC>( load("glGetObjectLabel") );
    ::glObjectPtrLabel = reinterpret_cast<PFNGLOBJECTPTRLABELPROC>( load("glObjectPtrLabel") );
    ::glGetObjectPtrLabel = reinterpret_cast<PFNGLGETOBJECTPTRLABELPROC>( load("glGetObjectPtrLabel") );
    ::glBufferStorage = reinterpret_cast<PFNGLBUFFERSTORAGEPROC>( load("glBufferStorage") );
    ::glClearTexImage = reinterpret_cast<PFNGLCLEARTEXIMAGEPROC>( load("glClearTexImage") );
    ::glClearTexSubImage = reinterpret_cast<PFNGLCLEARTEXSUBIMAGEPROC>( load("glClearTexSubImage") );
    ::glBindBuffersBase = reinterpret_cast<PFNGLBINDBUFFERSBASEPROC>( load("glBindBuffersBase") );
    ::glBindBuffersRange = reinterpret_cast<PFNGLBINDBUFFERSRANGEPROC>( load("glBindBuffersRange") );
    ::glBindTextures = reinterpret_cast<PFNGLBINDTEXTURESPROC>( load("glBindTextures") );
    ::glBindSamplers = reinterpret_cast<PFNGLBINDSAMPLERSPROC>( load("glBindSamplers") );
    ::glBindImageTextures = reinterpret_cast<PFNGLBINDIMAGETEXTURESPROC>( load("glBindImageTextures") );
    ::glBindVertexBuffers = reinterpret_cast<PFNGLBINDVERTEXBUFFERSPROC>( load("glBindVertexBuffers") );
    ::glGetTextureHandleARB = reinterpret_cast<PFNGLGETTEXTUREHANDLEARBPROC>( load("glGetTextureHandleARB") );
    ::glGetTextureSamplerHandleARB = reinterpret_cast<PFNGLGETTEXTURESAMPLERHANDLEARBPROC>( load("glGetTextureSamplerHandleARB") );
    ::glMakeTextureHandleResidentARB = reinterpret_cast<PFNGLMAKETEXTUREHANDLERESIDENTARBPROC>( load("glMakeTextureHandleResidentARB") );
    ::glMakeTextureHandleNonResidentARB = reinterpret_cast<PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC>( load("glMakeTextureHandleNonResidentARB") );
    ::glGetImageHandleARB = reinterpret_cast<PFNGLGETIMAGEHANDLEARBPROC>( load("glGetImageHandleARB") );
    ::glMakeImageHandleResidentARB = reinterpret_cast<PFNGLMAKEIMAGEHANDLERESIDENTARBPROC>( load("glMakeImageHandleResidentARB") );
    ::glMakeImageHandleNonResidentARB = reinterpret_cast<PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC>( load("glMakeImageHandleNonResidentARB") );
    ::glUniformHandleui64ARB = reinterpret_cast<PFNGLUNIFORMHANDLEUI64ARBPROC>( load("glUniformHandleui64ARB") );
    ::glUniformHandleui64vARB = reinterpret_cast<PFNGLUNIFORMHANDLEUI64VARBPROC>( load("glUniformHandleui64vARB") );
    ::glProgramUniformHandleui64ARB = reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC>( load("glProgramUniformHandleui64ARB") );
    ::glProgramUniformHandleui64vARB = reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC>( load("glProgramUniformHandleui64vARB") );
    ::glIsTextureHandleResidentARB = reinterpret_cast<PFNGLISTEXTUREHANDLERESIDENTARBPROC>( load("glIsTextureHandleResidentARB") );
    ::glIsImageHandleResidentARB = reinterpret_cast<PFNGLISIMAGEHANDLERESIDENTARBPROC>( load("glIsImageHandleResidentARB") );
    ::glVertexAttribL1ui64ARB = reinterpret_cast<PFNGLVERTEXATTRIBL1UI64ARBPROC>( load("glVertexAttribL1ui64ARB") );
    ::glVertexAttribL1ui64vARB = reinterpret_cast<PFNGLVERTEXATTRIBL1UI64VARBPROC>( load("glVertexAttribL1ui64vARB") );
    ::glGetVertexAttribLui64vARB = reinterpret_cast<PFNGLGETVERTEXATTRIBLUI64VARBPROC>( load("glGetVertexAttribLui64vARB") );
    ::glCreateSyncFromCLeventARB = reinterpret_cast<PFNGLCREATESYNCFROMCLEVENTARBPROC>( load("glCreateSyncFromCLeventARB") );
    ::glDispatchComputeGroupSizeARB = reinterpret_cast<PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC>( load("glDispatchComputeGroupSizeARB") );
    ::glDebugMessageControlARB = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLARBPROC>( load("glDebugMessageControlARB") );
    ::glDebugMessageInsertARB = reinterpret_cast<PFNGLDEBUGMESSAGEINSERTARBPROC>( load("glDebugMessageInsertARB") );
    ::glDebugMessageCallbackARB = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKARBPROC>( load("glDebugMessageCallbackARB") );
    ::glGetDebugMessageLogARB = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGARBPROC>( load("glGetDebugMessageLogARB") );
    ::glBlendEquationiARB = reinterpret_cast<PFNGLBLENDEQUATIONIARBPROC>( load("glBlendEquationiARB") );
    ::glBlendEquationSeparateiARB = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIARBPROC>( load("glBlendEquationSeparateiARB") );
    ::glBlendFunciARB = reinterpret_cast<PFNGLBLENDFUNCIARBPROC>( load("glBlendFunciARB") );
    ::glBlendFuncSeparateiARB = reinterpret_cast<PFNGLBLENDFUNCSEPARATEIARBPROC>( load("glBlendFuncSeparateiARB") );
    ::glMultiDrawArraysIndirectCountARB = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC>( load("glMultiDrawArraysIndirectCountARB") );
    ::glMultiDrawElementsIndirectCountARB = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC>( load("glMultiDrawElementsIndirectCountARB") );
    ::glGetGraphicsResetStatusARB = reinterpret_cast<PFNGLGETGRAPHICSRESETSTATUSARBPROC>( load("glGetGraphicsResetStatusARB") );
    ::glGetnTexImageARB = reinterpret_cast<PFNGLGETNTEXIMAGEARBPROC>( load("glGetnTexImageARB") );
    ::glReadnPixelsARB = reinterpret_cast<PFNGLREADNPIXELSARBPROC>( load("glReadnPixelsARB") );
    ::glGetnCompressedTexImageARB = reinterpret_cast<PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC>( load("glGetnCompressedTexImageARB") );
    ::glGetnUniformfvARB = reinterpret_cast<PFNGLGETNUNIFORMFVARBPROC>( load("glGetnUniformfvARB") );
    ::glGetnUniformivARB = reinterpret_cast<PFNGLGETNUNIFORMIVARBPROC>( load("glGetnUniformivARB") );
    ::glGetnUniformuivARB = reinterpret_cast<PFNGLGETNUNIFORMUIVARBPROC>( load("glGetnUniformuivARB") );
    ::glGetnUniformdvARB = reinterpret_cast<PFNGLGETNUNIFORMDVARBPROC>( load("glGetnUniformdvARB") );
    ::glMinSampleShadingARB = reinterpret_cast<PFNGLMINSAMPLESHADINGARBPROC>( load("glMinSampleShadingARB") );
    ::glNamedStringARB = reinterpret_cast<PFNGLNAMEDSTRINGARBPROC>( load("glNamedStringARB") );
    ::glDeleteNamedStringARB = reinterpret_cast<PFNGLDELETENAMEDSTRINGARBPROC>( load("glDeleteNamedStringARB") );
    ::glCompileShaderIncludeARB = reinterpret_cast<PFNGLCOMPILESHADERINCLUDEARBPROC>( load("glCompileShaderIncludeARB") );
    ::glIsNamedStringARB = reinterpret_cast<PFNGLISNAMEDSTRINGARBPROC>( load("glIsNamedStringARB") );
    ::glGetNamedStringARB = reinterpret_cast<PFNGLGETNAMEDSTRINGARBPROC>( load("glGetNamedStringARB") );
    ::glGetNamedStringivARB = reinterpret_cast<PFNGLGETNAMEDSTRINGIVARBPROC>( load("glGetNamedStringivARB") );
    ::glTexPageCommitmentARB = reinterpret_cast<PFNGLTEXPAGECOMMITMENTARBPROC>( load("glTexPageCommitmentARB") );

    const OpenGlSupportStatus supportStatus = getOpenGlSupportStatus();

    if( !supportStatus.ARB_texture_storage ) {
        ::glTexStorage1D = &storm::glTexStorage1D;
        ::glTexStorage2D = &storm::glTexStorage2D;
        ::glTexStorage3D = &storm::glTexStorage3D;
    }

    if( !supportStatus.ARB_texture_storage_multisample ) {
        ::glTexStorage2DMultisample = &storm::glTexStorage2DMultisample;
        ::glTexStorage3DMultisample = &storm::glTexStorage3DMultisample;
    }
}

const OpenGlSupportStatus& getOpenGlSupportStatus() {
    auto loadStatus = [] {
        OpenGlSupportStatus status = { OpenGlVersion(0, 0) };

        ::glGetIntegerv( GL_MAJOR_VERSION, &status.version.first );
        checkResult( "::glGetIntegerv" );
        ::glGetIntegerv( GL_MINOR_VERSION, &status.version.second );
        checkResult( "::glGetIntegerv" );

        GLint extensionsNumber = 0;
        ::glGetIntegerv( GL_NUM_EXTENSIONS, &extensionsNumber );
        checkResult( "::glGetIntegerv" );

        const std::unordered_map<std::string_view, bool*> extensionSupport = {
            {
                "GL_ARB_buffer_storage",
                &status.ARB_buffer_storage
            },
            {
                "GL_ARB_get_program_binary",
                &status.ARB_get_program_binary
            },
            {
                "GL_ARB_invalidate_subdata",
                &status.ARB_invalidate_subdata
            },
            {
                "GL_ARB_multi_bind",
                &status.ARB_multi_bind
            },
            {
                "GL_ARB_separate_shader_objects",
                &status.ARB_separate_shader_objects
            },
            {
                "GL_ARB_texture_storage",
                &status.ARB_texture_storage
            },
            {
                "GL_ARB_texture_storage_multisample",
                &status.ARB_texture_storage_multisample
            },
            {
                "GL_ARB_timer_query",
                &status.ARB_timer_query
            },
            {
                "GL_EXT_texture_filter_anisotropic",
                &status.EXT_texture_filter_anisotropic
            },
            {
                "GL_KHR_debug",
                &status.KHR_debug
            }
        };

        for( GLint index = 0; index < extensionsNumber; ++index ) {
            const char *extensionName = reinterpret_cast<const char*>(
                ::glGetStringi(GL_EXTENSIONS, index) );
            checkResult( "::glGetStringi" );

            getSupportedExtensions( extensionName, extensionSupport );
        }

        return status;
    };

    static const OpenGlSupportStatus openGlSupportStatus = loadStatus();
    return openGlSupportStatus;
}

#ifdef _WIN32

const WglSupportStatus& getWglSupportStatus() {
    auto loadStatus = [] {
        WglSupportStatus status = {};

        const auto wglGetExtensionsStringARB =
            reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(
                load("wglGetExtensionsStringARB") );

        const std::string_view extensions =
            wglGetExtensionsStringARB ?
            wglGetExtensionsStringARB( wglGetCurrentDC() ) :
            nullptr;

        getSupportedExtensions(
            extensions,
            {
                {
                    "WGL_ARB_create_context",
                    &status.ARB_create_context
                },
                {
                    "WGL_ARB_extensions_string",
                    &status.ARB_extensions_string
                },
                {
                    "WGL_EXT_swap_control",
                    &status.EXT_swap_control
                },
                {
                    "WGL_EXT_swap_control_tear",
                    &status.EXT_swap_control_tear
                }
            });

        return status;
    };

    static const WglSupportStatus wglSupportStatus = loadStatus();
    return wglSupportStatus;
}

#endif

#ifdef __linux__

const GlxSupportStatus& getGlxSupportStatus() {
    auto loadStatus = [] {
        GlxSupportStatus status = {};

        Display *display = XOpenDisplay( nullptr );

        const std::string_view extensions =
            glXQueryExtensionsString( display, XDefaultScreen(display) );

        getSupportedExtensions(
            extensions,
            {
                {
                    "GLX_ARB_create_context",
                    &status.ARB_create_context
                },
                {
                    "GLX_EXT_swap_control",
                    &status.EXT_swap_control
                },
                {
                    "GLX_MESA_swap_control",
                    &status.MESA_swap_control
                }
            });

        XCloseDisplay( display );

        return status;
    };

    static const GlxSupportStatus glxSupportStatus = loadStatus();
    return glxSupportStatus;
}

#endif

} // namespace storm