//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Session Implementation
//==============================================================================

#include "DX11GPASession.h"
#include "DX11GPAPass.h"


DX11GPASession::DX11GPASession(
    IGPAContext* pParentContext,
    GPA_Session_Sample_Type sampleType) :
    GPASession(pParentContext, sampleType)
{
}

GPA_API_Type DX11GPASession::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

GPAPass* DX11GPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList* pPassCounters = GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*pPassCounters)[0]);

    DX11GPAPass* pDx11Pass = new(std::nothrow) DX11GPAPass(this,
                                                           passIndex,
                                                           counterSource,
                                                           pPassCounters);

    if (nullptr == pDx11Pass)
    {
        GPA_LogError("Unable to allocate memory for the pass.");
    }
    else
    {
        pRetPass = pDx11Pass;
    }

    return pRetPass;
}
