//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Pass Object Implementation
//==============================================================================

#include "DX12GPAPass.h"
#include "GPACounterGeneratorDX12Base.h"
#include "DX12GPAContext.h"
#include "DX12GPASample.h"
#include "DX12GPACommandList.h"

DX12GPAPass::DX12GPAPass(IGPASession* pGpaSession,
                         PassIndex passIndex,
                         GPACounterSource counterSource,
                         IGPACounterScheduler* pCounterScheduler,
                         const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor),
    m_isSampleConfigInitialized(false)
{
    InitializeSampleConfig();
}

GPASample* DX12GPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                                GpaSampleType sampleType,
                                                ClientSampleId clientSampleId)
{
    DX12GPASample* pRetDx12GpaSample = nullptr;
    DX12GPACommandList* pDx12GpaCmdList = reinterpret_cast<DX12GPACommandList*>(pCmdList);

    // First Check whether the command list is opened and last sample is closed
    if (nullptr != pDx12GpaCmdList &&
        !pDx12GpaCmdList->DoesSampleExist(clientSampleId) &&
        pDx12GpaCmdList->IsCommandListRunning() &&
        pDx12GpaCmdList->IsLastSampleClosed())
    {
        pRetDx12GpaSample = new(std::nothrow) DX12GPASample(
            this,
            pCmdList,
            sampleType,
            clientSampleId);
    }

    return pRetDx12GpaSample;
}

bool DX12GPAPass::IsComplete() const
{
    bool complete = true;

    if (false == IsResultsCollectedFromDriver())
    {
        for (auto iter = GetCmdList().cbegin();
             iter != GetCmdList().cend();
             ++iter)
        {
            complete &= (*iter)->IsComplete();
        }
    }

    return complete;
}

bool DX12GPAPass::UpdateResults()
{
    bool isCompleted = false;

    if (IsComplete())
    {
        isCompleted = GPAPass::UpdateResults();

        if (isCompleted)
        {
            ResetPass();
        }
    }

    return isCompleted;
}

IGPACommandList* DX12GPAPass::CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType)
{
    IGPACommandList* pRetCmdList = nullptr;

    DX12GPACommandList* pDx12CmdList = new(std::nothrow) DX12GPACommandList(
        reinterpret_cast<DX12GPASession*>(GetGpaSession()),
        this,
        pCmd,
        cmdType);

    if (nullptr != pDx12CmdList)
    {
        pRetCmdList = pDx12CmdList;
        AddGPACommandList(pDx12CmdList);
    }

    return pRetCmdList;
}

bool DX12GPAPass::EndSample(IGPACommandList* pDx12GpaCmdList)
{
    bool success = false;

    if (nullptr != pDx12GpaCmdList &&
        pDx12GpaCmdList->IsCommandListRunning() &&
        !pDx12GpaCmdList->IsLastSampleClosed())
    {
        GPASample* pGpaSample = pDx12GpaCmdList->GetLastSample();

        if (nullptr != pGpaSample && !pGpaSample->IsClosed())
        {
            success = pDx12GpaCmdList->CloseLastSample();
        }
    }
    else
    {
        GPA_LogError("Either the command list is closed or there is no open sample on the command list.");
    }

    return success;
}

