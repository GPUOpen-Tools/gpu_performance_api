//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This is the header file that must be included by an application that
///         wishes to use GPUPerfAPI. It defines all the available entrypoints.
//==============================================================================

#ifndef _GPUPERFAPI_H_
#define _GPUPERFAPI_H_

#ifndef GPALIB_DECL
    /// macro for exporting an API function
    #ifdef _WIN32
        #ifdef __cplusplus
            #define GPALIB_DECL extern "C" __declspec( dllimport )
        #else
            #define GPALIB_DECL __declspec( dllimport )
        #endif
    #else //__linux__
        #ifdef __cplusplus
            #define GPALIB_DECL extern "C"
        #else
            #define GPALIB_DECL extern
        #endif
    #endif
#endif

#if DISABLE_GPA
    #define USE_GPA 0
#else 
    #define USE_GPA 1
#endif

#include <assert.h>
#include "GPUPerfAPITypes.h"
#include "GPUPerfAPIFunctionTypes.h"

/// UUID value for the version specific GPA API
/// UUID: {8A497207-7637-4135-B7B6-86C0D088866B}
/// This needs to be updated if the GPA API function table changes
#define GPA_API_3_0_UUID  { 0x8A497207,                         \
        0x7637,                                                 \
        0x4135,                                                 \
        { 0xB7, 0XB6, 0X86, 0XC0, 0XD0, 0X88, 0X86, 0x6B } };

/// UUID value for the current GPA API
const GPA_UUID GPA_API_CURRENT_UUID = GPA_API_3_0_UUID;


/// Structure to hold the function table of the exported GPA APIs
typedef struct _GPAApi
{
    GPA_UUID m_apiId;

#define GPA_FUNCTION_PREFIX(func) func##PtrType func;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX

#ifdef __cplusplus
    _GPAApi()
    {
        m_apiId = GPA_API_CURRENT_UUID;
#define GPA_FUNCTION_PREFIX(func) func = nullptr;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX
    }
#endif

} GPAApi;

#if USE_GPA

// Logging

/// \brief Register a callback function to receive log messages.
///
/// Only one callback function can be registered, so the implementation should be able
/// to handle the different types of messages. A parameter to the callback function will
/// indicate the message type being received. Messages will not contain a newline character
/// at the end of the message.
/// \param loggingType Identifies the type of messages to receive callbacks for.
/// \param pCallbackFuncPtr Pointer to the callback function
/// \return GPA_STATUS_OK, unless the callbackFuncPtr is nullptr and the loggingType is not
/// GPA_LOGGING_NONE, in which case GPA_STATUS_ERROR_NULL_POINTER is returned.
GPALIB_DECL GPA_Status GPA_RegisterLoggingCallback(
    GPA_Logging_Type loggingType,
    GPA_LoggingCallbackPtrType pCallbackFuncPtr);

// Init / Destroy GPA

/// \brief Initializes the driver so that counters are exposed.
///
/// This function must be called before the rendering context or device is created.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_Initialize();

/// \brief Undo any initialization to ensure proper behavior in applications that are not being profiled.
///
/// This function must be called after the rendering context or device is released / destroyed.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_Destroy();

// Context Startup / Finish

/// \brief Opens the counters in the specified context for reading.
///
/// This function must be called after GPA_Initialize and before any other GPA functions.
/// \param[in] pContext The context to open counters for. Typically a device pointer. Refer to GPA API specific documentation for further details.
/// \param[in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits
/// \param[out] pContextId Unique identifier of the opened context
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_OpenContext(
    void* pContext,
    GPA_OpenContextFlags flags,
    GPA_ContextId* pContextId);

/// \brief Closes the counters in the specified context.
///
/// GPA functions should not be called again until the counters are reopened with GPA_OpenContext.
/// \param[in] contextId Unique identifier of the opened context
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_CloseContext(
    GPA_ContextId contextId);


// Counter Interrogation

/// \brief Get the number of counters available.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[out] pCount The value which will hold the count upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetNumCounters(
    GPA_ContextId contextId,
    gpa_uint32* pCount);

/// \brief Get the name of a specific counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter name to query. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] ppName The address which will hold the name upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterName(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppName);

