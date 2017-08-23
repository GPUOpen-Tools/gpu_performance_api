//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of SW counters
//==============================================================================

#ifndef _VK_SOFTWARE_COUNTER_DATA_REQUEST_H_
#define _VK_SOFTWARE_COUNTER_DATA_REQUEST_H_

#include <vector>
#include <vulkan.h>

#include "VkDataRequest.h"
#include "VkSoftwareCountersResults.h"
#include "GPAContextStateVk.h"

/// Manage a single sample of SW counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkSoftwareCounterDataRequest : public VkDataRequest
{
public:
    /// Construct a Vk SW counter data request
    VkSoftwareCounterDataRequest();

    /// Destroy this Vk SW counter data request
    virtual ~VkSoftwareCounterDataRequest();

    virtual bool CollectResults(GPA_CounterResults& resultStorage) override;

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionId,
        const vector<gpa_uint32>* pCounters) override;

    virtual bool EndRequest() override;

    virtual void ReleaseCounters() override;

private:
    /// Struct to describe active counter
    struct ActiveCounter
    {
        gpa_uint32 m_index;               ///< index of counter
        GPA_VK_SW_QUERY_TYPE m_queryType; ///< query type of counter
    };

    typedef std::vector<ActiveCounter> ActiveCounterListType; ///< Typedef for a list of counters

    static const gpa_uint32 ms_unitializedSampleId = 0xFFFFFFFF; ///< Value of an uninitialized sample id

    GPA_ContextStateVk* m_pContextState; ///< The context the SW data request is executed on
    ActiveCounterListType m_activeCountersList; ///< The list of active counters
    unsigned int m_activeQueries; ///< The list of active queries
    VkCommandBuffer m_commandList; ///< The command list the data request is executed on
    gpa_uint32 m_swSampleId; ///< The SW sample ID executed on the context
    VkQueryPool m_queryPool; ///< The query pool that stores all the query results

    /// Copy constructor - private override to disable usage
    VkSoftwareCounterDataRequest(const VkSoftwareCounterDataRequest&) = delete;

    /// Move constructor - private override to disable usage
    VkSoftwareCounterDataRequest(VkSoftwareCounterDataRequest&&) = delete;

    /// Copy operator - private override to disable usage
    VkSoftwareCounterDataRequest& operator=(const VkSoftwareCounterDataRequest&) = delete;

    /// Move operator - private override to disable usage
    VkSoftwareCounterDataRequest& operator=(VkSoftwareCounterDataRequest&&) = delete;

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

};

#endif // _VK_SOFTWARE_COUNTER_DATA_REQUEST_H_

