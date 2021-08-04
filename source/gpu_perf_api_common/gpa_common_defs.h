//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
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

// The following will be merged into gpu_perf_api_types.h in a future version that supports streaming counters and sqtt data.
#define GPA_INITIALIZE_SIMULTANEOUS_QUEUES_ENABLE_BIT \
    static_cast<GpaInitializeBits>(1)  ///< Define for GPA_Initialize bit for enabling sqtt collection from all hardware queues.
#define GPA_SESSION_SAMPLE_TYPE_SQTT static_cast<GpaSessionSampleType>(1)                        ///< Define for sqtt session sample type.
#define GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER static_cast<GpaSessionSampleType>(2)           ///< Define for streaming counter session sample type.
#define GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT static_cast<GpaSessionSampleType>(3)  ///< Define for streaming counter and sqtt session sample type.
#define GPA_CONTEXT_SAMPLE_TYPE_SQTT static_cast<GpaContextSampleTypeBits>(2)                    ///< Define for sqtt context sample type.
#define GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER static_cast<GpaContextSampleTypeBits>(4)       ///< Define for streaming counter context sample type.

/// @brief Type used to define the mask of instructions included in SQTT data.
typedef enum
{
    kGpaSqttInstructionTypeNone = 0x00,        ///< Exclude all instructions from SQTT data.
    kGpaSqttInstructionTypeAll  = 0x7FFFFFFF,  ///< Include all instructions in SQTT data.
} GpaSqttInstructionBits;

/// Allows GpaSqttInstructionBits to be combined into a single parameter.
typedef GpaFlags GpaSqttInstructionFlags;

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

#endif  // GPU_PERF_API_COMMON_GPA_COMMON_DEFS_H_