/// \brief Get index of a counter given its name (case insensitive).
///
/// \param[in] contextId Unique identifier of the session
/// \param[in] pCounterName The name of the counter to get the index for.
/// \param[out] pIndex The index of the requested counter.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterIndex(
    GPA_ContextId contextId,
    const char* pCounterName,
    gpa_uint32* pIndex);

/// \brief Get Group of the specified counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter to query. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] ppGroup The address which will hold the group string upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterGroup(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppGroup);

/// \brief Get description of the specified counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter to query. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] ppDescription The address which will hold the description upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterDescription(
    GPA_ContextId contextId,
    gpa_uint32 index,
    const char** ppDescription);

/// \brief Get the counter data type of the specified counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] pCounterDataType The value which will hold the description upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterDataType(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_Data_Type* pCounterDataType);

/// \brief Get the counter usage type of the specified counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] pCounterUsageType The value which will hold the description upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterUsageType(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_Usage_Type* pCounterUsageType);

/// \brief Get the UUID of the specified counter.
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[in] index The index of the counter. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \param[out] pCounterUuid The value which will hold the counter UUID upon successful execution.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetCounterUuid(
    GPA_ContextId contextId,
    gpa_uint32 index,
    GPA_UUID* pCounterUuid);

/// \brief Get a string with the name of the specified counter data type.
///
/// Typically used to display counter types along with their name.
/// E.g. counterDataType of GPA_Data_Type_UINT64 would return "gpa_uint64".
/// \param[in] counterDataType The type to get the string for.
/// \param[out] ppTypeStr The value that will be set to contain a reference to the name of the counter data type.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetDataTypeAsStr(
    GPA_Data_Type counterDataType,
    const char** ppTypeStr);

/// \brief Get a string with the name of the specified counter usage type.
///
/// Converts the counter usage type to a string representation.
/// E.g. counterUsageType of GPA_USAGE_TYPE_PERCENTAGE would return "percentage".
/// \param[in] counterUsageType The type to get the string for.
/// \param[out] ppUsageTypeStr The value that will be set to contain a reference to the name of the counter usage type.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetUsageTypeAsStr(
    GPA_Usage_Type counterUsageType,
    const char** ppUsageTypeStr);


// Session handling

/// \brief Creates a session.
///
/// Creates a session on the supplied context. The session allows counters to be enabled,
/// samples to be measured, and stores the results of the profile.
/// \param[in] contextId The context on which to create the session.
/// \param[inout] pSessionId The address of a GPA_SessionId which will be populated with the created session Id.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_CreateSession(
    GPA_ContextId contextId,
    GPA_SessionId* pSessionId);

/// \brief Deletes a session object.
///
/// Deletes the supplied session, along with all counter results associated with the session.
/// \param[in] sessionId The session id that is to be deleted.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_DeleteSession(
    GPA_SessionId sessionId);

/// \brief Begin sampling with the currently enabled set of counters.
///
/// This must be called to begin the counter sampling process.
/// A unique sessionID will be returned which is later used to retrieve the counter values.
/// Session Identifiers are integers and always start from 1 on a newly opened context, upwards in sequence.
/// The set of enabled counters cannot be changed inside a BeginSession/EndSession sequence.
/// \param[in] sessionId Unique identifier of the GPA Session Object
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_BeginSession(
    GPA_SessionId sessionId);

/// \brief End sampling with the currently enabled set of counters.
///
/// \param[in] sessionId Unique identifier of the GPA Session Object
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EndSession(
    GPA_SessionId sessionId);


// Counter Scheduling

/// \brief Enable a specified counter.
///
/// Subsequent sampling sessions will provide values for any enabled counters.
/// Initially all counters are disabled, and must explicitly be enabled by calling this function.
/// \param[in] sessionId Unique identifier of the session on which to enable the counter.
/// \param[in] index The index of the counter to enable. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EnableCounter(
    GPA_SessionId sessionId,
    gpa_uint32 index);


/// \brief Disable a specified counter.
///
/// Subsequent sampling sessions will not provide values for any disabled counters.
/// Initially all counters are disabled, and must explicitly be enabled.
/// \param[in] sessionId Unique identifier of the session on which to disable the counter.
/// \param[in] index The index of the counter to enable. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_DisableCounter(
    GPA_SessionId sessionId,
    gpa_uint32 index);


