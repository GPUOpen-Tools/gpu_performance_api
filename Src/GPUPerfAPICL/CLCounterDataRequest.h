//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  The OpenCL Data request class
//==============================================================================

#ifndef _CL_COUNTER_DATA_REQUEST_H_
#define _CL_COUNTER_DATA_REQUEST_H_

#include "../GPUPerfAPI-Common/GPUPerfAPIImp.h"
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
    void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

protected:

    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);
    virtual bool EndRequest();
    virtual bool CollectResults(GPA_CounterResults& resultStorage);
    virtual void ReleaseCounters();

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
};

#endif // _CL_COUNTER_DATA_REQUEST_H_
