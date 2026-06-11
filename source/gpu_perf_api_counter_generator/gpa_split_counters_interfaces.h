//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Interfaces used for counter splitting.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_INTERFACES_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTERS_INTERFACES_H_

#include <algorithm>
#include <cstdint>
#include <list>
#include <limits>
#include <map>
#include <set>
#include <type_traits>
#include <vector>
#include <optional>
#include <span>

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
#include <sstream>
#endif

#include "gpu_perf_api_counter_generator/gpa_derived_counter.h"
#include "gpu_perf_api_common/logging.h"

/// @brief Enum to represent the different SQ shader stages.
enum GpaSqShaderStage : uint8_t
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
    std::vector<uint32_t> pass_counter_list;
};

/// @brief Stores the number of counters from each block that are used in a particular pass.
struct PerPassData
{
    /// The list of counters used from each HW block. Map from group index to list of counters.
    std::map<uint32_t, std::vector<GpaUInt32>> num_used_counters_per_block;
};

/// @brief Stores the counter indices for hardware counters.
struct GpaHardwareCounterIndices
{
    uint32_t public_index;    ///< The index of the hardware counter as exposed by GPUPerfAPI (first hw counter is after all public counters).
    uint32_t hardware_index;  ///< The 0-based index of the hardware counter.
};

/// @brief Records where to locate the results of a counter query in session requests.
struct GpaCounterResultLocation
{
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
    virtual void SetCounterIndex(uint32_t index) = 0;

    /// @brief Get the 0-based group index of the internal counter.
    ///
    /// @return The group index.
    [[nodiscard]] virtual uint32_t GroupIndex() const = 0;

    /// @brief Get the 0-based counter index of the internal counter.
    ///
    /// @return The counter index.
    [[nodiscard]] virtual uint32_t CounterIndex() const = 0;

    /// @brief Get the hardware counter bool.
    ///
    /// @return True if the counter is a hardware counter.
    [[nodiscard]] virtual bool IsHwCounter() const = 0;

    /// @brief Get the global group group index (the full index of the software groups that come after the hardware groups).
    ///
    /// @return The total number of groups.
    [[nodiscard]] virtual uint32_t GlobalGroupIndex() const = 0;

    /// @brief Get the global counter index.
    ///
    /// @return The global counter index.
    [[nodiscard]] virtual uint32_t GetGlobalCounterIndex() const = 0;
};

/// @brief Interface for a class that can split public and internal counters into separate passes.
class IGpaSplitCounters
{
public:
    /// @brief Initializes a new instance of the IGpaSplitCounters interface.
    ///
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] eop_time_counter_indices Set of End Of Pipeline timestamp counter indices.
    /// @param [in] top_time_counter_indices Set of Top Of Pipeline timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of counters that can be simultaneously enabled on the SQ block.
    /// @param [in] sq_counter_block_info The span of SQ counter groups.
    /// @param [in] isolated_from_sq_groups The span of counter groups that must be isolated from SQ counter groups.
    IGpaSplitCounters(const std::set<uint32_t>&              timestamp_block_ids,
                      const std::set<uint32_t>&              eop_time_counter_indices,
                      const std::set<uint32_t>&              top_time_counter_indices,
                      uint8_t                                max_sq_counters,
                      std::span<const GpaSqCounterGroupDesc> sq_counter_block_info,
                      std::span<const uint32_t>              isolated_from_sq_groups)
        : timestamp_block_ids_(timestamp_block_ids)
        , eop_time_counter_indices_(eop_time_counter_indices)
        , top_time_counter_indices_(top_time_counter_indices)
        , max_sq_counters_(max_sq_counters)
    {
        for (const auto& sq_group : sq_counter_block_info)
        {
            sq_counter_index_map_[sq_group.group_index] = sq_group;
            sq_shader_stage_group_map_[sq_group.sq_shader_stage].push_back(sq_group.group_index);

            // We need to isolate stage-specific SQ counters from various texture blocks that are also
            // affected by the shader stage mask in SQ.
            if (sq_group.sq_shader_stage != kSqAll)
            {
                isolated_sq_counter_index_set_.insert(sq_group.group_index);
            }
        }

        for (const uint32_t group_index : isolated_from_sq_groups)
        {
            isolated_from_sq_group_index_set_.insert(group_index);
        }
    }

    /// @brief Virtual destructor.
    virtual ~IGpaSplitCounters() = default;

    /// @brief Splits counters into multiple passes.
    ///
    /// @param [in] public_counters_to_split The set of public counters that need to be split into passes.
    /// @param [in] internal_counters_to_schedule Additional internal counters that need to be scheduled (used by internal builds).
    /// @param [in] counter_group_accessor A class to access the internal counters.
    /// @param [in] max_counters_per_group The maximum number of counters that can be enabled in a single pass on each HW block or SW group.
    /// @param [out] pass_partitions The resulting set of passes that the counters were split into.
    ///
    /// @return A GpaStatus code indicating if the counters could be scheduled successfully.
    [[nodiscard]] virtual GpaStatus SplitCounters(const std::vector<const GpaDerivedCounterInfoClass*>& public_counters_to_split,
                                                  const std::vector<GpaHardwareCounterIndices>&         internal_counters_to_schedule,
                                                  IGpaCounterGroupAccessor*                             counter_group_accessor,
                                                  const std::vector<uint32_t>&                          max_counters_per_group,
                                                  std::list<GpaCounterPass>&                            pass_partitions) = 0;

    /// @brief Avoid making a copy of the map by swapping it with the output parameter.
    ///
    /// @param [out] counter_result_location_map The map of counter result locations.
    void SwapCounterResultLocations(std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>>& counter_result_location_map)
    {
        counter_result_location_map_.swap(counter_result_location_map);
    }

