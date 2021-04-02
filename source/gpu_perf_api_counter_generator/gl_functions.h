//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL Functions
//==============================================================================

#ifndef X
#define X
#define X_DEFINED
#endif

#define GL_CORE_FUNCTIONS(X)        \
    X(glFlush, glFlush)             \
    X(glGetString, glGetString)     \
    X(glGetIntegerv, glGetIntegerv) \
    X(glGetError, glGetError)

#define WGL_CORE_FUNCTIONS(X)                     \
    X(wglCreateContext, wglCreateContext)         \
    X(wglDeleteContext, wglDeleteContext)         \
    X(wglGetCurrentContext, wglGetCurrentContext) \
    X(wglGetCurrentDC, wglGetCurrentDC)           \
    X(wglMakeCurrent, wglMakeCurrent)

#define GLX_CORE_FUNCTIONS(X)                     \
    X(glXCreateContext, glXCreateContext)         \
    X(glXDestroyContext, glXDestroyContext)       \
    X(glXMakeCurrent, glXMakeCurrent)             \
    X(glXGetCurrentContext, glXGetCurrentContext) \
    X(glXGetCurrentDisplay, glXGetCurrentDisplay) \
    X(glXChooseVisual, glXChooseVisual)           \
    X(glXChooseFBConfig, glXChooseFBConfig)       \
    X(glXCreatePbuffer, glXCreatePbuffer)

#define GL_EXT_FUNCTIONS(X)                                      \
    X(PFNGLGETQUERYOBJECTUI64VEXTPROC, glGetQueryObjectui64vEXT) \
    X(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv)             \
    X(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v)       \
    X(PFNGLGENQUERIESPROC, glGenQueries)                         \
    X(PFNGLDELETEQUERIESPROC, glDeleteQueries)                   \
    X(PFNGLQUERYCOUNTERPROC, glQueryCounter)                     \
    X(PFNGLGETSTRINGIPROC, glGetStringi)

#define GL_AMD_EXT_FUNCTIONS(X)                                                  \
    X(PFNGLGETPERFMONITORGROUPSAMDPROC, glGetPerfMonitorGroupsAMD)               \
    X(PFNGLGETPERFMONITORCOUNTERSAMDPROC, glGetPerfMonitorCountersAMD)           \
    X(PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, glGetPerfMonitorGroupStringAMD)     \
    X(PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, glGetPerfMonitorCounterStringAMD) \
    X(PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, glGetPerfMonitorCounterInfoAMD)     \
    X(PFNGLGENPERFMONITORSAMDPROC, glGenPerfMonitorsAMD)                         \
    X(PFNGLDELETEPERFMONITORSAMDPROC, glDeletePerfMonitorsAMD)                   \
    X(PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, glSelectPerfMonitorCountersAMD)     \
    X(PFNGLBEGINPERFMONITORAMDPROC, glBeginPerfMonitorAMD)                       \
    X(PFNGLENDPERFMONITORAMDPROC, glEndPerfMonitorAMD)                           \
    X(PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, glGetPerfMonitorCounterDataAMD)

#define WGL_EXT_FUNCTIONS(X) X(PFNWGLGETEXTENSIONSSTRINGARBPROC, wglGetExtensionsStringARB)

#define WGL_AMD_EXT_FUNCTIONS(X)                                                         \
    X(PFNWGLGETGPUIDSAMDPROC, wglGetGPUIDsAMD)                                           \
    X(PFNWGLGETGPUINFOAMDPROC, wglGetGPUInfoAMD)                                         \
    X(PFNWGLGETCONTEXTGPUIDAMDPROC, wglGetContextGPUIDAMD)                               \
    X(PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC, wglCreateAssociatedContextAMD)               \
    X(PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC, wglCreateAssociatedContextAttribsAMD) \
    X(PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC, wglDeleteAssociatedContextAMD)               \
    X(PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC, wglMakeAssociatedContextCurrentAMD)     \
    X(PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC, wglGetCurrentAssociatedContextAMD)

#define GLX_AMD_EXT_FUNCTIONS(X)                                                         \
    X(PFNGLXGETGPUIDSAMDPROC, glXGetGPUIDsAMD)                                           \
    X(PFNGLXGETGPUINFOAMDPROC, glXGetGPUInfoAMD)                                         \
    X(PFNGLXGETCONTEXTGPUIDAMDPROC, glXGetContextGPUIDAMD)                               \
    X(PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC, glXCreateAssociatedContextAMD)               \
    X(PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC, glXCreateAssociatedContextAttribsAMD) \
    X(PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC, glXDeleteAssociatedContextAMD)               \
    X(PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC, glXMakeAssociatedContextCurrentAMD)     \
    X(PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC, glXGetCurrentAssociatedContextAMD)

#ifdef X_DEFINED
#undef X
#undef X_DEFINED
#endif
