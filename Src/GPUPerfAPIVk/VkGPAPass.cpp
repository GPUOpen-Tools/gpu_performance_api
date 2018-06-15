//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan GPA Pass Object Implementation
//==============================================================================

#include <vulkan/vulkan.h>
#include <vk_amd_gpa_interface.h>

#include "VkGPAPass.h"
#include "VkGPACommandList.h"
#include "VkGPAContext.h"
#include "VkGPAHardwareSample.h"
#include "VkGPASoftwareSample.h"
#include "GPACounterGeneratorVKBase.h"

VkGPAPass::VkGPAPass(IGPASession* pGpaSession,
                     PassIndex passIndex,
                     GPACounterSource counterSource,
                     IGPACounterScheduler* pCounterScheduler,
                     const IGPACounterAccessor* pCounterAccessor):
    GPAPass(pGpaSession, passIndex, counterSource, pCounterScheduler, pCounterAccessor),
    m_isSampleBeginInfoInitialized(false)
{
    InitializeSampleConfig();
}

GPASample* VkGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                              GpaSampleType sampleType,
                                              unsigned int sampleId)
{
    VkGPAContext* pContext = reinterpret_cast<VkGPAContext*>(pCmdList->GetParentSession()->GetParentContext());
    assert(nullptr != pContext);

    GPASample* pSample = nullptr;

    if (GpaSampleType::Hardware == sampleType)
    {
        pSample = new(std::nothrow) VkGPAHardwareSample(this, pCmdList, sampleId, pContext->GetVkDevice());
    }
    else if (GpaSampleType::Software == sampleType)
    {
        pSample = new(std::nothrow) VkGPASoftwareSample(this, pCmdList, sampleId);
    }

    return pSample;
}

IGPACommandList* VkGPAPass::CreateAPISpecificCommandList(void* pCmd,
                                                         CommandListId commandListId,
                                                         GPA_Command_List_Type cmdType)
{

    VkGPACommandList* pVkCmdList = new(std::nothrow) VkGPACommandList(
        reinterpret_cast<VkGPASession*>(GetGpaSession()),
        this,
        pCmd,
        commandListId,
        cmdType);

    return pVkCmdList;
}

