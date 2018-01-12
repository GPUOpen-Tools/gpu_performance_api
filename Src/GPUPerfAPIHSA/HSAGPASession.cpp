//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Session Implementation
//==============================================================================

#include "HSAGPASession.h"
#include "HSAGPAPass.h"

HSAGPASession::HSAGPASession(
    IGPAContext* pParentContext) :
    GPASession(pParentContext, pParentContext->GetCounterScheduler())
{
}

HSAGPASession::~HSAGPASession()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}

GPA_API_Type HSAGPASession::GetAPIType() const
{
    return GPA_API_HSA;
}

GPAPass* HSAGPASession::CreateAPIPass(PassIndex passIndex)
{
    GPAPass* pRetPass = nullptr;

    CounterList* passCounters = GetCounterScheduler()->GetCountersForPass(passIndex);
    GPACounterSource counterSource = GetParentContext()->GetCounterSource((*passCounters)[0]);

    HSAGPAPass* pHsaPass = new(std::nothrow) HSAGPAPass(this, passIndex, counterSource, GetCounterScheduler(), GetParentContext()->GetCounterAccessor());

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
