//==============================================================================
// Copyright (c) 2016-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Counter splitter that puts one hardware counter per pass -- not used
///         in production, but can be useful for testing.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_ONE_PER_PASS_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_ONE_PER_PASS_H_

#include <vector>

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

/// @brief Splits counters such that each public counter is in its own pass (or multiple passes as needed).
///
/// In internal builds, the additional internal counters will also each go into their own pass.
class GpaSplitCountersOnePerPass : public IGpaSplitCounters
{
public:
    /// @brief Initializes a new instance of the GPASplitCountersOnePerPass class.
    ///
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] eop_time_counter_indices Set of End Of Pipeline timestamp counter indices.
    /// @param [in] top_time_counter_indices Set of Top Of Pipeline timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of counters that can be simultaneously enabled on the SQ block.
    /// @param [in] num_sq_blocks The number of SQ counter blocks.
    /// @param [in] sq_counter_block_info The list of SQ counter groups.
    /// @param [in] num_isolated_from_sq_groups The number of counter groups that must be isolated from SQ counter groups.
    /// @param [in] isolated_from_sq_groups The list of counter groups that must be isolated from SQ counter groups.
    GpaSplitCountersOnePerPass(const std::set<unsigned int>& timestamp_block_ids,
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
    virtual ~GpaSplitCountersOnePerPass(){};

    /// @brief Puts each public counter into its own pass (or set of passes) and each hardware counter into its own pass if not already scheduled.
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
                                            unsigned int&                                 num_scheduled_counters) override
    {
        // This will be the return value.
        std::list<GpaCounterPass> pass_partitions;

        // Make sure there are counters to schedule.
        if (public_counters_to_split.size() == 0 && internal_counters_to_schedule.size() == 0)
        {
            return pass_partitions;
        }

        // Temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> num_used_counters_per_pass_per_block;

        // Add initial pass partition and used counters per block.
        AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

        unsigned int                        pass_index        = 0;
        std::list<PerPassData>::iterator    counters_used_iter = num_used_counters_per_pass_per_block.begin();
        std::list<GpaCounterPass>::iterator counter_pass_iter  = pass_partitions.begin();

        // Iterate through each public counter.
        for (std::vector<const GpaDerivedCounterInfoClass*>::const_iterator public_iter = public_counters_to_split.begin();
             public_iter != public_counters_to_split.end();
             ++public_iter)
        {
            unsigned int initial_pass_for_this_pub_counter = pass_index;
            unsigned int current_pass_for_this_int_counter = pass_index;

            // Iterate through the internal counters and put them into the appropriate pass.
            for (const GpaUInt32 internal_counter : (*public_iter)->internal_counters_required_)
            {
                // Each internal counter should try to go into the first pass of this public counter.
                // Reset iterators...
                for (unsigned int i = current_pass_for_this_int_counter; i > initial_pass_for_this_pub_counter; --i)
                {
                    --counters_used_iter;
                    --counter_pass_iter;
                }

                // ... and reset current pass for this internal counter.
                current_pass_for_this_int_counter = initial_pass_for_this_pub_counter;

                bool done_allocating_counter = false;

                while (done_allocating_counter == false)
                {
                    accessor->SetCounterIndex(internal_counter);
                    unsigned int group_index = accessor->GroupIndex();

                    size_t counters_size = counter_pass_iter->pass_counter_list.size();

                    // Try to add the counter to the current pass.
                    if (counters_size == 0 ||
                        (CheckForTimestampCounters(accessor, *counter_pass_iter) && CanCounterBeAdded(accessor, *counters_used_iter, max_counters_per_group) &&
                         CheckForSQCounters(accessor, *counters_used_iter, max_sq_counters_) && CheckCountersAreCompatible(accessor, *counters_used_iter) &&
                         counters_size < 300))
                    {
                        counter_pass_iter->pass_counter_list.push_back(internal_counter);
                        counters_used_iter->num_used_counters_per_block[group_index].push_back(accessor->CounterIndex());
                        num_scheduled_counters += 1;
                        done_allocating_counter = true;

                        // Record where to get the result from.
                        AddCounterResultLocation((*public_iter)->counter_index_,
                                                 internal_counter,
                                                 current_pass_for_this_int_counter,
                                                 (unsigned int)counter_pass_iter->pass_counter_list.size() - 1);
                    }
                    else
                    {
                        // The counters needs to go into the next pass. Increment the pass index and let the loop happen again.
                        ++current_pass_for_this_int_counter;

                        if (current_pass_for_this_int_counter > pass_index)
                        {
                            ++pass_index;

                            AddNewPassInfo(pass_index + 1, &pass_partitions, &num_used_counters_per_pass_per_block);
                        }

                        ++counters_used_iter;
                        ++counter_pass_iter;
                    }
                }
            }

            if (public_iter != public_counters_to_split.end() - 1)
            {
                // Next counter will be in another pass.
                ++pass_index;

                GpaCounterPass counter_pass;
                pass_partitions.push_back(counter_pass);

                PerPassData new_pass;
                num_used_counters_per_pass_per_block.push_back(new_pass);

                // Point to the last item in this case so the next public counter can start at the pass just added.
                counters_used_iter = num_used_counters_per_pass_per_block.end();
                --counters_used_iter;
                counter_pass_iter = pass_partitions.end();
                --counter_pass_iter;
            }
        }

        InsertInternalCounters(pass_partitions, internal_counters_to_schedule, accessor, num_used_counters_per_pass_per_block, num_scheduled_counters);

        return pass_partitions;
    };

