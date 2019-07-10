//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL entry points
//==============================================================================

#ifndef _GL_ENTRY_POINTS_H_
#define _GL_ENTRY_POINTS_H_

#include <map>

#ifndef GLES

#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#endif

#ifdef _LINUX
#include <GL/glx.h>
#include <GL/glxext.h>
#endif

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

#ifdef _WIN32
typedef unsigned __int64 uint64_t;
#endif

// by default, GLES uses 32 bits for 64 bit types. GPA extensions require 64 bits
#define _USE64BIT

#include <stdint.h>
#include <GLES/egl.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

#define GET_PROC_ADDRESS_TYPE eglGetProcAddress
#define GET_PROC_ADDRESS_FUNC _eglGetProcAddress

#endif  // GLES

#ifdef WIN32
typedef HMODULE LibHandle;
#define GET_PROC_ADDRESS(f, type, name) (f) = (type)oglUtils::GET_PROC_ADDRESS_FUNC(name);
#else
typedef void* LibHandle;
#define GET_PROC_ADDRESS(f, type, name) (f) = (type)oglUtils::GET_PROC_ADDRESS_FUNC((const GLubyte*)name);
#endif

//declarations for GLX_MESA_query_renderer extension (subset -- just what is needed for GPA GL)
#ifndef GLX_MESA_query_renderer
#define GLX_MESA_query_renderer 1           /// constant used to query the renderer using the MESA extension
#define GLX_RENDERER_DEVICE_ID_MESA 0x8184  /// constant used to query the device id using the MESA extension
#endif                                      /* GLX_MESA_query_renderer */

#include "GLFuncTypes.h"

namespace oglUtils
{
    extern decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC;

#define DECLARE_CORE_FUNCS(type, typeString) extern decltype(type)* _o##type;

#include "GLFunctions.h"
    GL_CORE_FUNCTIONS(DECLARE_CORE_FUNCS)

#undef DECLARE_CORE_FUNCS

#define DECLARE_GL_PLATFORM_CORE_FUNCS(type, typeString) extern decltype(type)* _##type;

#ifdef WIN32
    WGL_CORE_FUNCTIONS(DECLARE_GL_PLATFORM_CORE_FUNCS)
#else
    GLX_CORE_FUNCTIONS(DECLARE_GL_PLATFORM_CORE_FUNCS)
#endif

#undef DECLARE_GL_PLATFORM_CORE_FUNCS

#define DECLARE_EXT_FUNCS(type, typeString) extern type _o##typeString;

#include "GLFunctions.h"
    GL_EXT_FUNCTIONS(DECLARE_EXT_FUNCS)
    GL_AMD_EXT_FUNCTIONS(DECLARE_EXT_FUNCS)

#undef DECLARE_EXT_FUNCS

// AMD GPU association extension functions
#define DECLARE_AMD_ASSOCIATION_FUNCS(type, typeString) extern type _##typeString;

#include "GLFunctions.h"
#ifdef WIN32
    WGL_AMD_EXT_FUNCTIONS(DECLARE_AMD_ASSOCIATION_FUNCS)
#else
    GLX_AMD_EXT_FUNCTIONS(DECLARE_AMD_ASSOCIATION_FUNCS)
#endif

#undef DECLARE_AMD_ASSOCIATION_FUNCS

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

    /// Initializes the GL core functions
    /// \return true upon success otherwise false
    bool InitializeGLCoreFunctions();

    /// Query supported extensions
    void QuerySupportedExtensions();

    /// Initializes the OpenGL extension function to use with current rendering context
    /// \return true upon successful otherwise false
    bool InitCtxExtFunctions();

    /// Initializes the OpenGL AMD perf extension function to use with current rendering context
    /// \return true upon successful otherwise false
    bool InitCtxAmdPerfExtFunctions();

    /// Initializes the OpenGL AMD Multi-GPU extension function to use with current rendering context
    /// \return true upon successful otherwise false
    bool InitCtxAmdMultiGpuExtFunctions();

    /// Returns whether the AMD GPU association for multiple GPU are available or not
    /// \return true if AMD extension exist otherwise false
    bool IsAmdGpuAssociationSupported();

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
