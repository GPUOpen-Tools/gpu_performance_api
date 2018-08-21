//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Session Implementation
//==============================================================================

#include "HSAGPASession.h"
#include "HSAGPAPass.h"

HSAGPASession::HSAGPASession(
    IGPAContext* pParentContext,
    GPA_Session_Sample_Type sampleType) :
    GPASession(pParentContext, sampleType)
{
}

GPA_API_Type HSAGPASession::GetAPIType() const
{
    return GPA_API_HSA;
}

GPAPass* HSAGPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList* pPassCounters = GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*pPassCounters)[0]);

    HSAGPAPass* pHsaPass = new(std::nothrow) HSAGPAPass(this,
                                                        passIndex,
                                                        counterSource,
                                                        pPassCounters);

    if (nullptr == pHsaPass)
    {
        GPA_LogError("Unable to allocate memory for the pass.");
    }
    else
    {
        pRetPass = pHsaPass;
    }

    return pRetPass;
}
