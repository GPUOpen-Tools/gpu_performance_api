//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#include "VkGPAHardwareSample.h"
#include "VkGPACommandList.h"
#include "GPAHardwareCounters.h"
#include "VkEntrypoints.h"
#include "vk_amd_gpa_interface.h"

VkGPAHardwareSample::VkGPAHardwareSample(GPAPass* pPass,
    IGPACommandList* pCmdList,
    unsigned int sampleId,
    VkDevice device) :
    VkGPASample(pPass, pCmdList, GpaSampleType::Hardware, sampleId),
    m_pContextState(nullptr),
    m_pCounterIds(nullptr),
    m_numCounters(0),
    m_sampleIndex(0),
    m_device(device),
    m_commandBuffer(m_pVkGpaCmdList->GetVkCommandBuffer()),
    m_isTimingRequest(false)
{
    VkGPACommandList* pVkGpaCmdList = static_cast<VkGPACommandList*>(pCmdList);
    m_gpaSession = (nullptr != pVkGpaCmdList) ? pVkGpaCmdList->GetAmdExtSession() : VK_NULL_HANDLE;
}

VkGPAHardwareSample::~VkGPAHardwareSample()
{
    if (VK_NULL_HANDLE != m_commandBuffer)
    {
        m_commandBuffer = VK_NULL_HANDLE;
    }
}

bool VkGPAHardwareSample::BeginRequest(IGPAContext* pContextState,
                                       const std::vector<gpa_uint32>* pCounters)
{
    bool result = true;

    m_pContextState = reinterpret_cast<VkGPAContext*>(pContextState);

    VkGpaSampleBeginInfoAMD gpaSampleConfig = { };
    gpaSampleConfig.sType = VK_STRUCTURE_TYPE_GPA_SAMPLE_BEGIN_INFO_AMD;

    const IGPACounterAccessor* pCounterAccessor = m_pContextState->GetCounterAccessor();
    const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

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

            m_pCounterIds = new(std::nothrow) VkGpaPerfCounterAMD[gpaSampleConfig.perfCounterCount];

            if (nullptr == m_pCounterIds)
            {
                GPA_LogError("Insufficient memory to allocate counters.");
                return false;
            }

            // add all desired counters
            for (size_t i = 0; i < pCounters->size(); i++)
            {
                const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[i]];
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
        if (pContextState->IsInvalidateAndFlushL2CacheEnabled())
        {
            gpaSampleConfig.cacheFlushOnCounterCollection = true;
            pContextState->SetInvalidateAndFlushL2Cache(false);
        }
    }

    result = false;

    VkResult beginResult = _vkCmdBeginGpaSampleAMD(m_commandBuffer, m_gpaSession, &gpaSampleConfig, &m_sampleIndex);
    result = (beginResult == VK_SUCCESS);

    if (result)
    {
        GPASample::SetDriverSampleId(m_sampleIndex);
    }

    return result;
}

bool VkGPAHardwareSample::EndRequest()
{
    _vkCmdEndGpaSampleAMD(m_commandBuffer, m_gpaSession, m_sampleIndex);

    delete[] m_pCounterIds;
    return true;
}

void VkGPAHardwareSample::ReleaseCounters()
{
}

bool VkGPAHardwareSample::UpdateResults()
{
    if (GPASampleState::RESULTS_COLLECTED == GetGpaSampleState())
    {
        return true;
    }

    bool isUpdated = false;

    // samples that are the original secondary samples will not have results
    if (IsSecondary() && !IsCopied())
    {
        MarkAsCompleted();
        isUpdated = true;
    }

    if (GPASampleState::PENDING_RESULTS == GetGpaSampleState())
    {
        isUpdated = (nullptr != PopulateSampleResults());
    }

    return isUpdated;
}

