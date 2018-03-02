//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL version of GPUPerfAPI
//==============================================================================


#include <string>
#include <vector>
#include <assert.h>
#include <sstream>

#ifdef _LINUX
    #include <dlfcn.h>
#endif

#include "GPUPerfAPIImp.h"
#include "GPACustomHWValidationManager.h"

#include "GLCounterDataRequestManager.h"
#include "GPACounterGenerator.h"
#include "GPUPerfAPIGL.h"
#include "ASICInfo.h"
#include "ADLUtil.h"
// This is from ADL's include directory.
#include "customer/oem_structures.h"

#include "DeviceInfoUtils.h"

using std::string;

static const char* pAMDRenderer = "AMD";        ///< AMD Renderer string
static const char* pATIRenderer = "ATI";        ///< ATI Renderer string (legacy)
static const char* pNVIDIARenderer = "NVIDIA";  ///< NVIDIA Renderer string
static const char* pIntelRenderer = "Intel";    ///< Intel Renderer string

#ifdef DEBUG_GL_ERRORS

/// declared as extern in GPUPerfAPI.h
/// Helps the CheckForGLErrors macro get and use the error without having to
/// redefine it every time within the macro, also simplifies CheckForGLErrorsCond below.
GLenum g_glError = GL_NO_ERROR;

/// checks for OpenGL errors and logs the specified message if there is an error
/// \param pcsErrMsg the error message to put in the log
/// \return true if there is an error; false if there is no error
bool CheckForGLErrorsCond(const char* pcsErrMsg)
{
    // Use the macro version for the asserts and error reporting.
    // It will set g_glError which can then be used as the conditional.
    CheckForGLErrors(pcsErrMsg);
    return g_glError != GL_NO_ERROR;
}

//=============================================================================
/// DebugCallback
///
/// The call back function when there is debug message generated;
//=============================================================================
GLvoid __stdcall DebugCallback(GLenum source,
                               GLenum type,
                               GLuint id,
                               GLenum severity,
                               GLsizei length,
                               const GLchar* message,
                               GLvoid* userParam)
{
    UNREFERENCED_PARAMETER(id);
    UNREFERENCED_PARAMETER(length);

    std::string string = "";

    string += "'";

    switch (source)
    {
        case GL_DEBUG_SOURCE_API_ARB:
            string += "OpenGL API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
            string += "Window System";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
            string += "Shader Compiler";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY_ARB :
            string += "Third Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION_ARB:
            string += "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER_ARB :
            string += "Other";
            break;

        default:
            string += "Unknown";
            break;
    }

    string += "' output a(n)";

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR_ARB:
            string += " Error ";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB :
            string += " Deprecated Behavior ";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB :
            string += " Undefined Behavior ";
            break;

        case GL_DEBUG_TYPE_PORTABILITY_ARB :
            string += " Portability ";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE_ARB:
            string += " Performance ";
            break;

        case GL_DEBUG_TYPE_OTHER_ARB :
            string += " Other ";
            break;

        default:
            string += " unknown ";
            break;
    }

    string += "message with ";

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH_ARB:
            string += "Severity - High ";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM_ARB:
            string += "Severity - Medium ";
            break;

        case GL_DEBUG_SEVERITY_LOW_ARB:
            string += "Severity - Low ";
            break;

        default:
            string += "Severity - unknown ";
            break;
    }

    if (nullptr != message)
    {
        string += "and message '";
        string += message;
        string += "'";
    }

    string += ": ";

    if (nullptr != userParam)
    {
        string += (GLchar*)userParam;
    }

    string += ".";

    GPA_LogMessage(string.c_str());
}

////=============================================================================
///// Set up the callback function and control operation
///// This is currently commented out because the glDebugMessageControlARB function is always
///// nullptr, but the other entrypoint is available. Also, calling this function with a non-debug
///// runtime will cause a GL_INVALID_OPERATION to be generated. This needs some smarter handling
/////
///// The call back function when there is debug message generated;
////=============================================================================
//void SetupDebugCallback()
//{
//   if (nullptr != _oglDebugMessageCallbackARB &&
//       nullptr != _oglDebugMessageControlARB)
//   {
//      _oglDebugMessageCallbackARB(&DebugCallback, nullptr);
//      _oglDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//   }
//}

