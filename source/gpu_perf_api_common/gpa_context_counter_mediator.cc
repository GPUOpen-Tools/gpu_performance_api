//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Context Counter Mediator Implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

GpaContextCounterMediator* GpaContextCounterMediator::kCounterManager = nullptr;

GpaContextCounterMediator* GpaContextCounterMediator::Instance()
{
    if (nullptr == kCounterManager)
    {
        kCounterManager = new (std::nothrow) GpaContextCounterMediator();
    }

    return kCounterManager;
}

void GpaContextCounterMediator::DeleteInstance()
{
    delete kCounterManager;
    kCounterManager = nullptr;
}

GpaContextCounterMediator::~GpaContextCounterMediator()
{
    session_info_map_.clear();
}

GpaStatus GpaContextCounterMediator::GenerateCounters(const IGpaSession* gpa_session, GpaOpenContextFlags flags)
{
    const IGpaContext* gpa_context = gpa_session->GetParentContext();

    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

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

            const GpaContextStatus contextStatus = {counter_scheduler, counter_accessor};

            if (kGpaStatusOk == counter_scheduler->SetCounterAccessor(counter_accessor, vendor_id, device_id, revision_id))
            {
                session_info_map_.insert(GpaCtxStatusInfoPair(gpa_session, contextStatus));
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

bool GpaContextCounterMediator::IsCounterSchedulingSupported(const IGpaSession* gpa_session) const
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return false;
    }

    return nullptr != session_info_map_.at(gpa_session).counter_scheduler && nullptr != session_info_map_.at(gpa_session).counter_accessor;
}

IGpaCounterAccessor* GpaContextCounterMediator::GetCounterAccessor(const IGpaSession* gpa_session) const
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    return session_info_map_.at(gpa_session).counter_accessor;
}

GpaStatus GpaContextCounterMediator::ScheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaSession* active_session = gpa_session->GetParentContext()->GetActiveSession();

    if (nullptr != active_session && gpa_session != active_session)
    {
        return kGpaStatusErrorOtherSessionActive;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map_.at(gpa_session).counter_scheduler;

    for (std::vector<GpaUInt32>::const_iterator it = counter_set.cbegin(); it != counter_set.cend(); ++it)
    {
        counter_scheduler->EnableCounter(*it);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::UnscheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map_.at(gpa_session).counter_scheduler;

    for (std::vector<GpaUInt32>::const_iterator it = counter_set.cbegin(); it != counter_set.cend(); ++it)
    {
        counter_scheduler->DisableCounter(*it);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::GetRequiredPassCount(const IGpaSession*            gpa_session,
                                                          const std::vector<GpaUInt32>& counter_set,
                                                          unsigned int&                 pass_required)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map_.at(gpa_session).counter_scheduler;

    GpaUInt32 pass_req = 0u;
    counter_scheduler->DisableAllCounters();

    bool succeed = true;

    for (std::vector<GpaUInt32>::const_iterator it = counter_set.cbegin(); it != counter_set.cend() && succeed; ++it)
    {
        succeed &= kGpaStatusOk == counter_scheduler->EnableCounter(*it);
    }

    if (!succeed)
    {
        return kGpaStatusErrorFailed;
    }

    GpaStatus ret_status = counter_scheduler->GetNumRequiredPasses(&pass_req);

    if (kGpaStatusOk == ret_status)
    {
        pass_required = pass_req;
    }

    return ret_status;
}

CounterResultLocationMap* GpaContextCounterMediator::GetCounterResultLocations(const IGpaSession* gpa_session, const unsigned int& public_counter_index)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map_.at(gpa_session).counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCounterResultLocations(public_counter_index);
}

void GpaContextCounterMediator::RemoveContext(IGpaSession* gpa_session)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (DoesSessionExist(gpa_session))
    {
        session_info_map_.erase(gpa_session);
    }
}

CounterList* GpaContextCounterMediator::GetCounterForPass(IGpaSession* gpa_session, PassIndex pass_index)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesSessionExist(gpa_session))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = session_info_map_[gpa_session].counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCountersForPass(pass_index);
}

bool GpaContextCounterMediator::DoesSessionExist(const IGpaSession* gpa_session) const
{
    return session_info_map_.find(gpa_session) != session_info_map_.cend();
}
