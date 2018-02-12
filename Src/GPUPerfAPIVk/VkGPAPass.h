//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
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
    virtual ~VkGPAPass() = default;

    /// \copydoc GPAPass::CreateAPISpecificSample()
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       unsigned int sampleId) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd,
                                                  CommandListId commandListId,
                                                  GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pVkGpaCmdList) override final;

    // TODO: Doxygen
    bool CopySecondarySamples(VkGPACommandList* pSecondaryVkGPACmdList,
                              VkGPACommandList* pPrimaryVkGPACmdList,
                              gpa_uint32 numSamples,
                              gpa_uint32* pNewSampleIds);

    /// Accessor to the VkGpaSampleBeginInfoAMD struct that should be used for all samples created in this pass.
    /// \return Const pointer to the VkGpaSampleBeginInfoAMD struct which enables counters for this pass.
    const VkGpaSampleBeginInfoAMD* GetVkSampleBeginInfo() const;

private:

    /// Initializes the sample config for the pass if pass counter source is hardware
    void InitializeSampleConfig();

    VkGpaSampleBeginInfoAMD             m_sampleBeginInfoAMD;           ///< AMD Extension struct to specify the counters in each sample. This will be the same for each sample within this pass.
    bool                                m_isSampleBeginInfoInitialized; ///< Indicates that the m_sampleBeginInfoAMD struct has been initialized.
    std::vector<VkGpaPerfCounterAMD>    m_counterIds;                   ///< Stores the enabled counter Ids so that the each sample within the pass can reference them.
};

#endif //_VK_GPA_PASS_H_
