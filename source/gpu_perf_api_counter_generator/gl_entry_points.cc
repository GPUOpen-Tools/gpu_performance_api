//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL entry points.
//==============================================================================

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/logging.h"

namespace ogl_utils
{
    decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC = nullptr;

    decltype(glFlush)*       ogl_flush         = nullptr;
    decltype(glGetString)*   ogl_get_string    = nullptr;
    decltype(glGetIntegerv)* ogl_get_integer_v = nullptr;
    decltype(glGetError)*    ogl_get_error     = nullptr;

#ifdef _LINUX
#ifndef GLES
    decltype(glXGetClientString)* ogl_x_get_client_string = nullptr;
#endif
#endif

    PFNGLGETSTRINGIPROC ogl_get_string_i = nullptr;

    PFNGLGETQUERYOBJECTIVPROC       ogl_get_query_objective_iv       = nullptr;
    PFNGLGENQUERIESPROC             ogl_gen_queries                  = nullptr;
    PFNGLDELETEQUERIESPROC          ogl_delete_queries               = nullptr;
    PFNGLQUERYCOUNTERPROC           ogl_query_counter                = nullptr;
    PFNGLGETQUERYOBJECTUI64VEXTPROC ogl_get_query_object_ui_64_v_ext = nullptr;

    /// AMD perf monitor extensions.
    PFNGLGETPERFMONITORGROUPSAMDPROC        ogl_get_perf_monitor_groups_amd         = nullptr;
    PFNGLGETPERFMONITORCOUNTERSAMDPROC      ogl_get_perf_monitor_counters_amd       = nullptr;
    PFNGLGETPERFMONITORGROUPSTRINGAMDPROC   ogl_get_perf_monitor_group_string_amd   = nullptr;
    PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC ogl_get_perf_monitor_counter_string_amd = nullptr;
    PFNGLGETPERFMONITORCOUNTERINFOAMDPROC   ogl_get_perf_monitor_counter_info_amd   = nullptr;
    PFNGLGENPERFMONITORSAMDPROC             ogl_gen_perf_monitors_amd               = nullptr;
    PFNGLDELETEPERFMONITORSAMDPROC          ogl_delete_perf_monitors_amd            = nullptr;
    PFNGLSELECTPERFMONITORCOUNTERSAMDPROC   ogl_select_perf_monitor_counters_amd    = nullptr;
    PFNGLBEGINPERFMONITORAMDPROC            ogl_begin_perf_monitor_amd              = nullptr;
    PFNGLENDPERFMONITORAMDPROC              ogl_end_perf_monitor_amd                = nullptr;
    PFNGLGETPERFMONITORCOUNTERDATAAMDPROC   ogl_get_perf_monitor_counter_data_amd   = nullptr;

#ifdef DEBUG_GL_ERRORS
    // Function pointers for the GL_ARB_debug_output extension - used to improve error reporting.
    PFN_OGL_GLDEBUGMESSAGECONTROLARB  ogl_debug_message_control_arb  = nullptr;
    PFN_OGL_GLDEBUGMESSAGEINSERTARB   ogl_debug_message_insert_arb   = nullptr;
    PFN_OGL_GLDEBUGMESSAGECALLBACKARB ogl_debug_message_callback_arb = nullptr;
    PFN_OGL_GLGETDEBUGMESSAGELOGARB   ogl_get_debug_message_log_arb  = nullptr;
#endif

    // Function pointers for GLX_MESA_query_renderer extension.
    PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA ogl_x_query_current_renderer_integer_mesa = nullptr;

    PFN_GL_SETGPADEVICECLOCKMODEAMDX ogl_set_gpa_device_clock_mode_amd_x = nullptr;

    const char* kAmdRendererString           = "AMD";
    const char* kRadeonRendererString        = "Radeon";
    const char* kAtiRendererString           = "ATI";
    const char* kNvidiaRendererString        = "NVIDIA";
    const char* kIntelRendererString         = "Intel";
    bool        are_gl_functions_initialized = false;
    LibHandle   gl_lib_handle                = nullptr;
#ifdef GLES
    LibHandle gl_es_lib_handle = nullptr;
#endif
    bool are_supported_extensions_queried = false;