#endif // DEBUG_GL_ERRORS

GPA_ContextStateGL* getCurrentContext()
{
    return static_cast<GPA_ContextStateGL* >(g_pCurrentContext);
}

// Don't want to check results throughout the frame.
gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 50;
}


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

/// Checks the OpenGL extensions and initializes the various function pointers.  The extensions queried are:
///    -- GL_AMD_performance_monitor
///    -- GL_ARB_timer_query (OpenGL)
///    -- GL_EXT_disjoint_timer_query (OpenGLES)
///    -- GL_AMD_debug_output
///    -- GLX_MESA_query_renderer
/// \return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED if the GL_AMD_performance_monitor or GL_ARB_timer_query extension entry points are not found
///         GPA_STATUS_OK otherwise
GPA_Status InitializeGLFunctions()
{
    GPA_Status retVal = GPA_STATUS_OK;

    bool bPerfMonExtFound = false;
    bool bTimerQueryExtFound = false;
    bool bDebugOutputExtFound = false;
    bool bMesaQueryRendererExtFound = false;

#ifdef _WIN32
    HMODULE module = LoadLibraryA("opengl32.dll");
#else
    void* module = dlopen("libGL.so", RTLD_LAZY);
#endif

    if (nullptr == module)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

#ifndef GLES

#ifdef _WIN32
    _wglGetCurrentContext = reinterpret_cast<decltype(wglGetCurrentContext)*>(GetProcAddress(module, "wglGetCurrentContext"));

    _wglGetProcAddress = reinterpret_cast<decltype(wglGetProcAddress)*>(GetProcAddress(module, "wglGetProcAddress"));

    if (nullptr == _wglGetProcAddress || nullptr == _wglGetCurrentContext)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

#endif

#ifdef _LINUX
    _glXGetProcAddressARB = reinterpret_cast<decltype(glXGetProcAddressARB)*>(dlsym(module, "glXGetProcAddressARB"));

    if (nullptr == _glXGetProcAddressARB)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

#endif

#else // GLES

#ifdef _WIN32
    _eglGetProcAddress = reinterpret_cast<decltype(eglGetProcAddress)*>(GetProcAddress(module, "eglGetProcAddress"));

    if (nullptr == _eglGetProcAddress)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

#endif

#ifdef _LINUX
    _eglGetProcAddress = reinterpret_cast<decltype(eglGetProcAddress)*>(dlsym(module, "eglGetProcAddress"));

    if (nullptr == _eglGetProcAddress)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

#endif

#endif // GLES

#ifdef _WIN32
    _oglFlush = reinterpret_cast<decltype(glFlush)*>(GetProcAddress(module, "glFlush"));
    _oglGetString = reinterpret_cast<decltype(glGetString)*>(GetProcAddress(module, "glGetString"));
    _oglGetIntegerv = reinterpret_cast<decltype(glGetIntegerv)*>(GetProcAddress(module, "glGetIntegerv"));
#endif
#ifdef _LINUX
    _oglFlush = reinterpret_cast<decltype(glFlush)*>(dlsym(module, "glFlush"));
    _oglGetString = reinterpret_cast<decltype(glGetString)*>(dlsym(module, "glGetString"));
    _oglGetIntegerv = reinterpret_cast<decltype(glGetIntegerv)*>(dlsym(module, "glGetIntegerv"));
#endif

    if (nullptr == _oglFlush || nullptr == _oglGetString || nullptr == _oglGetIntegerv)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
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

                if (bPerfMonExtFound == true && bTimerQueryExtFound == true && bDebugOutputExtFound == true && bMesaQueryRendererExtFound == true)
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
    GET_PROC_ADDRESS(_oglDebugMessageControlARB,  PFN_OGL_GLDEBUGMESSAGECONTROLARB,  "glDebugMessageControlAMD");
    GET_PROC_ADDRESS(_oglDebugMessageInsertARB,   PFN_OGL_GLDEBUGMESSAGEINSERTARB,   "glDebugMessageInsertAMD");
    GET_PROC_ADDRESS(_oglDebugMessageCallbackARB, PFN_OGL_GLDEBUGMESSAGECALLBACKARB, "glDebugMessageCallbackAMD");
    GET_PROC_ADDRESS(_oglGetDebugMessageLogARB,   PFN_OGL_GLGETDEBUGMESSAGELOGARB,   "glGetDebugMessageLogAMD");

    if (
        _oglDebugMessageControlARB  == nullptr ||
        _oglDebugMessageInsertARB   == nullptr ||
        _oglDebugMessageCallbackARB == nullptr ||
        _oglGetDebugMessageLogARB   == nullptr)
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
    GET_PROC_ADDRESS(_oglGetPerfMonitorGroupsAMD,        PFNGLGETPERFMONITORGROUPSAMDPROC,        "glGetPerfMonitorGroupsAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCountersAMD,      PFNGLGETPERFMONITORCOUNTERSAMDPROC,      "glGetPerfMonitorCountersAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorGroupStringAMD,   PFNGLGETPERFMONITORGROUPSTRINGAMDPROC,   "glGetPerfMonitorGroupStringAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterStringAMD, PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, "glGetPerfMonitorCounterStringAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterInfoAMD,   PFNGLGETPERFMONITORCOUNTERINFOAMDPROC,   "glGetPerfMonitorCounterInfoAMD");
    GET_PROC_ADDRESS(_oglGenPerfMonitorsAMD,             PFNGLGENPERFMONITORSAMDPROC,             "glGenPerfMonitorsAMD");
    GET_PROC_ADDRESS(_oglDeletePerfMonitorsAMD,          PFNGLDELETEPERFMONITORSAMDPROC,          "glDeletePerfMonitorsAMD");
    GET_PROC_ADDRESS(_oglSelectPerfMonitorCountersAMD,   PFNGLSELECTPERFMONITORCOUNTERSAMDPROC,   "glSelectPerfMonitorCountersAMD");
    GET_PROC_ADDRESS(_oglBeginPerfMonitorAMD,            PFNGLBEGINPERFMONITORAMDPROC,            "glBeginPerfMonitorAMD");
    GET_PROC_ADDRESS(_oglEndPerfMonitorAMD,              PFNGLENDPERFMONITORAMDPROC,              "glEndPerfMonitorAMD");
    GET_PROC_ADDRESS(_oglGetPerfMonitorCounterDataAMD,   PFNGLGETPERFMONITORCOUNTERDATAAMDPROC,   "glGetPerfMonitorCounterDataAMD");

    if (_oglGetPerfMonitorCountersAMD      == nullptr  ||
        _oglGetPerfMonitorGroupStringAMD   == nullptr  ||
        _oglGetPerfMonitorCounterInfoAMD   == nullptr  ||
        _oglGetPerfMonitorCounterStringAMD == nullptr  ||
        _oglGenPerfMonitorsAMD             == nullptr  ||
        _oglDeletePerfMonitorsAMD          == nullptr  ||
        _oglSelectPerfMonitorCountersAMD   == nullptr  ||
        _oglBeginPerfMonitorAMD            == nullptr  ||
        _oglEndPerfMonitorAMD              == nullptr  ||
        _oglGetPerfMonitorCounterDataAMD   == nullptr)
    {

        if (bPerfMonExtFound)
        {
            GPA_LogError("The GL_AMD_performance_monitor extension is exposed by the driver, but not all entry points are available.");
        }
        else
        {
            GPA_LogError("The GL_AMD_performance_monitor extension is not exposed by the driver.");
        }

        if (nullptr != g_pCurrentContext && g_pCurrentContext->m_hwInfo.IsAMD())
        {
            retVal = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED; // return error if AMD extension is missing on AMD hardware
        }
    }

#ifndef GLES
    GET_PROC_ADDRESS(_oglBeginQuery,               PFNGLBEGINQUERYPROC,             "glBeginQuery"); //not used anymore
    GET_PROC_ADDRESS(_oglEndQuery,                 PFNGLENDQUERYPROC,               "glEndQuery"); //not used anymore
    GET_PROC_ADDRESS(_oglGetQueryiv,               PFNGLGETQUERYIVPROC,             "glGetQueryiv"); //not used anymore
    GET_PROC_ADDRESS(_oglGetQueryObjectui64vEXT,   PFNGLGETQUERYOBJECTUI64VEXTPROC, "glGetQueryObjectui64vEXT");
    GET_PROC_ADDRESS(_oglGetQueryObjectiv,         PFNGLGETQUERYOBJECTIVPROC,       "glGetQueryObjectiv");
    GET_PROC_ADDRESS(_oglGenQueries,               PFNGLGENQUERIESPROC,             "glGenQueries");
    GET_PROC_ADDRESS(_oglDeleteQueries,            PFNGLDELETEQUERIESPROC,          "glDeleteQueries");
    GET_PROC_ADDRESS(_oglQueryCounter,             PFNGLQUERYCOUNTERPROC,           "glQueryCounter");
#else
    GET_PROC_ADDRESS(_oglBeginQuery,               PFNGLBEGINQUERYPROC,             "glBeginQueryEXT");
    GET_PROC_ADDRESS(_oglEndQuery,                 PFNGLENDQUERYPROC,               "glEndQueryEXT");
    GET_PROC_ADDRESS(_oglGetQueryiv,               PFNGLGETQUERYIVPROC,             "glGetQueryivEXT");
    GET_PROC_ADDRESS(_oglGetQueryObjectui64vEXT,   PFNGLGETQUERYOBJECTUI64VEXTPROC, "glGetQueryObjectui64vEXT");
    GET_PROC_ADDRESS(_oglGetQueryObjectiv,         PFNGLGETQUERYOBJECTIVPROC,       "glGetQueryObjectivEXT");
    GET_PROC_ADDRESS(_oglGenQueries,               PFNGLGENQUERIESPROC,             "glGenQueriesEXT");
    GET_PROC_ADDRESS(_oglDeleteQueries,            PFNGLDELETEQUERIESPROC,          "glDeleteQueriesEXT");
    GET_PROC_ADDRESS(_oglQueryCounter,             PFNGLQUERYCOUNTEREXTPROC,        "glQueryCounterEXT");

#ifndef GL_TIMESTAMP
#define GL_TIMESTAMP GL_TIMESTAMP_EXT
#endif // GL_TIMESTAMP
#endif // GLES

    if (_oglBeginQuery              == nullptr   ||
        _oglEndQuery                == nullptr   ||
        _oglGetQueryObjectui64vEXT  == nullptr   ||
        _oglGetQueryObjectiv        == nullptr   ||
        _oglGenQueries              == nullptr   ||
        _oglDeleteQueries           == nullptr   ||
        _oglQueryCounter            == nullptr)
    {
        if (bTimerQueryExtFound == false)
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

        retVal = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    GET_PROC_ADDRESS(_oglGetQueryObjectui64v, PFNGLGETQUERYOBJECTUI64VPROC, "glGetQueryObjectui64v");

    if (nullptr == _oglGetQueryObjectui64v)
    {
        GPA_LogMessage("glGetQueryObjectui64v entry point not exposed by the driver.");
    }

    return retVal;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    UNREFERENCED_PARAMETER(pContext);
    assert(nullptr != pHwInfo);

    // get the entry points
    GPA_Status status = InitializeGLFunctions();

    if (status != GPA_STATUS_OK)
    {
#ifndef GLES
        GPA_LogError("Could not initialize required OpenGL functions.");
#else
        GPA_LogError("Could not initialize required OpenGL ES functions.");
#endif // GLES
        return status;
    }

    const GLubyte* pRenderer = _oglGetString(GL_RENDERER);
    pHwInfo->SetDeviceName(reinterpret_cast<const char*>(pRenderer));

    // Handle non-AMD GPU vendors
    const GLubyte* pVendor = _oglGetString(GL_VENDOR);

    //TODO: should at least support GPUTime for these vendors then
    if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), pNVIDIARenderer))
    {
        pHwInfo->SetVendorID(NVIDIA_VENDOR_ID);
        pHwInfo->SetDeviceName(reinterpret_cast<const char*>(pRenderer));
        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
        return GPA_STATUS_OK;
    }
    else if (nullptr != strstr(reinterpret_cast<const char*>(pVendor), pIntelRenderer))
    {
        pHwInfo->SetVendorID(INTEL_VENDOR_ID);
        pHwInfo->SetDeviceName(reinterpret_cast<const char*>(pRenderer));
        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_INTEL);
        return GPA_STATUS_OK;
    }

    // instead of checking the vendor string to make sure it is ATI / AMD,
    // use the Renderer string - sometimes the GL driver team needs to override
    // the vendor string to make apps and games behave differently, so using
    // the renderer string is a better solution.
    if (strstr(reinterpret_cast<const char*>(pRenderer), pATIRenderer) == 0 ||
        strstr(reinterpret_cast<const char*>(pRenderer), pAMDRenderer) == 0)
    {
        pHwInfo->SetVendorID(AMD_VENDOR_ID);

        bool isDeviceIdKnown = false;

        if (nullptr != _oglXQueryCurrentRendererIntegerMESA)
        {
            // first try to get the device id from the glXQueryCurrentRendererIntegerMESA extension
            unsigned int driverDeviceId;
            _oglXQueryCurrentRendererIntegerMESA(GLX_RENDERER_DEVICE_ID_MESA, &driverDeviceId);

            // check to make sure the device id returned is found in the device info table
            GDT_HW_GENERATION hwGeneration;
            isDeviceIdKnown = AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(driverDeviceId, hwGeneration);

            if (isDeviceIdKnown)
            {
                pHwInfo->SetDeviceID(driverDeviceId);
            }
        }

        // if we were unable to use the glCQueryCurrentRendererIntegerMESA extension,
        // then fall back to the GPIN counters exposed by the driver
        if (!isDeviceIdKnown)
        {

            ASICInfo asicInfo;

            if (GetASICInfo(asicInfo) == false)
            {
                GPA_LogError("Unable to obtain asic information.");
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }

            // switch between values in ASICInfo.h and GPAHWInfo.cpp
            switch (asicInfo.eAsicRev)
            {
                case ATIASIC_ID_TAHITI_P:
                    pHwInfo->SetDeviceID(0x6779);
                    break;

                case ATIASIC_ID_PITCAIRN_PM:
                    pHwInfo->SetDeviceID(0x6818);
                    break;

                case ATIASIC_ID_CAPEVERDE_M:
                    pHwInfo->SetDeviceID(0x6838);
                    break;

                case ATIASIC_ID_OLAND_M:
                    pHwInfo->SetDeviceID(0x6610);
                    break;

                case ATIASIC_ID_HAINAN_M:
                    pHwInfo->SetDeviceID(0x6660);
                    break;

                case ATIASIC_ID_BONAIRE_M:
                    pHwInfo->SetDeviceID(0x665C);
                    break;

                case ATIASIC_ID_SPECTRE:
                    pHwInfo->SetDeviceID(0x1307);
                    break;

                case ATIASIC_ID_SPOOKY:
                    pHwInfo->SetDeviceID(0x1312);
                    break;

                case ATIASIC_ID_KALINDI:
                    pHwInfo->SetDeviceID(0x9830);
                    break;

                case ATIASIC_ID_HAWAII_P:
                    pHwInfo->SetDeviceID(0x67A0);
                    break;

                case ATIASIC_ID_ICELAND_M:
                    pHwInfo->SetDeviceID(0x6900);
                    break;

                case ATIASIC_ID_TONGA_P:
                    pHwInfo->SetDeviceID(0x6920);
                    break;

                case ATIASIC_ID_GODAVARI:
                    pHwInfo->SetDeviceID(0x9855);
                    break;

                case ATIASIC_ID_CARRIZO:
                    pHwInfo->SetDeviceID(0x9870);
                    break;

                case ATIASIC_ID_STONEY:
                    pHwInfo->SetDeviceID(0x98E4);
                    break;

                case ATIASIC_ID_FIJI_P:
                    pHwInfo->SetDeviceID(0x7300);
                    break;

                case ATIASIC_ID_ELLESMERE:
                    pHwInfo->SetDeviceID(0x67DF);
                    break;

                case ATIASIC_ID_BAFFIN:
                    pHwInfo->SetDeviceID(0x67FF);
                    break;

                case ATIASIC_ID_VEGAM:
                    pHwInfo->SetDeviceID(0x694C);
                    break;

                case ATIASIC_ID_LEXA:
                    pHwInfo->SetDeviceID(0x699F);
                    break;

                case ATIASIC_ID_VEGA:
                    pHwInfo->SetDeviceID(0x687F);
                    break;

                case ATIASIC_ID_VEGA_APU:
                    pHwInfo->SetDeviceID(0x15DD);
                    break;

                default:
                    GPA_LogError("Unsupported asic ID.");
                    return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                    break;
            }
        }

        if (!pHwInfo->UpdateRevisionIdBasedOnDeviceIDAndName())
        {
            // We didn't find a revision Id, set it to REVISION_ID_ANY
            pHwInfo->SetRevisionID(REVISION_ID_ANY);
        }

        return GPA_STATUS_OK;
    }

    GPA_LogError("A non-AMD graphics card was identified.");
    return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    UNREFERENCED_PARAMETER(pContext);
    assert(nullptr != pHwInfo);

    // get the entry points
    GPA_Status status = InitializeGLFunctions();

    if (status != GPA_STATUS_OK)
    {
#ifndef GLES
        GPA_LogError("Could not initialize required OpenGL functions.");
#else
        GPA_LogError("Could not initialize required OpenGL ES functions.");
#endif // GLES
        return status;
    }

    const GLubyte* pRenderer = _oglGetString(GL_RENDERER);

    const char* deviceName = nullptr;
    pHwInfo->GetDeviceName(deviceName);
    size_t deviceNameLen = strlen(deviceName);

    // instead of checking the vendor string to make sure it is ATI / AMD,
    // use the Renderer string - sometimes the GL driver team needs to override
    // the vendor string to make apps and games behave differently, so using
    // the renderer string is a better solution.
    bool isAMDRenderer = strstr(reinterpret_cast<const char*>(pRenderer), pATIRenderer) == 0 ||
                         strstr(reinterpret_cast<const char*>(pRenderer), pAMDRenderer) == 0;

    if (isAMDRenderer)
    {
        if (strncmp(deviceName, reinterpret_cast<const char*>(pRenderer), deviceNameLen) != 0)
        {
            // device names don't match, let the driver be the authority on the device name
            pHwInfo->SetDeviceName(reinterpret_cast<const char*>(pRenderer));
        }

        return GPA_STATUS_OK;
    }

    const GLubyte* pVendor = _oglGetString(GL_VENDOR);

    if (strstr(reinterpret_cast<const char*>(pVendor), pNVIDIARenderer))
    {
        if (pHwInfo->IsNVidia())
        {
            return GPA_STATUS_OK;
        }
        else
        {
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    if (strstr(reinterpret_cast<const char*>(pVendor), pIntelRenderer))
    {
        if (pHwInfo->IsIntel())
        {
            return GPA_STATUS_OK;
        }
        else
        {
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    GPA_LogError("A unknown graphics card was identified.");
    return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    UNREFERENCED_PARAMETER(pContext);

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // get the entry points
    GPA_Status status = InitializeGLFunctions();

    if (status != GPA_STATUS_OK)
    {
#ifndef GLES
        GPA_LogError("Could not initialize required OpenGL functions.");
#else
        GPA_LogError("Could not initialize required OpenGL ES functions.");
#endif // GLES
        return status;
    }

    // GPUTime information is returned in nanoseconds, so set the frequency to convert it into seconds
    pHwInfo->SetTimeStampFrequency(1000000000);

    status = GPACustomHwValidationManager::Instance()->ValidateHW(pContext, pHwInfo);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    // If GL has gotten this far, the hardware should be supported
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'ppNewContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateGL* pContext = new(std::nothrow) GPA_ContextStateGL();

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to create context.");
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        (*ppNewContext) = pContext;
    }

    return result;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_Initialize()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
// Startup / exit
GPA_Status GPA_IMP_OpenContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);

    //#ifdef DEBUG_GL_ERRORS
    //    SetupDebugCallback();
    //#endif // DEBUG_GL_ERRORS

    GPA_ContextStateGL* pGLContext = getCurrentContext();
    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (nullptr == pGLContext || pGLContext->m_hwInfo.GetHWGeneration(generation) == false)
    {
        GPA_LogError("Unable to get hardware generation.");
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 vendorId = 0;

    if (pGLContext->m_hwInfo.GetVendorID(vendorId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 deviceId = 0;

    if (pGLContext->m_hwInfo.GetDeviceID(deviceId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 revisionId = 0;

    if (pGLContext->m_hwInfo.GetRevisionID(revisionId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    // generate the expected counters
    GPA_Status status = GenerateCounters(GPA_API_OPENGL, vendorId, deviceId, revisionId, reinterpret_cast<GPA_ICounterAccessor**>(&(pGLContext->m_pCounterAccessor)), &(pGLContext->m_pCounterScheduler));

    if (g_pCurrentContext->m_hwInfo.IsAMD() && status == GPA_STATUS_OK)
    {
        // now query the GL API to get the hardware counter group names and Ids so that the expected groups can be verified and the group Ids can be updated.

        // Get the number of performance counter groups
        GLint nNumGroups;
        _oglGetPerfMonitorGroupsAMD(&nNumGroups, 0, nullptr);

        assert(nNumGroups > 0);

        if (nNumGroups == 0)
        {
            GPA_LogError("No counter groups are exposed by GL_AMD_performance_monitor.");
            return GPA_STATUS_ERROR_FAILED;
        }

        GPA_HardwareCounters* pHardwareCounters = pGLContext->m_pCounterAccessor->GetHardwareCounters();

        unsigned int expectedDriverGroups = pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount - 1;

        if (nNumGroups < (int)expectedDriverGroups)
        {
            // We should not proceed if the driver exposes less groups that we expect
            std::stringstream error;
            error << "GL_AMD_performance_monitor exposes " << nNumGroups << " counter groups, but GPUPerfAPI requires at least " << (int)expectedDriverGroups << ".";
            GPA_LogError(error.str().c_str());
            return GPA_STATUS_ERROR_FAILED;
        }

        if (nNumGroups > (int)expectedDriverGroups)
        {
            // report an error if the driver exposes more groups than we expect, but allow the code to continue.
            std::stringstream error;
            error << "GL_AMD_performance_monitor exposes " << nNumGroups << " counter groups, but GPUPerfAPI expected " << (int)expectedDriverGroups << ".";
            GPA_LogError(error.str().c_str());
        }

        // Get the group Ids
        GLuint* pPerfGroups = new(std::nothrow) GLuint[nNumGroups];

        if (nullptr == pPerfGroups)
        {
            GPA_LogError("Unable to allocate memory to store the group IDs.");
            return GPA_STATUS_ERROR_FAILED;
        }

        _oglGetPerfMonitorGroupsAMD(nullptr, nNumGroups, pPerfGroups);

        // declare this outside the loops
        std::vector<GPA_HardwareCounterDescExt>::iterator internalCounterIter = pHardwareCounters->m_counters.begin();

        int driverGroupNum = -1;

        // for each group, get the group name, number of counters, and max counters (and maybe validate them)
        for (int g = 0; g < (int)pHardwareCounters->m_groupCount; g++)
        {
            driverGroupNum++;
            char strName[64];
            memset(strName, 0, 64);
            GLint nCounters = 0;
            GLint nMaxActive = 0;

            // Get the group name
            if (g < nNumGroups)
            {
                _oglGetPerfMonitorGroupStringAMD(pPerfGroups[driverGroupNum], 64, nullptr, strName);

                // Get the number of counters and max active counters
                _oglGetPerfMonitorCountersAMD(pPerfGroups[driverGroupNum], &nCounters, &nMaxActive, 0, nullptr);

                if (generation == GDT_HW_GENERATION_SEAISLAND && strncmp(strName, "TCS", 64) == 0)
                {
                    // skip the TCS counter group because it is only exposed on Kabini and GPA GL does not currently support it.
                    GPA_LogMessage("Skipping TCS group.");
                    driverGroupNum++;
                    _oglGetPerfMonitorGroupStringAMD(pPerfGroups[driverGroupNum], 64, nullptr, strName);

                    // Get the number of counters and max active counters
                    _oglGetPerfMonitorCountersAMD(pPerfGroups[driverGroupNum], &nCounters, &nMaxActive, 0, nullptr);
                }

                // validate the values
                if (strncmp(pHardwareCounters->m_pGroups[g].m_pName, "GPUTime", 8) == 0)
                {
                    // ignore the GPUTime group -- it is not explicitly exposed by the driver -- it is handled separately by GPA
                    // we break here because GPUTime is always the last group exposed by GPA
                    break;
                }
                else if (strncmp(pHardwareCounters->m_pGroups[g].m_pName, strName, 64) != 0)
                {
                    std::stringstream error;
#ifndef GLES
                    error << "GPUPerfAPI's group name '" << pHardwareCounters->m_pGroups[g].m_pName << "' does not match the OpenGL returned name of '" << strName << "'.";
#else
                    error << "GPUPerfAPI's group name '" << pHardwareCounters->m_pGroups[g].m_pName << "' does not match the OpenGL ES returned name of '" << strName << "'.";
#endif // GLES
                    GPA_LogError(error.str().c_str());
                }
                else
                {
                    // only check for later errors if the group name is the same. If the group name is different, we expect these other two errors to happen also,
                    // so there is no reason to check for them.

                    if (generation == GDT_HW_GENERATION_SOUTHERNISLAND && strncmp(strName, "WM_MD", 64) == 0)
                    {
                        // For SI, the driver exposes WM_MD with 36 counters, but it really only has 6, so change this number
                        nCounters = 6;
                    }

                    // Make sure GPA and the driver have same number of counters.
                    // There will be no catastrophic errors if the GPA expects less counters than GL exposes, but we may not have the right counters... and may be reporting bad results.
                    // There could be major issues if the GPA expects more counters than GL exposes, because we may try to enable a counter that doesn't exist,
                    // in which case we hope the driver will return a 0 result and not write unexpected values into the register.
                    assert(pHardwareCounters->m_pGroups[g].m_numCounters == (unsigned int)nCounters);

                    if (pHardwareCounters->m_pGroups[g].m_numCounters != (unsigned int)nCounters)
                    {
                        std::stringstream error;
                        error << "GPUPerfAPI's group '" << pHardwareCounters->m_pGroups[g].m_pName << "' has " << pHardwareCounters->m_pGroups[g].m_numCounters << " counters, but OpenGL exposes '" << nCounters << ".";

                        if (pHardwareCounters->m_pGroups[g].m_numCounters < (unsigned int)nCounters)
                        {
                            // log as a message, because this isn't so bad
                            GPA_LogMessage(error.str().c_str());
                        }
                        else
                        {
                            // log as an error, because we should definitely fix this
                            GPA_LogError(error.str().c_str());
                        }
                    }

                    // This assert is good for debugging, but it will fire on most EG cards, because we "expect" SQ to have 8 max counters on cypress (high end), but
                    // we know that it will actually have less on lower end EG cards, and the driver returns the correct values, so our 8 != what the driver returns.
                    //assert( pHardwareCounters->Groups[g].maxActiveCounters == (unsigned int)nMaxActive );
                }
            }

            // update the group Id based on what was returned from the driver
            const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

            for (int c = 0; c < numCountersInGroup; c++)
            {
                internalCounterIter->m_groupIdDriver = pPerfGroups[driverGroupNum];

                if (internalCounterIter != pHardwareCounters->m_counters.end())
                {
                    ++internalCounterIter;
                }
            }
        }

        delete[] pPerfGroups;
    }

    return status;
}


GPA_Status GPA_IMP_CloseContext()
{
    return GPA_STATUS_OK;
}


// Context
GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndSession()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_BeginSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}


GPA_Status GPA_IMP_EndSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}


GPA_Status GPA_IMP_BeginSampleInSampleList(gpa_uint32 sampleID, void* pSampleList)
{
    UNREFERENCED_PARAMETER(sampleID);
    UNREFERENCED_PARAMETER(pSampleList);
    GPA_LogError("GPA_BeginSampleInSampleList is not supported. Use GPA_BeginSample instead.");

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}


GPA_Status GPA_IMP_EndSampleInSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);
    GPA_LogError("GPA_EndSampleInSampleList is not supported. Use GPA_EndSample instead.");

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}


GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID)
{
    UNREFERENCED_PARAMETER(sampleID);

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndSample()
{
    return GPA_STATUS_OK;
}


gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    // maximum latency is 4 for r6xx; should be the same for later generations too
    // DX had to move to 32 but I'm not sure why. We can update GL if we see issues.
    return 4;
}


GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("No context available. Unable to create a data request.");
        return nullptr;
    }
    else
    {
        GDT_HW_GENERATION generation;
        g_pCurrentContext->m_hwInfo.GetHWGeneration(generation);
        return GLCounterDataRequestManager::Instance()->GetCounterDataRequest(generation, nullptr);
    }
}
