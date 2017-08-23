//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#include "VkHardwareCounterDataRequest.h"
#include "vk_amd_gpa_interface.h"

VkHardwareCounterDataRequest::VkHardwareCounterDataRequest(VkDevice device) :
    m_pContextState(nullptr),
    m_pCounterIds(nullptr),
    m_numCounters(0),
    m_sampleIndex(0),
    m_device(device),
    m_commandBuffer(VK_NULL_HANDLE),
    m_isTimingRequest(false)
{
}

VkHardwareCounterDataRequest::~VkHardwareCounterDataRequest()
{
    if (VK_NULL_HANDLE != m_commandBuffer)
    {
        m_commandBuffer = VK_NULL_HANDLE;
    }
}

bool VkHardwareCounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    bool result = false;
    VkGpaSessionAMD gpaSession = VK_NULL_HANDLE;

    if (m_pContextState->GetGpaSessionForCommandList(m_commandBuffer, &gpaSession))
    {
        VkResult isReady = _vkGetGpaSessionStatusAMD(m_device, gpaSession);

        if (isReady == VK_SUCCESS)
        {
            size_t expectedResultsSize;

            if (m_isTimingRequest)
            {
                expectedResultsSize = 2 * sizeof(gpa_uint64); // timing requests have two timestamps
            }
            else
            {
                expectedResultsSize = m_numCounters * sizeof(gpa_uint64);
            }

            size_t reportedSize = 0;

            VkResult gotResultSize = _vkGetGpaSessionResultsAMD(m_device, gpaSession, m_sampleIndex, &reportedSize, nullptr);

            result = false;

            if (gotResultSize == VK_SUCCESS && 
                reportedSize == expectedResultsSize)
            {
                if (m_isTimingRequest)
                {
                    gpa_uint64 timestamps[2] = {};

                    VkResult gotResults = _vkGetGpaSessionResultsAMD(m_device, gpaSession, m_sampleIndex, &expectedResultsSize, timestamps);
                    result = (VK_SUCCESS == gotResults);
                    if (result)
                    {
                        gpa_uint64 difference = timestamps[1] - timestamps[0];
                        resultStorage.m_pResultBuffer[0] = difference;
                    }
                }
                else
                {
                    VkResult gotResults = _vkGetGpaSessionResultsAMD(m_device, gpaSession, m_sampleIndex, &expectedResultsSize, resultStorage.m_pResultBuffer);
                    result = (VK_SUCCESS == gotResults);
                }
            }

            if (!result)
            {
                GPA_LogError("Unable to get hw sample results.");
            }
        }
    }

    return result;
}

bool VkHardwareCounterDataRequest::BeginRequest(GPA_ContextState* pContextState,
                                                  void* pSampleList,
                                                  gpa_uint32 selectionId,
                                                  const vector<gpa_uint32>* pCounters)
{
    UNREFERENCED_PARAMETER(selectionId);
    UNREFERENCED_PARAMETER(pSampleList);

    bool result = true;

    m_pContextState = reinterpret_cast<GPA_ContextStateVk*>(pContextState);

    VkGpaSampleBeginInfoAMD gpaSampleConfig = { };
    gpaSampleConfig.sType = VK_STRUCTURE_TYPE_GPA_SAMPLE_BEGIN_INFO_AMD;

    GPA_HardwareCounters* pHardwareCounters = m_pContextState->m_pCounterAccessor->GetHardwareCounters();

    m_numCounters = static_cast<gpa_uint32>(pCounters->size());

    if (m_numCounters > 0)
    {
        if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex ||
            (*pCounters)[0] == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
        {
            m_isTimingRequest = true;
            m_pCounterIds = nullptr;

            gpaSampleConfig.sampleType = VkGpaSampleTypeAMD::VK_GPA_SAMPLE_TYPE_TIMING_AMD;

            if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex)
            {
                gpaSampleConfig.timingPreSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
            }
            else if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
            {
                gpaSampleConfig.timingPreSample = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            }

            gpaSampleConfig.timingPostSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        }
        else
        {
            VkGpaSqShaderStageFlagBitsAMD maskValue = VkGpaSqShaderStageFlagBitsAMD(0x00000080); // All the stages

            gpaSampleConfig.sampleType = VkGpaSampleTypeAMD::VK_GPA_SAMPLE_TYPE_CUMULATIVE_AMD;
            gpaSampleConfig.perfCounterCount = m_numCounters;

            m_pCounterIds = new (std::nothrow) VkGpaPerfCounterAMD[gpaSampleConfig.perfCounterCount];

            if (nullptr == m_pCounterIds)
            {
                GPA_LogError("Insufficient memory to allocate counters.");
                return false;
            }

            // add all desired counters
            for (size_t i = 0; i < pCounters->size(); i++)
            {
                GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[i]];
                m_pCounterIds[i].blockType = static_cast<VkGpaPerfBlockAMD>(pCounter->m_groupIdDriver);
                m_pCounterIds[i].blockInstance = static_cast<uint32_t>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);
                m_pCounterIds[i].eventID = static_cast<uint32_t>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);

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

            gpaSampleConfig.pPerfCounters = m_pCounterIds;
            gpaSampleConfig.streamingPerfTraceSampleInterval = 0;
            gpaSampleConfig.perfCounterDeviceMemoryLimit = 0;

            // set shader mask
            gpaSampleConfig.sqShaderMaskEnable = VK_TRUE;
            gpaSampleConfig.sqShaderMask = maskValue;
        }

        // Insert L2 cache invalidate and flush around counter sample
        if (pContextState->GetInvalidateAndFlushL2Cache())
        {
            gpaSampleConfig.cacheFlushOnCounterCollection = true;
            pContextState->SetInvalidateAndFlushL2Cache(false);
        }
    }


    result = false;
    VkCommandBuffer commandBuffer = static_cast<VkCommandBuffer>(pSampleList);
    m_commandBuffer = commandBuffer;

    VkGpaSessionAMD gpaSession = VK_NULL_HANDLE;

    if (m_pContextState->GetGpaSessionForCommandList(m_commandBuffer, &gpaSession))
    {
        VkResult beginResult = _vkCmdBeginGpaSampleAMD(commandBuffer, gpaSession, &gpaSampleConfig, &m_sampleIndex);
        result = (beginResult == VK_SUCCESS);

        if (result)
        {
            SetActiveCountersCount(m_numCounters);
        }
    }
    else
    {
        result = false;
    }

    return result;
}

bool VkHardwareCounterDataRequest::EndRequest()
{
    VkGpaSessionAMD gpaSession = VK_NULL_HANDLE;
    bool result = m_pContextState->GetGpaSessionForCommandList(m_commandBuffer, &gpaSession);

    if (result)
    {
        _vkCmdEndGpaSampleAMD(m_commandBuffer, gpaSession, m_sampleIndex);
    }

    delete[] m_pCounterIds;
    return result;
}

void VkHardwareCounterDataRequest::ReleaseCounters()
{
}
