//==============================================================================
// Copyright (c) 2014-2021 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Deprecated header; use gpu_performance_api/gpu_perf_api_functions.h
//==============================================================================

#pragma message("Warning: You are including a deprecated header. Please use gpu_performance_api/gpu_perf_api_functions.h")

// New header
#include "gpu_performance_api/gpu_perf_api_functions.h"

#ifndef GPA_DEPRECATED_FUNCTION_PREFIX
#define GPA_DEPRECATED_FUNCTION_PREFIX(f)     ///< placeholder macro in case it's not defined before including this file
#define NEED_TO_UNDEFINE_GPA_DEPRECATED_FUNCTION_PREFIX  ///< used a a flag to indicate whether or not the macro needs to be undefined later
#endif

// GPA API Table
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetFuncTable)

// Logging
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_RegisterLoggingCallback)

// Init / Destroy GPA
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_Initialize)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_Destroy)

// Context Startup / Finish
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_OpenContext)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_CloseContext)

// Context Interrogation
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetSupportedSampleTypes)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetDeviceAndRevisionId)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetDeviceName)

// Counter Interrogation
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetNumCounters)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterName)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterIndex)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterGroup)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterDescription)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterDataType)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterUsageType)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterUuid)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetCounterSampleType)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetDataTypeAsStr)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetUsageTypeAsStr)

// Session handling
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_CreateSession)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_DeleteSession)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_BeginSession)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EndSession)

// Counter Scheduling
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EnableCounter)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_DisableCounter)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EnableCounterByName)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_DisableCounterByName)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EnableAllCounters)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_DisableAllCounters)

// Query Counter Scheduling
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetPassCount)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetNumEnabledCounters)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetEnabledIndex)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_IsCounterEnabled)

// Sample Handling
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_BeginCommandList)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EndCommandList)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_BeginSample)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_EndSample)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_ContinueSampleOnCommandList)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_CopySecondarySamples)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetSampleCount)

// Query Results
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_IsPassComplete)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_IsSessionComplete)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetSampleResultSize)
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetSampleResult)

// Status / Error Query
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetStatusAsStr)

// Sample Handling
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetSampleId)

// GPA API Version
GPA_DEPRECATED_FUNCTION_PREFIX(GPA_GetVersion)

#ifdef NEED_TO_UNDEFINE_GPA_DEPRECATED_FUNCTION_PREFIX
#undef GPA_DEPRECATED_FUNCTION_PREFIX
#undef NEED_TO_UNDEFINE_GPA_DEPRECATED_FUNCTION_PREFIX
#endif
