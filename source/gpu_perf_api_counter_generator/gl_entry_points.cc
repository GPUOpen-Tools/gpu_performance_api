//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL entry points
//==============================================================================

#include "gpa_common_defs.h"
#include "gl_entry_points.h"
#include "logging.h"

namespace oglUtils
{
    decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC = nullptr;

    decltype(glFlush)*       _oglFlush       = nullptr;
    decltype(glGetString)*   _oglGetString   = nullptr;
    decltype(glGetIntegerv)* _oglGetIntegerv = nullptr;
    decltype(glGetError)*    _oglGetError    = nullptr;
    PFNGLGETSTRINGIPROC      _oglGetStringi  = nullptr;

    PFNGLGETQUERYOBJECTIVPROC       _oglGetQueryObjectiv       = nullptr;
    PFNGLGENQUERIESPROC             _oglGenQueries             = nullptr;
    PFNGLDELETEQUERIESPROC          _oglDeleteQueries          = nullptr;
    PFNGLQUERYCOUNTERPROC           _oglQueryCounter           = nullptr;
    PFNGLGETQUERYOBJECTUI64VEXTPROC _oglGetQueryObjectui64vEXT = nullptr;

    /// AMD perf monitor extensions
    PFNGLGETPERFMONITORGROUPSAMDPROC        _oglGetPerfMonitorGroupsAMD        = nullptr;
    PFNGLGETPERFMONITORCOUNTERSAMDPROC      _oglGetPerfMonitorCountersAMD      = nullptr;
    PFNGLGETPERFMONITORGROUPSTRINGAMDPROC   _oglGetPerfMonitorGroupStringAMD   = nullptr;
    PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC _oglGetPerfMonitorCounterStringAMD = nullptr;
    PFNGLGETPERFMONITORCOUNTERINFOAMDPROC   _oglGetPerfMonitorCounterInfoAMD   = nullptr;
    PFNGLGENPERFMONITORSAMDPROC             _oglGenPerfMonitorsAMD             = nullptr;
    PFNGLDELETEPERFMONITORSAMDPROC          _oglDeletePerfMonitorsAMD          = nullptr;
    PFNGLSELECTPERFMONITORCOUNTERSAMDPROC   _oglSelectPerfMonitorCountersAMD   = nullptr;
    PFNGLBEGINPERFMONITORAMDPROC            _oglBeginPerfMonitorAMD            = nullptr;
    PFNGLENDPERFMONITORAMDPROC              _oglEndPerfMonitorAMD              = nullptr;
    PFNGLGETPERFMONITORCOUNTERDATAAMDPROC   _oglGetPerfMonitorCounterDataAMD   = nullptr;

#ifdef DEBUG_GL_ERRORS
    // Function pointers for the GL_ARB_debug_output extension - used to improve error reporting.
    PFN_OGL_GLDEBUGMESSAGECONTROLARB  _oglDebugMessageControlARB  = nullptr;
    PFN_OGL_GLDEBUGMESSAGEINSERTARB   _oglDebugMessageInsertARB   = nullptr;
    PFN_OGL_GLDEBUGMESSAGECALLBACKARB _oglDebugMessageCallbackARB = nullptr;
    PFN_OGL_GLGETDEBUGMESSAGELOGARB   _oglGetDebugMessageLogARB   = nullptr;
#endif

    // Function pointers for GLX_MESA_query_renderer extension
    PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA _oglXQueryCurrentRendererIntegerMESA = nullptr;

    PFN_GL_SETGPADEVICECLOCKMODEAMDX _oglSetGpaDeviceClockModeAMDX = nullptr;

    const char* s_pAMDRenderer                = "AMD";
    const char* s_pRadeonRenderer             = "Radeon";
    const char* s_pATIRenderer                = "ATI";
    const char* s_pNVIDIARenderer             = "NVIDIA";
    const char* s_pIntelRenderer              = "Intel";
    bool        s_areGLFunctionsInitialized   = false;
    LibHandle   s_glLibHandle                 = nullptr;
#ifdef GLES
    LibHandle   s_eglLibHandle                = nullptr;
#endif
    bool        s_isSupportedExtensionQueried = false;

    std::map<GLExtension, Supported> s_glExtensions = {{std::string("GL_AMD_performance_monitor"), false},
                                                       {std::string("GL_ARB_timer_query"), false},
                                                       {std::string("GL_EXT_disjoint_timer_query"), false},
                                                       {std::string("GL_AMD_debug_output"), false},
                                                       {std::string("GLX_MESA_query_renderer"), false},
                                                       {std::string("WGL_AMD_gpu_association"), false},
                                                       {std::string("GLX_AMD_GPU_association"), false}};

