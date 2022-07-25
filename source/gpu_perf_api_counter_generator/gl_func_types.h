//==============================================================================
// Copyright (c) 2019-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief File defines the functions which are not declared in any of the GL headers.
//==============================================================================

#ifndef GPA_COUNTER_GENERATOR_GL_GL_FUNC_TYPES_H_
#define GPA_COUNTER_GENERATOR_GL_GL_FUNC_TYPES_H_

namespace ogl_utils
{
    typedef unsigned int GLhandle;                                                                        ///< Workaround missing def in headers.
    typedef bool(APIENTRY* PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA)(int attribute, unsigned int* value);  ///< Typedef for glxQueryCurrentRendererIntegerMesa.
    typedef unsigned int(APIENTRY* PFN_GL_SETGPADEVICECLOCKMODEAMDX)(void* clock_mode);                   ///< Typedef for glSetGpaDeviceClockModeAMDX.

    typedef void(APIENTRY* PFN_GL_GETPERFMONITORGROUPS2AMDPROC)(GLint* numGroups, GLsizei groupsSize, GLuint* groups, GLuint* numGroupInstances);
    typedef void(APIENTRY* PFN_GL_SELECTPERFMONITORCOUNTERS2AMDPROC)(GLuint monitor, GLboolean enable, GLuint group, GLuint instance, GLint numCounters, GLuint* counterList);

#ifdef GLES
    typedef GLvoid(APIENTRY* PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);                         ///< Typedef for glQueryCounter.
    typedef GLvoid(APIENTRY* PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum name, GLuint64* params);  ///< Typedef for glQueryObjectUI64.
#endif

#ifdef DEBUG_GL_ERRORS
    typedef unsigned int GLuint;  ///< Workaround missing def in headers.
    typedef GLvoid(
        APIENTRY* PFN_OGL_GLDEBUGMESSAGECONTROLARB)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGEINSERTARB)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf);
    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGECALLBACKARB)(GLvoid* callback, GLvoid* userParam);
    typedef GLuint(APIENTRY* PFN_OGL_GLGETDEBUGMESSAGELOGARB)(GLuint   count,
                                                              GLsizei  buffer_size,
                                                              GLenum*  sources,
                                                              GLenum*  types,
                                                              GLuint*  ids,
                                                              GLenum*  severities,
                                                              GLsizei* lengths,
                                                              GLchar*  message_log);
#endif

}
#endif  // GPA_COUNTER_GENERATOR_GL_GL_FUNC_TYPES_H_
