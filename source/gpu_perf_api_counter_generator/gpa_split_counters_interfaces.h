//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Interfaces used for counter splitting.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_INTERFACES_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_INTERFACES_H_

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
#include <sstream>
#include "gpu_perf_api_common/logging.h"
#endif

#include "gpu_perf_api_counter_generator/gpa_derived_counter.h"

/// @brief Enum to represent the different SQ shader stages.
enum GpaSqShaderStage
{
    kSqAll,          ///< All stages.
    kSqEs,           ///< ES Stage.
    kSqGs,           ///< GS Stage.
    kSqVs,           ///< VS Stage.
    kSqPs,           ///< PS Stage.
    kSqLs,           ///< LS Stage.
    kSqHs,           ///< HS Stage.
    kSqCs,           ///< CS Stage.
    kSqLast = kSqCs  ///< Last known stage.
};

/// @brief Structure representing an SQ counter group.
struct GpaSqCounterGroupDesc
{
    GpaUInt32        group_index;      ///< 0-based index of the group.
    GpaUInt32        shader_engine;    ///< 0-based index of the shader engine for this group.
    GpaSqShaderStage sq_shader_stage;  ///< The shader stage for this group.
};

/// @brief Structure to store the counters that are assigned to a particular pass.
struct GpaCounterPass
{
    /// The counters assigned to a profile pass.
    std::vector<unsigned int> pass_counter_list;
};

/// Typedef for a list of counter passes.
typedef std::list<GpaCounterPass> GpaCounterPassList;

/// @brief Stores the number of counters from each block that are used in a particular pass.
struct PerPassData
{
    /// The list of counters used from each HW block. Map from group index to list of counters.
    std::map<unsigned int, std::vector<GpaUInt32>> num_used_counters_per_block;
};

/// @brief Stores the counter indices for hardware counters.
struct GpaHardwareCounterIndices
{
    unsigned int public_index;    ///< The index of the hardware counter as exposed by GPUPerfAPI (first hw counter is after all public counters).
    unsigned int hardware_index;  ///< The 0-based index of the hardware counter.
};

/// @brief Stores the counter indices for software counters.
struct GpaSoftwareCounterIndices
{
    unsigned int public_index;    ///< The index of the software counter as exposed by GPUPerfAPI (first sw counter is after all public counters).
    unsigned int software_index;  ///< The 0-based index of the software counter.
};

/// @brief Records where to locate the results of a counter query in session requests.
class GpaCounterResultLocation
{
public:
    GpaUInt16 pass_index_;  ///< Index of the pass.
    GpaUInt16 offset_;      ///< Offset within pass ( 0 is first counter ).
};

/// @brief Interface for accessing information of an internal counter.
class IGpaCounterGroupAccessor
{
public:
    /// @brief Initializes an instance of the IGpaCounterAccessor interface.
    IGpaCounterGroupAccessor() = default;

    /// @brief Virtual destructor.
    virtual ~IGpaCounterGroupAccessor() = default;

    /// @brief Sets the counter index of which to get the group and counter Id.
    ///
    /// @param [in] index The counter index.
    virtual void SetCounterIndex(unsigned int index) = 0;

    /// @brief Get the 0-based group index of the internal counter.
    ///
    /// @return The group index.
    virtual unsigned int GroupIndex() const = 0;

    /// @brief Get the 0-based counter index of the internal counter.
    ///
    /// @return The counter index.
    virtual unsigned int CounterIndex() const = 0;

    /// @brief Get the hardware counter bool.
    ///
    /// @return True if the counter is a hardware counter.
    virtual bool IsHwCounter() const = 0;

    /// @brief Get the software counter bool.
    ///
    /// @return True if the counter is a software counter.
    virtual bool IsSwCounter() const = 0;

    /// @brief Get the global group group index (the full index of the software groups that come after the hardware groups).
    ///
    /// @return The total number of groups.
    virtual unsigned int GlobalGroupIndex() const = 0;
};

