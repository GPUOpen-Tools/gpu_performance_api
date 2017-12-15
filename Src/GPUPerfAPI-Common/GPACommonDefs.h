//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Common Internal usage definitions
//==============================================================================

#ifndef _GPA_COMMON_DEFS_H_
#define _GPA_COMMON_DEFS_H_

#ifdef _WIN32
    #include <Windows.h>
#endif

#include "Logging.h"
#include <cassert>

#define GPA_NOT_THREAD_SAFE_OBJECT          ///< Use this to declare non thread safe classes/structs
#define GPA_THREAD_SAFE_OBJECT              ///< Use this to declare thread safe classes/structs
#define GPA_NOT_THREAD_SAFE_FUNCTION        ///< Use this to declare non thread safe functions
#define GPA_THREAD_SAFE_FUNCTION            ///< Use this to declare thread safe functions
#define GPA_STUB_FUNCTION                   ///< Use this if function needs not to be implemented (stub function)

#define CHECK_STUB_FUNCTIONS 0
#if CHECK_STUB_FUNCTIONS
    #define GPA_FUNCTION_NOT_IMPLEMENTED    static_assert(false, "Function Not Implemented");
#else
    #define GPA_FUNCTION_NOT_IMPLEMENTED    static_assert(true, "Ignore function Not Implemented");
#endif

#define GPA_INTERNAL_CHECK_NULL_PARAM(parameterName)                                                                \
    if(nullptr == parameterName)                                                                                    \
    {                                                                                                               \
        GPA_LogDebugError("Parameter '"#parameterName"' is NULL.");                                                 \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }                                                                                                               \

#endif