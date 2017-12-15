//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Pass Object Header
//==============================================================================

#ifndef _DX11_GPA_PASS_H_
#define _DX11_GPA_PASS_H_

// GPA Common
#include "GPAPass.h"
#include "IGPACommandList.h"

class DX11GPACommandList;               // forward declaration

/// Class for DirectX 11 gpa pass
class DX11GPAPass : public GPAPass
{
public:

    /// Constructor
    DX11GPAPass(IGPASession* pGpaSession,
                PassIndex passIndex,
                GPACounterSource counterSource,
                IGPACounterScheduler* pCounterScheduler,
                IGPACounterAccessor* pCounterAccessor);

    /// \copydoc GPAPass::CreateAPISpecificSample
    GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                       GpaSampleType sampleType,
                                       ClientSampleId clientSampleId) override final;

    /// \copydoc GPAPass::ContinueSample
    bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList) override final;

    /// \copydoc GPAPass::UpdateResults
    bool UpdateResults() override final;

    /// \copydoc GPAPass::CreateCommandList
    IGPACommandList* CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType) override final;

    /// Destructor
    ~DX11GPAPass();
};

#endif // _DX11_GPA_PASS_H_