/// @brief Interface for a class that can split public and internal counters into separate passes.
class IGpaSplitCounters
{
public:
    /// @brief Initializes a new instance of the IGpaSplitCounters interface.
    ///
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] time_counter_indices Set of timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of counters that can be simultaneously enabled on the SQ block.
    /// @param [in] num_sq_groups The number of SQ counter groups.
    /// @param [in] sq_counter_block_info The list of SQ counter groups.
    /// @param [in] num_isolated_from_sq_groups The number of counter groups that must be isolated from SQ counter groups.
    /// @param [in] isolated_from_sq_groups The list of counter groups that must be isolated from SQ counter groups.
    IGpaSplitCounters(const std::set<unsigned int>& timestamp_block_ids,
                      const std::set<unsigned int>& time_counter_indices,
                      unsigned int                  max_sq_counters,
                      unsigned int                  num_sq_groups,
                      GpaSqCounterGroupDesc*        sq_counter_block_info,
                      unsigned int                  num_isolated_from_sq_groups,
                      const unsigned int*           isolated_from_sq_groups)
        : timestamp_block_ids_(timestamp_block_ids)
        , time_counter_indices_(time_counter_indices)
        , max_sq_counters_(max_sq_counters)
    {
        for (unsigned int i = 0; i < num_sq_groups; i++)
        {
            sq_counter_index_map_[sq_counter_block_info[i].group_index] = sq_counter_block_info[i];
            sq_shader_stage_group_map_[sq_counter_block_info[i].sq_shader_stage].push_back(sq_counter_block_info[i].group_index);

            // We need to isolate stage-specific SQ counters from various texture blocks that are also
            // affected by the shader stage mask in SQ.
            if (sq_counter_block_info[i].sq_shader_stage != kSqAll)
            {
                isolated_sq_counter_index_set_.insert(sq_counter_block_info[i].group_index);
            }
        }

        for (uint32_t i = 0; i < num_isolated_from_sq_groups; ++i)
        {
            isolated_from_sq_group_index_set_.insert(isolated_from_sq_groups[i]);
        }
    }

    /// @brief Virtual destructor.
    virtual ~IGpaSplitCounters()
    {
        sq_counter_index_map_.clear();
        sq_shader_stage_group_map_.clear();
    }

    /// @brief Splits counters into multiple passes.
    ///
    /// @param [in] public_counters_to_split The set of public counters that need to be split into passes.
    /// @param [in] internal_counters_to_schedule Additional internal counters that need to be scheduled (used by internal builds).
    /// @param [in] software_counters_to_schedule Additional software counters that need to be scheduled.
    /// @param [in] counter_group_accessor A class to access the internal counters.
    /// @param [in] max_counters_per_group The maximum number of counters that can be enabled in a single pass on each HW block or SW group.
    /// @param [out] num_scheduled_counters Indicates the total number of internal counters that were assigned to a pass.
    ///
    /// @return The list of passes that the counters are separated into.
    virtual std::list<GpaCounterPass> SplitCounters(const std::vector<const GpaDerivedCounterInfoClass*>& public_counters_to_split,
                                                    const std::vector<GpaHardwareCounterIndices>          internal_counters_to_schedule,
                                                    const std::vector<GpaSoftwareCounterIndices>          software_counters_to_schedule,
                                                    IGpaCounterGroupAccessor*                             counter_group_accessor,
                                                    const std::vector<unsigned int>&                      max_counters_per_group,
                                                    unsigned int&                                         num_scheduled_counters) = 0;

    /// @brief Get the counter result locations.
    ///
    /// @return The map of counter result locations.
    std::map<unsigned int, std::map<unsigned int, GpaCounterResultLocation>> GetCounterResultLocations() const
    {
        return counter_result_location_map_;
    }

