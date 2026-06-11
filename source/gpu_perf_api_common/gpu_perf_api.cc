//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief This file contains the main entry points into GPA.
//==============================================================================

/// Macro to mark a function for exporting.
#ifdef _WIN32
#define GPA_LIB_DECL extern "C" __declspec(dllexport)

// Using the static version of the runtime libraries simplifies installation and can help with performance.
#ifndef _MT
#error "Use the multithread, static version of the runtime library!"
#endif

#ifndef _CONTROL_FLOW_GUARD
#error "Control flow guard is not enabled!"
#endif

#else
#define GPA_LIB_DECL extern "C" __attribute__((visibility("default")))
#endif

#include "gpu_performance_api/gpu_perf_api.h"

#include <algorithm>
#include <mutex>
#include <span>
#include <sstream>

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_implementor_interface.h"
#include "gpu_perf_api_common/gpa_profiler.h"
#include "gpu_perf_api_common/gpa_session_interface.h"
#include "gpu_perf_api_common/gpa_unique_object.h"
#include "gpu_perf_api_common/gpa_version.h"
#include "gpu_perf_api_common/gpa_hw_support.h"
#include "gpu_perf_api_common/logging.h"

namespace
{
    IGpaImplementor* gpa_imp = nullptr;  ///< GPA implementor instance.
}  // namespace

extern IGpaImplementor& CreateImplementor();   ///< Function to create the GPA implementor instance.
extern void             DestroyImplementor();  ///< Function to destroy the GPA implementor instance.