protected:
    const std::set<uint32_t>& timestamp_block_ids_;       ///< Reference to set of timestamp block id's.
    const std::set<uint32_t>& eop_time_counter_indices_;  ///< Reference to set of EOP timestamp counter indices
    const std::set<uint32_t>& top_time_counter_indices_;  ///< Reference to set of TOP timestamp counter indices

    uint8_t max_sq_counters_ = 0;  ///< The maximum number of counters that can be enabled in a single pass in the SQ group.

    std::map<GpaUInt32, GpaSqCounterGroupDesc>        sq_counter_index_map_;       ///< Map from group index to the SQ counter group description for that group.
    std::map<GpaSqShaderStage, std::vector<uint32_t>> sq_shader_stage_group_map_;  ///< Map from shader stage to the list of SQ groups for that stage.
    std::set<GpaUInt32>                               isolated_sq_counter_index_set_;     ///< Set of isolated SQ counter groups.
    std::set<GpaUInt32>                               isolated_from_sq_group_index_set_;  ///< Set of groups that must be isolated from isolated SQ groups.

    /// A map between a public counter index and the set of hardware counters that compose the public counter.
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> counter_result_location_map_;

    /// @brief Determines whether the indicated block id is a timestamp block id.
    ///
    /// @param [in] block_id The block id to check.
    ///
    /// @return True if the block id is a timestamp block id.
    [[nodiscard]] bool IsTimestampBlockId(uint32_t block_id) const
    {
        return timestamp_block_ids_.contains(block_id);
    }

    /// @brief Determines whether the indicated counter index is a timestamp counter.
    ///
    /// @param [in] counter_index The counter index to check.
    ///
    /// @return True if the counter index is a timestamp counter.
    [[nodiscard]] bool IsTimeCounterIndex(uint32_t counter_index) const
    {
        return IsBottomToBottomTimeCounterIndex(counter_index) || IsTopToBottomTimeCounterIndex(counter_index);
    }

    /// @brief Determines whether the indicated counter index is a Bottom-To-Bottom timestamp counter.
    ///
    /// @param counter_index The counter index to check.
    ///
    /// @return True if the counter index is a Bottom-To-Bottom timestamp counter.
    [[nodiscard]] bool IsBottomToBottomTimeCounterIndex(uint32_t counter_index) const
    {
        return eop_time_counter_indices_.contains(counter_index);
    }

    /// @brief Determines whether the indicated counter index is a Top-to-Bottom timestamp counter.
    ///
    /// @param counter_index The counter index to check.
    ///
    /// @return True if the counter index is a Top-to-Bottom timestamp counter.
    [[nodiscard]] bool IsTopToBottomTimeCounterIndex(uint32_t counter_index) const
    {
        return top_time_counter_indices_.contains(counter_index);
    }

    /// @brief Adds a counter result location.
    ///
    /// @param [in] public_counter_index The index of the public counter whose result location is being added.
    /// @param [in] hardware_counter_index The index of a particular hardware counter that makes up the public counter specified by publicCounterIndex.
    /// @param [in] pass_index The index of the pass in which the counter is scheduled.
    /// @param [in] offset The offset of the result within that pass.
    void AddCounterResultLocation(uint32_t public_counter_index, uint32_t hardware_counter_index, uint32_t pass_index, size_t offset)
    {
        if (offset > std::numeric_limits<GpaUInt16>::max() || pass_index > std::numeric_limits<GpaUInt16>::max()) [[unlikely]]
        {
            assert(0);
            return;
        }

        const GpaCounterResultLocation location = {
            .pass_index_ = static_cast<GpaUInt16>(pass_index),
            .offset_     = static_cast<GpaUInt16>(offset),
        };

        counter_result_location_map_[public_counter_index][hardware_counter_index] = location;
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        std::stringstream ss;
        ss << "Result location for public counter: " << public_counter_index << ", hardwarecounter: " << hardware_counter_index << " is offset: " << offset
           << " in pass: " << pass_index;
        GpaLogger::Instance().LogDebugCounterDefs("{}", ss.str());
#endif
    }

    /// @brief Scans a vector to determine if it contains a specified element.
    ///
    /// @param [in] array The vector to scan.
    /// @param [in] element The item to search for.
    ///
    /// @return The index of the element if the vector contains it; otherwise `std::nullopt`.
    [[nodiscard]] std::optional<size_t> VectorContains(std::span<const uint32_t> array, const uint32_t element)
    {
        if (const auto it = std::ranges::find(array, element); it != array.end())
        {
            return std::distance(array.begin(), it);
        }
        return std::nullopt;
    }

    /// @brief Tests to see if the counter group is an isolated SQ counter group.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    ///
    /// @return True if a counter is an isolated SQ group counter.
    [[nodiscard]] bool IsIsolatedSqCounterGroup(const IGpaCounterGroupAccessor* counter_group_accessor) const
    {
        const uint32_t group_index = counter_group_accessor->GlobalGroupIndex();
        return isolated_sq_counter_index_set_.contains(group_index);
    }

    /// @brief Tests to see if the counter group must be isolated from the isolated SQ counter groups.
    ///
    /// @param [in] counter_group_accessor The counter accessor that describes the counter that needs to be scheduled.
    ///
    /// @return True if a counter must be isolated from isolated SQ group counters.
    [[nodiscard]] bool IsCounterGroupIsolatedFromIsolatedSqCounterGroup(const IGpaCounterGroupAccessor* counter_group_accessor) const
    {
        const uint32_t group_index = counter_group_accessor->GlobalGroupIndex();
        return isolated_from_sq_group_index_set_.contains(group_index);
    }

    /// @brief Tests to see if the enabled counters include one of those in the parameter set.
    ///
    /// @param [in] current_pass_data The counters enabled on each block in the current pass.
    /// @param [in] counter_set List of counter groups to check for in the enabled set.
    ///
    /// @return True if a counter enabled in the current pass is a member of the validation set.
    [[nodiscard]] bool EnabledCounterGroupsContain(const PerPassData& current_pass_data, const std::set<uint32_t>& counter_set) const
    {
        for (const auto& group_entry : current_pass_data.num_used_counters_per_block)
        {
            // Is the counter group in the list of interest?
            if (!counter_set.contains(group_entry.first))
            {
                continue;
            }

            // Check if any counters are scheduled on it.
            if (!group_entry.second.empty())
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
    [[nodiscard]] bool CheckCountersAreCompatible(const IGpaCounterGroupAccessor* counter_group_accessor, const PerPassData& current_pass_data) const
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
    void AddNewPassInfo(uint32_t num_required_passes, std::list<GpaCounterPass>* pass_partitions, std::list<PerPassData>* num_used_counters_per_pass_per_block)
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
    [[nodiscard]] bool CanCounterBeAdded(const IGpaCounterGroupAccessor* counter_group_accessor,
                                         PerPassData&                    current_pass_data,
                                         const std::vector<uint32_t>&    max_counters_per_group) const
    {
        uint32_t group_index          = counter_group_accessor->GlobalGroupIndex();
        size_t   new_group_used_count = 1;

        if (current_pass_data.num_used_counters_per_block.count(group_index) > 0)
        {
            new_group_used_count += current_pass_data.num_used_counters_per_block[group_index].size();
        }

        uint32_t group_limit = max_counters_per_group[group_index];
        if (group_limit == 0)
        {
            GpaLogger::Instance().LogDebugError("Group({}) counter limit is zero.", group_index);
            return false;
        }

        return new_group_used_count <= group_limit;
    }

    /// @brief Checks the current pass data to see if there are SQ counters on it, and will only allow counters belonging to the same SQ stage.
    ///
    /// @param [in] counter_group_accessor Counter accessor that describes the counter that needs to be scheduled.
    /// @param [in] current_pass_data The number of counters enabled on each block in the current pass.
    /// @param [in] max_sq_counters The maximum number of simultaneous counters allowed on the SQ block.
    ///
    /// @return True if a counter can be added to the block specified by blockIndex; false if the counter cannot be scheduled.
    [[nodiscard]] bool CheckForSQCounters(const IGpaCounterGroupAccessor* counter_group_accessor,
                                          const PerPassData&              current_pass_data,
                                          uint8_t                         max_sq_counters) const
    {
        const uint32_t group_index   = counter_group_accessor->GlobalGroupIndex();
        const uint32_t counter_index = counter_group_accessor->CounterIndex();

        const auto sq_it = sq_counter_index_map_.find(group_index);
        if (sq_it == sq_counter_index_map_.end())
        {
            return true;
        }

        const GpaSqCounterGroupDesc& sq_counter_group = sq_it->second;
        const std::vector<uint32_t>& groups           = sq_shader_stage_group_map_.at(sq_counter_group.sq_shader_stage);  // Groups for this stage.

        std::vector<uint32_t> this_stage_counters;
        this_stage_counters.reserve(max_sq_counters);

        // Check if this counter has already been added (either via the current or a different shader engine).
        for (uint32_t g : groups)
        {
            uint32_t this_group_index = sq_counter_index_map_.at(g).group_index;

            if (current_pass_data.num_used_counters_per_block.count(this_group_index) > 0)
            {
                for (uint32_t i = 0; i < current_pass_data.num_used_counters_per_block.at(this_group_index).size(); i++)
                {
                    const uint32_t cur_counter = current_pass_data.num_used_counters_per_block.at(this_group_index).at(i);

                    if (std::ranges::find(this_stage_counters, cur_counter) == this_stage_counters.end())
                    {
                        this_stage_counters.push_back(cur_counter);
                    }

                    if (current_pass_data.num_used_counters_per_block.at(this_group_index).at(i) == counter_index)
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
        for (std::underlying_type_t<GpaSqShaderStage> i = kSqAll; i <= kSqLast; ++i)
        {
            const auto stage = static_cast<GpaSqShaderStage>(i);

            if (stage == sq_counter_group.sq_shader_stage)
            {
                continue;
            }

            auto stage_it = sq_shader_stage_group_map_.find(stage);
            if (stage_it == sq_shader_stage_group_map_.end())
            {
                continue;
            }

            for (const uint32_t group : stage_it->second)
            {
                auto block_it = current_pass_data.num_used_counters_per_block.find(group);
                if (block_it != current_pass_data.num_used_counters_per_block.end() && !block_it->second.empty())
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
    [[nodiscard]] bool CheckForTimestampCounters(const IGpaCounterGroupAccessor* counter_group_accessor, const GpaCounterPass& current_pass_counters) const
    {
        const uint32_t block_index = counter_group_accessor->GlobalGroupIndex();

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
        else
        {
            bool all_timestamp_counters = false;

            // TOP counters can share the same pass
            // EOP counters can share the same pass
            // However, they cannot be mixed together
            if (IsBottomToBottomTimeCounterIndex(counter_group_accessor->GetGlobalCounterIndex()))
            {
                all_timestamp_counters = true;

                for (const auto counter : current_pass_counters.pass_counter_list)
                {
                    if (!IsBottomToBottomTimeCounterIndex(counter))
                    {
                        all_timestamp_counters = false;
                        break;
                    }
                }
            }
            else if (IsTopToBottomTimeCounterIndex(counter_group_accessor->GetGlobalCounterIndex()))
            {
                all_timestamp_counters = true;

                for (const auto counter : current_pass_counters.pass_counter_list)
                {
                    if (!IsTopToBottomTimeCounterIndex(counter))
                    {
                        all_timestamp_counters = false;
                        break;
                    }
                }
            }

            if (all_timestamp_counters)
            {
                return true;
            }
        }

        return false;
    }
};

#endif
