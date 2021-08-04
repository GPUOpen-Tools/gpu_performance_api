//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base Class for counter scheduling.
//==============================================================================

#include <list>
#include <sstream>
#include <vector>

#include "DeviceInfoUtils.h"

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_group_accessor.h"

GpaCounterSchedulerBase::GpaCounterSchedulerBase()
    : counter_accessor_(nullptr)
    , vendor_id_(0)
    , device_id_(0)
    , revision_id_(0)
    , counter_selection_changed_(false)
    , pass_index_(0)
{
}

void GpaCounterSchedulerBase::Reset()
{
    DisableAllCounters();
    pass_index_                = 0;
    counter_accessor_          = nullptr;
    counter_selection_changed_ = false;
}

GpaStatus GpaCounterSchedulerBase::SetCounterAccessor(IGpaCounterAccessor* counter_accessor, GpaUInt32 vendor_id, GpaUInt32 device_id, GpaUInt32 revision_id)
{
    if (nullptr == counter_accessor)
    {
        GPA_LOG_ERROR("Parameter 'counter_accessor' is NULL.");
        return kGpaStatusErrorNullPointer;
    }

    counter_accessor_ = counter_accessor;
    vendor_id_        = vendor_id;
    device_id_        = device_id;
    revision_id_      = revision_id;

    // Make sure there are enough bits to track the enabled counters.
    enabled_public_counter_bits_.resize(counter_accessor->GetNumCounters());
    fill(enabled_public_counter_bits_.begin(), enabled_public_counter_bits_.end(), false);

    return kGpaStatusOk;
}

GpaUInt32 GpaCounterSchedulerBase::GetNumEnabledCounters() const
{
    return static_cast<GpaUInt32>(enabled_public_indices_.size());
}

GpaStatus GpaCounterSchedulerBase::EnableCounter(GpaUInt32 index)
{
// See if the counter is already enabled.
#pragma region Check using only enabled_public_indices_
//   for (gpa_uint32 i = 0; i < (gpa_uint32)enabled_public_indices_.size(); i++)
//   {
//      if (enabled_public_indices_[i] == index)
//      {
//         return kGpaStatusErrorAlreadyEnabled;
//      }
//   }
#pragma endregion
    if (enabled_public_counter_bits_[index])
    {
        std::stringstream message;
        message << "Counter index " << index << " has already been enabled.";

        // We will log this as a debug message rather than an error at this point,
        // this error will be reported to the logger from the caller.
        GPA_LOG_DEBUG_MESSAGE(message.str().c_str());
        return kGpaStatusErrorAlreadyEnabled;
    }

    enabled_public_indices_.push_back(index);
    enabled_public_counter_bits_[index] = true;
    counter_selection_changed_          = true;

    return kGpaStatusOk;
}

GpaStatus GpaCounterSchedulerBase::DisableCounter(GpaUInt32 index)
{
    // See if counter enabled.
    for (int i = 0; i < static_cast<int>(enabled_public_indices_.size()); i++)
    {
        if (enabled_public_indices_[i] == index)
        {
            enabled_public_indices_.erase(enabled_public_indices_.begin() + i);

            if (kGpaStatusOk == DoDisableCounter(index))
            {
                counter_selection_changed_ = true;
                return kGpaStatusOk;
            }
        }
    }

    std::stringstream message;
    message << "Counter index " << index << " was not previously enabled, so it could not be disabled.";
    GPA_LOG_ERROR(message.str().c_str());
    return kGpaStatusErrorNotEnabled;
}

void GpaCounterSchedulerBase::DisableAllCounters()
{
    pass_partitions_.clear();
    enabled_public_indices_.clear();
    fill(enabled_public_counter_bits_.begin(), enabled_public_counter_bits_.end(), false);
    counter_selection_changed_ = true;
}

GpaStatus GpaCounterSchedulerBase::GetEnabledIndex(GpaUInt32 enabled_index, GpaUInt32* counter_at_index) const
{
    if (enabled_index >= static_cast<GpaUInt32>(enabled_public_indices_.size()))
    {
        std::stringstream message;
        message << "Parameter 'enabledNumber' is " << enabled_index << " but must be less than the number of enabled counters ("
                << enabled_public_indices_.size() << ").";
        GPA_LOG_ERROR(message.str().c_str());
        return kGpaStatusErrorIndexOutOfRange;
    }

    (*counter_at_index) = static_cast<GpaUInt32>(enabled_public_indices_[enabled_index]);

    return kGpaStatusOk;
}