    std::map<GLExtension, Supported> gl_extensions_map = {{std::string("GL_AMD_performance_monitor"), false},
                                                          {std::string("GL_ARB_timer_query"), false},
                                                          {std::string("GL_EXT_disjoint_timer_query"), false},
                                                          {std::string("GL_AMD_debug_output"), false},
                                                          {std::string("GLX_MESA_query_renderer"), false},
                                                          {std::string("WGL_AMD_gpu_association"), false},
                                                          {std::string("GLX_AMD_GPU_association"), false}};

    const int kGlDriverVerWithOnlyGcnSupport          = 13452;  ///< GL driver version where pre-GCN hardware was dropped.
    const int kGlDriverVerWithLinuxStableClockSupport = 13562;  ///< GL driver version where stable clocks are working on Linux.
    const int kGlDriverVerWithGpinCounters            = 13565;  ///< GL driver version where GPIN counters have been validated.

    void CheckExtension(const char* ext_name)
    {
        if ((nullptr != ext_name) && (gl_extensions_map.find(ext_name) != gl_extensions_map.end()))
        {
            gl_extensions_map[ext_name] = true;
        }
    }

    bool CheckForGlError(const std::string& error_message)
    {
        bool   error_found = false;
        GLenum gl_error    = ogl_utils::ogl_get_error();

        if (gl_error != GL_NO_ERROR)
        {
            switch (gl_error)
            {
            case GL_INVALID_ENUM:
            case GL_INVALID_VALUE:
            case GL_INVALID_OPERATION:
            case GL_STACK_OVERFLOW:
            case GL_STACK_UNDERFLOW:
            case GL_OUT_OF_MEMORY:
                error_found = true;
                GPA_LOG_ERROR(error_message.c_str());
                break;

            default:
                assert(gl_error == GL_NO_ERROR);
                break;
            }
        }

        return error_found;
    }

    void QuerySupportedPlatformExtensions()
    {
// On Linux we must enumerate the GLX extensions separately, as they will not be included in the list of GL_EXTENSIONS queried by ogl_get_string_i
#ifdef _LINUX
#ifndef GLES
        if (ogl_x_get_client_string == nullptr)
        {
            LOAD_LIBRARY_SYMBOL(ogl_x_get_client_string, glXGetClientString);
            if (ogl_x_get_client_string == nullptr)
            {
                GPA_LOG_ERROR("Could not load glXGetClientString; unable to enumerate GLX extensions.");
                return;
            }
        }

        // We open up an additional connection to the X server here to avoid passing around the X server connection used by the app itself.
        Display* display = XOpenDisplay(nullptr);
        if (display == nullptr)
        {
            GPA_LOG_ERROR("Failed to open connection to the X server; unable to enumerate GLX extensions.");
            return;
        }

        const char* ext_string = ogl_x_get_client_string(display, GLX_EXTENSIONS);
        if (ext_string == nullptr)
        {
            GPA_LOG_ERROR("Failed to retrieve extension string; unable to enumerate GLX extensions.");
            return;
        }

        const std::string glx_extensions  = ext_string;
        std::size_t       idx_entry_start = 0;

        // Walk through the extension string, which will be a list of space-separated identifiers
        do
        {
            if (idx_entry_start >= glx_extensions.length())
            {
                break;
            }

            std::size_t idx_entry_end = glx_extensions.find_first_of(' ', idx_entry_start);

            if (idx_entry_end != std::string::npos)
            {
                std::string ext_name = glx_extensions.substr(idx_entry_start, idx_entry_end - idx_entry_start);
                ++idx_entry_end;

                CheckExtension(ext_name.c_str());
            }

            idx_entry_start = idx_entry_end;
        } while (idx_entry_start != std::string::npos);

        XCloseDisplay(display);
#endif
#endif
    }
}  // namespace ogl_utils

