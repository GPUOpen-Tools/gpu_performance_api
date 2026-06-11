//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base Class for counter scheduling.
//==============================================================================

#include <list>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_group_accessor.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_consolidated.h"

GpaCounterSchedulerBase::GpaCounterSchedulerBase(GpaSessionSampleType sample_type)
    : sample_type_(sample_type)
{
}

void GpaCounterSchedulerBase::Reset()
{
    DisableAllCounters();
    pass_index_                = 0;
    counter_accessor_          = nullptr;
    counter_selection_changed_ = false;
}

GpaStatus GpaCounterSchedulerBase::SetCounterAccessor(IGpaCounterAccessor* counter_accessor, const GpaHwInfo& hw_info)
{
    if (nullptr == counter_accessor)
    {
        GpaLogger::Instance().LogError("Parameter 'counter_accessor' is NULL.");
        return kGpaStatusErrorNullPointer;
    }

    counter_accessor_ = counter_accessor;

    // We only need to get the device info that is relevant to counter scheduling, which is currently just the number of max SQ counters.
    num_sq_max_counters_ = hw_info.GetMaxSqCounters().value();

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
    if (index >= enabled_public_counter_bits_.size()) [[unlikely]]
    {
        return kGpaStatusErrorIndexOutOfRange;
    }

    if (enabled_public_counter_bits_[index]) [[unlikely]]
    {
        // We will log this as a debug message rather than an error at this point,
        // this error will be reported to the logger from the caller.
        GpaLogger::Instance().LogDebugMessage("Counter index {} has already been enabled.", index);
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

    GpaLogger::Instance().LogError("Counter index {} was not previously enabled, so it could not be disabled.", index);
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
        GpaLogger::Instance().LogError(
            "Parameter 'enabled_index' is {} but must be less than the number of enabled counters ({})", enabled_index, enabled_public_indices_.size());
        return kGpaStatusErrorIndexOutOfRange;
    }

    (*counter_at_index) = static_cast<GpaUInt32>(enabled_public_indices_[enabled_index]);

    return kGpaStatusOk;
}

