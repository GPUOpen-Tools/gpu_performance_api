//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Deprecated header; use gpu_performance_api/gpu_perf_api_stub.h
//==============================================================================

#ifndef GPU_PERF_API_STUB_H_
#define GPU_PERF_API_STUB_H_

#pragma message("Warning: You are including a deprecated header. Please use gpu_performance_api/gpu_perf_api_stub.h")

#include "gpu_performance_api/gpu_perf_api_stub.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4100)
#endif

#include <string.h>

#define RETURN_GPA_SUCCESS_DEPRECATED return GPA_STATUS_OK

// Logging

static inline GPA_Status GPA_RegisterLoggingCallback(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType pCallbackFuncPtr)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Init / Destroy GPA

static inline GPA_Status GPA_Initialize(GPA_InitializeFlags flags)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_Destroy()
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Context Startup / Finish

static inline GPA_Status GPA_OpenContext(void* pContext, GPA_OpenContextFlags flags, GPA_ContextId* pContextId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_CloseContext(GPA_ContextId contextId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Context Interrogation

static inline GPA_Status GPA_GetSupportedSampleTypes(GPA_ContextId contextId, GPA_ContextSampleTypeFlags* pSampleTypes)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetDeviceAndRevisionId(GPA_ContextId contextId, gpa_uint32* pDeviceId, gpa_uint32* pRevisionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetDeviceName(GPA_ContextId contextId, const char** ppDeviceName)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Counter Interrogation

static inline GPA_Status GPA_GetNumCounters(GPA_ContextId contextId, gpa_uint32* pCount)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterName(GPA_ContextId contextId, gpa_uint32 index, const char** ppName)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterIndex(GPA_ContextId contextId, const char* pCounterName, gpa_uint32* pIndex)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterGroup(GPA_ContextId contextId, gpa_uint32 index, const char** ppGroup)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterDescription(GPA_ContextId contextId, gpa_uint32 index, const char** ppDescription)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterDataType(GPA_ContextId contextId, gpa_uint32 index, GPA_Data_Type* pCounterDataType)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterUsageType(GPA_ContextId contextId, gpa_uint32 index, GPA_Usage_Type* pCounterUsageType)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterUuid(GPA_ContextId contextId, gpa_uint32 index, GPA_UUID* pCounterUuid)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetCounterSampleType(GPA_ContextId contextId, gpa_uint32 index, GPA_Counter_Sample_Type* pCounterSampleType)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetDataTypeAsStr(GPA_Data_Type counterDataType, const char** ppTypeStr)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetUsageTypeAsStr(GPA_Usage_Type counterUsageType, const char** ppUsageTypeStr)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Session handling

static inline GPA_Status GPA_CreateSession(GPA_ContextId contextId, GPA_Session_Sample_Type sampleType, GPA_SessionId* pSessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_DeleteSession(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_BeginSession(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_EndSession(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Counter Scheduling

static inline GPA_Status GPA_EnableCounter(GPA_SessionId sessionId, gpa_uint32 index)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_DisableCounter(GPA_SessionId sessionId, gpa_uint32 index)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_EnableCounterByName(GPA_SessionId sessionId, const char* pCounterName)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_DisableCounterByName(GPA_SessionId sessionId, const char* pCounterName)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_EnableAllCounters(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_DisableAllCounters(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Query Counter Scheduling

static inline GPA_Status GPA_GetPassCount(GPA_SessionId sessionId, gpa_uint32* pNumPasses)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetNumEnabledCounters(GPA_SessionId sessionId, gpa_uint32* pCount)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetEnabledIndex(GPA_SessionId sessionId, gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_IsCounterEnabled(GPA_SessionId sessionId, gpa_uint32 counterIndex)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Sample Handling

static inline GPA_Status GPA_BeginCommandList(GPA_SessionId         sessionId,
                                              gpa_uint32            passIndex,
                                              void*                 pCommandList,
                                              GPA_Command_List_Type command_list_type,
                                              GPA_CommandListId*    pCommandListId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_EndCommandList(GPA_CommandListId command_list_id)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_BeginSample(gpa_uint32 sampleId, GPA_CommandListId command_list_id)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_EndSample(GPA_CommandListId command_list_id)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_CopySecondarySamples(GPA_CommandListId secondaryCommandListId,
                                                  GPA_CommandListId primaryCommandListId,
                                                  gpa_uint32        numSamples,
                                                  gpa_uint32*       pNewSampleIds)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetSampleCount(GPA_SessionId sessionId, gpa_uint32* pSampleCount)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetSampleId(GPA_SessionId sessionId, gpa_uint32 index, gpa_uint32* pSampleId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Query Results

static inline GPA_Status GPA_IsPassComplete(GPA_SessionId sessionId, gpa_uint32 passIndex)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_IsSessionComplete(GPA_SessionId sessionId)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetSampleResultSize(GPA_SessionId sessionId, gpa_uint32 sampleId, size_t* sampleResultSizeInBytes)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

static inline GPA_Status GPA_GetSampleResult(GPA_SessionId sessionId, gpa_uint32 sampleId, size_t sampleResultSizeInBytes, void* pCounterSampleResults)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// Status / Error Query

static inline const char* GPA_GetStatusAsStr(GPA_Status status)
{
    return NULL;
}

// GPA API Version

static inline GPA_Status GPA_GetVersion(gpa_uint32* pMajorVersion, gpa_uint32* pMinorVersion, gpa_uint32* pBuild, gpa_uint32* pUpdateVersion)
{
    RETURN_GPA_SUCCESS_DEPRECATED;
}

// GPA API Table

static inline GPA_Status GPA_GetFuncTable(void* pGPAFuncTable)
{
    // All of the GPA functions will reside in user memory as this structure will be compiled along with the user code.
    // Fill the function table with the function in user memory.
    GPAFunctionTable* pLocalFuncTable = (GPAFunctionTable*)(pGPAFuncTable);

    gpa_uint32 majorVersion           = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    gpa_uint32 correctMajorVersion    = (majorVersion == pLocalFuncTable->m_majorVer ? 1 : 0);
    gpa_uint32 clientSuppliedMinorVer = pLocalFuncTable->m_minorVer;

    pLocalFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    pLocalFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

    if (!correctMajorVersion)
    {
        return GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH;
    }

    if (clientSuppliedMinorVer > GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
    {
        return GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH;
    }

    GPAFunctionTable localFuncTable;
#define GPA_DEPRECATED_FUNCTION_PREFIX(func) localFuncTable.func = func;  ///< Macro used by GPAFunctions.h
// Deprecated header
#include "gpu_perf_api_functions.h"
#undef GPA_DEPRECATED_FUNCTION_PREFIX

    memcpy(pGPAFuncTable, &localFuncTable, clientSuppliedMinorVer);
    return GPA_STATUS_OK;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif  // GPU_PERF_API_STUB_H_
