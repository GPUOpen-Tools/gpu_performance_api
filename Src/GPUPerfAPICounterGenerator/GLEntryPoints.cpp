//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  declares GL entry points
//==============================================================================


#include "GLEntryPoints.h"

decltype(glFlush)*                      _oglFlush                          = nullptr;
decltype(glGetString)*                  _oglGetString                      = nullptr;
decltype(glGetIntegerv)*                _oglGetIntegerv                    = nullptr;
#ifdef _WIN32
    decltype(wglGetCurrentContext)*     _wglGetCurrentContext              = nullptr;
#endif
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

// Function pointers for glQuery calls (needed for GPUTime via timer_query extension)
PFNGLGETQUERYOBJECTUI64VEXTPROC         _oglGetQueryObjectui64vEXT         = nullptr;
PFNGLGETQUERYOBJECTUI64VPROC            _oglGetQueryObjectui64v            = nullptr;
PFNGLGETQUERYOBJECTIVPROC               _oglGetQueryObjectiv               = nullptr;
PFNGLGENQUERIESPROC                     _oglGenQueries                     = nullptr;
PFNGLDELETEQUERIESPROC                  _oglDeleteQueries                  = nullptr;
PFNGLQUERYCOUNTERPROC                   _oglQueryCounter                   = nullptr;

// Function pointers for glGetStringi call to query extension strings in 3.x
PFNGLGETSTRINGIPROC                     _oglGetStringi                     = nullptr;

#ifdef DEBUG_GL_ERRORS
    // Function pointers for the GL_ARB_debug_output extension - used to improve error reporting.
    PFN_OGL_GLDEBUGMESSAGECONTROLARB    _oglDebugMessageControlARB         = nullptr;
    PFN_OGL_GLDEBUGMESSAGEINSERTARB     _oglDebugMessageInsertARB          = nullptr;
    PFN_OGL_GLDEBUGMESSAGECALLBACKARB   _oglDebugMessageCallbackARB        = nullptr;
    PFN_OGL_GLGETDEBUGMESSAGELOGARB     _oglGetDebugMessageLogARB          = nullptr;
#endif

// Function pointers for GLX_MESA_query_renderer extension
PFN_GLX_QUERYCURRENTRENDERERINTEGERMESA _oglXQueryCurrentRendererIntegerMESA = nullptr;