private:
    /// @brief Inserts each internal counter into a separate pass.
    ///
    /// @param [in,out] pass_partitions The pass partitions that are generated.
    /// @param [in] internal_counters The internal counters that need to be scheduled.
    /// @param [in] counter_accessor A interface that accesses the internal counters.
    /// @param [in] num_used_counters_per_pass_per_block A list of passes, each consisting of the number of counters scheduled on each block.
    /// @param [in,out] num_scheduled_counters The total number of internal counters that were scheduled.
    void InsertInternalCounters(std::list<GpaCounterPass>&                   pass_partitions,
                                const std::vector<GpaHardwareCounterIndices> internal_counters,
                                IGpaCounterGroupAccessor*                    counter_accessor,
                                std::list<PerPassData>                       num_used_counters_per_pass_per_block,
                                unsigned int&                                num_scheduled_counters)
    {
        if (internal_counters.size() == 0)
        {
            return;
        }

        // If there are no passes, then the first pass added below will be empty.
        // In this case, we have to special handle things further down.
        bool first_pass_empty = (num_scheduled_counters == 0);

        // Make sure there is room for the first pass.
        AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

        std::list<GpaCounterPass>::iterator current_pass_iter         = pass_partitions.end();
        std::list<PerPassData>::iterator    current_used_counters_iter = num_used_counters_per_pass_per_block.end();
        unsigned int                        pass_index               = (unsigned int)pass_partitions.size();

        // Back up the iterators so that they point to the last pass.
        --current_pass_iter;
        --current_used_counters_iter;

        // Schedule each of the internal counters in its own pass, unless it is already scheduled from one of the public counters.
        for (std::vector<GpaHardwareCounterIndices>::const_iterator internal_counter_iter = internal_counters.begin();
             internal_counter_iter != internal_counters.end();
             ++internal_counter_iter)
        {
            // If the counter is already scheduled in any pass, there is no reason to add it again.
            bool       counter_already_scheduled = false;
            GpaUInt16 search_pass_index         = 0;

            for (std::list<GpaCounterPass>::iterator tmp_pass_iter = pass_partitions.begin(); tmp_pass_iter != pass_partitions.end(); ++tmp_pass_iter)
            {
                int existing_offset = VectorContains<unsigned int>(tmp_pass_iter->pass_counter_list, internal_counter_iter->hardware_index);

                if (existing_offset >= 0)
                {
                    counter_already_scheduled = true;

                    // Record where to get the result from.
                    AddCounterResultLocation(internal_counter_iter->public_index, internal_counter_iter->hardware_index, search_pass_index, existing_offset);
                    break;
                }

                search_pass_index++;
            }

            if (counter_already_scheduled)
            {
                // Don't need to schedule this counter,
                // continue on to the next internal counter that needs to be scheduled.
                continue;
            }

            // The counter needs to be scheduled.
            // If the first pass is not empty, then skip over the addition of another pass for this current counter.
            if (first_pass_empty == false)
            {
                // Make sure there is enough space for the next pass.
                ++pass_index;
                AddNewPassInfo(pass_index, &pass_partitions, &num_used_counters_per_pass_per_block);
                ++current_pass_iter;
                ++current_used_counters_iter;
            }
            else
            {
                // The first counter is about to be scheduled in the pass, so
                // the pass will no longer be empty.
                first_pass_empty = false;
            }

            // The counter can be scheduled here.
            current_pass_iter->pass_counter_list.push_back(internal_counter_iter->hardware_index);

            current_used_counters_iter->num_used_counters_per_block[counter_accessor->GroupIndex()].push_back(counter_accessor->CounterIndex());
            num_scheduled_counters += 1;

            // Record where the result will be located.
            unsigned int offset = (unsigned int)current_pass_iter->pass_counter_list.size() - 1;
            AddCounterResultLocation(internal_counter_iter->public_index, internal_counter_iter->hardware_index, pass_index, offset);
        }
    }
};

#endif