/// Macro to check for out of range counter index.
#define CHECK_COUNTER_INDEX_OUT_OF_RANGE(index, gpa_context_id)                                                      \
    GpaUInt32 num_counters;                                                                                          \
    GpaStatus num_counter_status = gpa_context_id->GetNumCounters(&num_counters);                                    \
    if (kGpaStatusOk != num_counter_status)                                                                          \
    {                                                                                                                \
        return num_counter_status;                                                                                   \
    }                                                                                                                \
    if (index >= num_counters)                                                                                       \
    {                                                                                                                \
        GpaLogger::Instance().LogError("Parameter {} is {} but must be less than {}.", #index, index, num_counters); \
        return kGpaStatusErrorIndexOutOfRange;                                                                       \
    }

/// Macro to check if a context is open.
#define CHECK_CONTEXT_IS_OPEN(context)                                      \
    if (!context->IsOpen())                                                 \
    {                                                                       \
        GpaLogger::Instance().LogError("Context has not been not opened."); \
        return kGpaStatusErrorContextNotOpen;                               \
    }

/// Macro to check if a session exists.
#define CHECK_SESSION_ID_EXISTS(session_id)                              \
    if (nullptr == gpa_imp)                                              \
    {                                                                    \
        GpaLogger::Instance().LogError("GPA has not been initialized."); \
        return kGpaStatusErrorGpaNotInitialized;                         \
    }                                                                    \
    if (!session_id)                                                     \
    {                                                                    \
        GpaLogger::Instance().LogError("Session object is null.");       \
        return kGpaStatusErrorNullPointer;                               \
    }                                                                    \
    if (!gpa_imp->DoesSessionExist(session_id))                          \
    {                                                                    \
        GpaLogger::Instance().LogError("Unknown session object.");       \
        return kGpaStatusErrorSessionNotFound;                           \
    }

/// Macro to check if a command list exists.
#define CHECK_COMMAND_LIST_ID_EXISTS(command_list_id)                    \
    if (nullptr == gpa_imp)                                              \
    {                                                                    \
        GpaLogger::Instance().LogError("GPA has not been initialized."); \
        return kGpaStatusErrorGpaNotInitialized;                         \
    }                                                                    \
    if (!command_list_id)                                                \
    {                                                                    \
        GpaLogger::Instance().LogError("Command list object is null.");  \
        return kGpaStatusErrorNullPointer;                               \
    }                                                                    \
    if (!gpa_imp->DoesCommandListExist(command_list_id))                 \
    {                                                                    \
        GpaLogger::Instance().LogError("Unknown command list object.");  \
        return kGpaStatusErrorCommandListNotFound;                       \
    }

/// Macro to check if a session is still running.
#define CHECK_SESSION_RUNNING(session_id)                                                                                \
    if ((*session_id)->IsSessionRunning())                                                                               \
    {                                                                                                                    \
        GpaLogger::Instance().LogError("Session is still running. End the session before querying sample information."); \
        return kGpaStatusErrorSessionNotEnded;                                                                           \
    }

/// Macro to check if a session is running while enabling/disabling counters.
#define CHECK_SESSION_RUNNING_FOR_COUNTERS(session_id)                                           \
    if ((*session_id)->IsSessionRunning())                                                       \
    {                                                                                            \
        GpaLogger::Instance().LogError("Counter state cannot change while session is running."); \
        return kGpaStatusErrorCannotChangeCountersWhenSampling;                                  \
    }

#define GPA_PARAM_STRING(X) #X << " : " << X << " "

/// Macro to check if a context exists and is open.
[[nodiscard]] GpaStatus CheckGPAContentIdExistsAndIsOpen(GpaContextId gpa_context_id)
{
    if (!gpa_imp)
    {
        GpaLogger::Instance().LogError("GPA has not been initialized.");
        return kGpaStatusErrorGpaNotInitialized;
    }
    if (!gpa_context_id)
    {
        GpaLogger::Instance().LogError("Context object is null.");
        return kGpaStatusErrorNullPointer;
    }
    if (!gpa_imp->DoesContextExist(gpa_context_id))
    {
        GpaLogger::Instance().LogError("Unknown context object.");
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
        GpaLogger::Instance().LogError("Invalid pass.");
        return kGpaStatusErrorFailed;
    }

    if (!pass->DoesSampleExist(sample_id))
    {
        GpaLogger::Instance().LogError("Sample not found in pass.");
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
        GpaLogger::Instance().LogError("Sample not found in session.");
        return kGpaStatusErrorSampleNotFound;
    }

    return kGpaStatusOk;
}

/// Macro to check the session sample type.
#define CHECK_SESSION_SAMPLE_TYPE(sample_type)                                               \
    GpaSessionSampleType session_sample_type = (*gpa_session_id)->GetSampleType();           \
    if (sample_type != session_sample_type)                                                  \
    {                                                                                        \
        GpaLogger::Instance().LogError("Session does not support the correct sample type."); \
        return kGpaStatusErrorIncompatibleSampleTypes;                                       \
    }

/// Macro to check the session sample type when 2 sample types are valid.
#define CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(sample_type, additional_sample_type)              \
    GpaSessionSampleType session_sample_type = (*gpa_session_id)->GetSampleType();           \
    if (sample_type != session_sample_type && additional_sample_type != session_sample_type) \
    {                                                                                        \
        GpaLogger::Instance().LogError("Session does not support the correct sample type."); \
        return kGpaStatusErrorIncompatibleSampleTypes;                                       \
    }

GPA_LIB_DECL GpaStatus GpaGetVersion(GpaUInt32* major_version, GpaUInt32* minor_version, GpaUInt32* build, GpaUInt32* update_version)
{
    try
    {
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        GPA_CHECK_NULLPTR(major_version);
        GPA_CHECK_NULLPTR(minor_version);
        GPA_CHECK_NULLPTR(build);
        GPA_CHECK_NULLPTR(update_version);

        *major_version  = GPA_MAJOR_VERSION;
        *minor_version  = GPA_MINOR_VERSION;
        *build          = GPA_BUILD_NUMBER;
        *update_version = GPA_UPDATE_VERSION;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(*major_version) << GPA_PARAM_STRING(*minor_version) << GPA_PARAM_STRING(*build) << GPA_PARAM_STRING(*update_version));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        GPA_CHECK_NULLPTR(gpa_func_table);

        GpaFunctionTable* function_table = reinterpret_cast<GpaFunctionTable*>(gpa_func_table);

        bool      correct_major_version     = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER == function_table->major_version;
        GpaUInt32 client_supplied_minor_ver = function_table->minor_version;

        function_table->major_version = GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER;
        function_table->minor_version = GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER;

        if (!correct_major_version)
        {
            // NOTE: In most cases a client won't have registered a logging callback yet.
            GpaLogger::Instance().LogError("Client major version mismatch.");
            return kGpaStatusErrorLibLoadMajorVersionMismatch;
        }

        if (client_supplied_minor_ver > GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER)
        {
            // NOTE: In most cases a client won't have registered a logging callback yet.
            GpaLogger::Instance().LogError("Client minor version mismatch.");
            return kGpaStatusErrorLibLoadMinorVersionMismatch;
        }

        GpaFunctionTable gpa_function_table = {};
#define GPA_FUNCTION_PREFIX(func) gpa_function_table.func = func;
#include "gpu_performance_api/gpu_perf_api_functions.h"
#undef GPA_FUNCTION_PREFIX

        // Copy only as many bytes as the caller's table advertises: older callers may have
        // provided a smaller buffer, so we treat the destination as a raw byte range rather
        // than a full GpaFunctionTable to avoid UB.
        const GpaUInt32 copy_size = std::min(client_supplied_minor_ver, static_cast<GpaUInt32>(sizeof(gpa_function_table)));
        const auto      src_bytes = std::as_bytes(std::span{&gpa_function_table, 1}).first(copy_size);
        auto* const     dst_begin = static_cast<std::byte*>(gpa_func_table);
        const auto      dst_bytes = std::span<std::byte>{dst_begin, copy_size};
        std::ranges::copy(src_bytes, dst_bytes.begin());

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_func_table));

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
            GpaLogger::Instance().LogDebugError("Parameter 'callback_func_ptr' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        GpaLogger::Instance().SetLoggingCallback(logging_type, callback_func_ptr);

        GpaLogger::Instance().LogMessage("Logging callback registered successfully.");
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (gpa_imp != nullptr) [[unlikely]]
        {
            GpaLogger::Instance().LogError("GPA was already initialized.");
            return kGpaStatusErrorGpaAlreadyInitialized;
        }

        IGpaImplementor& implementor = CreateImplementor();
        gpa_imp                      = &implementor;

        const GpaStatus status = gpa_imp->Initialize(gpa_initialize_flags);

        if (status != kGpaStatusOk) [[unlikely]]
        {
            GpaDestroy();
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_initialize_flags) << GPA_PARAM_STRING(status));

        return status;
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (gpa_imp == nullptr) [[unlikely]]
        {
            GpaLogger::Instance().LogError("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        gpa_imp->Destroy();
        gpa_imp = nullptr;

        DestroyImplementor();

        return kGpaStatusOk;
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (nullptr == gpa_imp)
        {
            GpaLogger::Instance().LogError("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (nullptr == api_context)
        {
            GpaLogger::Instance().LogError("Parameter 'api_context' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        if (nullptr == gpa_context_id)
        {
            GpaLogger::Instance().LogError("Parameter 'gpa_context_id' is NULL.");
            return kGpaStatusErrorNullPointer;
        }

        GpaStatus ret_status = gpa_imp->OpenContext(api_context, gpa_open_context_flags, gpa_context_id);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(api_context)
                         << GPA_PARAM_STRING(gpa_open_context_flags) << GPA_PARAM_STRING(*gpa_context_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }

        if ((*gpa_context_id)->GetApiType() != gpa_imp->GetApiType())
        {
            GpaLogger::Instance().LogError("The context's API type does not match GPA's API type.");
            return kGpaStatusErrorInvalidParameter;
        }

        GpaStatus ret_status = gpa_imp->CloseContext(gpa_context_id);
        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(sample_types);

        const std::optional<GpaContextSampleTypeFlags> supported_sample_types = (*gpa_context_id)->GetSupportedSampleTypes();
        if (!supported_sample_types.has_value())
        {
            GpaLogger::Instance().LogError("Failed to get supported sample types.");
            return kGpaStatusErrorFailed;
        }

        *sample_types = *supported_sample_types;

        return kGpaStatusOk;
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(device_id);
        GPA_CHECK_NULLPTR(revision_id);

        const GpaHwInfo& hw_info = (*gpa_context_id)->GetHwInfo();

        GpaStatus ret_status = kGpaStatusErrorFailed;

        if (hw_info.GetDeviceId(*device_id) && hw_info.GetRevisionId(*revision_id))
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(*device_id) << GPA_PARAM_STRING(*revision_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(device_name);

        const GpaHwInfo& hw_info    = (*gpa_context_id)->GetHwInfo();
        GpaStatus        ret_status = kGpaStatusErrorFailed;

        if (hw_info.GetDeviceName(*device_name))
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id)
                         << GPA_PARAM_STRING(num_shader_engines) << GPA_PARAM_STRING(num_compute_units) << GPA_PARAM_STRING(num_simds)
                         << GPA_PARAM_STRING(num_waves_per_simd) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(hardware_generation);

        const GpaHwInfo& hw_info    = (*gpa_context_id)->GetHwInfo();
        GpaStatus        ret_status = kGpaStatusOk;

        // Realistically hw_info should always be able to provide a hardware generation for supported GPUs, but add a check just in case.
        if (const std::optional<device_info::HwGeneration> di_hw_generation = hw_info.GetHwGeneration(); di_hw_generation.has_value()) [[likely]]
        {
            *hardware_generation = ConvertDeviceInfoHwGenerationToGpaHwGeneration(di_hw_generation.value());
        }
        else
        {
            ret_status           = kGpaStatusErrorFailed;
            *hardware_generation = kGpaHwGenerationNone;
            GpaLogger::Instance().LogError("Failed to get device generation.");
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(max_wave_slots);

        // Calculate the max wave slots
        const GpaHwInfo& hw_info = (*gpa_context_id)->GetHwInfo();
        *max_wave_slots          = hw_info.GetMaxWaveSlots();

        constexpr GpaStatus ret_status = kGpaStatusOk;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status) << GPA_PARAM_STRING(*max_wave_slots));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceMaxVgprs(GpaContextId gpa_context_id, GpaUInt32* max_vgprs)
{
    try
    {
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(max_vgprs);

        GpaStatus ret_status = kGpaStatusOk;

        const GpaHwInfo& hw_info = (*gpa_context_id)->GetHwInfo();

        *max_vgprs = hw_info.GetTotalVgprs();

        if (*max_vgprs == 0)
        {
            assert(!"All supported GPUs should have a non-0 value!");
            ret_status = kGpaStatusErrorHardwareNotSupported;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status) << GPA_PARAM_STRING(*max_vgprs));

        return ret_status;
    }
    catch (...)
    {
        return kGpaStatusErrorException;
    }
}

GPA_LIB_DECL GpaStatus GpaGetDeviceMaxLdsBytes(GpaContextId gpa_context_id, GpaUInt32* max_lds_bytes)
{
    try
    {
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }
        GPA_CHECK_NULLPTR(max_lds_bytes);

        GpaStatus ret_status = kGpaStatusOk;

        const GpaHwInfo& hw_info = (*gpa_context_id)->GetHwInfo();

        if (const std::optional<uint32_t> result = hw_info.GetTotalLdsBytes(); result.has_value())
        {
            *max_lds_bytes = result.value();
        }
        else
        {
            assert(!"All supported GPUs should have a non-0 value!");
            *max_lds_bytes = 0;
            ret_status     = kGpaStatusErrorHardwareNotSupported;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id) << GPA_PARAM_STRING(ret_status) << GPA_PARAM_STRING(*max_lds_bytes));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(number_of_counters);

        GpaStatus ret_status = (*gpa_session_id)->GetNumCounters(number_of_counters);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(*number_of_counters) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_name);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(counter_name);
        GPA_CHECK_NULLPTR(counter_index);

        bool counter_found = (kGpaStatusOk == (*gpa_session_id)->GetCounterIndex(counter_name, counter_index));

        if (!counter_found)
        {
            GpaLogger::Instance().LogError("Specified counter '{}' was not found. Please check spelling or availability.", counter_name);
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_group);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_description);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_data_type);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_usage_type);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_uuid);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));
        GPA_CHECK_NULLPTR(counter_sample_type);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (kGpaDataTypeLast <= counter_data_type)
        {
            GpaLogger::Instance().LogError("Unable to get string for data type: invalid data type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        GPA_CHECK_NULLPTR(type_as_str);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (kGpaUsageTypeLast <= counter_usage_type)
        {
            GpaLogger::Instance().LogError("Unable to get string for usage type: invalid usage type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        GPA_CHECK_NULLPTR(usage_type_as_str);

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (const GpaStatus status = CheckGPAContentIdExistsAndIsOpen(gpa_context_id); status != kGpaStatusOk)
        {
            return status;
        }

        if (gpa_session_sample_type >= kGpaSessionSampleTypeLast)
        {
            GpaLogger::Instance().LogError("Invalid sample type specified.");
            return kGpaStatusErrorInvalidParameter;
        }

        GPA_CHECK_NULLPTR(gpa_session_id);

        const std::optional<GpaContextSampleTypeFlags> supported_sample_types = (*gpa_context_id)->GetSupportedSampleTypes();
        if (!supported_sample_types.has_value())
        {
            GpaLogger::Instance().LogError("Failed to get supported sample types.");
            return kGpaStatusErrorFailed;
        }

        // Next check that the set of sample types specified is compatible with context's set of supported sample types.
        {
            static_assert(GpaSessionSampleType::kGpaSessionSampleTypeLast == 4);

            // Returns false if the sample_type is incompatible with context's sample_types.
            auto invalid_sample_type = [&gpa_session_sample_type, &supported_sample_types](GpaSessionSampleType      sample_type,
                                                                                           GpaContextSampleTypeFlags sample_type_flags) -> bool {
                return (sample_type == gpa_session_sample_type) && (sample_type_flags != (sample_type_flags & *supported_sample_types));
            };
            const bool invalid_discrete = invalid_sample_type(kGpaSessionSampleTypeDiscreteCounter, kGpaContextSampleTypeDiscreteCounter);
            const bool invalid_spm      = invalid_sample_type(kGpaSessionSampleTypeStreamingCounter, kGpaContextSampleTypeStreamingCounter);
            const bool invalid_sqtt     = invalid_sample_type(kGpaSessionSampleTypeSqtt, kGpaContextSampleTypeSqtt);
            const auto invalid_spm_and_sqtt =
                invalid_sample_type(kGpaSessionSampleTypeStreamingCounterAndSqtt, kGpaContextSampleTypeStreamingCounter | kGpaContextSampleTypeSqtt);

            if (invalid_discrete || invalid_spm || invalid_sqtt || invalid_spm_and_sqtt)
            {
                GpaLogger::Instance().LogError("Unable to create session: sample_type is incompatible with context's sample_types.");
                return kGpaStatusErrorIncompatibleSampleTypes;
            }
        }

        *gpa_session_id      = (*gpa_context_id)->CreateSession(gpa_session_sample_type);
        GpaStatus ret_status = (nullptr != (*gpa_session_id)) ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_context_id)
                         << GPA_PARAM_STRING(gpa_session_sample_type) << GPA_PARAM_STRING(*gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaContext* gpa_context = (*gpa_session_id)->GetParentContext();
        GpaStatus    ret_status  = gpa_context->DeleteSession(gpa_session_id) ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();
        CHECK_CONTEXT_IS_OPEN(gpa_context);

        GpaStatus ret_status = gpa_context->BeginSession(gpa_session);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        IGpaSession* gpa_session = gpa_session_id->Object();
        GpaStatus    ret_status  = gpa_session->Reset();

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();

        GpaStatus ret_status = gpa_context->EndSession(gpa_session, false);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        IGpaSession* gpa_session = gpa_session_id->Object();
        IGpaContext* gpa_context = gpa_session->GetParentContext();

        GpaStatus ret_status = gpa_context->EndSession(gpa_session, true);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(gpa_sqtt_instruction_mask);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = kGpaStatusOk;

        *gpa_sqtt_instruction_mask = (*gpa_session_id)->GetSqttInstructionMask();

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = kGpaStatusOk;

        (*gpa_session_id)->SetSqttInstructionMask(sqtt_instruction_mask);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(sqt_compute_unit_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        *sqt_compute_unit_id = (*gpa_session_id)->GetSqttComputeUnitId();

        GpaStatus ret_status = kGpaStatusOk;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        (*gpa_session_id)->SetSqttComputeUnitId(sqtt_compute_unit_id);

        GpaStatus ret_status = kGpaStatusOk;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeSqtt);

        auto ret_status = (*gpa_session_id)->SqttBegin(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeSqtt);

        auto ret_status = (*gpa_session_id)->SqttEnd(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SqttGetSampleResultSize(sample_result_size_in_bytes);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeSqtt, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SqttGetSampleResult(sample_result_size_in_bytes, sqtt_results);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounterAndSqtt);

        const GpaStatus ret_status = (*gpa_session_id)->SqttSpmBegin(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounterAndSqtt);

        const GpaStatus ret_status = (*gpa_session_id)->SqttSpmEnd(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmSetSampleInterval(interval);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmSetDuration(ns_duration);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(command_list);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounter);

        auto ret_status = (*gpa_session_id)->SpmBegin(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE(kGpaSessionSampleTypeStreamingCounter);

        auto ret_status = (*gpa_session_id)->SpmEnd(command_list);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmGetSampleResultSize(sample_result_size_in_bytes);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        auto ret_status = (*gpa_session_id)->SpmGetSampleResult(sample_result_size_in_bytes, spm_results);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        CHECK_SESSION_SAMPLE_TYPE_MULTIPLE(kGpaSessionSampleTypeStreamingCounter, kGpaSessionSampleTypeStreamingCounterAndSqtt);

        GpaStatus ret_status = (*gpa_session_id)->SpmCalculateDerivedCounters(spm_data, derived_counter_count, derived_counter_results);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));

        GpaStatus ret_status = (*gpa_session_id)->EnableCounter(counter_index);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(counter_index) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_COUNTER_INDEX_OUT_OF_RANGE(counter_index, (*gpa_session_id));

        GpaStatus ret_status = (*gpa_session_id)->DisableCounter(counter_index);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(counter_index) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaUInt32 index;
        GpaStatus status = (*gpa_session_id)->GetCounterIndex(counter_name, &index);

        if (kGpaStatusOk != status)
        {
            GpaLogger::Instance().LogError("Specified counter '{}' was not found. Please check spelling or availability.", counter_name);
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaUInt32 index;
        GpaStatus status = (*gpa_session_id)->GetCounterIndex(counter_name, &index);

        if (kGpaStatusOk != status)
        {
            GpaLogger::Instance().LogError("Specified counter '{}' was not found. Please check spelling or availability.", counter_name);
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING_FOR_COUNTERS(gpa_session_id);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());

        GpaStatus ret_status = (*gpa_session_id)->DisableAllCounters();

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(number_of_passes);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        GpaStatus ret_status = (*gpa_session_id)->GetNumRequiredPasses(number_of_passes);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(*number_of_passes) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(enabled_counter_count);
        CHECK_CONTEXT_IS_OPEN((*gpa_session_id)->GetParentContext());
        GpaStatus ret_status = (*gpa_session_id)->GetNumEnabledCounters(enabled_counter_count);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(*enabled_counter_count) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(enabled_counter_index);
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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GpaLogger::Instance().LogError("Session has not been started.");
            return kGpaStatusErrorSessionNotStarted;
        }

        if (kGpaCommandListLast <= command_list_type)
        {
            GpaLogger::Instance().LogError("Invalid value for 'command_list_type' parameter.");
            return kGpaStatusErrorInvalidParameter;
        }

        bool command_list_required = gpa_imp->IsCommandListRequired();

        if (command_list_required)
        {
            if (!command_list)
            {
                GpaLogger::Instance().LogError("Command list cannot be NULL.");
                return kGpaStatusErrorNullPointer;
            }

            if (kGpaCommandListNone == command_list_type)
            {
                GpaLogger::Instance().LogError("NULL command list is not supported.");
                return kGpaStatusErrorInvalidParameter;
            }
        }
        else
        {
            if (command_list || (kGpaCommandListNone != command_list_type))
            {
                GpaLogger::Instance().LogError("'command_list' must be NULL and 'command_list_type' must be kGpaCommandListNone.");
                return kGpaStatusErrorInvalidParameter;
            }
        }

        GPA_CHECK_NULLPTR(gpa_command_list_id);

        if (gpa_imp->DoesCommandListExist(*gpa_command_list_id))
        {
            GpaLogger::Instance().LogError("Command List already created.");
            return kGpaStatusErrorCommandListAlreadyStarted;
        }

        *gpa_command_list_id = (*gpa_session_id)->CreateCommandList(pass_index, command_list, command_list_type);

        bool status = false;

        if (nullptr != *gpa_command_list_id)
        {
            status = (*(*gpa_command_list_id))->Begin();
            if (!status)
            {
                GpaLogger::Instance().LogError("Unable to begin the command list.");
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to create the command list.");
        }

        GpaStatus ret_status = status ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id)
                         << GPA_PARAM_STRING(pass_index) << GPA_PARAM_STRING(command_list) << GPA_PARAM_STRING(command_list_type)
                         << GPA_PARAM_STRING(*gpa_command_list_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_COMMAND_LIST_ID_EXISTS(gpa_command_list_id);

        if (!(*gpa_command_list_id)->IsCommandListRunning())
        {
            GpaLogger::Instance().LogError("Command list has already been ended.");
            return kGpaStatusErrorCommandListAlreadyEnded;
        }

        GpaStatus ret_status = (*gpa_command_list_id)->End() ? kGpaStatusOk : kGpaStatusErrorFailed;

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_command_list_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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
                GpaLogger::Instance().LogError("Invalid pass index.");
                ret_status = kGpaStatusErrorIndexOutOfRange;
            }
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(sample_id) << GPA_PARAM_STRING(gpa_command_list_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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
                GpaLogger::Instance().LogError("Invalid pass index.");
                ret_status = kGpaStatusErrorIndexOutOfRange;
            }
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_command_list_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (nullptr == gpa_imp)
        {
            GpaLogger::Instance().LogError("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (!gpa_imp->IsContinueSampleOnCommandListSupported())
        {
            GpaLogger::Instance().LogError("This feature is not supported.");
            return kGpaStatusErrorApiNotSupported;
        }

        GpaStatus ret_status = kGpaStatusOk;
        CHECK_COMMAND_LIST_ID_EXISTS(primary_gpa_command_list_id);

        if ((ret_status = CheckSampleIdExistsInPass((*primary_gpa_command_list_id)->GetPass(), source_sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        ret_status = ((*primary_gpa_command_list_id)->GetParentSession()->ContinueSampleOnCommandList(source_sample_id, primary_gpa_command_list_id));

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(source_sample_id) << GPA_PARAM_STRING(primary_gpa_command_list_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        if (nullptr == gpa_imp)
        {
            GpaLogger::Instance().LogError("GPA has not been initialized.");
            return kGpaStatusErrorGpaNotInitialized;
        }

        if (!gpa_imp->IsCopySecondarySampleSupported())
        {
            GpaLogger::Instance().LogError("This feature is not supported.");
            return kGpaStatusErrorApiNotSupported;
        }

        CHECK_COMMAND_LIST_ID_EXISTS(secondary_gpa_command_list_id);
        CHECK_COMMAND_LIST_ID_EXISTS(primary_gpa_command_list_id);

        GpaStatus ret_status = ((*primary_gpa_command_list_id)
                                    ->GetParentSession()
                                    ->CopySecondarySamples(secondary_gpa_command_list_id, primary_gpa_command_list_id, number_of_samples, new_sample_ids));

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(secondary_gpa_command_list_id) << GPA_PARAM_STRING(primary_gpa_command_list_id) << GPA_PARAM_STRING(number_of_samples)
                                                                         << GPA_PARAM_STRING(*new_sample_ids) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING(gpa_session_id);
        GPA_CHECK_NULLPTR(sample_count);

        *sample_count = (*gpa_session_id)->GetSampleCount();

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(*sample_count));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        CHECK_SESSION_RUNNING(gpa_session_id);
        GPA_CHECK_NULLPTR(sample_id);

        GpaStatus ret_status    = kGpaStatusErrorSampleNotFound;
        GpaUInt32 ret_sample_id = 0u;
        bool      found         = (*gpa_session_id)->GetSampleIdByIndex(index, ret_sample_id);

        if (found)
        {
            *sample_id = ret_sample_id;
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(index) << GPA_PARAM_STRING(*sample_id) << GPA_PARAM_STRING(ret_status));

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

        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GpaLogger::Instance().LogError("Session has not been started.");
            return kGpaStatusErrorSessionNotStarted;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        (*gpa_session_id)->UpdateResults();

        if ((*gpa_session_id)->IsResultReady())
        {
            ret_status = kGpaStatusOk;
        }

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        CHECK_SESSION_ID_EXISTS(gpa_session_id);

        GpaStatus ret_status = kGpaStatusResultNotReady;

        if (GpaSessionState::kGpaSessionStateNotStarted == (*gpa_session_id)->GetState())
        {
            GpaLogger::Instance().LogError("Session has not been started.");
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

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(pass_index) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        GpaStatus ret_status = kGpaStatusOk;

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(sample_result_size_in_bytes);

        if ((ret_status = CheckSampleIdExistsInSession(gpa_session_id, sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        *sample_result_size_in_bytes = (*gpa_session_id)->GetSampleResultSizeInBytes(sample_id);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id)
                         << GPA_PARAM_STRING(sample_id) << GPA_PARAM_STRING(*sample_result_size_in_bytes) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

        GpaStatus ret_status = kGpaStatusOk;

        CHECK_SESSION_ID_EXISTS(gpa_session_id);
        GPA_CHECK_NULLPTR(counter_sample_results);

        if ((ret_status = CheckSampleIdExistsInSession(gpa_session_id, sample_id)) != kGpaStatusOk)
        {
            return ret_status;
        }

        CHECK_SESSION_RUNNING(gpa_session_id);

        ret_status = (*gpa_session_id)->GetSampleResult(sample_id, sample_result_size_in_bytes, counter_sample_results);

        GPA_INTERNAL_LOG(GPA_PARAM_STRING(gpa_session_id) << GPA_PARAM_STRING(sample_id) << GPA_PARAM_STRING(sample_result_size_in_bytes)
                                                          << GPA_PARAM_STRING(counter_sample_results) << GPA_PARAM_STRING(ret_status));

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
        GPA_PROFILE_FUNCTION();
        GPA_TRACE_FUNCTION();

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
