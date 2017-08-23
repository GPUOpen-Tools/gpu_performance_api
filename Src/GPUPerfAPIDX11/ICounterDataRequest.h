//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Interface to a DX11 counter data request
//==============================================================================

#ifndef _I_COUNTER_DATA_REQUEST_H_
#define _I_COUNTER_DATA_REQUEST_H_

#include <vector>

#include "GPUPerfAPITypes.h"

struct GPA_CounterResults; ///< forward declaration
class GPA_ContextState;    ///< forward declaration

using std::vector;

/// Interface to a DX11 counter data request
class ICounterDataRequest
{
public:
    /// Destructor
    virtual ~ICounterDataRequest() {}

    /// Collects the results
    /// \param resultStorage the place to store counter results
    /// \param numActiveCounters the number of active counters
    /// \param sampleId the samplpe id whose results are needed
    ///\return false on failure
    virtual bool CollectResults(GPA_CounterResults& resultStorage, size_t numActiveCounters, gpa_uint32 sampleId) = 0;

    /// Begins the request
    /// \param pContextState the context on which the request is being made
    /// \param selectionID the selection ID of the request
    /// \param pCounters the counters to enable for this request
    ///\return false on failure
    virtual bool BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters) = 0;

    /// Ends the request
    ///\return false on failure
    virtual bool EndRequest() = 0;

    /// Releases the resources associated with the counters
    virtual void ReleaseCounters() = 0;

    /// Reset the counters
    /// \param selectionID the selection ID of the request
    /// \param pCounters the counters to enable for this request
    virtual void Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters) = 0;

protected:
    /// Constuctor
    ICounterDataRequest() {}

private:
    /// Disabled copy constructor
    ICounterDataRequest(const ICounterDataRequest& other) = delete;

    /// Disabled assignment operator
    ICounterDataRequest& operator=(const ICounterDataRequest& other) = delete;
};

#endif _I_COUNTER_DATA_REQUEST_H_
