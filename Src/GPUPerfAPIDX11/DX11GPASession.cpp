//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Session Implementation
//==============================================================================

#include "DX11GPASession.h"
#include "DX11GPAPass.h"


DX11GPASession::DX11GPASession(IGPAContext* pParentContext) :
    GPASession(pParentContext, pParentContext->GetCounterScheduler())
{
}

DX11GPASession::~DX11GPASession()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}

GPA_API_Type DX11GPASession::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

GPAPass* DX11GPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList* passCounters = GetCounterScheduler()->GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*passCounters)[0]);

    DX11GPAPass* pDx11Pass = new(std::nothrow) DX11GPAPass(this,
                                                           passIndex,
                                                           counterSource,
                                                           GetCounterScheduler(),
                                                           GetParentContext()->GetCounterAccessor());

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