bool ogl_utils::LoadGl()
{
    if (nullptr == gl_lib_handle)
    {
#ifdef _WIN32
#ifndef GLES
        gl_lib_handle = LoadLibraryA("opengl32.dll");
#else
        gl_lib_handle = LoadLibraryA("libEGL.dll");
#endif
#else
#ifndef GLES
        gl_lib_handle = dlopen("libGL.so", RTLD_LAZY);
#else
        gl_es_lib_handle = dlopen("libEGL.so", RTLD_NOW);

        if (nullptr == gl_lib_handle)
        {
            gl_lib_handle = dlopen("libGLESv3.so", RTLD_NOW);

            if (nullptr == gl_lib_handle)
            {
                gl_lib_handle = dlopen("libGLESv2.so", RTLD_NOW);

                if (nullptr == gl_lib_handle)
                {
                    gl_lib_handle = dlopen("libGLES.so", RTLD_NOW);
                }
            }
        }
#endif
#endif
    }

#ifndef GLES
    return nullptr != gl_lib_handle;
#else
    return nullptr != gl_lib_handle && nullptr != gl_es_lib_handle;
#endif
}

void ogl_utils::QuerySupportedExtensions()
{
    if (nullptr != ogl_get_string && !are_supported_extensions_queried)
    {
        GPA_LOG_MESSAGE("Using OpenGL 1.x method to query extensions.");
        GLint num_extensions = 0;
        ogl_get_integer_v(GL_NUM_EXTENSIONS, &num_extensions);

        if (nullptr != ogl_get_string_i)
        {
            for (GLint i = 0; i < num_extensions; i++)
            {
                const char* extension = reinterpret_cast<const char*>(ogl_get_string_i(GL_EXTENSIONS, i));
                CheckExtension(extension);
            }
        }

        QuerySupportedPlatformExtensions();

        are_supported_extensions_queried = true;
    }
}

bool ogl_utils::InitializeGlCoreFunctions()
{
    if (LoadGl())
    {
        // Load GL core functions.
        LOAD_LIBRARY_SYMBOL(ogl_flush, glFlush);
        LOAD_LIBRARY_SYMBOL(ogl_get_string, glGetString);
        LOAD_LIBRARY_SYMBOL(ogl_get_integer_v, glGetIntegerv);
        LOAD_LIBRARY_SYMBOL(ogl_get_error, glGetError);

        if (nullptr == ogl_flush || nullptr == ogl_get_string || nullptr == ogl_get_integer_v || nullptr == ogl_get_error)
        {
            GPA_LOG_MESSAGE("Unable to Initialize GL core functions.");
            return false;
        }

        return true;
    }

    return false;
}

