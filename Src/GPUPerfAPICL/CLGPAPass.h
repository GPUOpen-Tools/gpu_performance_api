//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Pass Object Header
//==============================================================================

#ifndef _CL_GPA_PASS_H_
#define _CL_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

/// Class for OpenCL gpa pass
class CLGPAPass : public GPAPass
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pCounterScheduler counter scheduler
    /// \param[in] pCounterAccessor counter accessor
    CLGPAPass(IGPASession* pGpaSession,
              PassIndex passIndex,
              GPACounterSource counterSource,
              IGPACounterScheduler* pCounterScheduler,
              const IGPACounterAccessor* pCounterAccessor);

    /// Destructor
    ~CLGPAPass();

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId clientSampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::CreateCommandList
    IGPACommandList* CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType) override final;

    /// \copydoc GPAPass::EndSample
    bool EndSample(IGPACommandList* pGpaCmdList) override final;
};

#endif // _CL_GPA_PASS_H_
