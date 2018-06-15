//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#ifndef _VK_GPA_HARDWARE_SAMPLE_H_
#define _VK_GPA_HARDWARE_SAMPLE_H_

#include <vector>
#include <vulkan/vulkan.h>
#include <vk_amd_gpa_interface.h>

#include "VkGPASample.h"
#include "VkGPAContext.h"

/// Manage a single sample of HW counters
///
/// Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkGPAHardwareSample : public VkGPASample
{
public:

    /// Constructor
    /// \param[in] pPass pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleId sample Id
    /// \param[in] device vk device
    VkGPAHardwareSample(GPAPass* pPass,
                        IGPACommandList* pCmdList,
                        unsigned int sampleId,
                        VkDevice device);

    /// Destructor
    virtual ~VkGPAHardwareSample();

    /// \copydoc VkGPASample::BeginRequest
    virtual bool BeginRequest() override final;

    /// \copydoc VkGPASample::EndRequest
    virtual bool EndRequest() override final;

    /// \copydoc VkGPASample::ReleaseCounters
    virtual void ReleaseCounters() override;

    /// \copydoc VkGPASample::UpdateResults()
    virtual bool UpdateResults() override;

private:

    /// Copy constructor - private override to disable usage
    VkGPAHardwareSample(const VkGPAHardwareSample&) = delete;

    /// Move constructor - private override to disable usage
    VkGPAHardwareSample(VkGPAHardwareSample&&) = delete;

    /// Copy operator - private override to disable usage
    /// \return reference to object
    VkGPAHardwareSample& operator=(const VkGPAHardwareSample&) = delete;

    /// Move operator - private override to disable usage
    /// \return reference to object
    VkGPAHardwareSample& operator=(VkGPAHardwareSample&&) = delete;

    /// Populates the sample result from the driver data.
    /// Should only be called after it is confirmed that the results are available in the driver.
    /// \return Pointer to the member variable that contains the results; should never be NULL.
    GPASampleResult* PopulateSampleResults();

    /// Returns the result from the driver
    /// \param[in] sampleDataSize size of result for the sample in bytes
    /// \param[in, out] pResultBuffer pointer to the buffer where result will be copied
    /// \return true if copying of data was successful otherwise false
    bool CopyResult(size_t sampleDataSize, void* pResultBuffer) const;

    VkGpaSessionAMD m_gpaSession;             ///< The underlying driver extension session that this sample is on.
    gpa_uint32      m_numCounters;            ///< number of counters in this sample
    uint32_t        m_sampleIndex;            ///< index of the sample being measured
    VkDevice        m_device;                 ///< The device on which the counters are being collected
    VkCommandBuffer m_commandBuffer;          ///< the command buffer for this sample
    bool            m_hasAnyHardwareCounters; ///< flag indicating if there are any non-skipped hardware counters in this request
};

#endif // _VK_GPA_HARDWARE_SAMPLE_H_
