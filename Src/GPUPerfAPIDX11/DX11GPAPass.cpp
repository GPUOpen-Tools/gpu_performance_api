//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Pass Object Implementation
//==============================================================================

#include "DX11GPAPass.h"
#include "DX11GPACommandList.h"
#include "DX11GPASample.h"
#include "GPAHardwareCounters.h"

GpuBlockInstanceLimitMap DX11GPAPass::ms_blockInstanceLimits;

DX11GPAPass::DX11GPAPass(IGPASession* pGpaSession,
                         PassIndex passIndex,
                         GPACounterSource counterSource,
                         IGPACounterScheduler* pCounterScheduler,
                         const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor)
{
    InitializeCounterInfo();
}

GPASample* DX11GPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                                GpaSampleType sampleType,
                                                ClientSampleId clientSampleId)
{
    // TODO: Handle software and hardware sample differently
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

IGPACommandList* DX11GPAPass::CreateAPISpecificCommandList(void* pCmd,
    CommandListId commandListId,
    GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    DX11GPACommandList* pRetCmdList = new(std::nothrow) DX11GPACommandList(GetGpaSession(), this, commandListId);

    return pRetCmdList;
}

bool DX11GPAPass::EndSample(IGPACommandList* pGpaCmdList)
{
    bool retVal = false;

    if (nullptr != pGpaCmdList)
    {
        retVal = pGpaCmdList->CloseLastSample();
    }

    return retVal;
}

bool DX11GPAPass::GetSQEngineParamValue(CounterIndex counterIndex, SQEngineParamValue& sqEngineParamValue)
{
    bool retVal = false;

    if (m_counterShaderMaskValueMap.find(counterIndex) != m_counterShaderMaskValueMap.end())
    {
        sqEngineParamValue = m_counterShaderMaskValueMap[counterIndex];
        retVal = true;
    }

    return retVal;
}

DX11GPAPass::~DX11GPAPass()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}

void DX11GPAPass::InitializeCounterInfo()
{
    DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(GetGpaSession()->GetParentContext());

    if (IsTimingPass())
    {
        for (CounterIndex counterIter = 0; counterIter < m_pCounterList->size(); counterIter++)
        {
            EnableCounterForPass(m_pCounterList->at(counterIter));
        }
    }
    else
    {
        if (nullptr != pDx11GpaContext)
        {
            GPUIndex activeGPU = pDx11GpaContext->GetActiveGpu();
            PopulateBlockInstanceLimits(activeGPU);

            const GPA_HardwareCounters* pHardwareCounters = pDx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

            for (CounterIndex counterIter = 0; counterIter < m_pCounterList->size(); counterIter++)
            {
                const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[m_pCounterList->at(counterIter)];
                PE_BLOCK_ID blockId = static_cast<PE_BLOCK_ID>(pCounter->m_groupIdDriver);
                UINT32 instance = static_cast<UINT32>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);

                if (PE_BLOCK_RLC == blockId)
                {
                    // RLC counters cause a reboot, so don't allow them to be enabled.
                    GPA_LogError("An unstable counter is included in the counter selection. Please remove it and re-profile.");
                    DisableAllCountersForPass();
                    break;
                }

                // On mid and low end hardware, not all block instances are available. This logic makes sure that we only attempt to
                // enable counters for block instances which exist.
                bool dontEnableCounter = false;

                if (ms_blockInstanceLimits.find(activeGPU) != ms_blockInstanceLimits.end())
                {
                    BlockInstanceLimitMap blockLimits = ms_blockInstanceLimits[activeGPU];

                    if (instance >= blockLimits[blockId])
                    {
                        // Don't try to enable this counter. When the results are collected, this will be given
                        // a result of 0, so that it has no contribution.
                        dontEnableCounter = true;
                    }
                }

                if (dontEnableCounter)
                {
                    continue;
                }

                EnableCounterForPass(m_pCounterList->at(counterIter));
            }

            if (GetEnabledCounterCount() > 0)
            {
                InitiliazeCounterExperimentParameters();
            }
        }
    }
}