/// \brief Enable a specified counter using the counter name (case insensitive).
///
/// Subsequent sampling sessions will provide values for any enabled counters.
/// Initially all counters are disabled, and must explicitly be enabled by calling this function.
/// \param[in] sessionId Unique identifier of the session
/// \param[in] pCounterName The name of the counter to enable.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EnableCounterByName(
    GPA_SessionId sessionId,
    const char* pCounterName);


/// \brief Disable a specified counter using the counter name (case insensitive).
///
/// Subsequent sampling sessions will not provide values for any disabled counters.
/// Initially all counters are disabled, and must explicitly be enabled.
/// \param[in] sessionId Unique identifier of the session
/// \param[in] pCounterName The name of the counter to disable.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_DisableCounterByName(
    GPA_SessionId sessionId,
    const char* pCounterName);


/// \brief Enable all counters.
///
/// Subsequent sampling sessions will provide values for all counters.
/// Initially all counters are disabled, and must explicitly be enabled by calling a function which enables them.
/// \param[in] sessionId Unique identifier of the session
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EnableAllCounters(
    GPA_SessionId sessionId);


/// \brief Disable all counters.
///
/// Subsequent sampling sessions will not provide values for any disabled counters.
/// Initially all counters are disabled, and must explicitly be enabled.
/// \param[in] sessionId Unique identifier of the session
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_DisableAllCounters(
    GPA_SessionId sessionId);


// Query Counter Scheduling

/// \brief Get the number of passes required for the currently enabled set of counters.
///
/// This represents the number of times the same sequence must be repeated to capture the counter data.
/// On each pass a different (compatible) set of counters will be measured.
/// \param[in] sessionId Unique identifier of the session
/// \param[out] pNumPasses The value of the number of passes.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetPassCount(
    GPA_SessionId sessionId,
    gpa_uint32* pNumPasses);


/// \brief Get the number of enabled counters.
///
/// \param[in] sessionId Unique identifier of the session
/// \param[out] pCount The value that will be set to the number of counters that are currently enabled.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetNumEnabledCounters(
    GPA_SessionId sessionId,
    gpa_uint32* pCount);


/// \brief Get the counter index for an enabled counter.
///
/// For example, if GPA_GetEnabledIndex returns 3, and I wanted the counter index of the first enabled counter,
/// I would call this function with enabledNumber equal to 0.
/// \param[in] sessionId Unique identifier of the session
/// \param[in] enabledNumber The number of the enabled counter to get the counter index for. Must lie between 0 and (GPA_GetNumEnabledCounters result - 1).
/// \param[out] pEnabledCounterIndex The value that will contain the index of the counter.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetEnabledIndex(
    GPA_SessionId sessionId,
    gpa_uint32 enabledNumber,
    gpa_uint32* pEnabledCounterIndex);


/// \brief Check that a counter is enabled.
///
/// \param[in] sessionId Unique identifier of the session
/// \param[in] counterIndex The index of the counter. Must lie between 0 and (GPA_GetNumCounters result - 1).
/// \return GPA_STATUS_OK is returned if the counter is enabled, GPA_STATUS_ERROR_NOT_FOUND otherwise.
GPALIB_DECL GPA_Status GPA_IsCounterEnabled(
    GPA_SessionId sessionId,
    gpa_uint32 counterIndex);

// Sample Handling

