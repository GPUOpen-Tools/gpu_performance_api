//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the resources used for VK SW queries
//==============================================================================

#ifndef _VK_COMMAND_LIST_SW_QUERY_GROUP_H_
#define _VK_COMMAND_LIST_SW_QUERY_GROUP_H_

#include "GPUPerfAPITypes.h"
#include "VkSoftwareCountersResults.h"
#include <map>

/// Class to manage the resources used for Vk SW queries.
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
    /// Construct a VkCommandListSWQueryGroup instance
    VkCommandListSWQueryGroup();

    /// Move constructor
    ///
    /// \param[in] other The command list moved
    VkCommandListSWQueryGroup(VkCommandListSWQueryGroup&& other);

    /// Destroy this VkCommandListSWQueryGroup
    ~VkCommandListSWQueryGroup();

    /// Move operator
    ///
    /// \return Reference to this VkCommandListSWQueryGroup
    /// \param[in] other The command list moved
    VkCommandListSWQueryGroup& operator=(VkCommandListSWQueryGroup&& other);

    /// Initialize the VkCommandListSWQueryGroup instance resources
    ///
    /// \return True if initialization succeeded, false if it failed
    /// \param physicalDevice The physical device that the device is from
    /// \param device The device queries are executed on
    /// \param commandList The command list the queries are excuted on
    /// \param groupSize The number of queries/results in this group
    bool Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandBuffer commandList, size_t groupSize);

    /// Cleanup the VkCommandListSwQueries instance resources
    void Cleanup();

    /// Get the active sample count for this group
    ///
    /// \return the number of active samples in this group
    gpa_uint32 GetSampleCount() const;

    /// Begin SW sample
    ///
    /// Increments the sample count for this group
    void BeginSwSample();

    /// End SW sample
    ///
    /// Signals the end of sample event and copies the results into the results buffer
    /// \see GetSwSampleResults
    /// \param[in] swSampleIndex The SW sample Index within this group
    void EndSwSample(const gpa_uint32 swSampleIndex);

    /// Release the given SW sample.
    ///
    /// Clears the results buffer for this sample, and decrements the sample count for this group
    /// \param[in] swSampleIndex The SW sample Index within this group
    void ReleaseSwSample(const gpa_uint32 swSampleIndex);

    /// Begin single SW query sampling
    ///
    /// \return True if sampling started, false if not
    /// \param[in] swSampleIndex The SW sample Index within this group
    /// \param[in] queryType The query type
    void BeginSwQuery(const gpa_uint32 swSampleIndex, const GPA_VK_SW_QUERY_TYPE queryType);

    /// End single SW query sampling
    ///
    /// \param[in] swSampleIndex The SW sample Index within this group
    /// \param[in] queryType The query type
    void EndSwQuery(const gpa_uint32 swSampleIndex, const GPA_VK_SW_QUERY_TYPE queryType);

    /// Get SW sample results
    ///
    /// \return True if results are avilable, false if results are not available
    /// \param[in] swSampleIndex The SW sample Index within this group
    /// \param[out] queryResults The SW countes results
    bool GetSwSampleResults(const gpa_uint32 swSampleIndex, GpaVkSoftwareQueryResults& queryResults);

private:
    /// Copy constructor - private override to prevent usage
    VkCommandListSWQueryGroup(const VkCommandListSWQueryGroup&) = delete;

    /// Copy operator - private override to prevent usage
    /// \return reference to object
    VkCommandListSWQueryGroup& operator=(const VkCommandListSWQueryGroup&) = delete;

    /// Create SW queries of the given type
    ///
    /// \return True if query pool creation succeeded, false if it failed
    /// \param device The device the pool is created on
    /// \param queryType The SW query type of the pool
    bool CreateSwQueryPool(VkDevice device, const GPA_VK_SW_QUERY_TYPE queryType);

    /// Associates the query types to a VkQueryType
    static const VkQueryType ms_queryTypes[GPA_VK_QUERY_TYPE_COUNT];

    /// Indicates which query types are enabled by the user for each sample.
    std::map<gpa_uint32, bool[GPA_VK_QUERY_TYPE_COUNT]> m_activeSampleQueries;

    size_t                        m_maxSamples;                          ///< The max number of samples that this group can hold
    gpa_uint32                    m_activeSampleCount;                   ///< The number of active samples in this group
    VkDevice                      m_device;                              ///< The device these queries are created on
    VkCommandBuffer               m_commandBuffer;                       ///< The command list that queries and counters are inserted to
    GpaVkSoftwareQueryResults*    m_pQueriesResults;                     ///< SW queries results
    VkQueryPool                   m_queryPools[GPA_VK_QUERY_TYPE_COUNT]; ///< A QueryPool for each query type
};

#endif // _VK_COMMAND_LIST_SW_QUERY_GROUP_H_
