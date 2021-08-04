//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vk Sample implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_sample.h"

#include "gpu_perf_api_vk/vk_gpa_command_list.h"

VkGpaSample::VkGpaSample(GpaPass* pass, IGpaCommandList* command_list, GpaSampleType sample_type, unsigned int sample_id)
    : GpaSample(pass, command_list, sample_type, sample_id)
{
    vk_gpa_command_list_ = static_cast<VkGpaCommandList*>(command_list);
}