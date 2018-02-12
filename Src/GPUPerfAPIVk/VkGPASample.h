//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkGPASample declaration
//==============================================================================

#ifndef _VK_GPA_SAMPLE_H_
#define _VK_GPA_SAMPLE_H_

#include "GPASample.h"

// Predeclared class
class VkGPACommandList;

/// Vulkan-specific GPA Sample
///
/// An intermediate Vk Sample interface to enable using the proxy design pattern
class VkGPASample : public GPASample
{
public:
    /// Constructor
    /// \param[in] pPass GPA Pass object
    /// \param[in] pCmdList gpa command list
    /// \param[in] sampleType gpa sample type
    /// \param[in] sampleId user-supplied sample id
    VkGPASample(GPAPass* pPass,
                IGPACommandList* pCmdList,
                GpaSampleType sampleType,
                unsigned int sampleId);

    /// Destroy this Vk counter data request instance
    virtual ~VkGPASample() = default;

    /// \copydoc GPASample::UpdateResults()
    virtual bool UpdateResults() override = 0;

protected:
    /// \copydoc GPASample::BeginRequest()
    virtual bool BeginRequest() override = 0;

    /// \copydoc GPASample::EndRequest()
    virtual bool EndRequest() override = 0;

    /// \copydoc GPASample::ReleaseCounters()
    virtual  void ReleaseCounters() override = 0;

    /// Vulkan-Specific GPACommandList
    VkGPACommandList* m_pVkGpaCmdList;

private:
    /// Default Constructor is deleted
    VkGPASample() = delete;

    /// Copy constructor - private override to disable usage
    VkGPASample(const VkGPASample& other) = delete;

    /// Move constructor - private override to disable usage
    VkGPASample(VkGPASample&& other) = delete;

    /// Copy operator - private override to disable usage
    VkGPASample& operator=(const VkGPASample& other) = delete;

    /// Move operator - private override to disable usage
    VkGPASample& operator=(VkGPASample&& other) = delete;
};

#endif // _VK_GPA_SAMPLE_H_
