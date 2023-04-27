//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief An accessor interface for the GpaCounterGeneratorBase class.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_ACCESSOR_INTERFACE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_ACCESSOR_INTERFACE_H_

#include <cstdint>
#include <vector>

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

struct GpaHardwareCounterDescExt;
class GpaHwInfo;
class GpaHardwareCounters;
class GpaSoftwareCounters;
class GpaDerivedCounterInfoClass;
class GpaCounterResultLocation;

/// @brief Indicates the source or origin of a counter.
enum class GpaCounterSource : uint32_t
{
    kUnknown,   ///< Invalid or unknown counter.
    kPublic,    ///< Counter is defined by GPA using other Hardware counters or hardware info.
    kHardware,  ///< Counter comes from the hardware.
};

/// @brief Stores the source of the counter and its local index into that family of counters.
struct GpaCounterSourceInfo
{
    GpaUInt32        local_counter_index;  ///< The local index of the counter.
    GpaCounterSource counter_source;       ///< The source of the counter.

    /// @brief Sets the data for the counter source info.
    ///
    /// @param [in] local_index The local index of the counter.
    /// @param [in] source The source of the counter.
    void Set(GpaUInt32 local_index, GpaCounterSource source)
    {
        local_counter_index = local_index;
        counter_source      = source;
    }
};

/// @brief An accessor interface for the GpaCounterGeneratorBase class.
class IGpaCounterAccessor
{
public:
    /// @brief Set the flags indicating which counters are allowed.
    ///
    /// @param [in] allow_public_counters Flag indicating whether or not public counters are allowed.
    /// @param [in] allow_hardware_counters Flag indicating whether or not hardware counters are allowed.
    virtual void SetAllowedCounters(bool allow_public_counters, bool allow_hardware_counters) = 0;

    /// @brief Get the number of available counters.
    ///
    /// @return The number of available counters.
    virtual GpaUInt32 GetNumCounters() const = 0;

    /// @brief Gets a counter's name.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The counter name.
    virtual const char* GetCounterName(GpaUInt32 index) const = 0;

    /// @brief Gets the category of the specified counter.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The category of the specified counter.
    virtual const char* GetCounterGroup(GpaUInt32 index) const = 0;

    /// @brief Gets a counter's description.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The counter description.
    virtual const char* GetCounterDescription(GpaUInt32 index) const = 0;

    /// @brief Gets the data type of a public counter.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The data type of the the desired counter.
    virtual GpaDataType GetCounterDataType(GpaUInt32 index) const = 0;

    /// @brief Gets the usage type of a public counter.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The usage of the the desired counter.
    virtual GpaUsageType GetCounterUsageType(GpaUInt32 index) const = 0;

    /// @brief Gets a counter's UUID.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The counter UUID.
    virtual GpaUuid GetCounterUuid(GpaUInt32 index) const = 0;

    /// @brief Gets the supported sample type of a counter.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumCounters().
    ///
    /// @return The counter's supported sample type.
    virtual GpaCounterSampleType GetCounterSampleType(GpaUInt32 index) const = 0;

    /// @brief Gets a public counter.
    ///
    /// @param [in] index The index of the public counter to return.
    ///
    /// @return A public counter.
    virtual const GpaDerivedCounterInfoClass* GetPublicCounter(GpaUInt32 index) const = 0;

    /// @brief Gets a hardware counter.
    ///
    /// @param [in] index The index of a hardware counter to return.
    ///
    /// @return A hardware counter.
    virtual const GpaHardwareCounterDescExt* GetHardwareCounterExt(GpaUInt32 index) const = 0;

    /// @brief Gets the number of public counters available.
    ///
    /// @return The number of public counters.
    virtual GpaUInt32 GetNumPublicCounters() const = 0;

    /// @brief Gets the internal counters required for the specified public counter index.
    ///
    /// @param [in] index The index of a public counter.
    ///
    /// @return A vector of internal counter indices.
    virtual std::vector<GpaUInt32> GetInternalCountersRequired(GpaUInt32 index) const = 0;

    /// @brief Computes a public counter value based on supplied results and hardware info.
    ///
    /// @param [in] counter_index The public counter index to calculate.
    /// @param [in] results A vector of hardware counter results.
    /// @param [in] internal_counter_types A vector of counter types.
    /// @param [in,out] result The computed counter result.
    /// @param [in] hardware_info Information about the hardware on which the result was generated.
    ///
    /// @return kGpaStatusOk on success, otherwise an error code.
    virtual GpaStatus ComputePublicCounterValue(GpaUInt32                            counter_index,
                                                const std::vector<const GpaUInt64*>& results,
                                                std::vector<GpaDataType>&            internal_counter_types,
                                                void*                                result,
                                                const GpaHwInfo*                     hardware_info) const = 0;

    /// @brief Compute a software counter value.
    ///
    /// @param [in] software_counter_index The index of the counter (within the range of software counters) whose value is needed.
    /// @param [in] value The value of the counter.
    /// @param [out] result The resulting value.
    /// @param [in] hw_info The hardware info.
    virtual void ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const = 0;

    /// @brief Gets the counter type information based on the global counter index.
    ///
    /// @param [in] global_index The index into the main list of counters.
    ///
    /// @return The info about the counter.
    virtual GpaCounterSourceInfo GetCounterSourceInfo(GpaUInt32 global_index) const = 0;

    /// @brief Gets a counter's index.
    ///
    /// @param [in] counter_name The name of a counter.
    /// @param [out] counter_index The index of the counter.
    ///
    /// @return True if the counter is found, false otherwise.
    virtual bool GetCounterIndex(const char* counter_name, GpaUInt32* counter_index) const = 0;

    /// @brief Gets a counter index.
    ///
    /// @param [in] gpa_hardware_block hardware block.
    /// @param [in] block_instance instance of the block.
    /// @param [in] block_event_id event id of the counter in the block.
    /// @param [in] gpa_shader_mask shader mask, used if SQ hardware block is used.
    /// @param [out] counter_index index of the counter.
    ///
    /// @return True if the counter is found, false otherwise.
    virtual bool GetCounterIndex(const GpaHwBlock&    gpa_hardware_block,
                                 const GpaUInt32&     block_instance,
                                 const GpaUInt32&     block_event_id,
                                 const GpaShaderMask& gpa_shader_mask,
                                 GpaUInt32*           counter_index) const = 0;

    /// @brief Returns the publicly-exposed index of the hardware counter with the specified index.
    ///
    /// @param [in] hardware_counter_index hardware counter index.
    /// @param [out] public_interface_counter_index publicly-exposed counter index.
    ///
    /// @return True if successful otherwise false.
    virtual bool GetPublicInterfaceCounterIndex(const GpaUInt32& hardware_counter_index, GpaUInt32* public_interface_counter_index) const = 0;

    /// @brief Get the hardware counters.
    ///
    /// @return The hardware counters.
    virtual const GpaHardwareCounters* GetHardwareCounters() const = 0;

    /// @brief Get the counter info.
    ///
    /// @param [in] counter_index Public counter index.
    ///
    /// @return kGpaStatusOk on success otherwise an error code.
    virtual GpaCounterInfo* GetCounterInfo(const GpaUInt32& counter_index) const = 0;

    /// @brief Virtual destructor.
    virtual ~IGpaCounterAccessor() = default;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_ACCESSOR_INTERFACE_H_