/*
Sampling in DX12/Vulkan : Usage notes

    Before creating any sample on a command list/buffer (primary or secondary), the command list/buffer (primary or secondary) should be in build state for sampling.
    Primary command list/buffer must be in build state if a sample is going to start on it (OR if secondary command list/buffer with samples is going to execute on it).
    This can be done using GPA_BeginCommandList. Any new sample must be associated with a command list/buffer (primary or secondary).

    You may create sample(s) on a command list/buffer (primary or secondary) using GPA_BeginSample. Each sample must have a unique sample Id.
    You may create sample(s) from multiple threads with the caveat that no two threads are creating samples on same command list/buffer (primary or secondary).
    Nesting of samples within a command list/buffer (primary or secondary) doesn't give accurate results. Therefore, GPA doesn't allow nesting of samples within primary command buffer.
    GPA also not allows to wrap a sample of secondary command list/buffer around a sample on its primary command list/buffer.
    If a sample has started on a command list/buffer (primary or secondary), it must be ended in the same command list/buffer.
    However, user may continue a primary command list/buffer sample to another primary command list/buffer given no other sample has been created before ending the continued sample on another command list.
    A counter will have no results for the sample created on secondary command list/buffer. Instead, you must copy secondary buffer samples to another set of samples on the associated primary command buffer.
    Copying of samples must be done after every execution of secondary command buffer.
    Command lists must also be in a closed state (for sampling) before executing them - This can be done by calling GPA_EndCommandList


mainthread
    // secondary command list/buffer samples
    GPA_BeginCommandList(sessionId1, pass1, secondaryCmd1, GPA_SECONDARY_COMMAND_LIST, secondaryCmd1Id)
    GPA_BeginSample(bundleSampleId1, secondaryCmd1Id)
    secondaryCmd1->Drawcalls
    GPA_EndSample(bundleSampleId1)
    GPA_BeginSample(bundleSampleId2, secondaryCmd1Id)
    secondaryCmd1->Drawcalls
    GPA_EndSample(bundleSampleId2)
    GPA_EndCommandList(secondaryCmd1Id)
    secondaryCmd1->close()

    // sample will span over multiple command list
    GPA_BeginCommandList(sessionId1, pass1, primaryCmd1, GPA_PRIMARY_COMMAND_LIST, primaryCmd1Id)
    GPA_BeginSample(sampleId1, primaryCmd1Id)
    primaryCmd1->drawCall()
    GPA_EndCommandList(primaryCmd1Id)
    primaryCmd1->close()

thread_1
    GPA_BeginCommandList(sessionId1, pass1, primaryCmd2, GPA_PRIMARY_COMMAND_LIST, primaryCmd2Id)
    GPA_BeginSample(sampleId2, primaryCmd2Id)
    primaryCmd2->Drawcalls
    GPA_EndSample(sampleId2)
    GPA_BeginSample(sampleId3, primaryCmd2Id)
    primaryCmd2->Drawcalls
    GPA_EndSample(sampleId3)
    GPA_EndCommandList(primaryCmd2Id)
    primaryCmd2->close()

thread_2
    GPA_BeginCommandList(sessionId1, pass1, primaryCmd3, GPA_PRIMARY_COMMAND_LIST, primaryCmd3Id)
    GPA_ContinueSampleOnCommandList(sampleId2, primaryCmd3Id) // continuing sample over multiple primary command list
    primaryCmd3->DrawCalls
    GPA_EndSample(sampleId2)
    GPA_BeginSample(sampleId4, primaryCmd3)
    primaryCmd3->Drawcalls
    GPA_EndSample(sampleId4)
    GPA_EndCommandList(primaryCmd3Id)
    primaryCmd3->close()

thread_3
    GPA_BeginCommandList(sessionId1, pass1, primaryCmd4, GPA_PRIMARY_COMMAND_LIST, primaryCmd4Id)
    GPA_BeginSample(primaryCmd4Id, sampleId5)
    primaryCmd3->DrawCalls
    GPA_EndSample(sampleId5)
    secondaryCmd1->execute()
    GPA_CopySecondarySamples(secondaryCmd1, primaryCmd4Id, 2, [sampleId5, sampleId6]) // continuing bundle sample over primary command list
    secondaryCmd1->execute()
    GPA_EndCommandList(primaryCmd4Id)
*/

/// \brief Begin command list for sampling
///
/// You will be unable to create samples on the specified command list/buffer before GPA_BeginCommandList is called
/// Command list corresponds to ID3D12GraphicsCommandList in DX12 and vkCommandBuffer in Vulkan.
/// In OpenCL/OpenGL/HSA/DX11, use GPA_NULL_COMMAND_LIST as pCommandList parameter and GPA_NO_COMMAND_LIST as gpaCommandListType
/// \param[in] sessionId Unique identifier of the GPA Session Object
/// \param[in] passIndex 0-based index of the pass
/// \param[in] pCommandList the command list on which to begin sampling - ignored in OpenCL/HSA/OpenGL/DX11 applications
/// \param[in] gpaCommandListType gpa command list type
/// \param[out] pCommandListId GPA created unique command list id
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_BeginCommandList(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex,
    void* pCommandList,
    GPA_Command_List_Type gpaCommandListType,
    GPA_CommandListId* pCommandListId);


