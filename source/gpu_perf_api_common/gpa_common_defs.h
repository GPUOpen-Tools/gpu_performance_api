//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Common Internal usage definitions.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_COMMON_DEFS_H_
#define GPU_PERF_API_COMMON_GPA_COMMON_DEFS_H_

#ifdef _WIN32
#include <Windows.h>
#endif
#include <cassert>

#include "gpu_perf_api_common/logging.h"

// Macro to make string.
#define GPA_STRING(X) #X
#define GPA_STRINGIFY(X) GPA_STRING(X)

#define GPA_NOT_THREAD_SAFE_OBJECT    ///< Use this to declare non thread safe classes/structs.
#define GPA_THREAD_SAFE_OBJECT        ///< Use this to declare thread safe classes/structs.
#define GPA_NOT_THREAD_SAFE_FUNCTION  ///< Use this to declare non thread safe functions.
#define GPA_THREAD_SAFE_FUNCTION      ///< Use this to declare thread safe functions.
#define GPA_STUB_FUNCTION             ///< Use this if function needs not to be implemented (stub function).

#define CHECK_STUB_FUNCTIONS 1  ///< Use this to trigger asserts for stubbed out functions.
#if CHECK_STUB_FUNCTIONS
#define GPA_FUNCTION_NOT_IMPLEMENTED static_assert(false, "Function Not Implemented");  ///< Use this to mark a function as not implemented.
#else
#define GPA_FUNCTION_NOT_IMPLEMENTED static_assert(true, "Ignore function Not Implemented");  ///< Use this to mark a function as not implemented.
#endif

/// Emits a log message and returns an error for a null parameter.
#define GPA_INTERNAL_CHECK_NULL_PARAM(parameter_name)                    \
    if (nullptr == parameter_name)                                       \
    {                                                                    \
        GPA_LOG_DEBUG_ERROR("Parameter '" #parameter_name "' is NULL."); \
        return kGpaStatusErrorNullPointer;                               \
    }

/// Asserts an expression.
#define GPA_ASSERT(expression)                     \
    {                                              \
        bool expression_result = expression;       \
        UNREFERENCED_PARAMETER(expression_result); \
        assert(expression_result);                 \
    }

/// Macro for an enum value string.
#define GPA_ENUM_STRING_VAL(X, Y) Y

#endif
