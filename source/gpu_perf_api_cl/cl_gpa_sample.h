//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Sample Header
//==============================================================================

#ifndef _CL_GPA_SAMPLE_H_
#define _CL_GPA_SAMPLE_H_

#include <vector>

#include "gpa_sample.h"
#include "cl_gpa_context.h"
#include "cl_perf_counter_block.h"

/// Class for CL Specific sample
class CLGPASample : public GPASample
{
public:
    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    CLGPASample(GPAPass* pPass, IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId);

    /// Delete default constructor
    CLGPASample() = delete;

    /// Destructor
    ~CLGPASample();

    /// \copydoc GPASample::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPASample::BeginRequest
    bool BeginRequest() override final;

    /// \copydoc GPASample::EndRequest
    bool EndRequest() override final;

    /// \copydoc GPASample::ReleaseCounters
    void ReleaseCounters() override final;

private:
    /// Obtains the index of the specified group ID
    /// \param blockID [out] the index of the block
    /// \param groupID the ID of the group to find.
    /// \return True if the group was found, false otherwise.
    bool FindBlockID(gpa_uint32& blockID, gpa_uint32 groupID);

    /// Deletes counter block objects
    void DeleteCounterBlocks();

    /// Release allocated counters
    void ReleaseBlockCounters();

    /// structure used to store data that is needed to retrieve and store the results for a counter
    struct CLCounter
    {
        /// Initializes a new CLCounter object
        CLCounter() = default;

        /// Destructor
        ~CLCounter() = default;

        gpa_uint32 m_counterID            = 0;      ///< ID that is calculated in the CounterDefinition files
        gpa_uint32 m_counterGroup         = 0;      ///< group that this counter is in
        gpa_uint32 m_counterIndex         = 0;      ///< index to this counter within its group
        bool       m_isCounterResultReady = false;  ///< indicates whether the result has been stored in the pCounterResult buffer
    };

    CLGPAContext* m_pCLGpaContext;  ///< Cache the context pointer
    CLCounter*    m_pClCounters;    ///< store the counters' data

    std::vector<clPerfCounterBlock*> m_clCounterBlocks;  ///< store the data to interface with opencl counters per HW block
    std::vector<cl_perfcounter_amd>  m_clCounterList;    ///< store the opencl counters
    cl_event                         m_clEvent;          ///< cl event to synchronize the counters

    gpa_uint32 m_dataReadyCount;  ///< number of counters with data ready
};

#endif  // _CL_GPA_SAMPLE_H_
