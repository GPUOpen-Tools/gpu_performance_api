//==============================================================================
// Copyright (c) 2018-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Context Counter Mediator Implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

namespace
{
    GpaContextCounterMediator::GpaCtxStatusInfoMap* session_info_map = nullptr;  ///< Pointer to a map of sessions to corresponding info.
    std::mutex                                      context_info_map_mutex;      ///< Mutex for context info map.

    /// @brief Checks whether the given session exists or not.
    ///
    /// @param [in] gpa_session GPA session.
    ///
    /// @return True if session exists otherwise false.
    [[nodiscard]] bool DoesSessionExist(const IGpaSession* gpa_session)
    {
        return session_info_map->contains(gpa_session);
    }
}  // namespace

GpaStatus GpaContextCounterMediator::Initialize(GpaCtxStatusInfoMap* map)
{
    if (map == nullptr)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!map->empty())
    {
        return kGpaStatusErrorFailed;
    }

    session_info_map = map;
    return kGpaStatusOk;
}

void GpaContextCounterMediator::Clear()
{
    session_info_map = nullptr;
}

GpaStatus GpaContextCounterMediator::GenerateCounters(const IGpaSession* gpa_session, GpaOpenContextFlags flags)
{
    const IGpaContext* gpa_context = gpa_session->GetParentContext();

    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorFailed;
    }

    GpaStatus             ret_status        = kGpaStatusOk;
    IGpaCounterAccessor*  counter_accessor  = nullptr;
    IGpaCounterScheduler* counter_scheduler = nullptr;
    const GpaHwInfo&      hw_info           = gpa_context->GetHwInfo();

    GpaUInt32 vendor_id;
    GpaUInt32 device_id;
    GpaUInt32 revision_id;

    if (hw_info.GetVendorId(vendor_id) && hw_info.GetDeviceId(device_id) && hw_info.GetRevisionId(revision_id))
    {
        const GpaSessionSampleType sample_type = gpa_session->GetSampleType();

        // Sqtt has no counters to generate.
        if (sample_type == kGpaSessionSampleTypeSqtt)
        {
            return ret_status;
        }

        ret_status =
            ::GenerateCounters(gpa_context->GetApiType(), sample_type, vendor_id, device_id, revision_id, flags, &counter_accessor, &counter_scheduler);

        if (kGpaStatusOk == ret_status)
        {
            assert(counter_accessor != nullptr);
            assert(counter_scheduler != nullptr);

            const GpaContextStatus context_status = {.counter_scheduler = counter_scheduler, .counter_accessor = counter_accessor};

            if (kGpaStatusOk == counter_scheduler->SetCounterAccessor(counter_accessor, vendor_id, device_id, revision_id))
            {
                session_info_map->insert(std::make_pair(gpa_session, context_status));
            }
            else
            {
                ret_status = kGpaStatusErrorFailed;
                GPA_LOG_ERROR("Failed to set counter accessor.");
            }
        }
    }
    else
    {
        ret_status = kGpaStatusErrorFailed;
    }

    return ret_status;
}

bool GpaContextCounterMediator::IsCounterSchedulingSupported(const IGpaSession* gpa_session)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return false;
    }

    return nullptr != session_info_map->at(gpa_session).counter_scheduler && nullptr != session_info_map->at(gpa_session).counter_accessor;
}

IGpaCounterAccessor* GpaContextCounterMediator::GetCounterAccessor(const IGpaSession* gpa_session)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    return session_info_map->at(gpa_session).counter_accessor;
}

GpaStatus GpaContextCounterMediator::ScheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaSession* active_session = gpa_session->GetParentContext()->GetActiveSession();

    if (nullptr != active_session && gpa_session != active_session)
    {
        return kGpaStatusErrorOtherSessionActive;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map->at(gpa_session).counter_scheduler;

    for (GpaUInt32 const& counter : counter_set)
    {
        counter_scheduler->EnableCounter(counter);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::UnscheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map->at(gpa_session).counter_scheduler;

    for (GpaUInt32 const& counter : counter_set)
    {
        counter_scheduler->DisableCounter(counter);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::GetRequiredPassCount(const IGpaSession*            gpa_session,
                                                          const std::vector<GpaUInt32>& counter_set,
                                                          unsigned int&                 pass_required)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map->at(gpa_session).counter_scheduler;

    counter_scheduler->DisableAllCounters();

    bool succeed = true;

    for (GpaUInt32 const& counter : counter_set)
    {
        succeed &= kGpaStatusOk == counter_scheduler->EnableCounter(counter);
    }

    if (!succeed)
    {
        return kGpaStatusErrorFailed;
    }

    GpaUInt32       pass_req   = {};
    const GpaStatus ret_status = counter_scheduler->GetNumRequiredPasses(&pass_req);

    if (kGpaStatusOk == ret_status)
    {
        pass_required = pass_req;
    }

    return ret_status;
}

CounterResultLocationMap* GpaContextCounterMediator::GetCounterResultLocations(const IGpaSession* gpa_session, const unsigned int& public_counter_index)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map->at(gpa_session).counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCounterResultLocations(public_counter_index);
}

void GpaContextCounterMediator::RemoveContext(IGpaSession* gpa_session)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (DoesSessionExist(gpa_session))
    {
        session_info_map->erase(gpa_session);
    }
}

CounterList* GpaContextCounterMediator::GetCounterForPass(IGpaSession* gpa_session, PassIndex pass_index)
{
    const std::lock_guard<std::mutex> lock(context_info_map_mutex);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map->at(gpa_session).counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCountersForPass(pass_index);
}
