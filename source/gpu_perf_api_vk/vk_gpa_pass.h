//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vulkan GPA Pass Object Header
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_PASS_H_
#define GPU_PERF_API_VK_VK_GPA_PASS_H_

#include "gpu_perf_api_common/gpa_pass.h"

#include "gpu_perf_api_vk/vk_includes.h"

class VkGpaCommandList;

/// @brief Vulkan-specific GPA Pass.
class VkGpaPass : public GpaPass
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    /// @param [in] pass_index Pass index.
    /// @param [in] counter_source Counter source.
    /// @param [in] pass_counters Counter list for the pass.
    VkGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// @brief Delete default constructor.
    VkGpaPass() = delete;

    /// @brief Destructor.
    virtual ~VkGpaPass() = default;

    /// @copydoc GpaPass::CreateApiSpecificSample(IGpaCommandList*, GpaSampleType, unsigned int)
    GpaSample* CreateApiSpecificSample(IGpaCommandList* command_list, GpaSampleType sample_type, unsigned int sample_id) override final;

    /// @copydoc GpaPass::CreateApiSpecificCommandList(void*, CommandListId, GpaCommandListType)
    IGpaCommandList* CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType command_type) override final;

    /// @copydoc GpaPass::EndSample(IGpaCommandList*)
    bool EndSample(IGpaCommandList* command_list) override final;

    /// @brief Copies samples from secondary command buffer to primary command buffer.
    ///
    /// @param [in] secondary_vk_gpa_command_list The secondary command buffer from which to copy samples.
    /// @param [in] primary_vk_gpa_command_list The primary command buffer to which to copy samples.
    /// @param [in] num_samples The number of samples to copy.
    /// @param [out] new_sample_ids The array of sample ids.
    ///
    /// @return True is the copy operation is successful.
    bool CopySecondarySamples(VkGpaCommandList* secondary_vk_gpa_command_list,
                              VkGpaCommandList* primary_vk_gpa_command_list,
                              GpaUInt32         num_samples,
                              GpaUInt32*        new_sample_ids);

    /// @brief Accessor to the VkGpaSampleBeginInfoAMD struct that should be used for all samples created in this pass.
    ///
    /// @return Const pointer to the VkGpaSampleBeginInfoAMD struct which enables counters for this pass.
    const VkGpaSampleBeginInfoAMD* GetVkSampleBeginInfo() const;

private:
    /// @brief Initializes the sample config for the pass if pass counter source is hardware.
    void InitializeSampleConfig();

    /// AMD Extension struct to specify the counters in each sample. This will be the same for each sample within this pass.
    VkGpaSampleBeginInfoAMD sample_begin_info_amd_;

    /// Indicates that the sample_begin_info_amd_ struct has been initialized.
    bool is_sample_begin_info_initialized_;

    /// Stores the enabled counter Ids so that the each sample within the pass can reference them.
    std::vector<VkGpaPerfCounterAMD> counter_ids_;
};

#endif  // GPU_PERF_API_VK_VK_GPA_PASS_H_