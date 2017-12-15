//==============================================================================
// Copyright (c) 2014-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA required public function declarations wrapped in a macro
//==============================================================================

#ifndef GPA_FUNCTION_PREFIX
    #define GPA_FUNCTION_PREFIX( f )             ///< placeholder macro in case it's not defined before including this file
    #define NEED_TO_UNDEFINE_GPA_FUNCTION_PREFIX ///< used a a flag to indicate whether or not the macro needs to be undefined later
#endif

// Logging
GPA_FUNCTION_PREFIX(GPA_RegisterLoggingCallback)

// Init / Destroy GPA
GPA_FUNCTION_PREFIX(GPA_Initialize)
GPA_FUNCTION_PREFIX(GPA_Destroy)

// Context Startup / Finish
GPA_FUNCTION_PREFIX(GPA_OpenContext)
GPA_FUNCTION_PREFIX(GPA_CloseContext)

// Counter Interrogation
GPA_FUNCTION_PREFIX(GPA_GetNumCounters)
GPA_FUNCTION_PREFIX(GPA_GetCounterName)
GPA_FUNCTION_PREFIX(GPA_GetCounterIndex)
GPA_FUNCTION_PREFIX(GPA_GetCounterGroup)
GPA_FUNCTION_PREFIX(GPA_GetCounterDescription)
GPA_FUNCTION_PREFIX(GPA_GetCounterDataType)
GPA_FUNCTION_PREFIX(GPA_GetCounterUsageType)
GPA_FUNCTION_PREFIX(GPA_GetCounterUuid)
GPA_FUNCTION_PREFIX(GPA_GetDataTypeAsStr)
GPA_FUNCTION_PREFIX(GPA_GetUsageTypeAsStr)

// Session handling
GPA_FUNCTION_PREFIX(GPA_CreateSession)
GPA_FUNCTION_PREFIX(GPA_DeleteSession)
GPA_FUNCTION_PREFIX(GPA_BeginSession)
GPA_FUNCTION_PREFIX(GPA_EndSession)

// Counter Scheduling
GPA_FUNCTION_PREFIX(GPA_EnableCounter)
GPA_FUNCTION_PREFIX(GPA_DisableCounter)
GPA_FUNCTION_PREFIX(GPA_EnableCounterByName)
GPA_FUNCTION_PREFIX(GPA_DisableCounterByName)
GPA_FUNCTION_PREFIX(GPA_EnableAllCounters)
GPA_FUNCTION_PREFIX(GPA_DisableAllCounters)
GPA_FUNCTION_PREFIX(GPA_GetPassCount)

// // Query Counter Scheduling
GPA_FUNCTION_PREFIX(GPA_GetNumEnabledCounters)
GPA_FUNCTION_PREFIX(GPA_GetEnabledIndex)
GPA_FUNCTION_PREFIX(GPA_IsCounterEnabled)

// Sample Handling
GPA_FUNCTION_PREFIX(GPA_BeginCommandList)
GPA_FUNCTION_PREFIX(GPA_EndCommandList)
GPA_FUNCTION_PREFIX(GPA_BeginSample)
GPA_FUNCTION_PREFIX(GPA_EndSample)
GPA_FUNCTION_PREFIX(GPA_ContinueSampleOnCommandList)
GPA_FUNCTION_PREFIX(GPA_CopySecondarySamples)
GPA_FUNCTION_PREFIX(GPA_GetSampleCount)

// Query Results
GPA_FUNCTION_PREFIX(GPA_IsPassComplete)
GPA_FUNCTION_PREFIX(GPA_IsSessionComplete)
GPA_FUNCTION_PREFIX(GPA_GetPerSampleResultSize)
GPA_FUNCTION_PREFIX(GPA_GetSampleResult)

// Status/Error Query
GPA_FUNCTION_PREFIX(GPA_GetStatusAsStr)

// Device Query
GPA_FUNCTION_PREFIX(GPA_GetDeviceAndRevisionId)
GPA_FUNCTION_PREFIX(GPA_GetDeviceName)

// Internal function
GPA_FUNCTION_PREFIX(GPA_InternalSetDrawCallCounts)


#ifdef NEED_TO_UNDEFINE_GPA_FUNCTION_PREFIX
    #undef GPA_FUNCTION_PREFIX
    #undef NEED_TO_UNDEFINE_GPA_FUNCTION_PREFIX
#endif
