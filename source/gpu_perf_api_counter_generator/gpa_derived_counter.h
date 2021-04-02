//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Manages a set of derived counters.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_DERIVED_COUNTER_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_DERIVED_COUNTER_H_

#include <assert.h>

#include <vector>

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_perf_api_common/gpa_hw_info.h"

class IGpaCounterAccessor;
using std::vector;

/// @brief Information about a derived counter that is exposed through the interface.
class GpaDerivedCounterInfoClass
{
public:
    /// @brief Constructor taking a compute expression string.
    ///
    /// @param [in] index The index of the derived counter.
    /// @param [in] counter_name The name of the derived counter.
    /// @param [in] counter_group The group of the derived counter.
    /// @param [in] counter_description The description of the derived counter.
    /// @param [in] data_type The data type of the derived counter.
    /// @param [in] usage_type The usage type of the derived counter.
    /// @param [in] internal_counters_required The list of hardware counters required by the derived counter.
    /// @param [in] compute_expression The formula used to compute the derived counter.
    /// @param [in] uuid UUID string that uniquely and consistently identifies the derived counter.
    GpaDerivedCounterInfoClass(unsigned int       index,
                               const char*        counter_name,
                               const char*        counter_group,
                               const char*        counter_description,
                               GpaDataType        data_type,
                               GpaUsageType       usage_type,
                               vector<GpaUInt32>& internal_counters_required,
                               const char*        compute_expression,
                               const char*        uuid);

    /// @brief Default Constructor.
    ///
    /// Temporary addition of a default constructor to allow vector to build and execute.
    GpaDerivedCounterInfoClass();

    /// @brief Destructor.
    ~GpaDerivedCounterInfoClass();

    /// @brief Returns the derived counter info.
    ///
    /// @param [in] gpa_counter_accessor Hardware counter accessor.
    ///
    /// @return Pointer to derived counter info.
    GpaCounterInfo* GetCounterInfo(const IGpaCounterAccessor* gpa_counter_accessor);

    unsigned int      counter_index_;               ///< Index of this counter.
    const char*       counter_name_;                ///< The name of the counter.
    const char*       counter_group_;               ///< A group to which the counter is related.
    const char*       counter_description_;         ///< A description of what the counter means.
    GpaDataType       data_type_;                   ///< Data type.
    GpaUsageType      usage_type_;                  ///< How the counter should be interpreted (percentage, ratio, bytes, etc).
    vector<GpaUInt32> internal_counters_required_;  ///< List of internal counters that are needed to calculate this derived counter.
    const char*       compute_expression_;          ///< A string expression that shows how to calculate this counter.
    GpaUuid           uuid_ = {};                   ///< UUID that uniquely and consistently identifies a counter.

private:
    /// @brief Initializes the derived counter info.
    ///
    /// @param [in] gpa_counter_accessor Hardware counter accessor.
    ///
    /// @return True upon success otherwise false.
    bool InitializeDerivedCounterHardwareInfo(const IGpaCounterAccessor* gpa_counter_accessor);

    GpaCounterInfo*           counter_info_;               ///< Derived counter info for the counter.
    bool                      derived_counter_info_init_;  ///< Flag indicating derive counter is initialized.
    std::vector<GpaHwCounter> hw_counter_info_list_;       ///< List of gpa hardware counter.
};

/// @brief The set of available derived counters.
class GpaDerivedCounters
{
public:
    /// @brief Initializes an instance of the GpaDerivedCounters class.
    GpaDerivedCounters()
        : counters_generated_(false)
    {
    }

    /// @brief Virtual destructor.
    virtual ~GpaDerivedCounters() = default;

    /// @brief Obtains the number of derived counters.
    ///
    /// @return The number of derived counters.
    virtual GpaUInt32 GetNumCounters() const;