/// \brief End command list for sampling
///
/// You will be unable to create samples on the specified command list/buffer after GPA_EndCommandList is called
/// \param[in] commandListId the command list on which to end sampling - ignored in OpenCL/HSA/OpenGL applications
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EndCommandList(
    GPA_CommandListId commandListId);


/// \brief Begin a sample in a command list
///
/// Each sample must be associated with a GPA command list.
/// Samples can be created by multiple threads provided no two threads are creating samples on same command list/buffer.
/// You must provide a unique Id for every new sample.
/// You may create as many samples as needed. However, nesting of samples is not allowed.
/// Each sample must be wrapped in sequence of GPA_BeginSample/GPA_EndSample before starting another one.
/// A sample can be started in one primary command list/buffer and continued/ended on another primary command list/buffer - See GPA_ContinueSampleOnCommandList.
/// \param[in] sampleId unique sample id
/// \param[in] commandListId unique command list id
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_BeginSample(
    gpa_uint32 sampleId,
    GPA_CommandListId commandListId);


/// \brief End a sample in a command list.
///
/// Each sample must be associated with a GPA command list.
/// Samples can be created by using multiple threads provided no two threads are creating samples on same command list/buffer.
/// You must provide a unique Id for every new sample.
/// You may create as many samples as needed. However, nesting of samples is not allowed.
/// Each sample must be wrapped in sequence of GPA_BeginSample/GPA_EndSample before starting another one.
/// A sample can be started in one primary command list/buffer and continued/ended on another primary command list/buffer - See GPA_ContinueSampleOnCommandList.
/// \param[in] commandListId command list id on which the sample is ending - the command list may be different than the command list on which the sample was started
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_EndSample(
    GPA_CommandListId commandListId);


/// \brief Continue a primary command list sample on another primary command list
///
/// For use with the explicit graphics APIs (DX12 and Vulkan).
/// Each sample must be associated with a command list.
/// Samples can be started on one primary command list and continued/ended on another primary command list.
/// \param[in] srcSampleId source sample id for the sample being continued on a different command list
/// \param[in] primaryCommandListId primary command list id on which sample is continuing
GPALIB_DECL GPA_Status GPA_ContinueSampleOnCommandList(
    gpa_uint32 srcSampleId,
    GPA_CommandListId primaryCommandListId);


/// \brief Copy a set of samples from a secondary command list/buffer sample back to the primary command list/buffer that executed the secondary command list/buffer
///
/// For use with the explicit graphics APIs (DX12 and Vulkan).
/// Each sample must be associated with a command list.
/// GPA doesn't collect data for the samples created on secondary command list/buffer unless they are copied to a new set of samples for the primary command list/buffer.
/// \param[in] secondaryCmdListId secondary command list/buffer where the secondary samples were created
/// \param[in] primaryCmdListId primary command list/buffer to which the samples results should be copied. This should be the command list/buffer that executed the secondary command lilst/buffer.
/// \param[in] numSamples number of secondary samples
/// \param[in] pNewSampleIds new sample ids on a primary command list
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_CopySecondarySamples(
    GPA_CommandListId secondaryCmdListId,
    GPA_CommandListId primaryCmdListId,
    gpa_uint32 numSamples,
    gpa_uint32* pNewSampleIds);


/// \brief Returns the number of samples created for the specified session
///
/// This is useful if samples are conditionally created and a count is not kept.
/// \param[in] sessionId pass Id to get the number of samples for.
/// \param[out] pSampleCount The value that will be set to the number of samples contained within the session.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetSampleCount(
    GPA_SessionId sessionId,
    gpa_uint32* pSampleCount);

// Query Results