GPASampleResult* VkGPAHardwareSample::PopulateSampleResults()
{
    size_t sampleDataSize = 0u;

    // Validate result space
    if (!GetPass()->IsTimingPass())
    {
        sampleDataSize = GetSampleResultLocation()->m_numCounters * sizeof(gpa_uint64);
    }
    else
    {
        // If the pass is timing, we will have one result space to return the result, although
        // we need to get the result in twice space size from the driver
        sampleDataSize = GetSampleResultLocation()->m_numCounters * 2 * sizeof(gpa_uint64);
    }

    gpa_uint64* pResultBuffer = nullptr;
    gpa_uint64 timingData[2];

    if (nullptr != GetSampleResultLocation()->m_pResultBuffer)
    {
        if (GetPass()->IsTimingPass())
        {
            pResultBuffer = timingData;
        }
        else
        {
            pResultBuffer = GetSampleResultLocation()->m_pResultBuffer;
        }

        if (CopyResult(sampleDataSize, pResultBuffer))
        {
            if (GetPass()->IsTimingPass())
            {
                // There will be one counter result space for this
                *(GetSampleResultLocation()->m_pResultBuffer) = timingData[1] - timingData[0];
            }

            if (IsSampleContinuing())
            {
                GPASampleResult* pSampleResult = reinterpret_cast<VkGPAHardwareSample*>(GetContinuingSample())->PopulateSampleResults();

                for (size_t counterIter = 0; counterIter < GetSampleResultLocation()->m_numCounters; counterIter++)
                {
                    GetSampleResultLocation()->m_pResultBuffer[counterIter] += pSampleResult->m_pResultBuffer[counterIter];
                }
            }

            MarkAsCompleted();
        }
        else
        {
            GPA_LogError("Unable to get the result from the driver");
        }
    }
    else
    {
        GPA_LogError("Incorrect space allocated for sample result");
    }

    return GetSampleResultLocation();
}

bool VkGPAHardwareSample::CopyResult(size_t sampleDataSize, void* pResultBuffer) const
{
    bool isDataReady = false;

    if (nullptr != pResultBuffer)
    {
        VkGPACommandList* pVkGpaCmdList = reinterpret_cast<VkGPACommandList*>(GetCmdList());

        VkGpaSessionAMD extSession = pVkGpaCmdList->GetAmdExtSession();

        if (IsCopied())
        {
            extSession = pVkGpaCmdList->GetCopiedAmdExtSession(GetClientSampleId());
            assert(VK_NULL_HANDLE != extSession);
        }
        else
        {
            extSession = pVkGpaCmdList->GetAmdExtSession();
            assert(VK_NULL_HANDLE != extSession);
        }

        VkGPAContext* pVkGPAContext = static_cast<VkGPAContext*>(pVkGpaCmdList->GetParentSession()->GetParentContext());
        VkDevice vkDevice = pVkGPAContext->GetVkDevice();

        if (VK_NULL_HANDLE == extSession)
        {
            GPA_LogError("Invalid profiling session encountered while copying results");
        }
        else
        {
            VkResult isReady = _vkGetGpaSessionStatusAMD(pVkGPAContext->GetVkDevice(), extSession);

            if (VK_SUCCESS == isReady)
            {
                size_t sampleDataSizeInDriver = 0u;
                VkResult gotResultSize = _vkGetGpaSessionResultsAMD(vkDevice, extSession, GetDriverSampleId(), &sampleDataSizeInDriver, nullptr);
                assert(VK_SUCCESS == gotResultSize);
                assert(sampleDataSize == sampleDataSizeInDriver);

                if (VK_SUCCESS == gotResultSize && sampleDataSize == sampleDataSizeInDriver)
                {
                    VkResult gotResults = _vkGetGpaSessionResultsAMD(vkDevice, extSession, GetDriverSampleId(), &sampleDataSizeInDriver, pResultBuffer);
                    assert(VK_SUCCESS == gotResults);
                    if (VK_SUCCESS == gotResults)
                    {
                        isDataReady = true;
                    }
                    else
                    {
                        GPA_LogError("Error occurred while getting sample results from driver");
                    }
                }
                else
                {
                    GPA_LogError("Error occurred while getting sample result size from driver");
                }
            }
        }
    }

    return isDataReady;
}
