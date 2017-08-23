//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12CounterDataRequestProxy declaration
//==============================================================================

#ifndef _DX12_COUNTER_DATA_REQUEST_PROXY_H_
#define _DX12_COUNTER_DATA_REQUEST_PROXY_H_

#include "DX12DataRequest.h"

/// \brief Manage a single sample of counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class DX12CounterDataRequestProxy : public DX12DataRequest
{
public:
    /// Construct a GPA counter data request instance
    DX12CounterDataRequestProxy();

    /// Destroy this GPA counter data request instance
    virtual ~DX12CounterDataRequestProxy();

    virtual bool CollectResults(GPA_CounterResults& resultStorage);

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters);

    virtual bool EndRequest();

    virtual void ReleaseCounters();

private:
    DX12DataRequest* m_pDataRequest; ///< The real data request

    /// Copy constructor - private override to disable usage
    DX12CounterDataRequestProxy(const DX12CounterDataRequestProxy& other) = delete;

    /// Move constructor - private override to disable usage
    DX12CounterDataRequestProxy(DX12CounterDataRequestProxy&& other) = delete;

    /// Copy operator - private override to disable usage
    DX12CounterDataRequestProxy& operator=(const DX12CounterDataRequestProxy& other) = delete;

    /// Move operator - private override to disable usage
    DX12CounterDataRequestProxy& operator=(DX12CounterDataRequestProxy&& other) = delete;
};

#endif // _DX12_COUNTER_DATA_REQUEST_PROXY_H_

