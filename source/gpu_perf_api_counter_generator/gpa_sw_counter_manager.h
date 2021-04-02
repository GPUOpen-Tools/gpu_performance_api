//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class to manage the D3D11 Query-based software counters.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SW_COUNTER_MANAGER_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SW_COUNTER_MANAGER_H_

#include <vector>
#include <set>
#include <unordered_map>

#include "TSingleton.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

/// @brief Enum for the D3D11 query counters.
enum class D3DCounters : GpaUInt32
{
    kGpuTime,
    kOcclusion,
    kIaVertices,
    kIaPrimitives,
    kVsInvocations,
    kGsInvocations,
    kGsPrimitives,
    kCInvocations,
    kCPrimitives,
    kPsInvocations,
    kHsInvocations,
    kDsInvocations,
    kCsInvocations,
    kOcclusionPredicate,
    kSoPrimsWritten,
    kSoPrimsStorageNeed,
    kSoOverFlowPred,
    kPrimsWrittenS0,
    kPrimsStorageNeedS0,
    kOverFlowPredS0,
    kPrimsWrittenS1,
    kPrimsStorageNeedS1,
    kOverFlowPredS1,
    kPrimsWrittenS2,
    kPrimsStorageNeedS2,
    kOverFlowPredS2,
    kPrimsWrittenS3,
    kPrimsStorageNeedS3,
    kOverFlowPredS3
};

typedef std::vector<GpaSoftwareCounterDesc>      SwCounterDescVec;     ///< Typedef for a list of software counters.
typedef std::set<GpaUInt32>                      EnabledSwCounterSet;  ///< Typedef for a set of enabled counters.
typedef std::unordered_map<GpaUInt32, GpaUInt32> CounterIndexMap;      ///< Typedef for a map of counter indices.

/// @brief Singleton wrapper class for DX11 SW counters.
class SwCounterManager : public TSingleton<SwCounterManager>
{
public:
    /// @brief Default constructor.
    SwCounterManager();

    /// @brief Virtual destructor.
    virtual ~SwCounterManager();

    /// @brief Generate a SW counter.
    ///
    /// @param [in] counter_desc Reference to the GPA_SoftwareCounterDesc to generate.
    void AddSwCounter(const GpaSoftwareCounterDesc& counter_desc);

    /// @brief Check if DX11 SW counters have been generated.
    ///
    /// @return True if DX11 SW counters generated.
    bool SwCountersGenerated() const;

    /// @brief Set SW counters generating status.
    ///
    /// @param [in] set The status of SW counter generation to be set.
    void SetSwCountersGenerated(const bool set);

    /// @brief Check if any SW counter is enabled.
    ///
    /// @return True if SW counters enabled.
    bool SwCounterEnabled() const;

    /// @brief Clear enabled SW counters.
    void ClearEnabledSwCounters();

    /// @brief Get SW counter list.
    ///
    /// @return A pointer to SwCounterDescVec.
    const SwCounterDescVec* GetSwCounters() const;

    /// @brief Get the number of SW counters.
    ///
    /// @return Number of SW counters.
    GpaUInt32 GetNumSwCounters() const;

    /// @brief Enable SW counter.
    ///
    /// @param [in] index The public index of the SW counter to be enabled.
    void EnableSwCounter(const GpaUInt32 index);

    /// @brief Disable SW counter.
    ///
    /// @param [in] index The public index of the SW counter to be disabled.
    void DisableSwCounter(GpaUInt32 index);

    /// @brief Map public counter index and SW counter index.
    ///
    /// @param [in] pub_index The public index of the SW counter.
    /// @param [in] sw_index The SW index of the SW counter.
    void AddSwCounterMap(const GpaUInt32 pub_index, const GpaUInt32 sw_index);

    /// @brief Set SW GPUTime counter public index.
    ///
    /// @param [in] pub_index The public index to set.
    void SetSwGpuTimeCounterIndex(const GpaUInt32 pub_index);

    /// @brief Get SW GPUTime counter public index.
    ///
    /// @return SW GPUTime counter public index.
    GpaUInt32 GetSwGpuTimeCounterIndex() const;

    /// @brief Set SW GPUTime counter enabled status.
    ///
    /// @param [in] enabled The status to set.
    void SetSwGpuTimeCounterEnabled(const bool enabled);

    /// @brief Get SW GPUTime counter enabled status.
    ///
    /// @return sw_gpu_time_enabled_.
    bool SwGpuTimeCounterEnabled() const;

    /// @brief Get public counter index of SW counter from SW counter map.
    ///
    /// @param [in] sw_index The SW index of the SW counter.
    ///
    /// @return Public counter index.
    GpaUInt32 GetSwCounterPubIndex(const GpaUInt32 sw_index) const;

    /// @brief Clear sw_counter_index_map_.
    void ClearSwCounterMap();

    /// @brief Set number of AMD counters.
    ///
    /// @param [in] counters Number of total AMD counters.
    void SetNumAmdCounters(const GpaUInt32 counters);

    /// @brief Get the number of AMD counters.
    ///
    /// @return Number of AMD counters.
    GpaUInt32 GetNumAmdCounters() const;

    /// @brief Get enabled SW counter list.
    ///
    /// @return A pointer to  enabledSwCounterSet.
    const EnabledSwCounterSet* GetEnabledSwCounters() const;

private:
    /// @brief Disable copy constructor.
    SwCounterManager(const SwCounterManager&) = delete;

    /// @brief Disable copy assignment operator.
    ///
    /// @return Reference to object.
    SwCounterManager& operator=(SwCounterManager&) = delete;

    SwCounterDescVec    sw_counters_;            ///< Vector containing SW D3D11 counters.
    EnabledSwCounterSet enabled_sw_counters_;    ///< Set of currently enabled SW D3D11 counters(ids).
    GpaUInt32           amd_counters_;           ///< Number of AMD counters.
    CounterIndexMap     sw_counter_index_map_;   ///< SW counter public index, SW index map.
    GpaUInt32           sw_gpu_time_counter_;    ///< SW GPUTime counter public index.
    bool                sw_gpu_time_enabled_;    ///< Indicates if SW GPUTime counter is enabled.
    bool                sw_counters_generated_;  ///< Indicates if SW counters have been generated.
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SW_COUNTER_MANAGER_H_
