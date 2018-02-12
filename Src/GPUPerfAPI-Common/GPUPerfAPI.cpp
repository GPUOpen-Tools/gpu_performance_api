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

extern IGPAImplementor* s_pGpaImp;

#define GPA_ENUM_STRING_VAL(X,Y) Y

#define CHECK_NULL_PARAM(parameterName)                                                                             \
    if(nullptr == parameterName)                                                                                    \
    {                                                                                                               \
        GPA_LogDebugError("Parameter '"#parameterName"' is NULL.");                                                 \
        return GPA_STATUS_ERROR_NULL_POINTER;                                                                       \
    }                                                                                                               \

#define CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, contextId)                                                          \
    gpa_uint32 numCounters;                                                                                         \
    GPA_Status numCountersStatus = contextId->GetNumCounters(&numCounters);                                         \
                                                                                                                    \
    if (GPA_STATUS_OK != numCountersStatus)                                                                         \
    {                                                                                                               \
         return numCountersStatus;                                                                                  \
    }                                                                                                               \
                                                                                                                    \
    if (index >= numCounters)                                                                                       \
    {                                                                                                               \
        std::stringstream message;                                                                                  \
        message << "Parameter '"#index"' is " << #index << " but must be less than " << numCounters << ".";         \
        GPA_LogError(message.str().c_str());                                                                        \
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;                                                                 \
    }                                                                                                               \

#define CHECK_CONTEXT_IS_OPEN(context)                                                                              \
    if(!context->IsOpen())                                                                                          \
    {                                                                                                               \
        GPA_LogError("Context must be opened to query counter information.");                                       \
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;                                                                  \
    }                                                                                                               \

#define CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId)                                                              \
    if(GPAObjectType::GPA_OBJECT_TYPE_CONTEXT != contextId->ObjectType())                                           \
    {                                                                                                               \
        return GPA_STATUS_ERROR_INVALID_PARAMETER;                                                                  \
    }                                                                                                               \
    if(!s_pGpaImp->DoesContextExist(contextId))                                                                     \
    {                                                                                                               \
        return GPA_STATUS_ERROR_INVALID_PARAMETER;                                                                  \
    }                                                                                                               \
    CHECK_CONTEXT_IS_OPEN(contextId->Object())                                                                      \

#define CHECK_SESSION_RUNNING(sessionId)                                                                            \
    if ((*sessionId)->IsSessionRunning())                                                                           \
    {                                                                                                               \
        GPA_LogError("Counter state cannot change while session is running.");                                      \
        return GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING;                                               \
    }                                                                                                               \


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
GPALIB_DECL GPA_Status GPA_Initialize()
{
    PROFILE_FUNCTION(GPA_Initialize);
    TRACE_FUNCTION(GPA_Initialize);

    GPA_Status retStatus = s_pGpaImp->Initialize();
    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_Destroy()
{
    PROFILE_FUNCTION(GPA_Destroy);
    TRACE_FUNCTION(GPA_Destroy);

    GPA_Status retStatus = s_pGpaImp->Destroy();

    // TODO: Need to figure out how to destroy the singleton instance
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

    // TEMPORARY FOR GPA 3.0 - disable Software counters
    flags |= GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT;

    return s_pGpaImp->OpenContext(pContext, flags, pContextId);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_CloseContext(
    GPA_ContextId contextId)
{
    PROFILE_FUNCTION(GPA_CloseContext);
    TRACE_FUNCTION(GPA_CloseContext);

    if ((*contextId)->GetAPIType() != s_pGpaImp->GetAPIType())
    {
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    if (!(*contextId)->IsOpen())
    {
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    return s_pGpaImp->CloseContext(contextId);
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
        return GPA_STATUS_ERROR_NOT_FOUND;
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
GPALIB_DECL GPA_Status GPA_CreateSession(
    GPA_ContextId contextId,
    GPA_SessionId* pSessionId)
{
    PROFILE_FUNCTION(GPA_CreateSession);
    TRACE_FUNCTION(GPA_CreateSession);

    CHECK_NULL_PARAM(pSessionId);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(contextId);
    *pSessionId = (*contextId)->CreateSession();
    return ((*pSessionId) != nullptr) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DeleteSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_DeleteSession);
    TRACE_FUNCTION(GPA_DeleteSession);

    CHECK_NULL_PARAM(sessionId);

    IGPAContext* pContextId = (*sessionId)->GetParentContext();
    return pContextId->DeleteSession(sessionId) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounter(
    GPA_SessionId sessionId,
    gpa_uint32 index)
{
    PROFILE_FUNCTION(GPA_EnableCounter);
    TRACE_FUNCTION(GPA_EnableCounter);

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
    CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, (*sessionId)->GetParentContext());

    return (*sessionId)->DisableCounter(index);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetNumEnabledCounters(
    GPA_SessionId sessionId,
    gpa_uint32* pCount)
{
    PROFILE_FUNCTION(GPA_GetNumEnabledCounters);
    TRACE_FUNCTION(GPA_GetNumEnabledCounters);

    CHECK_NULL_PARAM(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->IsCounterEnabled(counterIndex);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounterByName(
    GPA_SessionId sessionId,
    const char* pCounterName)
{
    PROFILE_FUNCTION(GPA_EnableCounterByName);
    TRACE_FUNCTION(GPA_EnableCounterByName);

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_SESSION_RUNNING(sessionId);
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

    CHECK_NULL_PARAM(sessionId);
    CHECK_NULL_PARAM(pNumPasses);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());
    return (*sessionId)->GetNumRequiredPasses(pNumPasses);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_BeginSession);
    TRACE_FUNCTION(GPA_BeginSession);

    CHECK_NULL_PARAM(sessionId);
    CHECK_CONTEXT_IS_OPEN((*sessionId)->GetParentContext());

    GPA_Status status = GPA_STATUS_OK;

    if (GPA_SESSION_STATE_NOT_STARTED != (*sessionId)->GetState())
    {
        GPA_LogError("Session is already active.");
        status = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        gpa_uint32 numEnabledCounters = 0;
        status = (*sessionId)->GetNumEnabledCounters(&numEnabledCounters);

        if (GPA_STATUS_OK != status)
        {
            GPA_LogError("Unable to get the number of enabled counters.");
        }
        else if (0 == numEnabledCounters)
        {
            GPA_LogError("Session can not be started without any enabled counters.");
            status = GPA_STATUS_ERROR_NO_COUNTERS_ENABLED;
        }
        else
        {
            if (!(*sessionId)->Begin())
            {
                status = GPA_STATUS_ERROR_FAILED;
            }
        }
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndSession(
    GPA_SessionId sessionId)
{
    PROFILE_FUNCTION(GPA_EndSession);
    TRACE_FUNCTION(GPA_EndSession);

    CHECK_NULL_PARAM(sessionId);
    bool status = true;

    if (GPA_SESSION_STATE_STARTED != (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        status = false;
    }
    else
    {
        status = (*sessionId)->End();
    }

    return status ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginCommandList(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex,
    void* pCommandList,
    GPA_Command_List_Type gpaCommandListType,
    GPA_CommandListId* pCommandListId)
{
    PROFILE_FUNCTION(GPA_BeginCommandList);
    TRACE_FUNCTION(GPA_BeginCommandList);

    CHECK_NULL_PARAM(sessionId);

    if (GPA_COMMAND_LIST_NONE != gpaCommandListType)
    {
        CHECK_NULL_PARAM(pCommandList);
    }

    CHECK_NULL_PARAM(pCommandListId);

    if (GPASessionState::GPA_SESSION_STATE_NOT_STARTED == (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        return GPA_STATUS_ERROR_FAILED;
    }

    if (GPA_COMMAND_LIST_NONE != gpaCommandListType && (*sessionId)->DoesCommandListExist(passIndex, *pCommandListId))
    {
        GPA_LogError("Command List already created.");
        return GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_STARTED;
    }

    *pCommandListId = (*sessionId)->CreateCommandList(passIndex, pCommandList, gpaCommandListType);

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
          GPA_LogError("Unnable to begin the command list.");
        }
    }
    else
    {
      GPA_LogError("Unnable to create the command list.");
    }

    return status ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndCommandList(
    GPA_CommandListId commandListId)
{
    PROFILE_FUNCTION(GPA_EndCommandList);
    TRACE_FUNCTION(GPA_EndCommandList);

    CHECK_NULL_PARAM(commandListId);

    if (!(*commandListId)->IsCommandListRunning())
    {
        GPA_LogError("Command list is already ended.");
        return GPA_STATUS_ERROR_FAILED;
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

    CHECK_NULL_PARAM(commandListId);

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

    CHECK_NULL_PARAM(commandListId);

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

    CHECK_NULL_PARAM(primaryCommandListId);

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

    CHECK_NULL_PARAM(secondaryCommandListId);
    CHECK_NULL_PARAM(primaryCommandListId);

    return ((*primaryCommandListId)->GetParentSession()->CopySecondarySamples(secondaryCommandListId, primaryCommandListId, numSamples, pNewSampleIds));
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleCount(
    GPA_SessionId sessionId,
    gpa_uint32* pSampleCount)
{
    PROFILE_FUNCTION(GPA_GetSampleCount);
    TRACE_FUNCTION(GPA_GetSampleCount);

    CHECK_NULL_PARAM(sessionId);

    if ((*sessionId)->IsSessionRunning())
    {
        GPA_LogError("Session is still running. End the session before querying sample information.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pSampleCount = (*sessionId)->GetSampleCount();
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsPassComplete(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex)
{
    PROFILE_FUNCTION(GPA_IsPassComplete);
    TRACE_FUNCTION(GPA_IsPassComplete);

    CHECK_NULL_PARAM(sessionId);

    GPA_Status retStatus = GPA_STATUS_RESULT_NOT_READY;

    if (GPASessionState::GPA_SESSION_STATE_NOT_STARTED == (*sessionId)->GetState())
    {
        GPA_LogError("Session has not been started.");
        return GPA_STATUS_ERROR_FAILED;
    }

    if ((*sessionId)->UpdateResults(passIndex))
    {
        retStatus = GPA_STATUS_OK;
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsSessionComplete(
    GPA_SessionId sessionId)
{
    GPA_Status retStatus = GPA_STATUS_RESULT_NOT_READY;

    PROFILE_FUNCTION(GPA_IsSessionComplete);
    TRACE_FUNCTION(GPA_IsSessionComplete);

    CHECK_NULL_PARAM(sessionId);

    if ((*sessionId)->IsSessionRunning())
    {
        GPA_LogError("Session is still running. End the session before querying session result information.");
        return GPA_STATUS_ERROR_FAILED;
    }

    (*sessionId)->UpdateResults();

    if ((*sessionId)->IsComplete())
    {
        retStatus = GPA_STATUS_OK;
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetPerSampleResultSize(
    GPA_SessionId sessionId,
    size_t* sampleResultSizeInBytes)
{
    PROFILE_FUNCTION(GPA_GetPerSampleResultSize);
    TRACE_FUNCTION(GPA_GetPerSampleResultSize);

    CHECK_NULL_PARAM(sessionId);

    GPA_Status status = GPA_STATUS_OK;

    if ((*sessionId)->IsSessionRunning())
    {
        GPA_LogError("Session is still running. End the session before querying sample information.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *sampleResultSizeInBytes = (*sessionId)->GetPerSampleResultSizeInBytes();
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

    CHECK_NULL_PARAM(sessionId);

    if ((*sessionId)->IsSessionRunning())
    {
        GPA_LogError("Session is still running. End the session before querying sample information.");
        return GPA_STATUS_ERROR_FAILED;
    }

    return (*sessionId)->GetSampleResult(sampleId, sampleResultSizeInBytes, pCounterSampleResults);
}

//-----------------------------------------------------------------------------
static const char* g_gpaStatusString[] =
{
    GPA_ENUM_STRING_VAL(GPA_STATUS_OK, "GPA Status: Ok."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_RESULT_NOT_READY, "GPA Status: Counter Results Not Ready.")
};

static const char* g_gpaErrorString[] =
{
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NULL_POINTER, "GPA Error: Null Pointer."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COUNTERS_NOT_OPEN, "GPA Error: Counters Not Open."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COUNTERS_ALREADY_OPEN, "GPA Error: Counters Already Opened."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE, "GPA Error: Index Out Of Range."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NOT_FOUND, "GPA Error: Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_ALREADY_ENABLED, "GPA Error: Already Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NO_COUNTERS_ENABLED, "GPA Error: No Counters Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NOT_ENABLED, "GPA Error: Not Enabled."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_NOT_STARTED, "GPA Error: Command List Not Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_ALREADY_STARTED, "GPA Error: Command List Already Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COMMAND_LIST_NOT_ENDED, "GPA Error: Command List Is Not Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_NOT_ENOUGH_PASSES, "GPA Error: Not Enough Passes."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_STARTED, "GPA Error: Sample Not Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED, "GPA Error: Sample Already Started."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_ENDED, "GPA Error: Sample Not Ended."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING, "GPA Error: Cannot Change Counters When Sampling."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SESSION_NOT_FOUND, "GPA Error: Session Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_FOUND, "GPA Error: Sample Not Found."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_NOT_FOUND_IN_ALL_PASSES, "GPA Error: Sample Not Found In All Passes."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE, "GPA Error: Counter Not Of Specified Type."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_READING_COUNTER_RESULT, "GPA Error: Reading Counter Result."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES, "GPA Error: Variable Number Of Samples In Passes."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_FAILED, "GPA Error: Failed."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, "GPA Error: Hardware Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED, "GPA Error: Driver Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_API_NOT_SUPPORTED, "GPA Error: API Not Supported."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_INVALID_PARAMETER, "GPA Error: Incorrect Parameter."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_LOAD_FAILED, "GPA Error: Loading The Library Failed."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_LIB_LOAD_VERSION_MISMATCH, "GPA Error: Version Mismatch Between The Loader And The GPUPerfAPI Library."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_GPA_NOT_INITIALIZED, "GPA Error: GPA Has Not Been Initialized."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED, "GPA Error: GPA Has Already Been Initialized."),
    GPA_ENUM_STRING_VAL(GPA_STATUS_ERROR_SAMPLE_IN_SECONDARY_COMMAND_LIST, "GPA Error: Sample In Secondary Command List.")
};

GPALIB_DECL const char* GPA_GetStatusAsStr(
    GPA_Status status)
{
    PROFILE_FUNCTION(GPA_GetStatusAsStr);
    TRACE_FUNCTION(GPA_GetStatusAsStr);

    if (status >= 0)
    {
        if (status < GPA_STATUS_MAX)
        {
            return g_gpaStatusString[status];
        }

        return "Unknown Status";
    }

    if (status > GPA_STATUS_MIN)
    {
        return g_gpaErrorString[(-status) - 1];
    }

    return "Unknown Error";
}

//-----------------------------------------------------------------------------
static const char* g_GPACounterDataTypeString[GPA_DATA_TYPE__LAST] =
{
    GPA_ENUM_STRING_VAL(GPA_Data_Type_FLOAT64, "gpa_float64"),
    GPA_ENUM_STRING_VAL(GPA_Data_Type_UINT64, "gpa_uint64")
};

GPALIB_DECL GPA_Status GPA_GetDataTypeAsStr(
    GPA_Data_Type counterDataType,
    const char** ppTypeStr)
{
    PROFILE_FUNCTION(GPA_GetDataTypeAsStr);
    TRACE_FUNCTION(GPA_GetDataTypeAsStr);

    if (GPA_DATA_TYPE__LAST > counterDataType)
    {
        *ppTypeStr = g_GPACounterDataTypeString[counterDataType];
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
static const char* g_GPAUsageTypeString[GPA_USAGE_TYPE__LAST] =
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

    if (GPA_USAGE_TYPE__LAST > counterUsageType)
    {
        *ppUsageTypeStr = g_GPAUsageTypeString[counterUsageType];
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceAndRevisionId(
    GPA_ContextId gpaContextId,
    gpa_uint32* pDeviceId,
    gpa_uint32* pRevisionId)
{
    PROFILE_FUNCTION(GPA_GetDeviceAndRevisionId);
    TRACE_FUNCTION(GPA_GetDeviceAndRevisionId);

    CHECK_NULL_PARAM(pDeviceId);
    CHECK_NULL_PARAM(pRevisionId);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(gpaContextId);

    const GPA_HWInfo* hwInfo = (*gpaContextId)->GetHwInfo();

    if (nullptr != hwInfo && hwInfo->GetDeviceID(*pDeviceId) && hwInfo->GetRevisionID(*pRevisionId))
    {
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceName(
    GPA_ContextId gpaContextId,
    const char** ppDeviceName)
{
    PROFILE_FUNCTION(GPA_GetDeviceName);
    TRACE_FUNCTION(GPA_GetDeviceName);

    CHECK_NULL_PARAM(ppDeviceName);
    CHECK_CONTEXT_ID_EXISTS_AND_IS_OPEN(gpaContextId);

    const GPA_HWInfo* hwInfo = (*gpaContextId)->GetHwInfo();

    if (nullptr != hwInfo && hwInfo->GetDeviceName(*ppDeviceName))
    {
        return GPA_STATUS_OK;
    }

    return  GPA_STATUS_ERROR_FAILED;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_InternalSetDrawCallCounts(
    const int iCounts)
{
    PROFILE_FUNCTION(GPA_InternalSetDrawCallCounts);
    TRACE_FUNCTION(GPA_InternalSetDrawCallCounts);

    UNREFERENCED_PARAMETER(iCounts);
    GPA_Status status = GPA_STATUS_OK;
    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetFuncTable(
    void** ppGPAFuncTable)
{
    PROFILE_FUNCTION(GPA_GetFuncTable);
    TRACE_FUNCTION(GPA_GetFuncTable);

    GPAApi* pApi = reinterpret_cast<GPAApi*>(*ppGPAFuncTable);

#define GPA_FUNCTION_PREFIX( func) pApi->func = func;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX

    pApi->m_apiId = GPA_API_CURRENT_UUID;
    return GPA_STATUS_OK;
}
