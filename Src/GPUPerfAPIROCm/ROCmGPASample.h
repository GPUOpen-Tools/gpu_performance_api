//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  ROCm GPA Sample Header
//==============================================================================

#ifndef _ROCM_GPA_SAMPLE_H_
#define _ROCM_GPA_SAMPLE_H_

#include <vector>

#include "GPASample.h"
#include "ROCmGPAContext.h"

/// Class for ROCm Specific sample
class ROCmGPASample : public GPASample
{
public:

    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    ROCmGPASample(GPAPass* pPass,
                  IGPACommandList* pCmdList,
                  GpaSampleType sampleType,
                  ClientSampleId sampleId);

    /// Delete default constructor
    ROCmGPASample() = delete;

    /// Destructor
    ~ROCmGPASample();

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest() override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

private:

    /// Structure to hold counter config and results.
    /// Passed to the Disaptch and Completion callbacks as user data
    struct DispatchData
    {
        rocprofiler_feature_t* m_pFeatures       = nullptr; ///< rocprofiler feature array
        unsigned               m_featureCount    = 0;       ///< the number of features
        unsigned int           m_groupIndex      = 0;       ///< index of the current group
        rocprofiler_group_t    m_group           = {};      ///< current profiling group
        rocprofiler_t*         m_pContext        = nullptr; ///< current profiling context
        bool                   m_isDataReady     = false;   ///< flag indicating if counter data is ready
        std::vector<uint64_t>  m_counterResults;            ///< vector of counter results
        ROCmGPAContext*        m_pROCmGpaContext = nullptr; ///< the context pointer
    };

    /// Callback function called for each dispatch
    /// \param pCallbackData data provided by roc profiler library
    /// \param pUserData data provided by the user
    /// \param pGroup the rocprofiler group
    /// \return the status of the operation
    static hsa_status_t DispatchCallback(const rocprofiler_callback_data_t* pCallbackData,
                                         void* pUserData,
                                         rocprofiler_group_t* pGroup);

    /// Callback function called when queues are destroyed
    /// \return the status of the operation
    static hsa_status_t QueueDestroyCallback(hsa_queue_t*, void*);

    /// Callback function called when each dispatch is complete
    /// \param group the rocprofiler group
    /// \param pUserData data provided by the user
    static bool DispatchCompletionCallback(rocprofiler_group_t group, void* pUserData);

    /// Release allocated counters
    void DestroyBlockCounters();

    /// Helper fucntion to build the counter name string expected by the rocprofiler library
    /// \param pGroupName the counter block name
    /// \param blockIndex the counter block instance
    /// \param counterIndexInGroup the counter index within it's group (the event id)
    /// \return a countername string formatted for the rocprofiler library
    std::string GetRocmProfilerCounterName(const char* pGroupName, gpa_uint32 blockInstance, gpa_uint64 counterIndexInGroup) const;

    ROCmGPAContext*          m_pROCmGpaContext; ///< Cache the context pointer
    DispatchData*            m_pDispatchData;   ///< The dispatch data for this sample
    std::vector<std::string> m_rocmCounters;    ///< List of ROCProfiler counters for this sample
};

#endif  // _ROCM_GPA_SAMPLE_H_
