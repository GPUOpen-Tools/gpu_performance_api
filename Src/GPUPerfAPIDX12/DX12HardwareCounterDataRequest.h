//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#ifndef _DX12_HARDWARE_COUNTER_DATA_REQUEST_H_
#define _DX12_HARDWARE_COUNTER_DATA_REQUEST_H_

#include <Windows.h>
#include <vector>
#include <D3D12.h>

#include "DX12DataRequest.h"
#include "GPAContextStateDX12.h"

/// Manage a single sample of HW counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class DX12HardwareCounterDataRequest : public DX12DataRequest
{
public:
    /// Construct a DX12 HW counter data request
    DX12HardwareCounterDataRequest();

    /// Destroy this DX12 HW counter data request
    virtual ~DX12HardwareCounterDataRequest();

    /// Collects the results if they are available.
    /// \param[out] resultStorage
    /// \return true if the results were collected; false if they are not available.
    virtual bool CollectResults(GPASampleResult& resultStorage);

    /// Start a counter sample.
    /// Begin must handle the case where a request is reused
    /// try and reuse resources if selectionID matches (which means the same counters are activated).
    /// \param pContextState pointer to object containing the context information for this request
    /// \param pSampleList the sample list where sampling is being started
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        const vector<gpa_uint32>* pCounters);

    /// Ends a counter sample.
    /// \return True on success; false on error.
    virtual bool EndRequest();

    /// Release allocated counters
    virtual void ReleaseCounters();

private:

    /// Copy constructor - private override to disable usage
    DX12HardwareCounterDataRequest(const DX12HardwareCounterDataRequest&) = delete;

    /// Move constructor - private override to disable usage
    DX12HardwareCounterDataRequest(DX12HardwareCounterDataRequest&&) = delete;

    /// Copy operator - private override to disable usage
    DX12HardwareCounterDataRequest& operator=(const DX12HardwareCounterDataRequest&) = delete;

    /// Move operator - private override to disable usage
    DX12HardwareCounterDataRequest& operator=(DX12HardwareCounterDataRequest&&) = delete;

    GPA_ContextStateDX12*        m_pContextState;         ///< the context state that owns this request
    gpa_uint32                   m_numCounters;           ///< number of counters in this request
    UINT32                       m_sampleIndex;           ///< index of the sample being measured
    ID3D12GraphicsCommandListPtr m_commandList;           ///< the command list for this request
    bool                         m_isTimingRequest;       ///< flag indicating if this request is a timing request
    std::list<size_t>            m_skippedCounterIndexes; ///< list of counters which are not valid for the current hardware
};

#endif // _DX12_HARDWARE_COUNTER_DATA_REQUEST_H_
