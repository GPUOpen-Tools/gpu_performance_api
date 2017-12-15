//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file defines function types to make it easier to dynamically load
///         different GPUPerfAPI DLLs into an application that supports multiple APIs.
///         Applications which statically link to GPUPerfAPI do not need to include
///         this file.
//==============================================================================

#ifndef _GPUPERFAPI_FUNCTION_TYPES_H_
#define _GPUPERFAPI_FUNCTION_TYPES_H_

#include "GPUPerfAPITypes.h"

// Logging
typedef void(*GPA_LoggingCallbackPtrType)(GPA_Logging_Type messageType, const char* pMessage); ///< Typedef for a function pointer for a logging callback function

typedef GPA_Status(*GPA_RegisterLoggingCallbackPtrType)(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType pCallbackFuncPtr); ///< Typedef for a function pointer for GPA_RegisterLoggingCallback

// Init / Destroy GPA
typedef GPA_Status(*GPA_InitializePtrType)();  ///< Typedef for a function pointer for GPA_Initialize
typedef GPA_Status(*GPA_DestroyPtrType)();  ///< Typedef for a function pointer for GPA_Destroy

// Context Startup / Finish
typedef GPA_Status(*GPA_OpenContextPtrType)(void* pContext, GPA_OpenContextFlags flags, GPA_ContextId* pContextId);  ///< Typedef for a function pointer for GPA_OpenContext
typedef GPA_Status(*GPA_CloseContextPtrType)(GPA_ContextId contextId);  ///< Typedef for a function pointer for GPA_CloseContext

// Counter Interrogation
typedef GPA_Status(*GPA_GetNumCountersPtrType)(GPA_ContextId contextId, gpa_uint32* pCount);  ///< Typedef for a function pointer for GPA_GetNumCounters
typedef GPA_Status(*GPA_GetCounterNamePtrType)(GPA_ContextId contextId, gpa_uint32 index, const char** ppName);  ///< Typedef for a function pointer for GPA_GetCounterName
typedef GPA_Status(*GPA_GetCounterIndexPtrType)(GPA_ContextId contextId, const char* pCounter, gpa_uint32* pIndex);  ///< Typedef for a function pointer for GPA_GetCounterIndex
typedef GPA_Status(*GPA_GetCounterGroupPtrType)(GPA_ContextId contextId, gpa_uint32 index, const char** ppGroup); ///< Typedef for a function pointer for GPA_GetCounterGroup
typedef GPA_Status(*GPA_GetCounterDescriptionPtrType)(GPA_ContextId contextId, gpa_uint32 index, const char** ppDescription);  ///< Typedef for a function pointer for GPA_GetCounterDescription
typedef GPA_Status(*GPA_GetCounterDataTypePtrType)(GPA_ContextId contextId, gpa_uint32 index, GPA_Data_Type* pCounterDataType);  ///< Typedef for a function pointer for GPA_GetCounterDataType
typedef GPA_Status(*GPA_GetCounterUsageTypePtrType)(GPA_ContextId contextId, gpa_uint32 index, GPA_Usage_Type* pCounterUsageType);  ///< Typedef for a function pointer for GPA_GetCounterUsageType
typedef GPA_Status(*GPA_GetDataTypeAsStrPtrType)(GPA_Data_Type counterDataType, const char** ppTypeStr);  ///< Typedef for a function pointer for GPA_GetDataTypeAsStr
typedef GPA_Status(*GPA_GetUsageTypeAsStrPtrType)(GPA_Usage_Type counterUsageType, const char** ppUsageTypeStr);  ///< Typedef for a function pointer for GPA_GetUsageTypeAsStr
typedef GPA_Status(*GPA_GetCounterUuidPtrType)(GPA_ContextId contextId, gpa_uint32 index, GPA_UUID* pCounterUuid);  ///< Typedef for a function pointer for GPA_GetCounterUuid

// Session handling
typedef GPA_Status(*GPA_CreateSessionPtrType)(GPA_ContextId contextId, GPA_SessionId* pSessionId); ///< Typedef for a function pointer for GPA_CreateSession
typedef GPA_Status(*GPA_DeleteSessionPtrType)(GPA_SessionId sessionId); ///< Typedef for a function pointer for GPA_DeleteSession
typedef GPA_Status(*GPA_BeginSessionPtrType)(GPA_SessionId sessionId);  ///< Typedef for a function pointer for GPA_BeginSession
typedef GPA_Status(*GPA_EndSessionPtrType)(GPA_SessionId sessionId);  ///< Typedef for a function pointer for GPA_EndSession

