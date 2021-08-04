//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
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
    context_info_map_.clear();
}

GpaStatus GpaContextCounterMediator::GenerateCounters(const IGpaContext* gpa_context, GpaOpenContextFlags flags, GpaUInt8 generate_asic_specific_counters)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (DoesContextExist(gpa_context))
    {
        return kGpaStatusErrorContextAlreadyOpen;
    }

    GpaStatus             ret_status        = kGpaStatusOk;
    IGpaCounterAccessor*  counter_accessor  = nullptr;
    IGpaCounterScheduler* counter_scheduler = nullptr;
    const GpaHwInfo*      hw_info           = gpa_context->GetHwInfo();

    if (nullptr == hw_info)
    {
        return kGpaStatusErrorFailed;
    }

    GpaUInt32 vendor_id;
    GpaUInt32 device_id;
    GpaUInt32 revision_id;

    if (hw_info->GetVendorId(vendor_id) && hw_info->GetDeviceId(device_id) && hw_info->GetRevisionId(revision_id))
    {
        ret_status = ::GenerateCounters(
            gpa_context->GetApiType(), vendor_id, device_id, revision_id, flags, generate_asic_specific_counters, &counter_accessor, &counter_scheduler);

        if (kGpaStatusOk == ret_status)
        {
            GpaContextStatus contextStatus = {counter_scheduler, counter_accessor};

            if (kGpaStatusOk == counter_scheduler->SetCounterAccessor(counter_accessor, vendor_id, device_id, revision_id))
            {
                context_info_map_.insert(GpaCtxStatusInfoPair(gpa_context, contextStatus));
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

bool GpaContextCounterMediator::IsCounterSchedulingSupported(const IGpaContext* gpa_context) const
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return false;
    }

    return nullptr != context_info_map_.at(gpa_context).counter_scheduler && nullptr != context_info_map_.at(gpa_context).counter_accessor;
}

IGpaCounterAccessor* GpaContextCounterMediator::GetCounterAccessor(const IGpaContext* gpa_context) const
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return nullptr;
    }

    return context_info_map_.at(gpa_context).counter_accessor;
}

GpaStatus GpaContextCounterMediator::ScheduleCounters(const IGpaContext* gpa_context, const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaSession* active_session = gpa_context->GetActiveSession();

    if (nullptr != active_session && gpa_session != active_session)
    {
        return kGpaStatusErrorOtherSessionActive;
    }

    IGpaCounterScheduler* counter_scheduler = context_info_map_.at(gpa_context).counter_scheduler;

    for (std::vector<GpaUInt32>::const_iterator it = counter_set.cbegin(); it != counter_set.cend(); ++it)
    {
        counter_scheduler->EnableCounter(*it);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::UnscheduleCounters(const IGpaContext*            gpa_context,
                                                        const IGpaSession*            gpa_session,
                                                        const std::vector<GpaUInt32>& counter_set)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaSession* active_session = gpa_context->GetActiveSession();

    if (nullptr != active_session && gpa_session != active_session)
    {
        return kGpaStatusErrorOtherSessionActive;
    }

    IGpaCounterScheduler* counter_scheduler = context_info_map_.at(gpa_context).counter_scheduler;

    for (std::vector<GpaUInt32>::const_iterator it = counter_set.cbegin(); it != counter_set.cend(); ++it)
    {
        counter_scheduler->DisableCounter(*it);
    }

    return kGpaStatusOk;
}

GpaStatus GpaContextCounterMediator::GetRequiredPassCount(const IGpaContext*            gpa_context,
                                                          const std::vector<GpaUInt32>& counter_set,
                                                          unsigned int&                 pass_required)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = context_info_map_.at(gpa_context).counter_scheduler;

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

CounterResultLocationMap* GpaContextCounterMediator::GetCounterResultLocations(const IGpaContext* gpa_context, const unsigned int& public_counter_index)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = context_info_map_.at(gpa_context).counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCounterResultLocations(public_counter_index);
}

void GpaContextCounterMediator::RemoveContext(IGpaContext* gpa_context)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (DoesContextExist(gpa_context))
    {
        context_info_map_.erase(gpa_context);
    }
}

CounterList* GpaContextCounterMediator::GetCounterForPass(IGpaContext* gpa_context, PassIndex pass_index)
{
    std::lock_guard<std::mutex> lock(context_info_map_mutex_);

    if (!DoesContextExist(gpa_context))
    {
        return nullptr;
    }

    IGpaCounterScheduler* counter_scheduler = context_info_map_[gpa_context].counter_scheduler;

    if (nullptr == counter_scheduler)
    {
        return nullptr;
    }

    return counter_scheduler->GetCountersForPass(pass_index);
}

bool GpaContextCounterMediator::DoesContextExist(const IGpaContext* gpa_context) const
{
    return context_info_map_.find(gpa_context) != context_info_map_.cend();
}
