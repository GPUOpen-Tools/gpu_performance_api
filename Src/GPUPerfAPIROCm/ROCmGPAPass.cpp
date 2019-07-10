//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  ROCm GPA Pass Object Implementation
//==============================================================================

#include "ROCmGPAPass.h"
#include "ROCmGPACommandList.h"
#include "ROCmGPASample.h"

ROCmGPAPass::ROCmGPAPass(IGPASession* pGpaSession, PassIndex passIndex, GPACounterSource counterSource, CounterList* pPassCounters)
    : GPAPass(pGpaSession, passIndex, counterSource, pPassCounters)
{
    EnableAllCountersForPass();
}

GPASample* ROCmGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId)
{
    GPASample* pRetSample = nullptr;

    ROCmGPASample* pROCmGpaSample = new (std::nothrow) ROCmGPASample(this, pCmdList, sampleType, sampleId);

    if (nullptr == pROCmGpaSample)
    {
        GPA_LogError("Unable to allocate memory for the sample.");
    }
    else
    {
        pRetSample = pROCmGpaSample;
    }

    return pRetSample;
}

bool ROCmGPAPass::ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList)
{
    // continuing samples not supported for ROCm
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(pPrimaryGpaCmdList);
    return false;
}

IGPACommandList* ROCmGPAPass::CreateAPISpecificCommandList(void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    ROCmGPACommandList* pRetCmdList = new (std::nothrow) ROCmGPACommandList(GetGpaSession(), this, commandListId);
    return pRetCmdList;
}

bool ROCmGPAPass::EndSample(IGPACommandList* pCmdList)
{
    bool retVal = false;

    if (nullptr != pCmdList)
    {
        retVal = pCmdList->CloseLastSample();
    }

    return retVal;
}
