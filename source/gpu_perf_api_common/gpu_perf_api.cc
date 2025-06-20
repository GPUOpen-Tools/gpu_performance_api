//==============================================================================
// Copyright (c) 2010-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief This file contains the main entry points into GPA.
//==============================================================================

/// Macro to mark a function for exporting.
#ifdef _LINUX
#define GPA_LIB_DECL extern "C" __attribute__((visibility("default")))
#else
#define GPA_LIB_DECL extern "C" __declspec(dllexport)
#endif

#include "gpu_performance_api/gpu_perf_api.h"

#include <mutex>
#include <sstream>

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_implementor_interface.h"
#include "gpu_perf_api_common/gpa_profiler.h"
#include "gpu_perf_api_common/gpa_session_interface.h"
#include "gpu_perf_api_common/gpa_unique_object.h"
#include "gpu_perf_api_common/gpa_version.h"
#include "gpu_perf_api_common/logging.h"

namespace
{
    IGpaImplementor* gpa_imp = nullptr;  ///< GPA implementor instance.
}  // namespace

extern IGpaImplementor* CreateImplementor();                   ///< Function to create the GPA implementor instance.
extern void             DestroyImplementor(IGpaImplementor*);  ///< Function to destroy the GPA implementor instance.

/// Macro to check for a null parameter.
#define CHECK_NULL_PARAM(parameter_name)                                 \
    if (!parameter_name)                                                 \
    {                                                                    \
        GPA_LOG_DEBUG_ERROR("Parameter '" #parameter_name "' is NULL."); \
        return kGpaStatusErrorNullPointer;                               \
    }

/// Macro to check for out of range counter index.
#define CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, gpa_context_id)                                     \
    GpaUInt32 num_counters;                                                                         \
    GpaStatus num_counter_status = gpa_context_id->GetNumCounters(&num_counters);                   \
    if (kGpaStatusOk != num_counter_status)                                                         \
    {                                                                                               \
        return num_counter_status;                                                                  \
    }                                                                                               \
    if (index >= num_counters)                                                                      \
    {                                                                                               \
        GPA_LOG_ERROR("Parameter %s is %d but must be less than %d.", #index, index, num_counters); \
        return kGpaStatusErrorIndexOutOfRange;                                                      \
    }

/// Macro to check if a context is open.
#define CHECK_CONTEXT_IS_OPEN(context)                     \
    if (!context->IsOpen())                                \
    {                                                      \
        GPA_LOG_ERROR("Context has not been not opened."); \
        return kGpaStatusErrorContextNotOpen;              \
    }

/// Macro to check if a session exists.
#define CHECK_SESSION_ID_EXISTS(session_id)             \
    if (nullptr == gpa_imp)                             \
    {                                                   \
        GPA_LOG_ERROR("GPA has not been initialized."); \
        return kGpaStatusErrorGpaNotInitialized;        \
    }                                                   \
    if (!session_id)                                    \
    {                                                   \
        GPA_LOG_ERROR("Session object is null.");       \
        return kGpaStatusErrorNullPointer;              \
    }                                                   \
    if (!gpa_imp->DoesSessionExist(session_id))         \
    {                                                   \
        GPA_LOG_ERROR("Unknown session object.");       \
        return kGpaStatusErrorSessionNotFound;          \
    }

/// Macro to check if a command list exists.
#define CHECK_COMMAND_LIST_ID_EXISTS(command_list_id)    \
    if (nullptr == gpa_imp)                              \
    {                                                    \
        GPA_LOG_ERROR("GPA has not been initialized.");  \
        return kGpaStatusErrorGpaNotInitialized;         \
    }                                                    \
    if (!command_list_id)                                \
    {                                                    \
        GPA_LOG_ERROR("Command list object is null.");   \
        return kGpaStatusErrorNullPointer;               \
    }                                                    \
    if (!gpa_imp->DoesCommandListExist(command_list_id)) \
    {                                                    \
        GPA_LOG_ERROR("Unknown command list object.");   \
        return kGpaStatusErrorCommandListNotFound;       \
    }

/// Macro to check if a session is still running.
#define CHECK_SESSION_RUNNING(session_id)                                                               \
    if ((*session_id)->IsSessionRunning())                                                              \
    {                                                                                                   \
        GPA_LOG_ERROR("Session is still running. End the session before querying sample information."); \
        return kGpaStatusErrorSessionNotEnded;                                                          \
    }

/// Macro to check if a session is running while enabling/disabling counters.
#define CHECK_SESSION_RUNNING_FOR_COUNTERS(session_id)                          \
    if ((*session_id)->IsSessionRunning())                                      \
    {                                                                           \
        GPA_LOG_ERROR("Counter state cannot change while session is running."); \
        return kGpaStatusErrorCannotChangeCountersWhenSampling;                 \
    }

#define MAKE_PARAM_STRING(X) #X << " : " << X << " "

/// Macro to check if a context exists and is open.
[[nodiscard]] GpaStatus CheckGPAContentIdExistsAndIsOpen(GpaContextId gpa_context_id)
{
    if (!gpa_imp)
    {
        GPA_LOG_ERROR("GPA has not been initialized.");
        return kGpaStatusErrorGpaNotInitialized;
    }
    if (!gpa_context_id)
    {
        GPA_LOG_ERROR("Context object is null.");
        return kGpaStatusErrorNullPointer;
    }
    if (!gpa_imp->DoesContextExist(gpa_context_id))
    {
        GPA_LOG_ERROR("Unknown context object.");
        return kGpaStatusErrorContextNotFound;
    }
    CHECK_CONTEXT_IS_OPEN(gpa_context_id->Object())
    return kGpaStatusOk;
}

/// Validate that sample id exists in a pass.
///
/// @param [in] pass The pass.
/// @param [in] sample_id The sample id.
///
/// @retval kGpaStatusOk if the sample id exists in the pass.
/// @retval kGpaStatusErrorFailed The supplied pass was null.
/// @retval kGpaStatusErrorSampleNotFound The sample could not be found.
GpaStatus CheckSampleIdExistsInPass(GpaPass* pass, GpaUInt32 sample_id)
{
    if (nullptr == pass)
    {
        GPA_LOG_ERROR("Invalid pass.");
        return kGpaStatusErrorFailed;
    }

    if (!pass->DoesSampleExist(sample_id))
    {
        GPA_LOG_ERROR("Sample not found in pass.");
        return kGpaStatusErrorSampleNotFound;
    }

    return kGpaStatusOk;
}

/// @brief Validate that sample id exists in a session.
///
/// @param [in] session_id The session id.
/// @param [in] sample_id The sample id.
///
/// @retval kGpaStatusOk if the sample id exists in the pass.
/// @retval kGpaStatusErrorSampleNotFound The sample could not be found.
GpaStatus CheckSampleIdExistsInSession(GpaSessionId session_id, GpaUInt32 sample_id)
{
    if (!(*session_id)->DoesSampleExist(sample_id))
    {
        GPA_LOG_ERROR("Sample not found in session.");
        return kGpaStatusErrorSampleNotFound;
    }

    return kGpaStatusOk;
}

/// Macro to check the session sample type.
#define CHECK_SESSION_SAMPLE_TYPE(sample_type)                                     \
    GpaSessionSampleType session_sample_type = (*gpa_session_id)->GetSampleType(); \
    if (sample_type != session_sample_type)                                        \
    {                                                                              \
        GPA_LOG_ERROR("Session does not support the correct sample type.");        \
        return kGpaStatusErrorIncompatibleSampleTypes;                             \
    }

/// Macro to check the session sample type when 2 sample types are valid.
#define CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(sample_type, additional_sample_type)              \
    GpaSessionSampleType session_sample_type = (*gpa_session_id)->GetSampleType();           \
    if (sample_type != session_sample_type && additional_sample_type != session_sample_type) \
    {                                                                                        \
        GPA_LOG_ERROR("Session does not support the correct sample type.");                  \
        return kGpaStatusErrorIncompatibleSampleTypes;                                       \
    }

GPA_LIB_DECL GpaStatus GpaGetVersion(GpaUInt32* major_version, GpaUInt32* minor_version, GpaUInt32* build, GpaUInt32* update_version)
{
    try
    {
        PROFILE_FUNCTION(GpaGetVersion);
        TRACE_FUNCTION(GpaGetVersion);

        CHECK_NULL_PARAM(major_version);
        CHECK_NULL_PARAM(minor_version);
        CHECK_NULL_PARAM(build);
        CHECK_NULL_PARAM(update_version);

        *major_version  = GPA_MAJOR_VERSION;
        *minor_version  = GPA_MINOR_VERSION;
        *build          = GPA_BUILD_NUMBER;
        *update_version = GPA_UPDATE_VERSION;

        GPA_INTERNAL_LOG(GpaGetVersion,
                         MAKE_PARAM_STRING(*major_version)
                             << MAKE_PARAM_STRING(*minor_version) << MAKE_PARAM_STRING(*build) << MAKE_PARAM_STRING(*update_version));

        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetFuncTable(void* gpa_func_table)
{
    try
    {
        PROFILE_FUNCTION(GpaGetFuncTable);
        TRACE_FUNCTION(GpaGetFuncTable);

        CHECK_NULL_PARAM(gpa_func_table);

        GpaFunctionTable* function_table = reinterpret_cast<GpaFunctionTable*>(gpa_func_table);

        bool      correct_major_version     = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER == function_table->major_version;
        GpaUInt32 client_supplied_minor_ver = function_table->minor_version;

        function_table->major_version = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
        function_table->minor_version = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

        if (!correct_major_version)
        {
            // NOTE: In most cases a client won't have registered a logging callback yet.
            GPA_LOG_ERROR("Client major version mismatch.");
            return kGpaStatusErrorLibLoadMajorVersionMismatch;
        }

        if (client_supplied_minor_ver > GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        {
            // NOTE: In most cases a client won't have registered a logging callback yet.
            GPA_LOG_ERROR("Client minor version mismatch.");
            return kGpaStatusErrorLibLoadMinorVersionMismatch;
        }

        GpaFunctionTable gpa_function_table;
#define GPA_FUNCTION_PREFIX(func) gpa_function_table.func = func;
#include "gpu_performance_api/gpu_perf_api_functions.h"
#undef GPA_FUNCTION_PREFIX

        // If the client-supplied table is smaller than GPA's table,
        // this will only copy a subset of the table, ignoring the
        // functions at the end of the table.
        memcpy(function_table, &gpa_function_table, client_supplied_minor_ver);

        GPA_INTERNAL_LOG(GpaGetFuncTable, MAKE_PARAM_STRING(gpa_func_table));

        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaRegisterLoggingCallback(GpaLoggingType logging_type, GpaLoggingCallbackPtrType callback_func_ptr)
{
    try
    {
        if (nullptr == callback_func_ptr && logging_type != kGpaLoggingNone)
        {
            GPA_LOG_DEBUG_ERROR("Parameter 'callback_func_ptr' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        GpaLogger::Instance()->SetLoggingCallback(logging_type, callback_func_ptr);

        GPA_LOG(kGpaLoggingMessage, "Logging callback registered successfully.");
        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaInitialize(GpaInitializeFlags gpa_initialize_flags)
{
    try
    {
        PROFILE_FUNCTION(GpaInitialize);
        TRACE_FUNCTION(GpaInitialize);

        if (gpa_imp != nullptr)
        {
            GPA_LOG_ERROR("GPA was already initialized.");
            return kGpaStatusErrorGpaAlreadyInitialized;
        }

        gpa_imp = CreateImplementor();

        if (nullptr == gpa_imp)
        {
            GPA_LOG_ERROR("GPA initialization failed.");
            return kGpaStatusErrorFailed;
        }

        GpaStatus ret_status = gpa_imp->Initialize(gpa_initialize_flags);

        if (kGpaStatusOk != ret_status)
        {
            GpaDestroy();
        }

        GPA_INTERNAL_LOG(GpaInitialize, MAKE_PARAM_STRING(gpa_initialize_flags) << MAKE_PARAM_STRING(ret_status))

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaDestroy()
{
    try
    {
        PROFILE_FUNCTION(GpaDestroy);
        TRACE_FUNCTION(GpaDestroy);

        if (nullptr == gpa_imp)
        {
            GPA_LOG_ERROR("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        GpaStatus ret_status = gpa_imp->Destroy();
        DestroyImplementor(gpa_imp);
        gpa_imp = nullptr;
        GpaLogger::DeleteInstance();
        GPA_INTERNAL_LOG(GpaDestroy, MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaOpenContext(void* api_context, GpaOpenContextFlags gpa_open_context_flags, GpaContextId* gpa_context_id)
{
    try
    {
        PROFILE_FUNCTION(GpaOpenContext);
        TRACE_FUNCTION(GpaOpenContext);

        if (nullptr == gpa_imp)
        {
            GPA_LOG_ERROR("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (nullptr == api_context)
        {
            GPA_LOG_ERROR("Parameter 'api_context' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        if (nullptr == gpa_context_id)
        {
            GPA_LOG_ERROR("Parameter 'gpa_context_id' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        GpaStatus ret_status = gpa_imp->OpenContext(api_context, gpa_open_context_flags, gpa_context_id);

        GPA_INTERNAL_LOG(GpaOpenContext,
                         MAKE_PARAM_STRING(api_context)
                             << MAKE_PARAM_STRING(gpa_open_context_flags) << MAKE_PARAM_STRING(*gpa_context_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaCloseContext(GpaContextId gpa_context_id)
{
    try
    {
        PROFILE_FUNCTION(GpaCloseContext);
        TRACE_FUNCTION(GpaCloseContext);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }

        if ((*gpa_context_id)->GetApiType() != gpa_imp->GetApiType())
        {
            GPA_LOG_ERROR("The context's API type does not match GPA's API type.");
            return kGpaStatusErrorInvalidParameter;
        }

        GpaStatus ret_status = gpa_imp->CloseContext(gpa_context_id);
        GPA_INTERNAL_LOG(GpaCloseContext, MAKE_PARAM_STRING(gpa_context_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetSupportedSampleTypes(GpaContextId gpa_context_id, GpaContextSampleTypeFlags* sample_types)
{
    try
    {
        PROFILE_FUNCTION(GpaGetSupportedSampleTypes);
        TRACE_FUNCTION(GpaGetSupportedSampleTypes);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        CHECK_NULL_PARAM(sample_types);

        return (*gpa_context_id)->GetSupportedSampleTypes(sample_types);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceAndRevisionId(GpaContextId gpa_context_id, GpaUInt32* device_id, GpaUInt32* revision_id)
{
    try
    {
        PROFILE_FUNCTION(GpaGetDeviceAndRevisionId);
        TRACE_FUNCTION(GpaGetDeviceAndRevisionId);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        CHECK_NULL_PARAM(device_id);
        CHECK_NULL_PARAM(revision_id);

        const GpaHwInfo* hw_info = (*gpa_context_id)->GetHwInfo();

        GpaStatus ret_status = kGpaStatusErrorFailed;

        if (nullptr != hw_info && hw_info->GetDeviceId(*device_id) && hw_info->GetRevisionId(*revision_id))
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GpaGetDeviceAndRevisionId,
                         MAKE_PARAM_STRING(gpa_context_id)
                             << MAKE_PARAM_STRING(*device_id) << MAKE_PARAM_STRING(*revision_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceName(GpaContextId gpa_context_id, const char** device_name)
{
    try
    {
        PROFILE_FUNCTION(GpaGetDeviceName);
        TRACE_FUNCTION(GpaGetDeviceName);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        CHECK_NULL_PARAM(device_name);

        const GpaHwInfo* hw_info    = (*gpa_context_id)->GetHwInfo();
        GpaStatus        ret_status = kGpaStatusErrorFailed;

        if (nullptr != hw_info && hw_info->GetDeviceName(*device_name))
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GpaGetDeviceName, MAKE_PARAM_STRING(gpa_context_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaUpdateDeviceInformation(GpaContextId gpa_context_id,
                                                  GpaUInt32    num_shader_engines,
                                                  GpaUInt32    num_compute_units,
                                                  GpaUInt32    num_simds,
                                                  GpaUInt32    num_waves_per_simd)
{
    try
    {
        PROFILE_FUNCTION(GpaUpdateDeviceInformation);
        TRACE_FUNCTION(GpaUpdateDeviceInformation);

        if (num_shader_engines == 0 || num_compute_units == 0 || num_simds == 0 || num_waves_per_simd == 0)
        {
            return kGpaStatusErrorInvalidParameter;
        }

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }

        GpaStatus ret_status = kGpaStatusOk;

        (*gpa_context_id)->UpdateHwInfo(num_shader_engines, num_compute_units, num_simds, num_waves_per_simd);

        GPA_INTERNAL_LOG(GpaUpdateDeviceInformation,
                         MAKE_PARAM_STRING(gpa_context_id)
                             << MAKE_PARAM_STRING(num_shader_engines) << MAKE_PARAM_STRING(num_compute_units) << MAKE_PARAM_STRING(num_simds)
                             << MAKE_PARAM_STRING(num_waves_per_simd) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceGeneration(GpaContextId gpa_context_id, GpaHwGeneration* hardware_generation)
{
    try
    {
        PROFILE_FUNCTION(GpaGetDeviceGeneration);
        TRACE_FUNCTION(GpaGetDeviceGeneration);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        CHECK_NULL_PARAM(hardware_generation);

        const GpaHwInfo* hw_info    = (*gpa_context_id)->GetHwInfo();
        GpaStatus        ret_status = kGpaStatusErrorFailed;

        GDT_HW_GENERATION gdt_hw_generation;
        if (nullptr != hw_info && hw_info->GetHwGeneration(gdt_hw_generation))
        {
            ret_status = kGpaStatusOk;

            switch (gdt_hw_generation)
            {
            case GDT_HW_GENERATION_NONE:
                *hardware_generation = kGpaHwGenerationNone;
                break;
            case GDT_HW_GENERATION_NVIDIA:
                *hardware_generation = kGpaHwGenerationNvidia;
                break;
            case GDT_HW_GENERATION_INTEL:
                *hardware_generation = kGpaHwGenerationIntel;
                break;
            case GDT_HW_GENERATION_SOUTHERNISLAND:
                *hardware_generation = kGpaHwGenerationGfx6;
                break;
            case GDT_HW_GENERATION_SEAISLAND:
                *hardware_generation = kGpaHwGenerationGfx7;
                break;
            case GDT_HW_GENERATION_VOLCANICISLAND:
                *hardware_generation = kGpaHwGenerationGfx8;
                break;
            case GDT_HW_GENERATION_GFX9:
                *hardware_generation = kGpaHwGenerationGfx9;
                break;
            case GDT_HW_GENERATION_GFX10:
                *hardware_generation = kGpaHwGenerationGfx10;
                break;
            case GDT_HW_GENERATION_GFX103:
                *hardware_generation = kGpaHwGenerationGfx103;
                break;
            case GDT_HW_GENERATION_GFX11:
                *hardware_generation = kGpaHwGenerationGfx11;
                break;
            case GDT_HW_GENERATION_GFX12:
                *hardware_generation = kGpaHwGenerationGfx12;
                break;
            case GDT_HW_GENERATION_LAST:
                *hardware_generation = kGpaHwGenerationLast;
                break;
            default:
                // In the case that we get an invalid enum value back, signal that an internal error has occurred
                *hardware_generation = kGpaHwGenerationNone;
                ret_status           = kGpaStatusErrorFailed;
                break;
            }
        }

        GPA_INTERNAL_LOG(GpaGetDeviceGeneration, MAKE_PARAM_STRING(gpa_context_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceMaxWaveSlots(GpaContextId gpa_context_id, GpaUInt32* max_wave_slots)
{
    try
    {
        PROFILE_FUNCTION(GpaGetDeviceMaxWaveSlots);
        TRACE_FUNCTION(GpaGetDeviceMaxWaveSlots);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        CHECK_NULL_PARAM(max_wave_slots);

        GpaStatus ret_status = kGpaStatusErrorFailed;

        if (const GpaHwInfo* hw_info = (*gpa_context_id)->GetHwInfo(); nullptr != hw_info)
        {
            ret_status = kGpaStatusOk;

            const auto num_simds           = static_cast<GpaUInt32>(hw_info->GetNumberSimds());
            const auto wave_slots_per_simd = static_cast<GpaUInt32>(hw_info->GetWavesPerSimd());
            const auto max                 = num_simds * wave_slots_per_simd;

            *max_wave_slots = max;
        }

        GPA_INTERNAL_LOG(GpaGetDeviceMaxWaveSlots, MAKE_PARAM_STRING(gpa_context_id) << MAKE_PARAM_STRING(ret_status) << MAKE_PARAM_STRING(*max_wave_slots));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetNumCounters(GpaSessionId gpa_session_id, GpaUInt32* number_of_counters)
{
    try
    {
        PROFILE_FUNCTION(GpaGetNumCounters);
        TRACE_FUNCTION(GpaGetNumCounters);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(number_of_counters);

        GpaStatus ret_status = (*gpa_session_id)->GetNumCounters(number_of_counters);

        GPA_INTERNAL_LOG(GpaGetNumCounters, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(*number_of_counters) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterName(GpaSessionId gpa_session_id, GpaUInt32 counter_index, const char** counter_name)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterName);
        TRACE_FUNCTION(GpaGetCounterName);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_name);

        return (*gpa_session_id)->GetCounterName(counter_index, counter_name);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterIndex(GpaSessionId gpa_session_id, const char* counter_name, GpaUInt32* counter_index)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterIndex);
        TRACE_FUNCTION(GpaGetCounterIndex);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(counter_name);
        CHECK_NULL_PARAM(counter_index);

        bool counter_found = (kGpaStatusOk == (*gpa_session_id)->GetCounterIndex(counter_name, counter_index));

        if (!counter_found)
        {
            GPA_LOG_ERROR("Specified counter '%s' was not found. Please check spelling or availability.", counter_name);
            return kGpaStatusErrorCounterNotFound;
        }

        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterGroup(GpaSessionId gpa_session_id, GpaUInt32 counter_index, const char** counter_group)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterGroup);
        TRACE_FUNCTION(GpaGetCounterGroup);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_group);

        return (*gpa_session_id)->GetCounterGroup(counter_index, counter_group);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterDescription(GpaSessionId gpa_session_id, GpaUInt32 counter_index, const char** counter_description)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterDescription);
        TRACE_FUNCTION(GpaGetCounterDescription);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_description);

        return (*gpa_session_id)->GetCounterDescription(counter_index, counter_description);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterDataType(GpaSessionId gpa_session_id, GpaUInt32 counter_index, GpaDataType* counter_data_type)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterDataType);
        TRACE_FUNCTION(GpaGetCounterDataType);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_data_type);

        return (*gpa_session_id)->GetCounterDataType(counter_index, counter_data_type);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterUsageType(GpaSessionId gpa_session_id, GpaUInt32 counter_index, GpaUsageType* counter_usage_type)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterUsageType);
        TRACE_FUNCTION(GpaGetCounterUsageType);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_usage_type);

        return (*gpa_session_id)->GetCounterUsageType(counter_index, counter_usage_type);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterUuid(GpaSessionId gpa_session_id, GpaUInt32 counter_index, GpaUuid* counter_uuid)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterUuid);
        TRACE_FUNCTION(GpaGetCounterUuid);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_uuid);

        return (*gpa_session_id)->GetCounterUuid(counter_index, counter_uuid);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetCounterSampleType(GpaSessionId gpa_session_id, GpaUInt32 counter_index, GpaCounterSampleType* counter_sample_type)
{
    try
    {
        PROFILE_FUNCTION(GpaGetCounterSampleType);
        TRACE_FUNCTION(GpaGetCounterSampleType);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        CHECK_NULL_PARAM(counter_sample_type);

        return (*gpa_session_id)->GetCounterSampleType(counter_index, counter_sample_type);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

/// Array of strings representing GpaDataType.
static const char* kCounterDataTypeString[] = {GPA_ENUM_STRING_VAL(kGpaDataTypeFloat64, "gpa_float64"), GPA_ENUM_STRING_VAL(kGpaDataTypeUint64, "gpa_uint64")};

/// Number of entries in the data type string array.
static const size_t kCounterDataStringSize = sizeof(kCounterDataTypeString) / sizeof(const char*);

static_assert(kCounterDataStringSize == kGpaDataTypeLast, "GPA Counter Data Type string array missing entries");

GPA_LIB_DECL GpaStatus GpaGetDataTypeAsStr(GpaDataType counter_data_type, const char** type_as_str)
{
    try
    {
        PROFILE_FUNCTION(GpaGetDataTypeAsStr);
        TRACE_FUNCTION(GpaGetDataTypeAsStr);

        if (kGpaDataTypeLast <= counter_data_type)
        {
            GPA_LOG_ERROR("Unable to get string for data type: invalid data type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        CHECK_NULL_PARAM(type_as_str);

        *type_as_str = kCounterDataTypeString[counter_data_type];
        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

/// Array of strings representing GpaUsageType.
static const char* kUsageTypeString[] = {GPA_ENUM_STRING_VAL(kGpaUsageTypeRatio, "ratio"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypePercentage, "percentage"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeCycles, "cycles"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeMilliseconds, "milliseconds"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeBytes, "bytes"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeItems, "items"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeKilobytes, "kilobytes"),
                                         GPA_ENUM_STRING_VAL(kGpaUsageTypeNanoseconds, "nanoseconds")};

/// Number of entries in the usage type array.
static const size_t kUsageTypeStringSize = sizeof(kUsageTypeString) / sizeof(const char*);

static_assert(kUsageTypeStringSize == kGpaUsageTypeLast, "GPA Usage Type string array missing entries");

GPA_LIB_DECL GpaStatus GpaGetUsageTypeAsStr(GpaUsageType counter_usage_type, const char** usage_type_as_str)
{
    try
    {
        PROFILE_FUNCTION(GpaGetUsageTypeAsStr);
        TRACE_FUNCTION(GpaGetUsageTypeAsStr);

        if (kGpaUsageTypeLast <= counter_usage_type)
        {
            GPA_LOG_ERROR("Unable to get string for usage type: invalid usage type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        CHECK_NULL_PARAM(usage_type_as_str);

        *usage_type_as_str = kUsageTypeString[counter_usage_type];
        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaCreateSession(GpaContextId gpa_context_id, GpaSessionSampleType gpa_session_sample_type, GpaSessionId* gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaCreateSession);
        TRACE_FUNCTION(GpaCreateSession);

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }

        if (gpa_session_sample_type >= kGpaSessionSampleTypeLast)
        {
            GPA_LOG_ERROR("Invalid sample type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        CHECK_NULL_PARAM(gpa_session_id);

        GpaContextSampleTypeFlags context_sample_types;

        GpaStatus local_status = (*gpa_context_id)->GetSupportedSampleTypes(&context_sample_types);

        if (kGpaStatusOk != local_status)
        {
            GPA_LOG_ERROR("Unable to get supported sample types from context.");
            return local_status;
        }

        // Next check that the set of sample types specified is compatible with context's set of supported sample types.
        {
            static_assert(GpaSessionSampleType::kGpaSessionSampleTypeLast == 4);

            // Returns false if the sample_type is incompatible with context's sample_types.
            auto invalid_sample_type = [&gpa_session_sample_type, &context_sample_types](GpaSessionSampleType      sample_type,
                                                                                         GpaContextSampleTypeFlags sample_type_flags) -> bool {
                return (sample_type == gpa_session_sample_type) && (sample_type_flags != (sample_type_flags & context_sample_types));
            };
            const bool invalid_discrete = invalid_sample_type(kGpaSessionSampleTypeDiscreteCounter, kGpaContextSampleTypeDiscreteCounter);
            const bool invalid_spm      = invalid_sample_type(kGpaSessionSampleTypeStreamingCounter, kGpaContextSampleTypeStreamingCounter);
            const bool invalid_sqtt     = invalid_sample_type(kGpaSessionSampleTypeSqtt, kGpaContextSampleTypeSqtt);
            const auto invalid_spm_and_sqtt =
                invalid_sample_type(kGpaSessionSampleTypeStreamingCounterAndSqtt, kGpaContextSampleTypeStreamingCounter | kGpaContextSampleTypeSqtt);

            if (invalid_discrete || invalid_spm || invalid_sqtt || invalid_spm_and_sqtt)
            {
                GPA_LOG_ERROR("Unable to create session: sample_type is incompatible with context's sample_types.");
                return kGpaStatusErrorIncompatibleSampleTypes;
            }
        }

        *gpa_session_id      = (*gpa_context_id)->CreateSession(gpa_session_sample_type);
        GpaStatus ret_status = (nullptr != (*gpa_session_id)) ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GpaCreateSession,
                         MAKE_PARAM_STRING(gpa_context_id)
                             << MAKE_PARAM_STRING(gpa_session_sample_type) << MAKE_PARAM_STRING(*gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaDeleteSession(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaDeleteSession);
        TRACE_FUNCTION(GpaDeleteSession);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaContext* gpa_context = (*gpa_session_id)->GetParentContext();
        GpaStatus    ret_status  = gpa_context->DeleteSession(gpa_session_id) ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GpaDeleteSession, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaBeginSession(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaBeginSession);
        TRACE_FUNCTION(GpaBeginSession);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();
        CHECK_CONTEXT_IS_OPEN(gpa_context);

        GpaStatus ret_status = gpa_context->BeginSession(gpa_session);

        GPA_INTERNAL_LOG(GpaBeginSession, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaResetSession(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaResetSession);
        TRACE_FUNCTION(GpaResetSession);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        IGpaSession* gpa_session = gpa_session_id->Object();
        GpaStatus    ret_status  = gpa_session->Reset();

        GPA_INTERNAL_LOG(GpaResetSession, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEndSession(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaEndSession);
        TRACE_FUNCTION(GpaEndSession);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();

        GpaStatus ret_status = gpa_context->EndSession(gpa_session, false);

        GPA_INTERNAL_LOG(GpaEndSession, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaAbortSession(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaAbortSession);
        TRACE_FUNCTION(GpaAbortSession);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();

        GpaStatus ret_status = gpa_context->EndSession(gpa_session, true);

        GPA_INTERNAL_LOG(GpaAbortSession, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttGetInstructionMask(GpaSessionId gpa_session_id, GpaSqttInstructionFlags* gpa_sqtt_instruction_mask)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttGetInstructionMask);
        TRACE_FUNCTION(GpaSqttGetInstructionMask);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(gpa_sqtt_instruction_mask);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = kGpaStatusOk;

        *gpa_sqtt_instruction_mask = (*gpa_session_id)->GetSqttInstructionMask();

        GPA_INTERNAL_LOG(GpaSqttGetInstructionMask, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttSetInstructionMask(GpaSessionId gpa_session_id, GpaSqttInstructionFlags sqtt_instruction_mask)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttSetInstructionMask);
        TRACE_FUNCTION(GpaSqttSetInstructionMask);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = kGpaStatusOk;

        (*gpa_session_id)->SetSqttInstructionMask(sqtt_instruction_mask);

        GPA_INTERNAL_LOG(GpaSqttSetInstructionMask, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttGetComputeUnitId(GpaSessionId gpa_session_id, GpaUInt32* sqt_compute_unit_id)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttGetComputeUnitId);
        TRACE_FUNCTION(GpaSqttGetComputeUnitId);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(sqt_compute_unit_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        *sqt_compute_unit_id = (*gpa_session_id)->GetSqttComputeUnitId();

        GpaStatus ret_status = kGpaStatusOk;

        GPA_INTERNAL_LOG(GpaSqttGetComputeUnitId, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttSetComputeUnitId(GpaSessionId gpa_session_id, GpaUInt32 sqtt_compute_unit_id)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttSetComputeUnitId);
        TRACE_FUNCTION(GpaSqttSetComputeUnitId);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        (*gpa_session_id)->SetSqttComputeUnitId(sqtt_compute_unit_id);

        GpaStatus ret_status = kGpaStatusOk;

        GPA_INTERNAL_LOG(GpaSqttSetComputeUnitId, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttBegin(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttBegin);
        TRACE_FUNCTION(GpaSqttBegin);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeSqtt);

        auto ret_status = (*gpa_session_id)->SqttBegin(command_list);

        GPA_INTERNAL_LOG(GpaSqttBegin, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttEnd(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttEnd);
        TRACE_FUNCTION(GPA_SqttGpaSqttEndEnd);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeSqtt);

        auto ret_status = (*gpa_session_id)->SqttEnd(command_list);

        GPA_INTERNAL_LOG(GpaSqttEnd, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttGetSampleResultSize(GpaSessionId gpa_session_id, size_t* sample_result_size_in_bytes)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttGetSampleResultSize);
        TRACE_FUNCTION(GpaSqttGetSampleResultSize);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SqttGetSampleResultSize(sample_result_size_in_bytes);

        GPA_INTERNAL_LOG(GpaSqttGetSampleResultSize, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttGetSampleResult(GpaSessionId gpa_session_id, size_t sample_result_size_in_bytes, void* sqtt_results)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttGetSampleResult);
        TRACE_FUNCTION(GpaSqttGetSampleResult);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SqttGetSampleResult(sample_result_size_in_bytes, sqtt_results);

        GPA_INTERNAL_LOG(GpaSqttGetSampleResult, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttSpmBegin(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttSpmBegin);
        TRACE_FUNCTION(GpaSqttSpmBegin);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounterAndSqtt);

        const GpaStatus ret_status = (*gpa_session_id)->SqttSpmBegin(command_list);

        GPA_INTERNAL_LOG(GpaSqttSpmBegin, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSqttSpmEnd(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSqttSpmEnd);
        TRACE_FUNCTION(GpaSqttSpmEnd);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounterAndSqtt);

        const GpaStatus ret_status = (*gpa_session_id)->SqttSpmEnd(command_list);

        GPA_INTERNAL_LOG(GpaSqttSpmEnd, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmSetSampleInterval(GpaSessionId gpa_session_id, GpaUInt32 interval)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmSetSampleInterval);
        TRACE_FUNCTION(GpaSpmSetSampleInterval);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmSetSampleInterval(interval);

        GPA_INTERNAL_LOG(GpaSpmSetSampleInterval, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmSetDuration(GpaSessionId gpa_session_id, GpaUInt32 ns_duration)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmSetDuration);
        TRACE_FUNCTION(GpaSpmSetDuration);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmSetDuration(ns_duration);

        GPA_INTERNAL_LOG(GpaSpmSetDuration, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmBegin(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmBegin);
        TRACE_FUNCTION(GpaSpmBegin);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounter);

        auto ret_status = (*gpa_session_id)->SpmBegin(command_list);

        GPA_INTERNAL_LOG(GpaSpmBegin, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmEnd(GpaSessionId gpa_session_id, void* command_list)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmEnd);
        TRACE_FUNCTION(GpaSpmEnd);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounter);

        auto ret_status = (*gpa_session_id)->SpmEnd(command_list);

        GPA_INTERNAL_LOG(GpaSpmEnd, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmGetSampleResultSize(GpaSessionId gpa_session_id, size_t* sample_result_size_in_bytes)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmGetSampleResultSize);
        TRACE_FUNCTION(GpaSpmGetSampleResultSize);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmGetSampleResultSize(sample_result_size_in_bytes);

        GPA_INTERNAL_LOG(GpaSpmGetSampleResultSize, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmGetSampleResult(GpaSessionId gpa_session_id, size_t sample_result_size_in_bytes, void* spm_results)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmGetSampleResult);
        TRACE_FUNCTION(GpaSpmGetSampleResult);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmGetSampleResult(sample_result_size_in_bytes, spm_results);

        GPA_INTERNAL_LOG(GpaSpmGetSampleResult, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaSpmCalculateDerivedCounters(GpaSessionId gpa_session_id,
                                                      GpaSpmData*  spm_data,
                                                      GpaUInt32    derived_counter_count,
                                                      GpaUInt64*   derived_counter_results)
{
    try
    {
        PROFILE_FUNCTION(GpaSpmCalculateDerivedCounters);
        TRACE_FUNCTION(GpaSpmCalculateDerivedCounters);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = (*gpa_session_id)->SpmCalculateDerivedCounters(spm_data, derived_counter_count, derived_counter_results);

        GPA_INTERNAL_LOG(GpaSpmCalculateDerivedCounters, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEnableCounter(GpaSessionId gpa_session_id, GpaUInt32 counter_index)
{
    try
    {
        PROFILE_FUNCTION(GpaEnableCounter);
        TRACE_FUNCTION(GpaEnableCounter);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));

        GpaStatus ret_status = (*gpa_session_id)->EnableCounter(counter_index);

        GPA_INTERNAL_LOG(GpaEnableCounter, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(counter_index) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaDisableCounter(GpaSessionId gpa_session_id, GpaUInt32 counter_index)
{
    try
    {
        PROFILE_FUNCTION(GpaDisableCounter);
        TRACE_FUNCTION(GpaDisableCounter);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));

        GpaStatus ret_status = (*gpa_session_id)->DisableCounter(counter_index);

        GPA_INTERNAL_LOG(GpaDisableCounter, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(counter_index) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEnableCounterByName(GpaSessionId gpa_session_id, const char* counter_name)
{
    try
    {
        PROFILE_FUNCTION(GpaEnableCounterByName);
        TRACE_FUNCTION(GpaEnableCounterByName);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaUInt32 index;
        GpaStatus status = (*gpa_session_id)->GetCounterIndex(counter_name, &index);

        if (kGpaStatusOk != status)
        {
            GPA_LOG_ERROR("Specified counter '%s' was not found. Please check spelling or availability.", counter_name);
            return kGpaStatusErrorCounterNotFound;
        }

        return GpaEnableCounter(gpa_session_id, index);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaDisableCounterByName(GpaSessionId gpa_session_id, const char* counter_name)
{
    try
    {
        PROFILE_FUNCTION(GpaDisableCounterByName);
        TRACE_FUNCTION(GpaDisableCounterByName);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaUInt32 index;
        GpaStatus status = (*gpa_session_id)->GetCounterIndex(counter_name, &index);

        if (kGpaStatusOk != status)
        {
            GPA_LOG_ERROR("Specified counter '%s' was not found. Please check spelling or availability.", counter_name);
            return kGpaStatusErrorCounterNotFound;
        }

        return GpaDisableCounter(gpa_session_id, index);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEnableAllCounters(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaEnableAllCounters);
        TRACE_FUNCTION(GpaEnableAllCounters);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaStatus ret_status = (*gpa_session_id)->DisableAllCounters();

        if (kGpaStatusOk == ret_status)
        {
            GpaUInt32 count;
            ret_status = (*gpa_session_id)->GetNumCounters(&count);

            if (kGpaStatusOk == ret_status)
            {
                for (GpaUInt32 counter_iter = 0; counter_iter < count; counter_iter++)
                {
                    ret_status = (*gpa_session_id)->EnableCounter(counter_iter);

                    if (kGpaStatusOk != ret_status)
                    {
                        break;
                    }
                }
            }
        }

        GPA_INTERNAL_LOG(GpaEnableAllCounters, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaDisableAllCounters(GpaSessionId gpa_session_id)
{
    try
    {
        PROFILE_FUNCTION(GpaDisableAllCounters);
        TRACE_FUNCTION(GpaDisableAllCounters);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaStatus ret_status = (*gpa_session_id)->DisableAllCounters();

        GPA_INTERNAL_LOG(GpaDisableAllCounters, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetPassCount(GpaSessionId gpa_session_id, GpaUInt32* number_of_passes)
{
    try
    {
        PROFILE_FUNCTION(GpaGetPassCount);
        TRACE_FUNCTION(GpaGetPassCount);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(number_of_passes);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        GpaStatus ret_status = (*gpa_session_id)->GetNumRequiredPasses(number_of_passes);

        GPA_INTERNAL_LOG(GpaGetPassCount, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(*number_of_passes) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetNumEnabledCounters(GpaSessionId gpa_session_id, GpaUInt32* enabled_counter_count)
{
    try
    {
        PROFILE_FUNCTION(GpaGetNumEnabledCounters);
        TRACE_FUNCTION(GpaGetNumEnabledCounters);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(enabled_counter_count);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        GpaStatus ret_status = (*gpa_session_id)->GetNumEnabledCounters(enabled_counter_count);

        GPA_INTERNAL_LOG(GpaGetNumEnabledCounters,
                         MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(*enabled_counter_count) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetEnabledIndex(GpaSessionId gpa_session_id, GpaUInt32 enabled_number, GpaUInt32* enabled_counter_index)
{
    try
    {
        PROFILE_FUNCTION(GpaGetEnabledIndex);
        TRACE_FUNCTION(GpaGetEnabledIndex);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(enabled_counter_index);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        return (*gpa_session_id)->GetEnabledIndex(enabled_number, enabled_counter_index);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaIsCounterEnabled(GpaSessionId gpa_session_id, GpaUInt32 counter_index)
{
    try
    {
        PROFILE_FUNCTION(GpaIsCounterEnabled);
        TRACE_FUNCTION(GpaIsCounterEnabled);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        return (*gpa_session_id)->IsCounterEnabled(counter_index);
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaBeginCommandList(GpaSessionId       gpa_session_id,
                                           GpaUInt32          pass_index,
                                           void*              command_list,
                                           GpaCommandListType command_list_type,
                                           GpaCommandListId*  gpa_command_list_id)
{
    try
    {
        PROFILE_FUNCTION(GpaBeginCommandList);
        TRACE_FUNCTION(GpaBeginCommandList);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GPA_LOG_ERROR("Session has not been started.");
            return kGpaStatusErrorSessionNotStarted;
        }

        if (kGpaCommandListLast <= command_list_type)
        {
            GPA_LOG_ERROR("Invalid value for 'command_list_type' parameter.");
            return kGpaStatusErrorInvalidParameter;
        }

        bool command_list_required = gpa_imp->IsCommandListRequired();

        if (command_list_required)
        {
            if (!command_list)
            {
                GPA_LOG_ERROR("Command list cannot be NULL.");
                return kGpaStatusErrorNullPointer;
            }

            if (kGpaCommandListNone == command_list_type)
            {
                GPA_LOG_ERROR("NULL command list is not supported.");
                return kGpaStatusErrorInvalidParameter;
            }
        }
        else
        {
            if (command_list || (kGpaCommandListNone != command_list_type))
            {
                GPA_LOG_ERROR("'command_list' must be NULL and 'command_list_type' must be kGpaCommandListNone.");
                return kGpaStatusErrorInvalidParameter;
            }
        }

        CHECK_NULL_PARAM(gpa_command_list_id);

        if (gpa_imp->DoesCommandListExist(*gpa_command_list_id))
        {
            GPA_LOG_ERROR("Command List already created.");
            return kGpaStatusErrorCommandListAlreadyStarted;
        }

        *gpa_command_list_id = (*gpa_session_id)->CreateCommandList(pass_index, command_list, command_list_type);

        bool status = false;

        if (nullptr != *gpa_command_list_id)
        {
            status = (*(*gpa_command_list_id))->Begin();

            if (status)
            {
                (*gpa_session_id)->GetParentContext()->SetInvalidateAndFlushL2Cache(true);
            }
            else
            {
                GPA_LOG_ERROR("Unable to begin the command list.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to create the command list.");
        }

        GpaStatus ret_status = status ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GpaBeginCommandList,
                         MAKE_PARAM_STRING(gpa_session_id)
                             << MAKE_PARAM_STRING(pass_index) << MAKE_PARAM_STRING(command_list) << MAKE_PARAM_STRING(command_list_type)
                             << MAKE_PARAM_STRING(*gpa_command_list_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEndCommandList(GpaCommandListId gpa_command_list_id)
{
    try
    {
        PROFILE_FUNCTION(GpaEndCommandList);
        TRACE_FUNCTION(GpaEndCommandList);

        CHECK_COMMAND_LIST_ID_EXISTS(gpa_command_list_id);

        if (!(*gpa_command_list_id)->IsCommandListRunning())
        {
            GPA_LOG_ERROR("Command list has already been ended.");
            return kGpaStatusErrorCommandListAlreadyEnded;
        }

        GpaStatus ret_status = (*gpa_command_list_id)->End() ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GpaEndCommandList, MAKE_PARAM_STRING(gpa_command_list_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaBeginSample(GpaUInt32 sample_id, GpaCommandListId gpa_command_list_id)
{
    try
    {
        PROFILE_FUNCTION(GpaBeginSample);
        TRACE_FUNCTION(GpaBeginSample);

        CHECK_COMMAND_LIST_ID_EXISTS(gpa_command_list_id);

        GpaStatus ret_status = kGpaStatusOk;

        // Only begin the sample if the current pass index is valid.
        GpaUInt32 num_required_passes = 0;
        ret_status                    = (*gpa_command_list_id)->GetParentSession()->GetNumRequiredPasses(&num_required_passes);

        if (kGpaStatusOk == ret_status)
        {
            if ((*gpa_command_list_id)->GetPass()->GetIndex() < num_required_passes)
            {
                ret_status = ((*gpa_command_list_id)->GetParentSession()->BeginSample(sample_id, gpa_command_list_id)) ? kGpaStatusOk : kGpaStatusErrorFailed;
            }
            else
            {
                GPA_LOG_ERROR("Invalid pass index.");
                ret_status = kGpaStatusErrorIndexOutOfRange;
            }
        }

        GPA_INTERNAL_LOG(GpaBeginSample, MAKE_PARAM_STRING(sample_id) << MAKE_PARAM_STRING(gpa_command_list_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaEndSample(GpaCommandListId gpa_command_list_id)
{
    try
    {
        PROFILE_FUNCTION(GpaEndSample);
        TRACE_FUNCTION(GpaEndSample);

        CHECK_COMMAND_LIST_ID_EXISTS(gpa_command_list_id);

        GpaStatus ret_status = kGpaStatusOk;

        // Only end the sample if the current pass index is valid.
        GpaUInt32 num_required_passes = 0;
        ret_status                    = (*gpa_command_list_id)->GetParentSession()->GetNumRequiredPasses(&num_required_passes);

        if (kGpaStatusOk == ret_status)
        {
            if ((*gpa_command_list_id)->GetPass()->GetIndex() < num_required_passes)
            {
                ret_status = ((*gpa_command_list_id)->GetParentSession()->EndSample(gpa_command_list_id)) ? kGpaStatusOk : kGpaStatusErrorFailed;
            }
            else
            {
                GPA_LOG_ERROR("Invalid pass index.");
                ret_status = kGpaStatusErrorIndexOutOfRange;
            }
        }

        GPA_INTERNAL_LOG(GpaEndSample, MAKE_PARAM_STRING(gpa_command_list_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaContinueSampleOnCommandList(GpaUInt32 source_sample_id, GpaCommandListId primary_gpa_command_list_id)
{
    try
    {
        PROFILE_FUNCTION(GpaContinueSampleOnCommandList);
        TRACE_FUNCTION(GpaContinueSampleOnCommandList);

        if (nullptr == gpa_imp)
        {
            GPA_LOG_ERROR("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (!gpa_imp->IsContinueSampleOnCommandListSupported())
        {
            GPA_LOG_ERROR("This feature is not supported.");
            return kGpaStatusErrorApiNotSupported;
        }

        GpaStatus ret_status = kGpaStatusOk;
        CHECK_COMMAND_LIST_ID_EXISTS(primary_gpa_command_list_id);

        if ((ret_status = CheckSampleIdExistsInPass((*primary_gpa_command_list_id)->GetPass(), source_sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        ret_status = ((*primary_gpa_command_list_id)->GetParentSession()->ContinueSampleOnCommandList(source_sample_id, primary_gpa_command_list_id));

        GPA_INTERNAL_LOG(GpaContinueSampleOnCommandList,
                         MAKE_PARAM_STRING(source_sample_id) << MAKE_PARAM_STRING(primary_gpa_command_list_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaCopySecondarySamples(GpaCommandListId secondary_gpa_command_list_id,
                                               GpaCommandListId primary_gpa_command_list_id,
                                               GpaUInt32        number_of_samples,
                                               GpaUInt32*       new_sample_ids)
{
    try
    {
        PROFILE_FUNCTION(GpaCopySecondarySamples);
        TRACE_FUNCTION(GpaCopySecondarySamples);

        if (nullptr == gpa_imp)
        {
            GPA_LOG_ERROR("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (!gpa_imp->IsCopySecondarySampleSupported())
        {
            GPA_LOG_ERROR("This feature is not supported.");
            return kGpaStatusErrorApiNotSupported;
        }

        CHECK_COMMAND_LIST_ID_EXISTS(secondary_gpa_command_list_id);
        CHECK_COMMAND_LIST_ID_EXISTS(primary_gpa_command_list_id);

        GpaStatus ret_status = ((*primary_gpa_command_list_id)
                                    ->GetParentSession()
                                    ->CopySecondarySamples(secondary_gpa_command_list_id, primary_gpa_command_list_id, number_of_samples, new_sample_ids));

        GPA_INTERNAL_LOG(GpaCopySecondarySamples,
                         MAKE_PARAM_STRING(secondary_gpa_command_list_id)
                             << MAKE_PARAM_STRING(primary_gpa_command_list_id) << MAKE_PARAM_STRING(number_of_samples) << MAKE_PARAM_STRING(*new_sample_ids)
                             << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetSampleCount(GpaSessionId gpa_session_id, GpaUInt32* sample_count)
{
    try
    {
        PROFILE_FUNCTION(GpaGetSampleCount);
        TRACE_FUNCTION(GpaGetSampleCount);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING(gpa_session_id);
        CHECK_NULL_PARAM(sample_count);

        *sample_count = (*gpa_session_id)->GetSampleCount();

        GPA_INTERNAL_LOG(GpaGetSampleCount, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(*sample_count));

        return kGpaStatusOk;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetSampleId(GpaSessionId gpa_session_id, GpaUInt32 index, GpaUInt32* sample_id)
{
    try
    {
        PROFILE_FUNCTION(GpaGetSampleId);
        TRACE_FUNCTION(GpaGetSampleId);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING(gpa_session_id);
        CHECK_NULL_PARAM(sample_id);

        GpaStatus ret_status    = kGpaStatusErrorSampleNotFound;
        GpaUInt32 ret_sample_id = 0u;
        bool      found         = (*gpa_session_id)->GetSampleIdByIndex(index, ret_sample_id);

        if (found)
        {
            *sample_id = ret_sample_id;
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GpaGetSampleId,
                         MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(index) << MAKE_PARAM_STRING(*sample_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaIsSessionComplete(GpaSessionId gpa_session_id)
{
    try
    {
        GpaStatus ret_status = kGpaStatusResultNotReady;

        PROFILE_FUNCTION(GpaIsSessionComplete);
        TRACE_FUNCTION(GpaIsSessionComplete);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GPA_LOG_ERROR("Session has not been started.");
            return kGpaStatusErrorSessionNotStarted;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        (*gpa_session_id)->UpdateResults();

        if ((*gpa_session_id)->IsResultReady())
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GpaIsSessionComplete, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaIsPassComplete(GpaSessionId gpa_session_id, GpaUInt32 pass_index)
{
    try
    {
        PROFILE_FUNCTION(GpaIsPassComplete);
        TRACE_FUNCTION(GpaIsPassComplete);

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        GpaStatus ret_status = kGpaStatusResultNotReady;

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GPA_LOG_ERROR("Session has not been started.");
            return kGpaStatusErrorSessionNotStarted;
        }

        ret_status = (*gpa_session_id)->IsPassComplete(pass_index);

        if (kGpaStatusOk == ret_status)
        {
            if ((*gpa_session_id)->UpdateResults(pass_index))
            {
                ret_status = kGpaStatusOk;
            }
            else
            {
                ret_status = kGpaStatusResultNotReady;
            }
        }

        GPA_INTERNAL_LOG(GpaIsSessionComplete, MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(pass_index) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetSampleResultSize(GpaSessionId gpa_session_id, GpaUInt32 sample_id, size_t* sample_result_size_in_bytes)
{
    try
    {
        PROFILE_FUNCTION(GpaGetSampleResultSize);
        TRACE_FUNCTION(GpaGetSampleResultSize);

        GpaStatus ret_status = kGpaStatusOk;

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(sample_result_size_in_bytes);

        if ((ret_status = CheckSampleIdExistsInSession(gpa_session_id, sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        *sample_result_size_in_bytes = (*gpa_session_id)->GetSampleResultSizeInBytes(sample_id);

        GPA_INTERNAL_LOG(GPA_GetSampleResultSize,
                         MAKE_PARAM_STRING(gpa_session_id)
                             << MAKE_PARAM_STRING(sample_id) << MAKE_PARAM_STRING(*sample_result_size_in_bytes) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetSampleResult(GpaSessionId gpa_session_id, GpaUInt32 sample_id, size_t sample_result_size_in_bytes, void* counter_sample_results)
{
    try
    {
        PROFILE_FUNCTION(GpaGetSampleResult);
        TRACE_FUNCTION(GpaGetSampleResult);

        GpaStatus ret_status = kGpaStatusOk;

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_NULL_PARAM(counter_sample_results);

        if ((ret_status = CheckSampleIdExistsInSession(gpa_session_id, sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        ret_status = (*gpa_session_id)->GetSampleResult(sample_id, sample_result_size_in_bytes, counter_sample_results);

        GPA_INTERNAL_LOG(GpaGetSampleResult,
                         MAKE_PARAM_STRING(gpa_session_id) << MAKE_PARAM_STRING(sample_id) << MAKE_PARAM_STRING(sample_result_size_in_bytes)
                                                           << MAKE_PARAM_STRING(counter_sample_results) << MAKE_PARAM_STRING(ret_status));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

/// Array of strings representing GpaStatus status strings.
static const char* kStatusString[] = {GPA_ENUM_STRING_VAL(kGpaStatusOk, "GPA Status: Ok."),
                                      GPA_ENUM_STRING_VAL(kGpaStatusResultNotReady, "GPA Status: Counter Results Not Ready.")};

/// Size of kStatusString array.
static size_t kStatusStringSize = sizeof(kStatusString) / sizeof(const char*);

/// Array of strings representing GpaStatus error strings.
static const char* kErrorString[] = {
    GPA_ENUM_STRING_VAL(kGpaStatusErrorNullPointer, "GPA Error: Null Pointer."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorContextNotOpen, "GPA Error: Context Not Open."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorContextAlreadyOpen, "GPA Error: Coontext Already Opened."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorIndexOutOfRange, "GPA Error: Index Out Of Range."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCounterNotFound, "GPA Error: Counter Not Found."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorAlreadyEnabled, "GPA Error: Already Enabled."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorNoCountersEnabled, "GPA Error: No Counters Enabled."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorNotEnabled, "GPA Error: Not Enabled."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCommandListAlreadyEnded, "GPA Error: Command List Already Ended."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCommandListAlreadyStarted, "GPA Error: Command List Already Started."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCommandListNotEnded, "GPA Error: Command List Is Not Ended."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorNotEnoughPasses, "GPA Error: Not Enough Passes."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSampleNotStarted, "GPA Error: Sample Not Started."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSampleAlreadyStarted, "GPA Error: Sample Already Started."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSampleNotEnded, "GPA Error: Sample Not Ended."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCannotChangeCountersWhenSampling, "GPA Error: Cannot Change Counters When Sampling."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSessionNotFound, "GPA Error: Session Not Found."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSampleNotFound, "GPA Error: Sample Not Found."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorContextNotFound, "GPA Error: Context Not Found."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorCommandListNotFound, "GPA Error: Command List Not Found."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorReadingSampleResult, "GPA Error: Reading Sample Result."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorVariableNumberOfSamplesInPasses, "GPA Error: Variable Number Of Samples In Passes."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorFailed, "GPA Error: Failed."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorHardwareNotSupported, "GPA Error: Hardware Not Supported."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorDriverNotSupported, "GPA Error: Driver Not Supported."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorApiNotSupported, "GPA Error: API Not Supported."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorInvalidParameter, "GPA Error: Incorrect Parameter."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorLibLoadFailed, "GPA Error: Loading The Library Failed."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorLibLoadMajorVersionMismatch, "GPA Error: Major Version Mismatch Between The Loader And The GPUPerfAPI Library."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorLibLoadMinorVersionMismatch, "GPA Error: Minor Version Mismatch Between The Loader And The GPUPerfAPI Library."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorGpaNotInitialized, "GPA Error: GPA Has Not Been Initialized."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorGpaAlreadyInitialized, "GPA Error: GPA Has Already Been Initialized."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSampleInSecondaryCommandList, "GPA Error: Sample In Secondary Command List."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorIncompatibleSampleTypes, "GPA Error: Incompatible Sample Types."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSessionAlreadyStarted, "GPA Error: Session Already Started."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSessionNotStarted, "GPA Error: Session Not Started."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorSessionNotEnded, "GPA Error: Session Not Ended."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorInvalidDataType, "GPA Error: Invalid Counter Datatype."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorInvalidCounterEquation, "GPA Error: Invalid Counter Equation."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorTimeout, "GPA Error: Attempt to Retrieve Data Failed due to Timeout."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorLibAlreadyLoaded, "GPA Error: Library Is Already Loaded."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorOtherSessionActive, "GPA Error: Other Session Is Active."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorException, "GPA Error: Exception Occurred."),
    GPA_ENUM_STRING_VAL(kGpaStatusErrorInvalidCounterGroupData, "GPA Error: Counter Group Data Is Invalid.")};

/// Size of kErrorString array.
static size_t kErrorStringSize = sizeof(kErrorString) / sizeof(const char*);

GPA_LIB_DECL const char* GpaGetStatusAsStr(GpaStatus gpa_status_as_str)
{
    try
    {
        PROFILE_FUNCTION(GpaGetStatusAsStr);
        TRACE_FUNCTION(GpaGetStatusAsStr);

        if (gpa_status_as_str >= 0)
        {
            size_t status_index = gpa_status_as_str;

            if (status_index < kStatusStringSize)
            {
                return kStatusString[status_index];
            }

            return "GPA Status: Unknown Status.";
        }

        size_t status_index = (-gpa_status_as_str) - 1;

        if (status_index < kErrorStringSize)
        {
            return kErrorString[status_index];
        }

        return "GPA Error: Unknown Error.";
    }
    catch (...)
    {
        return "GPA Error: Unknown Exception.";
    }
}
