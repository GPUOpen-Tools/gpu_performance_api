//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkDataRequest declaration
//==============================================================================

#ifndef _VK_DATA_REQUEST_H_
#define _VK_DATA_REQUEST_H_

#include <GPADataRequest.h>

/// Vk counter data request
///
/// An intermediate Vk data request interface to enable using the proxy design pattern
class VkDataRequest : public GPA_DataRequest
{
public:
    /// Destroy this Vk counter data request instance
    virtual ~VkDataRequest();

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionID,
        const vector<gpa_uint32>* pCounters) override
        = 0;

    virtual bool EndRequest() override = 0;

    virtual void ReleaseCounters() override = 0;

    /// Get the number of active counters
    /// \return Get number of active counters
    size_t GetActiveCountersCount() const;

protected:
    /// Construct a Vk counter data request instance
    VkDataRequest();

    /// Set the number of active counters
    /// \param[in] activeCountersCount The number of active counters
    void SetActiveCountersCount(const size_t activeCountersCount);

private:
    /// Copy constructor - private override to disable usage
    VkDataRequest(const VkDataRequest& other) = delete;

    /// Move constructor - private override to disable usage
    VkDataRequest(VkDataRequest&& other) = delete;

    /// Copy operator - private override to disable usage
    VkDataRequest& operator=(const VkDataRequest& other) = delete;

    /// Move operator - private override to disable usage
    VkDataRequest& operator=(VkDataRequest&& other) = delete;

};

#endif // _VK_DATA_REQUEST_H_
