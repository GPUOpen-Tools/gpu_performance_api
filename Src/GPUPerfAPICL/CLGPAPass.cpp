//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Pass Object Implementation
//==============================================================================

#include "CLGPAPass.h"
#include "CLGPACommandList.h"
#include "CLGPASample.h"

CLGPAPass::CLGPAPass(IGPASession* pGpaSession,
                     PassIndex passIndex,
                     GPACounterSource counterSource,
                     IGPACounterScheduler* pCounterScheduler,
                     const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor)
{
    EnableAllCountersForPass();
}

CLGPAPass::~CLGPAPass()
{
}

GPASample* CLGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                              GpaSampleType sampleType,
                                              ClientSampleId clientSampleId)
{
    GPASample* pRetSample = nullptr;

    CLGPASample* pCLGpaSample = new(std::nothrow) CLGPASample(this,
                                                              pCmdList,
                                                              sampleType,
                                                              clientSampleId);

    if (nullptr == pCLGpaSample)
    {
        GPA_LogError("Unable to allocate memory for the sample.");
    }
    else
    {
        pRetSample = pCLGpaSample;
    }

    return pRetSample;

}

bool CLGPAPass::ContinueSample(ClientSampleId srcSampleId,
                               IGPACommandList* pPrimaryGpaCmdList)
{
    // continuing samples not supported for OpenCL
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(pPrimaryGpaCmdList);
    return false;
}

IGPACommandList* CLGPAPass::CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    CLGPACommandList* pRetCmdList = new(std::nothrow) CLGPACommandList(GetGpaSession(), this);

    if (nullptr != pRetCmdList)
    {
        AddGPACommandList(pRetCmdList);
    }

    return pRetCmdList;
}

bool CLGPAPass::EndSample(IGPACommandList* pGpaCmdList)
{
    bool retVal = false;

    if (nullptr != pGpaCmdList)
    {
        retVal = pGpaCmdList->CloseLastSample();
    }

    return retVal;
}