void DX11GPAPass::InitiliazeCounterExperimentParameters()
{
    DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(GetGpaSession()->GetParentContext());
    const GPA_HardwareCounters* pHardwareCounters = pDx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

    auto PopulateExperimentParams = [&](const CounterIndex & counterIndex)->bool
    {
        const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[counterIndex];

        if (pCounter->m_groupIdDriver == PE_BLOCK_SQ)
        {
            // set the engine parameter if the SQ block is being used
            // convert the instance to a shader mask
            unsigned int maskValue = PE_SHADER_MASK_ALL;

            GPA_SQShaderStage stage = SQ_ALL;

            for (unsigned int j = 0; j < pHardwareCounters->m_sqGroupCount - 1; j++)
            {
                if (pHardwareCounters->m_pSQCounterGroups[j].m_groupIndex == pCounter->m_groupIndex)
                {
                    stage = pHardwareCounters->m_pSQCounterGroups[j].m_stage;
                    break;
                }
            }

            if (stage == SQ_ES) { maskValue = PE_SHADER_MASK_ES; }
            else if (stage == SQ_GS) { maskValue = PE_SHADER_MASK_GS; }
            else if (stage == SQ_VS) { maskValue = PE_SHADER_MASK_VS; }
            else if (stage == SQ_PS) { maskValue = PE_SHADER_MASK_PS; }
            else if (stage == SQ_LS) { maskValue = PE_SHADER_MASK_LS; }
            else if (stage == SQ_HS) { maskValue = PE_SHADER_MASK_HS; }
            else if (stage == SQ_CS) { maskValue = PE_SHADER_MASK_CS; }

            m_counterShaderMaskValueMap.insert(std::pair<CounterIndex, SQEngineParamValue>(counterIndex, maskValue));
        }

        return true;
    };

    IterateEnabledCounterList(PopulateExperimentParams);
}


void DX11GPAPass::PopulateBlockInstanceLimits(UINT activeGpu) const
{
    if (ms_blockInstanceLimits.find(activeGpu) == ms_blockInstanceLimits.end())
    {
        PE_BLOCK_COUNTER_INFO blockInfo = PE_BLOCK_COUNTER_INFO();
        BlockInstanceLimitMap blockLimits;

        for (unsigned int blockId = PE_BLOCK_UNKNOWN + 1; blockId < PE_BLOCK_MAX_CI; blockId++)
        {
            PE_BLOCK_ID peBlockId = static_cast<PE_BLOCK_ID>(blockId);

            if (GetBlockCounterInfo(activeGpu, peBlockId, &blockInfo))
            {
                blockLimits[peBlockId] = blockInfo.instanceCount;
            }
        }

        ms_blockInstanceLimits[activeGpu] = blockLimits;
    }
}

bool DX11GPAPass::GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo) const
{
    // Note: if using an older driver (one that doesn't support the new Perf Experiment interface -- see IsMgpuPerfExpSupported)
    //       gpuID will be 0. However, looking at driver sources, the implementation of GetBlockCounterInfo in those older
    //       drivers ignores this parameter anyway

    PE_RESULT result = PE_ERROR_UNAVAILABLE;
    DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(GetGpaSession()->GetParentContext());

    IAmdDxExtPerfProfile* pDxExtPerfProfile = pDx11GpaContext->GetAmdProfileExtension();

    if (nullptr != pDxExtPerfProfile)
    {
        result = pDxExtPerfProfile->GetBlockCounterInfo(gpuID, block, pBlockInfo);

        if (PE_OK != result)
        {
            GPA_LogError("Error querying Block Counter Info.");
            GPA_LogDebugError("  GPU: %d, Block %d.", gpuID, block);
        }
    }
    else
    {
        GPA_LogError("Perf profile extension function is not initialized");
    }

    return result == PE_OK;
}
