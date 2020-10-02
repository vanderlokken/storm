#include <storm/ogl/gpu_context_ogl.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace storm {

namespace {

template <class T>
void loadApiFunction(
    T &apiFunction, const std::function<void*(std::string_view)> &loader )
{
    apiFunction.value = reinterpret_cast<typename T::Type>( loader(T::Name) );
}

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

void setBooleanOpenGlState(
    const GpuContextOgl &gpuContext, GLenum state, bool value )
{
    if( value ) {
        gpuContext.call<GlEnable>( state );
    } else {
        gpuContext.call<GlDisable>( state );
    }
}

GpuContextOgl::GpuContextOgl() :
    _threadId( std::this_thread::get_id() )
{
}

void GpuContextOgl::loadApiFunctions(
    const std::function<void*(std::string_view)> &loader )
{
    loadApiFunction( _glCullFace, loader );
    loadApiFunction( _glFrontFace, loader );
    loadApiFunction( _glHint, loader );
    loadApiFunction( _glLineWidth, loader );
    loadApiFunction( _glPointSize, loader );
    loadApiFunction( _glPolygonMode, loader );
    loadApiFunction( _glScissor, loader );
    loadApiFunction( _glTexParameterf, loader );
    loadApiFunction( _glTexParameterfv, loader );
    loadApiFunction( _glTexParameteri, loader );
    loadApiFunction( _glTexParameteriv, loader );
    loadApiFunction( _glTexImage1D, loader );
    loadApiFunction( _glTexImage2D, loader );
    loadApiFunction( _glDrawBuffer, loader );
    loadApiFunction( _glClear, loader );
    loadApiFunction( _glClearColor, loader );
    loadApiFunction( _glClearStencil, loader );
    loadApiFunction( _glClearDepth, loader );
    loadApiFunction( _glStencilMask, loader );
    loadApiFunction( _glColorMask, loader );
    loadApiFunction( _glDepthMask, loader );
    loadApiFunction( _glDisable, loader );
    loadApiFunction( _glEnable, loader );
    loadApiFunction( _glFinish, loader );
    loadApiFunction( _glFlush, loader );
    loadApiFunction( _glBlendFunc, loader );
    loadApiFunction( _glLogicOp, loader );
    loadApiFunction( _glStencilFunc, loader );
    loadApiFunction( _glStencilOp, loader );
    loadApiFunction( _glDepthFunc, loader );
    loadApiFunction( _glPixelStoref, loader );
    loadApiFunction( _glPixelStorei, loader );
    loadApiFunction( _glReadBuffer, loader );
    loadApiFunction( _glReadPixels, loader );
    loadApiFunction( _glGetBooleanv, loader );
    loadApiFunction( _glGetDoublev, loader );
    loadApiFunction( _glGetError, loader );
    loadApiFunction( _glGetFloatv, loader );
    loadApiFunction( _glGetIntegerv, loader );
    loadApiFunction( _glGetString, loader );
    loadApiFunction( _glGetTexImage, loader );
    loadApiFunction( _glGetTexParameterfv, loader );
    loadApiFunction( _glGetTexParameteriv, loader );
    loadApiFunction( _glGetTexLevelParameterfv, loader );
    loadApiFunction( _glGetTexLevelParameteriv, loader );
    loadApiFunction( _glIsEnabled, loader );
    loadApiFunction( _glDepthRange, loader );
    loadApiFunction( _glViewport, loader );
    loadApiFunction( _glDrawArrays, loader );
    loadApiFunction( _glDrawElements, loader );
    loadApiFunction( _glGetPointerv, loader );
    loadApiFunction( _glPolygonOffset, loader );
    loadApiFunction( _glCopyTexImage1D, loader );
    loadApiFunction( _glCopyTexImage2D, loader );
    loadApiFunction( _glCopyTexSubImage1D, loader );
    loadApiFunction( _glCopyTexSubImage2D, loader );
    loadApiFunction( _glTexSubImage1D, loader );
    loadApiFunction( _glTexSubImage2D, loader );
    loadApiFunction( _glBindTexture, loader );
    loadApiFunction( _glDeleteTextures, loader );
    loadApiFunction( _glGenTextures, loader );
    loadApiFunction( _glIsTexture, loader );
    loadApiFunction( _glDrawRangeElements, loader );
    loadApiFunction( _glTexImage3D, loader );
    loadApiFunction( _glTexSubImage3D, loader );
    loadApiFunction( _glCopyTexSubImage3D, loader );
    loadApiFunction( _glActiveTexture, loader );
    loadApiFunction( _glSampleCoverage, loader );
    loadApiFunction( _glCompressedTexImage3D, loader );
    loadApiFunction( _glCompressedTexImage2D, loader );
    loadApiFunction( _glCompressedTexImage1D, loader );
    loadApiFunction( _glCompressedTexSubImage3D, loader );
    loadApiFunction( _glCompressedTexSubImage2D, loader );
    loadApiFunction( _glCompressedTexSubImage1D, loader );
    loadApiFunction( _glGetCompressedTexImage, loader );
    loadApiFunction( _glBlendFuncSeparate, loader );
    loadApiFunction( _glMultiDrawArrays, loader );
    loadApiFunction( _glMultiDrawElements, loader );
    loadApiFunction( _glPointParameterf, loader );
    loadApiFunction( _glPointParameterfv, loader );
    loadApiFunction( _glPointParameteri, loader );
    loadApiFunction( _glPointParameteriv, loader );
    loadApiFunction( _glBlendColor, loader );
    loadApiFunction( _glBlendEquation, loader );
    loadApiFunction( _glGenQueries, loader );
    loadApiFunction( _glDeleteQueries, loader );
    loadApiFunction( _glIsQuery, loader );
    loadApiFunction( _glBeginQuery, loader );
    loadApiFunction( _glEndQuery, loader );
    loadApiFunction( _glGetQueryiv, loader );
    loadApiFunction( _glGetQueryObjectiv, loader );
    loadApiFunction( _glGetQueryObjectuiv, loader );
    loadApiFunction( _glBindBuffer, loader );
    loadApiFunction( _glDeleteBuffers, loader );
    loadApiFunction( _glGenBuffers, loader );
    loadApiFunction( _glIsBuffer, loader );
    loadApiFunction( _glBufferData, loader );
    loadApiFunction( _glBufferSubData, loader );
    loadApiFunction( _glGetBufferSubData, loader );
    loadApiFunction( _glMapBuffer, loader );
    loadApiFunction( _glUnmapBuffer, loader );
    loadApiFunction( _glGetBufferParameteriv, loader );
    loadApiFunction( _glGetBufferPointerv, loader );
    loadApiFunction( _glBlendEquationSeparate, loader );
    loadApiFunction( _glDrawBuffers, loader );
    loadApiFunction( _glStencilOpSeparate, loader );
    loadApiFunction( _glStencilFuncSeparate, loader );
    loadApiFunction( _glStencilMaskSeparate, loader );
    loadApiFunction( _glAttachShader, loader );
    loadApiFunction( _glBindAttribLocation, loader );
    loadApiFunction( _glCompileShader, loader );
    loadApiFunction( _glCreateProgram, loader );
    loadApiFunction( _glCreateShader, loader );
    loadApiFunction( _glDeleteProgram, loader );
    loadApiFunction( _glDeleteShader, loader );
    loadApiFunction( _glDetachShader, loader );
    loadApiFunction( _glDisableVertexAttribArray, loader );
    loadApiFunction( _glEnableVertexAttribArray, loader );
    loadApiFunction( _glGetActiveAttrib, loader );
    loadApiFunction( _glGetActiveUniform, loader );
    loadApiFunction( _glGetAttachedShaders, loader );
    loadApiFunction( _glGetAttribLocation, loader );
    loadApiFunction( _glGetProgramiv, loader );
    loadApiFunction( _glGetProgramInfoLog, loader );
    loadApiFunction( _glGetShaderiv, loader );
    loadApiFunction( _glGetShaderInfoLog, loader );
    loadApiFunction( _glGetShaderSource, loader );
    loadApiFunction( _glGetUniformLocation, loader );
    loadApiFunction( _glGetUniformfv, loader );
    loadApiFunction( _glGetUniformiv, loader );
    loadApiFunction( _glGetVertexAttribdv, loader );
    loadApiFunction( _glGetVertexAttribfv, loader );
    loadApiFunction( _glGetVertexAttribiv, loader );
    loadApiFunction( _glGetVertexAttribPointerv, loader );
    loadApiFunction( _glIsProgram, loader );
    loadApiFunction( _glIsShader, loader );
    loadApiFunction( _glLinkProgram, loader );
    loadApiFunction( _glShaderSource, loader );
    loadApiFunction( _glUseProgram, loader );
    loadApiFunction( _glUniform1f, loader );
    loadApiFunction( _glUniform2f, loader );
    loadApiFunction( _glUniform3f, loader );
    loadApiFunction( _glUniform4f, loader );
    loadApiFunction( _glUniform1i, loader );
    loadApiFunction( _glUniform2i, loader );
    loadApiFunction( _glUniform3i, loader );
    loadApiFunction( _glUniform4i, loader );
    loadApiFunction( _glUniform1fv, loader );
    loadApiFunction( _glUniform2fv, loader );
    loadApiFunction( _glUniform3fv, loader );
    loadApiFunction( _glUniform4fv, loader );
    loadApiFunction( _glUniform1iv, loader );
    loadApiFunction( _glUniform2iv, loader );
    loadApiFunction( _glUniform3iv, loader );
    loadApiFunction( _glUniform4iv, loader );
    loadApiFunction( _glUniformMatrix2fv, loader );
    loadApiFunction( _glUniformMatrix3fv, loader );
    loadApiFunction( _glUniformMatrix4fv, loader );
    loadApiFunction( _glValidateProgram, loader );
    loadApiFunction( _glVertexAttrib1d, loader );
    loadApiFunction( _glVertexAttrib1dv, loader );
    loadApiFunction( _glVertexAttrib1f, loader );
    loadApiFunction( _glVertexAttrib1fv, loader );
    loadApiFunction( _glVertexAttrib1s, loader );
    loadApiFunction( _glVertexAttrib1sv, loader );
    loadApiFunction( _glVertexAttrib2d, loader );
    loadApiFunction( _glVertexAttrib2dv, loader );
    loadApiFunction( _glVertexAttrib2f, loader );
    loadApiFunction( _glVertexAttrib2fv, loader );
    loadApiFunction( _glVertexAttrib2s, loader );
    loadApiFunction( _glVertexAttrib2sv, loader );
    loadApiFunction( _glVertexAttrib3d, loader );
    loadApiFunction( _glVertexAttrib3dv, loader );
    loadApiFunction( _glVertexAttrib3f, loader );
    loadApiFunction( _glVertexAttrib3fv, loader );
    loadApiFunction( _glVertexAttrib3s, loader );
    loadApiFunction( _glVertexAttrib3sv, loader );
    loadApiFunction( _glVertexAttrib4Nbv, loader );
    loadApiFunction( _glVertexAttrib4Niv, loader );
    loadApiFunction( _glVertexAttrib4Nsv, loader );
    loadApiFunction( _glVertexAttrib4Nub, loader );
    loadApiFunction( _glVertexAttrib4Nubv, loader );
    loadApiFunction( _glVertexAttrib4Nuiv, loader );
    loadApiFunction( _glVertexAttrib4Nusv, loader );
    loadApiFunction( _glVertexAttrib4bv, loader );
    loadApiFunction( _glVertexAttrib4d, loader );
    loadApiFunction( _glVertexAttrib4dv, loader );
    loadApiFunction( _glVertexAttrib4f, loader );
    loadApiFunction( _glVertexAttrib4fv, loader );
    loadApiFunction( _glVertexAttrib4iv, loader );
    loadApiFunction( _glVertexAttrib4s, loader );
    loadApiFunction( _glVertexAttrib4sv, loader );
    loadApiFunction( _glVertexAttrib4ubv, loader );
    loadApiFunction( _glVertexAttrib4uiv, loader );
    loadApiFunction( _glVertexAttrib4usv, loader );
    loadApiFunction( _glVertexAttribPointer, loader );
    loadApiFunction( _glUniformMatrix2x3fv, loader );
    loadApiFunction( _glUniformMatrix3x2fv, loader );
    loadApiFunction( _glUniformMatrix2x4fv, loader );
    loadApiFunction( _glUniformMatrix4x2fv, loader );
    loadApiFunction( _glUniformMatrix3x4fv, loader );
    loadApiFunction( _glUniformMatrix4x3fv, loader );
    loadApiFunction( _glColorMaski, loader );
    loadApiFunction( _glGetBooleani_v, loader );
    loadApiFunction( _glGetIntegeri_v, loader );
    loadApiFunction( _glEnablei, loader );
    loadApiFunction( _glDisablei, loader );
    loadApiFunction( _glIsEnabledi, loader );
    loadApiFunction( _glBeginTransformFeedback, loader );
    loadApiFunction( _glEndTransformFeedback, loader );
    loadApiFunction( _glBindBufferRange, loader );
    loadApiFunction( _glBindBufferBase, loader );
    loadApiFunction( _glTransformFeedbackVaryings, loader );
    loadApiFunction( _glGetTransformFeedbackVarying, loader );
    loadApiFunction( _glClampColor, loader );
    loadApiFunction( _glBeginConditionalRender, loader );
    loadApiFunction( _glEndConditionalRender, loader );
    loadApiFunction( _glVertexAttribIPointer, loader );
    loadApiFunction( _glGetVertexAttribIiv, loader );
    loadApiFunction( _glGetVertexAttribIuiv, loader );
    loadApiFunction( _glVertexAttribI1i, loader );
    loadApiFunction( _glVertexAttribI2i, loader );
    loadApiFunction( _glVertexAttribI3i, loader );
    loadApiFunction( _glVertexAttribI4i, loader );
    loadApiFunction( _glVertexAttribI1ui, loader );
    loadApiFunction( _glVertexAttribI2ui, loader );
    loadApiFunction( _glVertexAttribI3ui, loader );
    loadApiFunction( _glVertexAttribI4ui, loader );
    loadApiFunction( _glVertexAttribI1iv, loader );
    loadApiFunction( _glVertexAttribI2iv, loader );
    loadApiFunction( _glVertexAttribI3iv, loader );
    loadApiFunction( _glVertexAttribI4iv, loader );
    loadApiFunction( _glVertexAttribI1uiv, loader );
    loadApiFunction( _glVertexAttribI2uiv, loader );
    loadApiFunction( _glVertexAttribI3uiv, loader );
    loadApiFunction( _glVertexAttribI4uiv, loader );
    loadApiFunction( _glVertexAttribI4bv, loader );
    loadApiFunction( _glVertexAttribI4sv, loader );
    loadApiFunction( _glVertexAttribI4ubv, loader );
    loadApiFunction( _glVertexAttribI4usv, loader );
    loadApiFunction( _glGetUniformuiv, loader );
    loadApiFunction( _glBindFragDataLocation, loader );
    loadApiFunction( _glGetFragDataLocation, loader );
    loadApiFunction( _glUniform1ui, loader );
    loadApiFunction( _glUniform2ui, loader );
    loadApiFunction( _glUniform3ui, loader );
    loadApiFunction( _glUniform4ui, loader );
    loadApiFunction( _glUniform1uiv, loader );
    loadApiFunction( _glUniform2uiv, loader );
    loadApiFunction( _glUniform3uiv, loader );
    loadApiFunction( _glUniform4uiv, loader );
    loadApiFunction( _glTexParameterIiv, loader );
    loadApiFunction( _glTexParameterIuiv, loader );
    loadApiFunction( _glGetTexParameterIiv, loader );
    loadApiFunction( _glGetTexParameterIuiv, loader );
    loadApiFunction( _glClearBufferiv, loader );
    loadApiFunction( _glClearBufferuiv, loader );
    loadApiFunction( _glClearBufferfv, loader );
    loadApiFunction( _glClearBufferfi, loader );
    loadApiFunction( _glGetStringi, loader );
    loadApiFunction( _glIsRenderbuffer, loader );
    loadApiFunction( _glBindRenderbuffer, loader );
    loadApiFunction( _glDeleteRenderbuffers, loader );
    loadApiFunction( _glGenRenderbuffers, loader );
    loadApiFunction( _glRenderbufferStorage, loader );
    loadApiFunction( _glGetRenderbufferParameteriv, loader );
    loadApiFunction( _glIsFramebuffer, loader );
    loadApiFunction( _glBindFramebuffer, loader );
    loadApiFunction( _glDeleteFramebuffers, loader );
    loadApiFunction( _glGenFramebuffers, loader );
    loadApiFunction( _glCheckFramebufferStatus, loader );
    loadApiFunction( _glFramebufferTexture1D, loader );
    loadApiFunction( _glFramebufferTexture2D, loader );
    loadApiFunction( _glFramebufferTexture3D, loader );
    loadApiFunction( _glFramebufferRenderbuffer, loader );
    loadApiFunction( _glGetFramebufferAttachmentParameteriv, loader );
    loadApiFunction( _glGenerateMipmap, loader );
    loadApiFunction( _glBlitFramebuffer, loader );
    loadApiFunction( _glRenderbufferStorageMultisample, loader );
    loadApiFunction( _glFramebufferTextureLayer, loader );
    loadApiFunction( _glMapBufferRange, loader );
    loadApiFunction( _glFlushMappedBufferRange, loader );
    loadApiFunction( _glBindVertexArray, loader );
    loadApiFunction( _glDeleteVertexArrays, loader );
    loadApiFunction( _glGenVertexArrays, loader );
    loadApiFunction( _glIsVertexArray, loader );
    loadApiFunction( _glDrawArraysInstanced, loader );
    loadApiFunction( _glDrawElementsInstanced, loader );
    loadApiFunction( _glTexBuffer, loader );
    loadApiFunction( _glPrimitiveRestartIndex, loader );
    loadApiFunction( _glCopyBufferSubData, loader );
    loadApiFunction( _glGetUniformIndices, loader );
    loadApiFunction( _glGetActiveUniformsiv, loader );
    loadApiFunction( _glGetActiveUniformName, loader );
    loadApiFunction( _glGetUniformBlockIndex, loader );
    loadApiFunction( _glGetActiveUniformBlockiv, loader );
    loadApiFunction( _glGetActiveUniformBlockName, loader );
    loadApiFunction( _glUniformBlockBinding, loader );
    loadApiFunction( _glDrawElementsBaseVertex, loader );
    loadApiFunction( _glDrawRangeElementsBaseVertex, loader );
    loadApiFunction( _glDrawElementsInstancedBaseVertex, loader );
    loadApiFunction( _glMultiDrawElementsBaseVertex, loader );
    loadApiFunction( _glProvokingVertex, loader );
    loadApiFunction( _glFenceSync, loader );
    loadApiFunction( _glIsSync, loader );
    loadApiFunction( _glDeleteSync, loader );
    loadApiFunction( _glClientWaitSync, loader );
    loadApiFunction( _glWaitSync, loader );
    loadApiFunction( _glGetInteger64v, loader );
    loadApiFunction( _glGetSynciv, loader );
    loadApiFunction( _glGetInteger64i_v, loader );
    loadApiFunction( _glGetBufferParameteri64v, loader );
    loadApiFunction( _glFramebufferTexture, loader );
    loadApiFunction( _glTexImage2DMultisample, loader );
    loadApiFunction( _glTexImage3DMultisample, loader );
    loadApiFunction( _glGetMultisamplefv, loader );
    loadApiFunction( _glSampleMaski, loader );
    loadApiFunction( _glBindFragDataLocationIndexed, loader );
    loadApiFunction( _glGetFragDataIndex, loader );
    loadApiFunction( _glGenSamplers, loader );
    loadApiFunction( _glDeleteSamplers, loader );
    loadApiFunction( _glIsSampler, loader );
    loadApiFunction( _glBindSampler, loader );
    loadApiFunction( _glSamplerParameteri, loader );
    loadApiFunction( _glSamplerParameteriv, loader );
    loadApiFunction( _glSamplerParameterf, loader );
    loadApiFunction( _glSamplerParameterfv, loader );
    loadApiFunction( _glSamplerParameterIiv, loader );
    loadApiFunction( _glSamplerParameterIuiv, loader );
    loadApiFunction( _glGetSamplerParameteriv, loader );
    loadApiFunction( _glGetSamplerParameterIiv, loader );
    loadApiFunction( _glGetSamplerParameterfv, loader );
    loadApiFunction( _glGetSamplerParameterIuiv, loader );
    loadApiFunction( _glQueryCounter, loader );
    loadApiFunction( _glGetQueryObjecti64v, loader );
    loadApiFunction( _glGetQueryObjectui64v, loader );
    loadApiFunction( _glVertexAttribDivisor, loader );
    loadApiFunction( _glVertexAttribP1ui, loader );
    loadApiFunction( _glVertexAttribP1uiv, loader );
    loadApiFunction( _glVertexAttribP2ui, loader );
    loadApiFunction( _glVertexAttribP2uiv, loader );
    loadApiFunction( _glVertexAttribP3ui, loader );
    loadApiFunction( _glVertexAttribP3uiv, loader );
    loadApiFunction( _glVertexAttribP4ui, loader );
    loadApiFunction( _glVertexAttribP4uiv, loader );
    loadApiFunction( _glMinSampleShading, loader );
    loadApiFunction( _glBlendEquationi, loader );
    loadApiFunction( _glBlendEquationSeparatei, loader );
    loadApiFunction( _glBlendFunci, loader );
    loadApiFunction( _glBlendFuncSeparatei, loader );
    loadApiFunction( _glDrawArraysIndirect, loader );
    loadApiFunction( _glDrawElementsIndirect, loader );
    loadApiFunction( _glUniform1d, loader );
    loadApiFunction( _glUniform2d, loader );
    loadApiFunction( _glUniform3d, loader );
    loadApiFunction( _glUniform4d, loader );
    loadApiFunction( _glUniform1dv, loader );
    loadApiFunction( _glUniform2dv, loader );
    loadApiFunction( _glUniform3dv, loader );
    loadApiFunction( _glUniform4dv, loader );
    loadApiFunction( _glUniformMatrix2dv, loader );
    loadApiFunction( _glUniformMatrix3dv, loader );
    loadApiFunction( _glUniformMatrix4dv, loader );
    loadApiFunction( _glUniformMatrix2x3dv, loader );
    loadApiFunction( _glUniformMatrix2x4dv, loader );
    loadApiFunction( _glUniformMatrix3x2dv, loader );
    loadApiFunction( _glUniformMatrix3x4dv, loader );
    loadApiFunction( _glUniformMatrix4x2dv, loader );
    loadApiFunction( _glUniformMatrix4x3dv, loader );
    loadApiFunction( _glGetUniformdv, loader );
    loadApiFunction( _glGetSubroutineUniformLocation, loader );
    loadApiFunction( _glGetSubroutineIndex, loader );
    loadApiFunction( _glGetActiveSubroutineUniformiv, loader );
    loadApiFunction( _glGetActiveSubroutineUniformName, loader );
    loadApiFunction( _glGetActiveSubroutineName, loader );
    loadApiFunction( _glUniformSubroutinesuiv, loader );
    loadApiFunction( _glGetUniformSubroutineuiv, loader );
    loadApiFunction( _glGetProgramStageiv, loader );
    loadApiFunction( _glPatchParameteri, loader );
    loadApiFunction( _glPatchParameterfv, loader );
    loadApiFunction( _glBindTransformFeedback, loader );
    loadApiFunction( _glDeleteTransformFeedbacks, loader );
    loadApiFunction( _glGenTransformFeedbacks, loader );
    loadApiFunction( _glIsTransformFeedback, loader );
    loadApiFunction( _glPauseTransformFeedback, loader );
    loadApiFunction( _glResumeTransformFeedback, loader );
    loadApiFunction( _glDrawTransformFeedback, loader );
    loadApiFunction( _glDrawTransformFeedbackStream, loader );
    loadApiFunction( _glBeginQueryIndexed, loader );
    loadApiFunction( _glEndQueryIndexed, loader );
    loadApiFunction( _glGetQueryIndexediv, loader );
    loadApiFunction( _glReleaseShaderCompiler, loader );
    loadApiFunction( _glShaderBinary, loader );
    loadApiFunction( _glGetShaderPrecisionFormat, loader );
    loadApiFunction( _glDepthRangef, loader );
    loadApiFunction( _glClearDepthf, loader );
    loadApiFunction( _glGetProgramBinary, loader );
    loadApiFunction( _glProgramBinary, loader );
    loadApiFunction( _glProgramParameteri, loader );
    loadApiFunction( _glUseProgramStages, loader );
    loadApiFunction( _glActiveShaderProgram, loader );
    loadApiFunction( _glCreateShaderProgramv, loader );
    loadApiFunction( _glBindProgramPipeline, loader );
    loadApiFunction( _glDeleteProgramPipelines, loader );
    loadApiFunction( _glGenProgramPipelines, loader );
    loadApiFunction( _glIsProgramPipeline, loader );
    loadApiFunction( _glGetProgramPipelineiv, loader );
    loadApiFunction( _glProgramUniform1i, loader );
    loadApiFunction( _glProgramUniform1iv, loader );
    loadApiFunction( _glProgramUniform1f, loader );
    loadApiFunction( _glProgramUniform1fv, loader );
    loadApiFunction( _glProgramUniform1d, loader );
    loadApiFunction( _glProgramUniform1dv, loader );
    loadApiFunction( _glProgramUniform1ui, loader );
    loadApiFunction( _glProgramUniform1uiv, loader );
    loadApiFunction( _glProgramUniform2i, loader );
    loadApiFunction( _glProgramUniform2iv, loader );
    loadApiFunction( _glProgramUniform2f, loader );
    loadApiFunction( _glProgramUniform2fv, loader );
    loadApiFunction( _glProgramUniform2d, loader );
    loadApiFunction( _glProgramUniform2dv, loader );
    loadApiFunction( _glProgramUniform2ui, loader );
    loadApiFunction( _glProgramUniform2uiv, loader );
    loadApiFunction( _glProgramUniform3i, loader );
    loadApiFunction( _glProgramUniform3iv, loader );
    loadApiFunction( _glProgramUniform3f, loader );
    loadApiFunction( _glProgramUniform3fv, loader );
    loadApiFunction( _glProgramUniform3d, loader );
    loadApiFunction( _glProgramUniform3dv, loader );
    loadApiFunction( _glProgramUniform3ui, loader );
    loadApiFunction( _glProgramUniform3uiv, loader );
    loadApiFunction( _glProgramUniform4i, loader );
    loadApiFunction( _glProgramUniform4iv, loader );
    loadApiFunction( _glProgramUniform4f, loader );
    loadApiFunction( _glProgramUniform4fv, loader );
    loadApiFunction( _glProgramUniform4d, loader );
    loadApiFunction( _glProgramUniform4dv, loader );
    loadApiFunction( _glProgramUniform4ui, loader );
    loadApiFunction( _glProgramUniform4uiv, loader );
    loadApiFunction( _glProgramUniformMatrix2fv, loader );
    loadApiFunction( _glProgramUniformMatrix3fv, loader );
    loadApiFunction( _glProgramUniformMatrix4fv, loader );
    loadApiFunction( _glProgramUniformMatrix2dv, loader );
    loadApiFunction( _glProgramUniformMatrix3dv, loader );
    loadApiFunction( _glProgramUniformMatrix4dv, loader );
    loadApiFunction( _glProgramUniformMatrix2x3fv, loader );
    loadApiFunction( _glProgramUniformMatrix3x2fv, loader );
    loadApiFunction( _glProgramUniformMatrix2x4fv, loader );
    loadApiFunction( _glProgramUniformMatrix4x2fv, loader );
    loadApiFunction( _glProgramUniformMatrix3x4fv, loader );
    loadApiFunction( _glProgramUniformMatrix4x3fv, loader );
    loadApiFunction( _glProgramUniformMatrix2x3dv, loader );
    loadApiFunction( _glProgramUniformMatrix3x2dv, loader );
    loadApiFunction( _glProgramUniformMatrix2x4dv, loader );
    loadApiFunction( _glProgramUniformMatrix4x2dv, loader );
    loadApiFunction( _glProgramUniformMatrix3x4dv, loader );
    loadApiFunction( _glProgramUniformMatrix4x3dv, loader );
    loadApiFunction( _glValidateProgramPipeline, loader );
    loadApiFunction( _glGetProgramPipelineInfoLog, loader );
    loadApiFunction( _glVertexAttribL1d, loader );
    loadApiFunction( _glVertexAttribL2d, loader );
    loadApiFunction( _glVertexAttribL3d, loader );
    loadApiFunction( _glVertexAttribL4d, loader );
    loadApiFunction( _glVertexAttribL1dv, loader );
    loadApiFunction( _glVertexAttribL2dv, loader );
    loadApiFunction( _glVertexAttribL3dv, loader );
    loadApiFunction( _glVertexAttribL4dv, loader );
    loadApiFunction( _glVertexAttribLPointer, loader );
    loadApiFunction( _glGetVertexAttribLdv, loader );
    loadApiFunction( _glViewportArrayv, loader );
    loadApiFunction( _glViewportIndexedf, loader );
    loadApiFunction( _glViewportIndexedfv, loader );
    loadApiFunction( _glScissorArrayv, loader );
    loadApiFunction( _glScissorIndexed, loader );
    loadApiFunction( _glScissorIndexedv, loader );
    loadApiFunction( _glDepthRangeArrayv, loader );
    loadApiFunction( _glDepthRangeIndexed, loader );
    loadApiFunction( _glGetFloati_v, loader );
    loadApiFunction( _glGetDoublei_v, loader );
    loadApiFunction( _glDrawArraysInstancedBaseInstance, loader );
    loadApiFunction( _glDrawElementsInstancedBaseInstance, loader );
    loadApiFunction( _glDrawElementsInstancedBaseVertexBaseInstance, loader );
    loadApiFunction( _glGetInternalformativ, loader );
    loadApiFunction( _glGetActiveAtomicCounterBufferiv, loader );
    loadApiFunction( _glBindImageTexture, loader );
    loadApiFunction( _glMemoryBarrier, loader );
    loadApiFunction( _glTexStorage1D, loader );
    loadApiFunction( _glTexStorage2D, loader );
    loadApiFunction( _glTexStorage3D, loader );
    loadApiFunction( _glDrawTransformFeedbackInstanced, loader );
    loadApiFunction( _glDrawTransformFeedbackStreamInstanced, loader );
    loadApiFunction( _glClearBufferData, loader );
    loadApiFunction( _glClearBufferSubData, loader );
    loadApiFunction( _glDispatchCompute, loader );
    loadApiFunction( _glDispatchComputeIndirect, loader );
    loadApiFunction( _glCopyImageSubData, loader );
    loadApiFunction( _glFramebufferParameteri, loader );
    loadApiFunction( _glGetFramebufferParameteriv, loader );
    loadApiFunction( _glGetInternalformati64v, loader );
    loadApiFunction( _glInvalidateTexSubImage, loader );
    loadApiFunction( _glInvalidateTexImage, loader );
    loadApiFunction( _glInvalidateBufferSubData, loader );
    loadApiFunction( _glInvalidateBufferData, loader );
    loadApiFunction( _glInvalidateFramebuffer, loader );
    loadApiFunction( _glInvalidateSubFramebuffer, loader );
    loadApiFunction( _glMultiDrawArraysIndirect, loader );
    loadApiFunction( _glMultiDrawElementsIndirect, loader );
    loadApiFunction( _glGetProgramInterfaceiv, loader );
    loadApiFunction( _glGetProgramResourceIndex, loader );
    loadApiFunction( _glGetProgramResourceName, loader );
    loadApiFunction( _glGetProgramResourceiv, loader );
    loadApiFunction( _glGetProgramResourceLocation, loader );
    loadApiFunction( _glGetProgramResourceLocationIndex, loader );
    loadApiFunction( _glShaderStorageBlockBinding, loader );
    loadApiFunction( _glTexBufferRange, loader );
    loadApiFunction( _glTexStorage2DMultisample, loader );
    loadApiFunction( _glTexStorage3DMultisample, loader );
    loadApiFunction( _glTextureView, loader );
    loadApiFunction( _glBindVertexBuffer, loader );
    loadApiFunction( _glVertexAttribFormat, loader );
    loadApiFunction( _glVertexAttribIFormat, loader );
    loadApiFunction( _glVertexAttribLFormat, loader );
    loadApiFunction( _glVertexAttribBinding, loader );
    loadApiFunction( _glVertexBindingDivisor, loader );
    loadApiFunction( _glDebugMessageControl, loader );
    loadApiFunction( _glDebugMessageInsert, loader );
    loadApiFunction( _glDebugMessageCallback, loader );
    loadApiFunction( _glGetDebugMessageLog, loader );
    loadApiFunction( _glPushDebugGroup, loader );
    loadApiFunction( _glPopDebugGroup, loader );
    loadApiFunction( _glObjectLabel, loader );
    loadApiFunction( _glGetObjectLabel, loader );
    loadApiFunction( _glObjectPtrLabel, loader );
    loadApiFunction( _glGetObjectPtrLabel, loader );
    loadApiFunction( _glBufferStorage, loader );
    loadApiFunction( _glClearTexImage, loader );
    loadApiFunction( _glClearTexSubImage, loader );
    loadApiFunction( _glBindBuffersBase, loader );
    loadApiFunction( _glBindBuffersRange, loader );
    loadApiFunction( _glBindTextures, loader );
    loadApiFunction( _glBindSamplers, loader );
    loadApiFunction( _glBindImageTextures, loader );
    loadApiFunction( _glBindVertexBuffers, loader );
    loadApiFunction( _glClipControl, loader );
    loadApiFunction( _glCreateTransformFeedbacks, loader );
    loadApiFunction( _glTransformFeedbackBufferBase, loader );
    loadApiFunction( _glTransformFeedbackBufferRange, loader );
    loadApiFunction( _glGetTransformFeedbackiv, loader );
    loadApiFunction( _glGetTransformFeedbacki_v, loader );
    loadApiFunction( _glGetTransformFeedbacki64_v, loader );
    loadApiFunction( _glCreateBuffers, loader );
    loadApiFunction( _glNamedBufferStorage, loader );
    loadApiFunction( _glNamedBufferData, loader );
    loadApiFunction( _glNamedBufferSubData, loader );
    loadApiFunction( _glCopyNamedBufferSubData, loader );
    loadApiFunction( _glClearNamedBufferData, loader );
    loadApiFunction( _glClearNamedBufferSubData, loader );
    loadApiFunction( _glMapNamedBuffer, loader );
    loadApiFunction( _glMapNamedBufferRange, loader );
    loadApiFunction( _glUnmapNamedBuffer, loader );
    loadApiFunction( _glFlushMappedNamedBufferRange, loader );
    loadApiFunction( _glGetNamedBufferParameteriv, loader );
    loadApiFunction( _glGetNamedBufferParameteri64v, loader );
    loadApiFunction( _glGetNamedBufferPointerv, loader );
    loadApiFunction( _glGetNamedBufferSubData, loader );
    loadApiFunction( _glCreateFramebuffers, loader );
    loadApiFunction( _glNamedFramebufferRenderbuffer, loader );
    loadApiFunction( _glNamedFramebufferParameteri, loader );
    loadApiFunction( _glNamedFramebufferTexture, loader );
    loadApiFunction( _glNamedFramebufferTextureLayer, loader );
    loadApiFunction( _glNamedFramebufferDrawBuffer, loader );
    loadApiFunction( _glNamedFramebufferDrawBuffers, loader );
    loadApiFunction( _glNamedFramebufferReadBuffer, loader );
    loadApiFunction( _glInvalidateNamedFramebufferData, loader );
    loadApiFunction( _glInvalidateNamedFramebufferSubData, loader );
    loadApiFunction( _glClearNamedFramebufferiv, loader );
    loadApiFunction( _glClearNamedFramebufferuiv, loader );
    loadApiFunction( _glClearNamedFramebufferfv, loader );
    loadApiFunction( _glClearNamedFramebufferfi, loader );
    loadApiFunction( _glBlitNamedFramebuffer, loader );
    loadApiFunction( _glCheckNamedFramebufferStatus, loader );
    loadApiFunction( _glGetNamedFramebufferParameteriv, loader );
    loadApiFunction( _glGetNamedFramebufferAttachmentParameteriv, loader );
    loadApiFunction( _glCreateRenderbuffers, loader );
    loadApiFunction( _glNamedRenderbufferStorage, loader );
    loadApiFunction( _glNamedRenderbufferStorageMultisample, loader );
    loadApiFunction( _glGetNamedRenderbufferParameteriv, loader );
    loadApiFunction( _glCreateTextures, loader );
    loadApiFunction( _glTextureBuffer, loader );
    loadApiFunction( _glTextureBufferRange, loader );
    loadApiFunction( _glTextureStorage1D, loader );
    loadApiFunction( _glTextureStorage2D, loader );
    loadApiFunction( _glTextureStorage3D, loader );
    loadApiFunction( _glTextureStorage2DMultisample, loader );
    loadApiFunction( _glTextureStorage3DMultisample, loader );
    loadApiFunction( _glTextureSubImage1D, loader );
    loadApiFunction( _glTextureSubImage2D, loader );
    loadApiFunction( _glTextureSubImage3D, loader );
    loadApiFunction( _glCompressedTextureSubImage1D, loader );
    loadApiFunction( _glCompressedTextureSubImage2D, loader );
    loadApiFunction( _glCompressedTextureSubImage3D, loader );
    loadApiFunction( _glCopyTextureSubImage1D, loader );
    loadApiFunction( _glCopyTextureSubImage2D, loader );
    loadApiFunction( _glCopyTextureSubImage3D, loader );
    loadApiFunction( _glTextureParameterf, loader );
    loadApiFunction( _glTextureParameterfv, loader );
    loadApiFunction( _glTextureParameteri, loader );
    loadApiFunction( _glTextureParameterIiv, loader );
    loadApiFunction( _glTextureParameterIuiv, loader );
    loadApiFunction( _glTextureParameteriv, loader );
    loadApiFunction( _glGenerateTextureMipmap, loader );
    loadApiFunction( _glBindTextureUnit, loader );
    loadApiFunction( _glGetTextureImage, loader );
    loadApiFunction( _glGetCompressedTextureImage, loader );
    loadApiFunction( _glGetTextureLevelParameterfv, loader );
    loadApiFunction( _glGetTextureLevelParameteriv, loader );
    loadApiFunction( _glGetTextureParameterfv, loader );
    loadApiFunction( _glGetTextureParameterIiv, loader );
    loadApiFunction( _glGetTextureParameterIuiv, loader );
    loadApiFunction( _glGetTextureParameteriv, loader );
    loadApiFunction( _glCreateVertexArrays, loader );
    loadApiFunction( _glDisableVertexArrayAttrib, loader );
    loadApiFunction( _glEnableVertexArrayAttrib, loader );
    loadApiFunction( _glVertexArrayElementBuffer, loader );
    loadApiFunction( _glVertexArrayVertexBuffer, loader );
    loadApiFunction( _glVertexArrayVertexBuffers, loader );
    loadApiFunction( _glVertexArrayAttribBinding, loader );
    loadApiFunction( _glVertexArrayAttribFormat, loader );
    loadApiFunction( _glVertexArrayAttribIFormat, loader );
    loadApiFunction( _glVertexArrayAttribLFormat, loader );
    loadApiFunction( _glVertexArrayBindingDivisor, loader );
    loadApiFunction( _glGetVertexArrayiv, loader );
    loadApiFunction( _glGetVertexArrayIndexediv, loader );
    loadApiFunction( _glGetVertexArrayIndexed64iv, loader );
    loadApiFunction( _glCreateSamplers, loader );
    loadApiFunction( _glCreateProgramPipelines, loader );
    loadApiFunction( _glCreateQueries, loader );
    loadApiFunction( _glGetQueryBufferObjecti64v, loader );
    loadApiFunction( _glGetQueryBufferObjectiv, loader );
    loadApiFunction( _glGetQueryBufferObjectui64v, loader );
    loadApiFunction( _glGetQueryBufferObjectuiv, loader );
    loadApiFunction( _glMemoryBarrierByRegion, loader );
    loadApiFunction( _glGetTextureSubImage, loader );
    loadApiFunction( _glGetCompressedTextureSubImage, loader );
    loadApiFunction( _glGetGraphicsResetStatus, loader );
    loadApiFunction( _glGetnCompressedTexImage, loader );
    loadApiFunction( _glGetnTexImage, loader );
    loadApiFunction( _glGetnUniformdv, loader );
    loadApiFunction( _glGetnUniformfv, loader );
    loadApiFunction( _glGetnUniformiv, loader );
    loadApiFunction( _glGetnUniformuiv, loader );
    loadApiFunction( _glReadnPixels, loader );
    loadApiFunction( _glTextureBarrier, loader );
    loadApiFunction( _glSpecializeShader, loader );
    loadApiFunction( _glMultiDrawArraysIndirectCount, loader );
    loadApiFunction( _glMultiDrawElementsIndirectCount, loader );
    loadApiFunction( _glPolygonOffsetClamp, loader );
    loadApiFunction( _glPrimitiveBoundingBoxARB, loader );
    loadApiFunction( _glGetTextureHandleARB, loader );
    loadApiFunction( _glGetTextureSamplerHandleARB, loader );
    loadApiFunction( _glMakeTextureHandleResidentARB, loader );
    loadApiFunction( _glMakeTextureHandleNonResidentARB, loader );
    loadApiFunction( _glGetImageHandleARB, loader );
    loadApiFunction( _glMakeImageHandleResidentARB, loader );
    loadApiFunction( _glMakeImageHandleNonResidentARB, loader );
    loadApiFunction( _glUniformHandleui64ARB, loader );
    loadApiFunction( _glUniformHandleui64vARB, loader );
    loadApiFunction( _glProgramUniformHandleui64ARB, loader );
    loadApiFunction( _glProgramUniformHandleui64vARB, loader );
    loadApiFunction( _glIsTextureHandleResidentARB, loader );
    loadApiFunction( _glIsImageHandleResidentARB, loader );
    loadApiFunction( _glVertexAttribL1ui64ARB, loader );
    loadApiFunction( _glVertexAttribL1ui64vARB, loader );
    loadApiFunction( _glGetVertexAttribLui64vARB, loader );
    loadApiFunction( _glCreateSyncFromCLeventARB, loader );
    loadApiFunction( _glDispatchComputeGroupSizeARB, loader );
    loadApiFunction( _glDebugMessageControlARB, loader );
    loadApiFunction( _glDebugMessageInsertARB, loader );
    loadApiFunction( _glDebugMessageCallbackARB, loader );
    loadApiFunction( _glGetDebugMessageLogARB, loader );
    loadApiFunction( _glBlendEquationiARB, loader );
    loadApiFunction( _glBlendEquationSeparateiARB, loader );
    loadApiFunction( _glBlendFunciARB, loader );
    loadApiFunction( _glBlendFuncSeparateiARB, loader );
    loadApiFunction( _glDrawArraysInstancedARB, loader );
    loadApiFunction( _glDrawElementsInstancedARB, loader );
    loadApiFunction( _glProgramParameteriARB, loader );
    loadApiFunction( _glFramebufferTextureARB, loader );
    loadApiFunction( _glFramebufferTextureLayerARB, loader );
    loadApiFunction( _glFramebufferTextureFaceARB, loader );
    loadApiFunction( _glSpecializeShaderARB, loader );
    loadApiFunction( _glUniform1i64ARB, loader );
    loadApiFunction( _glUniform2i64ARB, loader );
    loadApiFunction( _glUniform3i64ARB, loader );
    loadApiFunction( _glUniform4i64ARB, loader );
    loadApiFunction( _glUniform1i64vARB, loader );
    loadApiFunction( _glUniform2i64vARB, loader );
    loadApiFunction( _glUniform3i64vARB, loader );
    loadApiFunction( _glUniform4i64vARB, loader );
    loadApiFunction( _glUniform1ui64ARB, loader );
    loadApiFunction( _glUniform2ui64ARB, loader );
    loadApiFunction( _glUniform3ui64ARB, loader );
    loadApiFunction( _glUniform4ui64ARB, loader );
    loadApiFunction( _glUniform1ui64vARB, loader );
    loadApiFunction( _glUniform2ui64vARB, loader );
    loadApiFunction( _glUniform3ui64vARB, loader );
    loadApiFunction( _glUniform4ui64vARB, loader );
    loadApiFunction( _glGetUniformi64vARB, loader );
    loadApiFunction( _glGetUniformui64vARB, loader );
    loadApiFunction( _glGetnUniformi64vARB, loader );
    loadApiFunction( _glGetnUniformui64vARB, loader );
    loadApiFunction( _glProgramUniform1i64ARB, loader );
    loadApiFunction( _glProgramUniform2i64ARB, loader );
    loadApiFunction( _glProgramUniform3i64ARB, loader );
    loadApiFunction( _glProgramUniform4i64ARB, loader );
    loadApiFunction( _glProgramUniform1i64vARB, loader );
    loadApiFunction( _glProgramUniform2i64vARB, loader );
    loadApiFunction( _glProgramUniform3i64vARB, loader );
    loadApiFunction( _glProgramUniform4i64vARB, loader );
    loadApiFunction( _glProgramUniform1ui64ARB, loader );
    loadApiFunction( _glProgramUniform2ui64ARB, loader );
    loadApiFunction( _glProgramUniform3ui64ARB, loader );
    loadApiFunction( _glProgramUniform4ui64ARB, loader );
    loadApiFunction( _glProgramUniform1ui64vARB, loader );
    loadApiFunction( _glProgramUniform2ui64vARB, loader );
    loadApiFunction( _glProgramUniform3ui64vARB, loader );
    loadApiFunction( _glProgramUniform4ui64vARB, loader );
    loadApiFunction( _glMultiDrawArraysIndirectCountARB, loader );
    loadApiFunction( _glMultiDrawElementsIndirectCountARB, loader );
    loadApiFunction( _glVertexAttribDivisorARB, loader );
    loadApiFunction( _glMaxShaderCompilerThreadsARB, loader );
    loadApiFunction( _glGetGraphicsResetStatusARB, loader );
    loadApiFunction( _glGetnTexImageARB, loader );
    loadApiFunction( _glReadnPixelsARB, loader );
    loadApiFunction( _glGetnCompressedTexImageARB, loader );
    loadApiFunction( _glGetnUniformfvARB, loader );
    loadApiFunction( _glGetnUniformivARB, loader );
    loadApiFunction( _glGetnUniformuivARB, loader );
    loadApiFunction( _glGetnUniformdvARB, loader );
    loadApiFunction( _glFramebufferSampleLocationsfvARB, loader );
    loadApiFunction( _glNamedFramebufferSampleLocationsfvARB, loader );
    loadApiFunction( _glEvaluateDepthValuesARB, loader );
    loadApiFunction( _glMinSampleShadingARB, loader );
    loadApiFunction( _glNamedStringARB, loader );
    loadApiFunction( _glDeleteNamedStringARB, loader );
    loadApiFunction( _glCompileShaderIncludeARB, loader );
    loadApiFunction( _glIsNamedStringARB, loader );
    loadApiFunction( _glGetNamedStringARB, loader );
    loadApiFunction( _glGetNamedStringivARB, loader );
    loadApiFunction( _glBufferPageCommitmentARB, loader );
    loadApiFunction( _glNamedBufferPageCommitmentEXT, loader );
    loadApiFunction( _glNamedBufferPageCommitmentARB, loader );
    loadApiFunction( _glTexPageCommitmentARB, loader );
    loadApiFunction( _glTexBufferARB, loader );
    loadApiFunction( _glBlendBarrierKHR, loader );
    loadApiFunction( _glMaxShaderCompilerThreadsKHR, loader );
    loadApiFunction( _glGetPerfMonitorGroupsAMD, loader );
    loadApiFunction( _glGetPerfMonitorCountersAMD, loader );
    loadApiFunction( _glGetPerfMonitorGroupStringAMD, loader );
    loadApiFunction( _glGetPerfMonitorCounterStringAMD, loader );
    loadApiFunction( _glGetPerfMonitorCounterInfoAMD, loader );
    loadApiFunction( _glGenPerfMonitorsAMD, loader );
    loadApiFunction( _glDeletePerfMonitorsAMD, loader );
    loadApiFunction( _glSelectPerfMonitorCountersAMD, loader );
    loadApiFunction( _glBeginPerfMonitorAMD, loader );
    loadApiFunction( _glEndPerfMonitorAMD, loader );
    loadApiFunction( _glGetPerfMonitorCounterDataAMD, loader );
    loadApiFunction( _glEGLImageTargetTexStorageEXT, loader );
    loadApiFunction( _glEGLImageTargetTextureStorageEXT, loader );
    loadApiFunction( _glLabelObjectEXT, loader );
    loadApiFunction( _glGetObjectLabelEXT, loader );
    loadApiFunction( _glInsertEventMarkerEXT, loader );
    loadApiFunction( _glPushGroupMarkerEXT, loader );
    loadApiFunction( _glPopGroupMarkerEXT, loader );
    loadApiFunction( _glMatrixLoadfEXT, loader );
    loadApiFunction( _glMatrixLoaddEXT, loader );
    loadApiFunction( _glMatrixMultfEXT, loader );
    loadApiFunction( _glMatrixMultdEXT, loader );
    loadApiFunction( _glMatrixLoadIdentityEXT, loader );
    loadApiFunction( _glMatrixRotatefEXT, loader );
    loadApiFunction( _glMatrixRotatedEXT, loader );
    loadApiFunction( _glMatrixScalefEXT, loader );
    loadApiFunction( _glMatrixScaledEXT, loader );
    loadApiFunction( _glMatrixTranslatefEXT, loader );
    loadApiFunction( _glMatrixTranslatedEXT, loader );
    loadApiFunction( _glMatrixFrustumEXT, loader );
    loadApiFunction( _glMatrixOrthoEXT, loader );
    loadApiFunction( _glMatrixPopEXT, loader );
    loadApiFunction( _glMatrixPushEXT, loader );
    loadApiFunction( _glClientAttribDefaultEXT, loader );
    loadApiFunction( _glPushClientAttribDefaultEXT, loader );
    loadApiFunction( _glTextureParameterfEXT, loader );
    loadApiFunction( _glTextureParameterfvEXT, loader );
    loadApiFunction( _glTextureParameteriEXT, loader );
    loadApiFunction( _glTextureParameterivEXT, loader );
    loadApiFunction( _glTextureImage1DEXT, loader );
    loadApiFunction( _glTextureImage2DEXT, loader );
    loadApiFunction( _glTextureSubImage1DEXT, loader );
    loadApiFunction( _glTextureSubImage2DEXT, loader );
    loadApiFunction( _glCopyTextureImage1DEXT, loader );
    loadApiFunction( _glCopyTextureImage2DEXT, loader );
    loadApiFunction( _glCopyTextureSubImage1DEXT, loader );
    loadApiFunction( _glCopyTextureSubImage2DEXT, loader );
    loadApiFunction( _glGetTextureImageEXT, loader );
    loadApiFunction( _glGetTextureParameterfvEXT, loader );
    loadApiFunction( _glGetTextureParameterivEXT, loader );
    loadApiFunction( _glGetTextureLevelParameterfvEXT, loader );
    loadApiFunction( _glGetTextureLevelParameterivEXT, loader );
    loadApiFunction( _glTextureImage3DEXT, loader );
    loadApiFunction( _glTextureSubImage3DEXT, loader );
    loadApiFunction( _glCopyTextureSubImage3DEXT, loader );
    loadApiFunction( _glBindMultiTextureEXT, loader );
    loadApiFunction( _glMultiTexCoordPointerEXT, loader );
    loadApiFunction( _glMultiTexEnvfEXT, loader );
    loadApiFunction( _glMultiTexEnvfvEXT, loader );
    loadApiFunction( _glMultiTexEnviEXT, loader );
    loadApiFunction( _glMultiTexEnvivEXT, loader );
    loadApiFunction( _glMultiTexGendEXT, loader );
    loadApiFunction( _glMultiTexGendvEXT, loader );
    loadApiFunction( _glMultiTexGenfEXT, loader );
    loadApiFunction( _glMultiTexGenfvEXT, loader );
    loadApiFunction( _glMultiTexGeniEXT, loader );
    loadApiFunction( _glMultiTexGenivEXT, loader );
    loadApiFunction( _glGetMultiTexEnvfvEXT, loader );
    loadApiFunction( _glGetMultiTexEnvivEXT, loader );
    loadApiFunction( _glGetMultiTexGendvEXT, loader );
    loadApiFunction( _glGetMultiTexGenfvEXT, loader );
    loadApiFunction( _glGetMultiTexGenivEXT, loader );
    loadApiFunction( _glMultiTexParameteriEXT, loader );
    loadApiFunction( _glMultiTexParameterivEXT, loader );
    loadApiFunction( _glMultiTexParameterfEXT, loader );
    loadApiFunction( _glMultiTexParameterfvEXT, loader );
    loadApiFunction( _glMultiTexImage1DEXT, loader );
    loadApiFunction( _glMultiTexImage2DEXT, loader );
    loadApiFunction( _glMultiTexSubImage1DEXT, loader );
    loadApiFunction( _glMultiTexSubImage2DEXT, loader );
    loadApiFunction( _glCopyMultiTexImage1DEXT, loader );
    loadApiFunction( _glCopyMultiTexImage2DEXT, loader );
    loadApiFunction( _glCopyMultiTexSubImage1DEXT, loader );
    loadApiFunction( _glCopyMultiTexSubImage2DEXT, loader );
    loadApiFunction( _glGetMultiTexImageEXT, loader );
    loadApiFunction( _glGetMultiTexParameterfvEXT, loader );
    loadApiFunction( _glGetMultiTexParameterivEXT, loader );
    loadApiFunction( _glGetMultiTexLevelParameterfvEXT, loader );
    loadApiFunction( _glGetMultiTexLevelParameterivEXT, loader );
    loadApiFunction( _glMultiTexImage3DEXT, loader );
    loadApiFunction( _glMultiTexSubImage3DEXT, loader );
    loadApiFunction( _glCopyMultiTexSubImage3DEXT, loader );
    loadApiFunction( _glEnableClientStateIndexedEXT, loader );
    loadApiFunction( _glDisableClientStateIndexedEXT, loader );
    loadApiFunction( _glGetFloatIndexedvEXT, loader );
    loadApiFunction( _glGetDoubleIndexedvEXT, loader );
    loadApiFunction( _glGetPointerIndexedvEXT, loader );
    loadApiFunction( _glEnableIndexedEXT, loader );
    loadApiFunction( _glDisableIndexedEXT, loader );
    loadApiFunction( _glIsEnabledIndexedEXT, loader );
    loadApiFunction( _glGetIntegerIndexedvEXT, loader );
    loadApiFunction( _glGetBooleanIndexedvEXT, loader );
    loadApiFunction( _glCompressedTextureImage3DEXT, loader );
    loadApiFunction( _glCompressedTextureImage2DEXT, loader );
    loadApiFunction( _glCompressedTextureImage1DEXT, loader );
    loadApiFunction( _glCompressedTextureSubImage3DEXT, loader );
    loadApiFunction( _glCompressedTextureSubImage2DEXT, loader );
    loadApiFunction( _glCompressedTextureSubImage1DEXT, loader );
    loadApiFunction( _glGetCompressedTextureImageEXT, loader );
    loadApiFunction( _glCompressedMultiTexImage3DEXT, loader );
    loadApiFunction( _glCompressedMultiTexImage2DEXT, loader );
    loadApiFunction( _glCompressedMultiTexImage1DEXT, loader );
    loadApiFunction( _glCompressedMultiTexSubImage3DEXT, loader );
    loadApiFunction( _glCompressedMultiTexSubImage2DEXT, loader );
    loadApiFunction( _glCompressedMultiTexSubImage1DEXT, loader );
    loadApiFunction( _glGetCompressedMultiTexImageEXT, loader );
    loadApiFunction( _glMatrixLoadTransposefEXT, loader );
    loadApiFunction( _glMatrixLoadTransposedEXT, loader );
    loadApiFunction( _glMatrixMultTransposefEXT, loader );
    loadApiFunction( _glMatrixMultTransposedEXT, loader );
    loadApiFunction( _glNamedBufferDataEXT, loader );
    loadApiFunction( _glNamedBufferSubDataEXT, loader );
    loadApiFunction( _glMapNamedBufferEXT, loader );
    loadApiFunction( _glUnmapNamedBufferEXT, loader );
    loadApiFunction( _glGetNamedBufferParameterivEXT, loader );
    loadApiFunction( _glGetNamedBufferPointervEXT, loader );
    loadApiFunction( _glGetNamedBufferSubDataEXT, loader );
    loadApiFunction( _glProgramUniform1fEXT, loader );
    loadApiFunction( _glProgramUniform2fEXT, loader );
    loadApiFunction( _glProgramUniform3fEXT, loader );
    loadApiFunction( _glProgramUniform4fEXT, loader );
    loadApiFunction( _glProgramUniform1iEXT, loader );
    loadApiFunction( _glProgramUniform2iEXT, loader );
    loadApiFunction( _glProgramUniform3iEXT, loader );
    loadApiFunction( _glProgramUniform4iEXT, loader );
    loadApiFunction( _glProgramUniform1fvEXT, loader );
    loadApiFunction( _glProgramUniform2fvEXT, loader );
    loadApiFunction( _glProgramUniform3fvEXT, loader );
    loadApiFunction( _glProgramUniform4fvEXT, loader );
    loadApiFunction( _glProgramUniform1ivEXT, loader );
    loadApiFunction( _glProgramUniform2ivEXT, loader );
    loadApiFunction( _glProgramUniform3ivEXT, loader );
    loadApiFunction( _glProgramUniform4ivEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2x3fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3x2fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2x4fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4x2fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3x4fvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4x3fvEXT, loader );
    loadApiFunction( _glTextureBufferEXT, loader );
    loadApiFunction( _glMultiTexBufferEXT, loader );
    loadApiFunction( _glTextureParameterIivEXT, loader );
    loadApiFunction( _glTextureParameterIuivEXT, loader );
    loadApiFunction( _glGetTextureParameterIivEXT, loader );
    loadApiFunction( _glGetTextureParameterIuivEXT, loader );
    loadApiFunction( _glMultiTexParameterIivEXT, loader );
    loadApiFunction( _glMultiTexParameterIuivEXT, loader );
    loadApiFunction( _glGetMultiTexParameterIivEXT, loader );
    loadApiFunction( _glGetMultiTexParameterIuivEXT, loader );
    loadApiFunction( _glProgramUniform1uiEXT, loader );
    loadApiFunction( _glProgramUniform2uiEXT, loader );
    loadApiFunction( _glProgramUniform3uiEXT, loader );
    loadApiFunction( _glProgramUniform4uiEXT, loader );
    loadApiFunction( _glProgramUniform1uivEXT, loader );
    loadApiFunction( _glProgramUniform2uivEXT, loader );
    loadApiFunction( _glProgramUniform3uivEXT, loader );
    loadApiFunction( _glProgramUniform4uivEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameters4fvEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameterI4iEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameterI4ivEXT, loader );
    loadApiFunction( _glNamedProgramLocalParametersI4ivEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameterI4uiEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameterI4uivEXT, loader );
    loadApiFunction( _glNamedProgramLocalParametersI4uivEXT, loader );
    loadApiFunction( _glGetNamedProgramLocalParameterIivEXT, loader );
    loadApiFunction( _glGetNamedProgramLocalParameterIuivEXT, loader );
    loadApiFunction( _glEnableClientStateiEXT, loader );
    loadApiFunction( _glDisableClientStateiEXT, loader );
    loadApiFunction( _glGetFloati_vEXT, loader );
    loadApiFunction( _glGetDoublei_vEXT, loader );
    loadApiFunction( _glGetPointeri_vEXT, loader );
    loadApiFunction( _glNamedProgramStringEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameter4dEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameter4dvEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameter4fEXT, loader );
    loadApiFunction( _glNamedProgramLocalParameter4fvEXT, loader );
    loadApiFunction( _glGetNamedProgramLocalParameterdvEXT, loader );
    loadApiFunction( _glGetNamedProgramLocalParameterfvEXT, loader );
    loadApiFunction( _glGetNamedProgramivEXT, loader );
    loadApiFunction( _glGetNamedProgramStringEXT, loader );
    loadApiFunction( _glNamedRenderbufferStorageEXT, loader );
    loadApiFunction( _glGetNamedRenderbufferParameterivEXT, loader );
    loadApiFunction( _glNamedRenderbufferStorageMultisampleEXT, loader );
    loadApiFunction( _glNamedRenderbufferStorageMultisampleCoverageEXT, loader );
    loadApiFunction( _glCheckNamedFramebufferStatusEXT, loader );
    loadApiFunction( _glNamedFramebufferTexture1DEXT, loader );
    loadApiFunction( _glNamedFramebufferTexture2DEXT, loader );
    loadApiFunction( _glNamedFramebufferTexture3DEXT, loader );
    loadApiFunction( _glNamedFramebufferRenderbufferEXT, loader );
    loadApiFunction( _glGetNamedFramebufferAttachmentParameterivEXT, loader );
    loadApiFunction( _glGenerateTextureMipmapEXT, loader );
    loadApiFunction( _glGenerateMultiTexMipmapEXT, loader );
    loadApiFunction( _glFramebufferDrawBufferEXT, loader );
    loadApiFunction( _glFramebufferDrawBuffersEXT, loader );
    loadApiFunction( _glFramebufferReadBufferEXT, loader );
    loadApiFunction( _glGetFramebufferParameterivEXT, loader );
    loadApiFunction( _glNamedCopyBufferSubDataEXT, loader );
    loadApiFunction( _glNamedFramebufferTextureEXT, loader );
    loadApiFunction( _glNamedFramebufferTextureLayerEXT, loader );
    loadApiFunction( _glNamedFramebufferTextureFaceEXT, loader );
    loadApiFunction( _glTextureRenderbufferEXT, loader );
    loadApiFunction( _glMultiTexRenderbufferEXT, loader );
    loadApiFunction( _glVertexArrayVertexOffsetEXT, loader );
    loadApiFunction( _glVertexArrayColorOffsetEXT, loader );
    loadApiFunction( _glVertexArrayEdgeFlagOffsetEXT, loader );
    loadApiFunction( _glVertexArrayIndexOffsetEXT, loader );
    loadApiFunction( _glVertexArrayNormalOffsetEXT, loader );
    loadApiFunction( _glVertexArrayTexCoordOffsetEXT, loader );
    loadApiFunction( _glVertexArrayMultiTexCoordOffsetEXT, loader );
    loadApiFunction( _glVertexArrayFogCoordOffsetEXT, loader );
    loadApiFunction( _glVertexArraySecondaryColorOffsetEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribOffsetEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribIOffsetEXT, loader );
    loadApiFunction( _glEnableVertexArrayEXT, loader );
    loadApiFunction( _glDisableVertexArrayEXT, loader );
    loadApiFunction( _glEnableVertexArrayAttribEXT, loader );
    loadApiFunction( _glDisableVertexArrayAttribEXT, loader );
    loadApiFunction( _glGetVertexArrayIntegervEXT, loader );
    loadApiFunction( _glGetVertexArrayPointervEXT, loader );
    loadApiFunction( _glGetVertexArrayIntegeri_vEXT, loader );
    loadApiFunction( _glGetVertexArrayPointeri_vEXT, loader );
    loadApiFunction( _glMapNamedBufferRangeEXT, loader );
    loadApiFunction( _glFlushMappedNamedBufferRangeEXT, loader );
    loadApiFunction( _glNamedBufferStorageEXT, loader );
    loadApiFunction( _glClearNamedBufferDataEXT, loader );
    loadApiFunction( _glClearNamedBufferSubDataEXT, loader );
    loadApiFunction( _glNamedFramebufferParameteriEXT, loader );
    loadApiFunction( _glGetNamedFramebufferParameterivEXT, loader );
    loadApiFunction( _glProgramUniform1dEXT, loader );
    loadApiFunction( _glProgramUniform2dEXT, loader );
    loadApiFunction( _glProgramUniform3dEXT, loader );
    loadApiFunction( _glProgramUniform4dEXT, loader );
    loadApiFunction( _glProgramUniform1dvEXT, loader );
    loadApiFunction( _glProgramUniform2dvEXT, loader );
    loadApiFunction( _glProgramUniform3dvEXT, loader );
    loadApiFunction( _glProgramUniform4dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2x3dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix2x4dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3x2dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix3x4dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4x2dvEXT, loader );
    loadApiFunction( _glProgramUniformMatrix4x3dvEXT, loader );
    loadApiFunction( _glTextureBufferRangeEXT, loader );
    loadApiFunction( _glTextureStorage1DEXT, loader );
    loadApiFunction( _glTextureStorage2DEXT, loader );
    loadApiFunction( _glTextureStorage3DEXT, loader );
    loadApiFunction( _glTextureStorage2DMultisampleEXT, loader );
    loadApiFunction( _glTextureStorage3DMultisampleEXT, loader );
    loadApiFunction( _glVertexArrayBindVertexBufferEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribFormatEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribIFormatEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribLFormatEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribBindingEXT, loader );
    loadApiFunction( _glVertexArrayVertexBindingDivisorEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribLOffsetEXT, loader );
    loadApiFunction( _glTexturePageCommitmentEXT, loader );
    loadApiFunction( _glVertexArrayVertexAttribDivisorEXT, loader );
    loadApiFunction( _glDrawArraysInstancedEXT, loader );
    loadApiFunction( _glDrawElementsInstancedEXT, loader );
    loadApiFunction( _glPolygonOffsetClampEXT, loader );
    loadApiFunction( _glRasterSamplesEXT, loader );
    loadApiFunction( _glUseShaderProgramEXT, loader );
    loadApiFunction( _glActiveProgramEXT, loader );
    loadApiFunction( _glCreateShaderProgramEXT, loader );
    loadApiFunction( _glFramebufferFetchBarrierEXT, loader );
    loadApiFunction( _glWindowRectanglesEXT, loader );
    loadApiFunction( _glApplyFramebufferAttachmentCMAAINTEL, loader );
    loadApiFunction( _glBeginPerfQueryINTEL, loader );
    loadApiFunction( _glCreatePerfQueryINTEL, loader );
    loadApiFunction( _glDeletePerfQueryINTEL, loader );
    loadApiFunction( _glEndPerfQueryINTEL, loader );
    loadApiFunction( _glGetFirstPerfQueryIdINTEL, loader );
    loadApiFunction( _glGetNextPerfQueryIdINTEL, loader );
    loadApiFunction( _glGetPerfCounterInfoINTEL, loader );
    loadApiFunction( _glGetPerfQueryDataINTEL, loader );
    loadApiFunction( _glGetPerfQueryIdByNameINTEL, loader );
    loadApiFunction( _glGetPerfQueryInfoINTEL, loader );
    loadApiFunction( _glMultiDrawArraysIndirectBindlessNV, loader );
    loadApiFunction( _glMultiDrawElementsIndirectBindlessNV, loader );
    loadApiFunction( _glMultiDrawArraysIndirectBindlessCountNV, loader );
    loadApiFunction( _glMultiDrawElementsIndirectBindlessCountNV, loader );
    loadApiFunction( _glGetTextureHandleNV, loader );
    loadApiFunction( _glGetTextureSamplerHandleNV, loader );
    loadApiFunction( _glMakeTextureHandleResidentNV, loader );
    loadApiFunction( _glMakeTextureHandleNonResidentNV, loader );
    loadApiFunction( _glGetImageHandleNV, loader );
    loadApiFunction( _glMakeImageHandleResidentNV, loader );
    loadApiFunction( _glMakeImageHandleNonResidentNV, loader );
    loadApiFunction( _glUniformHandleui64NV, loader );
    loadApiFunction( _glUniformHandleui64vNV, loader );
    loadApiFunction( _glProgramUniformHandleui64NV, loader );
    loadApiFunction( _glProgramUniformHandleui64vNV, loader );
    loadApiFunction( _glIsTextureHandleResidentNV, loader );
    loadApiFunction( _glIsImageHandleResidentNV, loader );
    loadApiFunction( _glBlendParameteriNV, loader );
    loadApiFunction( _glBlendBarrierNV, loader );
    loadApiFunction( _glViewportPositionWScaleNV, loader );
    loadApiFunction( _glCreateStatesNV, loader );
    loadApiFunction( _glDeleteStatesNV, loader );
    loadApiFunction( _glIsStateNV, loader );
    loadApiFunction( _glStateCaptureNV, loader );
    loadApiFunction( _glGetCommandHeaderNV, loader );
    loadApiFunction( _glGetStageIndexNV, loader );
    loadApiFunction( _glDrawCommandsNV, loader );
    loadApiFunction( _glDrawCommandsAddressNV, loader );
    loadApiFunction( _glDrawCommandsStatesNV, loader );
    loadApiFunction( _glDrawCommandsStatesAddressNV, loader );
    loadApiFunction( _glCreateCommandListsNV, loader );
    loadApiFunction( _glDeleteCommandListsNV, loader );
    loadApiFunction( _glIsCommandListNV, loader );
    loadApiFunction( _glListDrawCommandsStatesClientNV, loader );
    loadApiFunction( _glCommandListSegmentsNV, loader );
    loadApiFunction( _glCompileCommandListNV, loader );
    loadApiFunction( _glCallCommandListNV, loader );
    loadApiFunction( _glBeginConditionalRenderNV, loader );
    loadApiFunction( _glEndConditionalRenderNV, loader );
    loadApiFunction( _glSubpixelPrecisionBiasNV, loader );
    loadApiFunction( _glConservativeRasterParameterfNV, loader );
    loadApiFunction( _glConservativeRasterParameteriNV, loader );
    loadApiFunction( _glDrawVkImageNV, loader );
    loadApiFunction( _glGetVkProcAddrNV, loader );
    loadApiFunction( _glWaitVkSemaphoreNV, loader );
    loadApiFunction( _glSignalVkSemaphoreNV, loader );
    loadApiFunction( _glSignalVkFenceNV, loader );
    loadApiFunction( _glFragmentCoverageColorNV, loader );
    loadApiFunction( _glCoverageModulationTableNV, loader );
    loadApiFunction( _glGetCoverageModulationTableNV, loader );
    loadApiFunction( _glCoverageModulationNV, loader );
    loadApiFunction( _glRenderbufferStorageMultisampleCoverageNV, loader );
    loadApiFunction( _glUniform1i64NV, loader );
    loadApiFunction( _glUniform2i64NV, loader );
    loadApiFunction( _glUniform3i64NV, loader );
    loadApiFunction( _glUniform4i64NV, loader );
    loadApiFunction( _glUniform1i64vNV, loader );
    loadApiFunction( _glUniform2i64vNV, loader );
    loadApiFunction( _glUniform3i64vNV, loader );
    loadApiFunction( _glUniform4i64vNV, loader );
    loadApiFunction( _glUniform1ui64NV, loader );
    loadApiFunction( _glUniform2ui64NV, loader );
    loadApiFunction( _glUniform3ui64NV, loader );
    loadApiFunction( _glUniform4ui64NV, loader );
    loadApiFunction( _glUniform1ui64vNV, loader );
    loadApiFunction( _glUniform2ui64vNV, loader );
    loadApiFunction( _glUniform3ui64vNV, loader );
    loadApiFunction( _glUniform4ui64vNV, loader );
    loadApiFunction( _glGetUniformi64vNV, loader );
    loadApiFunction( _glProgramUniform1i64NV, loader );
    loadApiFunction( _glProgramUniform2i64NV, loader );
    loadApiFunction( _glProgramUniform3i64NV, loader );
    loadApiFunction( _glProgramUniform4i64NV, loader );
    loadApiFunction( _glProgramUniform1i64vNV, loader );
    loadApiFunction( _glProgramUniform2i64vNV, loader );
    loadApiFunction( _glProgramUniform3i64vNV, loader );
    loadApiFunction( _glProgramUniform4i64vNV, loader );
    loadApiFunction( _glProgramUniform1ui64NV, loader );
    loadApiFunction( _glProgramUniform2ui64NV, loader );
    loadApiFunction( _glProgramUniform3ui64NV, loader );
    loadApiFunction( _glProgramUniform4ui64NV, loader );
    loadApiFunction( _glProgramUniform1ui64vNV, loader );
    loadApiFunction( _glProgramUniform2ui64vNV, loader );
    loadApiFunction( _glProgramUniform3ui64vNV, loader );
    loadApiFunction( _glProgramUniform4ui64vNV, loader );
    loadApiFunction( _glGetInternalformatSampleivNV, loader );
    loadApiFunction( _glGenPathsNV, loader );
    loadApiFunction( _glDeletePathsNV, loader );
    loadApiFunction( _glIsPathNV, loader );
    loadApiFunction( _glPathCommandsNV, loader );
    loadApiFunction( _glPathCoordsNV, loader );
    loadApiFunction( _glPathSubCommandsNV, loader );
    loadApiFunction( _glPathSubCoordsNV, loader );
    loadApiFunction( _glPathStringNV, loader );
    loadApiFunction( _glPathGlyphsNV, loader );
    loadApiFunction( _glPathGlyphRangeNV, loader );
    loadApiFunction( _glWeightPathsNV, loader );
    loadApiFunction( _glCopyPathNV, loader );
    loadApiFunction( _glInterpolatePathsNV, loader );
    loadApiFunction( _glTransformPathNV, loader );
    loadApiFunction( _glPathParameterivNV, loader );
    loadApiFunction( _glPathParameteriNV, loader );
    loadApiFunction( _glPathParameterfvNV, loader );
    loadApiFunction( _glPathParameterfNV, loader );
    loadApiFunction( _glPathDashArrayNV, loader );
    loadApiFunction( _glPathStencilFuncNV, loader );
    loadApiFunction( _glPathStencilDepthOffsetNV, loader );
    loadApiFunction( _glStencilFillPathNV, loader );
    loadApiFunction( _glStencilStrokePathNV, loader );
    loadApiFunction( _glStencilFillPathInstancedNV, loader );
    loadApiFunction( _glStencilStrokePathInstancedNV, loader );
    loadApiFunction( _glPathCoverDepthFuncNV, loader );
    loadApiFunction( _glCoverFillPathNV, loader );
    loadApiFunction( _glCoverStrokePathNV, loader );
    loadApiFunction( _glCoverFillPathInstancedNV, loader );
    loadApiFunction( _glCoverStrokePathInstancedNV, loader );
    loadApiFunction( _glGetPathParameterivNV, loader );
    loadApiFunction( _glGetPathParameterfvNV, loader );
    loadApiFunction( _glGetPathCommandsNV, loader );
    loadApiFunction( _glGetPathCoordsNV, loader );
    loadApiFunction( _glGetPathDashArrayNV, loader );
    loadApiFunction( _glGetPathMetricsNV, loader );
    loadApiFunction( _glGetPathMetricRangeNV, loader );
    loadApiFunction( _glGetPathSpacingNV, loader );
    loadApiFunction( _glIsPointInFillPathNV, loader );
    loadApiFunction( _glIsPointInStrokePathNV, loader );
    loadApiFunction( _glGetPathLengthNV, loader );
    loadApiFunction( _glPointAlongPathNV, loader );
    loadApiFunction( _glMatrixLoad3x2fNV, loader );
    loadApiFunction( _glMatrixLoad3x3fNV, loader );
    loadApiFunction( _glMatrixLoadTranspose3x3fNV, loader );
    loadApiFunction( _glMatrixMult3x2fNV, loader );
    loadApiFunction( _glMatrixMult3x3fNV, loader );
    loadApiFunction( _glMatrixMultTranspose3x3fNV, loader );
    loadApiFunction( _glStencilThenCoverFillPathNV, loader );
    loadApiFunction( _glStencilThenCoverStrokePathNV, loader );
    loadApiFunction( _glStencilThenCoverFillPathInstancedNV, loader );
    loadApiFunction( _glStencilThenCoverStrokePathInstancedNV, loader );
    loadApiFunction( _glPathGlyphIndexRangeNV, loader );
    loadApiFunction( _glPathGlyphIndexArrayNV, loader );
    loadApiFunction( _glPathMemoryGlyphIndexArrayNV, loader );
    loadApiFunction( _glProgramPathFragmentInputGenNV, loader );
    loadApiFunction( _glGetProgramResourcefvNV, loader );
    loadApiFunction( _glFramebufferSampleLocationsfvNV, loader );
    loadApiFunction( _glNamedFramebufferSampleLocationsfvNV, loader );
    loadApiFunction( _glResolveDepthValuesNV, loader );
    loadApiFunction( _glMakeBufferResidentNV, loader );
    loadApiFunction( _glMakeBufferNonResidentNV, loader );
    loadApiFunction( _glIsBufferResidentNV, loader );
    loadApiFunction( _glMakeNamedBufferResidentNV, loader );
    loadApiFunction( _glMakeNamedBufferNonResidentNV, loader );
    loadApiFunction( _glIsNamedBufferResidentNV, loader );
    loadApiFunction( _glGetBufferParameterui64vNV, loader );
    loadApiFunction( _glGetNamedBufferParameterui64vNV, loader );
    loadApiFunction( _glGetIntegerui64vNV, loader );
    loadApiFunction( _glUniformui64NV, loader );
    loadApiFunction( _glUniformui64vNV, loader );
    loadApiFunction( _glGetUniformui64vNV, loader );
    loadApiFunction( _glProgramUniformui64NV, loader );
    loadApiFunction( _glProgramUniformui64vNV, loader );
    loadApiFunction( _glTextureBarrierNV, loader );
    loadApiFunction( _glVertexAttribL1i64NV, loader );
    loadApiFunction( _glVertexAttribL2i64NV, loader );
    loadApiFunction( _glVertexAttribL3i64NV, loader );
    loadApiFunction( _glVertexAttribL4i64NV, loader );
    loadApiFunction( _glVertexAttribL1i64vNV, loader );
    loadApiFunction( _glVertexAttribL2i64vNV, loader );
    loadApiFunction( _glVertexAttribL3i64vNV, loader );
    loadApiFunction( _glVertexAttribL4i64vNV, loader );
    loadApiFunction( _glVertexAttribL1ui64NV, loader );
    loadApiFunction( _glVertexAttribL2ui64NV, loader );
    loadApiFunction( _glVertexAttribL3ui64NV, loader );
    loadApiFunction( _glVertexAttribL4ui64NV, loader );
    loadApiFunction( _glVertexAttribL1ui64vNV, loader );
    loadApiFunction( _glVertexAttribL2ui64vNV, loader );
    loadApiFunction( _glVertexAttribL3ui64vNV, loader );
    loadApiFunction( _glVertexAttribL4ui64vNV, loader );
    loadApiFunction( _glGetVertexAttribLi64vNV, loader );
    loadApiFunction( _glGetVertexAttribLui64vNV, loader );
    loadApiFunction( _glVertexAttribLFormatNV, loader );
    loadApiFunction( _glBufferAddressRangeNV, loader );
    loadApiFunction( _glVertexFormatNV, loader );
    loadApiFunction( _glNormalFormatNV, loader );
    loadApiFunction( _glColorFormatNV, loader );
    loadApiFunction( _glIndexFormatNV, loader );
    loadApiFunction( _glTexCoordFormatNV, loader );
    loadApiFunction( _glEdgeFlagFormatNV, loader );
    loadApiFunction( _glSecondaryColorFormatNV, loader );
    loadApiFunction( _glFogCoordFormatNV, loader );
    loadApiFunction( _glVertexAttribFormatNV, loader );
    loadApiFunction( _glVertexAttribIFormatNV, loader );
    loadApiFunction( _glGetIntegerui64i_vNV, loader );
    loadApiFunction( _glViewportSwizzleNV, loader );
    loadApiFunction( _glFramebufferTextureMultiviewOVR, loader );

#ifdef _WIN32
    loadApiFunction( _wglGetExtensionsStringEXT, loader );
    loadApiFunction( _wglGetExtensionsStringARB, loader );
    loadApiFunction( _wglCreateContextAttribsARB, loader );
    loadApiFunction( _wglSwapIntervalEXT, loader );
#endif

#ifdef __linux__
    loadApiFunction( _glXCreateContextAttribsARB, loader );
    loadApiFunction( _glXSwapIntervalEXT, loader );
    loadApiFunction( _glXSwapIntervalMESA, loader );
#endif

    obtainApiVersion();
    obtainExtensionSupportStatus();
}

void GpuContextOgl::obtainApiVersion() {
    std::string version =
        reinterpret_cast<const char*>( call<GlGetString>(GL_VERSION) );
    std::replace( version.begin(), version.end(), '.', ' ' );

    std::istringstream stream( version );
    stream >> _apiVersion.first >> _apiVersion.second;
}

void GpuContextOgl::obtainExtensionSupportStatus() {
    const std::unordered_map<std::string_view, bool*> extensionSupport = {
        {
            "GL_ARB_buffer_storage",
            &_extensionSupportStatus.arbBufferStorage
        },
        {
            "GL_ARB_get_program_binary",
            &_extensionSupportStatus.arbGetProgramBinary
        },
        {
            "GL_ARB_invalidate_subdata",
            &_extensionSupportStatus.arbInvalidateSubdata
        },
        {
            "GL_ARB_multi_bind",
            &_extensionSupportStatus.arbMultiBind
        },
        {
            "GL_ARB_separate_shader_objects",
            &_extensionSupportStatus.arbSeparateShaderObjects
        },
        {
            "GL_ARB_texture_storage",
            &_extensionSupportStatus.arbTextureStorage
        },
        {
            "GL_ARB_texture_storage_multisample",
            &_extensionSupportStatus.arbTextureStorageMultisample
        },
        {
            "GL_ARB_timer_query",
            &_extensionSupportStatus.arbTimerQuery
        },
        {
            "GL_EXT_texture_filter_anisotropic",
            &_extensionSupportStatus.extTextureFilterAnisotropic
        },
        {
            "GL_KHR_debug",
            &_extensionSupportStatus.khrDebug
        },
        {
            "EXT_swap_control",
            &_extensionSupportStatus.wglExtSwapControl
        },
        {
            "EXT_swap_control_tear",
            &_extensionSupportStatus.wglExtSwapControlTear
        }
    };

    GLint numExtensions = 0;
    call<GlGetIntegerv>( GL_NUM_EXTENSIONS, &numExtensions );

    for( GLint index = 0; index < numExtensions; ++index ) {
        const char *extensionName =
            reinterpret_cast<const char*>(
                call<GlGetStringi>(GL_EXTENSIONS, index) );

        getSupportedExtensions( extensionName, extensionSupport );
    }

#ifdef _WIN32
    const char *extensionsString = nullptr;

    if( isFunctionAvailable<WglGetExtensionsStringARB>() ) {
        extensionsString =
            callUnchecked<WglGetExtensionsStringARB>( wglGetCurrentDC() );
    }

    if( !extensionsString &&
            isFunctionAvailable<WglGetExtensionsStringEXT>() ) {
        extensionsString =
            callUnchecked<WglGetExtensionsStringEXT>();
    }

    if( extensionsString ) {
        getSupportedExtensions( extensionsString, extensionSupport );
    }
#endif

#ifdef __linux__
    Display *display = XOpenDisplay( nullptr );

    getSupportedExtensions(
        glXQueryExtensionsString(display, XDefaultScreen(display)),
        extensionSupport );

    XCloseDisplay( display );
#endif
}

}
