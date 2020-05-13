//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  File defines the functions which are not declared in any of the GL headers
//==============================================================================

#ifndef _GL_FUNC_TYPES_H_
#define _GL_FUNC_TYPES_H_

namespace oglUtils
{
    typedef unsigned int GLhandle;                                                                        ///< Workaround missing def in headers
    typedef bool(APIENTRY* PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA)(int attribute, unsigned int* value);  ///< typedef for glxQueryCurrentRendererIntegerMesa
    typedef unsigned int(APIENTRY* PFN_GL_SETGPADEVICECLOCKMODEAMDX)(void* clockmode);                    ///< typedef for glSetGpaDeviceClockModeAMDX

#ifdef GLES
    typedef GLvoid(APIENTRY* PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);                          ///< typedef for glQueryCounter
    typedef GLvoid(APIENTRY* PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64* params);  ///< typedef for glQueryObjectUI64
#endif

#ifdef DEBUG_GL_ERRORS
    typedef unsigned int GLuint;  // for some reason this doesn't get included from the gl.h include above? no idea...
    typedef GLvoid(
        APIENTRY* PFN_OGL_GLDEBUGMESSAGECONTROLARB)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGEINSERTARB)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf);
    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGECALLBACKARB)(GLvoid* callback, GLvoid* userParam);
    typedef GLuint(APIENTRY* PFN_OGL_GLGETDEBUGMESSAGELOGARB)(GLuint   count,
                                                              GLsizei  bufsize,
                                                              GLenum*  sources,
                                                              GLenum*  types,
                                                              GLuint*  ids,
                                                              GLenum*  severities,
                                                              GLsizei* lengths,
                                                              GLchar*  messageLog);
#endif

}  // namespace oglUtils
#endif