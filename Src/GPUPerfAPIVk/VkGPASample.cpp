//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vk Sample implementation
//==============================================================================

#include "VkGPASample.h"
#include "VkGPACommandList.h"

VkGPASample::VkGPASample(GPAPass* pPass, IGPACommandList* pCmdList, GpaSampleType sampleType, unsigned int sampleId)
    : GPASample(pPass, pCmdList, sampleType, sampleId)
{
    m_pVkGpaCmdList = static_cast<VkGPACommandList*>(pCmdList);
}
