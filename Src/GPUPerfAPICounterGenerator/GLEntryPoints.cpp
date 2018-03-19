//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL entry points
//==============================================================================


#include "GLEntryPoints.h"
#include "Logging.h"

#ifdef _LINUX
    #include <dlfcn.h>
#endif

namespace oglUtils
{
#ifndef GLES

    #ifdef _WIN32
        decltype(wglGetProcAddress)* _wglGetProcAddress = nullptr;
    #endif

    #ifdef _LINUX
        decltype(glXGetProcAddressARB)* _glXGetProcAddressARB = nullptr;
    #endif

#else
    decltype(eglGetProcAddress)* _eglGetProcAddress = nullptr;
#endif

decltype(glFlush)*                      _oglFlush = nullptr;
decltype(glGetString)*                  _oglGetString = nullptr;
decltype(glGetIntegerv)*                _oglGetIntegerv = nullptr;
decltype(glGetError)*                   _oglGetError = nullptr;
#ifdef _WIN32
    decltype(wglGetCurrentContext)*         _wglGetCurrentContext = nullptr;
#endif
PFNGLGETPERFMONITORGROUPSAMDPROC        _oglGetPerfMonitorGroupsAMD = nullptr;
PFNGLGETPERFMONITORCOUNTERSAMDPROC      _oglGetPerfMonitorCountersAMD = nullptr;
PFNGLGETPERFMONITORGROUPSTRINGAMDPROC   _oglGetPerfMonitorGroupStringAMD = nullptr;
PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC _oglGetPerfMonitorCounterStringAMD = nullptr;
PFNGLGETPERFMONITORCOUNTERINFOAMDPROC   _oglGetPerfMonitorCounterInfoAMD = nullptr;
PFNGLGENPERFMONITORSAMDPROC             _oglGenPerfMonitorsAMD = nullptr;
PFNGLDELETEPERFMONITORSAMDPROC          _oglDeletePerfMonitorsAMD = nullptr;
PFNGLSELECTPERFMONITORCOUNTERSAMDPROC   _oglSelectPerfMonitorCountersAMD = nullptr;
PFNGLBEGINPERFMONITORAMDPROC            _oglBeginPerfMonitorAMD = nullptr;
PFNGLENDPERFMONITORAMDPROC              _oglEndPerfMonitorAMD = nullptr;
PFNGLGETPERFMONITORCOUNTERDATAAMDPROC   _oglGetPerfMonitorCounterDataAMD = nullptr;

// Function pointers for glQuery calls (needed for GPUTime via timer_query extension)
PFNGLGETQUERYOBJECTUI64VEXTPROC         _oglGetQueryObjectui64vEXT = nullptr;
PFNGLGETQUERYOBJECTUI64VPROC            _oglGetQueryObjectui64v = nullptr;
PFNGLGETQUERYOBJECTIVPROC               _oglGetQueryObjectiv = nullptr;
PFNGLGENQUERIESPROC                     _oglGenQueries = nullptr;
PFNGLDELETEQUERIESPROC                  _oglDeleteQueries = nullptr;
PFNGLQUERYCOUNTERPROC                   _oglQueryCounter = nullptr;

// Function pointers for glGetStringi call to query extension strings in 3.x
PFNGLGETSTRINGIPROC                     _oglGetStringi = nullptr;

#ifdef DEBUG_GL_ERRORS
    // Function pointers for the GL_ARB_debug_output extension - used to improve error reporting.
    PFN_OGL_GLDEBUGMESSAGECONTROLARB    _oglDebugMessageControlARB = nullptr;
    PFN_OGL_GLDEBUGMESSAGEINSERTARB     _oglDebugMessageInsertARB = nullptr;
    PFN_OGL_GLDEBUGMESSAGECALLBACKARB   _oglDebugMessageCallbackARB = nullptr;
    PFN_OGL_GLGETDEBUGMESSAGELOGARB     _oglGetDebugMessageLogARB = nullptr;
#endif

// Function pointers for GLX_MESA_query_renderer extension
PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA _oglXQueryCurrentRendererIntegerMESA = nullptr;

const char* s_pAMDRenderer = "AMD";
const char* s_pRadeonRenderer = "Radeon";
const char* s_pATIRenderer = "ATI";
const char* s_pNVIDIARenderer = "NVIDIA";
const char* s_pIntelRenderer = "Intel";
bool s_areGLFunctionsInitialized = false;
}