/// \brief Determine if the pass has finished or not
///
/// After sampling a workload, results may be available immediately or take a certain amount of time to become available.
/// This function allows you to determine when the pass has finished and associated resources are no longer needed in the application
/// The function does not block, permitting periodic polling.
/// The application must not free its resources until this function returns GPA_STATUS_OK.
/// \param[in] sessionId session id
/// \param[in] passIndex 0-based index of the pass
/// \return GPA_STATUS_OK if pass is complete else GPA_STATUS_RESULT_NOT_READY
GPALIB_DECL GPA_Status GPA_IsPassComplete(
    GPA_SessionId sessionId,
    gpa_uint32 passIndex);


/// \brief Determine if all samples within a session are available.
///
/// After a sampling session results may be available immediately or take a certain amount of time to become available.
/// This function allows you to determine when the results of a session can be read.
/// The function does not block, permitting periodic polling.
/// To block until a sample is ready use GPA_GetSampleResult instead.
/// \param[in] sessionId The value that will be set to the session identifier.
/// \return GPA_STATUS_OK if pass is complete else GPA_STATUS_RESULT_NOT_READY
GPALIB_DECL GPA_Status GPA_IsSessionComplete(
    GPA_SessionId sessionId);


/// \brief Get the sample result size
///
/// \param[in] sessionId Unique identifier of the GPA Session Object
/// \param[in] sampleResultSizeInBytes size of sample in bytes
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetPerSampleResultSize(
    GPA_SessionId sessionId,
    gpa_uint32* sampleResultSizeInBytes);


/// \brief Get counter data of the sample. This function will block until results are ready. Use GPA_IsSessionComplete to check if results are ready
///
/// \param[in] sessionId The session identifier with the sample you wish to retrieve the result of.
/// \param[in] sampleID The identifier of the sample to get the result for.
/// \param[in] sampleResultSizeInBytes size of sample in bytes
/// \param[out] pCounterSampleResults address to which the counter data for the sample will be copied to
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetSampleResult(
    GPA_SessionId sessionId,
    gpa_uint32 sampleID,
    gpa_uint64 sampleResultSizeInBytes,
    void* pCounterSampleResults);


// Status/Error Query

/// \brief Get a string representation of a GPA status value.
///
/// Provides a simple method to convert a status enum value into a string which can be used to display log messages.
/// \param[in] status The status to convert into a string.
/// \return A string which describes the supplied status.
GPALIB_DECL const char* GPA_GetStatusAsStr(
    GPA_Status status);

// Device Query

/// \brief Get the GPU device and revision id associated with the current context
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[out] pDeviceID The value that will be set to the device id.
/// \param[out] pRevisionID The value that will be set to the device revision id.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetDeviceAndRevisionId(
    GPA_ContextId contextId,
    gpa_uint32* pDeviceID,
    gpa_uint32* pRevisionID);


/// \brief Get the GPU device name
///
/// \param[in] contextId Unique identifier of the opened context
/// \param[out] ppDeviceName The value that will be set to the device name.
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetDeviceName(
    GPA_ContextId contextId,
    const char** ppDeviceName);

// Internal function

/// \brief Internal function. Pass draw call counts to GPA for internal purposes.
///
/// \param iCounts the draw counts for the current frame
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_InternalSetDrawCallCounts(
    const int iCounts);


/// \brief Get the GPA Api function table
///
/// \param[out] ppGPAFuncTable pointer to pointer of GPAApi - GPA Function table structure
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
GPALIB_DECL GPA_Status GPA_GetFuncTable(
    void** ppGPAFuncTable);

#else /// Not USE_GPA

#define RETURN_GPA_SUCCESS return GPA_STATUS_OK
#define RETURN_GPA_RESULT_READY return GPA_STATUS_RESULT_READY;

// Logging
static  GPA_Status GPA_RegisterLoggingCallback(GPA_Logging_Type, GPA_LoggingCallbackPtrType) { RETURN_GPA_SUCCESS; }

