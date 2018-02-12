//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA GPA Pass Object Header
//==============================================================================

#ifndef _HSA_GPA_PASS_H_
#define _HSA_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

/// Class for HSA gpa pass
class HSAGPAPass : public GPAPass
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pCounterScheduler counter scheduler
    /// \param[in] pCounterAccessor counter accessor
    HSAGPAPass(IGPASession* pGpaSession,
               PassIndex passIndex,
               GPACounterSource counterSource,
               IGPACounterScheduler* pCounterScheduler,
               const IGPACounterAccessor* pCounterAccessor);

    /// Destructor
    ~HSAGPAPass();

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId clientSampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateAPISpecificCommandList
    IGPACommandList* CreateAPISpecificCommandList(void* pCmd,
                                                  CommandListId commandListId,
                                                  GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pGpaCmdList) override final;
};

#endif // _HSA_GPA_PASS_H_
