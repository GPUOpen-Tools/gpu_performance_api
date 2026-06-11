//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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
        GpaLogger::Instance().LogError("Invalid flags passed to GpaInitialize.");
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

void GpaImplementor::Destroy()
{
    if (is_initialized_)
    {
        is_initialized_ = false;
        GpaContextCounterMediator::Clear();
        session_info_map_.clear();
        app_context_info_gpa_context_map_.clear();
    }
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
        GpaLogger::Instance().LogError("More than one clock mode specified.");
        return kGpaStatusErrorInvalidParameter;
    }

    GpaStatus gpa_status = kGpaStatusOk;

    std::lock_guard<std::mutex> lock(device_gpa_context_map_mutex_);

    if (!DoesContextInfoExist(context))
    {
        const GpaDriverInfo driver_info = GpaQueryDriverInfo();
        if (!IsDriverSupported(context))
        {
            // Driver not supported, logging error.
            GpaLogger::Instance().LogError("Driver not supported.");
            return kGpaStatusErrorDriverNotSupported;
        }

        GpaHwInfo hw_info = {};
        if (IsDeviceSupported(context, flags, driver_info, &hw_info) != kGpaStatusOk)
        {
            GpaLogger::Instance().LogError("Device not supported.");
            gpa_status = kGpaStatusErrorHardwareNotSupported;
        }
        else
        {
            std::unique_ptr<IGpaContext> new_gpa_context = OpenApiContext(context, hw_info, flags);

            if (nullptr != new_gpa_context)
            {
                IGpaContext* raw_context = new_gpa_context.get();
                *gpa_context_id          = reinterpret_cast<GpaContextId>(GpaUniqueObjectManager::Instance().CreateObject(raw_context));
                app_context_info_gpa_context_map_.emplace(GetDeviceIdentifierFromContextInfo(context), std::move(new_gpa_context));
            }
            else
            {
                GpaLogger::Instance().LogError("Failed to open API-specific GPA Context.");
                gpa_status = kGpaStatusErrorFailed;
            }
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Context is already open.");
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
            if (iter->second.get() == gpa_context)
            {
                is_found   = true;
                found_iter = iter;
            }
        }

        if (is_found)
        {
            // Extract ownership from the map and transfer it to CloseApiContext, which destroys the context.
            std::unique_ptr<IGpaContext> owned_context = std::move(found_iter->second);
            app_context_info_gpa_context_map_.erase(found_iter);

            if (!CloseApiContext(std::move(owned_context)))
            {
                GpaLogger::Instance().LogDebugError("Unable to close the API-level GPA context.");
                gpa_status = kGpaStatusErrorFailed;
            }

            // CloseApiContext always destroys the context (via unique_ptr), so always clean up
            // the GpaContextId to prevent the unique object manager from holding a dangling reference.
            GpaUniqueObjectManager::Instance().DeleteObject(gpa_context_id);
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to close the GPAContext: context not found.");
            gpa_status = kGpaStatusErrorInvalidParameter;
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Invalid context supplied.");
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
    GpaHwInfo api_hw_info;

    if (const GpaStatus status = GetHwInfoFromApi(context_info, flags, api_hw_info); status != kGpaStatusOk)
    {
        GpaLogger::Instance().LogError("Unable to get hardware information from the API.");
        return status;
    }

    const GpaApiType api = GetApiType();

    if (api_hw_info.IsUnsupportedDevice(api, driver_info))
    {
        GpaLogger::Instance().LogError("The current hardware does not properly support GPUPerfAPI.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    if (!api_hw_info.UpdateDeviceInfoBasedOnDeviceDescription())
    {
        // If this fails, then the hardware must not be supported because we don't know enough about it.
        GpaLogger::Instance().LogError("Cannot update device information.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    // Warn about driver versions older than 26.20 which have known issues. Only emit
    // here (context-open path) to avoid false positives from offline/counter-lib queries that call
    // CalculateSupportedSampleTypes without ever setting the clock mode.
#ifdef _WIN32
    if (driver_info.driver_type == kAmdProprietaryDriver)
    {
        // NOTE: The GpaDriverInfo version aren't the same as the Adrenalin version numbers.
        // We have to correlate them to know which driver versions have the known issues.
        // The minimum version that contains the fixes is Adrenalin 26.7.1, which corresponds to 26.20.
        constexpr GpaUInt32 kMinMajorVersion = 26;
        constexpr GpaUInt32 kMinMinorVersion = 20;
        if (driver_info.major < kMinMajorVersion || (driver_info.major == kMinMajorVersion && driver_info.minor < kMinMinorVersion))
        {
            const auto hw_generation = api_hw_info.GetHwGeneration();
            if (hw_generation.has_value() && *hw_generation == device_info::HwGeneration::kGfx12)
            {
                GpaLogger::Instance().LogMessage(
                    "Update to newer driver to avoid sporadic TDRs on RDNA4 hardware! Please update to Adrenalin 26.7.1 or newer.");
            }

            // Don't alert the user about clock mode issues if they aren't planning to set anything.
            if ((flags & kGpaOpenContextClockModeNoneBit) == 0)
            {
                if (api == kGpaApiDirectx12)
                {
                    // DX12 doesn't currently have a way to register clock mode failures.
                    GpaLogger::Instance().LogMessage(
                        "If you are experiencing instability after several profiling iterations or a crash, it may be related to a known issue with your "
                        "current driver. Please update to Adrenalin 26.7.1 or newer.");
                }
                else
                {
                    GpaLogger::Instance().LogMessage(
                        "If you see 'Failed to set ClockMode for profiling' in your logs please update to Adrenalin 26.7.1 or newer.");
                }
            }
        }
    }
#endif

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
