//==============================================================================
// Copyright (c) 2014-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief This file implements the "consolidated" counter splitter.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_CONSOLIDATED_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_CONSOLIDATED_H_

#if defined(WIN32)
#include <Windows.h>
#endif  // WIN32

#include <vector>
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
#include <sstream>
#endif

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

/// @brief Splits counters such that no individual public counter will be split into any more passes than minimally required.
///
/// This is done by splitting the public counter on its own, and then finding a set of passes that allows each of the public counter's
/// passes to be scheduled.
class GpaSplitCountersConsolidated : public IGpaSplitCounters
{
public:
    /// @brief Initialize an instance of the GPASplitCountersConsolidated class.
    ///
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] time_counter_indices Set of timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of counters that can be simultaneously enabled on the SQ block.
    /// @param [in] num_sq_groups The number of SQ counter groups.
    /// @param [in] sq_counter_block_info The list of SQ counter groups.
    /// @param [in] num_isolated_from_sq_groups The number of counter groups that must be isolated from SQ counter groups.
    /// @param [in] isolated_from_sq_groups The list of counter groups that must be isolated from SQ counter groups.
    GpaSplitCountersConsolidated(const std::set<unsigned int>& timestamp_block_ids,
                               const std::set<unsigned int>& time_counter_indices,
                               unsigned int                  max_sq_counters,
                               unsigned int                  num_sq_groups,
                               GpaSqCounterGroupDesc*        sq_counter_block_info,
                               unsigned int                  num_isolated_from_sq_groups,
                               const unsigned int*           isolated_from_sq_groups)
        : IGpaSplitCounters(timestamp_block_ids,
                            time_counter_indices,
                            max_sq_counters,
                            num_sq_groups,
                            sq_counter_block_info,
                            num_isolated_from_sq_groups,
                            isolated_from_sq_groups){};

    /// @brief Virtual destructor.
    virtual ~GpaSplitCountersConsolidated(){};

    /// @brief Splits the counters according to the consolidated approach.
    ///
    /// Public counters that can fit in a single pass will be enabled in the same pass,
    /// single-pass counters should not be split into multiple passes,
    /// multi-pass counters should not take more passes than required,
    /// no more than a fixed number of counters per pass.
    ///
    /// @param [in] public_counters_to_split The set of public counters that need to be split into passes.
    /// @param [in] internal_counters_to_schedule Additional internal counters that need to be scheduled (used by internal builds).
    /// @param [in] counter_group_accessor A class to access the internal counters.
    /// @param [in] max_counters_per_group The maximum number of counters that can be enabled in a single pass on each HW block or SW group.
    /// @param [out] num_scheduled_counters Indicates the total number of internal counters that were assigned to a pass.
    ///
    /// @return The list of passes that the counters are separated into.
    std::list<GpaCounterPass> SplitCounters(const std::vector<const GpaDerivedCounterInfoClass*>& public_counters_to_split,
                                            const std::vector<GpaHardwareCounterIndices>          internal_counters_to_schedule,
                                            IGpaCounterGroupAccessor*                             accessor,
                                            const std::vector<unsigned int>&                      max_counters_per_group,
                                            unsigned int&                                         num_scheduled_counters) override
    {
        // The maximum number of internal counters to enable in a single pass. This may be updated if any of the public counters require more than this value
        // to be enabled in a single pass, otherwise the algorithm would get stuck in an infinite loop trying to find a viable pass for the public counter.
        // Adjusting this value makes a big difference in the number of passes that will be generated. Currently a very low value (2) will results in 39 passes.
        // A high value (~180) will result in 17 passes; lowering down to 120 still results in 17 passes, but the actual counters in each pass are slightly changed.
        // Other values I tried: 40=33 passes, 50=28 passes, 60=24 passes, 100=19passes, 120+ = 17 passes.
        const uint32_t max_internal_counters_per_pass = 120;

        // This will eventually be the return value.
        std::list<GpaCounterPass> pass_partitions;

        // Temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> num_used_counters_per_pass_per_block;

        // Handle the public counters.
        InsertPublicCounters(pass_partitions,
                             public_counters_to_split,
                             accessor,
                             num_used_counters_per_pass_per_block,
                             max_counters_per_group,
                             num_scheduled_counters,
                             max_internal_counters_per_pass);

        // Handle the internal counters.
        InsertHardwareCounters(
            pass_partitions, internal_counters_to_schedule, accessor, num_used_counters_per_pass_per_block, max_counters_per_group, num_scheduled_counters);

        return pass_partitions;
    }