protected:
    std::set<unsigned int> timestamp_block_ids_;   ///< Set of timestamp block id's.
    std::set<unsigned int> time_counter_indices_;  ///< Set of timestamp counter indices.

    unsigned int max_sq_counters_;  ///< The maximum number of counters that can be enabled in the SQ group.

    std::map<GpaUInt32, GpaSqCounterGroupDesc>       sq_counter_index_map_;       ///< Map from group index to the SQ counter group description for that group.
    std::map<GpaSqShaderStage, vector<unsigned int>> sq_shader_stage_group_map_;  ///< Map from shader stage to the list of SQ groups for that stage.
    std::set<GpaUInt32>                              isolated_sq_counter_index_set_;     ///< Set of isolated SQ counter groups.
    std::set<GpaUInt32>                              isolated_from_sq_group_index_set_;  ///< Set of groups that must be isolated from isolated SQ groups.

    /// A map between a public counter index and the set of hardware counters that compose the public counter.
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map<unsigned int, std::map<unsigned int, GpaCounterResultLocation>> counter_result_location_map_;

    /// @brief Determines whether the indicated block id is a timestamp block id.
    ///
    /// @param [in] block_id The block id to check.
    ///
    /// @return True if the block id is a timestamp block id.
    bool IsTimestampBlockId(unsigned int block_id)
    {
        return timestamp_block_ids_.find(block_id) != timestamp_block_ids_.end();
    }

    /// @brief Determines whether the indicated counter index is a timestamp counter.
    ///
    /// @param [in] counter_index The counter index to check.
    ///
    /// @return True if the counter index is a timestamp counter.
    bool IsTimeCounterIndex(unsigned int counter_index)
    {
        return time_counter_indices_.find(counter_index) != time_counter_indices_.end();
    }

    /// @brief Adds a counter result location.
    ///
    /// @param [in] public_counter_index The index of the public counter whose result location is being added.
    /// @param [in] hardware_counter_index The index of a particular hardware counter that makes up the public counter specified by publicCounterIndex.
    /// @param [in] pass_index The index of the pass in which the counter is scheduled.
    /// @param [in] offset The offset of the result within that pass.
    void AddCounterResultLocation(unsigned int public_counter_index, unsigned int hardware_counter_index, unsigned int pass_index, unsigned int offset)
    {
        GpaCounterResultLocation location = {};
        location.offset_                  = static_cast<GpaUInt16>(offset);
        location.pass_index_              = static_cast<GpaUInt16>(pass_index);

        counter_result_location_map_[public_counter_index][hardware_counter_index] = location;
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        std::stringstream ss;
        ss << "Result location for public counter: " << public_counter_index << ", hardwarecounter: " << hardware_counter_index << " is offset: " << offset
           << " in pass: " << pass_index;
        GPA_LOG_DEBUG_COUNTER_DEFS(ss.str().c_str());
#endif
    }

    /// @brief Scans a vector to determine if it contains a specified element.
    ///
    /// @param [in] array The vector to scan.
    /// @param [in] element The item to search for.
    ///
    /// @retval -1 if the vector does not contain the element.
    /// @return The index of the element if the vector does contain it.
    template <class T>
    int VectorContains(const vector<T>& array, const T& element)
    {
        int array_size = static_cast<int>(array.size());

        for (int i = 0; i < array_size; i++)
        {
            if (array[i] == element)
            {
                return i;
            }
        }

        return -1;
    };

    /// @brief Tests to see if the counter group is an isolated SQ counter group.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    ///
    /// @return True if a counter is an isolated SQ group counter.
    bool IsIsolatedSqCounterGroup(const IGpaCounterGroupAccessor* counter_group_accessor) const
    {
        unsigned int group_index = counter_group_accessor->GlobalGroupIndex();
        return isolated_sq_counter_index_set_.find(group_index) != isolated_sq_counter_index_set_.end();
    }

    /// @brief Tests to see if the counter group must be isolated from the isolated SQ counter groups.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    ///
    /// @return True if a counter must be isolated from isolated SQ group counters.
    bool IsCounterGroupIsolatedFromIsolatedSqCounterGroup(const IGpaCounterGroupAccessor* counter_group_accessor) const
    {
        unsigned int group_index = counter_group_accessor->GlobalGroupIndex();
        return isolated_from_sq_group_index_set_.find(group_index) != isolated_from_sq_group_index_set_.end();
    }

    /// @brief Tests to see if the enabled counters include one of those in the parameter set.
    ///
    /// @param [in] current_pass_data The counters enabled on each block in the current pass.
    /// @param [in] counter_set List of counter groups to check for in the enabled set.
    ///
    /// @return True if a counter enabled in the current pass is a member of the validation set.
    bool EnabledCounterGroupsContain(const PerPassData& current_pass_data, const std::set<uint32_t>& counter_set) const
    {
        for (const auto& group_entry : current_pass_data.num_used_counters_per_block)
        {
            // Is the counter group in the list of interest?
            if (counter_set.find(group_entry.first) == counter_set.end())
            {
                continue;
            }

            // Check if any counters are scheduled on it.
            if (group_entry.second.size())
            {
                return true;
            }
        }

        return false;
    }

    /// @brief Tests to see if the counter group that needs to be scheduled is compatible with those already scheduled.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    /// @param [in] current_pass_data The counters enabled on each block in the current pass.
    ///
    /// @return True if the counter is compatible with counters already scheduled on the current pass.
    bool CheckCountersAreCompatible(const IGpaCounterGroupAccessor* counter_group_accessor, const PerPassData& current_pass_data) const
    {
        // SQ counters cannot be scheduled on the same pass as TCC/TA/TCP/TCA/TD counters (and vice versa).

        if (IsIsolatedSqCounterGroup(counter_group_accessor))
        {
            return !EnabledCounterGroupsContain(current_pass_data, isolated_from_sq_group_index_set_);
        }

        if (IsCounterGroupIsolatedFromIsolatedSqCounterGroup(counter_group_accessor))
        {
            return !EnabledCounterGroupsContain(current_pass_data, isolated_sq_counter_index_set_);
        }

        return true;
    }

    /// @brief Ensures that there are enough pass partitions and per pass data for the number of required passes.
    ///
    /// @param [in] num_required_passes The number of passes that must be available in the arrays.
    /// @param [in,out] pass_partitions The list to add additional pass partitions.
    /// @param [in,out] num_used_counters_per_pass_per_block The list to which additional used counter info should be added.
    void AddNewPassInfo(unsigned int               num_required_passes,
                        std::list<GpaCounterPass>* pass_partitions,
                        std::list<PerPassData>*    num_used_counters_per_pass_per_block)
    {
        while (pass_partitions->size() < num_required_passes)
        {
            GpaCounterPass counter_pass;
            pass_partitions->push_back(counter_pass);

            PerPassData new_pass;
            num_used_counters_per_pass_per_block->push_back(new_pass);
        }
    }

    /// @brief Tests to see if a counter can be added to the specified groupIndex based on the number of counters allowed in a single pass for a particular block / group.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    /// @param [in] current_pass_data Contains the number of counters enabled on each block in the current pass.
    /// @param [in] max_counters_per_group Contains the maximum number of counters allowed on each block in a single pass.
    ///
    /// @return True if a counter can be added; false if not.
    bool CanCounterBeAdded(const IGpaCounterGroupAccessor*  counter_group_accessor,
                           PerPassData&                     current_pass_data,
                           const std::vector<unsigned int>& max_counters_per_group)
    {
        unsigned int group_index          = counter_group_accessor->GlobalGroupIndex();
        size_t       new_group_used_count = 1;

        if (current_pass_data.num_used_counters_per_block.count(group_index) > 0)
        {
            new_group_used_count += current_pass_data.num_used_counters_per_block[group_index].size();
        }

        unsigned int group_limit = max_counters_per_group[group_index];

        return new_group_used_count <= group_limit;
    }

    /// @brief Checks the current pass data to see if there are SQ counters on it, and will only allow counters belonging to the same SQ stage.
    ///
    /// @param [in] counter_group_accessor Counter accessor that describes the counter that needs to be scheduled.
    /// @param [in] current_pass_data The number of counters enabled on each block in the current pass.
    /// @param [in] max_sq_counters The maximum number of simultaneous counters allowed on the SQ block.
    ///
    /// @return True if a counter can be added to the block specified by blockIndex; false if the counter cannot be scheduled.
    bool CheckForSQCounters(const IGpaCounterGroupAccessor* counter_group_accessor, PerPassData& current_pass_data, unsigned int max_sq_counters)
    {
        unsigned int group_index   = counter_group_accessor->GlobalGroupIndex();
        unsigned int counter_index = counter_group_accessor->CounterIndex();

        if (sq_counter_index_map_.count(group_index) == 0)
        {
            // This counter is not an SQ counter so return true.
            return true;
        }

        GpaSqCounterGroupDesc sq_counter_group = sq_counter_index_map_[group_index];
        vector<unsigned int>  groups           = sq_shader_stage_group_map_[sq_counter_group.sq_shader_stage];  // Groups for this stage.

        vector<unsigned int> this_stage_counters;

        // Check if this counter has already been added (either via the current or a different shader engine).
        for (vector<unsigned int>::const_iterator it = groups.begin(); it != groups.end(); ++it)
        {
            unsigned int this_group_index = sq_counter_index_map_[*it].group_index;

            if (current_pass_data.num_used_counters_per_block.count(this_group_index) > 0)
            {
                for (unsigned int i = 0; i < current_pass_data.num_used_counters_per_block[this_group_index].size(); i++)
                {
                    unsigned int                         cur_counter = current_pass_data.num_used_counters_per_block[this_group_index][i];
                    vector<unsigned int>::const_iterator it2         = std::find(this_stage_counters.begin(), this_stage_counters.end(), cur_counter);

                    if (it2 == this_stage_counters.end())
                    {
                        this_stage_counters.push_back(cur_counter);
                    }

                    if (current_pass_data.num_used_counters_per_block[this_group_index][i] == counter_index)
                    {
                        // This counter was already added via a different shader engine so allow it here.
                        return true;
                    }
                }
            }
        }

        // Now check that we haven't exceeded the max number of SQ counters in this stage.
        if (this_stage_counters.size() >= max_sq_counters)
        {
            return false;
        }

        // Check that no counters from other stages are enabled.

        for (unsigned int i = kSqAll; i <= kSqLast; i++)
        {
            if (static_cast<GpaSqShaderStage>(i) == sq_counter_group.sq_shader_stage)
            {
                continue;
            }

            for (vector<unsigned int>::const_iterator it = sq_shader_stage_group_map_[static_cast<GpaSqShaderStage>(i)].begin();
                 it != sq_shader_stage_group_map_[static_cast<GpaSqShaderStage>(i)].end();
                 ++it)
            {
                if (!current_pass_data.num_used_counters_per_block[*it].empty())
                {
                    return false;
                }
            }
        }

        return true;
    }

    /// @brief Checks if there are timestamp counters -- the counters need to go in their own pass.
    ///
    /// This is because idles must not be active when they are read, and when measuring counters idles are used.
    ///
    /// @param [in] counter_group_accessor Counter accessor that describes the counter that needs to be scheduled.
    /// @param [in] current_pass_counters List of counters in current pass.
    ///
    /// @return True if the counter passes this check (not a timestamp, or it is a timestamp and can be added); false if the counter is a timestamp and cannot be added.
    bool CheckForTimestampCounters(const IGpaCounterGroupAccessor* counter_group_accessor, const GpaCounterPass& current_pass_counters)
    {
        unsigned int block_index = counter_group_accessor->GlobalGroupIndex();

        // If this is not a gpuTime counter, it can potentially be added.
        if (!IsTimestampBlockId(block_index))
        {
            // But only if there are no timestamp counters in the current pass.
            bool pass_contains_gpu_time_counter = false;

            for (size_t i = 0; i < current_pass_counters.pass_counter_list.size(); i++)
            {
                if (IsTimeCounterIndex(current_pass_counters.pass_counter_list[i]))
                {
                    pass_contains_gpu_time_counter = true;
                    break;
                }
            }

            return !pass_contains_gpu_time_counter;
        }

        // The counter is a GPUTimestamp counter.
        // If there are no other counters in this pass, check if can add timestamp.
        size_t num_counters_in_pass = current_pass_counters.pass_counter_list.size();

        if (num_counters_in_pass == 0)
        {
            // It's the first counter so it's ok.
            return true;
        }

        return false;
    }
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_INTERFACES_H_
