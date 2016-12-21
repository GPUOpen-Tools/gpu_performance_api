//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  declares GL entry points
//==============================================================================

#ifndef _GL_ENTRY_POINTS_H_
#define _GL_ENTRY_POINTS_H_

#ifndef GLES

#ifdef _WIN32
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif

#ifdef _LINUX
    #include <GL/glx.h>
    #include <GL/glxext.h>
#endif

// used for defining the proc addresses which are initialized below
#ifdef _WIN32
extern decltype(wglGetProcAddress)* _wglGetProcAddress; ///< function pointer for wglGetProcAddress
#define GET_PROC_ADDRESS(f,type,name)\
    (f) = (type) _wglGetProcAddress(name);
#endif

#ifdef _LINUX
extern decltype(glXGetProcAddressARB)* _glXGetProcAddressARB; ///< function pointer for glXGetProcAddressARB
#define GET_PROC_ADDRESS(f,type,name)\
    (f) = (type) _glXGetProcAddressARB( (const GLubyte*) name);
#endif

#else

#ifdef _WIN32
    typedef unsigned __int64 uint64_t;
#endif

// by default, GLES uses 32 bits for 64 bit types. GPA extensions require 64 bits
#define _USE64BIT

#include <stdint.h>
#include <GLES/egl.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

// used for defining the proc addresses which are initialized below
extern decltype(eglGetProcAddress)* _eglGetProcAddress; ///< function pointer for eglGetProcAddress
#define GET_PROC_ADDRESS(f,type,name)\
    (f) = (type) _eglGetProcAddress(name);

#endif // GLES

typedef unsigned int GLhandle; ///< Workaround missing def in headers

extern decltype(glFlush)*                      _oglFlush;                           ///< function pointer for glFlush
extern decltype(glGetString)*                  _oglGetString;                       ///< function pointer for glGetString
extern decltype(glGetIntegerv)*                _oglGetIntegerv;                     ///< function pointer for glGetIntegerv
#ifdef _WIN32
extern decltype(wglGetCurrentContext)*         _wglGetCurrentContext;               ///< function pointer for wglGetCurrentContext
#endif
extern PFNGLGETPERFMONITORGROUPSAMDPROC        _oglGetPerfMonitorGroupsAMD;         ///< function pointer for glGetPerfMonitorGroupsAMD
extern PFNGLGETPERFMONITORCOUNTERSAMDPROC      _oglGetPerfMonitorCountersAMD;       ///< function pointer for glGetPerfMonitorCountersAMD
extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC   _oglGetPerfMonitorGroupStringAMD;    ///< function pointer for glGetPerfMonitorGroupStringAMD
extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC _oglGetPerfMonitorCounterStringAMD;  ///< function pointer for glGetPerfMonitorCounterStringAMD
extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC   _oglGetPerfMonitorCounterInfoAMD;    ///< function pointer for glGetPerfMonitorCounterInfoAMD
extern PFNGLGENPERFMONITORSAMDPROC             _oglGenPerfMonitorsAMD;              ///< function pointer for glGenPerfMonitorsAMD
extern PFNGLDELETEPERFMONITORSAMDPROC          _oglDeletePerfMonitorsAMD;           ///< function pointer for glDeletePerfMonitorsAMD
extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC   _oglSelectPerfMonitorCountersAMD;    ///< function pointer for glSelectPerfMonitorCountersAMD
extern PFNGLBEGINPERFMONITORAMDPROC            _oglBeginPerfMonitorAMD;             ///< function pointer for glBeginPerfMonitorAMD
extern PFNGLENDPERFMONITORAMDPROC              _oglEndPerfMonitorAMD;               ///< function pointer for glEndPerfMonitorAMD
extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC   _oglGetPerfMonitorCounterDataAMD;    ///< function pointer for glGetPerfMonitorCounterDataAMD

#ifdef GLES
    typedef GLvoid(APIENTRY* PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);  ///< typedef for glQueryCounter
    typedef GLvoid(APIENTRY* PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64* params); ///< typedef for glQueryObjectUI64
#endif

/// constant for the AMD-specific extended timer result
#define GL_QUERY_EXTENDED_TIMER_RESULT_AMDX             0x8870
extern PFNGLBEGINQUERYPROC                     _oglBeginQuery;              ///< function pointer for glBeginQuery
extern PFNGLENDQUERYPROC                       _oglEndQuery;                ///< function pointer for glEndQuery
extern PFNGLGETQUERYIVPROC                     _oglGetQueryiv;              ///< function pointer for glGetQueryiv
extern PFNGLGETQUERYOBJECTUI64VEXTPROC         _oglGetQueryObjectui64vEXT;  ///< function pointer for glGetQueryObjectui64vEXT
extern PFNGLGETQUERYOBJECTIVPROC               _oglGetQueryObjectiv;        ///< function pointer for glGetQueryObjectiv
extern PFNGLGETQUERYOBJECTUI64VPROC            _oglGetQueryObjectui64v;     ///< function pointer for glGetQueryObjectui64v
extern PFNGLGENQUERIESPROC                     _oglGenQueries;              ///< function pointer for glGenQueries
extern PFNGLDELETEQUERIESPROC                  _oglDeleteQueries;           ///< function pointer for glDeleteQueries

extern PFNGLQUERYCOUNTERPROC                   _oglQueryCounter;            ///< function pointer for glQueryCounter

// Function pointers for glGetStringi call to query extension strings in 3.x
extern PFNGLGETSTRINGIPROC                     _oglGetStringi;              ///< function pointer for glGetStringi

#ifdef DEBUG_GL_ERRORS
    typedef unsigned int GLuint; // for some reason this doesn't get included from the gl.h include above? no idea...

    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGECONTROLARB)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
    extern PFN_OGL_GLDEBUGMESSAGECONTROLARB _oglDebugMessageControlARB;

    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGEINSERTARB)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf);
    extern PFN_OGL_GLDEBUGMESSAGEINSERTARB _oglDebugMessageInsertARB;

    typedef GLvoid(APIENTRY* PFN_OGL_GLDEBUGMESSAGECALLBACKARB)(GLvoid* callback, GLvoid* userParam);
    extern PFN_OGL_GLDEBUGMESSAGECALLBACKARB _oglDebugMessageCallbackARB;

    typedef GLuint(APIENTRY* PFN_OGL_GLGETDEBUGMESSAGELOGARB)(GLuint count, GLsizei bufsize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);
    extern PFN_OGL_GLGETDEBUGMESSAGELOGARB _oglGetDebugMessageLogARB;
#endif

//declarations for GLX_MESA_query_renderer extension (subset -- just what is needed for GPA GL)
#ifndef GLX_MESA_query_renderer
    /// constant used to query the renderer using the MESA extension
    #define GLX_MESA_query_renderer 1
    /// constant used to query the device id using the MESA extension
    #define GLX_RENDERER_DEVICE_ID_MESA       0x8184
#endif /* GLX_MESA_query_renderer */

typedef bool(APIENTRY* PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA)(int attribute, unsigned int* value); ///< typedef for glxQueryCurrentRendererIntegerMesa
extern PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA _oglXQueryCurrentRendererIntegerMESA;                 ///< function pointer for glxQueryCurrentRendererIntegerMesa


#endif // _GL_ENTRY_POINTS_H_