GpaStatus GpaCounterSchedulerBase::IsCounterEnabled(GpaUInt32 counter_index) const
{
    if (counter_index >= enabled_public_counter_bits_.size())
    {
        std::stringstream message;
        message << "Parameter 'counterIndex' is " << counter_index << " but must be less than the number of enabled counters ("
                << enabled_public_counter_bits_.size() << ").";
        GPA_LOG_ERROR(message.str().c_str());
        return kGpaStatusErrorIndexOutOfRange;
    }

    if (enabled_public_counter_bits_[counter_index])
    {
        return kGpaStatusOk;
    }
    else
    {
        std::stringstream message;
        message << "Parameter 'counter_index' (" << counter_index << ") is not an enabled counter.";
        GPA_LOG_MESSAGE(message.str().c_str());
        return kGpaStatusErrorCounterNotFound;
    }

#pragma region Previous method based on only using the enabled index list
#if 0
    GpaUInt32 count = 0;
    GpaStatus result = GpaGetEnabledCount(&count);

    if (result != kGpaStatusOk)
    {
        return result;
    }

    for (GpaUInt32 i = 0 ; i < count ; i++)
    {
        GpaUInt32 enabled_counter_index;
        result = GetEnabledIndex(i, &enabled_counter_index);

        if (result != kGpaStatusOk)
        {
            return result;
        }

        if (enabled_counter_index == counter_index)
        {
            return kGpaStatusOk;
        }
    }

#endif
#pragma endregion
}

GpaStatus GpaCounterSchedulerBase::GetNumRequiredPasses(GpaUInt32* num_required_passes_out)
{
    if (!counter_selection_changed_)
    {
        *num_required_passes_out = static_cast<GpaUInt32>(pass_partitions_.size());
        return kGpaStatusOk;
    }

    GpaCounterGeneratorBase* counter_generator_base = reinterpret_cast<GpaCounterGeneratorBase*>(counter_accessor_);

    if (nullptr == counter_generator_base)
    {
        return kGpaStatusErrorFailed;
    }

    const GpaHardwareCounters* hw_counters = counter_generator_base->GetHardwareCounters();

    unsigned int num_sq_max_counters = 0;

    GDT_DeviceInfo device_info = {};

    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(device_id_, revision_id_, device_info))
    {
        num_sq_max_counters = static_cast<unsigned int>(device_info.m_nNumSQMaxCounters);
    }

    IGpaSplitCounters* splitter = GpaSplitCounterFactory::GetNewCounterSplitter(GetPreferredSplittingAlgorithm(),
                                                                                hw_counters->timestamp_block_ids_,
                                                                                hw_counters->time_counter_indices_,
                                                                                num_sq_max_counters,
                                                                                hw_counters->sq_group_count_,
                                                                                hw_counters->sq_counter_groups_,
                                                                                hw_counters->isolated_group_count_,
                                                                                hw_counters->isolated_groups_);

    if (nullptr == splitter)
    {
        GPA_LOG_ERROR("Failed to create a counter splitting algorithm.");
        return kGpaStatusErrorFailed;
    }

    // Build the list of counters to split.
    std::vector<const GpaDerivedCounterInfoClass*> public_counters_to_split;
    std::vector<GpaHardwareCounterIndices>         internal_counters_to_schedule;
    std::vector<GpaSoftwareCounterIndices>         software_counters_to_schedule;

    for (std::vector<GpaUInt32>::const_iterator counter_iter = enabled_public_indices_.cbegin(); counter_iter != enabled_public_indices_.cend(); ++counter_iter)
    {
        GpaCounterSourceInfo info = counter_accessor_->GetCounterSourceInfo(*counter_iter);

        switch (info.counter_source)
        {
        case GpaCounterSource::kPublic:
        {
            public_counters_to_split.push_back(counter_accessor_->GetPublicCounter(*counter_iter));
            break;
        }

        case GpaCounterSource::kHardware:
        {
            // Hardware counter.
            std::vector<unsigned int> required_counters = counter_accessor_->GetInternalCountersRequired(*counter_iter);
            assert(required_counters.size() == 1);

            if (required_counters.size() == 1)
            {
                GpaHardwareCounterIndices indices = {};
                indices.public_index              = *counter_iter;
                indices.hardware_index            = required_counters[0];
                internal_counters_to_schedule.push_back(indices);
            }

            break;
        }

        case GpaCounterSource::kSoftware:
        {
            // Software counter.
            std::vector<unsigned int> required_counters = counter_accessor_->GetInternalCountersRequired(*counter_iter);
            assert(required_counters.size() == 1);

            if (required_counters.size() == 1)
            {
                GpaSoftwareCounterIndices indices = {};
                indices.public_index              = *counter_iter;

                indices.software_index = required_counters
                    [0];  // -pHWCounters->GetNumCounters(); // Subtract the number of HW counters to convert from the internal index to the software index.

                software_counters_to_schedule.push_back(indices);
            }

            break;
        }

        case GpaCounterSource::kUnknown:
        default:
        {
            // Do something sensible.
            GPA_LOG_ERROR("UNKNOWN_COUNTER.");
            return kGpaStatusErrorFailed;
        }
        }
    }

    // Get the Sw counters.
    const GpaSoftwareCounters* sw_counters = counter_generator_base->GetSoftwareCounters();

    // Build the list of max counters per group (includes both hardware and software groups).
    std::vector<unsigned int> max_counters_per_group;

    // Create space for the number of HW and SW groups.
    max_counters_per_group.reserve(hw_counters->group_count_ + hw_counters->additional_group_count_ + sw_counters->group_count_);

    // Add the HW groups max's.
    for (unsigned int i = 0; i < hw_counters->group_count_; ++i)
    {
        max_counters_per_group.push_back(hw_counters->internal_counter_groups_[i].max_active_discrete_counters);
    }

    // Add the Additional groups max's.
    for (unsigned int i = 0; i < hw_counters->additional_group_count_; ++i)
    {
        max_counters_per_group.push_back(hw_counters->additional_groups_[i].max_active_discrete_counters);
    }

    // TODO: properly handle software groups -- right now, this works because there is only ever a single group defined.
    if (sw_counters->group_count_ == 1)
    {
        max_counters_per_group.push_back(DoGetNumSoftwareCounters());
    }

    GpaCounterGroupAccessor accessor(
        hw_counters->internal_counter_groups_, hw_counters->group_count_, hw_counters->additional_groups_, hw_counters->additional_group_count_);

    unsigned int num_internal_counters_scheduled = 0;

    pass_partitions_ = splitter->SplitCounters(public_counters_to_split,
                                               internal_counters_to_schedule,
                                               software_counters_to_schedule,
                                               reinterpret_cast<IGpaCounterGroupAccessor*>(&accessor),
                                               max_counters_per_group,
                                               num_internal_counters_scheduled);

    counter_result_location_map_ = splitter->GetCounterResultLocations();

    delete splitter;
    splitter = nullptr;

    counter_selection_changed_ = false;
    *num_required_passes_out   = static_cast<GpaUInt32>(pass_partitions_.size());

    return kGpaStatusOk;
}