GpaStatus GpaCounterSchedulerBase::IsCounterEnabled(GpaUInt32 counter_index) const
{
    if (counter_index >= enabled_public_counter_bits_.size())
    {
        GpaLogger::Instance().LogError(
            "Parameter 'counter_index' is {} but must be less than the number of enabled counters ({})", counter_index, enabled_public_counter_bits_.size());
        return kGpaStatusErrorIndexOutOfRange;
    }

    if (enabled_public_counter_bits_[counter_index])
    {
        return kGpaStatusOk;
    }
    else
    {
        GpaLogger::Instance().LogMessage("Parameter 'counter_index' ({}) is not an enabled counter.", counter_index);
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
    assert(num_required_passes_out != nullptr);
    if (num_required_passes_out == nullptr) [[unlikely]]
    {
        return kGpaStatusErrorNullPointer;
    }

    *num_required_passes_out = 0;

    // Calculating the number of required passes is a costly operation,
    // so if the counter selection hasn't changed since the last time we calculated it, we can just return the previously calculated value.
    if (!counter_selection_changed_)
    {
        assert(pass_partitions_.size() < std::numeric_limits<GpaUInt32>::max());
        *num_required_passes_out = static_cast<GpaUInt32>(pass_partitions_.size());
        return kGpaStatusOk;
    }

    GpaCounterGeneratorBase* counter_generator_base = reinterpret_cast<GpaCounterGeneratorBase*>(counter_accessor_);
    if (nullptr == counter_generator_base)
    {
        return kGpaStatusErrorFailed;
    }

    const GpaHardwareCounters& hw_counters = counter_generator_base->GetHardwareCounters();

    // Build the list of counters to split.
    std::vector<const GpaDerivedCounterInfoClass*> public_counters_to_split;
    public_counters_to_split.reserve(enabled_public_indices_.size());

    std::vector<GpaHardwareCounterIndices> internal_counters_to_schedule;
    internal_counters_to_schedule.reserve(enabled_public_indices_.size());

    for (const uint32_t index : enabled_public_indices_)
    {
        const GpaCounterSourceInfo info = counter_accessor_->GetCounterSourceInfo(index);

        switch (info.counter_source)
        {
        case GpaCounterSource::kPublic:
        {
            public_counters_to_split.push_back(counter_accessor_->GetPublicCounter(index));
            break;
        }
        case GpaCounterSource::kHardware:
        {
            constexpr uint32_t kCounterSourceHardware = static_cast<uint32_t>(GpaCounterSource::kHardware);
            const GpaUInt32    hardware_index         = std::get<kCounterSourceHardware>(counter_accessor_->GetInternalCountersRequired(index));

            internal_counters_to_schedule.push_back(GpaHardwareCounterIndices{.public_index = index, .hardware_index = hardware_index});

            break;
        }
        [[unlikely]] case GpaCounterSource::kUnknown:
            [[fallthrough]];
        [[unlikely]] default:
        {
            GpaLogger::Instance().LogError("Counter index {} has an unknown source, cannot be scheduled.", index);
            return kGpaStatusErrorFailed;
        }
        }
    }

    // Build the list of max counters per group (includes both hardware and software groups).
    std::vector<uint32_t> max_counters_per_group;

    // Create space for the number of HW groups.
    max_counters_per_group.reserve(hw_counters.internal_counter_groups_.size() + hw_counters.additional_group_count_);

    std::unique_ptr<IGpaSplitCounters> splitter;

    // Set max events
    switch (sample_type_)
    {
    case kGpaSessionSampleTypeDiscreteCounter:
    {
        // Add the HW groups maxes.
        const unsigned int num_groups = static_cast<unsigned int>(hw_counters.internal_counter_groups_.size());
        for (unsigned int i = 0; i < num_groups; ++i)
        {
            auto count = hw_counters.internal_counter_groups_[i].max_active_discrete_counters;
            if (count == 0)
            {
                GpaLogger::Instance().LogMessage(
                    "Caution: Hardware counter group '{}' has zero for max_active_discrete_counters. This hardware block is not available for profiling.",
                    hw_counters.internal_counter_groups_[i].name);
            }
            max_counters_per_group.push_back(count);
        }

        // Add the additional groups maxes.
        for (unsigned int i = 0; i < hw_counters.additional_group_count_; ++i)
        {
            auto count = hw_counters.additional_groups_[i].max_active_discrete_counters;
            if (count == 0)
            {
                GpaLogger::Instance().LogMessage(
                    "Caution: Hardware counter additional group '{}' has zero for max_active_discrete_counters. This hardware block is not available for "
                    "profiling.",
                    hw_counters.additional_groups_[i].name);
            }
            max_counters_per_group.push_back(count);
        }

        splitter = std::make_unique<GpaSplitCountersConsolidated<kGpaSessionSampleTypeDiscreteCounter>>(
            hw_counters.timestamp_block_ids_,
            hw_counters.eop_time_counter_indices_,
            hw_counters.top_time_counter_indices_,
            num_sq_max_counters_,
            std::span(hw_counters.sq_counter_groups_, hw_counters.sq_group_count_),
            std::span(hw_counters.isolated_groups_, hw_counters.isolated_group_count_));

        break;
    }
    case kGpaSessionSampleTypeStreamingCounter:
    {
        // Add the HW groups max's.
        const unsigned int num_groups = static_cast<unsigned int>(hw_counters.internal_counter_groups_.size());
        for (unsigned int i = 0; i < num_groups; ++i)
        {
            auto count = hw_counters.internal_counter_groups_[i].max_active_spm_counters;
            max_counters_per_group.push_back(count);
        }

        // Add the Additional groups max's.
        for (unsigned int i = 0; i < hw_counters.additional_group_count_; ++i)
        {
            auto count = hw_counters.additional_groups_[i].max_active_spm_counters;
            max_counters_per_group.push_back(count);
        }

        splitter = std::make_unique<GpaSplitCountersConsolidated<kGpaSessionSampleTypeStreamingCounter>>(
            hw_counters.timestamp_block_ids_,
            hw_counters.eop_time_counter_indices_,
            hw_counters.top_time_counter_indices_,
            num_sq_max_counters_,
            std::span(hw_counters.sq_counter_groups_, hw_counters.sq_group_count_),
            std::span(hw_counters.isolated_groups_, hw_counters.isolated_group_count_));

        break;
    }
    [[unlikely]] case kGpaSessionSampleTypeSqtt:
        [[fallthrough]];
    [[unlikely]] case kGpaSessionSampleTypeStreamingCounterAndSqtt:
        [[fallthrough]];
    [[unlikely]] case kGpaSessionSampleTypeLast:
        [[fallthrough]];
    default:
    {
        GpaLogger::Instance().LogError("Invalid counter scheduler sample type.");
        return kGpaStatusErrorFailed;
    }
    }

    const auto additional_groups_span = std::span(hw_counters.additional_groups_, hw_counters.additional_group_count_);

    GpaCounterGroupAccessor accessor(hw_counters.internal_counter_groups_, additional_groups_span);

    const GpaStatus split_status =
        splitter->SplitCounters(public_counters_to_split, internal_counters_to_schedule, &accessor, max_counters_per_group, pass_partitions_);

    if (split_status == kGpaStatusOk) [[likely]]
    {
        splitter->SwapCounterResultLocations(counter_result_location_map_);

        counter_selection_changed_ = false;

        assert(pass_partitions_.size() < std::numeric_limits<GpaUInt32>::max());
        *num_required_passes_out = static_cast<GpaUInt32>(pass_partitions_.size());
    }

    return split_status;
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
