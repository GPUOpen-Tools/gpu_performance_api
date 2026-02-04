//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Counter group accessor class.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GROUP_ACCESSOR_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GROUP_ACCESSOR_H_

#include "gpa_counter.h"
#include "gpa_split_counters_interfaces.h"

/// @brief Indexes into an array of internal groups and counters and can access data from the internal counter.
class GpaCounterGroupAccessor : IGpaCounterGroupAccessor
{
public:
    /// @brief Initializes a new instance of the GPACounterGroupAccessor class.
    ///
    /// @param [in] hardware_groups The hardware counter groups.
    /// @param [in] hardware_group_count The number of hardware counter groups.
    /// @param [in] hardware_additional_groups The additional hardware counter groups.
    /// @param [in] hardware_additional_group_count The number of additional hardware counter groups.
    GpaCounterGroupAccessor(gpa_array_view<GpaCounterGroupDesc> hardware_groups,
                            unsigned int                        hardware_group_count,
                            GpaCounterGroupDesc*                hardware_additional_groups,
                            unsigned int                        hardware_additional_group_count)
        : hardware_groups_(hardware_groups)
        , hardware_group_count_(hardware_group_count)
        , hardware_additional_groups_(hardware_additional_groups)
        , hardware_additional_group_count_(hardware_additional_group_count)
        , group_index_(0)
        , counter_index_(0)
        , global_counter_index_(0)
    {
        is_hw_            = false;
        is_additional_hw_ = false;
        is_sw_            = false;
    }

    /// @brief Destructor.
    virtual ~GpaCounterGroupAccessor() = default;

    /// @copydoc IGpaCounterGroupAccessor::SetCounterIndex()
    void SetCounterIndex(unsigned int index) override
    {
        global_counter_index_ = index;

        // Count the number of counters that belong to groups that do not include the desired index.
        unsigned int prev_group_counters = 0;
        unsigned int tmp_sum             = 0;

        is_hw_            = false;
        is_additional_hw_ = false;
        is_sw_            = false;

        unsigned int internal_counters = 0;

        for (unsigned int i = 0; i < hardware_group_count_; ++i)
        {
            internal_counters += static_cast<unsigned int>(hardware_groups_[i].num_counters);
        }

        for (unsigned int i = 0; i < hardware_group_count_; ++i)
        {
            tmp_sum = prev_group_counters + static_cast<unsigned int>(hardware_groups_[i].num_counters);

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

        for (unsigned int i = 0; i < hardware_additional_group_count_; ++i)
        {
            tmp_sum = prev_group_counters + static_cast<unsigned int>(hardware_additional_groups_[i].num_counters);

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
    unsigned int GroupIndex() const override
    {
        return group_index_;
    }

    /// @copydoc IGpaCounterGroupAccessor::CounterIndex()
    unsigned int CounterIndex() const override
    {
        return counter_index_;
    }

    /// @copydoc IGpaCounterGroupAccessor::IsHwCounter()
    bool IsHwCounter() const override
    {
        return is_hw_;
    }

    /// @copydoc IGpaCounterGroupAccessor::GlobalGroupIndex()
    unsigned int GlobalGroupIndex() const override
    {
        unsigned int global_group_index = GroupIndex();

        if (is_additional_hw_)
        {
            // If this is a software counter then add in the HW group count.
            global_group_index += hardware_group_count_;
        }

        if (is_sw_)
        {
            // If this is a software counter then add in the HW group count.
            global_group_index += hardware_additional_group_count_;
        }

        return global_group_index;
    }

    /// @brief Get the additional hardware counter bool.
    ///
    /// @return True if the counter is an additional hardware counter (one exposed by the driver, but not by GPA).
    bool IsAdditionalHWCounter() const
    {
        return is_additional_hw_;
    }

    /// @copydoc IGpaCounterGroupAccessor::GetGlobalCounterIndex()
    unsigned int GetGlobalCounterIndex() const override
    {
        return global_counter_index_;
    }

private:
    gpa_array_view<GpaCounterGroupDesc> hardware_groups_;                  ///< Points to the array of internal hardware counter groups.
    unsigned int                        hardware_group_count_;             ///< Stores the number of hardware counter groups in the array.
    GpaCounterGroupDesc*                hardware_additional_groups_;       ///< Points to the array of internal additional hardware counter groups.
    unsigned int                        hardware_additional_group_count_;  ///< Stores the number of additional hardware counter groups in the array.
    unsigned int                        group_index_;                      ///< Stores the group index of the set counter index.
    unsigned int                        counter_index_;                    ///< Stores the counter index within the group of the set counter index.
    bool                                is_hw_;                            ///< Flag to record if the counter is hardware or not.
    bool         is_additional_hw_;     ///< Flag to record if the counter is an additional HW counter (one exposed by the driver but not by GPA).
    bool         is_sw_;                ///< Flag to record if the counter is SW.
    unsigned int global_counter_index_;  ///< Global counter index
};

#endif
