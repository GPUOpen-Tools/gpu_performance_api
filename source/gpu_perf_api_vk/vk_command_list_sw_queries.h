//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VkCommandListSwQueries declaration
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERIES_H_
#define GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERIES_H_

#include <vector>

#include "gpu_perf_api_vk/vk_command_list_sw_query_group.h"

/// @brief Container for SW queries and resources executed on a command buffer.
///
/// This class keeps a queryGroup (a set of all query types) for each sample,
/// since there can be multiple query types for a single GPA-level sample.
class VkCommandListSwQueries
{
public:
    /// @brief Construct a VkCommandListSwQueries instance.
    VkCommandListSwQueries();

    /// @brief Move constructor.
    ///
    /// @param [in] other The command list moved.
    VkCommandListSwQueries(VkCommandListSwQueries&& other);

    /// @brief Destroy this VkCommandListSwQueries.
    ~VkCommandListSwQueries();

    /// @brief Move operator.
    ///
    /// @param [in] other The command list moved.
    ///
    /// @return Reference to this VkCommandListSwQueries.
    VkCommandListSwQueries& operator=(VkCommandListSwQueries&& other);

    /// @brief Initialize the VkCommandListSwQueries instance resources.
    ///
    /// @param [in] physical_device The physical device that the device is from.
    /// @param [in] device The device Queries are executed on.
    /// @param [in] command_buffer The Command list the queries are executed on.
    ///
    /// @return True if initialization succeeded, false if it failed.
    bool Initialize(VkPhysicalDevice physical_device, VkDevice device, VkCommandBuffer command_buffer);

    /// @brief Acquire a sample ID.
    ///
    /// @param [out] sw_sample_id The SW sample ID - unique to the context.
    ///
    /// @return True if sampling started, false if not.
    bool BeginSwSample(GpaUInt32& sw_sample_id);

    /// @brief Signal the end of sample event.
    ///
    /// @see GetSwSampleResults
    ///
    /// @param [in] sw_sample_id The SW sample ID.
    void EndSwSample(const GpaUInt32 sw_sample_id);

    /// @brief Release the given SW sample.
    ///
    /// @param [in] sw_sample_id The SW sample ID.
    void ReleaseSwSample(const GpaUInt32 sw_sample_id);

    /// @brief Begin single SW query sampling.
    ///
    /// @param [in] sw_sample_id The SW sample ID.
    /// @param [in] query_type The query type.
    ///
    /// @return True if sampling started, false if not.
    void BeginSwQuery(const GpaUInt32 sw_sample_id, const GpaVkSwQueryType query_type);

    /// @brief End single SW query sampling.
    ///
    /// @param [in] sw_sample_id The SW sample ID.
    /// @param [in] query_type The query type.
    void EndSwQuery(const GpaUInt32 sw_sample_id, const GpaVkSwQueryType query_type);

    /// @brief Get SW sample results.
    ///
    /// @param [in] sw_sample_id The SW sample ID.
    /// @param [out] query_results The SW countes results.
    ///
    /// @return True if results are available, false if results are not available.
    bool GetSwSampleResults(const GpaUInt32 sw_sample_id, GpaVkSoftwareQueryResults& query_results);

private:
    /// @brief Copy constructor - private override to prevent usage.
    VkCommandListSwQueries(const VkCommandListSwQueries&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return reference to object.
    VkCommandListSwQueries& operator=(const VkCommandListSwQueries&) = delete;

    static const size_t kResultGroupSize = 256;  ///< The number of results to store in a group (additional samples will require an additional group).

    VkPhysicalDevice          physical_device_;  ///< The physical device that the device is from.
    VkCommandBuffer           command_buffer_;   ///< The command buffer queries and counters are inserted to.
    VkDevice                  device_;           ///< The device which created the command buffer.
    VkCommandListSWQueryGroup query_group_;      ///< The query group for this command buffer.
};

#endif  // GPU_PERF_API_VK_VK_COMMAND_LIST_SW_QUERIES_H_