    const int s_GL_DRIVER_VER_WITH_ONLY_GCN_SUPPORT           = 13452;  ///< GL driver version where pre-GCN hardware was dropped
    const int s_GL_DRIVER_VER_WITH_LINUX_STABLE_CLOCK_SUPPORT = 13562;  ///< GL driver version where stable clocks are working on Linux
    const int s_GL_DRIVER_VER_WITH_GPIN_COUNTERS              = 13565;  ///< GL driver version where GPIN counters have been validated

    bool CheckForGLError(const std::string& onErrorMessage)
    {
        bool   errorFound = false;
        GLenum glError    = oglUtils::_oglGetError();

        if (glError != GL_NO_ERROR)
        {
            switch (glError)
            {
            case GL_INVALID_ENUM:
            case GL_INVALID_VALUE:
            case GL_INVALID_OPERATION:
            case GL_STACK_OVERFLOW:
            case GL_STACK_UNDERFLOW:
            case GL_OUT_OF_MEMORY:
                errorFound = true;
                GPA_LogError(onErrorMessage.c_str());
                break;

            default:
                assert(glError == GL_NO_ERROR);
                break;
            }
        }

        return errorFound;
    }
}  // namespace oglUtils



bool oglUtils::LoadGL()
{
    if (nullptr == s_glLibHandle)
    {
#ifdef _WIN32
#ifndef GLES
        s_glLibHandle = LoadLibraryA("opengl32.dll");
#else
        s_glLibHandle = LoadLibraryA("libEGL.dll");
#endif
#else
#ifndef GLES
        s_glLibHandle = dlopen("libGL.so", RTLD_LAZY);
#else
        s_eglLibHandle = dlopen("libEGL.so", RTLD_NOW);

        if(nullptr == s_glLibHandle)
        {
            s_glLibHandle = dlopen("libGLESv3.so", RTLD_NOW);

            if(nullptr == s_glLibHandle)
            {
                s_glLibHandle = dlopen("libGLESv2.so", RTLD_NOW);

                if(nullptr == s_glLibHandle)
                {
                    s_glLibHandle = dlopen("libGLES.so", RTLD_NOW);
                }
            }
        }
#endif
#endif
    }

#ifndef GLES
    return nullptr != s_glLibHandle;
#else
    return nullptr != s_glLibHandle && nullptr != s_eglLibHandle;
#endif
}

void oglUtils::QuerySupportedExtensions()
{
    if (nullptr != _oglGetString && !s_isSupportedExtensionQueried)
    {
        GPA_LogMessage("Using OpenGL 1.x method to query extensions.");
        GLint numExtensions = 0;
        _oglGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

        if(nullptr != _oglGetStringi)
        {
            for (GLint i = 0; i < numExtensions; i++)
            {
                const char* pExtension = reinterpret_cast<const char*>(_oglGetStringi(GL_EXTENSIONS, i));

                if ((nullptr != pExtension) && (s_glExtensions.find(pExtension) != s_glExtensions.end()))
                {
                    s_glExtensions[pExtension] = true;
                }
            }
        }

        s_isSupportedExtensionQueried = true;
    }
}

bool oglUtils::InitializeGLCoreFunctions()
{
    if (LoadGL())
    {
        // Load GL core functions
        LOAD_LIBRARY_SYMBOL(_oglFlush, glFlush);
        LOAD_LIBRARY_SYMBOL(_oglGetString, glGetString);
        LOAD_LIBRARY_SYMBOL(_oglGetIntegerv, glGetIntegerv);
        LOAD_LIBRARY_SYMBOL(_oglGetError, glGetError);

        if (nullptr == _oglFlush ||
            nullptr == _oglGetString ||
            nullptr == _oglGetIntegerv ||
            nullptr == _oglGetError)
        {
            GPA_LogMessage("Unable to Initialize GL core functions.");
            return false;
        }

        return true;
    }

    return false;
}

