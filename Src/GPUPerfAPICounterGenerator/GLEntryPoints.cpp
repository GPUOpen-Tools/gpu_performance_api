//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GL entry points
//==============================================================================

#include "GPACommonDefs.h"
#include "GLEntryPoints.h"
#include "Logging.h"

#ifdef _LINUX
#include <dlfcn.h>
#define LOAD_SYMBOL dlsym
#else
#define LOAD_SYMBOL GetProcAddress
#endif

namespace oglUtils
{
    decltype(GET_PROC_ADDRESS_TYPE)* GET_PROC_ADDRESS_FUNC = nullptr;

#define DEFINE_CORE_FUNCS(type, typeString) decltype(type)* _o##type = nullptr;

#include "GLFunctions.h"
    GL_CORE_FUNCTIONS(DEFINE_CORE_FUNCS)

#undef DEFINE_CORE_FUNCS

#define DEFINE_GL_PLATFORM_CORE_FUNCS(type, typeString) decltype(type)* _##type = nullptr;

#ifdef WIN32
    WGL_CORE_FUNCTIONS(DEFINE_GL_PLATFORM_CORE_FUNCS)
#else
    GLX_CORE_FUNCTIONS(DEFINE_GL_PLATFORM_CORE_FUNCS)
#endif
#undef DEFINE_GL_PLATFORM_CORE_FUNCS

#define DEFINE_FUNC_PTRS(type, typeString) type _o##typeString = nullptr;

#include "GLFunctions.h"
    GL_EXT_FUNCTIONS(DEFINE_FUNC_PTRS)
    GL_AMD_EXT_FUNCTIONS(DEFINE_FUNC_PTRS)
#undef DEFINE_FUNC_PTRS

// AMD GPU association extension functions
#define DECLARE_AMD_ASSOCIATION_FUNCS(type, typeString) type _##typeString = nullptr;

#include "GLFunctions.h"
#ifdef WIN32
    WGL_AMD_EXT_FUNCTIONS(DECLARE_AMD_ASSOCIATION_FUNCS)
#else
    GLX_AMD_EXT_FUNCTIONS(DECLARE_AMD_ASSOCIATION_FUNCS)
#endif
#undef DECLARE_AMD_ASSOCIATION_FUNCS

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
    bool        s_isSupportedExtensionQueried = false;

    std::map<GLExtension, Supported> s_glExtensions = {{std::string("GL_AMD_performance_monitor"), false},
                                                       {std::string("GL_ARB_timer_query"), false},
                                                       {std::string("GL_EXT_disjoint_timer_query"), false},
                                                       {std::string("GL_AMD_debug_output"), false},
                                                       {std::string("GLX_MESA_query_renderer"), false},
                                                       {std::string("WGL_AMD_gpu_association"), false},
                                                       {std::string("GLX_AMD_GPU_association"), false}};
}  // namespace oglUtils

bool oglUtils::LoadGL()
{
    if (nullptr == s_glLibHandle)
    {
#ifdef _WIN32
        s_glLibHandle = LoadLibraryA("opengl32.dll");
#ifdef GLES
        s_glLibHandle = LoadLibraryA("libEGL.dll");
#endif
#else
        s_glLibHandle = dlopen("libGL.so", RTLD_LAZY);
#ifdef GLES
        s_glLibHandle = dlopen("libEGL.so", RTLD_LAZY);
#endif
#endif
    }

    return nullptr != s_glLibHandle;
}

