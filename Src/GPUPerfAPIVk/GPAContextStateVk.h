//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateVk declaration
//==============================================================================

#ifndef _GPA_CONTEXT_STATE_VK_H_
#define _GPA_CONTEXT_STATE_VK_H_

#include <vulkan.h>
#include <unordered_map>
#include <vector>

#include <AMDTMutex.h>
#include <GPAContextState.h>

#include "VkCommandListSwQueries.h"
#include "VkSoftwareCountersResults.h"
#include "VkEntrypoints.h"

/// GPA Vk context state
class GPA_ContextStateVk : public GPA_ContextState
{
public:
    /// Construct a GPA Vk context state instance
    GPA_ContextStateVk();

    /// Destroy this GPA Vk context state instance
    virtual ~GPA_ContextStateVk();

    /// Cleanup Vk GPA context resources
    void Cleanup();

    /// Set the physical device for this context state
    /// \param physicalDevice The Vk physical device that is being used to render and profile
    /// \return GPA_STATUS_OK if device was set correctly and stable clock mode was entered
    GPA_Status SetVkPhysicalDevice(VkPhysicalDevice physicalDevice);

    /// Set the logical device for this context state
    /// \param device The Vk device that is being used to render and profile
    void SetVkDevice(VkDevice device);
    VkDevice GetVkDevice();

    /// Get the time stamp frequencey
    /// \return GPA_STATUS_OK if time stampe frequencey access succeeded, GPA_STATUS_ERROR_FAILED if it failed
    /// \param[out] timestampFrequency The timestamp frequencey
    GPA_Status GetTimestampFrequency(gpa_uint64& timestampFrequency);

    /// Begin sampling on the specified command buffer
    /// \param[in] pCommandBuffer The command buffer that was just begun in the application.
    /// \return GPA_STATUS_OK if session start succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status BeginCommandBuffer(void* pCommandBuffer);

    /// End sampling on the specified command buffer
    /// \param[in] pCommandBuffer The command buffer that is about to end in the application.
    /// \return GPA_STATUS_OK if session end succeeded, GPA_STATUS_ERROR_FAILED if it failed
    GPA_Status EndCommandBuffer(void* pCommandBuffer);

    /// Gets the GpaSession object for the given command list
    /// \param commandBuffer the command buffer whose GpaSession is needed
    /// \param[out] pGpaSession the GpaSession associated with the command buffer
    /// \return true if a GpaSession was found for the command buffer, false otherwise
    bool GetGpaSessionForCommandList(VkCommandBuffer commandBuffer, VkGpaSessionAMD* pGpaSession);

    /// Begin SW sample
    ///
    /// Acquire a sample ID
    /// \return True if sampling started, false if not
    /// \param[in] commandBuffer The command buffer the SW sample (query) the is executed on
    /// \param[out] swSampleId The SW sample ID - unique to the context
    bool BeginSwSample(VkCommandBuffer commandBuffer, gpa_uint32& swSampleId);

    /// End SW sample
    ///
    /// Signal the end of sample event
    /// \see GetSwSampleResults
    /// \param[in] commandBuffer The command buffer the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    void EndSwSample(VkCommandBuffer commandBuffer, const gpa_uint32 swSampleId);

    /// Release the given SW sample.
    /// \param[in] commandBuffer The command buffer the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    void ReleaseSwSample(VkCommandBuffer commandBuffer, const gpa_uint32 swSampleId);

    /// Begin single SW query sampling
    /// \param[in] commandBuffer The command buffer the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void BeginSwQuery(
        VkCommandBuffer commandBuffer,
        const gpa_uint32 swSampleId,
        const GPA_VK_SW_QUERY_TYPE queryType);

    /// End single SW query sampling
    /// \param[in] commandBuffer The command list the SW sample (query) the is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[in] queryType The query type
    void EndSwQuery(
        VkCommandBuffer commandBuffer,
        const gpa_uint32 swSampleId,
        const GPA_VK_SW_QUERY_TYPE queryType);

    /// Get SW sample results
    /// \return True if results are available, false if results are not available
    /// \param[in] commandBuffer The command buffer the SW sample (query) is executed on
    /// \param[in] swSampleId The SW sample ID
    /// \param[out] queryResults The SW counter results
    bool GetSwSampleResults(
        VkCommandBuffer commandBuffer,
        const gpa_uint32 swSampleId,
        GpaVkSoftwareQueryResults& queryResults);

    /// Enable/disable the stable power state
    /// \return GPA_STATUS_OK if stable power is enabled/disabled, GPA_STATUS_ERROR_FAILED if it's not
    /// \param[in] useProfilingClocks true to use GPU clocks for profiling
    GPA_Status SetStableClocks(bool useProfilingClocks);

private:
    typedef std::unordered_map<VkCommandBuffer, VkCommandListSwQueries> CommandBufferQueriesType; ///< Typedef for map from command buffer to queries
    typedef std::unordered_map<VkCommandBuffer, VkGpaSessionAMD> CommandListGpaSessionType; ///< Typedef for map from command buffer to GPASession interface

    CommandListGpaSessionType    m_commandBufferGpaSession; ///< Map from command list to gpa session

    VkPhysicalDevice             m_physicalDevice;              ///< The physical device on which the device was created
    VkDevice                     m_device;                      ///< The device queries and counters are created on
    CommandBufferQueriesType     m_commandBufferQueries;        ///< Map from command buffer to queries
    AMDTMutex                    m_mutex;                       ///< Context access mutex
    VkGpaDeviceClockModeAMD      m_clockMode;                   ///< GPU Clock mode
};

#endif // _GPA_CONTEXT_STATE_VK_H_

