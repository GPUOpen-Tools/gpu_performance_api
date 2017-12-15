//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  The OpenCL Data request class
//==============================================================================

#ifndef _CL_COUNTER_DATA_REQUEST_H_
#define _CL_COUNTER_DATA_REQUEST_H_

#include "GPUPerfAPICL.h"

//-----------------------------------------------------------------------------
/// CLCounter Struct
/// structure used to store data that is needed to retrieve and store the
/// results for a counter.
//-----------------------------------------------------------------------------
struct CLCounter
{
    /// Initializes a new CLCounter object
    CLCounter()
    {
        uCounterID          = 0;
        uCounterGroup       = 0;
        uCounterIndex       = 0;
        bCounterResultReady = false;
    }

    gpa_uint32 uCounterID;        ///< ID that is calculated in the CounterDefinition files
    gpa_uint32 uCounterGroup;     ///< group that this counter is in
    gpa_uint32 uCounterIndex;     ///< index to this counter within its group
    bool bCounterResultReady;     ///< indicates whether the result has been stored in the pCounterResult buffer
};

//-----------------------------------------------------------------------------
/// CLCounterDataRequest class
/// this class is responsible for enabling, disabling, and gathering all the
/// counter results for a single request.
//-----------------------------------------------------------------------------
class CLCounterDataRequest : public GPA_DataRequest
{
public:
    /// Initializes a new CLCounterDataRequest object
    CLCounterDataRequest();

    /// Destructor
    ~CLCounterDataRequest();

    /// mechanism to permit reuse of resources
    /// selected counters may not have changed, so can just use query resources again
    /// \param selectionID the ID of the counter selection
    /// \param pCounters the list of counters
    void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

protected:

    /// Start a counter sample.
    /// Begin must handle the case where a request is reused
    /// try and reuse resources if selectionID matches (which means the same counters are activated).
    /// \param pContextState pointer to object containing the context information for this request
    /// \param pSampleList the sample list where sampling is being started
    /// \param selectionID the ID of the counter selection
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    virtual bool BeginRequest(GPA_ContextState* pContextState, void* pSampleList, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters) override;

    /// Ends a counter sample.
    /// \return True on success; false on error.
    virtual bool EndRequest() override;

    /// Collects the results if they are available.
    /// \param[out] resultStorage
    /// \return true if the results were collected; false if they are not available.
    virtual bool CollectResults(GPASampleResult& resultStorage) override;

    /// Release allocated counters
    virtual void ReleaseCounters() override;

    /// Deletes counter block objects
    void DeleteCounterBlocks();

    /// Obtains the index of the specified group ID
    /// \param uBlockID [out] the index of the block
    /// \param uGroupID the ID of the group to find.
    /// \return True if the group was found, false otherwise.
    bool FindBlockID(gpa_uint32& uBlockID, gpa_uint32 uGroupID);

    gpa_uint32 m_uCounterSelectionID;   ///< the id of the set of active counters
    CLCounter* m_counters;              ///< store the counters' data

    std::vector<clPerfCounterBlock*> m_clCounterBlocks; ///< store the data to interface with opencl counters per HW block
    std::vector<cl_perfcounter_amd> m_pclCounters;      ///< store the opencl counters
    cl_event m_clEvent;                                 ///< cl event to synchronize the counters

    gpa_uint32 m_uDataReadyCount;       ///< number of counters with data ready

private:

    /// Release allocated counters for CL Data Request
    void ReleaseCountersInCLDataRequest();
};

#endif // _CL_COUNTER_DATA_REQUEST_H_
