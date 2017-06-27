//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA Counter Data Request
//==============================================================================

#ifndef _HSA_COUNTER_DATA_REQUEST_H_
#define _HSA_COUNTER_DATA_REQUEST_H_

#include "GPUPerfAPIImp.h"
#include "GPUPerfAPIHSA.h"

/// Typedef for a map from counter group index to hsa_ext_tools_counter_block_t
typedef std::map<gpa_uint32, hsa_ext_tools_counter_block_t> HsaCounterGroupMap;

//-----------------------------------------------------------------------------
/// HSACounter Struct
/// structure used to store data that is needed to retrieve and store the
/// results for a counter.
//-----------------------------------------------------------------------------
struct HSACounter
{
    /// Initializes a new instance of the HSACounter class
    HSACounter()
    {
        m_counterID = 0;
        m_counterGroup = 0;
        m_counterIndex = 0;
        m_isCounterValid = false;
        m_isCounterResultReady = false;
        m_hsaPerfCounter = nullptr;
    }

    virtual ~HSACounter() {};

    gpa_uint32              m_counterID;            ///< ID that is calculated in the CounterDefinition files
    gpa_uint32              m_counterGroup;         ///< data type that GL specifies the result will be
    gpa_uint32              m_counterIndex;         ///< index to this counter within its group
    bool                    m_isCounterValid;       ///< indicates whether the counter is a valid counter; if not value will be zero
    bool                    m_isCounterResultReady; ///< indicates whether the result has been stored in the pCounterResult buffer
    hsa_ext_tools_counter_t m_hsaPerfCounter;       ///< Handle to the created HSA perf counter
};


//-----------------------------------------------------------------------------
/// HSACounterDataRequest class
/// this class is responsible for enabling, disabling, and gathering all the
/// counter results for a single request.
//-----------------------------------------------------------------------------
class HSACounterDataRequest : public GPA_DataRequest
{
public:

    /// Initializes a new HSACounterDataRequest object
    HSACounterDataRequest();

    /// Destructor
    ~HSACounterDataRequest();

    /// mechanism to permit reuse of resources
    /// selected counters may not have changed, so can just use query resources again
    /// \param selectionID index of the counter selection to reset
    /// \param pCounters The set of counters to enable in place of the existing ones
    void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

protected:

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters);

    virtual bool EndRequest();

    virtual bool CollectResults(GPA_CounterResults& resultStorage);

    virtual void ReleaseCounters();

protected:
    /// Array of active counters
    HSACounter* m_pCounters;

    /// Number of counters with data ready
    gpa_uint32 m_dataReadyCount;

    /// the id of the set of active counters
    gpa_uint32 m_counterSelectionID;

    /// HSA PMU instance
    hsa_ext_tools_pmu_t m_pmu;

    /// Store the data to interface with HSA counters per HW block
    HsaCounterGroupMap m_hsaGrpIdCtrGrpMap;
};

#endif //_HSA_COUNTER_DATA_REQUEST_H_
