//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file can be included by an application that wishes to use the ROCm
///         version of GPUPerfAPI. It defines a structure that can be passed to the
///         GPA_OpenContext call when using GPUPerfAPI with ROCm.
//==============================================================================

#ifndef _GPUPERFAPI_ROCM_H_
#define _GPUPERFAPI_ROCM_H_

#include "hsa.h"
#include "rocprofiler.h"

#ifdef GPA_SUPPORT_HSA // TODO: temporary ifdef -- once GPUPerfAPIHSA is gone, this can be removed
    #define GPA_DEPRECATED
#else
    #ifdef __GNUC__
        #define GPA_DEPRECATED __attribute__((deprecated))
    #elif _WIN32
        #define GPA_DEPRECATED __declspec(deprecated)
    #else
        #define GPA_DEPRECATED
    #endif
#endif

#ifndef GPALIB_DECL
    /// macro for exporting an API function
    #ifdef _WIN32
        #ifdef __cplusplus
            #define GPALIB_DECL extern "C" __declspec( dllimport )
        #else
            #define GPALIB_DECL __declspec( dllimport )
        #endif
    #else //__linux__
        #ifdef __cplusplus
            #define GPALIB_DECL extern "C"
        #else
            #define GPALIB_DECL extern
        #endif
    #endif
#endif

// NOTE: When using the ROCm version of GPUPerfAPI, you can initialize and call
//       GPUPerfAPI in one of two ways:
//         1) You must call GPA_Initialize prior to the application initializing
//            the HSA runtime with a call to hsa_init. You can then simply pass
//            in a hsa_queue_t* instance when calling GPA_OpenContext. When doing
//            this, GPUPerfAPI will set up the HSA runtime correctly to use the
//            AQL-emulation mode and the pre/post-dispatch callbacks.
//         2) You can perform all initialization yourself to ensure that AQL-emulation
//            mode is used and the pre/post-dispatch callbacks are used. In that case,
//            you can then call GPA_OpenContext with an instance of the below structure
//            (whose members you would initialize with data provided by the pre-dispatch
//            callback). Note: this second method is currently used by the Radeon Compute
//            Profiler, though in the future, it may be modified to use the first method.
//
//       It is recommended to use the first method above when using GPUPerfAPI directly
//       from a ROCm application.

/// an instance of this structure can be passed to GPA_OpenContext for the ROCm
/// version of GPUPerfAPI.
typedef struct _GPA_ROCm_Context
{
    const hsa_agent_t*   m_pAgent;                ///< the agent
    const hsa_queue_t*   m_pQueue;                ///< the queue
    GPA_DEPRECATED void* m_pAqlTranslationHandle; ///< deprecated no longer used in ROCm version -- the AQL translation handle (an opaque pointer) supplied by the pre-dispatch callback

#ifdef __cplusplus
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
    _GPA_ROCm_Context():
        m_pAgent(nullptr),
        m_pQueue(nullptr),
        m_pAqlTranslationHandle(nullptr)
    {
    }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#endif

} GPA_ROCm_Context;

typedef GPA_ROCm_Context GPA_HSA_Context;              // typedef for backwards compatibility

typedef void(*ROCmSetContextCallback)(rocprofiler_t*); // typedef for callback to be used to share rocprofiler context
typedef void(*ROCmDispatchCompleteCallback)();         // typedef for callback to be used when dispatches are complete

/// exported function called to give GPA a callback function to be called when dispatches are complete
/// \param pDispatchCompleteCallback the callback function
GPALIB_DECL void SetROCmDispatchCompleteCallback(ROCmDispatchCompleteCallback pDispatchCompleteCallback);

/// exported function called to give GPA a callback function to be called in order to share the rocprofiler context
/// \param pSetContextCallback the callback function
GPALIB_DECL void SetROCmSetContextCallback(ROCmSetContextCallback pSetContextCallback);

#endif // _GPUPERFAPI_ROCM_H_
