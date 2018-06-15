//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Pass Object Implementation
//==============================================================================

#include <cassert>

#include "CLGPAPass.h"
#include "CLGPACommandList.h"
#include "CLGPASample.h"
#include "GPAHardwareCounters.h"

CLGPAPass::CLGPAPass(IGPASession* pGpaSession,
                     PassIndex passIndex,
                     GPACounterSource counterSource,
                     IGPACounterScheduler* pCounterScheduler,
                     const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor)
{
    EnableAllCountersForPass();
    InitializeCLCounterInfo();
}

GPASample* CLGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                              GpaSampleType sampleType,
                                              ClientSampleId sampleId)
{
    GPASample* pRetSample = nullptr;

    CLGPASample* pCLGpaSample = new(std::nothrow) CLGPASample(this,
                                                              pCmdList,
                                                              sampleType,
                                                              sampleId);

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

IGPACommandList* CLGPAPass::CreateAPISpecificCommandList(void* pCmd,
                                                         CommandListId commandListId,
                                                         GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    CLGPACommandList* pRetCmdList = new(std::nothrow) CLGPACommandList(GetGpaSession(), this, commandListId);

    if (nullptr == pRetCmdList)
    {
        GPA_LogError("Unable to allocate memory for the command list.");
    }

    return pRetCmdList;
}

bool CLGPAPass::EndSample(IGPACommandList* pCmdList)
{
    bool retVal = false;

    if (nullptr != pCmdList)
    {
        retVal = pCmdList->CloseLastSample();
    }

    return retVal;
}

void CLGPAPass::IterateCLCounterMap(std::function<bool(GroupCountersPair groupCountrsPair)> function) const
{
    bool next = true;

    for (auto it = m_groupCountersMap.cbegin(); it != m_groupCountersMap.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void CLGPAPass::InitializeCLCounterInfo()
{
    CLGPAContext* pCLGpaContext = reinterpret_cast<CLGPAContext*>(GetGpaSession()->GetParentContext());

    const GPA_HardwareCounters* pHardwareCounters = pCLGpaContext->GetCounterAccessor()->GetHardwareCounters();
    gpa_uint32 groupCount = static_cast<gpa_uint32>(pHardwareCounters->m_groupCount);
    UNREFERENCED_PARAMETER(groupCount);

    auto AddCounterToCLCounterInfo = [&](CounterIndex counterIndex)-> bool
    {
        const GPA_HardwareCounterDescExt* pCounter = pCLGpaContext->GetCounterAccessor()->GetHardwareCounterExt(counterIndex);

        gpa_uint32 groupIndex = pCounter->m_groupIdDriver;
        assert(groupIndex <= groupCount);

        gpa_uint64 numCounters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
        UNREFERENCED_PARAMETER(numCounters);
        assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters);

        m_groupCountersMap[groupIndex].push_back(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
        return true;
    };

    IterateEnabledCounterList(AddCounterToCLCounterInfo);
}