#define LOAD_LIBRARY_SYMBOL(varName, type)                                              \
    if (nullptr == varName)                                                             \
    {                                                                                   \
        varName = reinterpret_cast<decltype(type)*>(LOAD_SYMBOL(s_glLibHandle, #type)); \
    }

bool oglUtils::InitializeGLCoreFunctions()
{
    if (LoadGL())
    {
        LOAD_LIBRARY_SYMBOL(_oglFlush, glFlush);
        LOAD_LIBRARY_SYMBOL(_oglGetString, glGetString);
        LOAD_LIBRARY_SYMBOL(_oglGetIntegerv, glGetIntegerv);
        LOAD_LIBRARY_SYMBOL(_oglGetError, glGetError);

        if (nullptr == _oglFlush || nullptr == _oglGetString || nullptr == _oglGetIntegerv || nullptr == _oglGetError)
        {
            GPA_LogMessage("Unable to Initialize GL core functions.");
            return false;
        }

        bool found = true;
#define DEFINE_GL_PLATFORM_CORE_FUNCS(type, typeString) \
    LOAD_LIBRARY_SYMBOL(_##typeString, type)            \
    found &= _##typeString != nullptr;

#ifdef WIN32
        WGL_CORE_FUNCTIONS(DEFINE_GL_PLATFORM_CORE_FUNCS)
#else
        GLX_CORE_FUNCTIONS(DEFINE_GL_PLATFORM_CORE_FUNCS)
#endif
#undef DEFINE_GL_PLATFORM_CORE_FUNCS

        if (!found)
        {
            GPA_LogMessage("Unable to Initialize GL Platform core functions.");
            return false;
        }

        GET_PROC_ADDRESS_FUNC = reinterpret_cast<decltype(GET_PROC_ADDRESS_TYPE)*>(LOAD_SYMBOL(s_glLibHandle, GPA_STRINGIFY(GET_PROC_ADDRESS_TYPE)));

        if (nullptr == GET_PROC_ADDRESS_FUNC)
        {
            GPA_LogError("Unable to Initialize required extension functions.");
            return false;
        }

        return true;
    }

    return false;
}

void oglUtils::QuerySupportedExtensions()
{
    if (InitializeGLCoreFunctions() && InitCtxExtFunctions() && nullptr != _oglGetString && !s_isSupportedExtensionQueried)
    {
        GPA_LogMessage("Using OpenGL 1.x method to query extensions.");
        GLint numExtensions = 0;
        _oglGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

        for (GLint i = 0; i < numExtensions; i++)
        {
            const char* pExtension = reinterpret_cast<const char*>(_oglGetStringi(GL_EXTENSIONS, i));

            if ((nullptr != pExtension) && (s_glExtensions.find(pExtension) != s_glExtensions.end()))
            {
                s_glExtensions[pExtension] = true;
            }
        }

        s_isSupportedExtensionQueried = true;
    }
}

bool oglUtils::IsAmdGpuAssociationSupported()
{
    QuerySupportedExtensions();
#ifdef WIN32
    return s_glExtensions["WGL_AMD_gpu_association"];
#else
    return s_glExtensions["GLX_AMD_GPU_association"];
#endif
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

    if (!InitializeGLCoreFunctions())
    {
        GPA_LogError("Unable to Initialize required GL functions.");
        return false;
    }

    QuerySupportedExtensions();

    bool bPerfMonExtFound    = s_glExtensions["GL_AMD_performance_monitor"];
    bool bTimerQueryExtFound = s_glExtensions["GL_ARB_timer_query"] || s_glExtensions["GL_EXT_disjoint_timer_query"];

    if (!InitCtxExtFunctions())
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
    GET_PROC_ADDRESS(_oglDebugMessageControlARB, PFN_OGL_GLDEBUGMESSAGECONTROLARB, "glDebugMessageControlAMD");
    GET_PROC_ADDRESS(_oglDebugMessageInsertARB, PFN_OGL_GLDEBUGMESSAGEINSERTARB, "glDebugMessageInsertAMD");
    GET_PROC_ADDRESS(_oglDebugMessageCallbackARB, PFN_OGL_GLDEBUGMESSAGECALLBACKARB, "glDebugMessageCallbackAMD");
    GET_PROC_ADDRESS(_oglGetDebugMessageLogARB, PFN_OGL_GLGETDEBUGMESSAGELOGARB, "glGetDebugMessageLogAMD");

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

bool oglUtils::InitCtxExtFunctions()
{
    if (LoadGL() && InitializeGLCoreFunctions() && nullptr != GET_PROC_ADDRESS_FUNC)
    {
        GET_PROC_ADDRESS(_oglGetStringi, PFNGLGETSTRINGIPROC, "glGetStringi");
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
#endif  // GL_TIMESTAMP
#endif  // GLES

        GET_PROC_ADDRESS(_oglGetQueryObjectui64v, PFNGLGETQUERYOBJECTUI64VPROC, "glGetQueryObjectui64v");

        if (nullptr == _oglGetQueryObjectui64v)
        {
            GPA_LogMessage("glGetQueryObjectui64v entry point not exposed by the driver.");
        }

        return !(nullptr == _oglGetQueryObjectui64vEXT || nullptr == _oglGetQueryObjectiv || nullptr == _oglGenQueries || nullptr == _oglDeleteQueries ||
                 nullptr == _oglQueryCounter);
    }

    return false;
}

bool oglUtils::InitCtxAmdPerfExtFunctions()
{
    if (LoadGL() && InitializeGLCoreFunctions() && nullptr != GET_PROC_ADDRESS_FUNC)
    {
        bool success = false;

// GL_AMD_performance_monitor extension
#define INIT_AMD_PERF_EXT_FUNC(type, typeString)        \
    GET_PROC_ADDRESS(_o##typeString, type, #typeString) \
    success = success || (nullptr != _o##typeString);

#include "GLFunctions.h"
        GL_AMD_EXT_FUNCTIONS(INIT_AMD_PERF_EXT_FUNC)
#undef INIT_AMD_PERF_EXT_FUNC

        // GL_SETGPADEVICECLOCKMODEAMDX extension
        GET_PROC_ADDRESS(_oglSetGpaDeviceClockModeAMDX, PFN_GL_SETGPADEVICECLOCKMODEAMDX, "glSetGpaDeviceClockModeAMDX");

#if defined(_LINUX) || defined(LINUX)
        // GLX_MESA_query_renderer extension
        GET_PROC_ADDRESS(_oglXQueryCurrentRendererIntegerMESA, PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA, "glXQueryCurrentRendererIntegerMESA");
#endif

        return success || (nullptr != _oglSetGpaDeviceClockModeAMDX);
    }

    return false;
}

bool oglUtils::InitCtxAmdMultiGpuExtFunctions()
{
    if (LoadGL() && InitializeGLCoreFunctions() && nullptr != GET_PROC_ADDRESS_FUNC)
    {
        QuerySupportedExtensions();
        bool success = false;

#define INIT_GL_AMD_EXT_FUNC(type, typeString)         \
    GET_PROC_ADDRESS(_##typeString, type, #typeString) \
    success = success || (nullptr != _##typeString);

#include "GLFunctions.h"
#ifdef WIN32
        WGL_AMD_EXT_FUNCTIONS(INIT_GL_AMD_EXT_FUNC)
#else
        GLX_AMD_EXT_FUNCTIONS(INIT_GL_AMD_EXT_FUNC)
#endif

#undef INIT_GL_AMD_EXT_FUNC

        return success;
    }

    return false;
}
