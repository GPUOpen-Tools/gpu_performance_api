//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Maintains a set of software counters.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SOFTWARE_COUNTERS_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SOFTWARE_COUNTERS_H_

#include <sstream>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpu_perf_api_counter_generator/gpa_sw_counter_manager.h"

/// @brief Struct to describe a software counter.
struct GpaSoftwareCounterDescExt
{
    GpaUInt32               group_index;            ///< Index of group containing this counter.
    GpaUInt32               group_id_driver;        ///< Group ID according to the driver.
    GpaUInt32               counter_id_driver;      ///< Counter ID according to the driver.
    GpaSoftwareCounterDesc* software_counter_desc;  ///< The internal counter.
};

/// @brief Maintains a set of software counters.
class GpaSoftwareCounters
{
public:
    /// @brief Initializes an instance of the GPA_SoftwareCounters class.
    GpaSoftwareCounters()
    {
        Clear();
    }

    /// @brief Virtual destructor.
    virtual ~GpaSoftwareCounters()
    {
    }

    /// @brief Clears all counter data.
    void Clear()
    {
        software_counter_list_.clear();
        counter_group_array_ = nullptr;
        counter_group_desc_  = nullptr;
        group_count_         = 0;
        counters_generated_  = false;
    }

    /// @brief Obtains the number of software counters.
    ///
    /// @return The number of software counters.
    GpaUInt32 GetNumCounters() const
    {
        return static_cast<GpaUInt32>(software_counter_list_.size());
    }

    /// @brief Gets the name of the specified counter.
    ///
    /// @param [in] index The index of the counter whose name is needed.
    ///
    /// @return The name of the specified counter.
    const char* GetCounterName(GpaUInt32 index) const
    {
        return software_counter_list_[index].software_counter_desc->name;
    }

    /// @brief Gets the group name of the specified counter.
    ///
    /// @param [in] index The index of the counter whose group is needed.
    ///
    /// @return The group name of the specified counter.
    const char* GetCounterGroup(GpaUInt32 index) const
    {
        return software_counter_list_[index].software_counter_desc->group;
    }

    /// @brief Gets the description of the specified counter.
    ///
    /// @param [in] index The index of the counter whose description is needed.
    ///
    /// @return The description of the specified counter.
    const char* GetCounterDescription(GpaUInt32 index) const
    {
        return software_counter_list_[index].software_counter_desc->description;
    }

    /// @brief Gets a counter's UUID.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's UUID.
    GpaUuid GetCounterUuid(GpaUInt32 index) const
    {
        return ::GetCounterUuid(GetCounterName(index), GetCounterDescription(index));
    }

    /// @brief Gets a counter's supported sample type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's supported sample type.
    GpaCounterSampleType GetCounterSampleType(GpaUInt32 index) const
    {
        UNREFERENCED_PARAMETER(index);

        // All software counters are discrete counters.
        return kGpaCounterSampleTypeDiscrete;
    }

    /// @brief Gets the type of the specified counter.
    ///
    /// @param [in] index The index of the counter whose type is needed.
    ///
    /// @return The type of the specified counter.
    GpaDataType GetCounterType(GpaUInt32 index) const
    {
        return software_counter_list_[index].software_counter_desc->type;
    }

    GpaSoftwareCounterDesc**               counter_group_array_;    ///< List of counter groups as defined by the list of counters in each group.
    GpaCounterGroupDesc*                   counter_group_desc_;     ///< List of internal counter groups.
    bool                                   counters_generated_;     ///< Indicates that the counters have been generated.
    std::vector<GpaSoftwareCounterDescExt> software_counter_list_;  ///< The list of software counters.
    unsigned int                           group_count_;            ///< The number of internal counter groups.
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SOFTWARE_COUNTERS_H_