bool oglUtils::InitializeGLFunctions()
{
    if (s_areGLFunctionsInitialized)
    {
        return true;
    }

    bool retVal = true;

    bool bPerfMonExtFound = false;
    bool bTimerQueryExtFound = false;
    bool bDebugOutputExtFound = false;
    bool bMesaQueryRendererExtFound = false;

#ifdef _WIN32
    HMODULE module = LoadLibraryA("opengl32.dll");
#ifdef GLES
    HMODULE eglmodule = LoadLibraryA("libEGL.dll");
#endif
#else
    void* module = dlopen("libGL.so", RTLD_LAZY);
#ifdef GLES
    void* eglmodule = dlopen("libEGL.so", RTLD_LAZY);
#endif
#endif

    if (nullptr == module)
    {
        GPA_LogError("Unable to get handle of OpenGL module.");
        return false;
    }

#ifndef GLES

#ifdef _WIN32
    _wglGetCurrentContext = reinterpret_cast<decltype(wglGetCurrentContext)*>(GetProcAddress(module, "wglGetCurrentContext"));

    _wglGetProcAddress = reinterpret_cast<decltype(wglGetProcAddress)*>(GetProcAddress(module, "wglGetProcAddress"));

    if (nullptr == _wglGetProcAddress || nullptr == _wglGetCurrentContext)
    {
        GPA_LogError("Unable to Initialize required extension functions.");
        return false;
    }

#endif

#ifdef _LINUX
    _glXGetProcAddressARB = reinterpret_cast<decltype(glXGetProcAddressARB)*>(dlsym(module, "glXGetProcAddressARB"));

    if (nullptr == _glXGetProcAddressARB)
    {
        GPA_LogError("Unable to Initialize required extension functions.");
        return false;
    }

#endif

#else // GLES

#ifdef _WIN32
    _eglGetProcAddress = reinterpret_cast<decltype(eglGetProcAddress)*>(GetProcAddress(eglmodule, "eglGetProcAddress"));

    if (nullptr == _eglGetProcAddress)
    {
        GPA_LogError("Unable to Initialize required extension functions.");
        return false;
    }

#endif

#ifdef _LINUX
    _eglGetProcAddress = reinterpret_cast<decltype(eglGetProcAddress)*>(dlsym(module, "eglGetProcAddress"));

    if (nullptr == _eglGetProcAddress)
    {
        GPA_LogError("Unable to Initialize required extension functions.");
        return false;
    }

#endif

#endif // GLES

#ifdef _WIN32
    _oglFlush = reinterpret_cast<decltype(glFlush)*>(GetProcAddress(module, "glFlush"));
    _oglGetString = reinterpret_cast<decltype(glGetString)*>(GetProcAddress(module, "glGetString"));
    _oglGetIntegerv = reinterpret_cast<decltype(glGetIntegerv)*>(GetProcAddress(module, "glGetIntegerv"));
    _oglGetError = reinterpret_cast<decltype(glGetError)*>(GetProcAddress(module, "glGetError"));
#endif
#ifdef _LINUX
    _oglFlush = reinterpret_cast<decltype(glFlush)*>(dlsym(module, "glFlush"));
    _oglGetString = reinterpret_cast<decltype(glGetString)*>(dlsym(module, "glGetString"));
    _oglGetIntegerv = reinterpret_cast<decltype(glGetIntegerv)*>(dlsym(module, "glGetIntegerv"));
    _oglGetError = reinterpret_cast<decltype(glGetError)*>(dlsym(module, "glGetError"));
#endif

    if (nullptr == _oglFlush ||
        nullptr == _oglGetString ||
        nullptr == _oglGetIntegerv ||
        nullptr == _oglGetError)
    {
        GPA_LogError("Unable to Initialize required GL functions.");
        return false;
    }

    GET_PROC_ADDRESS(_oglGetStringi, PFNGLGETSTRINGIPROC, "glGetStringi");

    // if OpenGL 3.x method of getting the extensions is available, use that, otherwise try the old method
    if (nullptr != _oglGetStringi)
    {
        GPA_LogMessage("Using OpenGL 3.x method to query extensions.");

        GLint numExtensions = 0;
        _oglGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

        for (GLint i = 0; i < numExtensions; i++)
        {
            const GLubyte* pExtension = _oglGetStringi(GL_EXTENSIONS, i);

            if (nullptr != pExtension)
            {
                if (_strcmpi(reinterpret_cast<const char*>(pExtension), "GL_AMD_performance_monitor") == 0)
                {
                    bPerfMonExtFound = true;
                }

#ifndef GLES

                if (_strcmpi(reinterpret_cast<const char*>(pExtension), "GL_ARB_timer_query") == 0)
                {
                    bTimerQueryExtFound = true;
                }

#else

                if (_strcmpi(reinterpret_cast<const char*>(pExtension), "GL_EXT_disjoint_timer_query") == 0)
                {
                    bTimerQueryExtFound = true;
                }

#endif // GLES

                if (_strcmpi(reinterpret_cast<const char*>(pExtension), "GL_AMD_debug_output") == 0)
                {
                    bDebugOutputExtFound = true;
                }

                if (_strcmpi(reinterpret_cast<const char*>(pExtension), "GLX_MESA_query_renderer") == 0)
                {
                    bMesaQueryRendererExtFound = true;
                }

                if (bPerfMonExtFound &&
                    bTimerQueryExtFound &&
                    bDebugOutputExtFound &&
                    bMesaQueryRendererExtFound)
                {
                    break;
                }
            }
        }
    }
    else
    {
        GPA_LogMessage("Using OpenGL 1.x method to query extensions.");
        const GLubyte* pExtensions = _oglGetString(GL_EXTENSIONS);

        if (nullptr != pExtensions)
        {
            if (nullptr != strstr(reinterpret_cast<const char*>(pExtensions), "GL_AMD_performance_monitor"))
            {
                bPerfMonExtFound = true;
            }

#ifndef GLES

            if (nullptr != strstr(reinterpret_cast<const char*>(pExtensions), "GL_ARB_timer_query"))
            {
                bTimerQueryExtFound = true;
            }

#else

            if (strstr(reinterpret_cast<const char*>(pExtensions), "GL_EXT_disjoint_timer_query") == 0)
            {
                bTimerQueryExtFound = true;
            }

#endif // GLES

            if (nullptr != strstr(reinterpret_cast<const char*>(pExtensions), "GL_AMD_debug_output"))
            {
                bDebugOutputExtFound = true;
            }

            if (nullptr != strstr(reinterpret_cast<const char*>(pExtensions), "GLX_MESA_query_renderer"))
            {
                bMesaQueryRendererExtFound = true;
            }
        }
    }

    // GLX_MESA_query_renderer extension
    GET_PROC_ADDRESS(_oglXQueryCurrentRendererIntegerMESA, PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA, "glXQueryCurrentRendererIntegerMESA");

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

#ifdef DEBUG_GL_ERRORS
    // GL_AMD_debug_output extension
    GET_PROC_ADDRESS(_oglDebugMessageControlARB, PFN_OGL_GLDEBUGMESSAGECONTROLARB, "glDebugMessageControlAMD");
    GET_PROC_ADDRESS(_oglDebugMessageInsertARB, PFN_OGL_GLDEBUGMESSAGEINSERTARB, "glDebugMessageInsertAMD");
    GET_PROC_ADDRESS(_oglDebugMessageCallbackARB, PFN_OGL_GLDEBUGMESSAGECALLBACKARB, "glDebugMessageCallbackAMD");
    GET_PROC_ADDRESS(_oglGetDebugMessageLogARB, PFN_OGL_GLGETDEBUGMESSAGELOGARB, "glGetDebugMessageLogAMD");

    if (
        nullptr == _oglDebugMessageControlARB ||
        nullptr == _oglDebugMessageInsertARB ||
        nullptr == _oglDebugMessageCallbackARB ||
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

    // GL_AMD_performance_monitor extension
    GET_PROC_ADDRESS(_oglGetPerfMonitorGroupsAMD, PFNGLGETPERFMONITORGROUPSAMDPROC, "glGetPerfMonitorGroupsAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCountersAMD, PFNGLGETPERFMONITORCOUNTERSAMDPROC, "glGetPerfMonitorCountersAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorGroupStringAMD, PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, "glGetPerfMonitorGroupStringAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterStringAMD, PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, "glGetPerfMonitorCounterStringAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterInfoAMD, PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, "glGetPerfMonitorCounterInfoAMD");
    GET_PROC_ADDRESS(_oglGenPerfMonitorsAMD, PFNGLGENPERFMONITORSAMDPROC, "glGenPerfMonitorsAMD");
    GET_PROC_ADDRESS(_oglDeletePerfMonitorsAMD, PFNGLDELETEPERFMONITORSAMDPROC, "glDeletePerfMonitorsAMD");
    GET_PROC_ADDRESS(_oglSelectPerfMonitorCountersAMD, PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, "glSelectPerfMonitorCountersAMD");
    GET_PROC_ADDRESS(_oglBeginPerfMonitorAMD, PFNGLBEGINPERFMONITORAMDPROC, "glBeginPerfMonitorAMD");
    GET_PROC_ADDRESS(_oglEndPerfMonitorAMD, PFNGLENDPERFMONITORAMDPROC, "glEndPerfMonitorAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterDataAMD, PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, "glGetPerfMonitorCounterDataAMD");

    if (nullptr == _oglGetPerfMonitorCountersAMD ||
        nullptr == _oglGetPerfMonitorGroupStringAMD ||
        nullptr == _oglGetPerfMonitorCounterInfoAMD ||
        nullptr == _oglGetPerfMonitorCounterStringAMD ||
        nullptr == _oglGenPerfMonitorsAMD ||
        nullptr == _oglDeletePerfMonitorsAMD ||
        nullptr == _oglSelectPerfMonitorCountersAMD ||
        nullptr == _oglBeginPerfMonitorAMD ||
        nullptr == _oglEndPerfMonitorAMD ||
        nullptr == _oglGetPerfMonitorCounterDataAMD)
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
            retVal = false; // return error if unable to retrieve renderer;
        }
        else if (strstr(reinterpret_cast<const char*>(pRenderer), s_pATIRenderer) == 0 ||
                 strstr(reinterpret_cast<const char*>(pRenderer), s_pAMDRenderer) == 0)
        {
            retVal = false; // return error if AMD extension is missing on AMD hardware
        }
    }

    GET_PROC_ADDRESS(_oglGetQueryObjectui64vEXT, PFNGLGETQUERYOBJECTUI64VEXTPROC, "glGetQueryObjectui64vEXT");

#if defined(GLES) && defined(WIN32)
    GET_PROC_ADDRESS(_oglGetQueryObjectiv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectivEXT");
    GET_PROC_ADDRESS(_oglGenQueries, PFNGLGENQUERIESPROC, "glGenQueriesEXT");
    GET_PROC_ADDRESS(_oglDeleteQueries, PFNGLDELETEQUERIESPROC, "glDeleteQueriesEXT");
    GET_PROC_ADDRESS(_oglQueryCounter, PFNGLQUERYCOUNTERPROC, "glQueryCounterEXT");

    if (nullptr == _oglGetQueryObjectiv)
    {
        GET_PROC_ADDRESS(_oglGetQueryObjectiv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectiv");
    }

    if (nullptr == _oglGenQueries)
    {
        GET_PROC_ADDRESS(_oglGenQueries, PFNGLGENQUERIESPROC, "glGenQueries");
    }

    if (nullptr == _oglDeleteQueries)
    {
        GET_PROC_ADDRESS(_oglDeleteQueries, PFNGLDELETEQUERIESPROC, "glDeleteQueries");
    }

    if (nullptr == _oglQueryCounter)
    {
        GET_PROC_ADDRESS(_oglQueryCounter, PFNGLQUERYCOUNTERPROC, "glQueryCounter");
    }

#else
    GET_PROC_ADDRESS(_oglGetQueryObjectiv, PFNGLGETQUERYOBJECTIVPROC, "glGetQueryObjectiv");
    GET_PROC_ADDRESS(_oglGenQueries, PFNGLGENQUERIESPROC, "glGenQueries");
    GET_PROC_ADDRESS(_oglDeleteQueries, PFNGLDELETEQUERIESPROC, "glDeleteQueries");
    GET_PROC_ADDRESS(_oglQueryCounter, PFNGLQUERYCOUNTERPROC, "glQueryCounter");
#endif

#ifdef GLES
#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif // GL_TIMESTAMP
#endif // GLES

    if (nullptr == _oglGetQueryObjectui64vEXT ||
        nullptr == _oglGetQueryObjectiv ||
        nullptr == _oglGenQueries ||
        nullptr == _oglDeleteQueries ||
        nullptr == _oglQueryCounter)
    {
        if (!bTimerQueryExtFound)
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

    GET_PROC_ADDRESS(_oglGetQueryObjectui64v, PFNGLGETQUERYOBJECTUI64VPROC, "glGetQueryObjectui64v");

    if (nullptr == _oglGetQueryObjectui64v)
    {
        GPA_LogMessage("glGetQueryObjectui64v entry point not exposed by the driver.");
    }

    s_areGLFunctionsInitialized = retVal;
    return retVal;
}
