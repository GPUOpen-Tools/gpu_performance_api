//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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

// The following will be merged into GPUPerfAPITypes.h in a future version that supports streaming counters and sqtt data
#define GPA_INITIALIZE_SIMULTANEOUS_QUEUES_ENABLE_BIT      static_cast<GPA_Initialize_Bits>(1)          ///< define for GPA_Initialize bit for enabling sqtt collection from all hardware queues
#define GPA_SESSION_SAMPLE_TYPE_SQTT                       static_cast<GPA_Session_Sample_Type>(1)      ///< define for sqtt session sample type
#define GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER          static_cast<GPA_Session_Sample_Type>(2)      ///< define for streaming counter session sample type
#define GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT static_cast<GPA_Session_Sample_Type>(3)      ///< define for streaming counter and sqtt session sample type
#define GPA_CONTEXT_SAMPLE_TYPE_SQTT                       static_cast<GPA_Context_Sample_Type_Bits>(2) ///< define for sqtt context sample type
#define GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER          static_cast<GPA_Context_Sample_Type_Bits>(4) ///< define for streaming counter context sample type

/// Type used to define the mask of instructions included in SQTT data.
/// Currently, this supports "all" or "none", but may include specific instruction types
/// in the future
typedef enum
{
    GPA_SQTT_INSTRUCTION_TYPE_NONE = 0x00,      ///< exclude all instructions from SQTT data
    GPA_SQTT_INSTRUCTION_TYPE_ALL = 0x7FFFFFFF, ///< include all instructions in SQTT data
} GPA_SQTT_Instruction_Bits;

/// Allows GPA_SQTT_Instruction_Bits to be combined into a single parameter.
typedef GPA_Flags GPA_SQTTInstructionFlags;

#define GPA_NOT_THREAD_SAFE_OBJECT          ///< Use this to declare non thread safe classes/structs
#define GPA_THREAD_SAFE_OBJECT              ///< Use this to declare thread safe classes/structs
#define GPA_NOT_THREAD_SAFE_FUNCTION        ///< Use this to declare non thread safe functions
#define GPA_THREAD_SAFE_FUNCTION            ///< Use this to declare thread safe functions
#define GPA_STUB_FUNCTION                   ///< Use this if function needs not to be implemented (stub function)

#define CHECK_STUB_FUNCTIONS 1              ///< Use this to trigger asserts for stubbed out functions
#if CHECK_STUB_FUNCTIONS
    #define GPA_FUNCTION_NOT_IMPLEMENTED    static_assert(false, "Function Not Implemented");       ///< Use this to mark a function as not implemented
#else
    #define GPA_FUNCTION_NOT_IMPLEMENTED    static_assert(true, "Ignore function Not Implemented"); ///< Use this to mark a function as not implemented
#endif

/// Emits a log message and returns an error for a null parameter
#define GPA_INTERNAL_CHECK_NULL_PARAM(parameterName)                      \
    if (nullptr == parameterName)                                         \
    {                                                                     \
        GPA_LogDebugError("Parameter '"#parameterName"' is NULL.");       \
        return GPA_STATUS_ERROR_NULL_POINTER;                             \
    }

/// Asserts an expression
#define GPA_ASSERT(expression)                                            \
    bool expressionResult = expression;                                   \
    UNREFERENCED_PARAMETER(expressionResult);                             \
    assert(expressionResult);

#endif
