//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA GPA Pass Object Implementation
//==============================================================================

#include "HSAGPAPass.h"
#include "HSAGPACommandList.h"
#include "HSAGPASample.h"

HSAGPAPass::HSAGPAPass(IGPASession* pGpaSession,
                       PassIndex passIndex,
                       GPACounterSource counterSource,
                       IGPACounterScheduler* pCounterScheduler,
                       const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor)
{
    EnableAllCountersForPass();
}

HSAGPAPass::~HSAGPAPass()
{
}

GPASample* HSAGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                               GpaSampleType sampleType,
                                               ClientSampleId clientSampleId)
{
    GPASample* pRetSample = nullptr;

    HSAGPASample* pHsaGpaSample = new(std::nothrow) HSAGPASample(this,
                                                                 pCmdList,
                                                                 sampleType,
                                                                 clientSampleId);

    if (nullptr == pHsaGpaSample)
    {
        GPA_LogError("Unable to allocate memory for the sample.");
    }
    else
    {
        pRetSample = pHsaGpaSample;
    }

    return pRetSample;

}

bool HSAGPAPass::ContinueSample(ClientSampleId srcSampleId,
                                IGPACommandList* pPrimaryGpaCmdList)
{
    // continuing samples not supported for HSA
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(pPrimaryGpaCmdList);
    return false;
}

IGPACommandList* HSAGPAPass::CreateAPISpecificCommandList(void* pCmd,
    CommandListId commandListId,
    GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    HSAGPACommandList* pRetCmdList = new(std::nothrow) HSAGPACommandList(GetGpaSession(), this, commandListId);
    return pRetCmdList;
}

bool HSAGPAPass::EndSample(IGPACommandList* pGpaCmdList)
{
    bool retVal = false;

    if (nullptr != pGpaCmdList)
    {
        retVal = pGpaCmdList->CloseLastSample();
    }

    return retVal;
}