private:
    /// @brief Structure representing a point to the requested GPA_PublicCounter, and the breakdown of hardware counter passes.
    struct PublicAndHardwareCounters
    {
        const GpaDerivedCounterInfoClass* public_counter = nullptr;  ///< The public counter.
        GpaCounterPass                    counter_pass;              ///< The set of hardware counters in a pass.
        uint32_t                          pass_index   = 0;          ///< The pass index.
        uint32_t                          total_passes = 0;          ///< The total passes required for the public counter.
    };

    /// @brief Checks passes created for previous public counters to see if the counters in the specified pass are already all scheduled in the same pass.
    ///
    /// If they are, then we can reuse that pass rather than creating a new pass for the current counter.
    ///
    /// @param [in] pass_partitions The list of passes created for all previously scheduled public counters.
    /// @param [in] pass The pass whose counters we are checking to see if they are all already scheduled in a single pass.
    /// @param [out] pass_index If the specified pass' counters are already scheduled, this will contain the pass index where they are scheduled.
    ///
    /// @return True if the specified pass' counters are already scheduled in a single pass, false otherwise.
    bool CheckAllCountersScheduledInSamePass(std::list<GpaCounterPass>& pass_partitions, const GpaCounterPass& pass, unsigned int* pass_index)
    {
        bool ret_val = false;

        if (!pass_index)
        {
            assert(0);
            return false;
        }

        *pass_index = 0;

        for (auto iterator = pass_partitions.cbegin(); iterator != pass_partitions.cend(); ++iterator, (*pass_index)++)
        {
            if (iterator->pass_counter_list.size() < pass.pass_counter_list.size())
            {
                // Current pass has fewer counters than pass to be scheduled.
                continue;
            }

            // For each pre-existing pass, see if the current pass' counters are already scheduled.
            bool all_counters_in_same_pass = true;

            for (auto pass_iter = pass.pass_counter_list.cbegin(); pass_iter != pass.pass_counter_list.cend(); ++pass_iter)
            {
                if (VectorContains<unsigned int>(iterator->pass_counter_list, *pass_iter) == -1)
                {
                    all_counters_in_same_pass = false;
                    break;
                }
            }

            if (all_counters_in_same_pass)
            {
                ret_val = true;
                break;
            }
        }

        return ret_val;
    }

    /// @brief Determines which pass to schedule hardware counters in.
    ///
    /// @param [in] counter_accessor The counter accessor for the counter.
    /// @param [in] single_counter_pass Calculated pass and hardware counter data required for the public counter.
    /// @param [in] max_internal_counters_per_pass The maximum number of counters per pass.
    /// @param [in] start_counter_pass_index Pass index the scheduling is starting from.
    /// @param [in] num_used_counters_per_pass_per_block A list of passes, each consisting of the number of counters scheduled on each block.
    /// @param [in] max_counters_per_group A vector containing the maximum number of simultaneous counters for each block.
    /// @param [in] existing_passes Mapping is used when setting up the results slots for the current counter.
    /// @param [in] counters_used_iter Current pass block.
    /// @param [in] dest_counter_pass_iter Destination pass.
    /// @param [in] pass_partitions The pass partitions that are generated.
    void ScheduleCounters(IGpaCounterGroupAccessor*             counter_accessor,
                          const GpaCounterPass&                 single_counter_pass,
                          uint32_t*                             max_internal_counters_per_pass,
                          uint32_t*                             start_counter_pass_index,
                          std::list<PerPassData>*               num_used_counters_per_pass_per_block,
                          const std::vector<unsigned int>&      max_counters_per_group,
                          std::map<unsigned int, unsigned int>* existing_passes,
                          std::list<PerPassData>::iterator*     counters_used_iter,
                          std::list<GpaCounterPass>::iterator*  dest_counter_pass_iter,
                          std::list<GpaCounterPass>*            pass_partitions)
    {
        if (!counter_accessor || !max_internal_counters_per_pass || !start_counter_pass_index || !num_used_counters_per_pass_per_block || !existing_passes ||
            !counters_used_iter || !dest_counter_pass_iter || !pass_partitions)
        {
            assert(0);
            return;
        }

        existing_passes->clear();

        // Loop until we find a good pass to put the counter in.
        while (1)
        {
            // These variables keep track of which pass within the single counter is currently being evaluated.
            unsigned int single_counter_pass_index = 0;
            auto         tmp_counters_used_iter    = counters_used_iter;
            auto         tmp_counter_pass_iter     = dest_counter_pass_iter;

            {
                unsigned int pass_index = 0;

                if (CheckAllCountersScheduledInSamePass(*pass_partitions, single_counter_pass, &pass_index))
                {
                    (*existing_passes)[0] = pass_index;
                    return;
                }
            }

            // Update the max number of internal counters allowed per pass to ensure that this singleCounterPass will have a chance of fitting.
            *max_internal_counters_per_pass = std::max(*max_internal_counters_per_pass, static_cast<uint32_t>(single_counter_pass.pass_counter_list.size()));

            // Make sure there is enough space for the next pass.
            AddNewPassInfo(single_counter_pass_index + *start_counter_pass_index + 1, pass_partitions, num_used_counters_per_pass_per_block);

            if (single_counter_pass_index > 0)
            {
                ++(*tmp_counters_used_iter);
                ++(*tmp_counter_pass_iter);
            }

            // Limit the pass to a maximum number of counters.
            bool all_passes_are_good = true;

            if ((*tmp_counter_pass_iter)->pass_counter_list.size() + single_counter_pass.pass_counter_list.size() > *max_internal_counters_per_pass)
            {
                all_passes_are_good = false;
            }
            else
            {
                // Local temp copy of the current pass info so that internal counters can be properly tracked for our 'testing' of the counters.
                PerPassData tmp_cur_counters_used = **tmp_counters_used_iter;

                // Test each internal counter to see if they can all fit in the current consolidated passes.
                for (auto internal_counter_iter = single_counter_pass.pass_counter_list.cbegin();
                     internal_counter_iter != single_counter_pass.pass_counter_list.cend();
                     ++internal_counter_iter)
                {
                    // If the counter is already there, no need to add it.
                    if (VectorContains<unsigned int>((*tmp_counter_pass_iter)->pass_counter_list, *internal_counter_iter) == -1)
                    {
                        // Check to see if the counter can be added.
                        counter_accessor->SetCounterIndex(*internal_counter_iter);
                        unsigned int group_index = counter_accessor->GroupIndex();

                        if (CheckForTimestampCounters(counter_accessor, **tmp_counter_pass_iter) == false ||  // Use tmpCounterPassIter.
                            CanCounterBeAdded(counter_accessor, tmp_cur_counters_used, max_counters_per_group) == false ||
                            CheckForSQCounters(counter_accessor, tmp_cur_counters_used, max_sq_counters_) == false ||
                            CheckCountersAreCompatible(counter_accessor, tmp_cur_counters_used) == false)
                        {
                            all_passes_are_good = false;
                            break;
                        }
                        else
                        {
                            // Track that the internal counters was 'scheduled'.
                            tmp_cur_counters_used.num_used_counters_per_block[group_index].push_back(counter_accessor->CounterIndex());
                        }
                    }
                }
            }

            if (all_passes_are_good)
            {
                return;
            }

            // The necessary passes for the single public counter did not fit with the previously scheduled counters.
            // Update iterators to try the next pass.
            // Iterate to the next pass and see if the counters are better here.
            ++single_counter_pass_index;
            AddNewPassInfo(single_counter_pass_index + *start_counter_pass_index + 1, pass_partitions, num_used_counters_per_pass_per_block);
            ++(*counters_used_iter);
            ++(*dest_counter_pass_iter);

            // The counter could not get scheduled starting from the current passIndex,
            // so continue and try the next one.
            ++(*start_counter_pass_index);
        }
    }

    /// @brief Schedules the hardware counters on the specified pass.
    ///
    /// @param [in] counter_accessor The counter accessor for the counter.
    /// @param [in] hardware_counters Current hardware counters for public counter.
    /// @param [in] num_scheduled_counters Number of counters that were scheduled.
    /// @param [in] single_counter_pass Calculated pass and hardware counter data required for the public counter.
    /// @param [in] start_counter_pass_index Pass index the scheduling is starting from.
    /// @param [in] existing_passes Mapping is used when setting up the results slots for the current counter.
    /// @param [in] counters_used_iter Current pass block.
    /// @param [in] dest_counter_pass_iter Destination pass.
    /// @param [in] pass_partitions The pass partitions that are generated.
    void AddCountersToPass(IGpaCounterGroupAccessor*             counter_accessor,
                           const PublicAndHardwareCounters*      hardware_counters,
                           unsigned int*                         num_scheduled_counters,
                           const GpaCounterPass&                 single_counter_pass,
                           uint32_t*                             start_counter_pass_index,
                           std::map<unsigned int, unsigned int>* existing_passes,
                           std::list<PerPassData>::iterator*     counters_used_iter,
                           std::list<GpaCounterPass>::iterator*  dest_counter_pass_iter,
                           std::list<GpaCounterPass>*            pass_partitions)
    {
        if (!counter_accessor || !hardware_counters || !num_scheduled_counters || !start_counter_pass_index || !existing_passes || !counters_used_iter ||
            !dest_counter_pass_iter || !pass_partitions)
        {
            assert(0);
            return;
        }

        // Add the counter to the found pass.
        // Iterate through all the internal counters and add them to the appropriate passes.
        unsigned int single_pass_index = 0;

        // Check if the existingPasses mapping contains this pass -- if so, then we have to use the counter result location already added to the counter_result_location_map_ member.
        if (existing_passes->find(single_pass_index) != existing_passes->cend())
        {
            uint32_t pass_index = (*existing_passes)[single_pass_index];

            for (auto internal_counter_iter = single_counter_pass.pass_counter_list.cbegin();
                 internal_counter_iter != single_counter_pass.pass_counter_list.cend();
                 ++internal_counter_iter)
            {
                auto it = pass_partitions->cbegin();

                for (uint32_t cur_pass = 0; it != pass_partitions->cend(); ++it, cur_pass++)
                {
                    if (cur_pass == pass_index)
                    {
                        break;
                    }
                }

                // We don't expect this to fail since we found these counters in "existing_passes".
                int existing_index = VectorContains<unsigned int>(it->pass_counter_list, *internal_counter_iter);
                assert(-1 != existing_index);

                AddCounterResultLocation(hardware_counters->public_counter->counter_index_, *internal_counter_iter, pass_index, existing_index);
            }
        }
        else
        {
            uint32_t pass_index = *start_counter_pass_index;

            for (auto internal_counter_iter = single_counter_pass.pass_counter_list.cbegin();
                 internal_counter_iter != single_counter_pass.pass_counter_list.cend();
                 ++internal_counter_iter)
            {
                // Only add the counter if it is not already there.
                int existing_index = VectorContains<unsigned int>((*dest_counter_pass_iter)->pass_counter_list, *internal_counter_iter);

                if (existing_index == -1)
                {
                    counter_accessor->SetCounterIndex(*internal_counter_iter);
                    (*dest_counter_pass_iter)->pass_counter_list.push_back(*internal_counter_iter);
                    (*counters_used_iter)->num_used_counters_per_block[counter_accessor->GroupIndex()].push_back(counter_accessor->CounterIndex());
                    *num_scheduled_counters += 1;

                    unsigned int offset = static_cast<unsigned int>((*dest_counter_pass_iter)->pass_counter_list.size()) - 1;

                    // Find the correct pass that the counter was added to.
                    pass_index = 0;

                    for (auto itt = pass_partitions->begin(); itt != pass_partitions->end() && itt != *dest_counter_pass_iter; ++itt)
                    {
                        ++pass_index;
                    }

                    AddCounterResultLocation(hardware_counters->public_counter->counter_index_, *internal_counter_iter, pass_index, offset);
                }
                else
                {
                    unsigned int offset = static_cast<unsigned int>(existing_index);
                    AddCounterResultLocation(hardware_counters->public_counter->counter_index_, *internal_counter_iter, pass_index, offset);
                }
            }

            // Increment to the next pass if we added any counters to this pass.
            ++(*dest_counter_pass_iter);
            ++(*counters_used_iter);
        }
    }

    /// @brief Inserts each public counter into the earliest possible pass.
    ///
    /// @param [in,out] pass_partitions The pass partitions that are generated.
    /// @param [in] input_counters_to_split The incoming counters we need to split.
    /// @param [in] counter_accessor A interface that accesses the public counters.
    /// @param [in] num_used_counters_per_pass_per_block A list of passes, each consisting of the number of counters scheduled on each block.
    /// @param [in] max_counters_per_group A vector containing the maximum number of simultaneous counters for each block.
    /// @param [in,out] num_scheduled_counters The total number of counters that were scheduled.
    /// @param [in] max_internal_counters_per_pass The maximum number of counters per pass.
    void InsertPublicCounters(std::list<GpaCounterPass>&                            pass_partitions,
                              const std::vector<const GpaDerivedCounterInfoClass*>& input_counters_to_split,
                              IGpaCounterGroupAccessor*                             counter_accessor,
                              std::list<PerPassData>&                               num_used_counters_per_pass_per_block,
                              const std::vector<unsigned int>&                      max_counters_per_group,
                              unsigned int&                                         num_scheduled_counters,
                              unsigned int                                          max_internal_counters_per_pass)
    {
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        std::stringstream ss;
#endif

        std::vector<PublicAndHardwareCounters> public_counters;

        // Determine number of hardware counters per public counter.
        // Because SplitSingleCounter has split the counter across 1 or more passes, we can treat each pass independently.
        // As a safety check, the internal logic in ScheduleCounters also calls the Check* functions to validate scheduling.
        for (auto public_iter = input_counters_to_split.cbegin(); public_iter != input_counters_to_split.cend(); ++public_iter)
        {
            std::list<GpaCounterPass> counter_passes = SplitSingleCounter(*public_iter, counter_accessor, max_counters_per_group);

            uint32_t pass_index = 1;

            for (auto iter_pass = counter_passes.begin(); iter_pass != counter_passes.end(); ++iter_pass, ++pass_index)
            {
                PublicAndHardwareCounters public_counter;
                public_counter.public_counter = *public_iter;
                public_counter.pass_index     = pass_index;
                public_counter.total_passes   = static_cast<uint32_t>(counter_passes.size());
                public_counter.counter_pass   = std::move(*iter_pass);
                public_counters.push_back(std::move(public_counter));
            }
        }

        // Sort by descending number of hardware counters per pass.
        // If we have 2 sets of hardware counters, one of which is a subset of the other, it will allow us to schedule them on the same pass.
        std::sort(public_counters.begin(), public_counters.end(), [](const PublicAndHardwareCounters& a, const PublicAndHardwareCounters& b) {
            return a.counter_pass.pass_counter_list.size() > b.counter_pass.pass_counter_list.size();
        });

        // Iterate through each public counter.
        for (auto public_iter = public_counters.cbegin(); public_iter != public_counters.cend(); ++public_iter)
        {
            // Scheduling the counter is an iterative process, and this variable will keep track of which pass index the scheduling is starting from.
            unsigned int start_counter_pass_index = 0;

            // Make sure there is enough space for the next pass.
            AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

            // Reset the iterators to the beginning each time we are trying to schedule a different public counter.
            auto counters_used_iter     = num_used_counters_per_pass_per_block.begin();
            auto dest_counter_pass_iter = pass_partitions.begin();

            // Retrieve the previously calculated pass and hardware counter data required for the public counter
            const GpaCounterPass& single_counter_pass = public_iter->counter_pass;

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
            ss.str("");
            ss << "Splitting Counter: " << public_iter->public_counter->counter_name_ << ". counterIndex: " << public_iter->public_counter->counter_index_
               << " pass: " << public_iter->pass_index << " of " << public_iter->total_passes;
            GPA_LOG_DEBUG_COUNTER_DEFS(ss.str().c_str());
#endif

            /// Contains a map between the pass index for a single split public counter and the pass index
            /// for a previously scheduled pass that contains all of the hw counters for that pass.
            /// For example, consider if counter XX can be split into 3 passes, and previously scheduled counters have been scheduled over 5 passes.
            /// If out of those five passes, pass 0, 4, and 5 already contain the counters from the single counter's pass 0, 1, and 2 respectively,
            /// then this map will contain:
            ///   0 = 0
            ///   1 = 4
            ///   2 = 5
            /// This mapping is used later when setting up the results slots for the current counter.
            std::map<unsigned int, unsigned int> existing_passes;

            ScheduleCounters(counter_accessor,
                             single_counter_pass,
                             &max_internal_counters_per_pass,
                             &start_counter_pass_index,
                             &num_used_counters_per_pass_per_block,
                             max_counters_per_group,
                             &existing_passes,
                             &counters_used_iter,
                             &dest_counter_pass_iter,
                             &pass_partitions);

            AddCountersToPass(counter_accessor,
                              &*public_iter,
                              &num_scheduled_counters,
                              single_counter_pass,
                              &start_counter_pass_index,
                              &existing_passes,
                              &counters_used_iter,
                              &dest_counter_pass_iter,
                              &pass_partitions);
        }

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        ss.str("");
        ss << "total passes: " << pass_partitions.size();
        GPA_LOG_DEBUG_COUNTER_DEFS(ss.str().c_str());

        for (auto it : pass_partitions)
        {
            ss.str("*****PASS*****");
            GPA_LOG_DEBUG_COUNTER_DEFS(ss.str().c_str());

            for (auto it1 : it.pass_counter_list)
            {
                ss.str("");
                ss << it1;
                GPA_LOG_DEBUG_COUNTER_DEFS(ss.str().c_str());
            }
        }

#endif
    }

    /// @brief Inserts each hardware counter into the earliest possible pass.
    ///
    /// NOTE: This could potentially do some load balancing by preferring passes with fewer counters in them.
    ///
    /// @param [in,out] pass_partitions The pass partitions that are generated.
    /// @param [in] internal_counters The internal counters that need to be scheduled.
    /// @param [in] counter_accessor A interface that accesses the internal counters.
    /// @param [in] num_used_counters_per_pass_per_block A list of passes, each consisting of the number of counters scheduled on each block.
    /// @param [in] max_counters_per_group A vector containing the maximum number of simultaneous counters for each block.
    /// @param [in,out] num_scheduled_counters The total number of internal counters that were scheduled.
    void InsertHardwareCounters(std::list<GpaCounterPass>&                   pass_partitions,
                                const std::vector<GpaHardwareCounterIndices> internal_counters,
                                IGpaCounterGroupAccessor*                    counter_accessor,
                                std::list<PerPassData>&                      num_used_counters_per_pass_per_block,
                                const std::vector<unsigned int>&             max_counters_per_group,
                                unsigned int&                                num_scheduled_counters)
    {
        // Schedule each of the internal counters.
        for (auto internal_counter_iter = internal_counters.cbegin(); internal_counter_iter != internal_counters.cend(); ++internal_counter_iter)
        {
            // If the counter is already scheduled in any pass, there is no reason to add it again.
            bool         counter_already_scheduled = false;
            unsigned int pass_index                = 0;

            for (auto pass_iter = pass_partitions.cbegin(); pass_iter != pass_partitions.cend(); ++pass_iter)
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

            // The counter needs to be scheduled.
            // Make sure there is enough space for the first pass.
            AddNewPassInfo(1, &pass_partitions, &num_used_counters_per_pass_per_block);

            counter_accessor->SetCounterIndex(internal_counter_iter->hardware_index);

            // Iterate through the passes again and find one where the counter can be inserted.
            pass_index              = 0;
            auto counters_used_iter = num_used_counters_per_pass_per_block.begin();

            for (auto pass_iter = pass_partitions.begin(); pass_iter != pass_partitions.end(); ++pass_iter)
            {
                if (CheckForTimestampCounters(counter_accessor, *pass_iter) == true &&
                    CanCounterBeAdded(counter_accessor, *counters_used_iter, max_counters_per_group) == true &&
                    CheckForSQCounters(counter_accessor, *counters_used_iter, max_sq_counters_) == true &&
                    CheckCountersAreCompatible(counter_accessor, *counters_used_iter) == true)
                {
                    // The counter can be scheduled here.
                    pass_iter->pass_counter_list.push_back(internal_counter_iter->hardware_index);
                    counters_used_iter->num_used_counters_per_block[counter_accessor->GroupIndex()].push_back(counter_accessor->CounterIndex());
                    num_scheduled_counters += 1;

                    // Record where the result will be located.
                    unsigned int offset = static_cast<unsigned int>(pass_iter->pass_counter_list.size()) - 1;
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

    /// @brief Separate a single counter into multiple passes based on the maxCountersPerGroup.
    ///
    /// @param [in] public_counter The counter that needs to be split.
    /// @param [in] counter_accessor The counter accessor for the counter.
    /// @param [in] max_counters_per_group The list of max counters per group.
    ///
    /// @return A list of passes.
    std::list<GpaCounterPass> SplitSingleCounter(const GpaDerivedCounterInfoClass* public_counter,
                                                 IGpaCounterGroupAccessor*         counter_accessor,
                                                 const std::vector<unsigned int>&  max_counters_per_group)
    {
        // This will eventually be the return value.
        std::list<GpaCounterPass> pass_partitions;
        GpaCounterPass            counter_pass;
        pass_partitions.push_back(counter_pass);

        // Temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> num_used_counters_per_pass_per_block;
        PerPassData            new_pass;
        num_used_counters_per_pass_per_block.push_back(new_pass);

        // Copy the set of unallocated counters.
        std::vector<GpaUInt32> counters_unallocated = public_counter->internal_counters_required_;

        // Iterate through the unallocated counters and put them into the appropriate pass.
        for (auto counter_iter = counters_unallocated.cbegin(); counter_iter != counters_unallocated.cend(); ++counter_iter)
        {
            unsigned int pass_index         = 0;
            auto         counters_used_iter = num_used_counters_per_pass_per_block.begin();
            auto         counter_pass_iter  = pass_partitions.begin();

            bool done_allocating_counter = false;

            while (done_allocating_counter == false)
            {
                // Make sure there is a partition for current pass.
                while (pass_index >= pass_partitions.size())
                {
                    GpaCounterPass counter_pass_inner;
                    pass_partitions.push_back(counter_pass_inner);
                }

                // Make sure there are counts for the number of used counters for current pass.
                while (pass_index >= num_used_counters_per_pass_per_block.size())
                {
                    PerPassData new_pass_inner;
                    num_used_counters_per_pass_per_block.push_back(new_pass_inner);
                }

                // Increment the pass iterator if past the first loop.
                if (pass_index > 0)
                {
                    ++counters_used_iter;
                    ++counter_pass_iter;
                }

                counter_accessor->SetCounterIndex(*counter_iter);
                unsigned int group_index = counter_accessor->GroupIndex();

                // Try to add the counter to the current pass.
                if (CheckForTimestampCounters(counter_accessor, *counter_pass_iter) &&
                    CanCounterBeAdded(counter_accessor, *counters_used_iter, max_counters_per_group) &&
                    CheckForSQCounters(counter_accessor, *counters_used_iter, max_sq_counters_) &&
                    CheckCountersAreCompatible(counter_accessor, *counters_used_iter))
                {
                    counter_pass_iter->pass_counter_list.push_back(*counter_iter);
                    counters_used_iter->num_used_counters_per_block[group_index].push_back(counter_accessor->CounterIndex());
                    done_allocating_counter = true;
                }
                else
                {
                    // The counters needs to go into the next pass. Increment the pass index and let the loop happen again.
                    ++pass_index;
                }
            }
        }

        // Return the passes.
        return pass_partitions;
    }
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_CONSOLIDATED_H_