void VkGPAPass::InitializeSampleConfig()
{
    if (!m_isSampleBeginInfoInitialized && GPACounterSource::HARDWARE == GetCounterSource())
    {
        m_sampleBeginInfoAMD = {};
        m_sampleBeginInfoAMD.sType = VK_STRUCTURE_TYPE_GPA_SAMPLE_BEGIN_INFO_AMD;
        m_sampleBeginInfoAMD.pNext = nullptr;

        const GPA_HardwareCounters* pHardwareCounters = (reinterpret_cast<const GPA_CounterGeneratorVKBase*>(GetCounterAccessor()))->GetHardwareCounters();

        if (!m_pCounterList->empty())
        {
            if (IsTimingPass())
            {
                m_sampleBeginInfoAMD.sampleType = VK_GPA_SAMPLE_TYPE_TIMING_AMD;

                if (m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex)
                {
                    m_sampleBeginInfoAMD.timingPreSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
                }
                else if (m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
                {
                    m_sampleBeginInfoAMD.timingPreSample = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                }

                m_sampleBeginInfoAMD.timingPostSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
                EnableCounterForPass(m_pCounterList->at(0));
            }
            else
            {
                // All the shader stages
                VkGpaSqShaderStageFlagBitsAMD maskValue = VK_GPA_SQ_SHADER_STAGE_FLAG_BITS_MAX_ENUM_AMD;

                m_sampleBeginInfoAMD.sampleType = VK_GPA_SAMPLE_TYPE_CUMULATIVE_AMD;

                // add all desired counters
                for (size_t i = 0; i < m_pCounterList->size(); i++)
                {
                    const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[m_pCounterList->at(i)];
                    VkGpaPerfBlockAMD block = static_cast<VkGpaPerfBlockAMD>(pCounter->m_groupIdDriver);
                    gpa_uint32 instance = pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance;
                    gpa_uint32 eventId = static_cast<gpa_uint32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);

                    if (reinterpret_cast<VkGPAContext*>(GetGpaSession()->GetParentContext())->GetInstanceCount(block) <= instance)
                    {
                        DisableCounterForPass(m_pCounterList->at(i));
                        continue;
                    }

                    if (reinterpret_cast<VkGPAContext*>(GetGpaSession()->GetParentContext())->GetMaxEventIdCount(block) <= eventId)
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
                    VkGpaPerfCounterAMD thisCounter;
                    thisCounter.blockType = block;
                    thisCounter.blockInstance = instance;
                    thisCounter.eventID = eventId;

                    m_counterIds.push_back(thisCounter);

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
                            maskValue = VK_GPA_SQ_SHADER_STAGE_ES_BIT_AMD;
                        }
                        else if (stage == SQ_GS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_GS_BIT_AMD;
                        }
                        else if (stage == SQ_VS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_VS_BIT_AMD;
                        }
                        else if (stage == SQ_PS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_PS_BIT_AMD;
                        }
                        else if (stage == SQ_LS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_LS_BIT_AMD;
                        }
                        else if (stage == SQ_HS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_HS_BIT_AMD;
                        }
                        else if (stage == SQ_CS)
                        {
                            maskValue = VK_GPA_SQ_SHADER_STAGE_CS_BIT_AMD;
                        }
                    }

                    EnableCounterForPass(m_pCounterList->at(i));
                }

                m_sampleBeginInfoAMD.perfCounterCount = GetNumEnabledCountersForPass();
                m_sampleBeginInfoAMD.pPerfCounters = m_counterIds.data();
                m_sampleBeginInfoAMD.streamingPerfTraceSampleInterval = 0;
                m_sampleBeginInfoAMD.sqThreadTraceDeviceMemoryLimit = 0;
                m_sampleBeginInfoAMD.perfCounterDeviceMemoryLimit = 0;
                m_sampleBeginInfoAMD.cacheFlushOnCounterCollection = VK_FALSE;

                // set shader mask
                m_sampleBeginInfoAMD.sqShaderMaskEnable = VK_TRUE;
                m_sampleBeginInfoAMD.sqShaderMask = maskValue;

                // sq Thread trace
                m_sampleBeginInfoAMD.sqThreadTraceEnable = VK_FALSE;
                m_sampleBeginInfoAMD.sqThreadTraceSuppressInstructionTokens = VK_TRUE;
            }

            // Insert L2 cache invalidate and flush around counter sample
            if (GetGpaSession()->GetParentContext()->IsInvalidateAndFlushL2CacheEnabled())
            {
                m_sampleBeginInfoAMD.cacheFlushOnCounterCollection = 1;
            }

            m_isSampleBeginInfoInitialized = true;
        }
    }
    else // software counter
    {
        // enable all desired counters
        EnableAllCountersForPass();
    }
}

bool VkGPAPass::EndSample(IGPACommandList* pCmdList)
{
    bool success = false;

    if (nullptr == pCmdList)
    {
        GPA_LogError("Null pointer to GPA CommandList supplied.");
    }
    else if (!pCmdList->IsCommandListRunning())
    {
        GPA_LogError("CommandList is closed for sampling.");
    }
    else if (pCmdList->IsLastSampleClosed())
    {
        GPA_LogError("There is no open sample on the CommandList.");
    }
    else
    {
        GPASample* pGpaSample = pCmdList->GetLastSample();

        if (nullptr != pGpaSample && !pGpaSample->IsClosed())
        {
            success = pCmdList->CloseLastSample();
        }
    }

    return success;
}

