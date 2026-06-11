//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Counter group accessor class.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GROUP_ACCESSOR_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GROUP_ACCESSOR_H_

#include <span>
#include "gpa_counter.h"
#include "gpa_split_counters_interfaces.h"

/// @brief Indexes into an array of internal groups and counters and can access data from the internal counter.
class GpaCounterGroupAccessor final : public IGpaCounterGroupAccessor
{
public:
    /// @brief Initializes a new instance of the GPACounterGroupAccessor class.
    ///
    /// @param [in] hardware_groups The hardware counter groups.
    /// @param [in] hardware_additional_groups The additional hardware counter groups.
    GpaCounterGroupAccessor(std::span<const GpaCounterGroupDesc> hardware_groups, std::span<const GpaCounterGroupDesc> hardware_additional_groups)
        : hardware_groups_(hardware_groups)
        , hardware_additional_groups_(hardware_additional_groups)
    {
    }

    /// @brief Destructor.
    ~GpaCounterGroupAccessor() override = default;

    /// @brief Copy constructor is deleted.
    GpaCounterGroupAccessor(const GpaCounterGroupAccessor&) = delete;

    /// @brief Copy assignment operator is deleted.
    GpaCounterGroupAccessor& operator=(const GpaCounterGroupAccessor&) = delete;

    /// @brief Move constructor is deleted.
    GpaCounterGroupAccessor(GpaCounterGroupAccessor&&) = delete;

    /// @brief Move assignment operator is deleted.
    GpaCounterGroupAccessor& operator=(GpaCounterGroupAccessor&&) = delete;

    /// @copydoc IGpaCounterGroupAccessor::SetCounterIndex()
    void SetCounterIndex(uint32_t index) override
    {
        global_counter_index_ = index;

        // Count the number of counters that belong to groups that do not include the desired index.
        uint32_t prev_group_counters = 0;
        uint32_t tmp_sum             = 0;

        is_hw_            = false;
        is_additional_hw_ = false;
        is_sw_            = false;

        uint32_t internal_counters = 0;

        for (uint32_t i = 0; i < hardware_groups_.size(); ++i)
        {
            internal_counters += static_cast<uint32_t>(hardware_groups_[i].num_counters);
        }

        for (uint32_t i = 0; i < hardware_groups_.size(); ++i)
        {
            tmp_sum = prev_group_counters + static_cast<uint32_t>(hardware_groups_[i].num_counters);

            if (tmp_sum > index)
            {
                // This group contains the desired counter index.
                // This is the right group, and we can calculate the right counter.
                group_index_   = i;
                counter_index_ = index - prev_group_counters;

                // This is a HW counter.
                is_hw_ = true;

                // Break from the loop.
                break;
            }
            else
            {
                // This group does not include the desired counter index.
                // Update the count and let the loop continue.
                prev_group_counters = tmp_sum;
            }
        }

        if (is_hw_ == true)
        {
            return;
        }

        for (uint32_t i = 0; i < hardware_additional_groups_.size(); ++i)
        {
            tmp_sum = prev_group_counters + static_cast<uint32_t>(hardware_additional_groups_[i].num_counters);

            if (tmp_sum > index)
            {
                // This group contains the desired counter index.
                // This is the right group, and we can calculate the right counter.
                group_index_   = i;
                counter_index_ = index - prev_group_counters;

                // This is an additional HW counter.
                is_additional_hw_ = true;

                // Break from the loop.
                break;
            }
            else
            {
                // This group does not include the desired counter index.
                // Update the count and let the loop continue.
                prev_group_counters = tmp_sum;
            }
        }

        if (is_additional_hw_ == true)
        {
            return;
        }

        group_index_ = 0;
        is_sw_       = true;

        if (index >= internal_counters)
        {
            counter_index_ = index - internal_counters;
        }
        else
        {
            counter_index_ = index;
        }
    }

    /// @copydoc IGpaCounterGroupAccessor::GroupIndex()
    [[nodiscard]] uint32_t GroupIndex() const override
    {
        return group_index_;
    }

    /// @copydoc IGpaCounterGroupAccessor::CounterIndex()
    [[nodiscard]] uint32_t CounterIndex() const override
    {
        return counter_index_;
    }

    /// @copydoc IGpaCounterGroupAccessor::IsHwCounter()
    [[nodiscard]] bool IsHwCounter() const override
    {
        return is_hw_;
    }

    /// @copydoc IGpaCounterGroupAccessor::GlobalGroupIndex()
    [[nodiscard]] uint32_t GlobalGroupIndex() const override
    {
        size_t global_group_index = GroupIndex();

        if (is_additional_hw_)
        {
            global_group_index += hardware_groups_.size();
        }

        if (is_sw_)
        {
            global_group_index += hardware_additional_groups_.size();
        }

        assert(global_group_index < static_cast<size_t>(std::numeric_limits<uint32_t>::max()));
        return static_cast<uint32_t>(global_group_index);
    }

    /// @brief Get the additional hardware counter bool.
    ///
    /// @return True if the counter is an additional hardware counter (one exposed by the driver, but not by GPA).
    [[nodiscard]] bool IsAdditionalHWCounter() const
    {
        return is_additional_hw_;
    }

    /// @copydoc IGpaCounterGroupAccessor::GetGlobalCounterIndex()
    [[nodiscard]] uint32_t GetGlobalCounterIndex() const override
    {
        return global_counter_index_;
    }

private:
    std::span<const GpaCounterGroupDesc> hardware_groups_;             ///< Points to the array of internal hardware counter groups.
    std::span<const GpaCounterGroupDesc> hardware_additional_groups_;  ///< Points to the array of internal additional hardware counter groups.
    uint32_t                             group_index_          = 0;    ///< Stores the group index of the set counter index.
    uint32_t                             counter_index_        = 0;    ///< Stores the counter index within the group of the set counter index.
    uint32_t                             global_counter_index_ = 0;    ///< Global counter index

    bool is_hw_ : 1            = false;  ///< Flag to record if the counter is hardware or not.
    bool is_additional_hw_ : 1 = false;  ///< Flag to record if the counter is an additional HW counter (one exposed by the driver but not by GPA).
    bool is_sw_ : 1            = false;  ///< Flag to record if the counter is SW.
};

#endif