bool ogl_utils::InitCtxAmdPerfExtFunctions()
{
    if (LoadGl())
    {
        if (nullptr == GET_PROC_ADDRESS_FUNC)
        {
#ifndef GLES
            GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(gl_lib_handle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#else
            GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(gl_es_lib_handle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#endif
        }

        // Load AMD Perf extension functions.
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_groups_amd, PFNGLGETPERFMONITORGROUPSAMDPROC, "glGetPerfMonitorGroupsAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_counters_amd, PFNGLGETPERFMONITORCOUNTERSAMDPROC, "glGetPerfMonitorCountersAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_group_string_amd, PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, "glGetPerfMonitorGroupStringAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_counter_string_amd, PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, "glGetPerfMonitorCounterStringAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_counter_info_amd, PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, "glGetPerfMonitorCounterInfoAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_gen_perf_monitors_amd, PFNGLGENPERFMONITORSAMDPROC, "glGenPerfMonitorsAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_delete_perf_monitors_amd, PFNGLDELETEPERFMONITORSAMDPROC, "glDeletePerfMonitorsAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_select_perf_monitor_counters_amd, PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, "glSelectPerfMonitorCountersAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_begin_perf_monitor_amd, PFNGLBEGINPERFMONITORAMDPROC, "glBeginPerfMonitorAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_end_perf_monitor_amd, PFNGLENDPERFMONITORAMDPROC, "glEndPerfMonitorAMD");
        GET_CONTEXT_PROC_ADDRESS(ogl_get_perf_monitor_counter_data_amd, PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, "glGetPerfMonitorCounterDataAMD");

        return (nullptr != ogl_get_perf_monitor_groups_amd && nullptr != ogl_get_perf_monitor_counters_amd &&
                nullptr != ogl_get_perf_monitor_group_string_amd && nullptr != ogl_get_perf_monitor_counter_string_amd &&
                nullptr != ogl_get_perf_monitor_counter_info_amd && nullptr != ogl_gen_perf_monitors_amd && nullptr != ogl_delete_perf_monitors_amd &&
                nullptr != ogl_select_perf_monitor_counters_amd && nullptr != ogl_begin_perf_monitor_amd && nullptr != ogl_end_perf_monitor_amd &&
                nullptr != ogl_get_perf_monitor_counter_data_amd);
    }

    return false;
}

bool ogl_utils::InitPlatformExtFunctions()
{
#ifdef _LINUX
#ifndef GLES
    if (LoadGl())
    {
        if (nullptr == GET_PROC_ADDRESS_FUNC)
        {
            GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(gl_lib_handle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
        }
        GET_CONTEXT_PROC_ADDRESS(ogl_x_query_current_renderer_integer_mesa, PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA, "glXQueryCurrentRendererIntegerMESA");
        return nullptr != ogl_x_query_current_renderer_integer_mesa;
    }
    else
    {
        return false;
    }
#endif
#endif
    return true;
}

bool ogl_utils::InitializeGlFunctions()
{
    if (are_gl_functions_initialized)
    {
        return true;
    }

    bool ret_val = true;

    if (!LoadGl())
    {
        GPA_LOG_ERROR("Unable to get handle of OpenGL module.");
        return false;
    }

#ifndef GLES
    GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(gl_lib_handle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#else
    GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(gl_es_lib_handle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#endif

    if (!InitializeGlCoreFunctions())
    {
        GPA_LOG_ERROR("Unable to Initialize required GL functions.");
        return false;
    }

    GET_CONTEXT_PROC_ADDRESS(ogl_get_string_i, PFNGLGETSTRINGIPROC, "glGetStringi");

    QuerySupportedExtensions();

    bool perf_mon_ext_found    = gl_extensions_map["GL_AMD_performance_monitor"];
    bool timer_query_ext_found = gl_extensions_map["GL_ARB_timer_query"] || gl_extensions_map["GL_EXT_disjoint_timer_query"];

    if (!InitCtxAmdPerfExtFunctions())
    {
        if (perf_mon_ext_found)
        {
            GPA_LOG_ERROR("The GL_AMD_performance_monitor extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            GPA_LOG_ERROR("The GL_AMD_performance_monitor extension is not exposed by the driver.");
        }

        const GLubyte* renderer = ogl_get_string(GL_RENDERER);

        if (nullptr == renderer)
        {
            // Return error if unable to retrieve renderer.
            ret_val = false;
        }
        else if (strstr(reinterpret_cast<const char*>(renderer), kAtiRendererString) == 0 ||
                 strstr(reinterpret_cast<const char*>(renderer), kAmdRendererString) == 0)
        {
            // Return error if AMD extension is missing on AMD hardware.
            ret_val = false;
        }
    }

    GET_CONTEXT_PROC_ADDRESS(ogl_set_gpa_device_clock_mode_amd_x, PFN_GL_SETGPADEVICECLOCKMODEAMDX, "glSetGpaDeviceClockModeAMDX");
    GET_CONTEXT_PROC_ADDRESS(ogl_get_query_object_ui_64_v_ext, PFNGLGETQUERYOBJECTUI64VPROC, "glGetQueryObjectui64v");

#if defined(GLES) && !defined(WIN32)
    GET_CONTEXT_PROC_ADDRESS(ogl_get_query_objective_iv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectivEXT");
    GET_CONTEXT_PROC_ADDRESS(ogl_gen_queries, PFNGLGENQUERIESPROC, "glGenQueriesEXT");
    GET_CONTEXT_PROC_ADDRESS(ogl_delete_queries, PFNGLDELETEQUERIESPROC, "glDeleteQueriesEXT");
    GET_CONTEXT_PROC_ADDRESS(ogl_query_counter, PFNGLQUERYCOUNTERPROC, "glQueryCounterEXT");
#else
    GET_CONTEXT_PROC_ADDRESS(ogl_get_query_objective_iv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectiv");
    GET_CONTEXT_PROC_ADDRESS(ogl_gen_queries, PFNGLGENQUERIESPROC, "glGenQueries");
    GET_CONTEXT_PROC_ADDRESS(ogl_delete_queries, PFNGLDELETEQUERIESPROC, "glDeleteQueries");
    GET_CONTEXT_PROC_ADDRESS(ogl_query_counter, PFNGLQUERYCOUNTERPROC, "glQueryCounter");
#endif

#ifdef GLES
#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif
#endif

    if (nullptr == ogl_get_query_objective_iv)
    {
        GPA_LOG_MESSAGE("glGetQueryObjectiv entry point not exposed by the driver.");
    }

    if (nullptr == ogl_gen_queries)
    {
        GPA_LOG_MESSAGE("glGenQueries entry point not exposed by the driver.");
    }

    if (nullptr == ogl_delete_queries)
    {
        GPA_LOG_MESSAGE("glDeleteQueries entry point not exposed by the driver.");
    }

    if (nullptr == ogl_query_counter)
    {
        GPA_LOG_MESSAGE("glQueryCounter entry point not exposed by the driver.");
    }

    if (nullptr == ogl_get_query_object_ui_64_v_ext)
    {
        GPA_LOG_MESSAGE("glGetQueryObjectui64vEXT entry point not exposed by the driver.");
    }

    if (nullptr == ogl_get_string_i || nullptr == ogl_get_query_object_ui_64_v_ext || nullptr == ogl_get_query_objective_iv || nullptr == ogl_gen_queries ||
        nullptr == ogl_delete_queries || nullptr == ogl_query_counter)
    {
        if (timer_query_ext_found)
        {
#ifndef GLES
            GPA_LOG_ERROR("The GL_ARB_timer_query extension is exposed by the driver, but the not all entry points are available.");
#else
            GPA_LOG_ERROR("The GL_EXT_disjoint_timer_query extension is exposed by the driver, but the entry points are not available.");
#endif
        }
        else
        {
#ifndef GLES
            GPA_LOG_ERROR("The GL_ARB_timer_query extension is not exposed by the driver.");
#else
            GPA_LOG_ERROR("The GL_EXT_disjoint_timer_query extension is not exposed by the driver.");
#endif
        }

        ret_val = false;
    }

#ifdef DEBUG_GL_ERRORS
    bool debug_output_ext_found = gl_extensions_map["GL_AMD_debug_output"];
    // GL_AMD_debug_output extension.
    GET_CONTEXT_PROC_ADDRESS(ogl_debug_message_control_arb, PFN_OGL_GLDEBUGMESSAGECONTROLARB, "glDebugMessageControlAMD");
    GET_CONTEXT_PROC_ADDRESS(ogl_debug_message_insert_arb, PFN_OGL_GLDEBUGMESSAGEINSERTARB, "glDebugMessageInsertAMD");
    GET_CONTEXT_PROC_ADDRESS(ogl_debug_message_callback_arb, PFN_OGL_GLDEBUGMESSAGECALLBACKARB, "glDebugMessageCallbackAMD");
    GET_CONTEXT_PROC_ADDRESS(ogl_get_debug_message_log_arb, PFN_OGL_GLGETDEBUGMESSAGELOGARB, "glGetDebugMessageLogAMD");

    if (nullptr == ogl_debug_message_control_arb || nullptr == ogl_debug_message_insert_arb || nullptr == ogl_debug_message_callback_arb ||
        nullptr == ogl_get_debug_message_log_arb)
    {
        if (debug_output_ext_found)
        {
            GPA_LOG_MESSAGE("The GL_AMD_debug_output extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            // This interface is not required, but does help improve error logging, so allow the code
            // to continue if this is not available.
            GPA_LOG_MESSAGE("The GL_AMD_debug_output extension is not exposed by the driver.");
        }
    }

#endif

#ifndef WIN32
    bool mesa_query_renderer_ext_found = gl_extensions_map["GLX_MESA_query_renderer"];
    if (!InitPlatformExtFunctions())
    {
        if (nullptr == ogl_x_query_current_renderer_integer_mesa)
        {
            if (mesa_query_renderer_ext_found)
            {
                GPA_LOG_MESSAGE("The GLX_MESA_query_renderer extension is exposed by the driver, but not all entry points are available.");
            }
            else
            {
                GPA_LOG_MESSAGE("The GLX_MESA_query_renderer extension is not exposed by the driver.");
            }
        }
    }

#endif

    if (nullptr == ogl_set_gpa_device_clock_mode_amd_x)
    {
        GPA_LOG_MESSAGE("The glSetGpaDeviceClockModeAMDX extension entry point is not exposed by the driver.");
    }

    are_gl_functions_initialized = ret_val;
    return ret_val;
}
