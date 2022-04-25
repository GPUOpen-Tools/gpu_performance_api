//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VkGpaSample declaration
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_SAMPLE_H_
#define GPU_PERF_API_VK_VK_GPA_SAMPLE_H_

#include "gpu_perf_api_common/gpa_sample.h"

class VkGpaCommandList;

/// @brief Vulkan-specific GPA Sample.
///
/// An intermediate Vk Sample interface to enable using the proxy design pattern.
class VkGpaSample : public GpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] pass Gpa Pass object.
    /// @param [in] cmd_list Gpa command list.
    /// @param [in] sample_type Gpa sample type.
    /// @param [in] sample_id User-supplied sample id.
    VkGpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, unsigned int sample_id);

    /// @brief Destroy this Vk counter data request instance.
    virtual ~VkGpaSample() = default;

    /// @copydoc GpaSample::UpdateResults()
    virtual bool UpdateResults() override = 0;

protected:
    /// @copydoc GpaSample::BeginRequest()
    virtual bool BeginRequest() override = 0;

    /// @copydoc GpaSample::EndRequest()
    virtual bool EndRequest() override = 0;

    /// @copydoc GpaSample::ReleaseCounters()
    virtual void ReleaseCounters() override = 0;

    /// @brief Vulkan-Specific GPACommandList.
    VkGpaCommandList* vk_gpa_command_list_;

private:
    /// @brief Delete default constructor.
    VkGpaSample() = delete;

    /// @brief Copy constructor - private override to disable usage.
    VkGpaSample(const VkGpaSample&) = delete;

    /// @brief Move constructor - private override to disable usage.
    VkGpaSample(VkGpaSample&&) = delete;

    /// @brief Copy operator - private override to disable usage.
    ///
    /// @return Reference to object
    VkGpaSample& operator=(const VkGpaSample&) = delete;

    /// @brief Move operator - private override to disable usage.
    ///
    /// @return Reference to object
    VkGpaSample& operator=(VkGpaSample&&) = delete;
};

#endif  // GPU_PERF_API_VK_VK_GPA_SAMPLE_H_
