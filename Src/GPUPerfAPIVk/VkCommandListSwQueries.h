//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkCommandListSwQueries declaration
//==============================================================================

#ifndef _VK_COMMAND_LIST_SW_QUERIES_H_
#define _VK_COMMAND_LIST_SW_QUERIES_H_

#include <vector>

#include "VkCommandListSWQueryGroup.h"

/// Container for SW queries and resources executed on a command buffer.
/// This class keeps a queryGroup (a set of all query types) for each sample,
/// since there can be multiple query types for a single GPA-level sample.
class VkCommandListSwQueries
{
public:
    /// Construct a VkCommandListSwQueries instance
    VkCommandListSwQueries();

    /// Move constructor
    ///
    /// \param[in] other The command list moved
    VkCommandListSwQueries(VkCommandListSwQueries&& other);

    /// Destroy this VkCommandListSwQueries
    ~VkCommandListSwQueries();

    /// Move operator
    ///
    /// \return Reference to this VkCommandListSwQueries
    /// \param[in] other The command list moved
    VkCommandListSwQueries& operator=(VkCommandListSwQueries&& other);

    /// Initialize the VkCommandListSwQueries instance resources
    ///
    /// \return True if initialization succeeded, false if it failed
    /// \param physicalDevice The physical device that the device is from
    /// \param device The device queries are executed on
    /// \param commandBuffer The command list the queries are excuted on
    bool Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandBuffer commandBuffer);

    /// Begin SW sample
    ///
    /// Acquire a sample ID
    /// \return True if sampling started, false if not
    /// \param[out] swSampleId The SW sample ID - unique to the context
    bool BeginSwSample(gpa_uint32& swSampleId);

    /// End SW sample
    ///
    /// Signal the end of sample event
    /// \see GetSwSampleResults
    /// \param[in] swSampleId The SW sample ID
    void EndSwSample(const gpa_uint32 swSampleId);

    /// Release the given SW sample.
    ///
    /// \param[in] swSampleId The SW sample ID
    void ReleaseSwSample(const gpa_uint32 swSampleId);

    /// Begin single SW query sampling
    ///
    /// \return True if sampling started, false if not
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void BeginSwQuery(const gpa_uint32 swSampleId, const GPA_VK_SW_QUERY_TYPE queryType);

    /// End single SW query sampling
    ///
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void EndSwQuery(const gpa_uint32 swSampleId, const GPA_VK_SW_QUERY_TYPE queryType);

    /// Get SW sample results
    ///
    /// \return True if results are available, false if results are not available
    /// \param[in] swSampleId The SW sample ID
    /// \param[out] queryResults The SW countes results
    bool GetSwSampleResults(const gpa_uint32 swSampleId, GpaVkSoftwareQueryResults& queryResults);

private:
    /// Copy constructor - private override to prevent usage
    VkCommandListSwQueries(const VkCommandListSwQueries&) = delete;

    /// Copy operator - private override to prevent usage
    /// \return reference to object
    VkCommandListSwQueries& operator=(const VkCommandListSwQueries&) = delete;

    static const size_t ms_resultGroupSize = 256;  ///< The number of results to store in a group (additional samples will require an additional group)

    VkPhysicalDevice          m_physicalDevice;  ///< The physical device that the device is from
    VkCommandBuffer           m_commandBuffer;   ///< The command buffer queries and counters are inserted to
    VkDevice                  m_device;          ///< The device which created the command buffer
    VkCommandListSWQueryGroup m_queryGroup;      ///< The query group for this command buffer
};

#endif  // _VK_COMMAND_LIST_SW_QUERIES_H_
