//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Class to manage the resources used for VK SW queries
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERY_GROUP_H_
#define GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERY_GROUP_H_

#include <map>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_vk/vk_software_counters_results.h"

/// @brief Class to manage the resources used for Vk SW queries.
///
/// In Vulkan, a VkQueryPool can contain a bunch of queries all of the same type.
/// This class will manage a group of VkQueryPools, one pool for each type of query
/// that is available.
/// For each "sample" from GPA, a new query from one (or more) of the query pools
/// will be needed, depending on what counters (ie, queries) are enabled by GPA.
/// The "queryId" that is available from this class is somewhat arbitrary
/// (it's taken from GPA DX12).
class VkCommandListSWQueryGroup
{
public:
    /// @brief Construct a VkCommandListSWQueryGroup instance.
    VkCommandListSWQueryGroup();

    /// @brief Move constructor.
    ///
    /// @param [in] other The command list moved.
    VkCommandListSWQueryGroup(VkCommandListSWQueryGroup&& other);

    /// @brief Destroy this VkCommandListSWQueryGroup.
    ~VkCommandListSWQueryGroup();

    /// @brief Move operator.
    ///
    /// @param [in] other The command list moved.
    ///
    /// @return Reference to this VkCommandListSWQueryGroup.
    VkCommandListSWQueryGroup& operator=(VkCommandListSWQueryGroup&& other);

    /// @brief Initialize the VkCommandListSWQueryGroup instance resources.
    ///
    /// @param [in] physical_device The physical device that the device is from.
    /// @param [in] device The device queries are executed on.
    /// @param [in] command_list The command list the queries are excuted on.
    /// @param [in] group_size The number of queries/results in this group.
    ///
    /// @return True if initialization succeeded, false if it failed.
    bool Initialize(VkPhysicalDevice physical_device, VkDevice device, VkCommandBuffer command_list, size_t group_size);

    /// @brief Cleanup the VkCommandListSwQueries instance resources.
    void Cleanup();

    /// @brief Get the active sample count for this group.
    ///
    /// @return The number of active samples in this group.
    GpaUInt32 GetSampleCount() const;

    /// @brief Increments the sample count for this group.
    void BeginSwSample();

    /// @brief Signals the end of sample event and copies the results into the results buffer.
    ///
    /// @see GetSwSampleResults
    ///
    /// @param [in] sw_sample_index The SW sample Index within this group.
    void EndSwSample(const GpaUInt32 sw_sample_index);

    /// @brief Clears the results buffer for this sample, and decrements the sample count for this group.
    ///
    /// @param [in] sw_sample_index The SW sample Index within this group.
    void ReleaseSwSample(const GpaUInt32 swSampleIndex);

    /// @brief Begin single SW query sampling.
    ///
    /// @param [in] sw_sample_index The SW sample Index within this group.
    /// @param [in] query_type The query type.
    ///
    /// @return True if sampling started, false if not.
    void BeginSwQuery(const GpaUInt32 sw_sample_index, const GpaVkSwQueryType query_type);

    /// @brief End single SW query sampling.
    ///
    /// @param [in] sw_sample_index The SW sample Index within this group.
    /// @param [in] query_type The query type.
    void EndSwQuery(const GpaUInt32 sw_sample_index, const GpaVkSwQueryType query_type);

    /// @brief Get SW sample results.
    ///
    /// @param [in] sw_sample_index The SW sample Index within this group.
    /// @param [out] query_results The SW countes results.
    ///
    /// @return True if results are avilable, false if results are not available.
    bool GetSwSampleResults(const GpaUInt32 sw_sample_index, GpaVkSoftwareQueryResults& query_results);

private:
    /// @brief Copy constructor - private override to prevent usage.
    VkCommandListSWQueryGroup(const VkCommandListSWQueryGroup&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return reference to object.
    VkCommandListSWQueryGroup& operator=(const VkCommandListSWQueryGroup&) = delete;

    /// @brief Create SW queries of the given type.
    ///
    /// @param [in] device The device the pool is created on.
    /// @param [in] query_type The SW query type of the pool.
    ///
    /// @return True if query pool creation succeeded, false if it failed.
    bool CreateSwQueryPool(VkDevice device, const GpaVkSwQueryType query_type);

    /// Associates the query types to a VkQueryType.
    static const VkQueryType kQueryTypes[kGpaVkQueryTypeCount];

    /// Indicates which query types are enabled by the user for each sample.
    std::map<GpaUInt32, bool[kGpaVkQueryTypeCount]> active_sample_queries_;

    size_t                     max_samples_;                        ///< The max number of samples that this group can hold.
    GpaUInt32                  active_sample_count_;                ///< The number of active samples in this group.
    VkDevice                   device_;                             ///< The device these queries are created on.
    VkCommandBuffer            command_buffer_;                     ///< The command list that queries and counters are inserted to.
    GpaVkSoftwareQueryResults* queries_results_;                    ///< SW queries results.
    VkQueryPool                query_pools_[kGpaVkQueryTypeCount];  ///< A QueryPool for each query type.
};

#endif  // GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERY_GROUP_H_