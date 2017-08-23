//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 Counter Data Request
//==============================================================================

#ifndef _DX11_COUNTER_DATA_REQUEST_H_
#define _DX11_COUNTER_DATA_REQUEST_H_

#include <d3d11.h>
#include "GPUPerfAPIImp.h"
#include "GPUPerfAPIDX11.h"
#include "ICounterDataRequest.h"

/// \brief Maintains the information pertaining to a single sample of counters.
/// Contains the list of enabled counters, can identify when the data is available,
/// and can return the results of the profile sample.
class DX11CounterDataRequest : public GPA_DataRequest
{
public:

    /// Store the counter object we are working with
    ICounterDataRequest* m_pCounterDataRequest;

    /// Initializes a new DX11CounterDataRequest object
    DX11CounterDataRequest();

    /// Destructor
    ~DX11CounterDataRequest();

    /// mechanism to permit reuse of resources
    /// selected counters may not have changed, so can just use query resources again
    /// \param selectionID index of the counter selection to reset
    /// \param pCounters The set of counters to enable in place of the existing ones
    void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);

    virtual bool CollectResults(GPA_CounterResults& resultStorage);

protected:

    virtual bool BeginRequest(GPA_ContextState* pContextState, void* pSampleList, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters);
    virtual bool EndRequest();
    virtual void ReleaseCounters();
};

#endif // _DX11_COUNTER_DATA_REQUEST_H_
