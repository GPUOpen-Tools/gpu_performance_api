//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  ROCm GPA Pass Object Header
//==============================================================================

#ifndef _ROCM_GPA_PASS_H_
#define _ROCM_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

/// Class for ROCm gpa pass
class ROCmGPAPass : public GPAPass
{
public:
    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pPassCounters counter list for the pass
    ROCmGPAPass(IGPASession* pGpaSession, PassIndex passIndex, GPACounterSource counterSource, CounterList* pPassCounters);

    /// Destructor
    ~ROCmGPAPass() = default;

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pCmdList) override final;
};

#endif  // _ROCM_GPA_PASS_H_
