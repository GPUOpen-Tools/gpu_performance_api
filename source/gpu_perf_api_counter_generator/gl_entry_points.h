//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL entry points
//==============================================================================

#ifndef _GL_ENTRY_POINTS_H_
#define _GL_ENTRY_POINTS_H_

#include <map>

#include "gl_include.h"
#include "gl_func_types.h"

#ifndef GLES

// used for defining the proc addresses which are initialized below
#ifdef _WIN32

#define GET_PROC_ADDRESS_TYPE wglGetProcAddress
#define GET_PROC_ADDRESS_FUNC _wglGetProcAddress

#endif

#ifdef _LINUX

#define GET_PROC_ADDRESS_TYPE glXGetProcAddressARB
#define GET_PROC_ADDRESS_FUNC _glXGetProcAddressARB
#endif

#else


#define GET_PROC_ADDRESS_TYPE eglGetProcAddress
#define GET_PROC_ADDRESS_FUNC _eglGetProcAddress

#endif  // GLES

#ifdef _LINUX
#include <dlfcn.h>
#define LOAD_SYMBOL dlsym
#else
#define LOAD_SYMBOL GetProcAddress
#endif

#ifdef WIN32
typedef HMODULE LibHandle;
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(oglUtils::GET_PROC_ADDRESS_FUNC(name));
#else
typedef void* LibHandle;
#ifdef GLES
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(oglUtils::GET_PROC_ADDRESS_FUNC((const char*)name));
#else
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(oglUtils::GET_PROC_ADDRESS_FUNC((const GLubyte*)name));
#endif
#endif

#define LOAD_LIBRARY_SYMBOL(varName, type)                                                \
    if (nullptr == (varName))                                                             \
    {                                                                                     \
        (varName) = reinterpret_cast<decltype(type)*>(LOAD_SYMBOL(s_glLibHandle, #type)); \
    }

//declarations for GLX_MESA_query_renderer extension (subset -- just what is needed for GPA GL)
#ifndef GLX_MESA_query_renderer
#define GLX_MESA_query_renderer 1           /// constant used to query the renderer using the MESA extension
#define GLX_RENDERER_DEVICE_ID_MESA 0x8184  /// constant used to query the device id using the MESA extension
#endif                                      /* GLX_MESA_query_renderer */

#ifdef GLES
    // GL_EXT_disjoint_timer_query
    #define PFNGLGENQUERIESPROC             PFNGLGENQUERIESEXTPROC
    #define PFNGLDELETEQUERIESPROC          PFNGLDELETEQUERIESEXTPROC
    #define PFNGLGETQUERYOBJECTIVPROC       PFNGLGETQUERYOBJECTIVEXTPROC
    #define PFNGLQUERYCOUNTERPROC           PFNGLQUERYCOUNTEREXTPROC
#endif

namespace oglUtils
{
    extern decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC;

    // Timer query GL extensions
    extern PFNGLGENQUERIESPROC              _oglGenQueries;
    extern PFNGLDELETEQUERIESPROC           _oglDeleteQueries;
    extern PFNGLGETQUERYOBJECTIVPROC        _oglGetQueryObjectiv;
    extern PFNGLQUERYCOUNTERPROC            _oglQueryCounter;

    extern decltype(glFlush)*               _oglFlush;
    extern decltype(glGetString)*           _oglGetString;
    extern decltype(glGetIntegerv)*         _oglGetIntegerv;
    extern decltype(glGetError)*            _oglGetError;
    extern PFNGLGETSTRINGIPROC              _oglGetStringi;

    extern PFNGLGETQUERYOBJECTUI64VEXTPROC  _oglGetQueryObjectui64vEXT; // Exists in GL and GLES as extension

    /// AMD perf monitor extensions
    extern PFNGLGETPERFMONITORGROUPSAMDPROC         _oglGetPerfMonitorGroupsAMD;
    extern PFNGLGETPERFMONITORCOUNTERSAMDPROC       _oglGetPerfMonitorCountersAMD;
    extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC    _oglGetPerfMonitorGroupStringAMD;
    extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC  _oglGetPerfMonitorCounterStringAMD;
    extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC    _oglGetPerfMonitorCounterInfoAMD;
    extern PFNGLGENPERFMONITORSAMDPROC              _oglGenPerfMonitorsAMD;
    extern PFNGLDELETEPERFMONITORSAMDPROC           _oglDeletePerfMonitorsAMD;
    extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC    _oglSelectPerfMonitorCountersAMD;
    extern PFNGLBEGINPERFMONITORAMDPROC             _oglBeginPerfMonitorAMD;
    extern PFNGLENDPERFMONITORAMDPROC               _oglEndPerfMonitorAMD;
    extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC    _oglGetPerfMonitorCounterDataAMD;

#ifdef DEBUG_GL_ERRORS
    extern PFN_OGL_GLDEBUGMESSAGECONTROLARB  _oglDebugMessageControlARB;
    extern PFN_OGL_GLDEBUGMESSAGEINSERTARB   _oglDebugMessageInsertARB;
    extern PFN_OGL_GLDEBUGMESSAGECALLBACKARB _oglDebugMessageCallbackARB;
    extern PFN_OGL_GLGETDEBUGMESSAGELOGARB   _oglGetDebugMessageLogARB;
#endif

    extern PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA _oglXQueryCurrentRendererIntegerMESA;  ///< function pointer for glxQueryCurrentRendererIntegerMesa
    extern PFN_GL_SETGPADEVICECLOCKMODEAMDX        _oglSetGpaDeviceClockModeAMDX;         ///< function pointer for glSetGpaDeviceClockModeAMDX

    /// Loads the OpenGL library
    /// \return true if loaded successfully otherwise false
    bool LoadGL();

    /// Queries OpenGL extensions and initializes the entry points needed for perf counter collection
    /// The extensions queried are:
    ///    -- GL_AMD_performance_monitor
    ///    -- GL_ARB_timer_query (OpenGL)
    ///    -- GL_EXT_disjoint_timer_query (OpenGLES)
    ///    -- GL_AMD_debug_output
    ///    -- GLX_MESA_query_renderer
    /// \return false if the GL_AMD_performance_monitor or GL_ARB_timer_query extension entry points are not found
    ///         true otherwise
    bool InitializeGLFunctions();

    /// Query supported extensions
    void QuerySupportedExtensions();

    /// Initializes the GL core functions
    /// \return true upon success otherwise false
    bool InitializeGLCoreFunctions();

    /// Initializes the OpenGL AMD perf extension function to use with current rendering context
    /// \return true upon successful otherwise false
    bool InitCtxAmdPerfExtFunctions();

    extern const char* s_pAMDRenderer;               ///< AMD Renderer string
    extern const char* s_pRadeonRenderer;            ///< Radeon Renderer string
    extern const char* s_pATIRenderer;               ///< ATI Renderer string (legacy)
    extern const char* s_pNVIDIARenderer;            ///< NVIDIA Renderer string
    extern const char* s_pIntelRenderer;             ///< Intel Renderer string
    extern bool        s_areGLFunctionsInitialized;  ///< flag indicating if the GL extensions and functions have been initialized
    extern LibHandle   s_glLibHandle;                ///< handle to the GL lib

    using GLExtension = std::string;                         ///< alias for GL extension
    using Supported   = bool;                                ///< alias for extension status
    extern std::map<GLExtension, Supported> s_glExtensions;  ///< Map of GL extensions and its status
}  // namespace oglUtils

#endif  // _GL_ENTRY_POINTS_H_