bool oglUtils::InitCtxAmdPerfExtFunctions()
{
    if (LoadGL())
    {
        if(nullptr == GET_PROC_ADDRESS_FUNC)
        {
#ifndef GLES
            GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(s_glLibHandle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#else
            GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(s_eglLibHandle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#endif
        }

        // Load AMD Perf extension functions
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorGroupsAMD, PFNGLGETPERFMONITORGROUPSAMDPROC, "glGetPerfMonitorGroupsAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorCountersAMD, PFNGLGETPERFMONITORCOUNTERSAMDPROC, "glGetPerfMonitorCountersAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorGroupStringAMD, PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, "glGetPerfMonitorGroupStringAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorCounterStringAMD, PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, "glGetPerfMonitorCounterStringAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorCounterInfoAMD, PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, "glGetPerfMonitorCounterInfoAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGenPerfMonitorsAMD, PFNGLGENPERFMONITORSAMDPROC, "glGenPerfMonitorsAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglDeletePerfMonitorsAMD, PFNGLDELETEPERFMONITORSAMDPROC, "glDeletePerfMonitorsAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglSelectPerfMonitorCountersAMD, PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, "glSelectPerfMonitorCountersAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglBeginPerfMonitorAMD, PFNGLBEGINPERFMONITORAMDPROC, "glBeginPerfMonitorAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglEndPerfMonitorAMD, PFNGLENDPERFMONITORAMDPROC, "glEndPerfMonitorAMD");
        GET_CONTEXT_PROC_ADDRESS(_oglGetPerfMonitorCounterDataAMD, PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, "glGetPerfMonitorCounterDataAMD");

        return (nullptr != _oglGetPerfMonitorGroupsAMD &&
                nullptr != _oglGetPerfMonitorCountersAMD &&
                nullptr != _oglGetPerfMonitorGroupStringAMD &&
                nullptr != _oglGetPerfMonitorCounterStringAMD &&
                nullptr != _oglGetPerfMonitorCounterInfoAMD &&
                nullptr != _oglGenPerfMonitorsAMD &&
                nullptr != _oglDeletePerfMonitorsAMD &&
                nullptr != _oglSelectPerfMonitorCountersAMD &&
                nullptr != _oglBeginPerfMonitorAMD &&
                nullptr != _oglEndPerfMonitorAMD && 
                nullptr != _oglGetPerfMonitorCounterDataAMD);
    }

    return false;
}

bool oglUtils::InitializeGLFunctions()
{
    if (s_areGLFunctionsInitialized)
    {
        return true;
    }

    bool retVal = true;

    if (!LoadGL())
    {
        GPA_LogError("Unable to get handle of OpenGL module.");
        return false;
    }

#ifndef GLES
    GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(s_glLibHandle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#else
    GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(s_eglLibHandle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));
#endif

    if (!InitializeGLCoreFunctions())
    {
        GPA_LogError("Unable to Initialize required GL functions.");
        return false;
    }

    GET_CONTEXT_PROC_ADDRESS(_oglGetStringi, PFNGLGETSTRINGIPROC, "glGetStringi");

    QuerySupportedExtensions();

    bool bPerfMonExtFound    = s_glExtensions["GL_AMD_performance_monitor"];
    bool bTimerQueryExtFound = s_glExtensions["GL_ARB_timer_query"] || s_glExtensions["GL_EXT_disjoint_timer_query"];

    if (!InitCtxAmdPerfExtFunctions())
    {
        if (bPerfMonExtFound)
        {
            GPA_LogError("The GL_AMD_performance_monitor extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            GPA_LogError("The GL_AMD_performance_monitor extension is not exposed by the driver.");
        }

        const GLubyte* pRenderer = _oglGetString(GL_RENDERER);

        if (nullptr == pRenderer)
        {
            retVal = false;  // return error if unable to retrieve renderer;
        }
        else if (strstr(reinterpret_cast<const char*>(pRenderer), s_pATIRenderer) == 0 || strstr(reinterpret_cast<const char*>(pRenderer), s_pAMDRenderer) == 0)
        {
            retVal = false;  // return error if AMD extension is missing on AMD hardware
        }
    }

    GET_CONTEXT_PROC_ADDRESS(_oglSetGpaDeviceClockModeAMDX, PFN_GL_SETGPADEVICECLOCKMODEAMDX, "glSetGpaDeviceClockModeAMDX");
    GET_CONTEXT_PROC_ADDRESS(_oglGetQueryObjectui64vEXT, PFNGLGETQUERYOBJECTUI64VPROC, "glGetQueryObjectui64v");

#if defined(GLES) && !defined(WIN32)
    GET_CONTEXT_PROC_ADDRESS(_oglGetQueryObjectiv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectivEXT");
    GET_CONTEXT_PROC_ADDRESS(_oglGenQueries, PFNGLGENQUERIESPROC, "glGenQueriesEXT");
    GET_CONTEXT_PROC_ADDRESS(_oglDeleteQueries, PFNGLDELETEQUERIESPROC, "glDeleteQueriesEXT");
    GET_CONTEXT_PROC_ADDRESS(_oglQueryCounter, PFNGLQUERYCOUNTERPROC, "glQueryCounterEXT");
#else
    GET_CONTEXT_PROC_ADDRESS(_oglGetQueryObjectiv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectiv");
    GET_CONTEXT_PROC_ADDRESS(_oglGenQueries, PFNGLGENQUERIESPROC, "glGenQueries");
    GET_CONTEXT_PROC_ADDRESS(_oglDeleteQueries, PFNGLDELETEQUERIESPROC, "glDeleteQueries");
    GET_CONTEXT_PROC_ADDRESS(_oglQueryCounter, PFNGLQUERYCOUNTERPROC, "glQueryCounter");
#endif

#ifdef GLES
#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif  // GL_TIMESTAMP
#endif  // GLES

    if (nullptr == _oglGetQueryObjectiv)
    {
        GPA_LogMessage("glGetQueryObjectiv entry point not exposed by the driver.");
    }

    if (nullptr == _oglGenQueries)
    {
        GPA_LogMessage("glGenQueries entry point not exposed by the driver.");
    }

    if (nullptr == _oglDeleteQueries)
    {
        GPA_LogMessage("glDeleteQueries entry point not exposed by the driver.");
    }

    if (nullptr == _oglQueryCounter)
    {
        GPA_LogMessage("glQueryCounter entry point not exposed by the driver.");
    }

    if (nullptr == _oglGetQueryObjectui64vEXT)
    {
        GPA_LogMessage("glGetQueryObjectui64vEXT entry point not exposed by the driver.");
    }

    if (nullptr == _oglGetStringi || nullptr == _oglGetQueryObjectui64vEXT || nullptr == _oglGetQueryObjectiv || nullptr == _oglGenQueries ||
        nullptr == _oglDeleteQueries || nullptr == _oglQueryCounter)
    {
        if (bTimerQueryExtFound)
        {
#ifndef GLES
            GPA_LogError("The GL_ARB_timer_query extension is exposed by the driver, but the not all entry points are available.");
#else
            GPA_LogError("The GL_EXT_disjoint_timer_query extension is exposed by the driver, but the entry points are not available.");
#endif
        }
        else
        {
#ifndef GLES
            GPA_LogError("The GL_ARB_timer_query extension is not exposed by the driver.");
#else
            GPA_LogError("The GL_EXT_disjoint_timer_query extension is not exposed by the driver.");
#endif
        }

        retVal = false;
    }

#ifdef DEBUG_GL_ERRORS
    bool bDebugOutputExtFound = s_glExtensions["GL_AMD_debug_output"];
    // GL_AMD_debug_output extension
    GET_CONTEXT_PROC_ADDRESS(_oglDebugMessageControlARB, PFN_OGL_GLDEBUGMESSAGECONTROLARB, "glDebugMessageControlAMD");
    GET_CONTEXT_PROC_ADDRESS(_oglDebugMessageInsertARB, PFN_OGL_GLDEBUGMESSAGEINSERTARB, "glDebugMessageInsertAMD");
    GET_CONTEXT_PROC_ADDRESS(_oglDebugMessageCallbackARB, PFN_OGL_GLDEBUGMESSAGECALLBACKARB, "glDebugMessageCallbackAMD");
    GET_CONTEXT_PROC_ADDRESS(_oglGetDebugMessageLogARB, PFN_OGL_GLGETDEBUGMESSAGELOGARB, "glGetDebugMessageLogAMD");

    if (nullptr == _oglDebugMessageControlARB || nullptr == _oglDebugMessageInsertARB || nullptr == _oglDebugMessageCallbackARB ||
        nullptr == _oglGetDebugMessageLogARB)
    {
        if (bDebugOutputExtFound)
        {
            GPA_LogMessage("The GL_AMD_debug_output extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            // this interface is not required, but does help improve error logging, so allow the code
            // to continue if this is not available.
            GPA_LogMessage("The GL_AMD_debug_output extension is not exposed by the driver.");
        }
    }

#endif

#ifndef WIN32
    bool bMesaQueryRendererExtFound = s_glExtensions["GLX_MESA_query_renderer"];

    if (nullptr == _oglXQueryCurrentRendererIntegerMESA)
    {
        if (bMesaQueryRendererExtFound)
        {
            GPA_LogMessage("The GLX_MESA_query_renderer extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            GPA_LogMessage("The GLX_MESA_query_renderer extension is not exposed by the driver.");
        }
    }

#endif

    if (nullptr == _oglSetGpaDeviceClockModeAMDX)
    {
        GPA_LogMessage("The glSetGpaDeviceClockModeAMDX extension entry point is not exposed by the driver.");
    }

    s_areGLFunctionsInitialized = retVal;
    return retVal;
}
