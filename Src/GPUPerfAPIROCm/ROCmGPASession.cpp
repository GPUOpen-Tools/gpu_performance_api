//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief ROCm GPA Session Implementation
//==============================================================================

#include "ROCmGPASession.h"
#include "ROCmGPAPass.h"

ROCmGPASession::ROCmGPASession(IGPAContext* pParentContext, GPA_Session_Sample_Type sampleType)
    : GPASession(pParentContext, sampleType)
{
}

GPA_API_Type ROCmGPASession::GetAPIType() const
{
    return GPA_API_ROCM;
}

GPAPass* ROCmGPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList*     pPassCounters = GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*pPassCounters)[0]);

    ROCmGPAPass* pROCmPass = new (std::nothrow) ROCmGPAPass(this, passIndex, counterSource, pPassCounters);

    if (nullptr == pROCmPass)
    {
        GPA_LogError("Unable to allocate memory for the pass.");
    }
    else
    {
        pRetPass = pROCmPass;
    }

    return pRetPass;
}
