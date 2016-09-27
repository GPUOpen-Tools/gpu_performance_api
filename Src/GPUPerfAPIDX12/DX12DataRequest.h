//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12DataRequest declaration
//==============================================================================

#ifndef _DX12_DATA_REQUEST_H_
#define _DX12_DATA_REQUEST_H_

#include <GPADataRequest.h>

/// DX12 counter data request
///
/// An intermediate DX12 data request interface to enable using the proxy design pattern
class DX12DataRequest : public GPA_DataRequest
{
public:
    /// Destroy this DX12 counter data request instance
    virtual ~DX12DataRequest();

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters)
        = 0;

    virtual bool EndRequest() = 0;

    virtual void ReleaseCounters() = 0;

    /// Get the number of active counters
    /// \return Get number of active counters
    size_t GetActiveCountersCount() const;

protected:
    /// Construct a DX12 counter data request instance
    DX12DataRequest();

    /// Set the number of active counters
    /// \param[in] activeCountersCount The number of active counters
    void SetActiveCountersCount(const size_t activeCountersCount);

private:
    /// Copy constructor - private override to disable usage
    DX12DataRequest(const DX12DataRequest& other) = delete;

    /// Move constructor - private override to disable usage
    DX12DataRequest(DX12DataRequest&& other) = delete;

    /// Copy operator - private override to disable usage
    DX12DataRequest& operator=(const DX12DataRequest& other) = delete;

    /// Move operator - private override to disable usage
    DX12DataRequest& operator=(DX12DataRequest&& other) = delete;

}; // end of class DX12DataRequest

#endif // _DX12_DATA_REQUEST_H_
