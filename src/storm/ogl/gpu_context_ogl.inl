namespace storm {

template <>
inline const GlCullFace&
GpuContextOgl::getFunction<GlCullFace>() const {
    return _glCullFace;
}

template <>
inline const GlFrontFace&
GpuContextOgl::getFunction<GlFrontFace>() const {
    return _glFrontFace;
}

template <>
inline const GlHint&
GpuContextOgl::getFunction<GlHint>() const {
    return _glHint;
}

template <>
inline const GlLineWidth&
GpuContextOgl::getFunction<GlLineWidth>() const {
    return _glLineWidth;
}

template <>
inline const GlPointSize&
GpuContextOgl::getFunction<GlPointSize>() const {
    return _glPointSize;
}

template <>
inline const GlPolygonMode&
GpuContextOgl::getFunction<GlPolygonMode>() const {
    return _glPolygonMode;
}

template <>
inline const GlScissor&
GpuContextOgl::getFunction<GlScissor>() const {
    return _glScissor;
}

template <>
inline const GlTexParameterf&
GpuContextOgl::getFunction<GlTexParameterf>() const {
    return _glTexParameterf;
}

template <>
inline const GlTexParameterfv&
GpuContextOgl::getFunction<GlTexParameterfv>() const {
    return _glTexParameterfv;
}

template <>
inline const GlTexParameteri&
GpuContextOgl::getFunction<GlTexParameteri>() const {
    return _glTexParameteri;
}

template <>
inline const GlTexParameteriv&
GpuContextOgl::getFunction<GlTexParameteriv>() const {
    return _glTexParameteriv;
}

template <>
inline const GlTexImage1D&
GpuContextOgl::getFunction<GlTexImage1D>() const {
    return _glTexImage1D;
}

template <>
inline const GlTexImage2D&
GpuContextOgl::getFunction<GlTexImage2D>() const {
    return _glTexImage2D;
}

template <>
inline const GlDrawBuffer&
GpuContextOgl::getFunction<GlDrawBuffer>() const {
    return _glDrawBuffer;
}

template <>
inline const GlClear&
GpuContextOgl::getFunction<GlClear>() const {
    return _glClear;
}

template <>
inline const GlClearColor&
GpuContextOgl::getFunction<GlClearColor>() const {
    return _glClearColor;
}

template <>
inline const GlClearStencil&
GpuContextOgl::getFunction<GlClearStencil>() const {
    return _glClearStencil;
}

template <>
inline const GlClearDepth&
GpuContextOgl::getFunction<GlClearDepth>() const {
    return _glClearDepth;
}

template <>
inline const GlStencilMask&
GpuContextOgl::getFunction<GlStencilMask>() const {
    return _glStencilMask;
}

template <>
inline const GlColorMask&
GpuContextOgl::getFunction<GlColorMask>() const {
    return _glColorMask;
}

template <>
inline const GlDepthMask&
GpuContextOgl::getFunction<GlDepthMask>() const {
    return _glDepthMask;
}

template <>
inline const GlDisable&
GpuContextOgl::getFunction<GlDisable>() const {
    return _glDisable;
}

template <>
inline const GlEnable&
GpuContextOgl::getFunction<GlEnable>() const {
    return _glEnable;
}

template <>
inline const GlFinish&
GpuContextOgl::getFunction<GlFinish>() const {
    return _glFinish;
}

template <>
inline const GlFlush&
GpuContextOgl::getFunction<GlFlush>() const {
    return _glFlush;
}

template <>
inline const GlBlendFunc&
GpuContextOgl::getFunction<GlBlendFunc>() const {
    return _glBlendFunc;
}

template <>
inline const GlLogicOp&
GpuContextOgl::getFunction<GlLogicOp>() const {
    return _glLogicOp;
}

template <>
inline const GlStencilFunc&
GpuContextOgl::getFunction<GlStencilFunc>() const {
    return _glStencilFunc;
}

template <>
inline const GlStencilOp&
GpuContextOgl::getFunction<GlStencilOp>() const {
    return _glStencilOp;
}

template <>
inline const GlDepthFunc&
GpuContextOgl::getFunction<GlDepthFunc>() const {
    return _glDepthFunc;
}

template <>
inline const GlPixelStoref&
GpuContextOgl::getFunction<GlPixelStoref>() const {
    return _glPixelStoref;
}

template <>
inline const GlPixelStorei&
GpuContextOgl::getFunction<GlPixelStorei>() const {
    return _glPixelStorei;
}

template <>
inline const GlReadBuffer&
GpuContextOgl::getFunction<GlReadBuffer>() const {
    return _glReadBuffer;
}

template <>
inline const GlReadPixels&
GpuContextOgl::getFunction<GlReadPixels>() const {
    return _glReadPixels;
}

template <>
inline const GlGetBooleanv&
GpuContextOgl::getFunction<GlGetBooleanv>() const {
    return _glGetBooleanv;
}

template <>
inline const GlGetDoublev&
GpuContextOgl::getFunction<GlGetDoublev>() const {
    return _glGetDoublev;
}

template <>
inline const GlGetError&
GpuContextOgl::getFunction<GlGetError>() const {
    return _glGetError;
}

template <>
inline const GlGetFloatv&
GpuContextOgl::getFunction<GlGetFloatv>() const {
    return _glGetFloatv;
}

template <>
inline const GlGetIntegerv&
GpuContextOgl::getFunction<GlGetIntegerv>() const {
    return _glGetIntegerv;
}

template <>
inline const GlGetString&
GpuContextOgl::getFunction<GlGetString>() const {
    return _glGetString;
}

template <>
inline const GlGetTexImage&
GpuContextOgl::getFunction<GlGetTexImage>() const {
    return _glGetTexImage;
}

template <>
inline const GlGetTexParameterfv&
GpuContextOgl::getFunction<GlGetTexParameterfv>() const {
    return _glGetTexParameterfv;
}

template <>
inline const GlGetTexParameteriv&
GpuContextOgl::getFunction<GlGetTexParameteriv>() const {
    return _glGetTexParameteriv;
}

template <>
inline const GlGetTexLevelParameterfv&
GpuContextOgl::getFunction<GlGetTexLevelParameterfv>() const {
    return _glGetTexLevelParameterfv;
}

template <>
inline const GlGetTexLevelParameteriv&
GpuContextOgl::getFunction<GlGetTexLevelParameteriv>() const {
    return _glGetTexLevelParameteriv;
}

template <>
inline const GlIsEnabled&
GpuContextOgl::getFunction<GlIsEnabled>() const {
    return _glIsEnabled;
}

template <>
inline const GlDepthRange&
GpuContextOgl::getFunction<GlDepthRange>() const {
    return _glDepthRange;
}

template <>
inline const GlViewport&
GpuContextOgl::getFunction<GlViewport>() const {
    return _glViewport;
}

template <>
inline const GlDrawArrays&
GpuContextOgl::getFunction<GlDrawArrays>() const {
    return _glDrawArrays;
}

template <>
inline const GlDrawElements&
GpuContextOgl::getFunction<GlDrawElements>() const {
    return _glDrawElements;
}

template <>
inline const GlGetPointerv&
GpuContextOgl::getFunction<GlGetPointerv>() const {
    return _glGetPointerv;
}

template <>
inline const GlPolygonOffset&
GpuContextOgl::getFunction<GlPolygonOffset>() const {
    return _glPolygonOffset;
}

template <>
inline const GlCopyTexImage1D&
GpuContextOgl::getFunction<GlCopyTexImage1D>() const {
    return _glCopyTexImage1D;
}

template <>
inline const GlCopyTexImage2D&
GpuContextOgl::getFunction<GlCopyTexImage2D>() const {
    return _glCopyTexImage2D;
}

template <>
inline const GlCopyTexSubImage1D&
GpuContextOgl::getFunction<GlCopyTexSubImage1D>() const {
    return _glCopyTexSubImage1D;
}

template <>
inline const GlCopyTexSubImage2D&
GpuContextOgl::getFunction<GlCopyTexSubImage2D>() const {
    return _glCopyTexSubImage2D;
}

template <>
inline const GlTexSubImage1D&
GpuContextOgl::getFunction<GlTexSubImage1D>() const {
    return _glTexSubImage1D;
}

template <>
inline const GlTexSubImage2D&
GpuContextOgl::getFunction<GlTexSubImage2D>() const {
    return _glTexSubImage2D;
}

template <>
inline const GlBindTexture&
GpuContextOgl::getFunction<GlBindTexture>() const {
    return _glBindTexture;
}

template <>
inline const GlDeleteTextures&
GpuContextOgl::getFunction<GlDeleteTextures>() const {
    return _glDeleteTextures;
}

template <>
inline const GlGenTextures&
GpuContextOgl::getFunction<GlGenTextures>() const {
    return _glGenTextures;
}

template <>
inline const GlIsTexture&
GpuContextOgl::getFunction<GlIsTexture>() const {
    return _glIsTexture;
}

template <>
inline const GlDrawRangeElements&
GpuContextOgl::getFunction<GlDrawRangeElements>() const {
    return _glDrawRangeElements;
}

template <>
inline const GlTexImage3D&
GpuContextOgl::getFunction<GlTexImage3D>() const {
    return _glTexImage3D;
}

template <>
inline const GlTexSubImage3D&
GpuContextOgl::getFunction<GlTexSubImage3D>() const {
    return _glTexSubImage3D;
}

template <>
inline const GlCopyTexSubImage3D&
GpuContextOgl::getFunction<GlCopyTexSubImage3D>() const {
    return _glCopyTexSubImage3D;
}

template <>
inline const GlActiveTexture&
GpuContextOgl::getFunction<GlActiveTexture>() const {
    return _glActiveTexture;
}

template <>
inline const GlSampleCoverage&
GpuContextOgl::getFunction<GlSampleCoverage>() const {
    return _glSampleCoverage;
}

template <>
inline const GlCompressedTexImage3D&
GpuContextOgl::getFunction<GlCompressedTexImage3D>() const {
    return _glCompressedTexImage3D;
}

template <>
inline const GlCompressedTexImage2D&
GpuContextOgl::getFunction<GlCompressedTexImage2D>() const {
    return _glCompressedTexImage2D;
}

template <>
inline const GlCompressedTexImage1D&
GpuContextOgl::getFunction<GlCompressedTexImage1D>() const {
    return _glCompressedTexImage1D;
}

template <>
inline const GlCompressedTexSubImage3D&
GpuContextOgl::getFunction<GlCompressedTexSubImage3D>() const {
    return _glCompressedTexSubImage3D;
}

template <>
inline const GlCompressedTexSubImage2D&
GpuContextOgl::getFunction<GlCompressedTexSubImage2D>() const {
    return _glCompressedTexSubImage2D;
}

template <>
inline const GlCompressedTexSubImage1D&
GpuContextOgl::getFunction<GlCompressedTexSubImage1D>() const {
    return _glCompressedTexSubImage1D;
}

template <>
inline const GlGetCompressedTexImage&
GpuContextOgl::getFunction<GlGetCompressedTexImage>() const {
    return _glGetCompressedTexImage;
}

template <>
inline const GlBlendFuncSeparate&
GpuContextOgl::getFunction<GlBlendFuncSeparate>() const {
    return _glBlendFuncSeparate;
}

template <>
inline const GlMultiDrawArrays&
GpuContextOgl::getFunction<GlMultiDrawArrays>() const {
    return _glMultiDrawArrays;
}

template <>
inline const GlMultiDrawElements&
GpuContextOgl::getFunction<GlMultiDrawElements>() const {
    return _glMultiDrawElements;
}

template <>
inline const GlPointParameterf&
GpuContextOgl::getFunction<GlPointParameterf>() const {
    return _glPointParameterf;
}

template <>
inline const GlPointParameterfv&
GpuContextOgl::getFunction<GlPointParameterfv>() const {
    return _glPointParameterfv;
}

template <>
inline const GlPointParameteri&
GpuContextOgl::getFunction<GlPointParameteri>() const {
    return _glPointParameteri;
}

template <>
inline const GlPointParameteriv&
GpuContextOgl::getFunction<GlPointParameteriv>() const {
    return _glPointParameteriv;
}

template <>
inline const GlBlendColor&
GpuContextOgl::getFunction<GlBlendColor>() const {
    return _glBlendColor;
}

template <>
inline const GlBlendEquation&
GpuContextOgl::getFunction<GlBlendEquation>() const {
    return _glBlendEquation;
}

template <>
inline const GlGenQueries&
GpuContextOgl::getFunction<GlGenQueries>() const {
    return _glGenQueries;
}

template <>
inline const GlDeleteQueries&
GpuContextOgl::getFunction<GlDeleteQueries>() const {
    return _glDeleteQueries;
}

template <>
inline const GlIsQuery&
GpuContextOgl::getFunction<GlIsQuery>() const {
    return _glIsQuery;
}

template <>
inline const GlBeginQuery&
GpuContextOgl::getFunction<GlBeginQuery>() const {
    return _glBeginQuery;
}

template <>
inline const GlEndQuery&
GpuContextOgl::getFunction<GlEndQuery>() const {
    return _glEndQuery;
}

template <>
inline const GlGetQueryiv&
GpuContextOgl::getFunction<GlGetQueryiv>() const {
    return _glGetQueryiv;
}

template <>
inline const GlGetQueryObjectiv&
GpuContextOgl::getFunction<GlGetQueryObjectiv>() const {
    return _glGetQueryObjectiv;
}

template <>
inline const GlGetQueryObjectuiv&
GpuContextOgl::getFunction<GlGetQueryObjectuiv>() const {
    return _glGetQueryObjectuiv;
}

template <>
inline const GlBindBuffer&
GpuContextOgl::getFunction<GlBindBuffer>() const {
    return _glBindBuffer;
}

template <>
inline const GlDeleteBuffers&
GpuContextOgl::getFunction<GlDeleteBuffers>() const {
    return _glDeleteBuffers;
}

template <>
inline const GlGenBuffers&
GpuContextOgl::getFunction<GlGenBuffers>() const {
    return _glGenBuffers;
}

template <>
inline const GlIsBuffer&
GpuContextOgl::getFunction<GlIsBuffer>() const {
    return _glIsBuffer;
}

template <>
inline const GlBufferData&
GpuContextOgl::getFunction<GlBufferData>() const {
    return _glBufferData;
}

template <>
inline const GlBufferSubData&
GpuContextOgl::getFunction<GlBufferSubData>() const {
    return _glBufferSubData;
}

template <>
inline const GlGetBufferSubData&
GpuContextOgl::getFunction<GlGetBufferSubData>() const {
    return _glGetBufferSubData;
}

template <>
inline const GlMapBuffer&
GpuContextOgl::getFunction<GlMapBuffer>() const {
    return _glMapBuffer;
}

template <>
inline const GlUnmapBuffer&
GpuContextOgl::getFunction<GlUnmapBuffer>() const {
    return _glUnmapBuffer;
}

template <>
inline const GlGetBufferParameteriv&
GpuContextOgl::getFunction<GlGetBufferParameteriv>() const {
    return _glGetBufferParameteriv;
}

template <>
inline const GlGetBufferPointerv&
GpuContextOgl::getFunction<GlGetBufferPointerv>() const {
    return _glGetBufferPointerv;
}

template <>
inline const GlBlendEquationSeparate&
GpuContextOgl::getFunction<GlBlendEquationSeparate>() const {
    return _glBlendEquationSeparate;
}

template <>
inline const GlDrawBuffers&
GpuContextOgl::getFunction<GlDrawBuffers>() const {
    return _glDrawBuffers;
}

template <>
inline const GlStencilOpSeparate&
GpuContextOgl::getFunction<GlStencilOpSeparate>() const {
    return _glStencilOpSeparate;
}

template <>
inline const GlStencilFuncSeparate&
GpuContextOgl::getFunction<GlStencilFuncSeparate>() const {
    return _glStencilFuncSeparate;
}

template <>
inline const GlStencilMaskSeparate&
GpuContextOgl::getFunction<GlStencilMaskSeparate>() const {
    return _glStencilMaskSeparate;
}

template <>
inline const GlAttachShader&
GpuContextOgl::getFunction<GlAttachShader>() const {
    return _glAttachShader;
}

template <>
inline const GlBindAttribLocation&
GpuContextOgl::getFunction<GlBindAttribLocation>() const {
    return _glBindAttribLocation;
}

template <>
inline const GlCompileShader&
GpuContextOgl::getFunction<GlCompileShader>() const {
    return _glCompileShader;
}

template <>
inline const GlCreateProgram&
GpuContextOgl::getFunction<GlCreateProgram>() const {
    return _glCreateProgram;
}

template <>
inline const GlCreateShader&
GpuContextOgl::getFunction<GlCreateShader>() const {
    return _glCreateShader;
}

template <>
inline const GlDeleteProgram&
GpuContextOgl::getFunction<GlDeleteProgram>() const {
    return _glDeleteProgram;
}

template <>
inline const GlDeleteShader&
GpuContextOgl::getFunction<GlDeleteShader>() const {
    return _glDeleteShader;
}

template <>
inline const GlDetachShader&
GpuContextOgl::getFunction<GlDetachShader>() const {
    return _glDetachShader;
}

template <>
inline const GlDisableVertexAttribArray&
GpuContextOgl::getFunction<GlDisableVertexAttribArray>() const {
    return _glDisableVertexAttribArray;
}

template <>
inline const GlEnableVertexAttribArray&
GpuContextOgl::getFunction<GlEnableVertexAttribArray>() const {
    return _glEnableVertexAttribArray;
}

template <>
inline const GlGetActiveAttrib&
GpuContextOgl::getFunction<GlGetActiveAttrib>() const {
    return _glGetActiveAttrib;
}

template <>
inline const GlGetActiveUniform&
GpuContextOgl::getFunction<GlGetActiveUniform>() const {
    return _glGetActiveUniform;
}

template <>
inline const GlGetAttachedShaders&
GpuContextOgl::getFunction<GlGetAttachedShaders>() const {
    return _glGetAttachedShaders;
}

template <>
inline const GlGetAttribLocation&
GpuContextOgl::getFunction<GlGetAttribLocation>() const {
    return _glGetAttribLocation;
}

template <>
inline const GlGetProgramiv&
GpuContextOgl::getFunction<GlGetProgramiv>() const {
    return _glGetProgramiv;
}

template <>
inline const GlGetProgramInfoLog&
GpuContextOgl::getFunction<GlGetProgramInfoLog>() const {
    return _glGetProgramInfoLog;
}

template <>
inline const GlGetShaderiv&
GpuContextOgl::getFunction<GlGetShaderiv>() const {
    return _glGetShaderiv;
}

template <>
inline const GlGetShaderInfoLog&
GpuContextOgl::getFunction<GlGetShaderInfoLog>() const {
    return _glGetShaderInfoLog;
}

template <>
inline const GlGetShaderSource&
GpuContextOgl::getFunction<GlGetShaderSource>() const {
    return _glGetShaderSource;
}

template <>
inline const GlGetUniformLocation&
GpuContextOgl::getFunction<GlGetUniformLocation>() const {
    return _glGetUniformLocation;
}

template <>
inline const GlGetUniformfv&
GpuContextOgl::getFunction<GlGetUniformfv>() const {
    return _glGetUniformfv;
}

template <>
inline const GlGetUniformiv&
GpuContextOgl::getFunction<GlGetUniformiv>() const {
    return _glGetUniformiv;
}

template <>
inline const GlGetVertexAttribdv&
GpuContextOgl::getFunction<GlGetVertexAttribdv>() const {
    return _glGetVertexAttribdv;
}

template <>
inline const GlGetVertexAttribfv&
GpuContextOgl::getFunction<GlGetVertexAttribfv>() const {
    return _glGetVertexAttribfv;
}

template <>
inline const GlGetVertexAttribiv&
GpuContextOgl::getFunction<GlGetVertexAttribiv>() const {
    return _glGetVertexAttribiv;
}

template <>
inline const GlGetVertexAttribPointerv&
GpuContextOgl::getFunction<GlGetVertexAttribPointerv>() const {
    return _glGetVertexAttribPointerv;
}

template <>
inline const GlIsProgram&
GpuContextOgl::getFunction<GlIsProgram>() const {
    return _glIsProgram;
}

template <>
inline const GlIsShader&
GpuContextOgl::getFunction<GlIsShader>() const {
    return _glIsShader;
}

template <>
inline const GlLinkProgram&
GpuContextOgl::getFunction<GlLinkProgram>() const {
    return _glLinkProgram;
}

template <>
inline const GlShaderSource&
GpuContextOgl::getFunction<GlShaderSource>() const {
    return _glShaderSource;
}

template <>
inline const GlUseProgram&
GpuContextOgl::getFunction<GlUseProgram>() const {
    return _glUseProgram;
}

template <>
inline const GlUniform1f&
GpuContextOgl::getFunction<GlUniform1f>() const {
    return _glUniform1f;
}

template <>
inline const GlUniform2f&
GpuContextOgl::getFunction<GlUniform2f>() const {
    return _glUniform2f;
}

template <>
inline const GlUniform3f&
GpuContextOgl::getFunction<GlUniform3f>() const {
    return _glUniform3f;
}

template <>
inline const GlUniform4f&
GpuContextOgl::getFunction<GlUniform4f>() const {
    return _glUniform4f;
}

template <>
inline const GlUniform1i&
GpuContextOgl::getFunction<GlUniform1i>() const {
    return _glUniform1i;
}

template <>
inline const GlUniform2i&
GpuContextOgl::getFunction<GlUniform2i>() const {
    return _glUniform2i;
}

template <>
inline const GlUniform3i&
GpuContextOgl::getFunction<GlUniform3i>() const {
    return _glUniform3i;
}

template <>
inline const GlUniform4i&
GpuContextOgl::getFunction<GlUniform4i>() const {
    return _glUniform4i;
}

template <>
inline const GlUniform1fv&
GpuContextOgl::getFunction<GlUniform1fv>() const {
    return _glUniform1fv;
}

template <>
inline const GlUniform2fv&
GpuContextOgl::getFunction<GlUniform2fv>() const {
    return _glUniform2fv;
}

template <>
inline const GlUniform3fv&
GpuContextOgl::getFunction<GlUniform3fv>() const {
    return _glUniform3fv;
}

template <>
inline const GlUniform4fv&
GpuContextOgl::getFunction<GlUniform4fv>() const {
    return _glUniform4fv;
}

template <>
inline const GlUniform1iv&
GpuContextOgl::getFunction<GlUniform1iv>() const {
    return _glUniform1iv;
}

template <>
inline const GlUniform2iv&
GpuContextOgl::getFunction<GlUniform2iv>() const {
    return _glUniform2iv;
}

template <>
inline const GlUniform3iv&
GpuContextOgl::getFunction<GlUniform3iv>() const {
    return _glUniform3iv;
}

template <>
inline const GlUniform4iv&
GpuContextOgl::getFunction<GlUniform4iv>() const {
    return _glUniform4iv;
}

template <>
inline const GlUniformMatrix2fv&
GpuContextOgl::getFunction<GlUniformMatrix2fv>() const {
    return _glUniformMatrix2fv;
}

template <>
inline const GlUniformMatrix3fv&
GpuContextOgl::getFunction<GlUniformMatrix3fv>() const {
    return _glUniformMatrix3fv;
}

template <>
inline const GlUniformMatrix4fv&
GpuContextOgl::getFunction<GlUniformMatrix4fv>() const {
    return _glUniformMatrix4fv;
}

template <>
inline const GlValidateProgram&
GpuContextOgl::getFunction<GlValidateProgram>() const {
    return _glValidateProgram;
}

template <>
inline const GlVertexAttrib1d&
GpuContextOgl::getFunction<GlVertexAttrib1d>() const {
    return _glVertexAttrib1d;
}

template <>
inline const GlVertexAttrib1dv&
GpuContextOgl::getFunction<GlVertexAttrib1dv>() const {
    return _glVertexAttrib1dv;
}

template <>
inline const GlVertexAttrib1f&
GpuContextOgl::getFunction<GlVertexAttrib1f>() const {
    return _glVertexAttrib1f;
}

template <>
inline const GlVertexAttrib1fv&
GpuContextOgl::getFunction<GlVertexAttrib1fv>() const {
    return _glVertexAttrib1fv;
}

template <>
inline const GlVertexAttrib1s&
GpuContextOgl::getFunction<GlVertexAttrib1s>() const {
    return _glVertexAttrib1s;
}

template <>
inline const GlVertexAttrib1sv&
GpuContextOgl::getFunction<GlVertexAttrib1sv>() const {
    return _glVertexAttrib1sv;
}

template <>
inline const GlVertexAttrib2d&
GpuContextOgl::getFunction<GlVertexAttrib2d>() const {
    return _glVertexAttrib2d;
}

template <>
inline const GlVertexAttrib2dv&
GpuContextOgl::getFunction<GlVertexAttrib2dv>() const {
    return _glVertexAttrib2dv;
}

template <>
inline const GlVertexAttrib2f&
GpuContextOgl::getFunction<GlVertexAttrib2f>() const {
    return _glVertexAttrib2f;
}

template <>
inline const GlVertexAttrib2fv&
GpuContextOgl::getFunction<GlVertexAttrib2fv>() const {
    return _glVertexAttrib2fv;
}

template <>
inline const GlVertexAttrib2s&
GpuContextOgl::getFunction<GlVertexAttrib2s>() const {
    return _glVertexAttrib2s;
}

template <>
inline const GlVertexAttrib2sv&
GpuContextOgl::getFunction<GlVertexAttrib2sv>() const {
    return _glVertexAttrib2sv;
}

template <>
inline const GlVertexAttrib3d&
GpuContextOgl::getFunction<GlVertexAttrib3d>() const {
    return _glVertexAttrib3d;
}

template <>
inline const GlVertexAttrib3dv&
GpuContextOgl::getFunction<GlVertexAttrib3dv>() const {
    return _glVertexAttrib3dv;
}

template <>
inline const GlVertexAttrib3f&
GpuContextOgl::getFunction<GlVertexAttrib3f>() const {
    return _glVertexAttrib3f;
}

template <>
inline const GlVertexAttrib3fv&
GpuContextOgl::getFunction<GlVertexAttrib3fv>() const {
    return _glVertexAttrib3fv;
}

template <>
inline const GlVertexAttrib3s&
GpuContextOgl::getFunction<GlVertexAttrib3s>() const {
    return _glVertexAttrib3s;
}

template <>
inline const GlVertexAttrib3sv&
GpuContextOgl::getFunction<GlVertexAttrib3sv>() const {
    return _glVertexAttrib3sv;
}

template <>
inline const GlVertexAttrib4Nbv&
GpuContextOgl::getFunction<GlVertexAttrib4Nbv>() const {
    return _glVertexAttrib4Nbv;
}

template <>
inline const GlVertexAttrib4Niv&
GpuContextOgl::getFunction<GlVertexAttrib4Niv>() const {
    return _glVertexAttrib4Niv;
}

template <>
inline const GlVertexAttrib4Nsv&
GpuContextOgl::getFunction<GlVertexAttrib4Nsv>() const {
    return _glVertexAttrib4Nsv;
}

template <>
inline const GlVertexAttrib4Nub&
GpuContextOgl::getFunction<GlVertexAttrib4Nub>() const {
    return _glVertexAttrib4Nub;
}

template <>
inline const GlVertexAttrib4Nubv&
GpuContextOgl::getFunction<GlVertexAttrib4Nubv>() const {
    return _glVertexAttrib4Nubv;
}

template <>
inline const GlVertexAttrib4Nuiv&
GpuContextOgl::getFunction<GlVertexAttrib4Nuiv>() const {
    return _glVertexAttrib4Nuiv;
}

template <>
inline const GlVertexAttrib4Nusv&
GpuContextOgl::getFunction<GlVertexAttrib4Nusv>() const {
    return _glVertexAttrib4Nusv;
}

template <>
inline const GlVertexAttrib4bv&
GpuContextOgl::getFunction<GlVertexAttrib4bv>() const {
    return _glVertexAttrib4bv;
}

template <>
inline const GlVertexAttrib4d&
GpuContextOgl::getFunction<GlVertexAttrib4d>() const {
    return _glVertexAttrib4d;
}

template <>
inline const GlVertexAttrib4dv&
GpuContextOgl::getFunction<GlVertexAttrib4dv>() const {
    return _glVertexAttrib4dv;
}

template <>
inline const GlVertexAttrib4f&
GpuContextOgl::getFunction<GlVertexAttrib4f>() const {
    return _glVertexAttrib4f;
}

template <>
inline const GlVertexAttrib4fv&
GpuContextOgl::getFunction<GlVertexAttrib4fv>() const {
    return _glVertexAttrib4fv;
}

template <>
inline const GlVertexAttrib4iv&
GpuContextOgl::getFunction<GlVertexAttrib4iv>() const {
    return _glVertexAttrib4iv;
}

template <>
inline const GlVertexAttrib4s&
GpuContextOgl::getFunction<GlVertexAttrib4s>() const {
    return _glVertexAttrib4s;
}

template <>
inline const GlVertexAttrib4sv&
GpuContextOgl::getFunction<GlVertexAttrib4sv>() const {
    return _glVertexAttrib4sv;
}

template <>
inline const GlVertexAttrib4ubv&
GpuContextOgl::getFunction<GlVertexAttrib4ubv>() const {
    return _glVertexAttrib4ubv;
}

template <>
inline const GlVertexAttrib4uiv&
GpuContextOgl::getFunction<GlVertexAttrib4uiv>() const {
    return _glVertexAttrib4uiv;
}

template <>
inline const GlVertexAttrib4usv&
GpuContextOgl::getFunction<GlVertexAttrib4usv>() const {
    return _glVertexAttrib4usv;
}

template <>
inline const GlVertexAttribPointer&
GpuContextOgl::getFunction<GlVertexAttribPointer>() const {
    return _glVertexAttribPointer;
}

template <>
inline const GlUniformMatrix2x3fv&
GpuContextOgl::getFunction<GlUniformMatrix2x3fv>() const {
    return _glUniformMatrix2x3fv;
}

template <>
inline const GlUniformMatrix3x2fv&
GpuContextOgl::getFunction<GlUniformMatrix3x2fv>() const {
    return _glUniformMatrix3x2fv;
}

template <>
inline const GlUniformMatrix2x4fv&
GpuContextOgl::getFunction<GlUniformMatrix2x4fv>() const {
    return _glUniformMatrix2x4fv;
}

template <>
inline const GlUniformMatrix4x2fv&
GpuContextOgl::getFunction<GlUniformMatrix4x2fv>() const {
    return _glUniformMatrix4x2fv;
}

template <>
inline const GlUniformMatrix3x4fv&
GpuContextOgl::getFunction<GlUniformMatrix3x4fv>() const {
    return _glUniformMatrix3x4fv;
}

template <>
inline const GlUniformMatrix4x3fv&
GpuContextOgl::getFunction<GlUniformMatrix4x3fv>() const {
    return _glUniformMatrix4x3fv;
}

template <>
inline const GlColorMaski&
GpuContextOgl::getFunction<GlColorMaski>() const {
    return _glColorMaski;
}

template <>
inline const GlGetBooleani_v&
GpuContextOgl::getFunction<GlGetBooleani_v>() const {
    return _glGetBooleani_v;
}

template <>
inline const GlGetIntegeri_v&
GpuContextOgl::getFunction<GlGetIntegeri_v>() const {
    return _glGetIntegeri_v;
}

template <>
inline const GlEnablei&
GpuContextOgl::getFunction<GlEnablei>() const {
    return _glEnablei;
}

template <>
inline const GlDisablei&
GpuContextOgl::getFunction<GlDisablei>() const {
    return _glDisablei;
}

template <>
inline const GlIsEnabledi&
GpuContextOgl::getFunction<GlIsEnabledi>() const {
    return _glIsEnabledi;
}

template <>
inline const GlBeginTransformFeedback&
GpuContextOgl::getFunction<GlBeginTransformFeedback>() const {
    return _glBeginTransformFeedback;
}

template <>
inline const GlEndTransformFeedback&
GpuContextOgl::getFunction<GlEndTransformFeedback>() const {
    return _glEndTransformFeedback;
}

template <>
inline const GlBindBufferRange&
GpuContextOgl::getFunction<GlBindBufferRange>() const {
    return _glBindBufferRange;
}

template <>
inline const GlBindBufferBase&
GpuContextOgl::getFunction<GlBindBufferBase>() const {
    return _glBindBufferBase;
}

template <>
inline const GlTransformFeedbackVaryings&
GpuContextOgl::getFunction<GlTransformFeedbackVaryings>() const {
    return _glTransformFeedbackVaryings;
}

template <>
inline const GlGetTransformFeedbackVarying&
GpuContextOgl::getFunction<GlGetTransformFeedbackVarying>() const {
    return _glGetTransformFeedbackVarying;
}

template <>
inline const GlClampColor&
GpuContextOgl::getFunction<GlClampColor>() const {
    return _glClampColor;
}

template <>
inline const GlBeginConditionalRender&
GpuContextOgl::getFunction<GlBeginConditionalRender>() const {
    return _glBeginConditionalRender;
}

template <>
inline const GlEndConditionalRender&
GpuContextOgl::getFunction<GlEndConditionalRender>() const {
    return _glEndConditionalRender;
}

template <>
inline const GlVertexAttribIPointer&
GpuContextOgl::getFunction<GlVertexAttribIPointer>() const {
    return _glVertexAttribIPointer;
}

template <>
inline const GlGetVertexAttribIiv&
GpuContextOgl::getFunction<GlGetVertexAttribIiv>() const {
    return _glGetVertexAttribIiv;
}

template <>
inline const GlGetVertexAttribIuiv&
GpuContextOgl::getFunction<GlGetVertexAttribIuiv>() const {
    return _glGetVertexAttribIuiv;
}

template <>
inline const GlVertexAttribI1i&
GpuContextOgl::getFunction<GlVertexAttribI1i>() const {
    return _glVertexAttribI1i;
}

template <>
inline const GlVertexAttribI2i&
GpuContextOgl::getFunction<GlVertexAttribI2i>() const {
    return _glVertexAttribI2i;
}

template <>
inline const GlVertexAttribI3i&
GpuContextOgl::getFunction<GlVertexAttribI3i>() const {
    return _glVertexAttribI3i;
}

template <>
inline const GlVertexAttribI4i&
GpuContextOgl::getFunction<GlVertexAttribI4i>() const {
    return _glVertexAttribI4i;
}

template <>
inline const GlVertexAttribI1ui&
GpuContextOgl::getFunction<GlVertexAttribI1ui>() const {
    return _glVertexAttribI1ui;
}

template <>
inline const GlVertexAttribI2ui&
GpuContextOgl::getFunction<GlVertexAttribI2ui>() const {
    return _glVertexAttribI2ui;
}

template <>
inline const GlVertexAttribI3ui&
GpuContextOgl::getFunction<GlVertexAttribI3ui>() const {
    return _glVertexAttribI3ui;
}

template <>
inline const GlVertexAttribI4ui&
GpuContextOgl::getFunction<GlVertexAttribI4ui>() const {
    return _glVertexAttribI4ui;
}

template <>
inline const GlVertexAttribI1iv&
GpuContextOgl::getFunction<GlVertexAttribI1iv>() const {
    return _glVertexAttribI1iv;
}

template <>
inline const GlVertexAttribI2iv&
GpuContextOgl::getFunction<GlVertexAttribI2iv>() const {
    return _glVertexAttribI2iv;
}

template <>
inline const GlVertexAttribI3iv&
GpuContextOgl::getFunction<GlVertexAttribI3iv>() const {
    return _glVertexAttribI3iv;
}

template <>
inline const GlVertexAttribI4iv&
GpuContextOgl::getFunction<GlVertexAttribI4iv>() const {
    return _glVertexAttribI4iv;
}

template <>
inline const GlVertexAttribI1uiv&
GpuContextOgl::getFunction<GlVertexAttribI1uiv>() const {
    return _glVertexAttribI1uiv;
}

template <>
inline const GlVertexAttribI2uiv&
GpuContextOgl::getFunction<GlVertexAttribI2uiv>() const {
    return _glVertexAttribI2uiv;
}

template <>
inline const GlVertexAttribI3uiv&
GpuContextOgl::getFunction<GlVertexAttribI3uiv>() const {
    return _glVertexAttribI3uiv;
}

template <>
inline const GlVertexAttribI4uiv&
GpuContextOgl::getFunction<GlVertexAttribI4uiv>() const {
    return _glVertexAttribI4uiv;
}

template <>
inline const GlVertexAttribI4bv&
GpuContextOgl::getFunction<GlVertexAttribI4bv>() const {
    return _glVertexAttribI4bv;
}

template <>
inline const GlVertexAttribI4sv&
GpuContextOgl::getFunction<GlVertexAttribI4sv>() const {
    return _glVertexAttribI4sv;
}

template <>
inline const GlVertexAttribI4ubv&
GpuContextOgl::getFunction<GlVertexAttribI4ubv>() const {
    return _glVertexAttribI4ubv;
}

template <>
inline const GlVertexAttribI4usv&
GpuContextOgl::getFunction<GlVertexAttribI4usv>() const {
    return _glVertexAttribI4usv;
}

template <>
inline const GlGetUniformuiv&
GpuContextOgl::getFunction<GlGetUniformuiv>() const {
    return _glGetUniformuiv;
}

template <>
inline const GlBindFragDataLocation&
GpuContextOgl::getFunction<GlBindFragDataLocation>() const {
    return _glBindFragDataLocation;
}

template <>
inline const GlGetFragDataLocation&
GpuContextOgl::getFunction<GlGetFragDataLocation>() const {
    return _glGetFragDataLocation;
}

template <>
inline const GlUniform1ui&
GpuContextOgl::getFunction<GlUniform1ui>() const {
    return _glUniform1ui;
}

template <>
inline const GlUniform2ui&
GpuContextOgl::getFunction<GlUniform2ui>() const {
    return _glUniform2ui;
}

template <>
inline const GlUniform3ui&
GpuContextOgl::getFunction<GlUniform3ui>() const {
    return _glUniform3ui;
}

template <>
inline const GlUniform4ui&
GpuContextOgl::getFunction<GlUniform4ui>() const {
    return _glUniform4ui;
}

template <>
inline const GlUniform1uiv&
GpuContextOgl::getFunction<GlUniform1uiv>() const {
    return _glUniform1uiv;
}

template <>
inline const GlUniform2uiv&
GpuContextOgl::getFunction<GlUniform2uiv>() const {
    return _glUniform2uiv;
}

template <>
inline const GlUniform3uiv&
GpuContextOgl::getFunction<GlUniform3uiv>() const {
    return _glUniform3uiv;
}

template <>
inline const GlUniform4uiv&
GpuContextOgl::getFunction<GlUniform4uiv>() const {
    return _glUniform4uiv;
}

template <>
inline const GlTexParameterIiv&
GpuContextOgl::getFunction<GlTexParameterIiv>() const {
    return _glTexParameterIiv;
}

template <>
inline const GlTexParameterIuiv&
GpuContextOgl::getFunction<GlTexParameterIuiv>() const {
    return _glTexParameterIuiv;
}

template <>
inline const GlGetTexParameterIiv&
GpuContextOgl::getFunction<GlGetTexParameterIiv>() const {
    return _glGetTexParameterIiv;
}

template <>
inline const GlGetTexParameterIuiv&
GpuContextOgl::getFunction<GlGetTexParameterIuiv>() const {
    return _glGetTexParameterIuiv;
}

template <>
inline const GlClearBufferiv&
GpuContextOgl::getFunction<GlClearBufferiv>() const {
    return _glClearBufferiv;
}

template <>
inline const GlClearBufferuiv&
GpuContextOgl::getFunction<GlClearBufferuiv>() const {
    return _glClearBufferuiv;
}

template <>
inline const GlClearBufferfv&
GpuContextOgl::getFunction<GlClearBufferfv>() const {
    return _glClearBufferfv;
}

template <>
inline const GlClearBufferfi&
GpuContextOgl::getFunction<GlClearBufferfi>() const {
    return _glClearBufferfi;
}

template <>
inline const GlGetStringi&
GpuContextOgl::getFunction<GlGetStringi>() const {
    return _glGetStringi;
}

template <>
inline const GlIsRenderbuffer&
GpuContextOgl::getFunction<GlIsRenderbuffer>() const {
    return _glIsRenderbuffer;
}

template <>
inline const GlBindRenderbuffer&
GpuContextOgl::getFunction<GlBindRenderbuffer>() const {
    return _glBindRenderbuffer;
}

template <>
inline const GlDeleteRenderbuffers&
GpuContextOgl::getFunction<GlDeleteRenderbuffers>() const {
    return _glDeleteRenderbuffers;
}

template <>
inline const GlGenRenderbuffers&
GpuContextOgl::getFunction<GlGenRenderbuffers>() const {
    return _glGenRenderbuffers;
}

template <>
inline const GlRenderbufferStorage&
GpuContextOgl::getFunction<GlRenderbufferStorage>() const {
    return _glRenderbufferStorage;
}

template <>
inline const GlGetRenderbufferParameteriv&
GpuContextOgl::getFunction<GlGetRenderbufferParameteriv>() const {
    return _glGetRenderbufferParameteriv;
}

template <>
inline const GlIsFramebuffer&
GpuContextOgl::getFunction<GlIsFramebuffer>() const {
    return _glIsFramebuffer;
}

template <>
inline const GlBindFramebuffer&
GpuContextOgl::getFunction<GlBindFramebuffer>() const {
    return _glBindFramebuffer;
}

template <>
inline const GlDeleteFramebuffers&
GpuContextOgl::getFunction<GlDeleteFramebuffers>() const {
    return _glDeleteFramebuffers;
}

template <>
inline const GlGenFramebuffers&
GpuContextOgl::getFunction<GlGenFramebuffers>() const {
    return _glGenFramebuffers;
}

template <>
inline const GlCheckFramebufferStatus&
GpuContextOgl::getFunction<GlCheckFramebufferStatus>() const {
    return _glCheckFramebufferStatus;
}

template <>
inline const GlFramebufferTexture1D&
GpuContextOgl::getFunction<GlFramebufferTexture1D>() const {
    return _glFramebufferTexture1D;
}

template <>
inline const GlFramebufferTexture2D&
GpuContextOgl::getFunction<GlFramebufferTexture2D>() const {
    return _glFramebufferTexture2D;
}

template <>
inline const GlFramebufferTexture3D&
GpuContextOgl::getFunction<GlFramebufferTexture3D>() const {
    return _glFramebufferTexture3D;
}

template <>
inline const GlFramebufferRenderbuffer&
GpuContextOgl::getFunction<GlFramebufferRenderbuffer>() const {
    return _glFramebufferRenderbuffer;
}

template <>
inline const GlGetFramebufferAttachmentParameteriv&
GpuContextOgl::getFunction<GlGetFramebufferAttachmentParameteriv>() const {
    return _glGetFramebufferAttachmentParameteriv;
}

template <>
inline const GlGenerateMipmap&
GpuContextOgl::getFunction<GlGenerateMipmap>() const {
    return _glGenerateMipmap;
}

template <>
inline const GlBlitFramebuffer&
GpuContextOgl::getFunction<GlBlitFramebuffer>() const {
    return _glBlitFramebuffer;
}

template <>
inline const GlRenderbufferStorageMultisample&
GpuContextOgl::getFunction<GlRenderbufferStorageMultisample>() const {
    return _glRenderbufferStorageMultisample;
}

template <>
inline const GlFramebufferTextureLayer&
GpuContextOgl::getFunction<GlFramebufferTextureLayer>() const {
    return _glFramebufferTextureLayer;
}

template <>
inline const GlMapBufferRange&
GpuContextOgl::getFunction<GlMapBufferRange>() const {
    return _glMapBufferRange;
}

template <>
inline const GlFlushMappedBufferRange&
GpuContextOgl::getFunction<GlFlushMappedBufferRange>() const {
    return _glFlushMappedBufferRange;
}

template <>
inline const GlBindVertexArray&
GpuContextOgl::getFunction<GlBindVertexArray>() const {
    return _glBindVertexArray;
}

template <>
inline const GlDeleteVertexArrays&
GpuContextOgl::getFunction<GlDeleteVertexArrays>() const {
    return _glDeleteVertexArrays;
}

template <>
inline const GlGenVertexArrays&
GpuContextOgl::getFunction<GlGenVertexArrays>() const {
    return _glGenVertexArrays;
}

template <>
inline const GlIsVertexArray&
GpuContextOgl::getFunction<GlIsVertexArray>() const {
    return _glIsVertexArray;
}

template <>
inline const GlDrawArraysInstanced&
GpuContextOgl::getFunction<GlDrawArraysInstanced>() const {
    return _glDrawArraysInstanced;
}

template <>
inline const GlDrawElementsInstanced&
GpuContextOgl::getFunction<GlDrawElementsInstanced>() const {
    return _glDrawElementsInstanced;
}

template <>
inline const GlTexBuffer&
GpuContextOgl::getFunction<GlTexBuffer>() const {
    return _glTexBuffer;
}

template <>
inline const GlPrimitiveRestartIndex&
GpuContextOgl::getFunction<GlPrimitiveRestartIndex>() const {
    return _glPrimitiveRestartIndex;
}

template <>
inline const GlCopyBufferSubData&
GpuContextOgl::getFunction<GlCopyBufferSubData>() const {
    return _glCopyBufferSubData;
}

template <>
inline const GlGetUniformIndices&
GpuContextOgl::getFunction<GlGetUniformIndices>() const {
    return _glGetUniformIndices;
}

template <>
inline const GlGetActiveUniformsiv&
GpuContextOgl::getFunction<GlGetActiveUniformsiv>() const {
    return _glGetActiveUniformsiv;
}

template <>
inline const GlGetActiveUniformName&
GpuContextOgl::getFunction<GlGetActiveUniformName>() const {
    return _glGetActiveUniformName;
}

template <>
inline const GlGetUniformBlockIndex&
GpuContextOgl::getFunction<GlGetUniformBlockIndex>() const {
    return _glGetUniformBlockIndex;
}

template <>
inline const GlGetActiveUniformBlockiv&
GpuContextOgl::getFunction<GlGetActiveUniformBlockiv>() const {
    return _glGetActiveUniformBlockiv;
}

template <>
inline const GlGetActiveUniformBlockName&
GpuContextOgl::getFunction<GlGetActiveUniformBlockName>() const {
    return _glGetActiveUniformBlockName;
}

template <>
inline const GlUniformBlockBinding&
GpuContextOgl::getFunction<GlUniformBlockBinding>() const {
    return _glUniformBlockBinding;
}

template <>
inline const GlDrawElementsBaseVertex&
GpuContextOgl::getFunction<GlDrawElementsBaseVertex>() const {
    return _glDrawElementsBaseVertex;
}

template <>
inline const GlDrawRangeElementsBaseVertex&
GpuContextOgl::getFunction<GlDrawRangeElementsBaseVertex>() const {
    return _glDrawRangeElementsBaseVertex;
}

template <>
inline const GlDrawElementsInstancedBaseVertex&
GpuContextOgl::getFunction<GlDrawElementsInstancedBaseVertex>() const {
    return _glDrawElementsInstancedBaseVertex;
}

template <>
inline const GlMultiDrawElementsBaseVertex&
GpuContextOgl::getFunction<GlMultiDrawElementsBaseVertex>() const {
    return _glMultiDrawElementsBaseVertex;
}

template <>
inline const GlProvokingVertex&
GpuContextOgl::getFunction<GlProvokingVertex>() const {
    return _glProvokingVertex;
}

template <>
inline const GlFenceSync&
GpuContextOgl::getFunction<GlFenceSync>() const {
    return _glFenceSync;
}

template <>
inline const GlIsSync&
GpuContextOgl::getFunction<GlIsSync>() const {
    return _glIsSync;
}

template <>
inline const GlDeleteSync&
GpuContextOgl::getFunction<GlDeleteSync>() const {
    return _glDeleteSync;
}

template <>
inline const GlClientWaitSync&
GpuContextOgl::getFunction<GlClientWaitSync>() const {
    return _glClientWaitSync;
}

template <>
inline const GlWaitSync&
GpuContextOgl::getFunction<GlWaitSync>() const {
    return _glWaitSync;
}

template <>
inline const GlGetInteger64v&
GpuContextOgl::getFunction<GlGetInteger64v>() const {
    return _glGetInteger64v;
}

template <>
inline const GlGetSynciv&
GpuContextOgl::getFunction<GlGetSynciv>() const {
    return _glGetSynciv;
}

template <>
inline const GlGetInteger64i_v&
GpuContextOgl::getFunction<GlGetInteger64i_v>() const {
    return _glGetInteger64i_v;
}

template <>
inline const GlGetBufferParameteri64v&
GpuContextOgl::getFunction<GlGetBufferParameteri64v>() const {
    return _glGetBufferParameteri64v;
}

template <>
inline const GlFramebufferTexture&
GpuContextOgl::getFunction<GlFramebufferTexture>() const {
    return _glFramebufferTexture;
}

template <>
inline const GlTexImage2DMultisample&
GpuContextOgl::getFunction<GlTexImage2DMultisample>() const {
    return _glTexImage2DMultisample;
}

template <>
inline const GlTexImage3DMultisample&
GpuContextOgl::getFunction<GlTexImage3DMultisample>() const {
    return _glTexImage3DMultisample;
}

template <>
inline const GlGetMultisamplefv&
GpuContextOgl::getFunction<GlGetMultisamplefv>() const {
    return _glGetMultisamplefv;
}

template <>
inline const GlSampleMaski&
GpuContextOgl::getFunction<GlSampleMaski>() const {
    return _glSampleMaski;
}

template <>
inline const GlBindFragDataLocationIndexed&
GpuContextOgl::getFunction<GlBindFragDataLocationIndexed>() const {
    return _glBindFragDataLocationIndexed;
}

template <>
inline const GlGetFragDataIndex&
GpuContextOgl::getFunction<GlGetFragDataIndex>() const {
    return _glGetFragDataIndex;
}

template <>
inline const GlGenSamplers&
GpuContextOgl::getFunction<GlGenSamplers>() const {
    return _glGenSamplers;
}

template <>
inline const GlDeleteSamplers&
GpuContextOgl::getFunction<GlDeleteSamplers>() const {
    return _glDeleteSamplers;
}

template <>
inline const GlIsSampler&
GpuContextOgl::getFunction<GlIsSampler>() const {
    return _glIsSampler;
}

template <>
inline const GlBindSampler&
GpuContextOgl::getFunction<GlBindSampler>() const {
    return _glBindSampler;
}

template <>
inline const GlSamplerParameteri&
GpuContextOgl::getFunction<GlSamplerParameteri>() const {
    return _glSamplerParameteri;
}

template <>
inline const GlSamplerParameteriv&
GpuContextOgl::getFunction<GlSamplerParameteriv>() const {
    return _glSamplerParameteriv;
}

template <>
inline const GlSamplerParameterf&
GpuContextOgl::getFunction<GlSamplerParameterf>() const {
    return _glSamplerParameterf;
}

template <>
inline const GlSamplerParameterfv&
GpuContextOgl::getFunction<GlSamplerParameterfv>() const {
    return _glSamplerParameterfv;
}

template <>
inline const GlSamplerParameterIiv&
GpuContextOgl::getFunction<GlSamplerParameterIiv>() const {
    return _glSamplerParameterIiv;
}

template <>
inline const GlSamplerParameterIuiv&
GpuContextOgl::getFunction<GlSamplerParameterIuiv>() const {
    return _glSamplerParameterIuiv;
}

template <>
inline const GlGetSamplerParameteriv&
GpuContextOgl::getFunction<GlGetSamplerParameteriv>() const {
    return _glGetSamplerParameteriv;
}

template <>
inline const GlGetSamplerParameterIiv&
GpuContextOgl::getFunction<GlGetSamplerParameterIiv>() const {
    return _glGetSamplerParameterIiv;
}

template <>
inline const GlGetSamplerParameterfv&
GpuContextOgl::getFunction<GlGetSamplerParameterfv>() const {
    return _glGetSamplerParameterfv;
}

template <>
inline const GlGetSamplerParameterIuiv&
GpuContextOgl::getFunction<GlGetSamplerParameterIuiv>() const {
    return _glGetSamplerParameterIuiv;
}

template <>
inline const GlQueryCounter&
GpuContextOgl::getFunction<GlQueryCounter>() const {
    return _glQueryCounter;
}

template <>
inline const GlGetQueryObjecti64v&
GpuContextOgl::getFunction<GlGetQueryObjecti64v>() const {
    return _glGetQueryObjecti64v;
}

template <>
inline const GlGetQueryObjectui64v&
GpuContextOgl::getFunction<GlGetQueryObjectui64v>() const {
    return _glGetQueryObjectui64v;
}

template <>
inline const GlVertexAttribDivisor&
GpuContextOgl::getFunction<GlVertexAttribDivisor>() const {
    return _glVertexAttribDivisor;
}

template <>
inline const GlVertexAttribP1ui&
GpuContextOgl::getFunction<GlVertexAttribP1ui>() const {
    return _glVertexAttribP1ui;
}

template <>
inline const GlVertexAttribP1uiv&
GpuContextOgl::getFunction<GlVertexAttribP1uiv>() const {
    return _glVertexAttribP1uiv;
}

template <>
inline const GlVertexAttribP2ui&
GpuContextOgl::getFunction<GlVertexAttribP2ui>() const {
    return _glVertexAttribP2ui;
}

template <>
inline const GlVertexAttribP2uiv&
GpuContextOgl::getFunction<GlVertexAttribP2uiv>() const {
    return _glVertexAttribP2uiv;
}

template <>
inline const GlVertexAttribP3ui&
GpuContextOgl::getFunction<GlVertexAttribP3ui>() const {
    return _glVertexAttribP3ui;
}

template <>
inline const GlVertexAttribP3uiv&
GpuContextOgl::getFunction<GlVertexAttribP3uiv>() const {
    return _glVertexAttribP3uiv;
}

template <>
inline const GlVertexAttribP4ui&
GpuContextOgl::getFunction<GlVertexAttribP4ui>() const {
    return _glVertexAttribP4ui;
}

template <>
inline const GlVertexAttribP4uiv&
GpuContextOgl::getFunction<GlVertexAttribP4uiv>() const {
    return _glVertexAttribP4uiv;
}

template <>
inline const GlMinSampleShading&
GpuContextOgl::getFunction<GlMinSampleShading>() const {
    return _glMinSampleShading;
}

template <>
inline const GlBlendEquationi&
GpuContextOgl::getFunction<GlBlendEquationi>() const {
    return _glBlendEquationi;
}

template <>
inline const GlBlendEquationSeparatei&
GpuContextOgl::getFunction<GlBlendEquationSeparatei>() const {
    return _glBlendEquationSeparatei;
}

template <>
inline const GlBlendFunci&
GpuContextOgl::getFunction<GlBlendFunci>() const {
    return _glBlendFunci;
}

template <>
inline const GlBlendFuncSeparatei&
GpuContextOgl::getFunction<GlBlendFuncSeparatei>() const {
    return _glBlendFuncSeparatei;
}

template <>
inline const GlDrawArraysIndirect&
GpuContextOgl::getFunction<GlDrawArraysIndirect>() const {
    return _glDrawArraysIndirect;
}

template <>
inline const GlDrawElementsIndirect&
GpuContextOgl::getFunction<GlDrawElementsIndirect>() const {
    return _glDrawElementsIndirect;
}

template <>
inline const GlUniform1d&
GpuContextOgl::getFunction<GlUniform1d>() const {
    return _glUniform1d;
}

template <>
inline const GlUniform2d&
GpuContextOgl::getFunction<GlUniform2d>() const {
    return _glUniform2d;
}

template <>
inline const GlUniform3d&
GpuContextOgl::getFunction<GlUniform3d>() const {
    return _glUniform3d;
}

template <>
inline const GlUniform4d&
GpuContextOgl::getFunction<GlUniform4d>() const {
    return _glUniform4d;
}

template <>
inline const GlUniform1dv&
GpuContextOgl::getFunction<GlUniform1dv>() const {
    return _glUniform1dv;
}

template <>
inline const GlUniform2dv&
GpuContextOgl::getFunction<GlUniform2dv>() const {
    return _glUniform2dv;
}

template <>
inline const GlUniform3dv&
GpuContextOgl::getFunction<GlUniform3dv>() const {
    return _glUniform3dv;
}

template <>
inline const GlUniform4dv&
GpuContextOgl::getFunction<GlUniform4dv>() const {
    return _glUniform4dv;
}

template <>
inline const GlUniformMatrix2dv&
GpuContextOgl::getFunction<GlUniformMatrix2dv>() const {
    return _glUniformMatrix2dv;
}

template <>
inline const GlUniformMatrix3dv&
GpuContextOgl::getFunction<GlUniformMatrix3dv>() const {
    return _glUniformMatrix3dv;
}

template <>
inline const GlUniformMatrix4dv&
GpuContextOgl::getFunction<GlUniformMatrix4dv>() const {
    return _glUniformMatrix4dv;
}

template <>
inline const GlUniformMatrix2x3dv&
GpuContextOgl::getFunction<GlUniformMatrix2x3dv>() const {
    return _glUniformMatrix2x3dv;
}

template <>
inline const GlUniformMatrix2x4dv&
GpuContextOgl::getFunction<GlUniformMatrix2x4dv>() const {
    return _glUniformMatrix2x4dv;
}

template <>
inline const GlUniformMatrix3x2dv&
GpuContextOgl::getFunction<GlUniformMatrix3x2dv>() const {
    return _glUniformMatrix3x2dv;
}

template <>
inline const GlUniformMatrix3x4dv&
GpuContextOgl::getFunction<GlUniformMatrix3x4dv>() const {
    return _glUniformMatrix3x4dv;
}

template <>
inline const GlUniformMatrix4x2dv&
GpuContextOgl::getFunction<GlUniformMatrix4x2dv>() const {
    return _glUniformMatrix4x2dv;
}

template <>
inline const GlUniformMatrix4x3dv&
GpuContextOgl::getFunction<GlUniformMatrix4x3dv>() const {
    return _glUniformMatrix4x3dv;
}

template <>
inline const GlGetUniformdv&
GpuContextOgl::getFunction<GlGetUniformdv>() const {
    return _glGetUniformdv;
}

template <>
inline const GlGetSubroutineUniformLocation&
GpuContextOgl::getFunction<GlGetSubroutineUniformLocation>() const {
    return _glGetSubroutineUniformLocation;
}

template <>
inline const GlGetSubroutineIndex&
GpuContextOgl::getFunction<GlGetSubroutineIndex>() const {
    return _glGetSubroutineIndex;
}

template <>
inline const GlGetActiveSubroutineUniformiv&
GpuContextOgl::getFunction<GlGetActiveSubroutineUniformiv>() const {
    return _glGetActiveSubroutineUniformiv;
}

template <>
inline const GlGetActiveSubroutineUniformName&
GpuContextOgl::getFunction<GlGetActiveSubroutineUniformName>() const {
    return _glGetActiveSubroutineUniformName;
}

template <>
inline const GlGetActiveSubroutineName&
GpuContextOgl::getFunction<GlGetActiveSubroutineName>() const {
    return _glGetActiveSubroutineName;
}

template <>
inline const GlUniformSubroutinesuiv&
GpuContextOgl::getFunction<GlUniformSubroutinesuiv>() const {
    return _glUniformSubroutinesuiv;
}

template <>
inline const GlGetUniformSubroutineuiv&
GpuContextOgl::getFunction<GlGetUniformSubroutineuiv>() const {
    return _glGetUniformSubroutineuiv;
}

template <>
inline const GlGetProgramStageiv&
GpuContextOgl::getFunction<GlGetProgramStageiv>() const {
    return _glGetProgramStageiv;
}

template <>
inline const GlPatchParameteri&
GpuContextOgl::getFunction<GlPatchParameteri>() const {
    return _glPatchParameteri;
}

template <>
inline const GlPatchParameterfv&
GpuContextOgl::getFunction<GlPatchParameterfv>() const {
    return _glPatchParameterfv;
}

template <>
inline const GlBindTransformFeedback&
GpuContextOgl::getFunction<GlBindTransformFeedback>() const {
    return _glBindTransformFeedback;
}

template <>
inline const GlDeleteTransformFeedbacks&
GpuContextOgl::getFunction<GlDeleteTransformFeedbacks>() const {
    return _glDeleteTransformFeedbacks;
}

template <>
inline const GlGenTransformFeedbacks&
GpuContextOgl::getFunction<GlGenTransformFeedbacks>() const {
    return _glGenTransformFeedbacks;
}

template <>
inline const GlIsTransformFeedback&
GpuContextOgl::getFunction<GlIsTransformFeedback>() const {
    return _glIsTransformFeedback;
}

template <>
inline const GlPauseTransformFeedback&
GpuContextOgl::getFunction<GlPauseTransformFeedback>() const {
    return _glPauseTransformFeedback;
}

template <>
inline const GlResumeTransformFeedback&
GpuContextOgl::getFunction<GlResumeTransformFeedback>() const {
    return _glResumeTransformFeedback;
}

template <>
inline const GlDrawTransformFeedback&
GpuContextOgl::getFunction<GlDrawTransformFeedback>() const {
    return _glDrawTransformFeedback;
}

template <>
inline const GlDrawTransformFeedbackStream&
GpuContextOgl::getFunction<GlDrawTransformFeedbackStream>() const {
    return _glDrawTransformFeedbackStream;
}

template <>
inline const GlBeginQueryIndexed&
GpuContextOgl::getFunction<GlBeginQueryIndexed>() const {
    return _glBeginQueryIndexed;
}

template <>
inline const GlEndQueryIndexed&
GpuContextOgl::getFunction<GlEndQueryIndexed>() const {
    return _glEndQueryIndexed;
}

template <>
inline const GlGetQueryIndexediv&
GpuContextOgl::getFunction<GlGetQueryIndexediv>() const {
    return _glGetQueryIndexediv;
}

template <>
inline const GlReleaseShaderCompiler&
GpuContextOgl::getFunction<GlReleaseShaderCompiler>() const {
    return _glReleaseShaderCompiler;
}

template <>
inline const GlShaderBinary&
GpuContextOgl::getFunction<GlShaderBinary>() const {
    return _glShaderBinary;
}

template <>
inline const GlGetShaderPrecisionFormat&
GpuContextOgl::getFunction<GlGetShaderPrecisionFormat>() const {
    return _glGetShaderPrecisionFormat;
}

template <>
inline const GlDepthRangef&
GpuContextOgl::getFunction<GlDepthRangef>() const {
    return _glDepthRangef;
}

template <>
inline const GlClearDepthf&
GpuContextOgl::getFunction<GlClearDepthf>() const {
    return _glClearDepthf;
}

template <>
inline const GlGetProgramBinary&
GpuContextOgl::getFunction<GlGetProgramBinary>() const {
    return _glGetProgramBinary;
}

template <>
inline const GlProgramBinary&
GpuContextOgl::getFunction<GlProgramBinary>() const {
    return _glProgramBinary;
}

template <>
inline const GlProgramParameteri&
GpuContextOgl::getFunction<GlProgramParameteri>() const {
    return _glProgramParameteri;
}

template <>
inline const GlUseProgramStages&
GpuContextOgl::getFunction<GlUseProgramStages>() const {
    return _glUseProgramStages;
}

template <>
inline const GlActiveShaderProgram&
GpuContextOgl::getFunction<GlActiveShaderProgram>() const {
    return _glActiveShaderProgram;
}

template <>
inline const GlCreateShaderProgramv&
GpuContextOgl::getFunction<GlCreateShaderProgramv>() const {
    return _glCreateShaderProgramv;
}

template <>
inline const GlBindProgramPipeline&
GpuContextOgl::getFunction<GlBindProgramPipeline>() const {
    return _glBindProgramPipeline;
}

template <>
inline const GlDeleteProgramPipelines&
GpuContextOgl::getFunction<GlDeleteProgramPipelines>() const {
    return _glDeleteProgramPipelines;
}

template <>
inline const GlGenProgramPipelines&
GpuContextOgl::getFunction<GlGenProgramPipelines>() const {
    return _glGenProgramPipelines;
}

template <>
inline const GlIsProgramPipeline&
GpuContextOgl::getFunction<GlIsProgramPipeline>() const {
    return _glIsProgramPipeline;
}

template <>
inline const GlGetProgramPipelineiv&
GpuContextOgl::getFunction<GlGetProgramPipelineiv>() const {
    return _glGetProgramPipelineiv;
}

template <>
inline const GlProgramUniform1i&
GpuContextOgl::getFunction<GlProgramUniform1i>() const {
    return _glProgramUniform1i;
}

template <>
inline const GlProgramUniform1iv&
GpuContextOgl::getFunction<GlProgramUniform1iv>() const {
    return _glProgramUniform1iv;
}

template <>
inline const GlProgramUniform1f&
GpuContextOgl::getFunction<GlProgramUniform1f>() const {
    return _glProgramUniform1f;
}

template <>
inline const GlProgramUniform1fv&
GpuContextOgl::getFunction<GlProgramUniform1fv>() const {
    return _glProgramUniform1fv;
}

template <>
inline const GlProgramUniform1d&
GpuContextOgl::getFunction<GlProgramUniform1d>() const {
    return _glProgramUniform1d;
}

template <>
inline const GlProgramUniform1dv&
GpuContextOgl::getFunction<GlProgramUniform1dv>() const {
    return _glProgramUniform1dv;
}

template <>
inline const GlProgramUniform1ui&
GpuContextOgl::getFunction<GlProgramUniform1ui>() const {
    return _glProgramUniform1ui;
}

template <>
inline const GlProgramUniform1uiv&
GpuContextOgl::getFunction<GlProgramUniform1uiv>() const {
    return _glProgramUniform1uiv;
}

template <>
inline const GlProgramUniform2i&
GpuContextOgl::getFunction<GlProgramUniform2i>() const {
    return _glProgramUniform2i;
}

template <>
inline const GlProgramUniform2iv&
GpuContextOgl::getFunction<GlProgramUniform2iv>() const {
    return _glProgramUniform2iv;
}

template <>
inline const GlProgramUniform2f&
GpuContextOgl::getFunction<GlProgramUniform2f>() const {
    return _glProgramUniform2f;
}

template <>
inline const GlProgramUniform2fv&
GpuContextOgl::getFunction<GlProgramUniform2fv>() const {
    return _glProgramUniform2fv;
}

template <>
inline const GlProgramUniform2d&
GpuContextOgl::getFunction<GlProgramUniform2d>() const {
    return _glProgramUniform2d;
}

template <>
inline const GlProgramUniform2dv&
GpuContextOgl::getFunction<GlProgramUniform2dv>() const {
    return _glProgramUniform2dv;
}

template <>
inline const GlProgramUniform2ui&
GpuContextOgl::getFunction<GlProgramUniform2ui>() const {
    return _glProgramUniform2ui;
}

template <>
inline const GlProgramUniform2uiv&
GpuContextOgl::getFunction<GlProgramUniform2uiv>() const {
    return _glProgramUniform2uiv;
}

template <>
inline const GlProgramUniform3i&
GpuContextOgl::getFunction<GlProgramUniform3i>() const {
    return _glProgramUniform3i;
}

template <>
inline const GlProgramUniform3iv&
GpuContextOgl::getFunction<GlProgramUniform3iv>() const {
    return _glProgramUniform3iv;
}

template <>
inline const GlProgramUniform3f&
GpuContextOgl::getFunction<GlProgramUniform3f>() const {
    return _glProgramUniform3f;
}

template <>
inline const GlProgramUniform3fv&
GpuContextOgl::getFunction<GlProgramUniform3fv>() const {
    return _glProgramUniform3fv;
}

template <>
inline const GlProgramUniform3d&
GpuContextOgl::getFunction<GlProgramUniform3d>() const {
    return _glProgramUniform3d;
}

template <>
inline const GlProgramUniform3dv&
GpuContextOgl::getFunction<GlProgramUniform3dv>() const {
    return _glProgramUniform3dv;
}

template <>
inline const GlProgramUniform3ui&
GpuContextOgl::getFunction<GlProgramUniform3ui>() const {
    return _glProgramUniform3ui;
}

template <>
inline const GlProgramUniform3uiv&
GpuContextOgl::getFunction<GlProgramUniform3uiv>() const {
    return _glProgramUniform3uiv;
}

template <>
inline const GlProgramUniform4i&
GpuContextOgl::getFunction<GlProgramUniform4i>() const {
    return _glProgramUniform4i;
}

template <>
inline const GlProgramUniform4iv&
GpuContextOgl::getFunction<GlProgramUniform4iv>() const {
    return _glProgramUniform4iv;
}

template <>
inline const GlProgramUniform4f&
GpuContextOgl::getFunction<GlProgramUniform4f>() const {
    return _glProgramUniform4f;
}

template <>
inline const GlProgramUniform4fv&
GpuContextOgl::getFunction<GlProgramUniform4fv>() const {
    return _glProgramUniform4fv;
}

template <>
inline const GlProgramUniform4d&
GpuContextOgl::getFunction<GlProgramUniform4d>() const {
    return _glProgramUniform4d;
}

template <>
inline const GlProgramUniform4dv&
GpuContextOgl::getFunction<GlProgramUniform4dv>() const {
    return _glProgramUniform4dv;
}

template <>
inline const GlProgramUniform4ui&
GpuContextOgl::getFunction<GlProgramUniform4ui>() const {
    return _glProgramUniform4ui;
}

template <>
inline const GlProgramUniform4uiv&
GpuContextOgl::getFunction<GlProgramUniform4uiv>() const {
    return _glProgramUniform4uiv;
}

template <>
inline const GlProgramUniformMatrix2fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2fv>() const {
    return _glProgramUniformMatrix2fv;
}

template <>
inline const GlProgramUniformMatrix3fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3fv>() const {
    return _glProgramUniformMatrix3fv;
}

template <>
inline const GlProgramUniformMatrix4fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4fv>() const {
    return _glProgramUniformMatrix4fv;
}

template <>
inline const GlProgramUniformMatrix2dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2dv>() const {
    return _glProgramUniformMatrix2dv;
}

template <>
inline const GlProgramUniformMatrix3dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3dv>() const {
    return _glProgramUniformMatrix3dv;
}

template <>
inline const GlProgramUniformMatrix4dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4dv>() const {
    return _glProgramUniformMatrix4dv;
}

template <>
inline const GlProgramUniformMatrix2x3fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x3fv>() const {
    return _glProgramUniformMatrix2x3fv;
}

template <>
inline const GlProgramUniformMatrix3x2fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x2fv>() const {
    return _glProgramUniformMatrix3x2fv;
}

template <>
inline const GlProgramUniformMatrix2x4fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x4fv>() const {
    return _glProgramUniformMatrix2x4fv;
}

template <>
inline const GlProgramUniformMatrix4x2fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x2fv>() const {
    return _glProgramUniformMatrix4x2fv;
}

template <>
inline const GlProgramUniformMatrix3x4fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x4fv>() const {
    return _glProgramUniformMatrix3x4fv;
}

template <>
inline const GlProgramUniformMatrix4x3fv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x3fv>() const {
    return _glProgramUniformMatrix4x3fv;
}

template <>
inline const GlProgramUniformMatrix2x3dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x3dv>() const {
    return _glProgramUniformMatrix2x3dv;
}

template <>
inline const GlProgramUniformMatrix3x2dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x2dv>() const {
    return _glProgramUniformMatrix3x2dv;
}

template <>
inline const GlProgramUniformMatrix2x4dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x4dv>() const {
    return _glProgramUniformMatrix2x4dv;
}

template <>
inline const GlProgramUniformMatrix4x2dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x2dv>() const {
    return _glProgramUniformMatrix4x2dv;
}

template <>
inline const GlProgramUniformMatrix3x4dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x4dv>() const {
    return _glProgramUniformMatrix3x4dv;
}

template <>
inline const GlProgramUniformMatrix4x3dv&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x3dv>() const {
    return _glProgramUniformMatrix4x3dv;
}

template <>
inline const GlValidateProgramPipeline&
GpuContextOgl::getFunction<GlValidateProgramPipeline>() const {
    return _glValidateProgramPipeline;
}

template <>
inline const GlGetProgramPipelineInfoLog&
GpuContextOgl::getFunction<GlGetProgramPipelineInfoLog>() const {
    return _glGetProgramPipelineInfoLog;
}

template <>
inline const GlVertexAttribL1d&
GpuContextOgl::getFunction<GlVertexAttribL1d>() const {
    return _glVertexAttribL1d;
}

template <>
inline const GlVertexAttribL2d&
GpuContextOgl::getFunction<GlVertexAttribL2d>() const {
    return _glVertexAttribL2d;
}

template <>
inline const GlVertexAttribL3d&
GpuContextOgl::getFunction<GlVertexAttribL3d>() const {
    return _glVertexAttribL3d;
}

template <>
inline const GlVertexAttribL4d&
GpuContextOgl::getFunction<GlVertexAttribL4d>() const {
    return _glVertexAttribL4d;
}

template <>
inline const GlVertexAttribL1dv&
GpuContextOgl::getFunction<GlVertexAttribL1dv>() const {
    return _glVertexAttribL1dv;
}

template <>
inline const GlVertexAttribL2dv&
GpuContextOgl::getFunction<GlVertexAttribL2dv>() const {
    return _glVertexAttribL2dv;
}

template <>
inline const GlVertexAttribL3dv&
GpuContextOgl::getFunction<GlVertexAttribL3dv>() const {
    return _glVertexAttribL3dv;
}

template <>
inline const GlVertexAttribL4dv&
GpuContextOgl::getFunction<GlVertexAttribL4dv>() const {
    return _glVertexAttribL4dv;
}

template <>
inline const GlVertexAttribLPointer&
GpuContextOgl::getFunction<GlVertexAttribLPointer>() const {
    return _glVertexAttribLPointer;
}

template <>
inline const GlGetVertexAttribLdv&
GpuContextOgl::getFunction<GlGetVertexAttribLdv>() const {
    return _glGetVertexAttribLdv;
}

template <>
inline const GlViewportArrayv&
GpuContextOgl::getFunction<GlViewportArrayv>() const {
    return _glViewportArrayv;
}

template <>
inline const GlViewportIndexedf&
GpuContextOgl::getFunction<GlViewportIndexedf>() const {
    return _glViewportIndexedf;
}

template <>
inline const GlViewportIndexedfv&
GpuContextOgl::getFunction<GlViewportIndexedfv>() const {
    return _glViewportIndexedfv;
}

template <>
inline const GlScissorArrayv&
GpuContextOgl::getFunction<GlScissorArrayv>() const {
    return _glScissorArrayv;
}

template <>
inline const GlScissorIndexed&
GpuContextOgl::getFunction<GlScissorIndexed>() const {
    return _glScissorIndexed;
}

template <>
inline const GlScissorIndexedv&
GpuContextOgl::getFunction<GlScissorIndexedv>() const {
    return _glScissorIndexedv;
}

template <>
inline const GlDepthRangeArrayv&
GpuContextOgl::getFunction<GlDepthRangeArrayv>() const {
    return _glDepthRangeArrayv;
}

template <>
inline const GlDepthRangeIndexed&
GpuContextOgl::getFunction<GlDepthRangeIndexed>() const {
    return _glDepthRangeIndexed;
}

template <>
inline const GlGetFloati_v&
GpuContextOgl::getFunction<GlGetFloati_v>() const {
    return _glGetFloati_v;
}

template <>
inline const GlGetDoublei_v&
GpuContextOgl::getFunction<GlGetDoublei_v>() const {
    return _glGetDoublei_v;
}

template <>
inline const GlDrawArraysInstancedBaseInstance&
GpuContextOgl::getFunction<GlDrawArraysInstancedBaseInstance>() const {
    return _glDrawArraysInstancedBaseInstance;
}

template <>
inline const GlDrawElementsInstancedBaseInstance&
GpuContextOgl::getFunction<GlDrawElementsInstancedBaseInstance>() const {
    return _glDrawElementsInstancedBaseInstance;
}

template <>
inline const GlDrawElementsInstancedBaseVertexBaseInstance&
GpuContextOgl::getFunction<GlDrawElementsInstancedBaseVertexBaseInstance>() const {
    return _glDrawElementsInstancedBaseVertexBaseInstance;
}

template <>
inline const GlGetInternalformativ&
GpuContextOgl::getFunction<GlGetInternalformativ>() const {
    return _glGetInternalformativ;
}

template <>
inline const GlGetActiveAtomicCounterBufferiv&
GpuContextOgl::getFunction<GlGetActiveAtomicCounterBufferiv>() const {
    return _glGetActiveAtomicCounterBufferiv;
}

template <>
inline const GlBindImageTexture&
GpuContextOgl::getFunction<GlBindImageTexture>() const {
    return _glBindImageTexture;
}

template <>
inline const GlMemoryBarrier&
GpuContextOgl::getFunction<GlMemoryBarrier>() const {
    return _glMemoryBarrier;
}

template <>
inline const GlTexStorage1D&
GpuContextOgl::getFunction<GlTexStorage1D>() const {
    return _glTexStorage1D;
}

template <>
inline const GlTexStorage2D&
GpuContextOgl::getFunction<GlTexStorage2D>() const {
    return _glTexStorage2D;
}

template <>
inline const GlTexStorage3D&
GpuContextOgl::getFunction<GlTexStorage3D>() const {
    return _glTexStorage3D;
}

template <>
inline const GlDrawTransformFeedbackInstanced&
GpuContextOgl::getFunction<GlDrawTransformFeedbackInstanced>() const {
    return _glDrawTransformFeedbackInstanced;
}

template <>
inline const GlDrawTransformFeedbackStreamInstanced&
GpuContextOgl::getFunction<GlDrawTransformFeedbackStreamInstanced>() const {
    return _glDrawTransformFeedbackStreamInstanced;
}

template <>
inline const GlClearBufferData&
GpuContextOgl::getFunction<GlClearBufferData>() const {
    return _glClearBufferData;
}

template <>
inline const GlClearBufferSubData&
GpuContextOgl::getFunction<GlClearBufferSubData>() const {
    return _glClearBufferSubData;
}

template <>
inline const GlDispatchCompute&
GpuContextOgl::getFunction<GlDispatchCompute>() const {
    return _glDispatchCompute;
}

template <>
inline const GlDispatchComputeIndirect&
GpuContextOgl::getFunction<GlDispatchComputeIndirect>() const {
    return _glDispatchComputeIndirect;
}

template <>
inline const GlCopyImageSubData&
GpuContextOgl::getFunction<GlCopyImageSubData>() const {
    return _glCopyImageSubData;
}

template <>
inline const GlFramebufferParameteri&
GpuContextOgl::getFunction<GlFramebufferParameteri>() const {
    return _glFramebufferParameteri;
}

template <>
inline const GlGetFramebufferParameteriv&
GpuContextOgl::getFunction<GlGetFramebufferParameteriv>() const {
    return _glGetFramebufferParameteriv;
}

template <>
inline const GlGetInternalformati64v&
GpuContextOgl::getFunction<GlGetInternalformati64v>() const {
    return _glGetInternalformati64v;
}

template <>
inline const GlInvalidateTexSubImage&
GpuContextOgl::getFunction<GlInvalidateTexSubImage>() const {
    return _glInvalidateTexSubImage;
}

template <>
inline const GlInvalidateTexImage&
GpuContextOgl::getFunction<GlInvalidateTexImage>() const {
    return _glInvalidateTexImage;
}

template <>
inline const GlInvalidateBufferSubData&
GpuContextOgl::getFunction<GlInvalidateBufferSubData>() const {
    return _glInvalidateBufferSubData;
}

template <>
inline const GlInvalidateBufferData&
GpuContextOgl::getFunction<GlInvalidateBufferData>() const {
    return _glInvalidateBufferData;
}

template <>
inline const GlInvalidateFramebuffer&
GpuContextOgl::getFunction<GlInvalidateFramebuffer>() const {
    return _glInvalidateFramebuffer;
}

template <>
inline const GlInvalidateSubFramebuffer&
GpuContextOgl::getFunction<GlInvalidateSubFramebuffer>() const {
    return _glInvalidateSubFramebuffer;
}

template <>
inline const GlMultiDrawArraysIndirect&
GpuContextOgl::getFunction<GlMultiDrawArraysIndirect>() const {
    return _glMultiDrawArraysIndirect;
}

template <>
inline const GlMultiDrawElementsIndirect&
GpuContextOgl::getFunction<GlMultiDrawElementsIndirect>() const {
    return _glMultiDrawElementsIndirect;
}

template <>
inline const GlGetProgramInterfaceiv&
GpuContextOgl::getFunction<GlGetProgramInterfaceiv>() const {
    return _glGetProgramInterfaceiv;
}

template <>
inline const GlGetProgramResourceIndex&
GpuContextOgl::getFunction<GlGetProgramResourceIndex>() const {
    return _glGetProgramResourceIndex;
}

template <>
inline const GlGetProgramResourceName&
GpuContextOgl::getFunction<GlGetProgramResourceName>() const {
    return _glGetProgramResourceName;
}

template <>
inline const GlGetProgramResourceiv&
GpuContextOgl::getFunction<GlGetProgramResourceiv>() const {
    return _glGetProgramResourceiv;
}

template <>
inline const GlGetProgramResourceLocation&
GpuContextOgl::getFunction<GlGetProgramResourceLocation>() const {
    return _glGetProgramResourceLocation;
}

template <>
inline const GlGetProgramResourceLocationIndex&
GpuContextOgl::getFunction<GlGetProgramResourceLocationIndex>() const {
    return _glGetProgramResourceLocationIndex;
}

template <>
inline const GlShaderStorageBlockBinding&
GpuContextOgl::getFunction<GlShaderStorageBlockBinding>() const {
    return _glShaderStorageBlockBinding;
}

template <>
inline const GlTexBufferRange&
GpuContextOgl::getFunction<GlTexBufferRange>() const {
    return _glTexBufferRange;
}

template <>
inline const GlTexStorage2DMultisample&
GpuContextOgl::getFunction<GlTexStorage2DMultisample>() const {
    return _glTexStorage2DMultisample;
}

template <>
inline const GlTexStorage3DMultisample&
GpuContextOgl::getFunction<GlTexStorage3DMultisample>() const {
    return _glTexStorage3DMultisample;
}

template <>
inline const GlTextureView&
GpuContextOgl::getFunction<GlTextureView>() const {
    return _glTextureView;
}

template <>
inline const GlBindVertexBuffer&
GpuContextOgl::getFunction<GlBindVertexBuffer>() const {
    return _glBindVertexBuffer;
}

template <>
inline const GlVertexAttribFormat&
GpuContextOgl::getFunction<GlVertexAttribFormat>() const {
    return _glVertexAttribFormat;
}

template <>
inline const GlVertexAttribIFormat&
GpuContextOgl::getFunction<GlVertexAttribIFormat>() const {
    return _glVertexAttribIFormat;
}

template <>
inline const GlVertexAttribLFormat&
GpuContextOgl::getFunction<GlVertexAttribLFormat>() const {
    return _glVertexAttribLFormat;
}

template <>
inline const GlVertexAttribBinding&
GpuContextOgl::getFunction<GlVertexAttribBinding>() const {
    return _glVertexAttribBinding;
}

template <>
inline const GlVertexBindingDivisor&
GpuContextOgl::getFunction<GlVertexBindingDivisor>() const {
    return _glVertexBindingDivisor;
}

template <>
inline const GlDebugMessageControl&
GpuContextOgl::getFunction<GlDebugMessageControl>() const {
    return _glDebugMessageControl;
}

template <>
inline const GlDebugMessageInsert&
GpuContextOgl::getFunction<GlDebugMessageInsert>() const {
    return _glDebugMessageInsert;
}

template <>
inline const GlDebugMessageCallback&
GpuContextOgl::getFunction<GlDebugMessageCallback>() const {
    return _glDebugMessageCallback;
}

template <>
inline const GlGetDebugMessageLog&
GpuContextOgl::getFunction<GlGetDebugMessageLog>() const {
    return _glGetDebugMessageLog;
}

template <>
inline const GlPushDebugGroup&
GpuContextOgl::getFunction<GlPushDebugGroup>() const {
    return _glPushDebugGroup;
}

template <>
inline const GlPopDebugGroup&
GpuContextOgl::getFunction<GlPopDebugGroup>() const {
    return _glPopDebugGroup;
}

template <>
inline const GlObjectLabel&
GpuContextOgl::getFunction<GlObjectLabel>() const {
    return _glObjectLabel;
}

template <>
inline const GlGetObjectLabel&
GpuContextOgl::getFunction<GlGetObjectLabel>() const {
    return _glGetObjectLabel;
}

template <>
inline const GlObjectPtrLabel&
GpuContextOgl::getFunction<GlObjectPtrLabel>() const {
    return _glObjectPtrLabel;
}

template <>
inline const GlGetObjectPtrLabel&
GpuContextOgl::getFunction<GlGetObjectPtrLabel>() const {
    return _glGetObjectPtrLabel;
}

template <>
inline const GlBufferStorage&
GpuContextOgl::getFunction<GlBufferStorage>() const {
    return _glBufferStorage;
}

template <>
inline const GlClearTexImage&
GpuContextOgl::getFunction<GlClearTexImage>() const {
    return _glClearTexImage;
}

template <>
inline const GlClearTexSubImage&
GpuContextOgl::getFunction<GlClearTexSubImage>() const {
    return _glClearTexSubImage;
}

template <>
inline const GlBindBuffersBase&
GpuContextOgl::getFunction<GlBindBuffersBase>() const {
    return _glBindBuffersBase;
}

template <>
inline const GlBindBuffersRange&
GpuContextOgl::getFunction<GlBindBuffersRange>() const {
    return _glBindBuffersRange;
}

template <>
inline const GlBindTextures&
GpuContextOgl::getFunction<GlBindTextures>() const {
    return _glBindTextures;
}

template <>
inline const GlBindSamplers&
GpuContextOgl::getFunction<GlBindSamplers>() const {
    return _glBindSamplers;
}

template <>
inline const GlBindImageTextures&
GpuContextOgl::getFunction<GlBindImageTextures>() const {
    return _glBindImageTextures;
}

template <>
inline const GlBindVertexBuffers&
GpuContextOgl::getFunction<GlBindVertexBuffers>() const {
    return _glBindVertexBuffers;
}

template <>
inline const GlClipControl&
GpuContextOgl::getFunction<GlClipControl>() const {
    return _glClipControl;
}

template <>
inline const GlCreateTransformFeedbacks&
GpuContextOgl::getFunction<GlCreateTransformFeedbacks>() const {
    return _glCreateTransformFeedbacks;
}

template <>
inline const GlTransformFeedbackBufferBase&
GpuContextOgl::getFunction<GlTransformFeedbackBufferBase>() const {
    return _glTransformFeedbackBufferBase;
}

template <>
inline const GlTransformFeedbackBufferRange&
GpuContextOgl::getFunction<GlTransformFeedbackBufferRange>() const {
    return _glTransformFeedbackBufferRange;
}

template <>
inline const GlGetTransformFeedbackiv&
GpuContextOgl::getFunction<GlGetTransformFeedbackiv>() const {
    return _glGetTransformFeedbackiv;
}

template <>
inline const GlGetTransformFeedbacki_v&
GpuContextOgl::getFunction<GlGetTransformFeedbacki_v>() const {
    return _glGetTransformFeedbacki_v;
}

template <>
inline const GlGetTransformFeedbacki64_v&
GpuContextOgl::getFunction<GlGetTransformFeedbacki64_v>() const {
    return _glGetTransformFeedbacki64_v;
}

template <>
inline const GlCreateBuffers&
GpuContextOgl::getFunction<GlCreateBuffers>() const {
    return _glCreateBuffers;
}

template <>
inline const GlNamedBufferStorage&
GpuContextOgl::getFunction<GlNamedBufferStorage>() const {
    return _glNamedBufferStorage;
}

template <>
inline const GlNamedBufferData&
GpuContextOgl::getFunction<GlNamedBufferData>() const {
    return _glNamedBufferData;
}

template <>
inline const GlNamedBufferSubData&
GpuContextOgl::getFunction<GlNamedBufferSubData>() const {
    return _glNamedBufferSubData;
}

template <>
inline const GlCopyNamedBufferSubData&
GpuContextOgl::getFunction<GlCopyNamedBufferSubData>() const {
    return _glCopyNamedBufferSubData;
}

template <>
inline const GlClearNamedBufferData&
GpuContextOgl::getFunction<GlClearNamedBufferData>() const {
    return _glClearNamedBufferData;
}

template <>
inline const GlClearNamedBufferSubData&
GpuContextOgl::getFunction<GlClearNamedBufferSubData>() const {
    return _glClearNamedBufferSubData;
}

template <>
inline const GlMapNamedBuffer&
GpuContextOgl::getFunction<GlMapNamedBuffer>() const {
    return _glMapNamedBuffer;
}

template <>
inline const GlMapNamedBufferRange&
GpuContextOgl::getFunction<GlMapNamedBufferRange>() const {
    return _glMapNamedBufferRange;
}

template <>
inline const GlUnmapNamedBuffer&
GpuContextOgl::getFunction<GlUnmapNamedBuffer>() const {
    return _glUnmapNamedBuffer;
}

template <>
inline const GlFlushMappedNamedBufferRange&
GpuContextOgl::getFunction<GlFlushMappedNamedBufferRange>() const {
    return _glFlushMappedNamedBufferRange;
}

template <>
inline const GlGetNamedBufferParameteriv&
GpuContextOgl::getFunction<GlGetNamedBufferParameteriv>() const {
    return _glGetNamedBufferParameteriv;
}

template <>
inline const GlGetNamedBufferParameteri64v&
GpuContextOgl::getFunction<GlGetNamedBufferParameteri64v>() const {
    return _glGetNamedBufferParameteri64v;
}

template <>
inline const GlGetNamedBufferPointerv&
GpuContextOgl::getFunction<GlGetNamedBufferPointerv>() const {
    return _glGetNamedBufferPointerv;
}

template <>
inline const GlGetNamedBufferSubData&
GpuContextOgl::getFunction<GlGetNamedBufferSubData>() const {
    return _glGetNamedBufferSubData;
}

template <>
inline const GlCreateFramebuffers&
GpuContextOgl::getFunction<GlCreateFramebuffers>() const {
    return _glCreateFramebuffers;
}

template <>
inline const GlNamedFramebufferRenderbuffer&
GpuContextOgl::getFunction<GlNamedFramebufferRenderbuffer>() const {
    return _glNamedFramebufferRenderbuffer;
}

template <>
inline const GlNamedFramebufferParameteri&
GpuContextOgl::getFunction<GlNamedFramebufferParameteri>() const {
    return _glNamedFramebufferParameteri;
}

template <>
inline const GlNamedFramebufferTexture&
GpuContextOgl::getFunction<GlNamedFramebufferTexture>() const {
    return _glNamedFramebufferTexture;
}

template <>
inline const GlNamedFramebufferTextureLayer&
GpuContextOgl::getFunction<GlNamedFramebufferTextureLayer>() const {
    return _glNamedFramebufferTextureLayer;
}

template <>
inline const GlNamedFramebufferDrawBuffer&
GpuContextOgl::getFunction<GlNamedFramebufferDrawBuffer>() const {
    return _glNamedFramebufferDrawBuffer;
}

template <>
inline const GlNamedFramebufferDrawBuffers&
GpuContextOgl::getFunction<GlNamedFramebufferDrawBuffers>() const {
    return _glNamedFramebufferDrawBuffers;
}

template <>
inline const GlNamedFramebufferReadBuffer&
GpuContextOgl::getFunction<GlNamedFramebufferReadBuffer>() const {
    return _glNamedFramebufferReadBuffer;
}

template <>
inline const GlInvalidateNamedFramebufferData&
GpuContextOgl::getFunction<GlInvalidateNamedFramebufferData>() const {
    return _glInvalidateNamedFramebufferData;
}

template <>
inline const GlInvalidateNamedFramebufferSubData&
GpuContextOgl::getFunction<GlInvalidateNamedFramebufferSubData>() const {
    return _glInvalidateNamedFramebufferSubData;
}

template <>
inline const GlClearNamedFramebufferiv&
GpuContextOgl::getFunction<GlClearNamedFramebufferiv>() const {
    return _glClearNamedFramebufferiv;
}

template <>
inline const GlClearNamedFramebufferuiv&
GpuContextOgl::getFunction<GlClearNamedFramebufferuiv>() const {
    return _glClearNamedFramebufferuiv;
}

template <>
inline const GlClearNamedFramebufferfv&
GpuContextOgl::getFunction<GlClearNamedFramebufferfv>() const {
    return _glClearNamedFramebufferfv;
}

template <>
inline const GlClearNamedFramebufferfi&
GpuContextOgl::getFunction<GlClearNamedFramebufferfi>() const {
    return _glClearNamedFramebufferfi;
}

template <>
inline const GlBlitNamedFramebuffer&
GpuContextOgl::getFunction<GlBlitNamedFramebuffer>() const {
    return _glBlitNamedFramebuffer;
}

template <>
inline const GlCheckNamedFramebufferStatus&
GpuContextOgl::getFunction<GlCheckNamedFramebufferStatus>() const {
    return _glCheckNamedFramebufferStatus;
}

template <>
inline const GlGetNamedFramebufferParameteriv&
GpuContextOgl::getFunction<GlGetNamedFramebufferParameteriv>() const {
    return _glGetNamedFramebufferParameteriv;
}

template <>
inline const GlGetNamedFramebufferAttachmentParameteriv&
GpuContextOgl::getFunction<GlGetNamedFramebufferAttachmentParameteriv>() const {
    return _glGetNamedFramebufferAttachmentParameteriv;
}

template <>
inline const GlCreateRenderbuffers&
GpuContextOgl::getFunction<GlCreateRenderbuffers>() const {
    return _glCreateRenderbuffers;
}

template <>
inline const GlNamedRenderbufferStorage&
GpuContextOgl::getFunction<GlNamedRenderbufferStorage>() const {
    return _glNamedRenderbufferStorage;
}

template <>
inline const GlNamedRenderbufferStorageMultisample&
GpuContextOgl::getFunction<GlNamedRenderbufferStorageMultisample>() const {
    return _glNamedRenderbufferStorageMultisample;
}

template <>
inline const GlGetNamedRenderbufferParameteriv&
GpuContextOgl::getFunction<GlGetNamedRenderbufferParameteriv>() const {
    return _glGetNamedRenderbufferParameteriv;
}

template <>
inline const GlCreateTextures&
GpuContextOgl::getFunction<GlCreateTextures>() const {
    return _glCreateTextures;
}

template <>
inline const GlTextureBuffer&
GpuContextOgl::getFunction<GlTextureBuffer>() const {
    return _glTextureBuffer;
}

template <>
inline const GlTextureBufferRange&
GpuContextOgl::getFunction<GlTextureBufferRange>() const {
    return _glTextureBufferRange;
}

template <>
inline const GlTextureStorage1D&
GpuContextOgl::getFunction<GlTextureStorage1D>() const {
    return _glTextureStorage1D;
}

template <>
inline const GlTextureStorage2D&
GpuContextOgl::getFunction<GlTextureStorage2D>() const {
    return _glTextureStorage2D;
}

template <>
inline const GlTextureStorage3D&
GpuContextOgl::getFunction<GlTextureStorage3D>() const {
    return _glTextureStorage3D;
}

template <>
inline const GlTextureStorage2DMultisample&
GpuContextOgl::getFunction<GlTextureStorage2DMultisample>() const {
    return _glTextureStorage2DMultisample;
}

template <>
inline const GlTextureStorage3DMultisample&
GpuContextOgl::getFunction<GlTextureStorage3DMultisample>() const {
    return _glTextureStorage3DMultisample;
}

template <>
inline const GlTextureSubImage1D&
GpuContextOgl::getFunction<GlTextureSubImage1D>() const {
    return _glTextureSubImage1D;
}

template <>
inline const GlTextureSubImage2D&
GpuContextOgl::getFunction<GlTextureSubImage2D>() const {
    return _glTextureSubImage2D;
}

template <>
inline const GlTextureSubImage3D&
GpuContextOgl::getFunction<GlTextureSubImage3D>() const {
    return _glTextureSubImage3D;
}

template <>
inline const GlCompressedTextureSubImage1D&
GpuContextOgl::getFunction<GlCompressedTextureSubImage1D>() const {
    return _glCompressedTextureSubImage1D;
}

template <>
inline const GlCompressedTextureSubImage2D&
GpuContextOgl::getFunction<GlCompressedTextureSubImage2D>() const {
    return _glCompressedTextureSubImage2D;
}

template <>
inline const GlCompressedTextureSubImage3D&
GpuContextOgl::getFunction<GlCompressedTextureSubImage3D>() const {
    return _glCompressedTextureSubImage3D;
}

template <>
inline const GlCopyTextureSubImage1D&
GpuContextOgl::getFunction<GlCopyTextureSubImage1D>() const {
    return _glCopyTextureSubImage1D;
}

template <>
inline const GlCopyTextureSubImage2D&
GpuContextOgl::getFunction<GlCopyTextureSubImage2D>() const {
    return _glCopyTextureSubImage2D;
}

template <>
inline const GlCopyTextureSubImage3D&
GpuContextOgl::getFunction<GlCopyTextureSubImage3D>() const {
    return _glCopyTextureSubImage3D;
}

template <>
inline const GlTextureParameterf&
GpuContextOgl::getFunction<GlTextureParameterf>() const {
    return _glTextureParameterf;
}

template <>
inline const GlTextureParameterfv&
GpuContextOgl::getFunction<GlTextureParameterfv>() const {
    return _glTextureParameterfv;
}

template <>
inline const GlTextureParameteri&
GpuContextOgl::getFunction<GlTextureParameteri>() const {
    return _glTextureParameteri;
}

template <>
inline const GlTextureParameterIiv&
GpuContextOgl::getFunction<GlTextureParameterIiv>() const {
    return _glTextureParameterIiv;
}

template <>
inline const GlTextureParameterIuiv&
GpuContextOgl::getFunction<GlTextureParameterIuiv>() const {
    return _glTextureParameterIuiv;
}

template <>
inline const GlTextureParameteriv&
GpuContextOgl::getFunction<GlTextureParameteriv>() const {
    return _glTextureParameteriv;
}

template <>
inline const GlGenerateTextureMipmap&
GpuContextOgl::getFunction<GlGenerateTextureMipmap>() const {
    return _glGenerateTextureMipmap;
}

template <>
inline const GlBindTextureUnit&
GpuContextOgl::getFunction<GlBindTextureUnit>() const {
    return _glBindTextureUnit;
}

template <>
inline const GlGetTextureImage&
GpuContextOgl::getFunction<GlGetTextureImage>() const {
    return _glGetTextureImage;
}

template <>
inline const GlGetCompressedTextureImage&
GpuContextOgl::getFunction<GlGetCompressedTextureImage>() const {
    return _glGetCompressedTextureImage;
}

template <>
inline const GlGetTextureLevelParameterfv&
GpuContextOgl::getFunction<GlGetTextureLevelParameterfv>() const {
    return _glGetTextureLevelParameterfv;
}

template <>
inline const GlGetTextureLevelParameteriv&
GpuContextOgl::getFunction<GlGetTextureLevelParameteriv>() const {
    return _glGetTextureLevelParameteriv;
}

template <>
inline const GlGetTextureParameterfv&
GpuContextOgl::getFunction<GlGetTextureParameterfv>() const {
    return _glGetTextureParameterfv;
}

template <>
inline const GlGetTextureParameterIiv&
GpuContextOgl::getFunction<GlGetTextureParameterIiv>() const {
    return _glGetTextureParameterIiv;
}

template <>
inline const GlGetTextureParameterIuiv&
GpuContextOgl::getFunction<GlGetTextureParameterIuiv>() const {
    return _glGetTextureParameterIuiv;
}

template <>
inline const GlGetTextureParameteriv&
GpuContextOgl::getFunction<GlGetTextureParameteriv>() const {
    return _glGetTextureParameteriv;
}

template <>
inline const GlCreateVertexArrays&
GpuContextOgl::getFunction<GlCreateVertexArrays>() const {
    return _glCreateVertexArrays;
}

template <>
inline const GlDisableVertexArrayAttrib&
GpuContextOgl::getFunction<GlDisableVertexArrayAttrib>() const {
    return _glDisableVertexArrayAttrib;
}

template <>
inline const GlEnableVertexArrayAttrib&
GpuContextOgl::getFunction<GlEnableVertexArrayAttrib>() const {
    return _glEnableVertexArrayAttrib;
}

template <>
inline const GlVertexArrayElementBuffer&
GpuContextOgl::getFunction<GlVertexArrayElementBuffer>() const {
    return _glVertexArrayElementBuffer;
}

template <>
inline const GlVertexArrayVertexBuffer&
GpuContextOgl::getFunction<GlVertexArrayVertexBuffer>() const {
    return _glVertexArrayVertexBuffer;
}

template <>
inline const GlVertexArrayVertexBuffers&
GpuContextOgl::getFunction<GlVertexArrayVertexBuffers>() const {
    return _glVertexArrayVertexBuffers;
}

template <>
inline const GlVertexArrayAttribBinding&
GpuContextOgl::getFunction<GlVertexArrayAttribBinding>() const {
    return _glVertexArrayAttribBinding;
}

template <>
inline const GlVertexArrayAttribFormat&
GpuContextOgl::getFunction<GlVertexArrayAttribFormat>() const {
    return _glVertexArrayAttribFormat;
}

template <>
inline const GlVertexArrayAttribIFormat&
GpuContextOgl::getFunction<GlVertexArrayAttribIFormat>() const {
    return _glVertexArrayAttribIFormat;
}

template <>
inline const GlVertexArrayAttribLFormat&
GpuContextOgl::getFunction<GlVertexArrayAttribLFormat>() const {
    return _glVertexArrayAttribLFormat;
}

template <>
inline const GlVertexArrayBindingDivisor&
GpuContextOgl::getFunction<GlVertexArrayBindingDivisor>() const {
    return _glVertexArrayBindingDivisor;
}

template <>
inline const GlGetVertexArrayiv&
GpuContextOgl::getFunction<GlGetVertexArrayiv>() const {
    return _glGetVertexArrayiv;
}

template <>
inline const GlGetVertexArrayIndexediv&
GpuContextOgl::getFunction<GlGetVertexArrayIndexediv>() const {
    return _glGetVertexArrayIndexediv;
}

template <>
inline const GlGetVertexArrayIndexed64iv&
GpuContextOgl::getFunction<GlGetVertexArrayIndexed64iv>() const {
    return _glGetVertexArrayIndexed64iv;
}

template <>
inline const GlCreateSamplers&
GpuContextOgl::getFunction<GlCreateSamplers>() const {
    return _glCreateSamplers;
}

template <>
inline const GlCreateProgramPipelines&
GpuContextOgl::getFunction<GlCreateProgramPipelines>() const {
    return _glCreateProgramPipelines;
}

template <>
inline const GlCreateQueries&
GpuContextOgl::getFunction<GlCreateQueries>() const {
    return _glCreateQueries;
}

template <>
inline const GlGetQueryBufferObjecti64v&
GpuContextOgl::getFunction<GlGetQueryBufferObjecti64v>() const {
    return _glGetQueryBufferObjecti64v;
}

template <>
inline const GlGetQueryBufferObjectiv&
GpuContextOgl::getFunction<GlGetQueryBufferObjectiv>() const {
    return _glGetQueryBufferObjectiv;
}

template <>
inline const GlGetQueryBufferObjectui64v&
GpuContextOgl::getFunction<GlGetQueryBufferObjectui64v>() const {
    return _glGetQueryBufferObjectui64v;
}

template <>
inline const GlGetQueryBufferObjectuiv&
GpuContextOgl::getFunction<GlGetQueryBufferObjectuiv>() const {
    return _glGetQueryBufferObjectuiv;
}

template <>
inline const GlMemoryBarrierByRegion&
GpuContextOgl::getFunction<GlMemoryBarrierByRegion>() const {
    return _glMemoryBarrierByRegion;
}

template <>
inline const GlGetTextureSubImage&
GpuContextOgl::getFunction<GlGetTextureSubImage>() const {
    return _glGetTextureSubImage;
}

template <>
inline const GlGetCompressedTextureSubImage&
GpuContextOgl::getFunction<GlGetCompressedTextureSubImage>() const {
    return _glGetCompressedTextureSubImage;
}

template <>
inline const GlGetGraphicsResetStatus&
GpuContextOgl::getFunction<GlGetGraphicsResetStatus>() const {
    return _glGetGraphicsResetStatus;
}

template <>
inline const GlGetnCompressedTexImage&
GpuContextOgl::getFunction<GlGetnCompressedTexImage>() const {
    return _glGetnCompressedTexImage;
}

template <>
inline const GlGetnTexImage&
GpuContextOgl::getFunction<GlGetnTexImage>() const {
    return _glGetnTexImage;
}

template <>
inline const GlGetnUniformdv&
GpuContextOgl::getFunction<GlGetnUniformdv>() const {
    return _glGetnUniformdv;
}

template <>
inline const GlGetnUniformfv&
GpuContextOgl::getFunction<GlGetnUniformfv>() const {
    return _glGetnUniformfv;
}

template <>
inline const GlGetnUniformiv&
GpuContextOgl::getFunction<GlGetnUniformiv>() const {
    return _glGetnUniformiv;
}

template <>
inline const GlGetnUniformuiv&
GpuContextOgl::getFunction<GlGetnUniformuiv>() const {
    return _glGetnUniformuiv;
}

template <>
inline const GlReadnPixels&
GpuContextOgl::getFunction<GlReadnPixels>() const {
    return _glReadnPixels;
}

template <>
inline const GlTextureBarrier&
GpuContextOgl::getFunction<GlTextureBarrier>() const {
    return _glTextureBarrier;
}

template <>
inline const GlSpecializeShader&
GpuContextOgl::getFunction<GlSpecializeShader>() const {
    return _glSpecializeShader;
}

template <>
inline const GlMultiDrawArraysIndirectCount&
GpuContextOgl::getFunction<GlMultiDrawArraysIndirectCount>() const {
    return _glMultiDrawArraysIndirectCount;
}

template <>
inline const GlMultiDrawElementsIndirectCount&
GpuContextOgl::getFunction<GlMultiDrawElementsIndirectCount>() const {
    return _glMultiDrawElementsIndirectCount;
}

template <>
inline const GlPolygonOffsetClamp&
GpuContextOgl::getFunction<GlPolygonOffsetClamp>() const {
    return _glPolygonOffsetClamp;
}

template <>
inline const GlPrimitiveBoundingBoxARB&
GpuContextOgl::getFunction<GlPrimitiveBoundingBoxARB>() const {
    return _glPrimitiveBoundingBoxARB;
}

template <>
inline const GlGetTextureHandleARB&
GpuContextOgl::getFunction<GlGetTextureHandleARB>() const {
    return _glGetTextureHandleARB;
}

template <>
inline const GlGetTextureSamplerHandleARB&
GpuContextOgl::getFunction<GlGetTextureSamplerHandleARB>() const {
    return _glGetTextureSamplerHandleARB;
}

template <>
inline const GlMakeTextureHandleResidentARB&
GpuContextOgl::getFunction<GlMakeTextureHandleResidentARB>() const {
    return _glMakeTextureHandleResidentARB;
}

template <>
inline const GlMakeTextureHandleNonResidentARB&
GpuContextOgl::getFunction<GlMakeTextureHandleNonResidentARB>() const {
    return _glMakeTextureHandleNonResidentARB;
}

template <>
inline const GlGetImageHandleARB&
GpuContextOgl::getFunction<GlGetImageHandleARB>() const {
    return _glGetImageHandleARB;
}

template <>
inline const GlMakeImageHandleResidentARB&
GpuContextOgl::getFunction<GlMakeImageHandleResidentARB>() const {
    return _glMakeImageHandleResidentARB;
}

template <>
inline const GlMakeImageHandleNonResidentARB&
GpuContextOgl::getFunction<GlMakeImageHandleNonResidentARB>() const {
    return _glMakeImageHandleNonResidentARB;
}

template <>
inline const GlUniformHandleui64ARB&
GpuContextOgl::getFunction<GlUniformHandleui64ARB>() const {
    return _glUniformHandleui64ARB;
}

template <>
inline const GlUniformHandleui64vARB&
GpuContextOgl::getFunction<GlUniformHandleui64vARB>() const {
    return _glUniformHandleui64vARB;
}

template <>
inline const GlProgramUniformHandleui64ARB&
GpuContextOgl::getFunction<GlProgramUniformHandleui64ARB>() const {
    return _glProgramUniformHandleui64ARB;
}

template <>
inline const GlProgramUniformHandleui64vARB&
GpuContextOgl::getFunction<GlProgramUniformHandleui64vARB>() const {
    return _glProgramUniformHandleui64vARB;
}

template <>
inline const GlIsTextureHandleResidentARB&
GpuContextOgl::getFunction<GlIsTextureHandleResidentARB>() const {
    return _glIsTextureHandleResidentARB;
}

template <>
inline const GlIsImageHandleResidentARB&
GpuContextOgl::getFunction<GlIsImageHandleResidentARB>() const {
    return _glIsImageHandleResidentARB;
}

template <>
inline const GlVertexAttribL1ui64ARB&
GpuContextOgl::getFunction<GlVertexAttribL1ui64ARB>() const {
    return _glVertexAttribL1ui64ARB;
}

template <>
inline const GlVertexAttribL1ui64vARB&
GpuContextOgl::getFunction<GlVertexAttribL1ui64vARB>() const {
    return _glVertexAttribL1ui64vARB;
}

template <>
inline const GlGetVertexAttribLui64vARB&
GpuContextOgl::getFunction<GlGetVertexAttribLui64vARB>() const {
    return _glGetVertexAttribLui64vARB;
}

template <>
inline const GlCreateSyncFromCLeventARB&
GpuContextOgl::getFunction<GlCreateSyncFromCLeventARB>() const {
    return _glCreateSyncFromCLeventARB;
}

template <>
inline const GlDispatchComputeGroupSizeARB&
GpuContextOgl::getFunction<GlDispatchComputeGroupSizeARB>() const {
    return _glDispatchComputeGroupSizeARB;
}

template <>
inline const GlDebugMessageControlARB&
GpuContextOgl::getFunction<GlDebugMessageControlARB>() const {
    return _glDebugMessageControlARB;
}

template <>
inline const GlDebugMessageInsertARB&
GpuContextOgl::getFunction<GlDebugMessageInsertARB>() const {
    return _glDebugMessageInsertARB;
}

template <>
inline const GlDebugMessageCallbackARB&
GpuContextOgl::getFunction<GlDebugMessageCallbackARB>() const {
    return _glDebugMessageCallbackARB;
}

template <>
inline const GlGetDebugMessageLogARB&
GpuContextOgl::getFunction<GlGetDebugMessageLogARB>() const {
    return _glGetDebugMessageLogARB;
}

template <>
inline const GlBlendEquationiARB&
GpuContextOgl::getFunction<GlBlendEquationiARB>() const {
    return _glBlendEquationiARB;
}

template <>
inline const GlBlendEquationSeparateiARB&
GpuContextOgl::getFunction<GlBlendEquationSeparateiARB>() const {
    return _glBlendEquationSeparateiARB;
}

template <>
inline const GlBlendFunciARB&
GpuContextOgl::getFunction<GlBlendFunciARB>() const {
    return _glBlendFunciARB;
}

template <>
inline const GlBlendFuncSeparateiARB&
GpuContextOgl::getFunction<GlBlendFuncSeparateiARB>() const {
    return _glBlendFuncSeparateiARB;
}

template <>
inline const GlDrawArraysInstancedARB&
GpuContextOgl::getFunction<GlDrawArraysInstancedARB>() const {
    return _glDrawArraysInstancedARB;
}

template <>
inline const GlDrawElementsInstancedARB&
GpuContextOgl::getFunction<GlDrawElementsInstancedARB>() const {
    return _glDrawElementsInstancedARB;
}

template <>
inline const GlProgramParameteriARB&
GpuContextOgl::getFunction<GlProgramParameteriARB>() const {
    return _glProgramParameteriARB;
}

template <>
inline const GlFramebufferTextureARB&
GpuContextOgl::getFunction<GlFramebufferTextureARB>() const {
    return _glFramebufferTextureARB;
}

template <>
inline const GlFramebufferTextureLayerARB&
GpuContextOgl::getFunction<GlFramebufferTextureLayerARB>() const {
    return _glFramebufferTextureLayerARB;
}

template <>
inline const GlFramebufferTextureFaceARB&
GpuContextOgl::getFunction<GlFramebufferTextureFaceARB>() const {
    return _glFramebufferTextureFaceARB;
}

template <>
inline const GlSpecializeShaderARB&
GpuContextOgl::getFunction<GlSpecializeShaderARB>() const {
    return _glSpecializeShaderARB;
}

template <>
inline const GlUniform1i64ARB&
GpuContextOgl::getFunction<GlUniform1i64ARB>() const {
    return _glUniform1i64ARB;
}

template <>
inline const GlUniform2i64ARB&
GpuContextOgl::getFunction<GlUniform2i64ARB>() const {
    return _glUniform2i64ARB;
}

template <>
inline const GlUniform3i64ARB&
GpuContextOgl::getFunction<GlUniform3i64ARB>() const {
    return _glUniform3i64ARB;
}

template <>
inline const GlUniform4i64ARB&
GpuContextOgl::getFunction<GlUniform4i64ARB>() const {
    return _glUniform4i64ARB;
}

template <>
inline const GlUniform1i64vARB&
GpuContextOgl::getFunction<GlUniform1i64vARB>() const {
    return _glUniform1i64vARB;
}

template <>
inline const GlUniform2i64vARB&
GpuContextOgl::getFunction<GlUniform2i64vARB>() const {
    return _glUniform2i64vARB;
}

template <>
inline const GlUniform3i64vARB&
GpuContextOgl::getFunction<GlUniform3i64vARB>() const {
    return _glUniform3i64vARB;
}

template <>
inline const GlUniform4i64vARB&
GpuContextOgl::getFunction<GlUniform4i64vARB>() const {
    return _glUniform4i64vARB;
}

template <>
inline const GlUniform1ui64ARB&
GpuContextOgl::getFunction<GlUniform1ui64ARB>() const {
    return _glUniform1ui64ARB;
}

template <>
inline const GlUniform2ui64ARB&
GpuContextOgl::getFunction<GlUniform2ui64ARB>() const {
    return _glUniform2ui64ARB;
}

template <>
inline const GlUniform3ui64ARB&
GpuContextOgl::getFunction<GlUniform3ui64ARB>() const {
    return _glUniform3ui64ARB;
}

template <>
inline const GlUniform4ui64ARB&
GpuContextOgl::getFunction<GlUniform4ui64ARB>() const {
    return _glUniform4ui64ARB;
}

template <>
inline const GlUniform1ui64vARB&
GpuContextOgl::getFunction<GlUniform1ui64vARB>() const {
    return _glUniform1ui64vARB;
}

template <>
inline const GlUniform2ui64vARB&
GpuContextOgl::getFunction<GlUniform2ui64vARB>() const {
    return _glUniform2ui64vARB;
}

template <>
inline const GlUniform3ui64vARB&
GpuContextOgl::getFunction<GlUniform3ui64vARB>() const {
    return _glUniform3ui64vARB;
}

template <>
inline const GlUniform4ui64vARB&
GpuContextOgl::getFunction<GlUniform4ui64vARB>() const {
    return _glUniform4ui64vARB;
}

template <>
inline const GlGetUniformi64vARB&
GpuContextOgl::getFunction<GlGetUniformi64vARB>() const {
    return _glGetUniformi64vARB;
}

template <>
inline const GlGetUniformui64vARB&
GpuContextOgl::getFunction<GlGetUniformui64vARB>() const {
    return _glGetUniformui64vARB;
}

template <>
inline const GlGetnUniformi64vARB&
GpuContextOgl::getFunction<GlGetnUniformi64vARB>() const {
    return _glGetnUniformi64vARB;
}

template <>
inline const GlGetnUniformui64vARB&
GpuContextOgl::getFunction<GlGetnUniformui64vARB>() const {
    return _glGetnUniformui64vARB;
}

template <>
inline const GlProgramUniform1i64ARB&
GpuContextOgl::getFunction<GlProgramUniform1i64ARB>() const {
    return _glProgramUniform1i64ARB;
}

template <>
inline const GlProgramUniform2i64ARB&
GpuContextOgl::getFunction<GlProgramUniform2i64ARB>() const {
    return _glProgramUniform2i64ARB;
}

template <>
inline const GlProgramUniform3i64ARB&
GpuContextOgl::getFunction<GlProgramUniform3i64ARB>() const {
    return _glProgramUniform3i64ARB;
}

template <>
inline const GlProgramUniform4i64ARB&
GpuContextOgl::getFunction<GlProgramUniform4i64ARB>() const {
    return _glProgramUniform4i64ARB;
}

template <>
inline const GlProgramUniform1i64vARB&
GpuContextOgl::getFunction<GlProgramUniform1i64vARB>() const {
    return _glProgramUniform1i64vARB;
}

template <>
inline const GlProgramUniform2i64vARB&
GpuContextOgl::getFunction<GlProgramUniform2i64vARB>() const {
    return _glProgramUniform2i64vARB;
}

template <>
inline const GlProgramUniform3i64vARB&
GpuContextOgl::getFunction<GlProgramUniform3i64vARB>() const {
    return _glProgramUniform3i64vARB;
}

template <>
inline const GlProgramUniform4i64vARB&
GpuContextOgl::getFunction<GlProgramUniform4i64vARB>() const {
    return _glProgramUniform4i64vARB;
}

template <>
inline const GlProgramUniform1ui64ARB&
GpuContextOgl::getFunction<GlProgramUniform1ui64ARB>() const {
    return _glProgramUniform1ui64ARB;
}

template <>
inline const GlProgramUniform2ui64ARB&
GpuContextOgl::getFunction<GlProgramUniform2ui64ARB>() const {
    return _glProgramUniform2ui64ARB;
}

template <>
inline const GlProgramUniform3ui64ARB&
GpuContextOgl::getFunction<GlProgramUniform3ui64ARB>() const {
    return _glProgramUniform3ui64ARB;
}

template <>
inline const GlProgramUniform4ui64ARB&
GpuContextOgl::getFunction<GlProgramUniform4ui64ARB>() const {
    return _glProgramUniform4ui64ARB;
}

template <>
inline const GlProgramUniform1ui64vARB&
GpuContextOgl::getFunction<GlProgramUniform1ui64vARB>() const {
    return _glProgramUniform1ui64vARB;
}

template <>
inline const GlProgramUniform2ui64vARB&
GpuContextOgl::getFunction<GlProgramUniform2ui64vARB>() const {
    return _glProgramUniform2ui64vARB;
}

template <>
inline const GlProgramUniform3ui64vARB&
GpuContextOgl::getFunction<GlProgramUniform3ui64vARB>() const {
    return _glProgramUniform3ui64vARB;
}

template <>
inline const GlProgramUniform4ui64vARB&
GpuContextOgl::getFunction<GlProgramUniform4ui64vARB>() const {
    return _glProgramUniform4ui64vARB;
}

template <>
inline const GlMultiDrawArraysIndirectCountARB&
GpuContextOgl::getFunction<GlMultiDrawArraysIndirectCountARB>() const {
    return _glMultiDrawArraysIndirectCountARB;
}

template <>
inline const GlMultiDrawElementsIndirectCountARB&
GpuContextOgl::getFunction<GlMultiDrawElementsIndirectCountARB>() const {
    return _glMultiDrawElementsIndirectCountARB;
}

template <>
inline const GlVertexAttribDivisorARB&
GpuContextOgl::getFunction<GlVertexAttribDivisorARB>() const {
    return _glVertexAttribDivisorARB;
}

template <>
inline const GlMaxShaderCompilerThreadsARB&
GpuContextOgl::getFunction<GlMaxShaderCompilerThreadsARB>() const {
    return _glMaxShaderCompilerThreadsARB;
}

template <>
inline const GlGetGraphicsResetStatusARB&
GpuContextOgl::getFunction<GlGetGraphicsResetStatusARB>() const {
    return _glGetGraphicsResetStatusARB;
}

template <>
inline const GlGetnTexImageARB&
GpuContextOgl::getFunction<GlGetnTexImageARB>() const {
    return _glGetnTexImageARB;
}

template <>
inline const GlReadnPixelsARB&
GpuContextOgl::getFunction<GlReadnPixelsARB>() const {
    return _glReadnPixelsARB;
}

template <>
inline const GlGetnCompressedTexImageARB&
GpuContextOgl::getFunction<GlGetnCompressedTexImageARB>() const {
    return _glGetnCompressedTexImageARB;
}

template <>
inline const GlGetnUniformfvARB&
GpuContextOgl::getFunction<GlGetnUniformfvARB>() const {
    return _glGetnUniformfvARB;
}

template <>
inline const GlGetnUniformivARB&
GpuContextOgl::getFunction<GlGetnUniformivARB>() const {
    return _glGetnUniformivARB;
}

template <>
inline const GlGetnUniformuivARB&
GpuContextOgl::getFunction<GlGetnUniformuivARB>() const {
    return _glGetnUniformuivARB;
}

template <>
inline const GlGetnUniformdvARB&
GpuContextOgl::getFunction<GlGetnUniformdvARB>() const {
    return _glGetnUniformdvARB;
}

template <>
inline const GlFramebufferSampleLocationsfvARB&
GpuContextOgl::getFunction<GlFramebufferSampleLocationsfvARB>() const {
    return _glFramebufferSampleLocationsfvARB;
}

template <>
inline const GlNamedFramebufferSampleLocationsfvARB&
GpuContextOgl::getFunction<GlNamedFramebufferSampleLocationsfvARB>() const {
    return _glNamedFramebufferSampleLocationsfvARB;
}

template <>
inline const GlEvaluateDepthValuesARB&
GpuContextOgl::getFunction<GlEvaluateDepthValuesARB>() const {
    return _glEvaluateDepthValuesARB;
}

template <>
inline const GlMinSampleShadingARB&
GpuContextOgl::getFunction<GlMinSampleShadingARB>() const {
    return _glMinSampleShadingARB;
}

template <>
inline const GlNamedStringARB&
GpuContextOgl::getFunction<GlNamedStringARB>() const {
    return _glNamedStringARB;
}

template <>
inline const GlDeleteNamedStringARB&
GpuContextOgl::getFunction<GlDeleteNamedStringARB>() const {
    return _glDeleteNamedStringARB;
}

template <>
inline const GlCompileShaderIncludeARB&
GpuContextOgl::getFunction<GlCompileShaderIncludeARB>() const {
    return _glCompileShaderIncludeARB;
}

template <>
inline const GlIsNamedStringARB&
GpuContextOgl::getFunction<GlIsNamedStringARB>() const {
    return _glIsNamedStringARB;
}

template <>
inline const GlGetNamedStringARB&
GpuContextOgl::getFunction<GlGetNamedStringARB>() const {
    return _glGetNamedStringARB;
}

template <>
inline const GlGetNamedStringivARB&
GpuContextOgl::getFunction<GlGetNamedStringivARB>() const {
    return _glGetNamedStringivARB;
}

template <>
inline const GlBufferPageCommitmentARB&
GpuContextOgl::getFunction<GlBufferPageCommitmentARB>() const {
    return _glBufferPageCommitmentARB;
}

template <>
inline const GlNamedBufferPageCommitmentEXT&
GpuContextOgl::getFunction<GlNamedBufferPageCommitmentEXT>() const {
    return _glNamedBufferPageCommitmentEXT;
}

template <>
inline const GlNamedBufferPageCommitmentARB&
GpuContextOgl::getFunction<GlNamedBufferPageCommitmentARB>() const {
    return _glNamedBufferPageCommitmentARB;
}

template <>
inline const GlTexPageCommitmentARB&
GpuContextOgl::getFunction<GlTexPageCommitmentARB>() const {
    return _glTexPageCommitmentARB;
}

template <>
inline const GlTexBufferARB&
GpuContextOgl::getFunction<GlTexBufferARB>() const {
    return _glTexBufferARB;
}

template <>
inline const GlBlendBarrierKHR&
GpuContextOgl::getFunction<GlBlendBarrierKHR>() const {
    return _glBlendBarrierKHR;
}

template <>
inline const GlMaxShaderCompilerThreadsKHR&
GpuContextOgl::getFunction<GlMaxShaderCompilerThreadsKHR>() const {
    return _glMaxShaderCompilerThreadsKHR;
}

template <>
inline const GlGetPerfMonitorGroupsAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorGroupsAMD>() const {
    return _glGetPerfMonitorGroupsAMD;
}

template <>
inline const GlGetPerfMonitorCountersAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorCountersAMD>() const {
    return _glGetPerfMonitorCountersAMD;
}

template <>
inline const GlGetPerfMonitorGroupStringAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorGroupStringAMD>() const {
    return _glGetPerfMonitorGroupStringAMD;
}

template <>
inline const GlGetPerfMonitorCounterStringAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorCounterStringAMD>() const {
    return _glGetPerfMonitorCounterStringAMD;
}

template <>
inline const GlGetPerfMonitorCounterInfoAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorCounterInfoAMD>() const {
    return _glGetPerfMonitorCounterInfoAMD;
}

template <>
inline const GlGenPerfMonitorsAMD&
GpuContextOgl::getFunction<GlGenPerfMonitorsAMD>() const {
    return _glGenPerfMonitorsAMD;
}

template <>
inline const GlDeletePerfMonitorsAMD&
GpuContextOgl::getFunction<GlDeletePerfMonitorsAMD>() const {
    return _glDeletePerfMonitorsAMD;
}

template <>
inline const GlSelectPerfMonitorCountersAMD&
GpuContextOgl::getFunction<GlSelectPerfMonitorCountersAMD>() const {
    return _glSelectPerfMonitorCountersAMD;
}

template <>
inline const GlBeginPerfMonitorAMD&
GpuContextOgl::getFunction<GlBeginPerfMonitorAMD>() const {
    return _glBeginPerfMonitorAMD;
}

template <>
inline const GlEndPerfMonitorAMD&
GpuContextOgl::getFunction<GlEndPerfMonitorAMD>() const {
    return _glEndPerfMonitorAMD;
}

template <>
inline const GlGetPerfMonitorCounterDataAMD&
GpuContextOgl::getFunction<GlGetPerfMonitorCounterDataAMD>() const {
    return _glGetPerfMonitorCounterDataAMD;
}

template <>
inline const GlEGLImageTargetTexStorageEXT&
GpuContextOgl::getFunction<GlEGLImageTargetTexStorageEXT>() const {
    return _glEGLImageTargetTexStorageEXT;
}

template <>
inline const GlEGLImageTargetTextureStorageEXT&
GpuContextOgl::getFunction<GlEGLImageTargetTextureStorageEXT>() const {
    return _glEGLImageTargetTextureStorageEXT;
}

template <>
inline const GlLabelObjectEXT&
GpuContextOgl::getFunction<GlLabelObjectEXT>() const {
    return _glLabelObjectEXT;
}

template <>
inline const GlGetObjectLabelEXT&
GpuContextOgl::getFunction<GlGetObjectLabelEXT>() const {
    return _glGetObjectLabelEXT;
}

template <>
inline const GlInsertEventMarkerEXT&
GpuContextOgl::getFunction<GlInsertEventMarkerEXT>() const {
    return _glInsertEventMarkerEXT;
}

template <>
inline const GlPushGroupMarkerEXT&
GpuContextOgl::getFunction<GlPushGroupMarkerEXT>() const {
    return _glPushGroupMarkerEXT;
}

template <>
inline const GlPopGroupMarkerEXT&
GpuContextOgl::getFunction<GlPopGroupMarkerEXT>() const {
    return _glPopGroupMarkerEXT;
}

template <>
inline const GlMatrixLoadfEXT&
GpuContextOgl::getFunction<GlMatrixLoadfEXT>() const {
    return _glMatrixLoadfEXT;
}

template <>
inline const GlMatrixLoaddEXT&
GpuContextOgl::getFunction<GlMatrixLoaddEXT>() const {
    return _glMatrixLoaddEXT;
}

template <>
inline const GlMatrixMultfEXT&
GpuContextOgl::getFunction<GlMatrixMultfEXT>() const {
    return _glMatrixMultfEXT;
}

template <>
inline const GlMatrixMultdEXT&
GpuContextOgl::getFunction<GlMatrixMultdEXT>() const {
    return _glMatrixMultdEXT;
}

template <>
inline const GlMatrixLoadIdentityEXT&
GpuContextOgl::getFunction<GlMatrixLoadIdentityEXT>() const {
    return _glMatrixLoadIdentityEXT;
}

template <>
inline const GlMatrixRotatefEXT&
GpuContextOgl::getFunction<GlMatrixRotatefEXT>() const {
    return _glMatrixRotatefEXT;
}

template <>
inline const GlMatrixRotatedEXT&
GpuContextOgl::getFunction<GlMatrixRotatedEXT>() const {
    return _glMatrixRotatedEXT;
}

template <>
inline const GlMatrixScalefEXT&
GpuContextOgl::getFunction<GlMatrixScalefEXT>() const {
    return _glMatrixScalefEXT;
}

template <>
inline const GlMatrixScaledEXT&
GpuContextOgl::getFunction<GlMatrixScaledEXT>() const {
    return _glMatrixScaledEXT;
}

template <>
inline const GlMatrixTranslatefEXT&
GpuContextOgl::getFunction<GlMatrixTranslatefEXT>() const {
    return _glMatrixTranslatefEXT;
}

template <>
inline const GlMatrixTranslatedEXT&
GpuContextOgl::getFunction<GlMatrixTranslatedEXT>() const {
    return _glMatrixTranslatedEXT;
}

template <>
inline const GlMatrixFrustumEXT&
GpuContextOgl::getFunction<GlMatrixFrustumEXT>() const {
    return _glMatrixFrustumEXT;
}

template <>
inline const GlMatrixOrthoEXT&
GpuContextOgl::getFunction<GlMatrixOrthoEXT>() const {
    return _glMatrixOrthoEXT;
}

template <>
inline const GlMatrixPopEXT&
GpuContextOgl::getFunction<GlMatrixPopEXT>() const {
    return _glMatrixPopEXT;
}

template <>
inline const GlMatrixPushEXT&
GpuContextOgl::getFunction<GlMatrixPushEXT>() const {
    return _glMatrixPushEXT;
}

template <>
inline const GlClientAttribDefaultEXT&
GpuContextOgl::getFunction<GlClientAttribDefaultEXT>() const {
    return _glClientAttribDefaultEXT;
}

template <>
inline const GlPushClientAttribDefaultEXT&
GpuContextOgl::getFunction<GlPushClientAttribDefaultEXT>() const {
    return _glPushClientAttribDefaultEXT;
}

template <>
inline const GlTextureParameterfEXT&
GpuContextOgl::getFunction<GlTextureParameterfEXT>() const {
    return _glTextureParameterfEXT;
}

template <>
inline const GlTextureParameterfvEXT&
GpuContextOgl::getFunction<GlTextureParameterfvEXT>() const {
    return _glTextureParameterfvEXT;
}

template <>
inline const GlTextureParameteriEXT&
GpuContextOgl::getFunction<GlTextureParameteriEXT>() const {
    return _glTextureParameteriEXT;
}

template <>
inline const GlTextureParameterivEXT&
GpuContextOgl::getFunction<GlTextureParameterivEXT>() const {
    return _glTextureParameterivEXT;
}

template <>
inline const GlTextureImage1DEXT&
GpuContextOgl::getFunction<GlTextureImage1DEXT>() const {
    return _glTextureImage1DEXT;
}

template <>
inline const GlTextureImage2DEXT&
GpuContextOgl::getFunction<GlTextureImage2DEXT>() const {
    return _glTextureImage2DEXT;
}

template <>
inline const GlTextureSubImage1DEXT&
GpuContextOgl::getFunction<GlTextureSubImage1DEXT>() const {
    return _glTextureSubImage1DEXT;
}

template <>
inline const GlTextureSubImage2DEXT&
GpuContextOgl::getFunction<GlTextureSubImage2DEXT>() const {
    return _glTextureSubImage2DEXT;
}

template <>
inline const GlCopyTextureImage1DEXT&
GpuContextOgl::getFunction<GlCopyTextureImage1DEXT>() const {
    return _glCopyTextureImage1DEXT;
}

template <>
inline const GlCopyTextureImage2DEXT&
GpuContextOgl::getFunction<GlCopyTextureImage2DEXT>() const {
    return _glCopyTextureImage2DEXT;
}

template <>
inline const GlCopyTextureSubImage1DEXT&
GpuContextOgl::getFunction<GlCopyTextureSubImage1DEXT>() const {
    return _glCopyTextureSubImage1DEXT;
}

template <>
inline const GlCopyTextureSubImage2DEXT&
GpuContextOgl::getFunction<GlCopyTextureSubImage2DEXT>() const {
    return _glCopyTextureSubImage2DEXT;
}

template <>
inline const GlGetTextureImageEXT&
GpuContextOgl::getFunction<GlGetTextureImageEXT>() const {
    return _glGetTextureImageEXT;
}

template <>
inline const GlGetTextureParameterfvEXT&
GpuContextOgl::getFunction<GlGetTextureParameterfvEXT>() const {
    return _glGetTextureParameterfvEXT;
}

template <>
inline const GlGetTextureParameterivEXT&
GpuContextOgl::getFunction<GlGetTextureParameterivEXT>() const {
    return _glGetTextureParameterivEXT;
}

template <>
inline const GlGetTextureLevelParameterfvEXT&
GpuContextOgl::getFunction<GlGetTextureLevelParameterfvEXT>() const {
    return _glGetTextureLevelParameterfvEXT;
}

template <>
inline const GlGetTextureLevelParameterivEXT&
GpuContextOgl::getFunction<GlGetTextureLevelParameterivEXT>() const {
    return _glGetTextureLevelParameterivEXT;
}

template <>
inline const GlTextureImage3DEXT&
GpuContextOgl::getFunction<GlTextureImage3DEXT>() const {
    return _glTextureImage3DEXT;
}

template <>
inline const GlTextureSubImage3DEXT&
GpuContextOgl::getFunction<GlTextureSubImage3DEXT>() const {
    return _glTextureSubImage3DEXT;
}

template <>
inline const GlCopyTextureSubImage3DEXT&
GpuContextOgl::getFunction<GlCopyTextureSubImage3DEXT>() const {
    return _glCopyTextureSubImage3DEXT;
}

template <>
inline const GlBindMultiTextureEXT&
GpuContextOgl::getFunction<GlBindMultiTextureEXT>() const {
    return _glBindMultiTextureEXT;
}

template <>
inline const GlMultiTexCoordPointerEXT&
GpuContextOgl::getFunction<GlMultiTexCoordPointerEXT>() const {
    return _glMultiTexCoordPointerEXT;
}

template <>
inline const GlMultiTexEnvfEXT&
GpuContextOgl::getFunction<GlMultiTexEnvfEXT>() const {
    return _glMultiTexEnvfEXT;
}

template <>
inline const GlMultiTexEnvfvEXT&
GpuContextOgl::getFunction<GlMultiTexEnvfvEXT>() const {
    return _glMultiTexEnvfvEXT;
}

template <>
inline const GlMultiTexEnviEXT&
GpuContextOgl::getFunction<GlMultiTexEnviEXT>() const {
    return _glMultiTexEnviEXT;
}

template <>
inline const GlMultiTexEnvivEXT&
GpuContextOgl::getFunction<GlMultiTexEnvivEXT>() const {
    return _glMultiTexEnvivEXT;
}

template <>
inline const GlMultiTexGendEXT&
GpuContextOgl::getFunction<GlMultiTexGendEXT>() const {
    return _glMultiTexGendEXT;
}

template <>
inline const GlMultiTexGendvEXT&
GpuContextOgl::getFunction<GlMultiTexGendvEXT>() const {
    return _glMultiTexGendvEXT;
}

template <>
inline const GlMultiTexGenfEXT&
GpuContextOgl::getFunction<GlMultiTexGenfEXT>() const {
    return _glMultiTexGenfEXT;
}

template <>
inline const GlMultiTexGenfvEXT&
GpuContextOgl::getFunction<GlMultiTexGenfvEXT>() const {
    return _glMultiTexGenfvEXT;
}

template <>
inline const GlMultiTexGeniEXT&
GpuContextOgl::getFunction<GlMultiTexGeniEXT>() const {
    return _glMultiTexGeniEXT;
}

template <>
inline const GlMultiTexGenivEXT&
GpuContextOgl::getFunction<GlMultiTexGenivEXT>() const {
    return _glMultiTexGenivEXT;
}

template <>
inline const GlGetMultiTexEnvfvEXT&
GpuContextOgl::getFunction<GlGetMultiTexEnvfvEXT>() const {
    return _glGetMultiTexEnvfvEXT;
}

template <>
inline const GlGetMultiTexEnvivEXT&
GpuContextOgl::getFunction<GlGetMultiTexEnvivEXT>() const {
    return _glGetMultiTexEnvivEXT;
}

template <>
inline const GlGetMultiTexGendvEXT&
GpuContextOgl::getFunction<GlGetMultiTexGendvEXT>() const {
    return _glGetMultiTexGendvEXT;
}

template <>
inline const GlGetMultiTexGenfvEXT&
GpuContextOgl::getFunction<GlGetMultiTexGenfvEXT>() const {
    return _glGetMultiTexGenfvEXT;
}

template <>
inline const GlGetMultiTexGenivEXT&
GpuContextOgl::getFunction<GlGetMultiTexGenivEXT>() const {
    return _glGetMultiTexGenivEXT;
}

template <>
inline const GlMultiTexParameteriEXT&
GpuContextOgl::getFunction<GlMultiTexParameteriEXT>() const {
    return _glMultiTexParameteriEXT;
}

template <>
inline const GlMultiTexParameterivEXT&
GpuContextOgl::getFunction<GlMultiTexParameterivEXT>() const {
    return _glMultiTexParameterivEXT;
}

template <>
inline const GlMultiTexParameterfEXT&
GpuContextOgl::getFunction<GlMultiTexParameterfEXT>() const {
    return _glMultiTexParameterfEXT;
}

template <>
inline const GlMultiTexParameterfvEXT&
GpuContextOgl::getFunction<GlMultiTexParameterfvEXT>() const {
    return _glMultiTexParameterfvEXT;
}

template <>
inline const GlMultiTexImage1DEXT&
GpuContextOgl::getFunction<GlMultiTexImage1DEXT>() const {
    return _glMultiTexImage1DEXT;
}

template <>
inline const GlMultiTexImage2DEXT&
GpuContextOgl::getFunction<GlMultiTexImage2DEXT>() const {
    return _glMultiTexImage2DEXT;
}

template <>
inline const GlMultiTexSubImage1DEXT&
GpuContextOgl::getFunction<GlMultiTexSubImage1DEXT>() const {
    return _glMultiTexSubImage1DEXT;
}

template <>
inline const GlMultiTexSubImage2DEXT&
GpuContextOgl::getFunction<GlMultiTexSubImage2DEXT>() const {
    return _glMultiTexSubImage2DEXT;
}

template <>
inline const GlCopyMultiTexImage1DEXT&
GpuContextOgl::getFunction<GlCopyMultiTexImage1DEXT>() const {
    return _glCopyMultiTexImage1DEXT;
}

template <>
inline const GlCopyMultiTexImage2DEXT&
GpuContextOgl::getFunction<GlCopyMultiTexImage2DEXT>() const {
    return _glCopyMultiTexImage2DEXT;
}

template <>
inline const GlCopyMultiTexSubImage1DEXT&
GpuContextOgl::getFunction<GlCopyMultiTexSubImage1DEXT>() const {
    return _glCopyMultiTexSubImage1DEXT;
}

template <>
inline const GlCopyMultiTexSubImage2DEXT&
GpuContextOgl::getFunction<GlCopyMultiTexSubImage2DEXT>() const {
    return _glCopyMultiTexSubImage2DEXT;
}

template <>
inline const GlGetMultiTexImageEXT&
GpuContextOgl::getFunction<GlGetMultiTexImageEXT>() const {
    return _glGetMultiTexImageEXT;
}

template <>
inline const GlGetMultiTexParameterfvEXT&
GpuContextOgl::getFunction<GlGetMultiTexParameterfvEXT>() const {
    return _glGetMultiTexParameterfvEXT;
}

template <>
inline const GlGetMultiTexParameterivEXT&
GpuContextOgl::getFunction<GlGetMultiTexParameterivEXT>() const {
    return _glGetMultiTexParameterivEXT;
}

template <>
inline const GlGetMultiTexLevelParameterfvEXT&
GpuContextOgl::getFunction<GlGetMultiTexLevelParameterfvEXT>() const {
    return _glGetMultiTexLevelParameterfvEXT;
}

template <>
inline const GlGetMultiTexLevelParameterivEXT&
GpuContextOgl::getFunction<GlGetMultiTexLevelParameterivEXT>() const {
    return _glGetMultiTexLevelParameterivEXT;
}

template <>
inline const GlMultiTexImage3DEXT&
GpuContextOgl::getFunction<GlMultiTexImage3DEXT>() const {
    return _glMultiTexImage3DEXT;
}

template <>
inline const GlMultiTexSubImage3DEXT&
GpuContextOgl::getFunction<GlMultiTexSubImage3DEXT>() const {
    return _glMultiTexSubImage3DEXT;
}

template <>
inline const GlCopyMultiTexSubImage3DEXT&
GpuContextOgl::getFunction<GlCopyMultiTexSubImage3DEXT>() const {
    return _glCopyMultiTexSubImage3DEXT;
}

template <>
inline const GlEnableClientStateIndexedEXT&
GpuContextOgl::getFunction<GlEnableClientStateIndexedEXT>() const {
    return _glEnableClientStateIndexedEXT;
}

template <>
inline const GlDisableClientStateIndexedEXT&
GpuContextOgl::getFunction<GlDisableClientStateIndexedEXT>() const {
    return _glDisableClientStateIndexedEXT;
}

template <>
inline const GlGetFloatIndexedvEXT&
GpuContextOgl::getFunction<GlGetFloatIndexedvEXT>() const {
    return _glGetFloatIndexedvEXT;
}

template <>
inline const GlGetDoubleIndexedvEXT&
GpuContextOgl::getFunction<GlGetDoubleIndexedvEXT>() const {
    return _glGetDoubleIndexedvEXT;
}

template <>
inline const GlGetPointerIndexedvEXT&
GpuContextOgl::getFunction<GlGetPointerIndexedvEXT>() const {
    return _glGetPointerIndexedvEXT;
}

template <>
inline const GlEnableIndexedEXT&
GpuContextOgl::getFunction<GlEnableIndexedEXT>() const {
    return _glEnableIndexedEXT;
}

template <>
inline const GlDisableIndexedEXT&
GpuContextOgl::getFunction<GlDisableIndexedEXT>() const {
    return _glDisableIndexedEXT;
}

template <>
inline const GlIsEnabledIndexedEXT&
GpuContextOgl::getFunction<GlIsEnabledIndexedEXT>() const {
    return _glIsEnabledIndexedEXT;
}

template <>
inline const GlGetIntegerIndexedvEXT&
GpuContextOgl::getFunction<GlGetIntegerIndexedvEXT>() const {
    return _glGetIntegerIndexedvEXT;
}

template <>
inline const GlGetBooleanIndexedvEXT&
GpuContextOgl::getFunction<GlGetBooleanIndexedvEXT>() const {
    return _glGetBooleanIndexedvEXT;
}

template <>
inline const GlCompressedTextureImage3DEXT&
GpuContextOgl::getFunction<GlCompressedTextureImage3DEXT>() const {
    return _glCompressedTextureImage3DEXT;
}

template <>
inline const GlCompressedTextureImage2DEXT&
GpuContextOgl::getFunction<GlCompressedTextureImage2DEXT>() const {
    return _glCompressedTextureImage2DEXT;
}

template <>
inline const GlCompressedTextureImage1DEXT&
GpuContextOgl::getFunction<GlCompressedTextureImage1DEXT>() const {
    return _glCompressedTextureImage1DEXT;
}

template <>
inline const GlCompressedTextureSubImage3DEXT&
GpuContextOgl::getFunction<GlCompressedTextureSubImage3DEXT>() const {
    return _glCompressedTextureSubImage3DEXT;
}

template <>
inline const GlCompressedTextureSubImage2DEXT&
GpuContextOgl::getFunction<GlCompressedTextureSubImage2DEXT>() const {
    return _glCompressedTextureSubImage2DEXT;
}

template <>
inline const GlCompressedTextureSubImage1DEXT&
GpuContextOgl::getFunction<GlCompressedTextureSubImage1DEXT>() const {
    return _glCompressedTextureSubImage1DEXT;
}

template <>
inline const GlGetCompressedTextureImageEXT&
GpuContextOgl::getFunction<GlGetCompressedTextureImageEXT>() const {
    return _glGetCompressedTextureImageEXT;
}

template <>
inline const GlCompressedMultiTexImage3DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexImage3DEXT>() const {
    return _glCompressedMultiTexImage3DEXT;
}

template <>
inline const GlCompressedMultiTexImage2DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexImage2DEXT>() const {
    return _glCompressedMultiTexImage2DEXT;
}

template <>
inline const GlCompressedMultiTexImage1DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexImage1DEXT>() const {
    return _glCompressedMultiTexImage1DEXT;
}

template <>
inline const GlCompressedMultiTexSubImage3DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexSubImage3DEXT>() const {
    return _glCompressedMultiTexSubImage3DEXT;
}

template <>
inline const GlCompressedMultiTexSubImage2DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexSubImage2DEXT>() const {
    return _glCompressedMultiTexSubImage2DEXT;
}

template <>
inline const GlCompressedMultiTexSubImage1DEXT&
GpuContextOgl::getFunction<GlCompressedMultiTexSubImage1DEXT>() const {
    return _glCompressedMultiTexSubImage1DEXT;
}

template <>
inline const GlGetCompressedMultiTexImageEXT&
GpuContextOgl::getFunction<GlGetCompressedMultiTexImageEXT>() const {
    return _glGetCompressedMultiTexImageEXT;
}

template <>
inline const GlMatrixLoadTransposefEXT&
GpuContextOgl::getFunction<GlMatrixLoadTransposefEXT>() const {
    return _glMatrixLoadTransposefEXT;
}

template <>
inline const GlMatrixLoadTransposedEXT&
GpuContextOgl::getFunction<GlMatrixLoadTransposedEXT>() const {
    return _glMatrixLoadTransposedEXT;
}

template <>
inline const GlMatrixMultTransposefEXT&
GpuContextOgl::getFunction<GlMatrixMultTransposefEXT>() const {
    return _glMatrixMultTransposefEXT;
}

template <>
inline const GlMatrixMultTransposedEXT&
GpuContextOgl::getFunction<GlMatrixMultTransposedEXT>() const {
    return _glMatrixMultTransposedEXT;
}

template <>
inline const GlNamedBufferDataEXT&
GpuContextOgl::getFunction<GlNamedBufferDataEXT>() const {
    return _glNamedBufferDataEXT;
}

template <>
inline const GlNamedBufferSubDataEXT&
GpuContextOgl::getFunction<GlNamedBufferSubDataEXT>() const {
    return _glNamedBufferSubDataEXT;
}

template <>
inline const GlMapNamedBufferEXT&
GpuContextOgl::getFunction<GlMapNamedBufferEXT>() const {
    return _glMapNamedBufferEXT;
}

template <>
inline const GlUnmapNamedBufferEXT&
GpuContextOgl::getFunction<GlUnmapNamedBufferEXT>() const {
    return _glUnmapNamedBufferEXT;
}

template <>
inline const GlGetNamedBufferParameterivEXT&
GpuContextOgl::getFunction<GlGetNamedBufferParameterivEXT>() const {
    return _glGetNamedBufferParameterivEXT;
}

template <>
inline const GlGetNamedBufferPointervEXT&
GpuContextOgl::getFunction<GlGetNamedBufferPointervEXT>() const {
    return _glGetNamedBufferPointervEXT;
}

template <>
inline const GlGetNamedBufferSubDataEXT&
GpuContextOgl::getFunction<GlGetNamedBufferSubDataEXT>() const {
    return _glGetNamedBufferSubDataEXT;
}

template <>
inline const GlProgramUniform1fEXT&
GpuContextOgl::getFunction<GlProgramUniform1fEXT>() const {
    return _glProgramUniform1fEXT;
}

template <>
inline const GlProgramUniform2fEXT&
GpuContextOgl::getFunction<GlProgramUniform2fEXT>() const {
    return _glProgramUniform2fEXT;
}

template <>
inline const GlProgramUniform3fEXT&
GpuContextOgl::getFunction<GlProgramUniform3fEXT>() const {
    return _glProgramUniform3fEXT;
}

template <>
inline const GlProgramUniform4fEXT&
GpuContextOgl::getFunction<GlProgramUniform4fEXT>() const {
    return _glProgramUniform4fEXT;
}

template <>
inline const GlProgramUniform1iEXT&
GpuContextOgl::getFunction<GlProgramUniform1iEXT>() const {
    return _glProgramUniform1iEXT;
}

template <>
inline const GlProgramUniform2iEXT&
GpuContextOgl::getFunction<GlProgramUniform2iEXT>() const {
    return _glProgramUniform2iEXT;
}

template <>
inline const GlProgramUniform3iEXT&
GpuContextOgl::getFunction<GlProgramUniform3iEXT>() const {
    return _glProgramUniform3iEXT;
}

template <>
inline const GlProgramUniform4iEXT&
GpuContextOgl::getFunction<GlProgramUniform4iEXT>() const {
    return _glProgramUniform4iEXT;
}

template <>
inline const GlProgramUniform1fvEXT&
GpuContextOgl::getFunction<GlProgramUniform1fvEXT>() const {
    return _glProgramUniform1fvEXT;
}

template <>
inline const GlProgramUniform2fvEXT&
GpuContextOgl::getFunction<GlProgramUniform2fvEXT>() const {
    return _glProgramUniform2fvEXT;
}

template <>
inline const GlProgramUniform3fvEXT&
GpuContextOgl::getFunction<GlProgramUniform3fvEXT>() const {
    return _glProgramUniform3fvEXT;
}

template <>
inline const GlProgramUniform4fvEXT&
GpuContextOgl::getFunction<GlProgramUniform4fvEXT>() const {
    return _glProgramUniform4fvEXT;
}

template <>
inline const GlProgramUniform1ivEXT&
GpuContextOgl::getFunction<GlProgramUniform1ivEXT>() const {
    return _glProgramUniform1ivEXT;
}

template <>
inline const GlProgramUniform2ivEXT&
GpuContextOgl::getFunction<GlProgramUniform2ivEXT>() const {
    return _glProgramUniform2ivEXT;
}

template <>
inline const GlProgramUniform3ivEXT&
GpuContextOgl::getFunction<GlProgramUniform3ivEXT>() const {
    return _glProgramUniform3ivEXT;
}

template <>
inline const GlProgramUniform4ivEXT&
GpuContextOgl::getFunction<GlProgramUniform4ivEXT>() const {
    return _glProgramUniform4ivEXT;
}

template <>
inline const GlProgramUniformMatrix2fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2fvEXT>() const {
    return _glProgramUniformMatrix2fvEXT;
}

template <>
inline const GlProgramUniformMatrix3fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3fvEXT>() const {
    return _glProgramUniformMatrix3fvEXT;
}

template <>
inline const GlProgramUniformMatrix4fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4fvEXT>() const {
    return _glProgramUniformMatrix4fvEXT;
}

template <>
inline const GlProgramUniformMatrix2x3fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x3fvEXT>() const {
    return _glProgramUniformMatrix2x3fvEXT;
}

template <>
inline const GlProgramUniformMatrix3x2fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x2fvEXT>() const {
    return _glProgramUniformMatrix3x2fvEXT;
}

template <>
inline const GlProgramUniformMatrix2x4fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x4fvEXT>() const {
    return _glProgramUniformMatrix2x4fvEXT;
}

template <>
inline const GlProgramUniformMatrix4x2fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x2fvEXT>() const {
    return _glProgramUniformMatrix4x2fvEXT;
}

template <>
inline const GlProgramUniformMatrix3x4fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x4fvEXT>() const {
    return _glProgramUniformMatrix3x4fvEXT;
}

template <>
inline const GlProgramUniformMatrix4x3fvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x3fvEXT>() const {
    return _glProgramUniformMatrix4x3fvEXT;
}

template <>
inline const GlTextureBufferEXT&
GpuContextOgl::getFunction<GlTextureBufferEXT>() const {
    return _glTextureBufferEXT;
}

template <>
inline const GlMultiTexBufferEXT&
GpuContextOgl::getFunction<GlMultiTexBufferEXT>() const {
    return _glMultiTexBufferEXT;
}

template <>
inline const GlTextureParameterIivEXT&
GpuContextOgl::getFunction<GlTextureParameterIivEXT>() const {
    return _glTextureParameterIivEXT;
}

template <>
inline const GlTextureParameterIuivEXT&
GpuContextOgl::getFunction<GlTextureParameterIuivEXT>() const {
    return _glTextureParameterIuivEXT;
}

template <>
inline const GlGetTextureParameterIivEXT&
GpuContextOgl::getFunction<GlGetTextureParameterIivEXT>() const {
    return _glGetTextureParameterIivEXT;
}

template <>
inline const GlGetTextureParameterIuivEXT&
GpuContextOgl::getFunction<GlGetTextureParameterIuivEXT>() const {
    return _glGetTextureParameterIuivEXT;
}

template <>
inline const GlMultiTexParameterIivEXT&
GpuContextOgl::getFunction<GlMultiTexParameterIivEXT>() const {
    return _glMultiTexParameterIivEXT;
}

template <>
inline const GlMultiTexParameterIuivEXT&
GpuContextOgl::getFunction<GlMultiTexParameterIuivEXT>() const {
    return _glMultiTexParameterIuivEXT;
}

template <>
inline const GlGetMultiTexParameterIivEXT&
GpuContextOgl::getFunction<GlGetMultiTexParameterIivEXT>() const {
    return _glGetMultiTexParameterIivEXT;
}

template <>
inline const GlGetMultiTexParameterIuivEXT&
GpuContextOgl::getFunction<GlGetMultiTexParameterIuivEXT>() const {
    return _glGetMultiTexParameterIuivEXT;
}

template <>
inline const GlProgramUniform1uiEXT&
GpuContextOgl::getFunction<GlProgramUniform1uiEXT>() const {
    return _glProgramUniform1uiEXT;
}

template <>
inline const GlProgramUniform2uiEXT&
GpuContextOgl::getFunction<GlProgramUniform2uiEXT>() const {
    return _glProgramUniform2uiEXT;
}

template <>
inline const GlProgramUniform3uiEXT&
GpuContextOgl::getFunction<GlProgramUniform3uiEXT>() const {
    return _glProgramUniform3uiEXT;
}

template <>
inline const GlProgramUniform4uiEXT&
GpuContextOgl::getFunction<GlProgramUniform4uiEXT>() const {
    return _glProgramUniform4uiEXT;
}

template <>
inline const GlProgramUniform1uivEXT&
GpuContextOgl::getFunction<GlProgramUniform1uivEXT>() const {
    return _glProgramUniform1uivEXT;
}

template <>
inline const GlProgramUniform2uivEXT&
GpuContextOgl::getFunction<GlProgramUniform2uivEXT>() const {
    return _glProgramUniform2uivEXT;
}

template <>
inline const GlProgramUniform3uivEXT&
GpuContextOgl::getFunction<GlProgramUniform3uivEXT>() const {
    return _glProgramUniform3uivEXT;
}

template <>
inline const GlProgramUniform4uivEXT&
GpuContextOgl::getFunction<GlProgramUniform4uivEXT>() const {
    return _glProgramUniform4uivEXT;
}

template <>
inline const GlNamedProgramLocalParameters4fvEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameters4fvEXT>() const {
    return _glNamedProgramLocalParameters4fvEXT;
}

template <>
inline const GlNamedProgramLocalParameterI4iEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameterI4iEXT>() const {
    return _glNamedProgramLocalParameterI4iEXT;
}

template <>
inline const GlNamedProgramLocalParameterI4ivEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameterI4ivEXT>() const {
    return _glNamedProgramLocalParameterI4ivEXT;
}

template <>
inline const GlNamedProgramLocalParametersI4ivEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParametersI4ivEXT>() const {
    return _glNamedProgramLocalParametersI4ivEXT;
}

template <>
inline const GlNamedProgramLocalParameterI4uiEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameterI4uiEXT>() const {
    return _glNamedProgramLocalParameterI4uiEXT;
}

template <>
inline const GlNamedProgramLocalParameterI4uivEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameterI4uivEXT>() const {
    return _glNamedProgramLocalParameterI4uivEXT;
}

template <>
inline const GlNamedProgramLocalParametersI4uivEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParametersI4uivEXT>() const {
    return _glNamedProgramLocalParametersI4uivEXT;
}

template <>
inline const GlGetNamedProgramLocalParameterIivEXT&
GpuContextOgl::getFunction<GlGetNamedProgramLocalParameterIivEXT>() const {
    return _glGetNamedProgramLocalParameterIivEXT;
}

template <>
inline const GlGetNamedProgramLocalParameterIuivEXT&
GpuContextOgl::getFunction<GlGetNamedProgramLocalParameterIuivEXT>() const {
    return _glGetNamedProgramLocalParameterIuivEXT;
}

template <>
inline const GlEnableClientStateiEXT&
GpuContextOgl::getFunction<GlEnableClientStateiEXT>() const {
    return _glEnableClientStateiEXT;
}

template <>
inline const GlDisableClientStateiEXT&
GpuContextOgl::getFunction<GlDisableClientStateiEXT>() const {
    return _glDisableClientStateiEXT;
}

template <>
inline const GlGetFloati_vEXT&
GpuContextOgl::getFunction<GlGetFloati_vEXT>() const {
    return _glGetFloati_vEXT;
}

template <>
inline const GlGetDoublei_vEXT&
GpuContextOgl::getFunction<GlGetDoublei_vEXT>() const {
    return _glGetDoublei_vEXT;
}

template <>
inline const GlGetPointeri_vEXT&
GpuContextOgl::getFunction<GlGetPointeri_vEXT>() const {
    return _glGetPointeri_vEXT;
}

template <>
inline const GlNamedProgramStringEXT&
GpuContextOgl::getFunction<GlNamedProgramStringEXT>() const {
    return _glNamedProgramStringEXT;
}

template <>
inline const GlNamedProgramLocalParameter4dEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameter4dEXT>() const {
    return _glNamedProgramLocalParameter4dEXT;
}

template <>
inline const GlNamedProgramLocalParameter4dvEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameter4dvEXT>() const {
    return _glNamedProgramLocalParameter4dvEXT;
}

template <>
inline const GlNamedProgramLocalParameter4fEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameter4fEXT>() const {
    return _glNamedProgramLocalParameter4fEXT;
}

template <>
inline const GlNamedProgramLocalParameter4fvEXT&
GpuContextOgl::getFunction<GlNamedProgramLocalParameter4fvEXT>() const {
    return _glNamedProgramLocalParameter4fvEXT;
}

template <>
inline const GlGetNamedProgramLocalParameterdvEXT&
GpuContextOgl::getFunction<GlGetNamedProgramLocalParameterdvEXT>() const {
    return _glGetNamedProgramLocalParameterdvEXT;
}

template <>
inline const GlGetNamedProgramLocalParameterfvEXT&
GpuContextOgl::getFunction<GlGetNamedProgramLocalParameterfvEXT>() const {
    return _glGetNamedProgramLocalParameterfvEXT;
}

template <>
inline const GlGetNamedProgramivEXT&
GpuContextOgl::getFunction<GlGetNamedProgramivEXT>() const {
    return _glGetNamedProgramivEXT;
}

template <>
inline const GlGetNamedProgramStringEXT&
GpuContextOgl::getFunction<GlGetNamedProgramStringEXT>() const {
    return _glGetNamedProgramStringEXT;
}

template <>
inline const GlNamedRenderbufferStorageEXT&
GpuContextOgl::getFunction<GlNamedRenderbufferStorageEXT>() const {
    return _glNamedRenderbufferStorageEXT;
}

template <>
inline const GlGetNamedRenderbufferParameterivEXT&
GpuContextOgl::getFunction<GlGetNamedRenderbufferParameterivEXT>() const {
    return _glGetNamedRenderbufferParameterivEXT;
}

template <>
inline const GlNamedRenderbufferStorageMultisampleEXT&
GpuContextOgl::getFunction<GlNamedRenderbufferStorageMultisampleEXT>() const {
    return _glNamedRenderbufferStorageMultisampleEXT;
}

template <>
inline const GlNamedRenderbufferStorageMultisampleCoverageEXT&
GpuContextOgl::getFunction<GlNamedRenderbufferStorageMultisampleCoverageEXT>() const {
    return _glNamedRenderbufferStorageMultisampleCoverageEXT;
}

template <>
inline const GlCheckNamedFramebufferStatusEXT&
GpuContextOgl::getFunction<GlCheckNamedFramebufferStatusEXT>() const {
    return _glCheckNamedFramebufferStatusEXT;
}

template <>
inline const GlNamedFramebufferTexture1DEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTexture1DEXT>() const {
    return _glNamedFramebufferTexture1DEXT;
}

template <>
inline const GlNamedFramebufferTexture2DEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTexture2DEXT>() const {
    return _glNamedFramebufferTexture2DEXT;
}

template <>
inline const GlNamedFramebufferTexture3DEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTexture3DEXT>() const {
    return _glNamedFramebufferTexture3DEXT;
}

template <>
inline const GlNamedFramebufferRenderbufferEXT&
GpuContextOgl::getFunction<GlNamedFramebufferRenderbufferEXT>() const {
    return _glNamedFramebufferRenderbufferEXT;
}

template <>
inline const GlGetNamedFramebufferAttachmentParameterivEXT&
GpuContextOgl::getFunction<GlGetNamedFramebufferAttachmentParameterivEXT>() const {
    return _glGetNamedFramebufferAttachmentParameterivEXT;
}

template <>
inline const GlGenerateTextureMipmapEXT&
GpuContextOgl::getFunction<GlGenerateTextureMipmapEXT>() const {
    return _glGenerateTextureMipmapEXT;
}

template <>
inline const GlGenerateMultiTexMipmapEXT&
GpuContextOgl::getFunction<GlGenerateMultiTexMipmapEXT>() const {
    return _glGenerateMultiTexMipmapEXT;
}

template <>
inline const GlFramebufferDrawBufferEXT&
GpuContextOgl::getFunction<GlFramebufferDrawBufferEXT>() const {
    return _glFramebufferDrawBufferEXT;
}

template <>
inline const GlFramebufferDrawBuffersEXT&
GpuContextOgl::getFunction<GlFramebufferDrawBuffersEXT>() const {
    return _glFramebufferDrawBuffersEXT;
}

template <>
inline const GlFramebufferReadBufferEXT&
GpuContextOgl::getFunction<GlFramebufferReadBufferEXT>() const {
    return _glFramebufferReadBufferEXT;
}

template <>
inline const GlGetFramebufferParameterivEXT&
GpuContextOgl::getFunction<GlGetFramebufferParameterivEXT>() const {
    return _glGetFramebufferParameterivEXT;
}

template <>
inline const GlNamedCopyBufferSubDataEXT&
GpuContextOgl::getFunction<GlNamedCopyBufferSubDataEXT>() const {
    return _glNamedCopyBufferSubDataEXT;
}

template <>
inline const GlNamedFramebufferTextureEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTextureEXT>() const {
    return _glNamedFramebufferTextureEXT;
}

template <>
inline const GlNamedFramebufferTextureLayerEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTextureLayerEXT>() const {
    return _glNamedFramebufferTextureLayerEXT;
}

template <>
inline const GlNamedFramebufferTextureFaceEXT&
GpuContextOgl::getFunction<GlNamedFramebufferTextureFaceEXT>() const {
    return _glNamedFramebufferTextureFaceEXT;
}

template <>
inline const GlTextureRenderbufferEXT&
GpuContextOgl::getFunction<GlTextureRenderbufferEXT>() const {
    return _glTextureRenderbufferEXT;
}

template <>
inline const GlMultiTexRenderbufferEXT&
GpuContextOgl::getFunction<GlMultiTexRenderbufferEXT>() const {
    return _glMultiTexRenderbufferEXT;
}

template <>
inline const GlVertexArrayVertexOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexOffsetEXT>() const {
    return _glVertexArrayVertexOffsetEXT;
}

template <>
inline const GlVertexArrayColorOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayColorOffsetEXT>() const {
    return _glVertexArrayColorOffsetEXT;
}

template <>
inline const GlVertexArrayEdgeFlagOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayEdgeFlagOffsetEXT>() const {
    return _glVertexArrayEdgeFlagOffsetEXT;
}

template <>
inline const GlVertexArrayIndexOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayIndexOffsetEXT>() const {
    return _glVertexArrayIndexOffsetEXT;
}

template <>
inline const GlVertexArrayNormalOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayNormalOffsetEXT>() const {
    return _glVertexArrayNormalOffsetEXT;
}

template <>
inline const GlVertexArrayTexCoordOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayTexCoordOffsetEXT>() const {
    return _glVertexArrayTexCoordOffsetEXT;
}

template <>
inline const GlVertexArrayMultiTexCoordOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayMultiTexCoordOffsetEXT>() const {
    return _glVertexArrayMultiTexCoordOffsetEXT;
}

template <>
inline const GlVertexArrayFogCoordOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayFogCoordOffsetEXT>() const {
    return _glVertexArrayFogCoordOffsetEXT;
}

template <>
inline const GlVertexArraySecondaryColorOffsetEXT&
GpuContextOgl::getFunction<GlVertexArraySecondaryColorOffsetEXT>() const {
    return _glVertexArraySecondaryColorOffsetEXT;
}

template <>
inline const GlVertexArrayVertexAttribOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribOffsetEXT>() const {
    return _glVertexArrayVertexAttribOffsetEXT;
}

template <>
inline const GlVertexArrayVertexAttribIOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribIOffsetEXT>() const {
    return _glVertexArrayVertexAttribIOffsetEXT;
}

template <>
inline const GlEnableVertexArrayEXT&
GpuContextOgl::getFunction<GlEnableVertexArrayEXT>() const {
    return _glEnableVertexArrayEXT;
}

template <>
inline const GlDisableVertexArrayEXT&
GpuContextOgl::getFunction<GlDisableVertexArrayEXT>() const {
    return _glDisableVertexArrayEXT;
}

template <>
inline const GlEnableVertexArrayAttribEXT&
GpuContextOgl::getFunction<GlEnableVertexArrayAttribEXT>() const {
    return _glEnableVertexArrayAttribEXT;
}

template <>
inline const GlDisableVertexArrayAttribEXT&
GpuContextOgl::getFunction<GlDisableVertexArrayAttribEXT>() const {
    return _glDisableVertexArrayAttribEXT;
}

template <>
inline const GlGetVertexArrayIntegervEXT&
GpuContextOgl::getFunction<GlGetVertexArrayIntegervEXT>() const {
    return _glGetVertexArrayIntegervEXT;
}

template <>
inline const GlGetVertexArrayPointervEXT&
GpuContextOgl::getFunction<GlGetVertexArrayPointervEXT>() const {
    return _glGetVertexArrayPointervEXT;
}

template <>
inline const GlGetVertexArrayIntegeri_vEXT&
GpuContextOgl::getFunction<GlGetVertexArrayIntegeri_vEXT>() const {
    return _glGetVertexArrayIntegeri_vEXT;
}

template <>
inline const GlGetVertexArrayPointeri_vEXT&
GpuContextOgl::getFunction<GlGetVertexArrayPointeri_vEXT>() const {
    return _glGetVertexArrayPointeri_vEXT;
}

template <>
inline const GlMapNamedBufferRangeEXT&
GpuContextOgl::getFunction<GlMapNamedBufferRangeEXT>() const {
    return _glMapNamedBufferRangeEXT;
}

template <>
inline const GlFlushMappedNamedBufferRangeEXT&
GpuContextOgl::getFunction<GlFlushMappedNamedBufferRangeEXT>() const {
    return _glFlushMappedNamedBufferRangeEXT;
}

template <>
inline const GlNamedBufferStorageEXT&
GpuContextOgl::getFunction<GlNamedBufferStorageEXT>() const {
    return _glNamedBufferStorageEXT;
}

template <>
inline const GlClearNamedBufferDataEXT&
GpuContextOgl::getFunction<GlClearNamedBufferDataEXT>() const {
    return _glClearNamedBufferDataEXT;
}

template <>
inline const GlClearNamedBufferSubDataEXT&
GpuContextOgl::getFunction<GlClearNamedBufferSubDataEXT>() const {
    return _glClearNamedBufferSubDataEXT;
}

template <>
inline const GlNamedFramebufferParameteriEXT&
GpuContextOgl::getFunction<GlNamedFramebufferParameteriEXT>() const {
    return _glNamedFramebufferParameteriEXT;
}

template <>
inline const GlGetNamedFramebufferParameterivEXT&
GpuContextOgl::getFunction<GlGetNamedFramebufferParameterivEXT>() const {
    return _glGetNamedFramebufferParameterivEXT;
}

template <>
inline const GlProgramUniform1dEXT&
GpuContextOgl::getFunction<GlProgramUniform1dEXT>() const {
    return _glProgramUniform1dEXT;
}

template <>
inline const GlProgramUniform2dEXT&
GpuContextOgl::getFunction<GlProgramUniform2dEXT>() const {
    return _glProgramUniform2dEXT;
}

template <>
inline const GlProgramUniform3dEXT&
GpuContextOgl::getFunction<GlProgramUniform3dEXT>() const {
    return _glProgramUniform3dEXT;
}

template <>
inline const GlProgramUniform4dEXT&
GpuContextOgl::getFunction<GlProgramUniform4dEXT>() const {
    return _glProgramUniform4dEXT;
}

template <>
inline const GlProgramUniform1dvEXT&
GpuContextOgl::getFunction<GlProgramUniform1dvEXT>() const {
    return _glProgramUniform1dvEXT;
}

template <>
inline const GlProgramUniform2dvEXT&
GpuContextOgl::getFunction<GlProgramUniform2dvEXT>() const {
    return _glProgramUniform2dvEXT;
}

template <>
inline const GlProgramUniform3dvEXT&
GpuContextOgl::getFunction<GlProgramUniform3dvEXT>() const {
    return _glProgramUniform3dvEXT;
}

template <>
inline const GlProgramUniform4dvEXT&
GpuContextOgl::getFunction<GlProgramUniform4dvEXT>() const {
    return _glProgramUniform4dvEXT;
}

template <>
inline const GlProgramUniformMatrix2dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2dvEXT>() const {
    return _glProgramUniformMatrix2dvEXT;
}

template <>
inline const GlProgramUniformMatrix3dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3dvEXT>() const {
    return _glProgramUniformMatrix3dvEXT;
}

template <>
inline const GlProgramUniformMatrix4dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4dvEXT>() const {
    return _glProgramUniformMatrix4dvEXT;
}

template <>
inline const GlProgramUniformMatrix2x3dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x3dvEXT>() const {
    return _glProgramUniformMatrix2x3dvEXT;
}

template <>
inline const GlProgramUniformMatrix2x4dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix2x4dvEXT>() const {
    return _glProgramUniformMatrix2x4dvEXT;
}

template <>
inline const GlProgramUniformMatrix3x2dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x2dvEXT>() const {
    return _glProgramUniformMatrix3x2dvEXT;
}

template <>
inline const GlProgramUniformMatrix3x4dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix3x4dvEXT>() const {
    return _glProgramUniformMatrix3x4dvEXT;
}

template <>
inline const GlProgramUniformMatrix4x2dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x2dvEXT>() const {
    return _glProgramUniformMatrix4x2dvEXT;
}

template <>
inline const GlProgramUniformMatrix4x3dvEXT&
GpuContextOgl::getFunction<GlProgramUniformMatrix4x3dvEXT>() const {
    return _glProgramUniformMatrix4x3dvEXT;
}

template <>
inline const GlTextureBufferRangeEXT&
GpuContextOgl::getFunction<GlTextureBufferRangeEXT>() const {
    return _glTextureBufferRangeEXT;
}

template <>
inline const GlTextureStorage1DEXT&
GpuContextOgl::getFunction<GlTextureStorage1DEXT>() const {
    return _glTextureStorage1DEXT;
}

template <>
inline const GlTextureStorage2DEXT&
GpuContextOgl::getFunction<GlTextureStorage2DEXT>() const {
    return _glTextureStorage2DEXT;
}

template <>
inline const GlTextureStorage3DEXT&
GpuContextOgl::getFunction<GlTextureStorage3DEXT>() const {
    return _glTextureStorage3DEXT;
}

template <>
inline const GlTextureStorage2DMultisampleEXT&
GpuContextOgl::getFunction<GlTextureStorage2DMultisampleEXT>() const {
    return _glTextureStorage2DMultisampleEXT;
}

template <>
inline const GlTextureStorage3DMultisampleEXT&
GpuContextOgl::getFunction<GlTextureStorage3DMultisampleEXT>() const {
    return _glTextureStorage3DMultisampleEXT;
}

template <>
inline const GlVertexArrayBindVertexBufferEXT&
GpuContextOgl::getFunction<GlVertexArrayBindVertexBufferEXT>() const {
    return _glVertexArrayBindVertexBufferEXT;
}

template <>
inline const GlVertexArrayVertexAttribFormatEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribFormatEXT>() const {
    return _glVertexArrayVertexAttribFormatEXT;
}

template <>
inline const GlVertexArrayVertexAttribIFormatEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribIFormatEXT>() const {
    return _glVertexArrayVertexAttribIFormatEXT;
}

template <>
inline const GlVertexArrayVertexAttribLFormatEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribLFormatEXT>() const {
    return _glVertexArrayVertexAttribLFormatEXT;
}

template <>
inline const GlVertexArrayVertexAttribBindingEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribBindingEXT>() const {
    return _glVertexArrayVertexAttribBindingEXT;
}

template <>
inline const GlVertexArrayVertexBindingDivisorEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexBindingDivisorEXT>() const {
    return _glVertexArrayVertexBindingDivisorEXT;
}

template <>
inline const GlVertexArrayVertexAttribLOffsetEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribLOffsetEXT>() const {
    return _glVertexArrayVertexAttribLOffsetEXT;
}

template <>
inline const GlTexturePageCommitmentEXT&
GpuContextOgl::getFunction<GlTexturePageCommitmentEXT>() const {
    return _glTexturePageCommitmentEXT;
}

template <>
inline const GlVertexArrayVertexAttribDivisorEXT&
GpuContextOgl::getFunction<GlVertexArrayVertexAttribDivisorEXT>() const {
    return _glVertexArrayVertexAttribDivisorEXT;
}

template <>
inline const GlDrawArraysInstancedEXT&
GpuContextOgl::getFunction<GlDrawArraysInstancedEXT>() const {
    return _glDrawArraysInstancedEXT;
}

template <>
inline const GlDrawElementsInstancedEXT&
GpuContextOgl::getFunction<GlDrawElementsInstancedEXT>() const {
    return _glDrawElementsInstancedEXT;
}

template <>
inline const GlPolygonOffsetClampEXT&
GpuContextOgl::getFunction<GlPolygonOffsetClampEXT>() const {
    return _glPolygonOffsetClampEXT;
}

template <>
inline const GlRasterSamplesEXT&
GpuContextOgl::getFunction<GlRasterSamplesEXT>() const {
    return _glRasterSamplesEXT;
}

template <>
inline const GlUseShaderProgramEXT&
GpuContextOgl::getFunction<GlUseShaderProgramEXT>() const {
    return _glUseShaderProgramEXT;
}

template <>
inline const GlActiveProgramEXT&
GpuContextOgl::getFunction<GlActiveProgramEXT>() const {
    return _glActiveProgramEXT;
}

template <>
inline const GlCreateShaderProgramEXT&
GpuContextOgl::getFunction<GlCreateShaderProgramEXT>() const {
    return _glCreateShaderProgramEXT;
}

template <>
inline const GlFramebufferFetchBarrierEXT&
GpuContextOgl::getFunction<GlFramebufferFetchBarrierEXT>() const {
    return _glFramebufferFetchBarrierEXT;
}

template <>
inline const GlWindowRectanglesEXT&
GpuContextOgl::getFunction<GlWindowRectanglesEXT>() const {
    return _glWindowRectanglesEXT;
}

template <>
inline const GlApplyFramebufferAttachmentCMAAINTEL&
GpuContextOgl::getFunction<GlApplyFramebufferAttachmentCMAAINTEL>() const {
    return _glApplyFramebufferAttachmentCMAAINTEL;
}

template <>
inline const GlBeginPerfQueryINTEL&
GpuContextOgl::getFunction<GlBeginPerfQueryINTEL>() const {
    return _glBeginPerfQueryINTEL;
}

template <>
inline const GlCreatePerfQueryINTEL&
GpuContextOgl::getFunction<GlCreatePerfQueryINTEL>() const {
    return _glCreatePerfQueryINTEL;
}

template <>
inline const GlDeletePerfQueryINTEL&
GpuContextOgl::getFunction<GlDeletePerfQueryINTEL>() const {
    return _glDeletePerfQueryINTEL;
}

template <>
inline const GlEndPerfQueryINTEL&
GpuContextOgl::getFunction<GlEndPerfQueryINTEL>() const {
    return _glEndPerfQueryINTEL;
}

template <>
inline const GlGetFirstPerfQueryIdINTEL&
GpuContextOgl::getFunction<GlGetFirstPerfQueryIdINTEL>() const {
    return _glGetFirstPerfQueryIdINTEL;
}

template <>
inline const GlGetNextPerfQueryIdINTEL&
GpuContextOgl::getFunction<GlGetNextPerfQueryIdINTEL>() const {
    return _glGetNextPerfQueryIdINTEL;
}

template <>
inline const GlGetPerfCounterInfoINTEL&
GpuContextOgl::getFunction<GlGetPerfCounterInfoINTEL>() const {
    return _glGetPerfCounterInfoINTEL;
}

template <>
inline const GlGetPerfQueryDataINTEL&
GpuContextOgl::getFunction<GlGetPerfQueryDataINTEL>() const {
    return _glGetPerfQueryDataINTEL;
}

template <>
inline const GlGetPerfQueryIdByNameINTEL&
GpuContextOgl::getFunction<GlGetPerfQueryIdByNameINTEL>() const {
    return _glGetPerfQueryIdByNameINTEL;
}

template <>
inline const GlGetPerfQueryInfoINTEL&
GpuContextOgl::getFunction<GlGetPerfQueryInfoINTEL>() const {
    return _glGetPerfQueryInfoINTEL;
}

template <>
inline const GlMultiDrawArraysIndirectBindlessNV&
GpuContextOgl::getFunction<GlMultiDrawArraysIndirectBindlessNV>() const {
    return _glMultiDrawArraysIndirectBindlessNV;
}

template <>
inline const GlMultiDrawElementsIndirectBindlessNV&
GpuContextOgl::getFunction<GlMultiDrawElementsIndirectBindlessNV>() const {
    return _glMultiDrawElementsIndirectBindlessNV;
}

template <>
inline const GlMultiDrawArraysIndirectBindlessCountNV&
GpuContextOgl::getFunction<GlMultiDrawArraysIndirectBindlessCountNV>() const {
    return _glMultiDrawArraysIndirectBindlessCountNV;
}

template <>
inline const GlMultiDrawElementsIndirectBindlessCountNV&
GpuContextOgl::getFunction<GlMultiDrawElementsIndirectBindlessCountNV>() const {
    return _glMultiDrawElementsIndirectBindlessCountNV;
}

template <>
inline const GlGetTextureHandleNV&
GpuContextOgl::getFunction<GlGetTextureHandleNV>() const {
    return _glGetTextureHandleNV;
}

template <>
inline const GlGetTextureSamplerHandleNV&
GpuContextOgl::getFunction<GlGetTextureSamplerHandleNV>() const {
    return _glGetTextureSamplerHandleNV;
}

template <>
inline const GlMakeTextureHandleResidentNV&
GpuContextOgl::getFunction<GlMakeTextureHandleResidentNV>() const {
    return _glMakeTextureHandleResidentNV;
}

template <>
inline const GlMakeTextureHandleNonResidentNV&
GpuContextOgl::getFunction<GlMakeTextureHandleNonResidentNV>() const {
    return _glMakeTextureHandleNonResidentNV;
}

template <>
inline const GlGetImageHandleNV&
GpuContextOgl::getFunction<GlGetImageHandleNV>() const {
    return _glGetImageHandleNV;
}

template <>
inline const GlMakeImageHandleResidentNV&
GpuContextOgl::getFunction<GlMakeImageHandleResidentNV>() const {
    return _glMakeImageHandleResidentNV;
}

template <>
inline const GlMakeImageHandleNonResidentNV&
GpuContextOgl::getFunction<GlMakeImageHandleNonResidentNV>() const {
    return _glMakeImageHandleNonResidentNV;
}

template <>
inline const GlUniformHandleui64NV&
GpuContextOgl::getFunction<GlUniformHandleui64NV>() const {
    return _glUniformHandleui64NV;
}

template <>
inline const GlUniformHandleui64vNV&
GpuContextOgl::getFunction<GlUniformHandleui64vNV>() const {
    return _glUniformHandleui64vNV;
}

template <>
inline const GlProgramUniformHandleui64NV&
GpuContextOgl::getFunction<GlProgramUniformHandleui64NV>() const {
    return _glProgramUniformHandleui64NV;
}

template <>
inline const GlProgramUniformHandleui64vNV&
GpuContextOgl::getFunction<GlProgramUniformHandleui64vNV>() const {
    return _glProgramUniformHandleui64vNV;
}

template <>
inline const GlIsTextureHandleResidentNV&
GpuContextOgl::getFunction<GlIsTextureHandleResidentNV>() const {
    return _glIsTextureHandleResidentNV;
}

template <>
inline const GlIsImageHandleResidentNV&
GpuContextOgl::getFunction<GlIsImageHandleResidentNV>() const {
    return _glIsImageHandleResidentNV;
}

template <>
inline const GlBlendParameteriNV&
GpuContextOgl::getFunction<GlBlendParameteriNV>() const {
    return _glBlendParameteriNV;
}

template <>
inline const GlBlendBarrierNV&
GpuContextOgl::getFunction<GlBlendBarrierNV>() const {
    return _glBlendBarrierNV;
}

template <>
inline const GlViewportPositionWScaleNV&
GpuContextOgl::getFunction<GlViewportPositionWScaleNV>() const {
    return _glViewportPositionWScaleNV;
}

template <>
inline const GlCreateStatesNV&
GpuContextOgl::getFunction<GlCreateStatesNV>() const {
    return _glCreateStatesNV;
}

template <>
inline const GlDeleteStatesNV&
GpuContextOgl::getFunction<GlDeleteStatesNV>() const {
    return _glDeleteStatesNV;
}

template <>
inline const GlIsStateNV&
GpuContextOgl::getFunction<GlIsStateNV>() const {
    return _glIsStateNV;
}

template <>
inline const GlStateCaptureNV&
GpuContextOgl::getFunction<GlStateCaptureNV>() const {
    return _glStateCaptureNV;
}

template <>
inline const GlGetCommandHeaderNV&
GpuContextOgl::getFunction<GlGetCommandHeaderNV>() const {
    return _glGetCommandHeaderNV;
}

template <>
inline const GlGetStageIndexNV&
GpuContextOgl::getFunction<GlGetStageIndexNV>() const {
    return _glGetStageIndexNV;
}

template <>
inline const GlDrawCommandsNV&
GpuContextOgl::getFunction<GlDrawCommandsNV>() const {
    return _glDrawCommandsNV;
}

template <>
inline const GlDrawCommandsAddressNV&
GpuContextOgl::getFunction<GlDrawCommandsAddressNV>() const {
    return _glDrawCommandsAddressNV;
}

template <>
inline const GlDrawCommandsStatesNV&
GpuContextOgl::getFunction<GlDrawCommandsStatesNV>() const {
    return _glDrawCommandsStatesNV;
}

template <>
inline const GlDrawCommandsStatesAddressNV&
GpuContextOgl::getFunction<GlDrawCommandsStatesAddressNV>() const {
    return _glDrawCommandsStatesAddressNV;
}

template <>
inline const GlCreateCommandListsNV&
GpuContextOgl::getFunction<GlCreateCommandListsNV>() const {
    return _glCreateCommandListsNV;
}

template <>
inline const GlDeleteCommandListsNV&
GpuContextOgl::getFunction<GlDeleteCommandListsNV>() const {
    return _glDeleteCommandListsNV;
}

template <>
inline const GlIsCommandListNV&
GpuContextOgl::getFunction<GlIsCommandListNV>() const {
    return _glIsCommandListNV;
}

template <>
inline const GlListDrawCommandsStatesClientNV&
GpuContextOgl::getFunction<GlListDrawCommandsStatesClientNV>() const {
    return _glListDrawCommandsStatesClientNV;
}

template <>
inline const GlCommandListSegmentsNV&
GpuContextOgl::getFunction<GlCommandListSegmentsNV>() const {
    return _glCommandListSegmentsNV;
}

template <>
inline const GlCompileCommandListNV&
GpuContextOgl::getFunction<GlCompileCommandListNV>() const {
    return _glCompileCommandListNV;
}

template <>
inline const GlCallCommandListNV&
GpuContextOgl::getFunction<GlCallCommandListNV>() const {
    return _glCallCommandListNV;
}

template <>
inline const GlBeginConditionalRenderNV&
GpuContextOgl::getFunction<GlBeginConditionalRenderNV>() const {
    return _glBeginConditionalRenderNV;
}

template <>
inline const GlEndConditionalRenderNV&
GpuContextOgl::getFunction<GlEndConditionalRenderNV>() const {
    return _glEndConditionalRenderNV;
}

template <>
inline const GlSubpixelPrecisionBiasNV&
GpuContextOgl::getFunction<GlSubpixelPrecisionBiasNV>() const {
    return _glSubpixelPrecisionBiasNV;
}

template <>
inline const GlConservativeRasterParameterfNV&
GpuContextOgl::getFunction<GlConservativeRasterParameterfNV>() const {
    return _glConservativeRasterParameterfNV;
}

template <>
inline const GlConservativeRasterParameteriNV&
GpuContextOgl::getFunction<GlConservativeRasterParameteriNV>() const {
    return _glConservativeRasterParameteriNV;
}

template <>
inline const GlDrawVkImageNV&
GpuContextOgl::getFunction<GlDrawVkImageNV>() const {
    return _glDrawVkImageNV;
}

template <>
inline const GlGetVkProcAddrNV&
GpuContextOgl::getFunction<GlGetVkProcAddrNV>() const {
    return _glGetVkProcAddrNV;
}

template <>
inline const GlWaitVkSemaphoreNV&
GpuContextOgl::getFunction<GlWaitVkSemaphoreNV>() const {
    return _glWaitVkSemaphoreNV;
}

template <>
inline const GlSignalVkSemaphoreNV&
GpuContextOgl::getFunction<GlSignalVkSemaphoreNV>() const {
    return _glSignalVkSemaphoreNV;
}

template <>
inline const GlSignalVkFenceNV&
GpuContextOgl::getFunction<GlSignalVkFenceNV>() const {
    return _glSignalVkFenceNV;
}

template <>
inline const GlFragmentCoverageColorNV&
GpuContextOgl::getFunction<GlFragmentCoverageColorNV>() const {
    return _glFragmentCoverageColorNV;
}

template <>
inline const GlCoverageModulationTableNV&
GpuContextOgl::getFunction<GlCoverageModulationTableNV>() const {
    return _glCoverageModulationTableNV;
}

template <>
inline const GlGetCoverageModulationTableNV&
GpuContextOgl::getFunction<GlGetCoverageModulationTableNV>() const {
    return _glGetCoverageModulationTableNV;
}

template <>
inline const GlCoverageModulationNV&
GpuContextOgl::getFunction<GlCoverageModulationNV>() const {
    return _glCoverageModulationNV;
}

template <>
inline const GlRenderbufferStorageMultisampleCoverageNV&
GpuContextOgl::getFunction<GlRenderbufferStorageMultisampleCoverageNV>() const {
    return _glRenderbufferStorageMultisampleCoverageNV;
}

template <>
inline const GlUniform1i64NV&
GpuContextOgl::getFunction<GlUniform1i64NV>() const {
    return _glUniform1i64NV;
}

template <>
inline const GlUniform2i64NV&
GpuContextOgl::getFunction<GlUniform2i64NV>() const {
    return _glUniform2i64NV;
}

template <>
inline const GlUniform3i64NV&
GpuContextOgl::getFunction<GlUniform3i64NV>() const {
    return _glUniform3i64NV;
}

template <>
inline const GlUniform4i64NV&
GpuContextOgl::getFunction<GlUniform4i64NV>() const {
    return _glUniform4i64NV;
}

template <>
inline const GlUniform1i64vNV&
GpuContextOgl::getFunction<GlUniform1i64vNV>() const {
    return _glUniform1i64vNV;
}

template <>
inline const GlUniform2i64vNV&
GpuContextOgl::getFunction<GlUniform2i64vNV>() const {
    return _glUniform2i64vNV;
}

template <>
inline const GlUniform3i64vNV&
GpuContextOgl::getFunction<GlUniform3i64vNV>() const {
    return _glUniform3i64vNV;
}

template <>
inline const GlUniform4i64vNV&
GpuContextOgl::getFunction<GlUniform4i64vNV>() const {
    return _glUniform4i64vNV;
}

template <>
inline const GlUniform1ui64NV&
GpuContextOgl::getFunction<GlUniform1ui64NV>() const {
    return _glUniform1ui64NV;
}

template <>
inline const GlUniform2ui64NV&
GpuContextOgl::getFunction<GlUniform2ui64NV>() const {
    return _glUniform2ui64NV;
}

template <>
inline const GlUniform3ui64NV&
GpuContextOgl::getFunction<GlUniform3ui64NV>() const {
    return _glUniform3ui64NV;
}

template <>
inline const GlUniform4ui64NV&
GpuContextOgl::getFunction<GlUniform4ui64NV>() const {
    return _glUniform4ui64NV;
}

template <>
inline const GlUniform1ui64vNV&
GpuContextOgl::getFunction<GlUniform1ui64vNV>() const {
    return _glUniform1ui64vNV;
}

template <>
inline const GlUniform2ui64vNV&
GpuContextOgl::getFunction<GlUniform2ui64vNV>() const {
    return _glUniform2ui64vNV;
}

template <>
inline const GlUniform3ui64vNV&
GpuContextOgl::getFunction<GlUniform3ui64vNV>() const {
    return _glUniform3ui64vNV;
}

template <>
inline const GlUniform4ui64vNV&
GpuContextOgl::getFunction<GlUniform4ui64vNV>() const {
    return _glUniform4ui64vNV;
}

template <>
inline const GlGetUniformi64vNV&
GpuContextOgl::getFunction<GlGetUniformi64vNV>() const {
    return _glGetUniformi64vNV;
}

template <>
inline const GlProgramUniform1i64NV&
GpuContextOgl::getFunction<GlProgramUniform1i64NV>() const {
    return _glProgramUniform1i64NV;
}

template <>
inline const GlProgramUniform2i64NV&
GpuContextOgl::getFunction<GlProgramUniform2i64NV>() const {
    return _glProgramUniform2i64NV;
}

template <>
inline const GlProgramUniform3i64NV&
GpuContextOgl::getFunction<GlProgramUniform3i64NV>() const {
    return _glProgramUniform3i64NV;
}

template <>
inline const GlProgramUniform4i64NV&
GpuContextOgl::getFunction<GlProgramUniform4i64NV>() const {
    return _glProgramUniform4i64NV;
}

template <>
inline const GlProgramUniform1i64vNV&
GpuContextOgl::getFunction<GlProgramUniform1i64vNV>() const {
    return _glProgramUniform1i64vNV;
}

template <>
inline const GlProgramUniform2i64vNV&
GpuContextOgl::getFunction<GlProgramUniform2i64vNV>() const {
    return _glProgramUniform2i64vNV;
}

template <>
inline const GlProgramUniform3i64vNV&
GpuContextOgl::getFunction<GlProgramUniform3i64vNV>() const {
    return _glProgramUniform3i64vNV;
}

template <>
inline const GlProgramUniform4i64vNV&
GpuContextOgl::getFunction<GlProgramUniform4i64vNV>() const {
    return _glProgramUniform4i64vNV;
}

template <>
inline const GlProgramUniform1ui64NV&
GpuContextOgl::getFunction<GlProgramUniform1ui64NV>() const {
    return _glProgramUniform1ui64NV;
}

template <>
inline const GlProgramUniform2ui64NV&
GpuContextOgl::getFunction<GlProgramUniform2ui64NV>() const {
    return _glProgramUniform2ui64NV;
}

template <>
inline const GlProgramUniform3ui64NV&
GpuContextOgl::getFunction<GlProgramUniform3ui64NV>() const {
    return _glProgramUniform3ui64NV;
}

template <>
inline const GlProgramUniform4ui64NV&
GpuContextOgl::getFunction<GlProgramUniform4ui64NV>() const {
    return _glProgramUniform4ui64NV;
}

template <>
inline const GlProgramUniform1ui64vNV&
GpuContextOgl::getFunction<GlProgramUniform1ui64vNV>() const {
    return _glProgramUniform1ui64vNV;
}

template <>
inline const GlProgramUniform2ui64vNV&
GpuContextOgl::getFunction<GlProgramUniform2ui64vNV>() const {
    return _glProgramUniform2ui64vNV;
}

template <>
inline const GlProgramUniform3ui64vNV&
GpuContextOgl::getFunction<GlProgramUniform3ui64vNV>() const {
    return _glProgramUniform3ui64vNV;
}

template <>
inline const GlProgramUniform4ui64vNV&
GpuContextOgl::getFunction<GlProgramUniform4ui64vNV>() const {
    return _glProgramUniform4ui64vNV;
}

template <>
inline const GlGetInternalformatSampleivNV&
GpuContextOgl::getFunction<GlGetInternalformatSampleivNV>() const {
    return _glGetInternalformatSampleivNV;
}

template <>
inline const GlGenPathsNV&
GpuContextOgl::getFunction<GlGenPathsNV>() const {
    return _glGenPathsNV;
}

template <>
inline const GlDeletePathsNV&
GpuContextOgl::getFunction<GlDeletePathsNV>() const {
    return _glDeletePathsNV;
}

template <>
inline const GlIsPathNV&
GpuContextOgl::getFunction<GlIsPathNV>() const {
    return _glIsPathNV;
}

template <>
inline const GlPathCommandsNV&
GpuContextOgl::getFunction<GlPathCommandsNV>() const {
    return _glPathCommandsNV;
}

template <>
inline const GlPathCoordsNV&
GpuContextOgl::getFunction<GlPathCoordsNV>() const {
    return _glPathCoordsNV;
}

template <>
inline const GlPathSubCommandsNV&
GpuContextOgl::getFunction<GlPathSubCommandsNV>() const {
    return _glPathSubCommandsNV;
}

template <>
inline const GlPathSubCoordsNV&
GpuContextOgl::getFunction<GlPathSubCoordsNV>() const {
    return _glPathSubCoordsNV;
}

template <>
inline const GlPathStringNV&
GpuContextOgl::getFunction<GlPathStringNV>() const {
    return _glPathStringNV;
}

template <>
inline const GlPathGlyphsNV&
GpuContextOgl::getFunction<GlPathGlyphsNV>() const {
    return _glPathGlyphsNV;
}

template <>
inline const GlPathGlyphRangeNV&
GpuContextOgl::getFunction<GlPathGlyphRangeNV>() const {
    return _glPathGlyphRangeNV;
}

template <>
inline const GlWeightPathsNV&
GpuContextOgl::getFunction<GlWeightPathsNV>() const {
    return _glWeightPathsNV;
}

template <>
inline const GlCopyPathNV&
GpuContextOgl::getFunction<GlCopyPathNV>() const {
    return _glCopyPathNV;
}

template <>
inline const GlInterpolatePathsNV&
GpuContextOgl::getFunction<GlInterpolatePathsNV>() const {
    return _glInterpolatePathsNV;
}

template <>
inline const GlTransformPathNV&
GpuContextOgl::getFunction<GlTransformPathNV>() const {
    return _glTransformPathNV;
}

template <>
inline const GlPathParameterivNV&
GpuContextOgl::getFunction<GlPathParameterivNV>() const {
    return _glPathParameterivNV;
}

template <>
inline const GlPathParameteriNV&
GpuContextOgl::getFunction<GlPathParameteriNV>() const {
    return _glPathParameteriNV;
}

template <>
inline const GlPathParameterfvNV&
GpuContextOgl::getFunction<GlPathParameterfvNV>() const {
    return _glPathParameterfvNV;
}

template <>
inline const GlPathParameterfNV&
GpuContextOgl::getFunction<GlPathParameterfNV>() const {
    return _glPathParameterfNV;
}

template <>
inline const GlPathDashArrayNV&
GpuContextOgl::getFunction<GlPathDashArrayNV>() const {
    return _glPathDashArrayNV;
}

template <>
inline const GlPathStencilFuncNV&
GpuContextOgl::getFunction<GlPathStencilFuncNV>() const {
    return _glPathStencilFuncNV;
}

template <>
inline const GlPathStencilDepthOffsetNV&
GpuContextOgl::getFunction<GlPathStencilDepthOffsetNV>() const {
    return _glPathStencilDepthOffsetNV;
}

template <>
inline const GlStencilFillPathNV&
GpuContextOgl::getFunction<GlStencilFillPathNV>() const {
    return _glStencilFillPathNV;
}

template <>
inline const GlStencilStrokePathNV&
GpuContextOgl::getFunction<GlStencilStrokePathNV>() const {
    return _glStencilStrokePathNV;
}

template <>
inline const GlStencilFillPathInstancedNV&
GpuContextOgl::getFunction<GlStencilFillPathInstancedNV>() const {
    return _glStencilFillPathInstancedNV;
}

template <>
inline const GlStencilStrokePathInstancedNV&
GpuContextOgl::getFunction<GlStencilStrokePathInstancedNV>() const {
    return _glStencilStrokePathInstancedNV;
}

template <>
inline const GlPathCoverDepthFuncNV&
GpuContextOgl::getFunction<GlPathCoverDepthFuncNV>() const {
    return _glPathCoverDepthFuncNV;
}

template <>
inline const GlCoverFillPathNV&
GpuContextOgl::getFunction<GlCoverFillPathNV>() const {
    return _glCoverFillPathNV;
}

template <>
inline const GlCoverStrokePathNV&
GpuContextOgl::getFunction<GlCoverStrokePathNV>() const {
    return _glCoverStrokePathNV;
}

template <>
inline const GlCoverFillPathInstancedNV&
GpuContextOgl::getFunction<GlCoverFillPathInstancedNV>() const {
    return _glCoverFillPathInstancedNV;
}

template <>
inline const GlCoverStrokePathInstancedNV&
GpuContextOgl::getFunction<GlCoverStrokePathInstancedNV>() const {
    return _glCoverStrokePathInstancedNV;
}

template <>
inline const GlGetPathParameterivNV&
GpuContextOgl::getFunction<GlGetPathParameterivNV>() const {
    return _glGetPathParameterivNV;
}

template <>
inline const GlGetPathParameterfvNV&
GpuContextOgl::getFunction<GlGetPathParameterfvNV>() const {
    return _glGetPathParameterfvNV;
}

template <>
inline const GlGetPathCommandsNV&
GpuContextOgl::getFunction<GlGetPathCommandsNV>() const {
    return _glGetPathCommandsNV;
}

template <>
inline const GlGetPathCoordsNV&
GpuContextOgl::getFunction<GlGetPathCoordsNV>() const {
    return _glGetPathCoordsNV;
}

template <>
inline const GlGetPathDashArrayNV&
GpuContextOgl::getFunction<GlGetPathDashArrayNV>() const {
    return _glGetPathDashArrayNV;
}

template <>
inline const GlGetPathMetricsNV&
GpuContextOgl::getFunction<GlGetPathMetricsNV>() const {
    return _glGetPathMetricsNV;
}

template <>
inline const GlGetPathMetricRangeNV&
GpuContextOgl::getFunction<GlGetPathMetricRangeNV>() const {
    return _glGetPathMetricRangeNV;
}

template <>
inline const GlGetPathSpacingNV&
GpuContextOgl::getFunction<GlGetPathSpacingNV>() const {
    return _glGetPathSpacingNV;
}

template <>
inline const GlIsPointInFillPathNV&
GpuContextOgl::getFunction<GlIsPointInFillPathNV>() const {
    return _glIsPointInFillPathNV;
}

template <>
inline const GlIsPointInStrokePathNV&
GpuContextOgl::getFunction<GlIsPointInStrokePathNV>() const {
    return _glIsPointInStrokePathNV;
}

template <>
inline const GlGetPathLengthNV&
GpuContextOgl::getFunction<GlGetPathLengthNV>() const {
    return _glGetPathLengthNV;
}

template <>
inline const GlPointAlongPathNV&
GpuContextOgl::getFunction<GlPointAlongPathNV>() const {
    return _glPointAlongPathNV;
}

template <>
inline const GlMatrixLoad3x2fNV&
GpuContextOgl::getFunction<GlMatrixLoad3x2fNV>() const {
    return _glMatrixLoad3x2fNV;
}

template <>
inline const GlMatrixLoad3x3fNV&
GpuContextOgl::getFunction<GlMatrixLoad3x3fNV>() const {
    return _glMatrixLoad3x3fNV;
}

template <>
inline const GlMatrixLoadTranspose3x3fNV&
GpuContextOgl::getFunction<GlMatrixLoadTranspose3x3fNV>() const {
    return _glMatrixLoadTranspose3x3fNV;
}

template <>
inline const GlMatrixMult3x2fNV&
GpuContextOgl::getFunction<GlMatrixMult3x2fNV>() const {
    return _glMatrixMult3x2fNV;
}

template <>
inline const GlMatrixMult3x3fNV&
GpuContextOgl::getFunction<GlMatrixMult3x3fNV>() const {
    return _glMatrixMult3x3fNV;
}

template <>
inline const GlMatrixMultTranspose3x3fNV&
GpuContextOgl::getFunction<GlMatrixMultTranspose3x3fNV>() const {
    return _glMatrixMultTranspose3x3fNV;
}

template <>
inline const GlStencilThenCoverFillPathNV&
GpuContextOgl::getFunction<GlStencilThenCoverFillPathNV>() const {
    return _glStencilThenCoverFillPathNV;
}

template <>
inline const GlStencilThenCoverStrokePathNV&
GpuContextOgl::getFunction<GlStencilThenCoverStrokePathNV>() const {
    return _glStencilThenCoverStrokePathNV;
}

template <>
inline const GlStencilThenCoverFillPathInstancedNV&
GpuContextOgl::getFunction<GlStencilThenCoverFillPathInstancedNV>() const {
    return _glStencilThenCoverFillPathInstancedNV;
}

template <>
inline const GlStencilThenCoverStrokePathInstancedNV&
GpuContextOgl::getFunction<GlStencilThenCoverStrokePathInstancedNV>() const {
    return _glStencilThenCoverStrokePathInstancedNV;
}

template <>
inline const GlPathGlyphIndexRangeNV&
GpuContextOgl::getFunction<GlPathGlyphIndexRangeNV>() const {
    return _glPathGlyphIndexRangeNV;
}

template <>
inline const GlPathGlyphIndexArrayNV&
GpuContextOgl::getFunction<GlPathGlyphIndexArrayNV>() const {
    return _glPathGlyphIndexArrayNV;
}

template <>
inline const GlPathMemoryGlyphIndexArrayNV&
GpuContextOgl::getFunction<GlPathMemoryGlyphIndexArrayNV>() const {
    return _glPathMemoryGlyphIndexArrayNV;
}

template <>
inline const GlProgramPathFragmentInputGenNV&
GpuContextOgl::getFunction<GlProgramPathFragmentInputGenNV>() const {
    return _glProgramPathFragmentInputGenNV;
}

template <>
inline const GlGetProgramResourcefvNV&
GpuContextOgl::getFunction<GlGetProgramResourcefvNV>() const {
    return _glGetProgramResourcefvNV;
}

template <>
inline const GlFramebufferSampleLocationsfvNV&
GpuContextOgl::getFunction<GlFramebufferSampleLocationsfvNV>() const {
    return _glFramebufferSampleLocationsfvNV;
}

template <>
inline const GlNamedFramebufferSampleLocationsfvNV&
GpuContextOgl::getFunction<GlNamedFramebufferSampleLocationsfvNV>() const {
    return _glNamedFramebufferSampleLocationsfvNV;
}

template <>
inline const GlResolveDepthValuesNV&
GpuContextOgl::getFunction<GlResolveDepthValuesNV>() const {
    return _glResolveDepthValuesNV;
}

template <>
inline const GlMakeBufferResidentNV&
GpuContextOgl::getFunction<GlMakeBufferResidentNV>() const {
    return _glMakeBufferResidentNV;
}

template <>
inline const GlMakeBufferNonResidentNV&
GpuContextOgl::getFunction<GlMakeBufferNonResidentNV>() const {
    return _glMakeBufferNonResidentNV;
}

template <>
inline const GlIsBufferResidentNV&
GpuContextOgl::getFunction<GlIsBufferResidentNV>() const {
    return _glIsBufferResidentNV;
}

template <>
inline const GlMakeNamedBufferResidentNV&
GpuContextOgl::getFunction<GlMakeNamedBufferResidentNV>() const {
    return _glMakeNamedBufferResidentNV;
}

template <>
inline const GlMakeNamedBufferNonResidentNV&
GpuContextOgl::getFunction<GlMakeNamedBufferNonResidentNV>() const {
    return _glMakeNamedBufferNonResidentNV;
}

template <>
inline const GlIsNamedBufferResidentNV&
GpuContextOgl::getFunction<GlIsNamedBufferResidentNV>() const {
    return _glIsNamedBufferResidentNV;
}

template <>
inline const GlGetBufferParameterui64vNV&
GpuContextOgl::getFunction<GlGetBufferParameterui64vNV>() const {
    return _glGetBufferParameterui64vNV;
}

template <>
inline const GlGetNamedBufferParameterui64vNV&
GpuContextOgl::getFunction<GlGetNamedBufferParameterui64vNV>() const {
    return _glGetNamedBufferParameterui64vNV;
}

template <>
inline const GlGetIntegerui64vNV&
GpuContextOgl::getFunction<GlGetIntegerui64vNV>() const {
    return _glGetIntegerui64vNV;
}

template <>
inline const GlUniformui64NV&
GpuContextOgl::getFunction<GlUniformui64NV>() const {
    return _glUniformui64NV;
}

template <>
inline const GlUniformui64vNV&
GpuContextOgl::getFunction<GlUniformui64vNV>() const {
    return _glUniformui64vNV;
}

template <>
inline const GlGetUniformui64vNV&
GpuContextOgl::getFunction<GlGetUniformui64vNV>() const {
    return _glGetUniformui64vNV;
}

template <>
inline const GlProgramUniformui64NV&
GpuContextOgl::getFunction<GlProgramUniformui64NV>() const {
    return _glProgramUniformui64NV;
}

template <>
inline const GlProgramUniformui64vNV&
GpuContextOgl::getFunction<GlProgramUniformui64vNV>() const {
    return _glProgramUniformui64vNV;
}

template <>
inline const GlTextureBarrierNV&
GpuContextOgl::getFunction<GlTextureBarrierNV>() const {
    return _glTextureBarrierNV;
}

template <>
inline const GlVertexAttribL1i64NV&
GpuContextOgl::getFunction<GlVertexAttribL1i64NV>() const {
    return _glVertexAttribL1i64NV;
}

template <>
inline const GlVertexAttribL2i64NV&
GpuContextOgl::getFunction<GlVertexAttribL2i64NV>() const {
    return _glVertexAttribL2i64NV;
}

template <>
inline const GlVertexAttribL3i64NV&
GpuContextOgl::getFunction<GlVertexAttribL3i64NV>() const {
    return _glVertexAttribL3i64NV;
}

template <>
inline const GlVertexAttribL4i64NV&
GpuContextOgl::getFunction<GlVertexAttribL4i64NV>() const {
    return _glVertexAttribL4i64NV;
}

template <>
inline const GlVertexAttribL1i64vNV&
GpuContextOgl::getFunction<GlVertexAttribL1i64vNV>() const {
    return _glVertexAttribL1i64vNV;
}

template <>
inline const GlVertexAttribL2i64vNV&
GpuContextOgl::getFunction<GlVertexAttribL2i64vNV>() const {
    return _glVertexAttribL2i64vNV;
}

template <>
inline const GlVertexAttribL3i64vNV&
GpuContextOgl::getFunction<GlVertexAttribL3i64vNV>() const {
    return _glVertexAttribL3i64vNV;
}

template <>
inline const GlVertexAttribL4i64vNV&
GpuContextOgl::getFunction<GlVertexAttribL4i64vNV>() const {
    return _glVertexAttribL4i64vNV;
}

template <>
inline const GlVertexAttribL1ui64NV&
GpuContextOgl::getFunction<GlVertexAttribL1ui64NV>() const {
    return _glVertexAttribL1ui64NV;
}

template <>
inline const GlVertexAttribL2ui64NV&
GpuContextOgl::getFunction<GlVertexAttribL2ui64NV>() const {
    return _glVertexAttribL2ui64NV;
}

template <>
inline const GlVertexAttribL3ui64NV&
GpuContextOgl::getFunction<GlVertexAttribL3ui64NV>() const {
    return _glVertexAttribL3ui64NV;
}

template <>
inline const GlVertexAttribL4ui64NV&
GpuContextOgl::getFunction<GlVertexAttribL4ui64NV>() const {
    return _glVertexAttribL4ui64NV;
}

template <>
inline const GlVertexAttribL1ui64vNV&
GpuContextOgl::getFunction<GlVertexAttribL1ui64vNV>() const {
    return _glVertexAttribL1ui64vNV;
}

template <>
inline const GlVertexAttribL2ui64vNV&
GpuContextOgl::getFunction<GlVertexAttribL2ui64vNV>() const {
    return _glVertexAttribL2ui64vNV;
}

template <>
inline const GlVertexAttribL3ui64vNV&
GpuContextOgl::getFunction<GlVertexAttribL3ui64vNV>() const {
    return _glVertexAttribL3ui64vNV;
}

template <>
inline const GlVertexAttribL4ui64vNV&
GpuContextOgl::getFunction<GlVertexAttribL4ui64vNV>() const {
    return _glVertexAttribL4ui64vNV;
}

template <>
inline const GlGetVertexAttribLi64vNV&
GpuContextOgl::getFunction<GlGetVertexAttribLi64vNV>() const {
    return _glGetVertexAttribLi64vNV;
}

template <>
inline const GlGetVertexAttribLui64vNV&
GpuContextOgl::getFunction<GlGetVertexAttribLui64vNV>() const {
    return _glGetVertexAttribLui64vNV;
}

template <>
inline const GlVertexAttribLFormatNV&
GpuContextOgl::getFunction<GlVertexAttribLFormatNV>() const {
    return _glVertexAttribLFormatNV;
}

template <>
inline const GlBufferAddressRangeNV&
GpuContextOgl::getFunction<GlBufferAddressRangeNV>() const {
    return _glBufferAddressRangeNV;
}

template <>
inline const GlVertexFormatNV&
GpuContextOgl::getFunction<GlVertexFormatNV>() const {
    return _glVertexFormatNV;
}

template <>
inline const GlNormalFormatNV&
GpuContextOgl::getFunction<GlNormalFormatNV>() const {
    return _glNormalFormatNV;
}

template <>
inline const GlColorFormatNV&
GpuContextOgl::getFunction<GlColorFormatNV>() const {
    return _glColorFormatNV;
}

template <>
inline const GlIndexFormatNV&
GpuContextOgl::getFunction<GlIndexFormatNV>() const {
    return _glIndexFormatNV;
}

template <>
inline const GlTexCoordFormatNV&
GpuContextOgl::getFunction<GlTexCoordFormatNV>() const {
    return _glTexCoordFormatNV;
}

template <>
inline const GlEdgeFlagFormatNV&
GpuContextOgl::getFunction<GlEdgeFlagFormatNV>() const {
    return _glEdgeFlagFormatNV;
}

template <>
inline const GlSecondaryColorFormatNV&
GpuContextOgl::getFunction<GlSecondaryColorFormatNV>() const {
    return _glSecondaryColorFormatNV;
}

template <>
inline const GlFogCoordFormatNV&
GpuContextOgl::getFunction<GlFogCoordFormatNV>() const {
    return _glFogCoordFormatNV;
}

template <>
inline const GlVertexAttribFormatNV&
GpuContextOgl::getFunction<GlVertexAttribFormatNV>() const {
    return _glVertexAttribFormatNV;
}

template <>
inline const GlVertexAttribIFormatNV&
GpuContextOgl::getFunction<GlVertexAttribIFormatNV>() const {
    return _glVertexAttribIFormatNV;
}

template <>
inline const GlGetIntegerui64i_vNV&
GpuContextOgl::getFunction<GlGetIntegerui64i_vNV>() const {
    return _glGetIntegerui64i_vNV;
}

template <>
inline const GlViewportSwizzleNV&
GpuContextOgl::getFunction<GlViewportSwizzleNV>() const {
    return _glViewportSwizzleNV;
}

template <>
inline const GlFramebufferTextureMultiviewOVR&
GpuContextOgl::getFunction<GlFramebufferTextureMultiviewOVR>() const {
    return _glFramebufferTextureMultiviewOVR;
}

#ifdef _WIN32

template <>
inline const WglGetExtensionsStringEXT&
GpuContextOgl::getFunction<WglGetExtensionsStringEXT>() const {
    return _wglGetExtensionsStringEXT;
}

template <>
inline const WglGetExtensionsStringARB&
GpuContextOgl::getFunction<WglGetExtensionsStringARB>() const {
    return _wglGetExtensionsStringARB;
}

template <>
inline const WglCreateContextAttribsARB&
GpuContextOgl::getFunction<WglCreateContextAttribsARB>() const {
    return _wglCreateContextAttribsARB;
}

template <>
inline const WglSwapIntervalEXT&
GpuContextOgl::getFunction<WglSwapIntervalEXT>() const {
    return _wglSwapIntervalEXT;
}

#endif

#ifdef __linux__

template <>
inline const GlXCreateContextAttribsARB&
GpuContextOgl::getFunction<GlXCreateContextAttribsARB>() const {
    return _glXCreateContextAttribsARB;
}

template <>
inline const GlXSwapIntervalEXT&
GpuContextOgl::getFunction<GlXSwapIntervalEXT>() const {
    return _glXSwapIntervalEXT;
}

template <>
inline const GlXSwapIntervalMESA&
GpuContextOgl::getFunction<GlXSwapIntervalMESA>() const {
    return _glXSwapIntervalMESA;
}

#endif

}
