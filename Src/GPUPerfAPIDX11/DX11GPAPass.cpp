//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Pass Object Implementation
//==============================================================================

#include "DX11GPAPass.h"
#include "DX11GPACommandList.h"
#include "DX11GPASample.h"

DX11GPAPass::DX11GPAPass(IGPASession* pGpaSession,
                         PassIndex passIndex,
                         GPACounterSource counterSource,
                         IGPACounterScheduler* pCounterScheduler,
                         IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor)
{
}

GPASample* DX11GPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                                GpaSampleType sampleType,
                                                ClientSampleId clientSampleId)
{
    GPASample* pRetSample = nullptr;

    DX11GPASample* pDx11GpaSample = new(std::nothrow) DX11GPASample(
        this,
        pCmdList,
        sampleType,
        clientSampleId);

    if (nullptr != pDx11GpaSample)
    {
        pRetSample = pDx11GpaSample;
    }

    return pRetSample;

}

bool DX11GPAPass::ContinueSample(ClientSampleId srcSampleId,
                                 IGPACommandList* pPrimaryGpaCmdList)
{
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(pPrimaryGpaCmdList);
    bool status = static_cast<bool>(GPA_STATUS_ERROR_API_NOT_SUPPORTED); // This is only to show that this functionality is not supported in DX11
    status = false;
    return status;
}

bool DX11GPAPass::UpdateResults()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return true;
}

IGPACommandList* DX11GPAPass::CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    DX11GPACommandList* pRetCmdList = new(std::nothrow) DX11GPACommandList(GetGpaSession(), this);

    if (nullptr != pRetCmdList)
    {
        AddGPACommandList(pRetCmdList);
    }

    return pRetCmdList;
}

DX11GPAPass::~DX11GPAPass()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}