bool DX12GPAPass::CopySecondarySamples(std::vector<ClientSampleId> clientSamples,
                                       DX12GPACommandList* pDx12PrimaryGpaCmdList,
                                       DX12GPACommandList* pDx12SecondaryGpaCmdList)
{

    bool success = false;

    // 1. Validate all new sample id are unique
    // 2. Create new samples for new passed sample id
    // 3. Update the session <-> Cmd Map

    bool isAllUniqueSampleIds = true;

    for (auto iter = clientSamples.cbegin(); iter != clientSamples.cend(); ++iter)
    {
        isAllUniqueSampleIds &= !DoesSampleExist(*iter);
    }

    if (true == isAllUniqueSampleIds)
    {
        if (GPA_COMMAND_LIST_PRIMARY == pDx12PrimaryGpaCmdList->GetCmdType() &&
            GPA_COMMAND_LIST_SECONDARY == pDx12SecondaryGpaCmdList->GetCmdType())
        {
            if (pDx12PrimaryGpaCmdList->GetPass()->GetIndex() == pDx12SecondaryGpaCmdList->GetPass()->GetIndex())
            {
                // Validate
                // 1. secondary command list is not open
                // 2. No pending sample on the secondary command list
                if (!pDx12SecondaryGpaCmdList->IsCommandListRunning() && pDx12SecondaryGpaCmdList->IsLastSampleClosed())
                {
                    // Validate
                    // 1. primary command list is open
                    // 2. No pending sample on the primary command list
                    if (pDx12PrimaryGpaCmdList->IsCommandListRunning() && pDx12PrimaryGpaCmdList->IsLastSampleClosed())
                    {
                        // Validate - Number of sample ids must be equal to the created sample on the secondary command list
                        if (pDx12SecondaryGpaCmdList->GetSampleCount() == clientSamples.size())
                        {
                            std::vector<ClientSampleId> originalClientSampleIds;
                            // Copy the results

                            unsigned int index = 0;
                            std::vector<DX12GPASample*> newSampleList;

                            for (auto iter = clientSamples.begin(); iter != clientSamples.end(); ++iter)
                            {
                                GpaSampleType sampleType = GetCounterSource() == GPACounterSource::HARDWARE ? GpaSampleType::Hardware : GpaSampleType::Software;
                                DX12GPASample* pNewSample = reinterpret_cast<DX12GPASample*>(CreateAPISpecificSample(pDx12SecondaryGpaCmdList,
                                                                                             sampleType,
                                                                                             *iter));

                                if (nullptr != pNewSample)
                                {
                                    // Add this sample to command list as well to sample list
                                    AddClientSample(*iter, pNewSample);
                                    newSampleList.push_back(pNewSample);
                                }
                                else
                                {
                                    GPA_LogError("Unable to copy secondary samples: Unable to create sample.");
                                }

                                index++;
                            }

                            success = true;

                            if (pDx12SecondaryGpaCmdList->CopyBundleSamples(clientSamples,
                                                                          pDx12PrimaryGpaCmdList,
                                                                          originalClientSampleIds))
                            {
                                index = 0;

                                for (auto iter = newSampleList.begin(); iter != newSampleList.end(); ++iter)
                                {
                                    // Driver sample id will be same as that of the original one
                                    DX12GPASample* pSecondaryCmdSample =
                                        pDx12SecondaryGpaCmdList->GetSample(originalClientSampleIds[index]);

                                    if (nullptr != pSecondaryCmdSample)
                                    {
                                        (*iter)->SetAsCopied();
                                        (*iter)->SetDriverSampleId(pSecondaryCmdSample->GetDriverSampleId());
                                    }
                                    else
                                    {
                                        success = false;
                                    }

                                    index++;
                                }
                            }
                            else
                            {
                                success = false;
                            }
                        }
                        else
                        {
                            GPA_LogError("Unable to copy secondary samples: Number of new sample ids is not same as that on secondary command list.");
                        }
                    }
                    else
                    {
                        GPA_LogError("Unable to copy secondary samples: Either primary command list is closed or the last sample is not closed.");
                    }
                }
                else
                {
                    GPA_LogError("Unable to copy secondary samples: Either secondary command list is not closed or the last sample is not closed.");
                }
            }
            else
            {
                GPA_LogError("Unable to copy secondary samples: Primary and Secondary command list must be from the same pass.");
            }
        }
        else
        {
            GPA_LogError("Unable to copy secondary samples: One primary command list and one secondary command list are required.");
        }
    }
    else
    {
        GPA_LogError("Unable to copy secondary samples: Not all client sample ids are unique.");
    }

    return success;
}


AmdExtGpaSampleConfig DX12GPAPass::GetAmdExtSampleConfig() const
{
    return m_amdExtsampleConfig;
}

DX12GPAPass::~DX12GPAPass()
{
    if (AmdExtGpaSampleType::Timing != m_amdExtsampleConfig.type)
    {
        delete[] m_amdExtsampleConfig.perfCounters.pIds;
    }

    ResetPass();
}

