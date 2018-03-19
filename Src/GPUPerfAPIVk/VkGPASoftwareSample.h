//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of SW counters
//==============================================================================

#ifndef _VK_GPA_SOFTWARE_SAMPLE_H_
#define _VK_GPA_SOFTWARE_SAMPLE_H_

#include <vector>
#include <vulkan.h>

#include "VkGPASample.h"
#include "VkSoftwareCountersResults.h"
#include "VkGPAContext.h"
#include "VkCommandListSwQueries.h"

/// Manage a single sample of SW counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkGPASoftwareSample : public VkGPASample
{
public:
    /// Constructor
    /// \param[in] pPass pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleId sample Id
    VkGPASoftwareSample(GPAPass* pPass,
                        IGPACommandList* pCmdList,
                        unsigned int sampleId);

    /// Destructor
    virtual ~VkGPASoftwareSample();

    /// Assigns the already-initialized queries to the software sample.
    /// Needed because Vulkan requires that the queries be reset at the
    /// very beginning of the command buffer, and at that time we don't
    /// know if there will be any samples on the command list, so we
    /// initialize them anyway, and assign the queries to the sample
    /// prior to GPASample::Begin() being called.
    /// \param pSwQueries Pointer to the VkCommandListSwQueries object
    ///        that contains all the query pools and queries.
    void AssignQueries(VkCommandListSwQueries* pSwQueries);

    /// \copydoc VkGPASample::BeginRequest()
    virtual bool BeginRequest() override final;

    /// \copydoc VkGPASample::EndRequest()
    virtual bool EndRequest() override final;

    /// \copydoc VkGPASample::ReleaseCounters
    virtual void ReleaseCounters() override final;

    /// Default Constructor deleted
    VkGPASoftwareSample() = delete;

private:
    /// Struct to describe active counter
    struct ActiveCounter
    {
        gpa_uint32 m_index;               ///< index of counter
        GPA_VK_SW_QUERY_TYPE m_queryType; ///< query type of counter
    };

    typedef std::vector<ActiveCounter> ActiveCounterListType; ///< Typedef for a list of counters

    static const gpa_uint32 ms_unitializedSampleId = 0xFFFFFFFF; ///< Value of an uninitialized sample id

    /// Copy constructor - private override to disable usage
    VkGPASoftwareSample(const VkGPASoftwareSample&) = delete;

    /// Move constructor - private override to disable usage
    VkGPASoftwareSample(VkGPASoftwareSample&&) = delete;

    /// Copy operator - private override to disable usage
    /// \return reference to object
    VkGPASoftwareSample& operator=(const VkGPASoftwareSample&) = delete;

    /// Move operator - private override to disable usage
    /// \return reference to object
    VkGPASoftwareSample& operator=(VkGPASoftwareSample&&) = delete;

    /// Get counter result for a counter derived from a timestamp query
    /// \return True if counter results were collected, false if not
    /// \param[in] queryResults The SW queries results
    /// \param[in] counterIndex The counter index
    /// \param[out] counterResult Counter result
    bool GetTimestampQueryCounterResult(
        const GpaVkSoftwareQueryResults& queryResults,
        const gpa_uint32 counterIndex,
        gpa_uint64& counterResult) const;

    /// Get counter result for a counter derived from the pipeline statistics query
    /// \return True if counter results were collected, false if not
    /// \param[in] queryResults The SW queries results
    /// \param[in] counterIndex The counter index
    /// \param[out] counterResult Counter result
    bool GetPipelineQueryCounterResult(
        const GpaVkSoftwareQueryResults& queryResults,
        const gpa_uint32 counterIndex,
        gpa_uint64& counterResult) const;

    /// \copydoc VkGPASample::UpdateResults()
    virtual bool UpdateResults() override;

    VkGPAContext*           m_pContextState;      ///< The context the SW Sample is executed on
    ActiveCounterListType   m_activeCountersList; ///< The list of active counters
    unsigned int            m_activeQueries;      ///< The number of active queries
    VkCommandBuffer         m_commandList;        ///< The command list the sample is executed on
    gpa_uint32              m_swSampleId;         ///< The SW sample ID executed on the context
    VkCommandListSwQueries* m_pSwQueries;         ///< The Software queries being used by this sample
};

#endif // _VK_GPA_SOFTWARE_SAMPLE_H_