bool GpaCounterSchedulerBase::GetCounterSelectionChanged() const
{
    return counter_selection_changed_;
}

GpaStatus GpaCounterSchedulerBase::BeginProfile()
{
    pass_index_                = 0;
    counter_selection_changed_ = false;

    return DoBeginProfile();
}

void GpaCounterSchedulerBase::BeginPass()
{
    DoBeginPass();

    pass_index_++;
}

std::vector<unsigned int>* GpaCounterSchedulerBase::GetCountersForPass(GpaUInt32 pass_index)
{
    if (pass_index >= pass_partitions_.size())
    {
        return nullptr;
    }

    auto         iter = pass_partitions_.begin();
    unsigned int i    = 0;

    while (i < pass_index)
    {
        ++iter;
        i++;
    }

    return &(iter->pass_counter_list);
}

void GpaCounterSchedulerBase::EndPass()
{
    DoEndPass();
}

GpaStatus GpaCounterSchedulerBase::EndProfile()
{
    if (pass_index_ < pass_partitions_.size())
    {
        return kGpaStatusErrorNotEnoughPasses;
    }

    return DoEndProfile();
}

CounterResultLocationMap* GpaCounterSchedulerBase::GetCounterResultLocations(unsigned int public_counter_index)
{
    auto iter = counter_result_location_map_.find(public_counter_index);

    if (iter != counter_result_location_map_.end())
    {
        return &(iter->second);
    }

    return nullptr;
}

void GpaCounterSchedulerBase::SetDrawCallCounts(int internal_counts)
{
    DoSetDrawCallCounts(internal_counts);
}

GpaStatus GpaCounterSchedulerBase::DoDisableCounter(GpaUInt32 index)
{
    enabled_public_counter_bits_[index] = false;
    return kGpaStatusOk;
}

GpaUInt32 GpaCounterSchedulerBase::DoGetNumSoftwareCounters() const
{
    GpaUInt32 ret_val = 0;

    GpaCounterGeneratorBase* counter_generator_base = reinterpret_cast<GpaCounterGeneratorBase*>(counter_accessor_);

    if (nullptr != counter_generator_base)
    {
        const GpaSoftwareCounters* sw_counters = counter_generator_base->GetSoftwareCounters();

        if (nullptr != sw_counters)
        {
            ret_val = static_cast<GpaUInt32>(sw_counters->software_counter_list_.size());
        }
    }

    return ret_val;
}

GpaStatus GpaCounterSchedulerBase::DoBeginProfile()
{
    // Do nothing in base class.
    return kGpaStatusOk;
}

GpaStatus GpaCounterSchedulerBase::DoEndProfile()
{
    // Do nothing in base class.
    return kGpaStatusOk;
}

void GpaCounterSchedulerBase::DoBeginPass()
{
    // Do nothing in base class.
}

void GpaCounterSchedulerBase::DoEndPass()
{
    // Do nothing in base class.
}

void GpaCounterSchedulerBase::DoSetDrawCallCounts(int internal_count)
{
    UNREFERENCED_PARAMETER(internal_count);
    // Do nothing in base.
}