void DX12GPAPass::InitializeSampleConfig()
{
    if (!m_isSampleConfigInitialized && GPACounterSource::HARDWARE == GetCounterSource())
    {
        std::vector<AmdExtPerfCounterId> counterIds;

        const GPA_HardwareCounters* pHardwareCounters = (reinterpret_cast<const GPA_CounterGeneratorDX12Base*>(GetCounterAccessor()))->GetHardwareCounters();

        if (!m_pCounterList->empty())
        {
            if (IsTimingPass())
            {
                m_amdExtsampleConfig.type = AmdExtGpaSampleType::Timing;

                if (m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex)
                {
                    m_amdExtsampleConfig.timing.preSample = AmdExtHwPipePoint::HwPipeBottom;
                }
                else if (m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
                {
                    m_amdExtsampleConfig.timing.preSample = AmdExtHwPipePoint::HwPipeTop;
                }

                m_amdExtsampleConfig.timing.postSample = AmdExtHwPipePoint::HwPipeBottom;
                EnableCounterForPass(m_pCounterList->at(0));
            }
            else
            {
                AmdExtPerfExperimentShaderFlags maskValue = PerfShaderMaskAll;

                m_amdExtsampleConfig.type = AmdExtGpaSampleType::Cumulative;
                m_amdExtsampleConfig.flags.u32All = 0;

                // add all desired counters
                for (size_t i = 0; i < m_pCounterList->size(); i++)
                {
                    const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[m_pCounterList->at(i)];
                    AmdExtGpuBlock block = static_cast<AmdExtGpuBlock>(pCounter->m_groupIdDriver);
                    UINT32 instance = static_cast<UINT32>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);
                    UINT32 eventId = static_cast<UINT32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);

                    if (reinterpret_cast<DX12GPAContext*>(GetGpaSession()->GetParentContext())->GetInstanceCount(block) <= instance)
                    {
                        DisableCounterForPass(m_pCounterList->at(i));
                        continue;
                    }

                    if (reinterpret_cast<DX12GPAContext*>(GetGpaSession()->GetParentContext())->GetMaxEventIdCount(block) <= eventId)
                    {
                        DisableCounterForPass(m_pCounterList->at(i));
                        continue;
                    }

                    // Validate requested counter vs number of actual hardware counters and group index
                    uint32_t groupIndex = pCounter->m_groupIndex;

                    uint32_t counters = 0;

                    if (groupIndex < pHardwareCounters->m_groupCount)
                    {
                        counters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
                    }
                    else
                    {
                        counters = pHardwareCounters->m_pAdditionalGroups[groupIndex - pHardwareCounters->m_groupCount].m_numCounters;
                    }

                    if (pCounter->m_pHardwareCounter->m_counterIndexInGroup > counters)
                    {
                        assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= counters);
                        DisableCounterForPass(m_pCounterList->at(i));
                        continue;
                    }

                    if (groupIndex > (pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount))
                    {
                        assert(groupIndex <= (pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount));
                        DisableCounterForPass(m_pCounterList->at(i));
                        continue;
                    }

                    // Add counter to valid vector
                    AmdExtPerfCounterId thisCounter;
                    thisCounter.block = block;
                    thisCounter.instance = instance;
                    thisCounter.eventId = eventId;

                    counterIds.push_back(thisCounter);

                    // if dealing with an SQ counter, check if the the stage mask needs to be set
                    if (pCounter->m_groupIndex >= pHardwareCounters->m_pSQCounterGroups[0].m_groupIndex && pCounter->m_groupIndex <= pHardwareCounters->m_pSQCounterGroups[pHardwareCounters->m_sqGroupCount - 1].m_groupIndex)
                    {
                        GPA_SQShaderStage stage = SQ_ALL;

                        for (unsigned int j = 0; j < pHardwareCounters->m_sqGroupCount - 1; j++)
                        {
                            if (pHardwareCounters->m_pSQCounterGroups[j].m_groupIndex == pCounter->m_groupIndex)
                            {
                                stage = pHardwareCounters->m_pSQCounterGroups[j].m_stage;
                                break;
                            }
                        }

                        if (stage == SQ_ES)
                        {
                            maskValue = PerfShaderMaskEs;
                        }
                        else if (stage == SQ_GS)
                        {
                            maskValue = PerfShaderMaskGs;
                        }
                        else if (stage == SQ_VS)
                        {
                            maskValue = PerfShaderMaskVs;
                        }
                        else if (stage == SQ_PS)
                        {
                            maskValue = PerfShaderMaskPs;
                        }
                        else if (stage == SQ_LS)
                        {
                            maskValue = PerfShaderMaskLs;
                        }
                        else if (stage == SQ_HS)
                        {
                            maskValue = PerfShaderMaskHs;
                        }
                        else if (stage == SQ_CS)
                        {
                            maskValue = PerfShaderMaskCs;
                        }
                    }

                    EnableCounterForPass(m_pCounterList->at(i));
                }

                m_amdExtsampleConfig.perfCounters.numCounters = GetNumEnabledCountersForPass();
                AmdExtPerfCounterId* pAmdExtPerfCounterId = new(std::nothrow) AmdExtPerfCounterId[m_pCounterList->size()];

                if (nullptr != pAmdExtPerfCounterId)
                {
                    memcpy(pAmdExtPerfCounterId, counterIds.data(), sizeof(AmdExtPerfCounterId) * counterIds.size());
                }

                m_amdExtsampleConfig.perfCounters.pIds = pAmdExtPerfCounterId;
                m_amdExtsampleConfig.perfCounters.spmTraceSampleInterval = 0;
                m_amdExtsampleConfig.perfCounters.gpuMemoryLimit = 0;

                // set shader mask
                m_amdExtsampleConfig.flags.sqShaderMask = 1;
                m_amdExtsampleConfig.sqShaderMask = maskValue;
            }

            // Insert L2 cache invalidate and flush around counter sample
            if (GetGpaSession()->GetParentContext()->IsInvalidateAndFlushL2CacheEnabled())
            {
                m_amdExtsampleConfig.flags.cacheFlushOnCounterCollection = 1;
            }

            m_isSampleConfigInitialized = true;
        }
    }
}

void DX12GPAPass::ResetPass() const
{
    LockCommandListMutex();

    for (auto it = GetCmdList().begin();
         it != GetCmdList().end(); ++it)
    {
        DX12GPACommandList* pDx12CmdList = reinterpret_cast<DX12GPACommandList*>(*it);
        pDx12CmdList->ReleaseNonGPAResources();
    }

    UnlockCommandListMutex();
}
