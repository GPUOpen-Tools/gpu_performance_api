//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL entry points.
//==============================================================================

#ifndef GPA_COUNTER_GENERATOR_GL_GL_ENTRY_POINTS_H_
#define GPA_COUNTER_GENERATOR_GL_GL_ENTRY_POINTS_H_

#include <map>

#include "gpu_perf_api_counter_generator/gl_include.h"
#include "gpu_perf_api_counter_generator/gl_func_types.h"

#ifndef GLES

// Used for defining the proc addresses which are initialized below.
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
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(ogl_utils::GET_PROC_ADDRESS_FUNC(name));
#else
typedef void* LibHandle;
#ifdef GLES
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(ogl_utils::GET_PROC_ADDRESS_FUNC((const char*)name));
#else
#define GET_CONTEXT_PROC_ADDRESS(f, type, name) (f) = reinterpret_cast<type>(ogl_utils::GET_PROC_ADDRESS_FUNC((const GLubyte*)name));
#endif
#endif

#define LOAD_LIBRARY_SYMBOL(varName, type)                                                \
    if (nullptr == (varName))                                                             \
    {                                                                                     \
        (varName) = reinterpret_cast<decltype(type)*>(LOAD_SYMBOL(gl_lib_handle, #type)); \
    }

// Declarations for GLX_MESA_query_renderer extension (subset -- just what is needed for GPA GL).
#ifndef GLX_MESA_query_renderer
#define GLX_MESA_query_renderer 1           /// Constant used to query the renderer using the MESA extension.
#define GLX_RENDERER_DEVICE_ID_MESA 0x8184  /// Constant used to query the device id using the MESA extension.
#endif

#ifdef GLES
// GL_EXT_disjoint_timer_query.
#define PFNGLGENQUERIESPROC PFNGLGENQUERIESEXTPROC
#define PFNGLDELETEQUERIESPROC PFNGLDELETEQUERIESEXTPROC
#define PFNGLGETQUERYOBJECTIVPROC PFNGLGETQUERYOBJECTIVEXTPROC
#define PFNGLQUERYCOUNTERPROC PFNGLQUERYCOUNTEREXTPROC
#endif

namespace ogl_utils
{
    extern decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC;

    // Timer query GL extensions.
    extern PFNGLGENQUERIESPROC       ogl_gen_queries;
    extern PFNGLDELETEQUERIESPROC    ogl_delete_queries;
    extern PFNGLGETQUERYOBJECTIVPROC ogl_get_query_objective_iv;
    extern PFNGLQUERYCOUNTERPROC     ogl_query_counter;

    extern decltype(glFlush)*       ogl_flush;
    extern decltype(glGetString)*   ogl_get_string;
    extern decltype(glGetIntegerv)* ogl_get_integer_v;
    extern decltype(glGetError)*    ogl_get_error;
    extern PFNGLGETSTRINGIPROC      ogl_get_string_i;

    extern PFNGLGETQUERYOBJECTUI64VEXTPROC ogl_get_query_object_ui_64_v_ext;  // Exists in GL and GLES as extension.

    /// AMD perf monitor extensions.
    extern PFNGLGETPERFMONITORGROUPSAMDPROC        ogl_get_perf_monitor_groups_amd;
    extern PFNGLGETPERFMONITORCOUNTERSAMDPROC      ogl_get_perf_monitor_counters_amd;
    extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC   ogl_get_perf_monitor_group_string_amd;
    extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC ogl_get_perf_monitor_counter_string_amd;
    extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC   ogl_get_perf_monitor_counter_info_amd;
    extern PFNGLGENPERFMONITORSAMDPROC             ogl_gen_perf_monitors_amd;
    extern PFNGLDELETEPERFMONITORSAMDPROC          ogl_delete_perf_monitors_amd;
    extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC   ogl_select_perf_monitor_counters_amd;
    extern PFNGLBEGINPERFMONITORAMDPROC            ogl_begin_perf_monitor_amd;
    extern PFNGLENDPERFMONITORAMDPROC              ogl_end_perf_monitor_amd;
    extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC   ogl_get_perf_monitor_counter_data_amd;

#ifdef DEBUG_GL_ERRORS
    extern PFN_OGL_GLDEBUGMESSAGECONTROLARB  ogl_debug_message_control_arb;
    extern PFN_OGL_GLDEBUGMESSAGEINSERTARB   ogl_debug_message_insert_arb;
    extern PFN_OGL_GLDEBUGMESSAGECALLBACKARB ogl_debug_message_callback_arb;
    extern PFN_OGL_GLGETDEBUGMESSAGELOGARB   ogl_get_debug_message_log_arb;
#endif

    extern PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA ogl_x_query_current_renderer_integer_mesa;  ///< Function pointer for glxQueryCurrentRendererIntegerMesa.
    extern PFN_GL_SETGPADEVICECLOCKMODEAMDX        ogl_set_gpa_device_clock_mode_amd_x;        ///< Function pointer for glSetGpaDeviceClockModeAMDX.

    /// @brief Loads the OpenGL library.
    ///
    /// @return True if loaded successfully otherwise false.
    bool LoadGl();

    /// @brief Queries OpenGL extensions and initializes the entry points needed for perf counter collection.
    ///
    /// The extensions queried are:
    ///    -- GL_AMD_performance_monitor
    ///    -- GL_ARB_timer_query (OpenGL)
    ///    -- GL_EXT_disjoint_timer_query (OpenGLES)
    ///    -- GL_AMD_debug_output
    ///    -- GLX_MESA_query_renderer
    ///
    /// @retval false If the GL_AMD_performance_monitor or GL_ARB_timer_query extension entry points are not found.
    /// @retval true Otherwise.
    bool InitializeGlFunctions();

    /// @brief Query supported extensions.
    void QuerySupportedExtensions();

    /// @brief Initializes the GL core functions.
    ///
    /// @return True upon success otherwise false.
    bool InitializeGlCoreFunctions();

    /// @brief Initializes the OpenGL AMD perf extension function to use with current rendering context.
    ///
    /// @return True upon successful otherwise false.
    bool InitCtxAmdPerfExtFunctions();

    /// @brief Initialize platform-specific OpenGL extensions.
    ///
    /// @return True upon success otherwise false.
    bool InitPlatformExtFunctions();

    extern const char* kAmdRendererString;            ///< AMD Renderer string.
    extern const char* kRadeonRendererString;         ///< Radeon Renderer string.
    extern const char* kAtiRendererString;            ///< ATI Renderer string (legacy).
    extern const char* kNvidiaRendererString;         ///< NVIDIA Renderer string.
    extern const char* kIntelRendererString;          ///< Intel Renderer string.
    extern bool        are_gl_functions_initialized;  ///< Flag indicating if the GL extensions and functions have been initialized.
    extern LibHandle   gl_lib_handle;                 ///< Handle to the GL lib.

    using GLExtension = std::string;                            ///< Alias for GL extension.
    using Supported   = bool;                                   ///< Alias for extension status.
    extern std::map<GLExtension, Supported> gl_extensions_map;  ///< Map of GL extensions and its status.
}  // namespace ogl_utils

#endif  // GPA_COUNTER_GENERATOR_GL_GL_ENTRY_POINTS_H_