// Counter Scheduling
typedef GPA_Status(*GPA_EnableCounterPtrType)(GPA_SessionId sessionId, gpa_uint32 index);  ///< Typedef for a function pointer for GPA_EnableCounter
typedef GPA_Status(*GPA_DisableCounterPtrType)(GPA_SessionId sessionId, gpa_uint32 index);  ///< Typedef for a function pointer for GPA_DisableCounter
typedef GPA_Status(*GPA_EnableCounterByNamePtrType)(GPA_SessionId sessionId, const char* pCounter);  ///< Typedef for a function pointer for GPA_EnableCounterByName
typedef GPA_Status(*GPA_DisableCounterByNamePtrType)(GPA_SessionId sessionId, const char* pCounter);  ///< Typedef for a function pointer for GPA_DisableCounterByName
typedef GPA_Status(*GPA_EnableAllCountersPtrType)(GPA_SessionId sessionId);  ///< Typedef for a function pointer for GPA_EnableAllCounters
typedef GPA_Status(*GPA_DisableAllCountersPtrType)(GPA_SessionId sessionId);  ///< Typedef for a function pointer for GPA_DisableAllCounters

// Query Counter Scheduling
typedef GPA_Status(*GPA_GetPassCountPtrType)(GPA_SessionId sessionId, gpa_uint32* pNumPasses);  ///< Typedef for a function pointer for GPA_GetPassCount
typedef GPA_Status(*GPA_GetNumEnabledCountersPtrType)(GPA_SessionId sessionId, gpa_uint32* pCount);  ///< Typedef for a function pointer for GetNumEnabledCounters
typedef GPA_Status(*GPA_GetEnabledIndexPtrType)(GPA_SessionId sessionId, gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex);  ///< Typedef for a function pointer for GPA_GetEnabledIndex
typedef GPA_Status(*GPA_IsCounterEnabledPtrType)(GPA_SessionId sessionId, gpa_uint32 counterIndex);  ///< Typedef for a function pointer for GPA_IsCounterEnabled

// Sample Handling
typedef GPA_Status(*GPA_BeginCommandListPtrType)(GPA_SessionId sessionId, gpa_uint32 passId, void* pCommandList, GPA_Command_List_Type gpaCommandListType, GPA_CommandListId* pCommandListId);  ///< Typedef for a function pointer for GPA_BeginCommandList
typedef GPA_Status(*GPA_EndCommandListPtrType)(GPA_CommandListId commandListId);  ///< Typedef for a function pointer for GPA_EndCommandList
typedef GPA_Status(*GPA_BeginSamplePtrType)(gpa_uint32 sampleId, GPA_CommandListId commandListId);  ///< Typedef for a function pointer for GPA_BeginSample
typedef GPA_Status(*GPA_EndSamplePtrType)(GPA_CommandListId commandListId);  ///< Typedef for a function pointer for GPA_EndSample
typedef GPA_Status(*GPA_ContinueSampleOnCommandListPtrType)(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId);  ///< Typedef for a function pointer for GPA_ContinueSampleOnCommandList
typedef GPA_Status(*GPA_CopySecondarySamplesPtrType)(GPA_CommandListId secondaryCmdListId, GPA_CommandListId primaryCmdListId, gpa_uint32 numSamples, gpa_uint32* pNewSampleIds);  ///< Typedef for a function pointer for GPA_CopySecondarySamples
typedef GPA_Status(*GPA_GetSampleCountPtrType)(GPA_SessionId sessionId, gpa_uint32* pSampleCount);  ///< Typedef for a function pointer for GPA_GetSampleCount

// Query Results
typedef GPA_Status(*GPA_IsSessionCompletePtrType)(GPA_SessionId sessionId);  ///< Typedef for a function pointer for GPA_IsSessionComplete
typedef GPA_Status(*GPA_IsPassCompletePtrType)(GPA_SessionId sessionId, gpa_uint32 passIndex); ///< Typedef for a function pointer for GPA_IsPassComplete
typedef GPA_Status(*GPA_GetPerSampleResultSizePtrType)(GPA_SessionId sessionId, gpa_uint32* pSampleSizeInBytes);  ///< Typedef for a function pointer for GPA_GetPerSampleResultSize
typedef GPA_Status(*GPA_GetSampleResultPtrType)(GPA_SessionId sessionId, gpa_uint32 sampleID, gpa_uint64 sampleResultSizeInBytes, void* pCounterValues); ///< Typedef for a function pointer for GPA_GetSampleResult

// Status/Error Query
typedef const char* (*GPA_GetStatusAsStrPtrType)(GPA_Status status);  ///< Typedef for a function pointer for GPA_GetStatusAsStr

// Device Query
typedef GPA_Status(*GPA_GetDeviceAndRevisionIdPtrType)(GPA_ContextId gpaContextId, gpa_uint32* pDeviceID, gpa_uint32* pRevisionID);  ///< Typedef for a function pointer for GPA_GetDeviceAndRevisionId
typedef GPA_Status(*GPA_GetDeviceNamePtrType)(GPA_ContextId gpaContextId, const char** ppDeviceName);  ///< Typedef for a function pointer for GPA_GetDeviceName

// Internal function
typedef GPA_Status(*GPA_InternalSetDrawCallCountsPtrType)(const int iCounts);  ///< Typedef for a function pointer for GPA_InternalSetDrawCallCounts

// GPA API table
typedef GPA_Status(*GPA_GetFuncTablePtrType)(void** ppGPAFuncTable); ///< Typedef for a function pointer for GPA_GetFuncTablePtrType


#endif // _GPUPERFAPI_FUNCTION_TYPES_H_
