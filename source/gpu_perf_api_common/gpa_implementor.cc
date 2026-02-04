//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Common GPA Implementor.
//==============================================================================

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_unique_object.h"
#include "gpu_perf_api_common/logging.h"
#include "gpu_perf_api_common/gpa_hw_support.h"

GpaImplementor::GpaImplementor()
    : is_initialized_(false)
    , init_flags_(kGpaInitializeDefaultBit)
{
}

GpaStatus GpaImplementor::Initialize(GpaInitializeFlags flags)
{
    init_flags_ = flags;

    GpaStatus gpa_status = kGpaStatusErrorGpaAlreadyInitialized;

    if (kGpaInitializeDefaultBit != flags && kGpaInitializeSimultaneousQueuesEnableBit != flags && kGpaInitializeEnableSqttBit != flags)
    {
        GPA_LOG_ERROR("Invalid flags passed to GpaInitialize.");
        gpa_status = kGpaStatusErrorInvalidParameter;
    }
    else
    {
        if (!is_initialized_)
        {
            is_initialized_ = true;
            gpa_status      = GpaContextCounterMediator::Initialize(&session_info_map_);
        }
    }

    return gpa_status;
}

GpaStatus GpaImplementor::Destroy()
{
    GpaStatus gpa_status = kGpaStatusErrorGpaNotInitialized;

    if (is_initialized_)
    {
        is_initialized_ = false;
        gpa_status = kGpaStatusOk;
        GpaContextCounterMediator::Clear();
        session_info_map_.clear();
        app_context_info_gpa_context_map_.clear();
    }

    return gpa_status;
}

GpaStatus GpaImplementor::OpenContext(void* context, GpaOpenContextFlags flags, GpaContextId* gpa_context_id)
{
    // Validate that only a single clock mode is specified.
    unsigned int num_clock_modes = 0;

    if (kGpaOpenContextClockModeNoneBit & flags)
    {
        num_clock_modes++;
    }

    if (kGpaOpenContextClockModePeakBit & flags)
    {
        num_clock_modes++;
    }

    if (kGpaOpenContextClockModeMinMemoryBit & flags)
    {
        num_clock_modes++;
    }

    if (kGpaOpenContextClockModeMinEngineBit & flags)
    {
        num_clock_modes++;
    }

    if (1 < num_clock_modes)
    {
        GPA_LOG_ERROR("More than one clock mode specified.");
        return kGpaStatusErrorInvalidParameter;
    }

    GpaStatus gpa_status = kGpaStatusOk;

    std::lock_guard<std::mutex> lock(device_gpa_context_map_mutex_);

    if (!DoesContextInfoExist(context))
    {
        GpaHwInfo hw_info;

        const GpaDriverInfo driver_info = GpaQueryDriverInfo();
        if (!IsDriverSupported(context))
        {
            // Driver not supported, logging error.
            GPA_LOG_ERROR("Driver not supported.");
            return kGpaStatusErrorDriverNotSupported;
        }

        if (IsDeviceSupported(context, flags, driver_info, &hw_info) != kGpaStatusOk)
        {
            GPA_LOG_ERROR("Device not supported.");
            gpa_status = kGpaStatusErrorHardwareNotSupported;
        }
        else
        {
            IGpaContext* new_gpa_context = nullptr;
            new_gpa_context              = OpenApiContext(context, hw_info, flags);

            if (nullptr != new_gpa_context)
            {
                *gpa_context_id = reinterpret_cast<GpaContextId>(GpaUniqueObjectManager::Instance().CreateObject(new_gpa_context));
                app_context_info_gpa_context_map_.insert(GpaDeviceIdentifierGpaContextPair(GetDeviceIdentifierFromContextInfo(context), new_gpa_context));
            }
            else
            {
                GPA_LOG_ERROR("Failed to open API-specific GPA Context.");
                gpa_status = kGpaStatusErrorFailed;
            }
        }
    }
    else
    {
        GPA_LOG_ERROR("Context is already open.");
        gpa_status = kGpaStatusErrorContextAlreadyOpen;
    }

    return gpa_status;
}

