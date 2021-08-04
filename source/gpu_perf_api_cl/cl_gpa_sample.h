//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  CL GPA Sample Header
//==============================================================================

#ifndef _CL_GPA_SAMPLE_H_
#define _CL_GPA_SAMPLE_H_

#include <vector>

#include "gpa_sample.h"
#include "cl_gpa_context.h"
#include "cl_perf_counter_block.h"

/// Class for CL Specific sample
class ClGpaSample : public GpaSample
{
public:
    /// Constructor
    /// @param [in] pass GPA Pass object
    /// @param [in] cmd_list gpa command list
    /// @param [in] sample_type gpa sample type
    /// @param [in] sample_id user-supplied sample id
    ClGpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id);

    /// Delete default constructor
    ClGpaSample() = delete;

    /// Destructor
    ~ClGpaSample();

    /// @copydoc GpaSample::UpdateResults
    bool UpdateResults() override final;

    /// @copydoc GpaSample::BeginRequest
    bool BeginRequest() override final;

    /// @copydoc GpaSample::EndRequest
    bool EndRequest() override final;

    /// @copydoc GpaSample::ReleaseCounters
    void ReleaseCounters() override final;

private:
    /// Obtains the index of the specified group ID
    /// @param block_id [out] the index of the block
    /// @param group_id the ID of the group to find.
    /// @return True if the group was found, false otherwise.
    bool FindBlockId(GpaUInt32& block_id, GpaUInt32 group_id);

    /// Deletes counter block objects
    void DeleteCounterBlocks();

    /// Release allocated counters
    void ReleaseBlockCounters();

    /// structure used to store data that is needed to retrieve and store the results for a counter
    struct ClCounter
    {
        /// Constructor
        ClCounter() = default;

        /// Destructor
        ~ClCounter() = default;

        GpaUInt32 counter_id              = 0;      ///< ID that is calculated in the CounterDefinition files
        GpaUInt32 counter_group           = 0;      ///< group that this counter is in
        GpaUInt32 counter_index           = 0;      ///< index to this counter within its group
        bool      is_counter_result_ready = false;  ///< indicates whether the result has been stored in the pCounterResult buffer
    };

    ClGpaContext* cl_gpa_context_;  ///< Cache the context pointer
    ClCounter*    cl_counters_;     ///< store the counters' data

    std::vector<ClPerfCounterBlock*> cl_counter_blocks_;  ///< store the data to interface with opencl counters per HW block
    std::vector<cl_perfcounter_amd>  cl_counter_list_;    ///< store the opencl counters
    cl_event                         cl_event_;           ///< cl event to synchronize the counters

    GpaUInt32 data_ready_count_;  ///< number of counters with data ready
};

#endif  // _CL_GPA_SAMPLE_H_
