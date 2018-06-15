//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief This file contains the main entrypoints into GPA
//==============================================================================

/// macro to mark a function for exporting
#ifdef _LINUX
    #define GPALIB_DECL extern "C"
#else
    #define GPALIB_DECL extern "C" __declspec( dllexport )
#endif

// std
#include <mutex>
#include <sstream>

// local
#include "GPUPerfAPI.h"
#include "Logging.h"
#include "GPAProfiler.h"
#include "IGPAImplementor.h"
#include "GPAUniqueObject.h"
#include "IGPACommandList.h"
#include "IGPAContext.h"
#include "IGPASession.h"
#include "GPAVersion.h"

extern IGPAImplementor* s_pGpaImp; ///< GPA implementor instance

/// Macro for an enum value string
#define GPA_ENUM_STRING_VAL(X,Y) Y

/// Macro to check for a null parameter
#define CHECK_NULL_PARAM(parameterName)                                                                             \
    if (nullptr == parameterName)                                                                                   \
    {                                                                                                               \
        GPA_LogDebugError("Parameter '"#parameterName"' is NULL.");                                                 \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }

/// Macro to check for out of range counter index
#define CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, contextId)                                                          \
    gpa_uint32 numCounters;                                                                                         \
    GPA_Status numCountersStatus = contextId->GetNumCounters(&numCounters);                                         \
    if (GPA_STATUS_OK != numCountersStatus)                                                                         \
    {                                                                                                               \
        return numCountersStatus;                                                                                   \
    }                                                                                                               \
    if (index >= numCounters)                                                                                       \
    {                                                                                                               \
        std::stringstream message;                                                                                  \
        message << "Parameter '"#index"' is " << #index << " but must be less than " << numCounters << ".";         \
        GPA_LogError(message.str().c_str());                                                                        \
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;                                                                 \
    }

/// Macro to check if a context is open
#define CHECK_CONTEXT_IS_OPEN(context)                                                                              \
    if (!context->IsOpen())                                                                                         \
    {                                                                                                               \
        GPA_LogError("Context has not been not opened.");                                                           \
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;                                                                   \
    }

/// Macro to check if a context exists and is open
#define CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId)                                                              \
    if (nullptr == contextId)                                                                                       \
    {                                                                                                               \
        GPA_LogError("Context object is null.");                                                                    \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }                                                                                                               \
    if (!s_pGpaImp->DoesContextExist(contextId))                                                                    \
    {                                                                                                               \
        GPA_LogError("Unknown context object.");                                                                    \
        return GPA_STATUS_ERROR_CONTEXT_NOT_FOUND;                                                                  \
    }                                                                                                               \
    CHECK_CONTEXT_IS_OPEN(contextId->Object())

/// Macro to check if a session exists
#define CHECK_SESSION_ID_EXISTS(sessionId)                                                                          \
    if (nullptr == sessionId)                                                                                       \
    {                                                                                                               \
        GPA_LogError("Session object is null.");                                                                    \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }                                                                                                               \
    if (!s_pGpaImp->DoesSessionExist(sessionId))                                                                    \
    {                                                                                                               \
        GPA_LogError("Unknown session object.");                                                                    \
        return GPA_STATUS_ERROR_SESSION_NOT_FOUND;                                                                  \
    }

/// Macro to check if a command list exists
#define CHECK_COMMANDLIST_ID_EXISTS(commandListId)                                                                  \
    if (nullptr == commandListId)                                                                                   \
    {                                                                                                               \
        GPA_LogError("Command list object is null.");                                                               \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }                                                                                                               \
    if (!s_pGpaImp->DoesCommandListExist(commandListId))                                                            \
    {                                                                                                               \
        GPA_LogError("Unknown command list object.");                                                               \
        return GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND;                                                             \
    }

/// Macro to check if a session is still running
#define CHECK_SESSION_RUNNING(sessionId)                                                                            \
    if ((*sessionId)->IsSessionRunning())                                                                           \
    {                                                                                                               \
        GPA_LogError("Session is still running. End the session before querying sample information.");              \
        return GPA_STATUS_ERROR_SESSION_NOT_ENDED;                                                                  \
    }

/// Macro to check if a session is running while enabling/disabling counters
#define CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId)                                                               \
    if ((*sessionId)->IsSessionRunning())                                                                           \
    {                                                                                                               \
        GPA_LogError("Counter state cannot change while session is running.");                                      \
        return GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING;                                               \
    }

/// Validate that sample id exists in a pass
/// \param[in] pPass The pass
/// \param[in] sampleId The sample id
/// \return GPA_STATUS_OK if the sample id exists in the pass, otherwise an error code
GPA_Status CheckSampleIdExistsInPass(GPAPass* pPass, gpa_uint32 sampleId)
{
    if (nullptr == pPass)
    {
        GPA_LogError("Invalid pass.");
        return GPA_STATUS_ERROR_FAILED;
    }

    if (!pPass->DoesSampleExist(sampleId))
    {
        GPA_LogError("Sample not found in pass.");
        return GPA_STATUS_ERROR_SAMPLE_NOT_FOUND;
    }

    return GPA_STATUS_OK;
}

/// Validate that sample id exists in a session
/// \param[in] sessionId The session id
/// \param[in] sampleId The sample id
/// \return GPA_STATUS_OK if the sample id exists in the pass, otherwise an error code
GPA_Status CheckSampleIdExistsInSession(GPA_SessionId sessionId, gpa_uint32 sampleId)
{
    if (!(*sessionId)->DoesSampleExist(sampleId))
    {
        GPA_LogError("Sample not found in session.");
        return GPA_STATUS_ERROR_SAMPLE_NOT_FOUND;
    }

    return GPA_STATUS_OK;
}

/// Macro to check the session sample type
#define CHECK_SESSION_SAMPLE_TYPE(sampleType, additionalsampleType)                                                 \
    GPA_Session_Sample_Type sessionSampleType = (*sessionId)->GetSampleType();                                      \
    if (sampleType != sessionSampleType && additionalsampleType != sessionSampleType)                               \
    {                                                                                                               \
        GPA_LogError("Session does not support the correct sample type.");                                          \
        return GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES;                                                          \
    }


//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetVersion(
    gpa_uint32* pMajorVersion,
    gpa_uint32* pMinorVersion,
    gpa_uint32* pBuild,
    gpa_uint32* pUpdateVersion)
{
    PROFILE_FUNCTION(GPA_GetVersion);
    TRACE_FUNCTION(GPA_GetVersion);

    CHECK_NULL_PARAM(pMajorVersion);
    CHECK_NULL_PARAM(pMinorVersion);
    CHECK_NULL_PARAM(pBuild);
    CHECK_NULL_PARAM(pUpdateVersion);

    *pMajorVersion = GPA_MAJOR_VERSION;
    *pMinorVersion = GPA_MINOR_VERSION;
    *pBuild = GPA_BUILD_NUMBER;
    *pUpdateVersion = GPA_UPDATE_VERSION;

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetFuncTable(
    void* pGPAFuncTable)
{
    PROFILE_FUNCTION(GPA_GetFuncTable);
    TRACE_FUNCTION(GPA_GetFuncTable);

    CHECK_NULL_PARAM(pGPAFuncTable);

    GPAFunctionTable* pFuncTable = reinterpret_cast<GPAFunctionTable*>(pGPAFuncTable);

    bool correctMajorVersion = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER == pFuncTable->m_majorVer;
    gpa_uint32 clientSuppliedMinorVer = pFuncTable->m_minorVer;

    pFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
    pFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

    if (!correctMajorVersion)
    {
        // NOTE: in most cases a client won't have registered a logging callback yet
        GPA_LogError("Client major version mismatch.");
        return GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH;
    }

    if (clientSuppliedMinorVer > GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
    {
        // NOTE: in most cases a client won't have registered a logging callback yet
        GPA_LogError("Client minor version mismatch.");
        return GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH;
    }

    GPAFunctionTable gpaFuncTable;
#define GPA_FUNCTION_PREFIX( func) gpaFuncTable.func = func;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX

    // if the client-supplied table is smaller than GPA's table,
    // this will only copy a subset of the table, ignoring the
    // functions at the end of the table
    memcpy(pFuncTable, &gpaFuncTable, clientSuppliedMinorVer);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_RegisterLoggingCallback(
    GPA_Logging_Type loggingType,
    GPA_LoggingCallbackPtrType pCallbackFuncPtr)
{
    if (nullptr == pCallbackFuncPtr &&
        loggingType != GPA_LOGGING_NONE)
    {
        GPA_LogDebugError("Parameter 'pCallbackFuncPtr' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    g_loggerSingleton.SetLoggingCallback(loggingType, pCallbackFuncPtr);

    GPA_Log(GPA_LOGGING_MESSAGE, "Logging callback registered successfully.");
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_Initialize(GPA_InitializeFlags flags)
{
    PROFILE_FUNCTION(GPA_Initialize);
    TRACE_FUNCTION(GPA_Initialize);

    GPA_Status retStatus = s_pGpaImp->Initialize(flags);
    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_Destroy()
{
    PROFILE_FUNCTION(GPA_Destroy);
    TRACE_FUNCTION(GPA_Destroy);

    GPA_Status retStatus = s_pGpaImp->Destroy();

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_OpenContext(
    void* pContext,
    GPA_OpenContextFlags flags,
    GPA_ContextId* pContextId)
{
    PROFILE_FUNCTION(GPA_OpenContext);
    TRACE_FUNCTION(GPA_OpenContext);

    if (!pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // For GPA 3.0 - disable Software counters
    flags |= GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT;

    return s_pGpaImp->OpenContext(pContext, flags, pContextId);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_CloseContext(
    GPA_ContextId contextId)
{
    PROFILE_FUNCTION(GPA_CloseContext);
    TRACE_FUNCTION(GPA_CloseContext);

    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    if ((*contextId)->GetAPIType() != s_pGpaImp->GetAPIType())
    {
        GPA_LogError("The context's API type does not match GPA's API type.");
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    return s_pGpaImp->CloseContext(contextId);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSupportedSampleTypes(
    GPA_ContextId contextId,
    GPA_ContextSampleTypeFlags* pSampleTypes)
{
    PROFILE_FUNCTION(GPA_GetSupportedSampleTypes);
    TRACE_FUNCTION(GPA_GetSupportedSampleTypes);

    CHECK_NULL_PARAM(pSampleTypes);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    return (*contextId)->GetSupportedSampleTypes(pSampleTypes);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceAndRevisionId(
    GPA_ContextId contextId,
    gpa_uint32* pDeviceId,
    gpa_uint32* pRevisionId)
{
    PROFILE_FUNCTION(GPA_GetDeviceAndRevisionId);
    TRACE_FUNCTION(GPA_GetDeviceAndRevisionId);

    CHECK_NULL_PARAM(pDeviceId);
    CHECK_NULL_PARAM(pRevisionId);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    const GPA_HWInfo* hwInfo = (*contextId)->GetHwInfo();

    if (nullptr != hwInfo && hwInfo->GetDeviceID(*pDeviceId) && hwInfo->GetRevisionID(*pRevisionId))
    {
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceName(
    GPA_ContextId contextId,
    const char** ppDeviceName)
{
    PROFILE_FUNCTION(GPA_GetDeviceName);
    TRACE_FUNCTION(GPA_GetDeviceName);

    CHECK_NULL_PARAM(ppDeviceName);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    const GPA_HWInfo* hwInfo = (*contextId)->GetHwInfo();

    if (nullptr != hwInfo && hwInfo->GetDeviceName(*ppDeviceName))
    {
        return GPA_STATUS_OK;
    }

    return  GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetNumCounters(
    GPA_ContextId contextId,
    gpa_uint32* pCount)
{
    PROFILE_FUNCTION(GPA_GetNumCounters);
    TRACE_FUNCTION(GPA_GetNumCounters);

    CHECK_NULL_PARAM(pCount);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    return (*contextId)->GetNumCounters(pCount);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterName(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppName)
{
    PROFILE_FUNCTION(GPA_GetCounterName);
    TRACE_FUNCTION(GPA_GetCounterName);

    CHECK_NULL_PARAM(ppName);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterName(index, ppName);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterIndex(
    GPA_ContextId contextId,
    const char* pCounterName,
    gpa_uint32* pIndex)
{
    PROFILE_FUNCTION(GPA_GetCounterIndex);
    TRACE_FUNCTION(GPA_GetCounterIndex);

    CHECK_NULL_PARAM(pCounterName);
    CHECK_NULL_PARAM(pIndex);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    bool counterFound = (GPA_STATUS_OK == (*contextId)->GetCounterIndex(pCounterName, pIndex));

    if (!counterFound)
    {
        std::string message = "Specified counter '";
        message += pCounterName;
        message += "' was not found. Please check spelling or availability.";
        GPA_LogError(message.c_str());
        return GPA_STATUS_ERROR_COUNTER_NOT_FOUND;
    }

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterGroup(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppGroup)
{
    PROFILE_FUNCTION(GPA_GetCounterGroup);
    TRACE_FUNCTION(GPA_GetCounterGroup);

    CHECK_NULL_PARAM(ppGroup);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterGroup(index, ppGroup);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterDescription(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppDescription)
{

    PROFILE_FUNCTION(GPA_GetCounterDescription);
    TRACE_FUNCTION(GPA_GetCounterDescription);

    CHECK_NULL_PARAM(ppDescription);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterDescription(index, ppDescription);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterDataType(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_Data_Type* pCounterDataType)
{
    PROFILE_FUNCTION(GPA_GetCounterDataType);
    TRACE_FUNCTION(GPA_GetCounterDataType);

    CHECK_NULL_PARAM(pCounterDataType);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterDataType(index, pCounterDataType);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterUsageType(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_Usage_Type* pCounterUsageType)
{
    PROFILE_FUNCTION(GPA_GetCounterUsageType);
    TRACE_FUNCTION(GPA_GetCounterUsageType);

    CHECK_NULL_PARAM(pCounterUsageType);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterUsageType(index, pCounterUsageType);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterUuid(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_UUID* pCounterUuid)
{
    PROFILE_FUNCTION(GPA_GetCounterUuid);
    TRACE_FUNCTION(GPA_GetCounterUuid);

    CHECK_NULL_PARAM(pCounterUuid);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterUuid(index, pCounterUuid);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterSampleType(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_Counter_Sample_Type* pCounterSampleType)
{
    PROFILE_FUNCTION(GPA_GetCounterSampleType);
    TRACE_FUNCTION(GPA_GetCounterSampleType);

    CHECK_NULL_PARAM(pCounterSampleType);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*contextId));

    return (*contextId)->GetCounterSampleType(index, pCounterSampleType);
}

//-----------------------------------------------------------------------------
/// array of strings representing GPA_Data_Type
static const char* g_counterDataTypeString[GPA_DATA_TYPE__LAST] =
{
    GPA_ENUM_STRING_VAL(GPA_DATA_TYPE_FLOAT64, "gpa_float64"),
    GPA_ENUM_STRING_VAL(GPA_DATA_TYPE_UINT64, "gpa_uint64")
};

GPALIB_DECL GPA_Status GPA_GetDataTypeAsStr(
    GPA_Data_Type counterDataType,
    const char** ppTypeStr)
{
    PROFILE_FUNCTION(GPA_GetDataTypeAsStr);
    TRACE_FUNCTION(GPA_GetDataTypeAsStr);

    CHECK_NULL_PARAM(ppTypeStr);

    if (GPA_DATA_TYPE__LAST > counterDataType)
    {
        *ppTypeStr = g_counterDataTypeString[counterDataType];
        return GPA_STATUS_OK;
    }

    GPA_LogError("Unable to get string for data type: invalid data type specified.");
    return GPA_STATUS_ERROR_INVALID_PARAMETER;
}

//-----------------------------------------------------------------------------
/// array of strings representing GPA_Usage_Type
static const char* g_usageTypeString[GPA_USAGE_TYPE__LAST] =
{
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_RATIO, "ratio"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_PERCENTAGE, "percentage"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_CYCLES, "cycles"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_MILLISECONDS, "milliseconds"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_BYTES, "bytes"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_ITEMS, "items"),
    GPA_ENUM_STRING_VAL(GPA_USAGE_TYPE_KILOBYTES, "kilobytes")
};

GPALIB_DECL GPA_Status GPA_GetUsageTypeAsStr(
    GPA_Usage_Type counterUsageType,
    const char** ppUsageTypeStr)
{
    PROFILE_FUNCTION(GPA_GetUsageTypeAsStr);
    TRACE_FUNCTION(GPA_GetUsageTypeAsStr);

    CHECK_NULL_PARAM(ppUsageTypeStr);

    if (GPA_USAGE_TYPE__LAST > counterUsageType)
    {
        *ppUsageTypeStr = g_usageTypeString[counterUsageType];
        return GPA_STATUS_OK;
    }

    GPA_LogError("Unable to get string for usage type: invalid usage type specified.");
    return GPA_STATUS_ERROR_INVALID_PARAMETER;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_CreateSession(
    GPA_ContextId contextId,
    GPA_Session_Sample_Type sampleType,
    GPA_SessionId* pSessionId)
{
    PROFILE_FUNCTION(GPA_CreateSession);
    TRACE_FUNCTION(GPA_CreateSession);

    CHECK_NULL_PARAM(pSessionId);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);

    if (GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT < sampleType)
    {
        GPA_LogError("Invalid sample type specified.");
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    GPA_ContextSampleTypeFlags contextSampleTypes;

    GPA_Status localStatus = (*contextId)->GetSupportedSampleTypes(&contextSampleTypes);

    if (GPA_STATUS_OK != localStatus)
    {
        GPA_LogError("Unable to get supported sample types from context.");
        return localStatus;
    }

    // next check that the set of sample types specified is compatible with context's set of supported sample types
    if ((GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER == sampleType && (GPA_CONTEXT_SAMPLE_TYPE_DISCRETE_COUNTER != (GPA_CONTEXT_SAMPLE_TYPE_DISCRETE_COUNTER & contextSampleTypes))) ||
        (GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER == sampleType && (GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER != (GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER & contextSampleTypes))) ||
        (GPA_SESSION_SAMPLE_TYPE_SQTT == sampleType && (GPA_CONTEXT_SAMPLE_TYPE_SQTT != (GPA_CONTEXT_SAMPLE_TYPE_SQTT & contextSampleTypes))) ||
        (GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT == sampleType && ((GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER | GPA_CONTEXT_SAMPLE_TYPE_SQTT) != (GPA_CONTEXT_SAMPLE_TYPE_STREAMING_COUNTER | GPA_CONTEXT_SAMPLE_TYPE_SQTT & contextSampleTypes))))
    {
        GPA_LogError("Unable to create session: sampleTypes incompatible with context's sampleTypes.");
        return GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES;
    }

    *pSessionId = (*contextId)->CreateSession(sampleType);
    return (nullptr != (*pSessionId)) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DeleteSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_DeleteSession);
    TRACE_FUNCTION(GPA_DeleteSession);

    CHECK_SESSION_ID_EXISTS(sessionId);

    IGPAContext* pContextId = (*sessionId)->GetParentContext();
    return pContextId->DeleteSession(sessionId) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_BeginSession);
    TRACE_FUNCTION(GPA_BeginSession);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());

    GPA_Status status = (*sessionId)->Begin();

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_EndSession);
    TRACE_FUNCTION(GPA_EndSession);

    CHECK_SESSION_ID_EXISTS(sessionId);
    GPA_Status status = (*sessionId)->End();

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounter(
    GPA_SessionId sessionId,
    gpa_uint32 index)
{
    PROFILE_FUNCTION(GPA_EnableCounter);
    TRACE_FUNCTION(GPA_EnableCounter);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*sessionId)->GetParentContext());

    return (*sessionId)->EnableCounter(index);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableCounter(
    GPA_SessionId sessionId,
    gpa_uint32 index)
{
    PROFILE_FUNCTION(GPA_DisableCounter);
    TRACE_FUNCTION(GPA_DisableCounter);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*sessionId)->GetParentContext());

    return (*sessionId)->DisableCounter(index);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounterByName(
    GPA_SessionId sessionId,
    const char* pCounterName)
{
    PROFILE_FUNCTION(GPA_EnableCounterByName);
    TRACE_FUNCTION(GPA_EnableCounterByName);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());

    gpa_uint32 index;
    GPA_Status status = (*sessionId)->GetParentContext()->GetCounterIndex(pCounterName, &index);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    return GPA_EnableCounter(sessionId, index);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableCounterByName(
    GPA_SessionId sessionId,
    const char* pCounterName)
{
    PROFILE_FUNCTION(GPA_DisableCounterByName);
    TRACE_FUNCTION(GPA_DisableCounterByName);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());

    gpa_uint32 index;
    GPA_Status status = (*sessionId)->GetParentContext()->GetCounterIndex(pCounterName, &index);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    return GPA_DisableCounter(sessionId, index);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableAllCounters(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_EnableAllCounters);
    TRACE_FUNCTION(GPA_EnableAllCounters);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());

    GPA_Status status = (*sessionId)->DisableAllCounters();

    if (GPA_STATUS_OK == status)
    {
        gpa_uint32 count;
        status = (*sessionId)->GetParentContext()->GetNumCounters(&count);

        if (GPA_STATUS_OK == status)
        {
            for (gpa_uint32 counterIter = 0; counterIter < count; counterIter++)
            {
                status = (*sessionId)->EnableCounter(counterIter);

                if (GPA_STATUS_OK != status)
                {
                    return status;
                }
            }
        }
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableAllCounters(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_DisableAllCounters);
    TRACE_FUNCTION(GPA_DisableAllCounters);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING_FOR_COUNTERS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->DisableAllCounters();
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetPassCount(
    GPA_SessionId sessionId,
    gpa_uint32* pNumPasses)
{
    PROFILE_FUNCTION(GPA_GetPassCount);
    TRACE_FUNCTION(GPA_GetPassCount);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_NULL_PARAM(pNumPasses);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->GetNumRequiredPasses(pNumPasses);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetNumEnabledCounters(
    GPA_SessionId sessionId,
    gpa_uint32* pCount)
{
    PROFILE_FUNCTION(GPA_GetNumEnabledCounters);
    TRACE_FUNCTION(GPA_GetNumEnabledCounters);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_NULL_PARAM(pCount);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->GetNumEnabledCounters(pCount);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetEnabledIndex(
    GPA_SessionId sessionId,
    gpa_uint32 enabledNumber,
    gpa_uint32* pEnabledCounterIndex)
{
    PROFILE_FUNCTION(GPA_GetEnabledIndex);
    TRACE_FUNCTION(GPA_GetEnabledIndex);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_NULL_PARAM(pEnabledCounterIndex);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->GetEnabledIndex(enabledNumber, pEnabledCounterIndex);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsCounterEnabled(
    GPA_SessionId sessionId,
    gpa_uint32 counterIndex)
{
    PROFILE_FUNCTION(GPA_IsCounterEnabled);
    TRACE_FUNCTION(GPA_IsCounterEnabled);

    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->IsCounterEnabled(counterIndex);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginCommandList(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex,
    void* pCommandList,
    GPA_Command_List_Type commandListType,
    GPA_CommandListId* pCommandListId)
{
    PROFILE_FUNCTION(GPA_BeginCommandList);
    TRACE_FUNCTION(GPA_BeginCommandList);

    CHECK_SESSION_ID_EXISTS(sessionId);

    if (GPA_COMMAND_LIST__LAST <= commandListType)
    {
        GPA_LogError("Invalid value for 'commandListType' parameter.");
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    if (GPA_COMMAND_LIST_NONE != commandListType)
    {
        CHECK_NULL_PARAM(pCommandList);
    }
    else if (nullptr != pCommandList)
    {
        GPA_LogError("'pCommandList' must be NULL when GPA_COMMAND_LIST_NONE is specified.");
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    CHECK_NULL_PARAM(pCommandListId);

    if (GPASessionState::GPA_SESSION_STATE_NOT_STARTED == (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        return GPA_STATUS_ERROR_SESSION_NOT_STARTED;
    }

    if (s_pGpaImp->DoesCommandListExist(*pCommandListId))
    {
        GPA_LogError("Command List already created.");
        return GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_STARTED;
    }

    *pCommandListId = (*sessionId)->CreateCommandList(passIndex, pCommandList, commandListType);

    bool status = false;

    if (nullptr != *pCommandListId)
    {
        status = (*(*pCommandListId))->Begin();

        if (status)
        {
            (*sessionId)->GetParentContext()->SetInvalidateAndFlushL2Cache(true);
        }
        else
        {
            GPA_LogError("Unable to begin the command list.");
        }
    }
    else
    {
        GPA_LogError("Unable to create the command list.");
    }

    return status ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndCommandList(
    GPA_CommandListId commandListId)
{
    PROFILE_FUNCTION(GPA_EndCommandList);
    TRACE_FUNCTION(GPA_EndCommandList);

    CHECK_COMMANDLIST_ID_EXISTS(commandListId);

    if (!(*commandListId)->IsCommandListRunning())
    {
        GPA_LogError("Command list has already been ended.");
        return GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_ENDED;
    }

    return (*commandListId)->End() ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginSample(
    gpa_uint32 sampleId,
    GPA_CommandListId commandListId)
{
    PROFILE_FUNCTION(GPA_BeginSample);
    TRACE_FUNCTION(GPA_BeginSample);

    CHECK_COMMANDLIST_ID_EXISTS(commandListId);

    GPA_Status status = GPA_STATUS_OK;

    // Only begin the sample if the current pass index is valid
    gpa_uint32 numRequiredPasses = 0;
    status = (*commandListId)->GetParentSession()->GetNumRequiredPasses(&numRequiredPasses);

    if (GPA_STATUS_OK == status)
    {
        if ((*commandListId)->GetPass()->GetIndex() < numRequiredPasses)
        {
            status = ((*commandListId)->GetParentSession()->BeginSample(sampleId, commandListId)) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            GPA_LogError("Invalid pass index.");
            status = GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
        }
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndSample(
    GPA_CommandListId commandListId)
{
    PROFILE_FUNCTION(GPA_EndSample);
    TRACE_FUNCTION(GPA_EndSample);

    CHECK_COMMANDLIST_ID_EXISTS(commandListId);

    GPA_Status status = GPA_STATUS_OK;

    // Only end the sample if the current pass index is valid
    gpa_uint32 numRequiredPasses = 0;
    status = (*commandListId)->GetParentSession()->GetNumRequiredPasses(&numRequiredPasses);

    if (GPA_STATUS_OK == status)
    {
        if ((*commandListId)->GetPass()->GetIndex() < numRequiredPasses)
        {
            status = ((*commandListId)->GetParentSession()->EndSample(commandListId)) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            GPA_LogError("Invalid pass index.");
            status = GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
        }
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_ContinueSampleOnCommandList(
    gpa_uint32 srcSampleId,
    GPA_CommandListId primaryCommandListId)
{
    PROFILE_FUNCTION(GPA_ContinueSampleOnCommandList);
    TRACE_FUNCTION(GPA_ContinueSampleOnCommandList);

    GPA_Status status = GPA_STATUS_OK;
    CHECK_COMMANDLIST_ID_EXISTS(primaryCommandListId);

    if ((status = CheckSampleIdExistsInPass((*primaryCommandListId)->GetPass(), srcSampleId)) != GPA_STATUS_OK)
    {
        return status;
    }

    return ((*primaryCommandListId)->GetParentSession()->ContinueSampleOnCommandList(srcSampleId, primaryCommandListId));
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_CopySecondarySamples(
    GPA_CommandListId secondaryCommandListId,
    GPA_CommandListId primaryCommandListId,
    gpa_uint32 numSamples,
    gpa_uint32* pNewSampleIds)
{
    PROFILE_FUNCTION(GPA_CopySecondarySamples);
    TRACE_FUNCTION(GPA_CopySecondarySamples);

    CHECK_COMMANDLIST_ID_EXISTS(secondaryCommandListId);
    CHECK_COMMANDLIST_ID_EXISTS(primaryCommandListId);

    return ((*primaryCommandListId)->GetParentSession()->CopySecondarySamples(secondaryCommandListId, primaryCommandListId, numSamples, pNewSampleIds));
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleCount(
    GPA_SessionId sessionId,
    gpa_uint32* pSampleCount)
{
    PROFILE_FUNCTION(GPA_GetSampleCount);
    TRACE_FUNCTION(GPA_GetSampleCount);

    CHECK_NULL_PARAM(pSampleCount);
    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING(sessionId);

    *pSampleCount = (*sessionId)->GetSampleCount();
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleId(GPA_SessionId sessionId, gpa_uint32 index, gpa_uint32* pSampleId)
{
    PROFILE_FUNCTION(GPA_GetSampleId);
    TRACE_FUNCTION(GPA_GetSampleId);

    CHECK_NULL_PARAM(pSampleId);
    CHECK_SESSION_ID_EXISTS(sessionId);
    CHECK_SESSION_RUNNING(sessionId);

    GPA_Status gpaStatus = GPA_STATUS_ERROR_SAMPLE_NOT_FOUND;
    gpa_uint32 sampleId = 0u;
    bool found = (*sessionId)->GetSampleIdByIndex(index, sampleId);

    if (found)
    {
        *pSampleId = sampleId;
        gpaStatus = GPA_STATUS_OK;
    }

    return gpaStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsSessionComplete(
    GPA_SessionId sessionId)
{
    GPA_Status retStatus = GPA_STATUS_RESULT_NOT_READY;

    PROFILE_FUNCTION(GPA_IsSessionComplete);
    TRACE_FUNCTION(GPA_IsSessionComplete);

    CHECK_SESSION_ID_EXISTS(sessionId);

    if (GPASessionState::GPA_SESSION_STATE_NOT_STARTED == (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        return GPA_STATUS_ERROR_SESSION_NOT_STARTED;
    }

    CHECK_SESSION_RUNNING(sessionId);

    (*sessionId)->UpdateResults();

    if ((*sessionId)->IsResultReady())
    {
        retStatus = GPA_STATUS_OK;
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsPassComplete(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex)
{
    PROFILE_FUNCTION(GPA_IsPassComplete);
    TRACE_FUNCTION(GPA_IsPassComplete);

    CHECK_SESSION_ID_EXISTS(sessionId);

    GPA_Status retStatus = GPA_STATUS_RESULT_NOT_READY;

    if (GPASessionState::GPA_SESSION_STATE_NOT_STARTED == (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        return GPA_STATUS_ERROR_SESSION_NOT_STARTED;
    }

    retStatus = (*sessionId)->IsPassComplete(passIndex);

    if (GPA_STATUS_OK == retStatus)
    {
        if ((*sessionId)->UpdateResults(passIndex))
        {
            retStatus = GPA_STATUS_OK;
        }
        else
        {
            retStatus = GPA_STATUS_RESULT_NOT_READY;
        }
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleResultSize(
    GPA_SessionId sessionId,
    gpa_uint32 sampleId,
    size_t* pSampleResultSizeInBytes)
{
    PROFILE_FUNCTION(GPA_GetSampleResultSize);
    TRACE_FUNCTION(GPA_GetSampleResultSize);

    GPA_Status status = GPA_STATUS_OK;

    CHECK_NULL_PARAM(pSampleResultSizeInBytes);
    CHECK_SESSION_ID_EXISTS(sessionId);

    if ((status = CheckSampleIdExistsInSession(sessionId, sampleId)) != GPA_STATUS_OK)
    {
        return status;
    }

    CHECK_SESSION_RUNNING(sessionId);

    *pSampleResultSizeInBytes = (*sessionId)->GetSampleResultSizeInBytes(sampleId);
    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleResult(
    GPA_SessionId sessionId,
    gpa_uint32 sampleId,
    size_t sampleResultSizeInBytes,
    void* pCounterSampleResults)
{
    PROFILE_FUNCTION(GPA_GetSampleResult);
    TRACE_FUNCTION(GPA_GetSampleResult);

    GPA_Status status = GPA_STATUS_OK;

    CHECK_NULL_PARAM(pCounterSampleResults);
    CHECK_SESSION_ID_EXISTS(sessionId);

    if ((status = CheckSampleIdExistsInSession(sessionId, sampleId)) != GPA_STATUS_OK)
    {
        return status;
    }

    CHECK_SESSION_RUNNING(sessionId);

    return (*sessionId)->GetSampleResult(sampleId, sampleResultSizeInBytes, pCounterSampleResults);
}

//-----------------------------------------------------------------------------
/// array of strings representing GPA_Status status strings
static const char* g_statusString[] =
{
    GPA_ENUM_STRING_VAL(GPA_STATUS_OK, "GPA Status: Ok."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_RESULT_NOT_READY, "GPA Status: Counter Results Not Ready.")
};

/// size of g_statusString array
static size_t g_statusStringSize = sizeof(g_statusString) / sizeof(const char*);

/// array of strings representing GPA_Status error strings
static const char* g_errorString[] =
{
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NULL_POINTER, "GPA Error: Null Pointer."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_CONTEXT_NOT_OPEN, "GPA Error: Context Not Open."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_CONTEXT_ALREADY_OPEN, "GPA Error: Coontext Already Opened."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE, "GPA Error: Index Out Of Range."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COUNTER_NOT_FOUND, "GPA Error: Counter Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_ALREADY_ENABLED, "GPA Error: Already Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NO_COUNTERS_ENABLED, "GPA Error: No Counters Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NOT_ENABLED, "GPA Error: Not Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_ENDED, "GPA Error: Command List Already Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_STARTED, "GPA Error: Command List Already Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_NOT_ENDED, "GPA Error: Command List Is Not Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NOT_ENOUGH_PASSES, "GPA Error: Not Enough Passes."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_STARTED, "GPA Error: Sample Not Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED, "GPA Error: Sample Already Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_ENDED, "GPA Error: Sample Not Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING, "GPA Error: Cannot Change Counters When Sampling."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SESSION_NOT_FOUND, "GPA Error: Session Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_FOUND, "GPA Error: Sample Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_CONTEXT_NOT_FOUND, "GPA Error: Context Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_NOT_FOUND, "GPA Error: Command List Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_READING_SAMPLE_RESULT, "GPA Error: Reading Sample Result."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES, "GPA Error: Variable Number Of Samples In Passes."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_FAILED, "GPA Error: Failed."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, "GPA Error: Hardware Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED, "GPA Error: Driver Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_API_NOT_SUPPORTED, "GPA Error: API Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INVALID_PARAMETER, "GPA Error: Incorrect Parameter."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_LOAD_FAILED, "GPA Error: Loading The Library Failed."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH, "GPA Error: Major Version Mismatch Between The Loader And The GPUPerfAPI Library."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH, "GPA Error: Minor Version Mismatch Between The Loader And The GPUPerfAPI Library."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_GPA_NOT_INITIALIZED, "GPA Error: GPA Has Not Been Initialized."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED, "GPA Error: GPA Has Already Been Initialized."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_IN_SECONDARY_COMMAND_LIST, "GPA Error: Sample In Secondary Command List."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES, "GPA Error: Incompatible Sample Types."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SESSION_ALREADY_STARTED, "GPA Error: Session Already Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SESSION_NOT_STARTED, "GPA Error: Session Not Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SESSION_NOT_ENDED, "GPA Error: Session Not Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INVALID_DATATYPE, "GPA Error: Invalid Counter Datatype."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INVALID_COUNTER_EQUATION, "GPA Error: Invalid Counter Equation."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_TIMEOUT, "GPA Error: Attempt to Retrieve Data Failed due to Timeout."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_ALREADY_LOADED, "GPA Error: Library Is Already Loaded."),
};

/// size of g_errorString array
static size_t g_errorStringSize = sizeof(g_errorString) / sizeof(const char*);

GPALIB_DECL const char* GPA_GetStatusAsStr(
    GPA_Status status)
{
    PROFILE_FUNCTION(GPA_GetStatusAsStr);
    TRACE_FUNCTION(GPA_GetStatusAsStr);

    if (status >= 0)
    {
        size_t statusIndex = status;

        if (statusIndex < g_statusStringSize)
        {
            return g_statusString[statusIndex];
        }

        return "GPA Status: Unknown Status.";
    }

    size_t statusIndex = (-status) - 1;

    if (statusIndex < g_errorStringSize)
    {
        return g_errorString[statusIndex];
    }

    return "GPA Error: Unknown Error.";
}
