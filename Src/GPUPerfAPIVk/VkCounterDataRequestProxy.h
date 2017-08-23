//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief VKCounterDataRequestProxy declaration
//==============================================================================

#ifndef _VK_COUNTER_DATA_REQUEST_PROXY_H_
#define _VK_COUNTER_DATA_REQUEST_PROXY_H_

#include "VkDataRequest.h"

/// \brief Manage a single sample of counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkCounterDataRequestProxy : public VkDataRequest
{
public:
    /// Construct a GPA counter data request instance
    VkCounterDataRequestProxy();

    /// Destroy this GPA counter data request instance
    virtual ~VkCounterDataRequestProxy();

    virtual bool CollectResults(GPA_CounterResults& resultStorage) override;

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters) override;

    virtual bool EndRequest() override;

    virtual void ReleaseCounters() override;

private:
    VkDataRequest* m_pDataRequest; ///< The real data request

    /// Copy constructor - private override to disable usage
    VkCounterDataRequestProxy(const VkCounterDataRequestProxy& other) = delete;

    /// Move constructor - private override to disable usage
    VkCounterDataRequestProxy(VkCounterDataRequestProxy&& other) = delete;

    /// Copy operator - private override to disable usage
    VkCounterDataRequestProxy& operator=(const VkCounterDataRequestProxy& other) = delete;

    /// Move operator - private override to disable usage
    VkCounterDataRequestProxy& operator=(VkCounterDataRequestProxy&& other) = delete;
};

#endif // _VK_COUNTER_DATA_REQUEST_PROXY_H_