// Init / Destroy GPA
static GPA_Status GPA_Initialize() { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_Destroy() { RETURN_GPA_SUCCESS; }

// Context Startup / Finish
static GPA_Status GPA_OpenContext(void*, GPA_OpenContextFlags, GPA_ContextId*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_CloseContext(GPA_ContextId) { RETURN_GPA_SUCCESS; }

// Counter Interrogation
static GPA_Status GPA_GetNumCounters(GPA_ContextId, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterName(GPA_ContextId, gpa_uint32, const char**) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterIndex(GPA_ContextId, const char*, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterGroup(GPA_ContextId, gpa_uint32, const char**) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterDescription(GPA_ContextId, gpa_uint32, const char**) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterDataType(GPA_ContextId, gpa_uint32, GPA_Data_Type*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterUsageType(GPA_ContextId, gpa_uint32, GPA_Usage_Type*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetDataTypeAsStr(GPA_Data_Type, const char**) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetUsageTypeAsStr(GPA_Usage_Type, const char**) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetCounterUuid(GPA_ContextId, gpa_uint32, GPA_UUID*) { RETURN_GPA_SUCCESS; }

// Session handling
static GPA_Status GPA_CreateSession(GPA_ContextId, GPA_SessionId*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_DeleteSession(GPA_SessionId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_BeginSession(GPA_SessionId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_EndSession(GPA_SessionId) { RETURN_GPA_SUCCESS; }

// Counter Scheduling
static GPA_Status GPA_EnableCounter(GPA_SessionId, gpa_uint32) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_DisableCounter(GPA_SessionId, gpa_uint32) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_EnableCounterByName(GPA_SessionId, const char*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_DisableCounterByName(GPA_SessionId, const char*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_EnableAllCounters(GPA_SessionId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_DisableAllCounters(GPA_SessionId) { RETURN_GPA_SUCCESS; }

// Query Counter Scheduling
static GPA_Status GPA_GetPassCount(GPA_SessionId, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetNumEnabledCounters(GPA_SessionId, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetEnabledIndex(GPA_SessionId, gpa_uint32, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_IsCounterEnabled(GPA_SessionId, gpa_uint32) { RETURN_GPA_SUCCESS; }

// Sample Handling
static GPA_Status GPA_BeginCommandList(GPA_SessionId, gpa_uint32, void*, GPA_Command_List_Type, GPA_CommandListId*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_EndCommandList(GPA_CommandListId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_BeginSample(gpa_uint32, GPA_CommandListId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_EndSample(GPA_CommandListId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_ContinueSampleOnCommandList(gpa_uint32, GPA_CommandListId) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_CopySecondarySamples(GPA_CommandListId, GPA_CommandListId, gpa_uint32, gpa_uint32*) { RETURN_GPA_SUCCESS; };
static GPA_Status GPA_GetSampleCount(GPA_SessionId, gpa_uint32*) { RETURN_GPA_SUCCESS; }

// Query Results
static GPA_Status GPA_IsSessionComplete(GPA_SessionId) { RETURN_GPA_RESULT_READY; }
static GPA_Status GPA_IsPassComplete(GPA_SessionId, gpa_uint32) { RETURN_GPA_RESULT_READY; }
static GPA_Status GPA_GetPerSampleResultSize(GPA_SessionId, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetSampleResult(GPA_SessionId, gpa_uint32, gpa_uint64, void*) { RETURN_GPA_SUCCESS; }

// Status/Error Query
static const char* GPA_GetStatusAsStr(GPA_Status) { return nullptr; }

// Device Query
static GPA_Status GPA_GetDeviceAndRevisionId(GPA_ContextId, gpa_uint32*, gpa_uint32*) { RETURN_GPA_SUCCESS; }
static GPA_Status GPA_GetDeviceName(GPA_ContextId, const char**) { RETURN_GPA_SUCCESS; }

// Internal function
static GPA_Status GPA_InternalSetDrawCallCounts(const int) { RETURN_GPA_SUCCESS; }

// GPA API table
static GPA_Status GPA_GetFuncTable(void** ppGPAFuncTable)
{
    /// All of the GPA functions will reside in user memory as it will be compiled along with the user code
    /// Fill the function table with the function in user memory
    GPAApi* pApi = reinterpret_cast<GPAApi*>(*ppGPAFuncTable);

#define GPA_FUNCTION_PREFIX( func) pApi->func = func;
#include "GPAFunctions.h"
#undef GPA_FUNCTION_PREFIX

    pApi->m_apiId = GPA_API_CURRENT_UUID;
    return GPA_STATUS_OK;
}
#endif // USE_GPA

#endif // _GPUPERFAPI_H_
