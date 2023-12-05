//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief This file contains the main entry points into GPA
//==============================================================================

#pragma message("Warning: You are referencing a deprecated file.")

// Deprecated header
#include "gpu_perf_api.h"

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetVersion(gpa_uint32* major_version, gpa_uint32* minor_version, gpa_uint32* build, gpa_uint32* update_version)
{
    GpaStatus gpa_status = GpaGetVersion(reinterpret_cast<GpaUInt32*>(major_version),
                                         reinterpret_cast<GpaUInt32*>(minor_version),
                                         reinterpret_cast<GpaUInt32*>(build),
                                         reinterpret_cast<GpaUInt32*>(update_version));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetFuncTable(void* gpa_func_table)
{
    try
    {
        PROFILE_FUNCTION(GPA_GetFuncTable);
        TRACE_FUNCTION(GPA_GetFuncTable);

        if(nullptr == gpa_func_table)
        {
            return GPA_STATUS_ERROR_NULL_POINTER;
        }

        GPAFunctionTable* pFuncTable = reinterpret_cast<GPAFunctionTable*>(gpa_func_table);

        bool       correctMajorVersion    = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER == pFuncTable->m_majorVer;
        gpa_uint32 clientSuppliedMinorVer = pFuncTable->m_minorVer;

        pFuncTable->m_majorVer = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
        pFuncTable->m_minorVer = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

        if (!correctMajorVersion)
        {
            // NOTE: in most cases a client won't have registered a logging callback yet
            GPA_LOG_ERROR("Client major version mismatch.");
            return GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH;
        }

        if (clientSuppliedMinorVer > GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        {
            // NOTE: in most cases a client won't have registered a logging callback yet
            GPA_LOG_ERROR("Client minor version mismatch.");
            return GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH;
        }

        GPAFunctionTable gpaFuncTable;
#define GPA_DEPRECATED_FUNCTION_PREFIX(func) gpaFuncTable.func = func;
// Deprecated header
#include "gpu_perf_api_functions.h"
#undef GPA_DEPRECATED_FUNCTION_PREFIX

        // if the client-supplied table is smaller than GPA's table,
        // this will only copy a subset of the table, ignoring the
        // functions at the end of the table
        memcpy(pFuncTable, &gpaFuncTable, clientSuppliedMinorVer);

        GPA_INTERNAL_LOG(GPA_GetFuncTable, MAKE_PARAM_STRING(gpa_func_table));

        return GPA_STATUS_OK;
    }
    catch (...)
    {
        return GPA_STATUS_ERROR_EXCEPTION;
    }
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_RegisterLoggingCallback(GPA_Logging_Type logging_type, GPA_LoggingCallbackPtrType callback_func_ptr)
{
    GpaStatus gpa_status = GpaRegisterLoggingCallback(static_cast<GpaLoggingType>(logging_type), reinterpret_cast<GpaLoggingCallbackPtrType>(callback_func_ptr));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_Initialize(GPA_InitializeFlags gpa_initialize_flags)
{
    GpaStatus gpa_status = GpaInitialize(static_cast<GpaInitializeFlags>(gpa_initialize_flags));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_Destroy()
{
    GpaStatus gpa_status = GpaDestroy();

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_OpenContext(void* api_context, GPA_OpenContextFlags gpa_open_context_flags, GPA_ContextId* gpa_context_id)
{
    GpaStatus gpa_status = GpaOpenContext(api_context, static_cast<GpaOpenContextFlags>(gpa_open_context_flags), reinterpret_cast<GpaContextId*>(gpa_context_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_CloseContext(GPA_ContextId gpa_context_id)
{
    GpaStatus gpa_status = GpaCloseContext(reinterpret_cast<GpaContextId>(gpa_context_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetSupportedSampleTypes(GPA_ContextId gpa_context_id, GPA_ContextSampleTypeFlags* sample_types)
{
    GpaStatus gpa_status = GpaGetSupportedSampleTypes(reinterpret_cast<GpaContextId>(gpa_context_id), reinterpret_cast<GpaContextSampleTypeFlags*>(sample_types));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetDeviceAndRevisionId(GPA_ContextId gpa_context_id, gpa_uint32* device_id, gpa_uint32* revision_id)
{
    GpaStatus gpa_status = GpaGetDeviceAndRevisionId(reinterpret_cast<GpaContextId>(gpa_context_id),
                                                     reinterpret_cast<GpaUInt32*>(device_id),
                                                     reinterpret_cast<GpaUInt32*>(revision_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetDeviceName(GPA_ContextId gpa_context_id, const char** device_name)
{
    GpaStatus gpa_status = GpaGetDeviceName(reinterpret_cast<GpaContextId>(gpa_context_id), device_name);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetNumCounters(GPA_ContextId gpa_context_id, gpa_uint32* number_of_counters)
{
    GpaStatus gpa_status = GpaGetNumCounters(reinterpret_cast<GpaContextId>(gpa_context_id), reinterpret_cast<GpaUInt32*>(number_of_counters));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterName(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, const char** counter_name)
{
    GpaStatus gpa_status = GpaGetCounterName(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), counter_name);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterIndex(GPA_ContextId gpa_context_id, const char* counter_name, gpa_uint32* counter_index)
{
    GpaStatus gpa_status = GpaGetCounterIndex(reinterpret_cast<GpaContextId>(gpa_context_id), counter_name, reinterpret_cast<GpaUInt32*>(counter_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterGroup(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, const char** counter_group)
{
    GpaStatus gpa_status = GpaGetCounterGroup(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), counter_group);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterDescription(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, const char** counter_description)
{
    GpaStatus gpa_status = GpaGetCounterDescription(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), counter_description);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterDataType(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, GPA_Data_Type* counter_data_type)
{
    GpaStatus gpa_status = GpaGetCounterDataType(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), reinterpret_cast<GpaDataType*>(counter_data_type));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterUsageType(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, GPA_Usage_Type* counter_usage_type)
{
    GpaStatus gpa_status = GpaGetCounterUsageType(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), reinterpret_cast<GpaUsageType*>(counter_usage_type));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterUuid(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, GPA_UUID* counter_uuid)
{
    GpaStatus gpa_status = GpaGetCounterUuid(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), reinterpret_cast<GpaUuid*>(counter_uuid));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetCounterSampleType(GPA_ContextId gpa_context_id, gpa_uint32 counter_index, GPA_Counter_Sample_Type* counter_sample_type)
{
    GpaStatus gpa_status = GpaGetCounterSampleType(reinterpret_cast<GpaContextId>(gpa_context_id), static_cast<GpaUInt32>(counter_index), reinterpret_cast<GpaCounterSampleType*>(counter_sample_type));

    return static_cast<GPA_Status>(gpa_status);
}

GPA_LIB_DECL GPA_Status GPA_GetDataTypeAsStr(GPA_Data_Type counter_data_type, const char** data_type_as_str)
{
    GpaStatus gpa_status = GpaGetDataTypeAsStr(static_cast<GpaDataType>(counter_data_type), data_type_as_str);

    return static_cast<GPA_Status>(gpa_status);
}

GPA_LIB_DECL GPA_Status GPA_GetUsageTypeAsStr(GPA_Usage_Type counter_usage_type, const char** usage_type_as_str)
{
    GpaStatus gpa_status = GpaGetUsageTypeAsStr(static_cast<GpaUsageType>(counter_usage_type), usage_type_as_str);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_CreateSession(GPA_ContextId gpa_context_id, GPA_Session_Sample_Type gpa_session_sample_type, GPA_SessionId* gpa_session_id)
{
    GpaStatus gpa_status = GpaCreateSession(reinterpret_cast<GpaContextId>(gpa_context_id),
                                            static_cast<GpaSessionSampleType>(gpa_session_sample_type),
                                            reinterpret_cast<GpaSessionId*>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_DeleteSession(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaDeleteSession(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_BeginSession(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaBeginSession(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EndSession(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaEndSession(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EnableCounter(GPA_SessionId gpa_session_id, gpa_uint32 counter_index)
{
    GpaStatus gpa_status = GpaEnableCounter(reinterpret_cast<GpaSessionId>(gpa_session_id), static_cast<GpaUInt32>(counter_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_DisableCounter(GPA_SessionId gpa_session_id, gpa_uint32 counter_index)
{
    GpaStatus gpa_status = GpaDisableCounter(reinterpret_cast<GpaSessionId>(gpa_session_id), static_cast<GpaUInt32>(counter_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EnableCounterByName(GPA_SessionId gpa_session_id, const char* counter_name)
{
    GpaStatus gpa_status = GpaEnableCounterByName(reinterpret_cast<GpaSessionId>(gpa_session_id), counter_name);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_DisableCounterByName(GPA_SessionId gpa_session_id, const char* counter_name)
{
    GpaStatus gpa_status = GpaDisableCounterByName(reinterpret_cast<GpaSessionId>(gpa_session_id), counter_name);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EnableAllCounters(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaEnableAllCounters(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_DisableAllCounters(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaDisableAllCounters(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetPassCount(GPA_SessionId gpa_session_id, gpa_uint32* number_of_passes)
{
    GpaStatus gpa_status = GpaGetPassCount(reinterpret_cast<GpaSessionId>(gpa_session_id), reinterpret_cast<GpaUInt32*>(number_of_passes));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetNumEnabledCounters(GPA_SessionId gpa_session_id, gpa_uint32* enabled_counter_count)
{
    GpaStatus gpa_status = GpaGetNumEnabledCounters(reinterpret_cast<GpaSessionId>(gpa_session_id), reinterpret_cast<GpaUInt32*>(enabled_counter_count));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetEnabledIndex(GPA_SessionId gpa_session_id, gpa_uint32 enabled_number, gpa_uint32* enabled_counter_index)
{
    GpaStatus gpa_status = GpaGetEnabledIndex(reinterpret_cast<GpaSessionId>(gpa_session_id), static_cast<GpaUInt32>(enabled_number), reinterpret_cast<GpaUInt32*>(enabled_counter_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_IsCounterEnabled(GPA_SessionId gpa_session_id, gpa_uint32 counter_index)
{
    GpaStatus gpa_status = GpaIsCounterEnabled(reinterpret_cast<GpaSessionId>(gpa_session_id), static_cast<GpaUInt32>(counter_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_BeginCommandList(GPA_SessionId        gpa_session_id,
                                            gpa_uint32            pass_index,
                                            void*                 command_list,
                                            GPA_Command_List_Type command_list_type,
                                            GPA_CommandListId*    gpa_command_list_id)
{
    GpaStatus gpa_status = GpaBeginCommandList(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                               static_cast<GpaUInt32>(pass_index),
                                               command_list,
                                               static_cast<GpaCommandListType>(command_list_type),
                                               reinterpret_cast<GpaCommandListId*>(gpa_command_list_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EndCommandList(GPA_CommandListId gpa_command_list_id)
{
    GpaStatus gpa_status = GpaEndCommandList(reinterpret_cast<GpaCommandListId>(gpa_command_list_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_BeginSample(gpa_uint32 sample_id, GPA_CommandListId gpa_command_list_id)
{
    GpaStatus gpa_status = GpaBeginSample(static_cast<GpaUInt32>(sample_id),
                                          reinterpret_cast<GpaCommandListId>(gpa_command_list_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_EndSample(GPA_CommandListId gpa_command_list_id)
{
    GpaStatus gpa_status = GpaEndSample(reinterpret_cast<GpaCommandListId>(gpa_command_list_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_ContinueSampleOnCommandList(gpa_uint32 source_sample_id, GPA_CommandListId primary_gpa_command_list_id)
{
    GpaStatus gpa_status = GpaContinueSampleOnCommandList(static_cast<GpaUInt32>(source_sample_id),
                                                          reinterpret_cast<GpaCommandListId>(primary_gpa_command_list_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_CopySecondarySamples(GPA_CommandListId secondary_gpa_command_list_id,
                                                GPA_CommandListId primary_gpa_command_list_id,
                                                gpa_uint32        number_of_samples,
                                                gpa_uint32*       new_sample_ids)
{
    GpaStatus gpa_status = GpaCopySecondarySamples(reinterpret_cast<GpaCommandListId>(secondary_gpa_command_list_id),
                                                   reinterpret_cast<GpaCommandListId>(primary_gpa_command_list_id),
                                                   static_cast<GpaUInt32>(number_of_samples),
                                                   reinterpret_cast<GpaUInt32*>(new_sample_ids));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetSampleCount(GPA_SessionId gpa_session_id, gpa_uint32* sample_count)
{
    GpaStatus gpa_status = GpaGetSampleCount(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                             reinterpret_cast<GpaUInt32*>(sample_count));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetSampleId(GPA_SessionId gpa_session_id, gpa_uint32 index, gpa_uint32* sample_id)
{
    GpaStatus gpa_status = GpaGetSampleId(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                          static_cast<GpaUInt32>(index),
                                          reinterpret_cast<GpaUInt32*>(sample_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_IsSessionComplete(GPA_SessionId gpa_session_id)
{
    GpaStatus gpa_status = GpaIsSessionComplete(reinterpret_cast<GpaSessionId>(gpa_session_id));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_IsPassComplete(GPA_SessionId gpa_session_id, gpa_uint32 pass_index)
{
    GpaStatus gpa_status = GpaIsPassComplete(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                             static_cast<GpaUInt32>(pass_index));

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetSampleResultSize(GPA_SessionId gpa_session_id, gpa_uint32 sample_id, size_t* sample_result_size_in_bytes)
{
    GpaStatus gpa_status = GpaGetSampleResultSize(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                                  static_cast<GpaUInt32>(sample_id),
                                                  sample_result_size_in_bytes);

    return static_cast<GPA_Status>(gpa_status);
}

//-----------------------------------------------------------------------------
GPA_LIB_DECL GPA_Status GPA_GetSampleResult(GPA_SessionId gpa_session_id, gpa_uint32 sample_id, size_t sample_result_size_in_bytes, void* counter_sample_results)
{
    GpaStatus gpa_status = GpaGetSampleResult(reinterpret_cast<GpaSessionId>(gpa_session_id),
                                                  static_cast<GpaUInt32>(sample_id),
                                                  sample_result_size_in_bytes,
                                                  counter_sample_results);

    return static_cast<GPA_Status>(gpa_status);
}

GPA_LIB_DECL const char* GPA_GetStatusAsStr(GPA_Status gpa_status_as_str)
{
    return GpaGetStatusAsStr(static_cast<GpaStatus>(gpa_status_as_str));
}
