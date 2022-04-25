//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Class to manage a single sample of HW counters
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_HARDWARE_SAMPLE_H_
#define GPU_PERF_API_VK_VK_GPA_HARDWARE_SAMPLE_H_

#include <vector>

#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_gpa_sample.h"
#include "gpu_perf_api_vk/vk_includes.h"

/// @brief Contains the list of enabled counters in the sample.
/// Can detect when counter results are available.
/// Give access to counter results.
class VkGpaHardwareSample : public VkGpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] pass Pass object.
    /// @param [in] cmd_list Gpa command list.
    /// @param [in] sample_id Sample Id.
    /// @param [in] device Vk device.
    VkGpaHardwareSample(GpaPass* pas, IGpaCommandList* cmd_list, unsigned int sample_id, VkDevice device);

    /// @brief Destructor.
    virtual ~VkGpaHardwareSample();

    /// @copydoc VkGpaSample::BeginRequest()
    virtual bool BeginRequest() override final;

    /// @copydoc VkGpaSample::EndRequest()
    virtual bool EndRequest() override final;

    /// @copydoc VkGpaSample::ReleaseCounters()
    virtual void ReleaseCounters() override;

    /// @copydoc VkGpaSample::UpdateResults()
    virtual bool UpdateResults() override;

private:
    /// @brief Copy constructor - private override to disable usage.
    VkGpaHardwareSample(const VkGpaHardwareSample&) = delete;

    /// @brief Move constructor - private override to disable usage.
    VkGpaHardwareSample(VkGpaHardwareSample&&) = delete;

    /// @brief Copy operator - private override to disable usage.
    ///
    /// @return reference to object.
    VkGpaHardwareSample& operator=(const VkGpaHardwareSample&) = delete;

    /// @brief Move operator - private override to disable usage.
    ///
    /// @return reference to object.
    VkGpaHardwareSample& operator=(VkGpaHardwareSample&&) = delete;

    /// @brief Populates the sample result from the driver data. Should only be called after it is confirmed that the results are available in the driver.
    ///
    /// @return Pointer to the member variable that contains the results; should never be NULL.
    GpaSampleResult* PopulateSampleResults();

    /// @brief Returns the result from the driver.
    ///
    /// @param [in] sample_data_size Size of result for the sample in bytes.
    /// @param [in,out] result_buffer Pointer to the buffer where result will be copied.
    ///
    /// @return True if copying of data was successful otherwise false.
    bool CopyResult(size_t sample_data_size, void* result_buffer) const;

    VkGpaSessionAMD gpa_session_;                ///< The underlying driver extension session that this sample is on.
    GpaUInt32       num_counters_;               ///< Number of counters in this sample.
    uint32_t        sample_index_;               ///< Index of the sample being measured.
    VkDevice        device_;                     ///< The device on which the counters are being collected.
    VkCommandBuffer command_buffer_;             ///< The command buffer for this sample.
    bool            has_any_hardware_counters_;  ///< Flag indicating if there are any non-skipped hardware counters in this request.
};

#endif  // GPU_PERF_API_VK_VK_GPA_HARDWARE_SAMPLE_H_
