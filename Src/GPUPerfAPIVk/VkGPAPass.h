//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan GPA Pass Object Header
//==============================================================================

#ifndef _VK_GPA_PASS_H_
#define _VK_GPA_PASS_H_

#include "GPAPass.h"
#include <vulkan.h>
#include <vk_amd_gpa_interface.h>

// forward declaration
class VkGPACommandList;

/// Vulkan-specific GPA Pass
class VkGPAPass : public GPAPass
{
public:

    /// Default constructor is deleted.
    VkGPAPass() = delete;

    /// Constructor
    VkGPAPass(IGPASession* pGpaSession,
              PassIndex passIndex,
              GPACounterSource counterSource,
              IGPACounterScheduler* pCounterScheduler,
              const IGPACounterAccessor* pCounterAccessor);

    /// Destructor
    virtual ~VkGPAPass();

    /// \copydoc GPAPass::CreateAPISpecificSample()
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList, GpaSampleType sampleType, unsigned int sampleId) override final;

    /// \copydoc GPAPass::CreateCommandList
    IGPACommandList* CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pVkGpaCmdList) override final;

    bool CopySecondarySamples(VkGPACommandList* pSecondaryVkGPACmdList,
        VkGPACommandList* pPrimaryVkGPACmdList,
        gpa_uint32 numSamples,
        gpa_uint32* pNewSampleIds);

private:

    /// Initializes the sample config for the pass if pass counter source is hardware
    void InitializeSampleConfig();

    VkGpaSampleBeginInfoAMD     m_sampleBeginInfoAMD;           ///< AMD Extension struct to specify the counters in each sample. This will be the same for each sample within this pass.
    bool                        m_isSampleBeginInfoInitialized; ///< Indicates that the m_sampleBeginInfoAMD struct has been initialized.
};

#endif //_VK_GPA_PASS_H_