GpaStatus GpaImplementor::CloseContext(GpaContextId gpa_context_id)
{
    GpaStatus gpa_status = kGpaStatusOk;

    if (GpaObjectType::kGpaObjectTypeContext == gpa_context_id->ObjectType() && gpa_context_id->Object()->GetApiType() == GetApiType())
    {
        std::lock_guard<std::mutex> lock(device_gpa_context_map_mutex_);

        IGpaContext* gpa_context = gpa_context_id->Object();

        // Find the context.
        bool                                       is_found   = false;
        GpaDeviceIdentifierGpaContextMap::iterator found_iter = app_context_info_gpa_context_map_.end();

        for (auto iter = app_context_info_gpa_context_map_.begin(); !is_found && iter != app_context_info_gpa_context_map_.end(); ++iter)
        {
            if (iter->second == gpa_context)
            {
                is_found   = true;
                found_iter = iter;
            }
        }

        if (is_found)
        {
            if (CloseApiContext(gpa_context))
            {
                app_context_info_gpa_context_map_.erase(found_iter);
                GpaUniqueObjectManager::Instance().DeleteObject(gpa_context_id);
            }
            else
            {
                GPA_LOG_DEBUG_ERROR("Unable to close the API-level GPA context.");
                gpa_status = kGpaStatusErrorFailed;
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to close the GPAContext: context not found.");
            gpa_status = kGpaStatusErrorInvalidParameter;
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid context supplied.");
        gpa_status = kGpaStatusErrorInvalidParameter;
    }

    return gpa_status;
}

GpaObjectType GpaImplementor::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeImplementation;
}

bool GpaImplementor::DoesContextExist(GpaContextId gpa_context_id) const
{
    bool context_found = false;

    if (nullptr != gpa_context_id)
    {
        context_found = GpaUniqueObjectManager::Instance().DoesExist(gpa_context_id);

        if (context_found && GpaObjectType::kGpaObjectTypeContext == gpa_context_id->ObjectType() && GetApiType() == gpa_context_id->Object()->GetApiType())
        {
            context_found = true;
        }
    }

    return context_found;
}

bool GpaImplementor::DoesSessionExist(GpaSessionId gpa_session_id) const
{
    bool session_found = false;

    if (nullptr != gpa_session_id)
    {
        session_found = GpaUniqueObjectManager::Instance().DoesExist(gpa_session_id);

        if (session_found && GpaObjectType::kGpaObjectTypeSession == gpa_session_id->ObjectType())
        {
            session_found = true;
        }
    }

    return session_found;
}

bool GpaImplementor::DoesCommandListExist(GpaCommandListId command_list_id) const
{
    bool command_list_found = false;

    if (nullptr != command_list_id)
    {
        command_list_found = GpaUniqueObjectManager::Instance().DoesExist(command_list_id);

        if (command_list_found && GpaObjectType::kGpaObjectTypeCommandList == command_list_id->ObjectType())
        {
            command_list_found = true;
        }
    }

    return command_list_found;
}

GpaInitializeFlags GpaImplementor::GetInitializeFlags() const
{
    return init_flags_;
}

bool GpaImplementor::IsCommandListRequired() const
{
    return false;
}

bool GpaImplementor::IsContinueSampleOnCommandListSupported() const
{
    return false;
}

bool GpaImplementor::IsCopySecondarySampleSupported() const
{
    return false;
}

bool GpaImplementor::DoesContextInfoExist(GpaContextInfoPtr context_info) const
{
    return app_context_info_gpa_context_map_.find(GetDeviceIdentifierFromContextInfo(context_info)) != app_context_info_gpa_context_map_.cend();
}

GpaStatus GpaImplementor::IsDeviceSupported(GpaContextInfoPtr    context_info,
                                            GpaOpenContextFlags  flags,
                                            GpaDriverInfo const& driver_info,
                                            GpaHwInfo*           hw_info) const
{
    GpaHwInfo    api_hw_info;

    if (!GetHwInfoFromApi(context_info, flags, api_hw_info))
    {
        GPA_LOG_ERROR("Unable to get hardware information from the API.");
        return kGpaStatusErrorFailed;
    }

    const GpaApiType api = GetApiType();

    if (api_hw_info.IsAmd())
    {
        // Checking for AMD GPUs that are not supported by GPA for one reason or another.
        if (api_hw_info.IsUnsupportedDeviceId(api, driver_info))
        {
            GPA_LOG_ERROR("The current hardware does not properly support GPUPerfAPI.");
            return kGpaStatusErrorHardwareNotSupported;
        }

        const bool device_info_ok = api_hw_info.UpdateDeviceInfoBasedOnDeviceId(api, driver_info);

        if (!device_info_ok)
        {
            // If this fails, then the hardware must not be supported because we don't know enough about it.
            GPA_LOG_ERROR("Cannot update device information.");
            return kGpaStatusErrorHardwareNotSupported;
        }
    }

    // Give the API-specific implementation a chance to verify that the hardware is supported.
    const GpaStatus status = VerifyApiHwSupport(context_info, flags, api_hw_info) ? kGpaStatusOk : kGpaStatusErrorFailed;

    if (kGpaStatusOk == status)
    {
        *hw_info = api_hw_info;
    }

    return status;
}

bool GpaImplementor::IsDriverSupported(GpaContextInfoPtr context_info) const
{
    UNREFERENCED_PARAMETER(context_info);
    return true;
}

bool GpaImplementor::CompareHwInfo(const GpaHwInfo& first, const GpaHwInfo& second) const
{
    return first == second;
}