bool VkGPAPass::CopySecondarySamples(VkGPACommandList* pSecondaryVkGPACmdList,
                                     VkGPACommandList* pPrimaryVkGPACmdList,
                                     gpa_uint32 numSamples,
                                     gpa_uint32* pNewSampleIds)
{
    bool copied = false;

    // 1. Validate all new sample id are unique
    // 2. Create new samples for new passed sample id
    // 3. Update the session <-> Cmd Map

    bool areNewSamplesUnique = true;

    for (gpa_uint32 i = 0; i < numSamples; ++i)
    {
        areNewSamplesUnique &= !DoesSampleExist(pNewSampleIds[i]);
    }

    if (areNewSamplesUnique)
    {
        if (GPA_COMMAND_LIST_PRIMARY == pPrimaryVkGPACmdList->GetCmdType() &&
            GPA_COMMAND_LIST_SECONDARY == pSecondaryVkGPACmdList->GetCmdType())
        {
            if (pPrimaryVkGPACmdList->GetPass()->GetIndex() == pSecondaryVkGPACmdList->GetPass()->GetIndex())
            {
                // Validate
                // 1. secondary command list is not open
                // 2. No pending sample on the secondary command list
                if (!pSecondaryVkGPACmdList->IsCommandListRunning() && pSecondaryVkGPACmdList->IsLastSampleClosed())
                {
                    // Validate
                    // 1. primary command list is open
                    // 2. No pending sample on the primary command list
                    if (pPrimaryVkGPACmdList->IsCommandListRunning() && pPrimaryVkGPACmdList->IsLastSampleClosed())
                    {
                        // Validate - Number of sample ids must be equal to the created sample on the secondary command list
                        if (pSecondaryVkGPACmdList->GetSampleCount() == numSamples)
                        {
                            std::vector<ClientSampleId> originalClientSampleIds;

                            // Create new sample objects to represent the copied samples
                            unsigned int index = 0;
                            std::vector<VkGPASample*> newSampleList;

                            for (gpa_uint32 i = 0; i < numSamples; ++i)
                            {
                                GpaSampleType sampleType = GetCounterSource() == GPACounterSource::HARDWARE ? GpaSampleType::Hardware : GpaSampleType::Software;
                                VkGPASample* pNewSample = reinterpret_cast<VkGPASample*>(CreateAPISpecificSample(pSecondaryVkGPACmdList,
                                                                                         sampleType,
                                                                                         pNewSampleIds[i]));

                                if (nullptr != pNewSample)
                                {
                                    // Add this sample to command list as well to sample list
                                    AddClientSample(pNewSampleIds[i], pNewSample);
                                    newSampleList.push_back(pNewSample);
                                }
                                else
                                {
                                    GPA_LogError("Unable to copy secondary samples: Unable to create sample.");
                                }

                                index++;
                            }

                            // assume they will succeed,
                            copied = true;

                            if (pSecondaryVkGPACmdList->CopySecondarySamples(pPrimaryVkGPACmdList, numSamples, pNewSampleIds, originalClientSampleIds))
                            {
                                index = 0;

                                for (auto iter = newSampleList.begin(); iter != newSampleList.end(); ++iter)
                                {
                                    // Driver sample id will be same as that of the original one
                                    VkGPASample* pSecondaryCmdSample =
                                        reinterpret_cast<VkGPASample*>(pSecondaryVkGPACmdList->GetSample(originalClientSampleIds[index]));

                                    if (nullptr != pSecondaryCmdSample)
                                    {
                                        (*iter)->SetAsCopied();
                                        (*iter)->SetDriverSampleId(pSecondaryCmdSample->GetDriverSampleId());
                                    }
                                    else
                                    {
                                        copied = false;
                                    }

                                    index++;
                                }
                            }
                            else
                            {
                                copied = false;
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

    return copied;
}

const VkGpaSampleBeginInfoAMD* VkGPAPass::GetVkSampleBeginInfo() const
{
    const VkGpaSampleBeginInfoAMD* pInfo = nullptr;

    if (m_isSampleBeginInfoInitialized)
    {
        pInfo = &m_sampleBeginInfoAMD;
    }

    return pInfo;
}
