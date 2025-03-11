//==============================================================================
// Copyright (c) 2016-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Counter splitter that puts max number of hardware counter per pass
///         not used in production, but can be useful for testing.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_

#include <vector>

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

/// @brief Splits counters such that as many internal counters will be scheduled per pass as possible.
class GpaSplitCountersMaxPerPass : public IGpaSplitCounters
{
public:
    /// Initializes a new instance of the GPASplitCountersMaxPerPass class.
    ///
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] eop_time_counter_indices Set of End Of Pipeline timestamp counter indices.
    /// @param [in] top_time_counter_indices Set of Top Of Pipeline timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of counters that can be simultaneously enabled on the SQ block.
    /// @param [in] num_sq_groups The number of SQ counter groups.
    /// @param [in] sq_counter_block_info The list of SQ counter groups.
    /// @param [in] num_isolated_from_sq_groups The number of counter groups that must be isolated from SQ counter groups.
    /// @param [in] isolated_from_sq_groups The list of counter groups that must be isolated from SQ counter groups.
    GpaSplitCountersMaxPerPass(const std::set<unsigned int>& timestamp_block_ids,
                               const std::set<unsigned int>& eop_time_counter_indices,
                               const std::set<unsigned int>& top_time_counter_indices,
                               unsigned int                  max_sq_counters,
                               unsigned int                  num_sq_groups,
                               GpaSqCounterGroupDesc*        sq_counter_block_info,
                               unsigned int                  num_isolated_from_sq_groups,
                               const unsigned int*           isolated_from_sq_groups)
        : IGpaSplitCounters(timestamp_block_ids,
                            eop_time_counter_indices,
                            top_time_counter_indices,
                            max_sq_counters,
                            num_sq_groups,
                            sq_counter_block_info,
                            num_isolated_from_sq_groups,
                            isolated_from_sq_groups){};

    /// @brief Virtual destructor.
    virtual ~GpaSplitCountersMaxPerPass(){};

    /// @brief Puts as many counters in the first pass as will fit based on the maxCountersPerGroup, will expand to additional passes as required by the hardware.
    ///
    /// @param [in] public_counters_to_split The set of public counters that need to be split into passes.
    /// @param [in] internal_counters_to_schedule Additional internal counters that need to be scheduled (used by internal builds).
    /// @param [in] counter_group_accessor A class to access the internal counters.
    /// @param [in] max_counters_per_group The maximum number of counters that can be enabled in a single pass on each HW block or SW group.
    /// @param [out] num_scheduled_counters Indicates the total number of internal counters that were assigned to a pass.
    ///
    /// @return The list of passes that the counters are separated into.
    std::list<GpaCounterPass> SplitCounters(const std::vector<const GpaDerivedCounterInfoClass*>& public_counters_to_split,
                                            const std::vector<GpaHardwareCounterIndices>  internal_counters_to_schedule,
                                            IGpaCounterGroupAccessor*                     accessor,
                                            const std::vector<unsigned int>&              max_counters_per_group,
                                            unsigned int&                                 num_scheduled_counters)
    {
        // This will eventually be the return value.
        std::list<GpaCounterPass> pass_partitions;

        // Make sure there are counters to schedule.
        if (public_counters_to_split.size() == 0 && internal_counters_to_schedule.size() == 0)
        {
            return pass_partitions;
        }

        // Temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> num_used_counters_per_pass_per_block;

        // Add initial pass information
        AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

        // Will store the locations for each scheduled internal counter to help ensure that we don't duplicate any scheduling.
        std::map<unsigned int, GpaCounterResultLocation> internal_counter_result_locations;

        // Iterate through each public counter.
        for (std::vector<const GpaDerivedCounterInfoClass*>::const_iterator public_iter = public_counters_to_split.begin();
             public_iter != public_counters_to_split.end();
             ++public_iter)
        {
            // Iterate through the internal counters and put them into the appropriate pass (first available pass).
            for (std::vector<GpaUInt32>::const_iterator counter_iter = (*public_iter)->internal_counters_required_.begin();
                 counter_iter != (*public_iter)->internal_counters_required_.end();
                 ++counter_iter)
            {
                // See if the internal counter has already been scheduled.
                std::map<unsigned int, GpaCounterResultLocation>::iterator found_counter = internal_counter_result_locations.find(*counter_iter);

                if (found_counter != internal_counter_result_locations.end())
                {
                    // Counter has been scheduled.
                    // Use the same result location for this instance of the counter.
                    AddCounterResultLocation((*public_iter)->counter_index_, *counter_iter, found_counter->second.pass_index_, found_counter->second.offset_);
                }
                else
                {
                    // Counter has not been scheduled.
                    // So need to find a pass to put it in.
                    unsigned int                        pass_index        = 0;
                    std::list<PerPassData>::iterator    counters_used_iter = num_used_counters_per_pass_per_block.begin();
                    std::list<GpaCounterPass>::iterator counter_pass_iter  = pass_partitions.begin();

                    bool done_allocating_counter = false;

                    while (done_allocating_counter == false)
                    {
                        // Make sure there is a partition for current pass.
                        AddNewPassInfo(pass_index + 1, &pass_partitions, &num_used_counters_per_pass_per_block);

                        // Increment the pass iterator if past the first loop.
                        if (pass_index > 0)
                        {
                            ++counters_used_iter;
                            ++counter_pass_iter;
                        }

                        accessor->SetCounterIndex(*counter_iter);
                        unsigned int group_index = accessor->GroupIndex();

                        // Try to add the counter to the current pass.
                        if (CheckForTimestampCounters(accessor, *counter_pass_iter) && CanCounterBeAdded(accessor, *counters_used_iter, max_counters_per_group) &&
                            CheckForSQCounters(accessor, *counters_used_iter, max_sq_counters_) && CheckCountersAreCompatible(accessor, *counters_used_iter) &&
                            counter_pass_iter->pass_counter_list.size() < 300)
                        {
                            counter_pass_iter->pass_counter_list.push_back(*counter_iter);
                            counters_used_iter->num_used_counters_per_block[group_index].push_back(accessor->CounterIndex());
                            done_allocating_counter = true;

                            // Record where the internal counter was scheduled.
                            GpaCounterResultLocation location;
                            location.pass_index_                              = (GpaUInt16)pass_index;
                            location.offset_                            = (GpaUInt16)counter_pass_iter->pass_counter_list.size() - 1;
                            internal_counter_result_locations[*counter_iter] = location;

                            // Record where to get the result from
                            AddCounterResultLocation((*public_iter)->counter_index_, *counter_iter, location.pass_index_, location.offset_);
                        }
                        else
                        {
                            // The counters needs to go into the next pass. Increment the pass index and let the loop happen again.
                            ++pass_index;
                        }
                    }
                }
            }
        }

        // Set the number of scheduled internal counters.
        num_scheduled_counters = (unsigned int)internal_counter_result_locations.size();

        InsertHardwareCounters(pass_partitions, internal_counters_to_schedule, accessor, num_used_counters_per_pass_per_block, max_counters_per_group, num_scheduled_counters);

        return pass_partitions;
    }

