//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12DataRequest declaration
//==============================================================================

#ifndef _DX12_DATA_REQUEST_H_
#define _DX12_DATA_REQUEST_H_



/// DX12 counter data request
///
/// An intermediate DX12 data request interface to enable using the proxy design pattern
class DX12DataRequest : public GPA_DataRequest
{
public:
    /// Destroy this DX12 counter data request instance
    virtual ~DX12DataRequest() {}

    /// Start a counter sample.
    /// Begin must handle the case where a request is reused
    /// try and reuse resources if selectionID matches (which means the same counters are activated).
    /// \param pContextState pointer to object containing the context information for this request
    /// \param pSampleList the sample list where sampling is being started
    /// \param selectionID the ID of the counter selection
    /// \param pCounters the set of counters to enable
    /// \return True if the sample could be started; false otherwise.
    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters)
        = 0;

    /// Ends a counter sample.
    /// \return True on success; false on error.
    virtual bool EndRequest() = 0;

    /// Release allocated counters
    virtual void ReleaseCounters() = 0;

protected:
    /// Construct a DX12 counter data request instance
    DX12DataRequest() {}

private:
    /// Copy constructor - private override to disable usage
    DX12DataRequest(const DX12DataRequest& other) = delete;

    /// Move constructor - private override to disable usage
    DX12DataRequest(DX12DataRequest&& other) = delete;

    /// Copy operator - private override to disable usage
    DX12DataRequest& operator=(const DX12DataRequest& other) = delete;

    /// Move operator - private override to disable usage
    DX12DataRequest& operator=(DX12DataRequest&& other) = delete;

};

#endif // _DX12_DATA_REQUEST_H_