    /// @brief Gets a counter's name.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's name.
    virtual const char* GetCounterName(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].counter_name_;
    }

    /// @brief Gets a counter's group name.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's group name.
    virtual const char* GetCounterGroup(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].counter_group_;
    }

    /// @brief Gets a counter's description.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's description.
    virtual const char* GetCounterDescription(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].counter_description_;
    }

    /// @brief Gets a counter's usage type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's usage type.
    virtual GpaUsageType GetCounterUsageType(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].usage_type_;
    }

    /// @brief Gets a counter's data type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's data type.
    virtual GpaDataType GetCounterDataType(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].data_type_;
    }

    /// @brief Gets a counter's UUID.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's UUID.
    virtual GpaUuid GetCounterUuid(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].uuid_;
    }

    /// @brief Gets a counter's supported sample type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's supported sample types (a combination of GpaCounterSampleBits).
    virtual GpaCounterSampleType GetCounterSampleType(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());

        // TODO: Hardcoding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for public counters to specify which sample types they support.

        //return pass_counter_list[index].supported_sample_types_;
        UNREFERENCED_PARAMETER(index);
        return kGpaCounterSampleTypeDiscrete;
    }

    /// @brief Defines a public counter based on an expression.
    ///
    /// @param [in] counter_name The name of the counter.
    /// @param [in] counter_group The group that the counter is related to.
    /// @param [in] counter_description The description of the counter.
    /// @param [in] data_type The data type of the counter.
    /// @param [in] usage_type The usage type of the counter.
    /// @param [in] internal_counters_required The list of required internal counters.
    /// @param [in] compute_expression The compute expression of the counter.
    /// @param [in] uuid UUID string that uniquely and consistently identifies the counter.
    virtual void DefineDerivedCounter(const char*        counter_name,
                                      const char*        counter_group,
                                      const char*        counter_description,
                                      GpaDataType        data_type,
                                      GpaUsageType       usage_type,
                                      vector<GpaUInt32>& internal_counters_required,
                                      const char*        compute_expression,
                                      const char*        uuid);

    /// @brief Updates an existing derived counter based on ASIC-specific registers.
    ///
    /// @param [in] counter_name The name of the counter.
    /// @param [in] internal_counters_required The list of required internal counters.
    /// @param [in] compute_expression The compute expression of the counter.
    virtual void UpdateAsicSpecificDerivedCounter(const char* counter_name, vector<GpaUInt32>& internal_counters_required, const char* compute_expression);

    /// @brief Adds a derived counter to the set of available counters.
    ///
    /// @param [in] derived_counter the derived counter to add.
    virtual void AddDerivedCounter(GpaDerivedCounterInfoClass& derived_counter)
    {
        derived_counter_list_.push_back(derived_counter);
    }

    /// @brief Get the counter at the specified index.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter at the specified index.
    virtual const GpaDerivedCounterInfoClass* GetCounter(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return &derived_counter_list_[index];
    }

    /// @brief Clears the list of available counters.
    virtual void Clear();

    /// @brief Gets the list of internal counters that are required for a derived counter.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The list of internal counters.
    virtual const vector<GpaUInt32>& GetInternalCountersRequired(GpaUInt32 index) const
    {
        assert(index < derived_counter_list_.size());
        return derived_counter_list_[index].internal_counters_required_;
    }

    /// @brief Computes a counter's result.
    ///
    /// @param [in] counter_index The index of the counter.
    /// @param [in] results The counter results buffer.
    /// @param [in] internal_counter_types The list of internal counter types.
    /// @param [in] result The result of the computation.
    /// @param [in] hw_info The hardware info for the current hardware.
    ///
    /// @return kGpaStatusOk on success, otherwise an error code.
    virtual GpaStatus ComputeCounterValue(GpaUInt32                       counter_index,
                                          const vector<const GpaUInt64*>& results,
                                          vector<GpaDataType>&            internal_counter_types,
                                          void*                           result,
                                          const GpaHwInfo*                hw_info) const;

    bool counters_generated_;  ///< Indicates that the derived counters have been generated.

protected:
    vector<GpaDerivedCounterInfoClass> derived_counter_list_;  ///< The set of available derived counters.
};

#ifdef AMDT_INTERNAL

struct GpaCounterDesc;
/// @brief Entry point to get internal derived counters.
///
/// @param [in] api_type The API whose counters are needed.
/// @param [in] desired_generation The generation whose counters are needed.
/// @param [out] internal_derived_counters[out] Pointer to array of internal derived counters.
/// @param [out] internal_derived_counter_count Pointer to count of internal derived counters.
///
/// @return internal_derived_counter_count.
GpaStatus GpaGetInternalDerivedCounters(GpaApiType             api_type,
                                        GpaHwGeneration        desired_generation,
                                        const GpaCounterDesc** internal_derived_counters,
                                        size_t*                internal_derived_counter_count);

#endif  // AMDT_INTERNAL

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_DERIVED_COUNTER_H_
