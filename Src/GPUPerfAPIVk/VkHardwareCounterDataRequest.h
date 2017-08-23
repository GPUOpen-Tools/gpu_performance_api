//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#ifndef _VK_HARDWARE_COUNTER_DATA_REQUEST_H_
#define _VK_HARDWARE_COUNTER_DATA_REQUEST_H_

#include <vector>
#include <vulkan.h>

#include "VkDataRequest.h"
#include "GPAContextStateVk.h"

/// Manage a single sample of HW counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkHardwareCounterDataRequest : public VkDataRequest
{
public:
    /// Construct a Vk HW counter data request
    VkHardwareCounterDataRequest(VkDevice device);

    /// Destroy this Vk HW counter data request
    virtual ~VkHardwareCounterDataRequest();

    virtual bool CollectResults(GPA_CounterResults& resultStorage) override;

    virtual bool BeginRequest(
        GPA_ContextState* pContextState,
        void* pSampleList,
        gpa_uint32 selectionId,
        const vector<gpa_uint32>* pCounters) override;

    virtual bool EndRequest() override;

    virtual void ReleaseCounters() override;

private:

    /// Copy constructor - private override to disable usage
    VkHardwareCounterDataRequest(const VkHardwareCounterDataRequest&) = delete;

    /// Move constructor - private override to disable usage
    VkHardwareCounterDataRequest(VkHardwareCounterDataRequest&&) = delete;

    /// Copy operator - private override to disable usage
    VkHardwareCounterDataRequest& operator=(const VkHardwareCounterDataRequest&) = delete;

    /// Move operator - private override to disable usage
    VkHardwareCounterDataRequest& operator=(VkHardwareCounterDataRequest&&) = delete;

    GPA_ContextStateVk*          m_pContextState;   ///< the context state that owns this request
    VkGpaPerfCounterAMD*         m_pCounterIds;     ///< ids of the counters in this request
    gpa_uint32                   m_numCounters;     ///< number of counters in this request
    uint32_t                     m_sampleIndex;     ///< index of the sample being measured
    VkDevice                     m_device;          ///< The device on which the counters are being collected
    VkCommandBuffer              m_commandBuffer;   ///< the command buffer for this request
    bool                         m_isTimingRequest; ///< flag indicating if this request is a timing request
};

#endif // _VK_HARDWARE_COUNTER_DATA_REQUEST_H_