private:
    /// @brief Inserts each hardware counter into the earliest possible pass.
    ///
    /// @param [in,out] pass_partitions The pass partitions that are generated.
    /// @param [in] internal_counters The internal counters that need to be scheduled.
    /// @param [in] accessor A interface that accesses the internal counters.
    /// @param [in] num_used_counters_per_pass_per_block A list of passes, each consisting of the number of counters scheduled on each block.
    /// @param [in] max_counters_per_group A vector containing the maximum number of simultaneous counters for each block.
    /// @param [in,out] num_scheduled_counters The total number of internal counters that were scheduled.
    void InsertHardwareCounters(std::list<GpaCounterPass>&                   pass_partitions,
                                const std::vector<GpaHardwareCounterIndices> internal_counters,
                                IGpaCounterGroupAccessor*                    accessor,
                                std::list<PerPassData>                       num_used_counters_per_pass_per_block,
                                const std::vector<unsigned int>&             max_counters_per_group,
                                unsigned int&                                num_scheduled_counters)
    {
        // Schedule each of the internal counters.
        for (std::vector<GpaHardwareCounterIndices>::const_iterator internal_counter_iter = internal_counters.begin();
             internal_counter_iter != internal_counters.end();
             ++internal_counter_iter)
        {
            // If the counter is already scheduled in any pass, there is no reason to add it again.
            bool         counter_already_scheduled = false;
            unsigned int pass_index               = 0;

            for (std::list<GpaCounterPass>::iterator pass_iter = pass_partitions.begin(); pass_iter != pass_partitions.end(); ++pass_iter)
            {
                int existing_offset = VectorContains<unsigned int>(pass_iter->pass_counter_list, internal_counter_iter->hardware_index);

                if (existing_offset >= 0)
                {
                    counter_already_scheduled = true;

                    // Record where to get the result from.
                    AddCounterResultLocation(internal_counter_iter->public_index, internal_counter_iter->hardware_index, pass_index, existing_offset);
                    break;
                }

                pass_index++;
            }

            if (counter_already_scheduled)
            {
                // Don't need to schedule this counter,
                // continue on to the next internal counter that needs to be scheduled.
                continue;
            }

            // The counter needs to be scheduled,
            // make sure there is enough space for the first pass.
            AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

            accessor->SetCounterIndex(internal_counter_iter->hardware_index);

            // Iterate through the passes again and find one where the counter can be inserted.
            pass_index                                         = 0;
            std::list<PerPassData>::iterator counters_used_iter = num_used_counters_per_pass_per_block.begin();

            for (std::list<GpaCounterPass>::iterator pass_iter = pass_partitions.begin(); pass_iter != pass_partitions.end(); ++pass_iter)
            {
                if (CheckForTimestampCounters(accessor, *pass_iter) == true && CanCounterBeAdded(accessor, *counters_used_iter, max_counters_per_group) == true &&
                    CheckForSQCounters(accessor, *counters_used_iter, max_sq_counters_) == true && CheckCountersAreCompatible(accessor, *counters_used_iter) == true)
                {
                    // The counter can be scheduled here.
                    pass_iter->pass_counter_list.push_back(internal_counter_iter->hardware_index);
                    counters_used_iter->num_used_counters_per_block[accessor->GroupIndex()].push_back(accessor->CounterIndex());
                    num_scheduled_counters += 1;

                    // Record where the result will be located.
                    unsigned int offset = (unsigned int)pass_iter->pass_counter_list.size() - 1;
                    AddCounterResultLocation(internal_counter_iter->public_index, internal_counter_iter->hardware_index, pass_index, offset);
                    break;
                }
                else
                {
                    ++pass_index;

                    // Make sure there is enough space for the next pass.
                    AddNewPassInfo(pass_index + 1, &pass_partitions, &num_used_counters_per_pass_per_block);

                    // Increment the iterator after any necessary new passes have been allocated.
                    ++counters_used_iter;
                }
            }
        }
    }
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_
