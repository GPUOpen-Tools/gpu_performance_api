//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#include "VkGPAHardwareSample.h"
#include "VkGPACommandList.h"
#include "VkGPAPass.h"
#include "GPAHardwareCounters.h"
#include "VkEntrypoints.h"
#include "GPAContextCounterMediator.h"

VkGPAHardwareSample::VkGPAHardwareSample(GPAPass* pPass,
                                         IGPACommandList* pCmdList,
                                         unsigned int sampleId,
                                         VkDevice device) :
    VkGPASample(pPass, pCmdList, GpaSampleType::Hardware, sampleId),
    m_numCounters(0),
    m_sampleIndex(0),
    m_device(device),
    m_commandBuffer(m_pVkGpaCmdList->GetVkCommandBuffer()),
    m_hasAnyHardwareCounters(false)
{
    VkGPACommandList* pVkGpaCmdList = dynamic_cast<VkGPACommandList*>(pCmdList);
    m_gpaSession = (nullptr != pVkGpaCmdList) ? pVkGpaCmdList->GetAmdExtSession() : VK_NULL_HANDLE;
}

VkGPAHardwareSample::~VkGPAHardwareSample()
{
    if (VK_NULL_HANDLE != m_commandBuffer)
    {
        m_commandBuffer = VK_NULL_HANDLE;
    }
}

bool VkGPAHardwareSample::BeginRequest()
{
    bool result = false;

    m_numCounters = GetPass()->GetEnabledCounterCount();
    m_hasAnyHardwareCounters = m_numCounters > 0;

    VkGPAPass* pVkGpaPass = dynamic_cast<VkGPAPass*>(GetPass());

    if (nullptr == pVkGpaPass)
    {
        GPA_LogError("Invalid GPAPass encountered in hardware sample begin request.");
    }
    else
    {
        if (GetPass()->IsTimingPass() || m_hasAnyHardwareCounters)
        {
            VkResult beginResult = _vkCmdBeginGpaSampleAMD(m_commandBuffer, m_gpaSession, pVkGpaPass->GetVkSampleBeginInfo(), &m_sampleIndex);
            result = (VK_SUCCESS == beginResult);

            if (result)
            {
                GPASample::SetDriverSampleId(m_sampleIndex);
            }
        }
        else
        {
            // Sample doesn't have any available hardware counters for this specific hardware revision, so we need to pretend this succeeded.
            result = true;
        }
    }

    return result;
}

bool VkGPAHardwareSample::EndRequest()
{
    if (GetPass()->IsTimingPass() || m_hasAnyHardwareCounters)
    {
        _vkCmdEndGpaSampleAMD(m_commandBuffer, m_gpaSession, m_sampleIndex);
    }

    return true;
}

void VkGPAHardwareSample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
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
    if (GetPass()->IsTimingPass())
    {
        sampleDataSize = 2 * sizeof(uint64_t);
    }
    else
    {
        sampleDataSize = GetSampleResultLocation()->GetBufferBytes();
    }

    gpa_uint64* pResultBuffer = nullptr;
    gpa_uint64 timingData[2];

    if (sampleDataSize > 0)
    {
        if (nullptr == GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer())
        {
            GPA_LogError("Incorrect space allocated for sample result.");
        }
        else
        {
            if (GetPass()->IsTimingPass())
            {
                pResultBuffer = timingData;
            }
            else
            {
                pResultBuffer = GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer();
            }

            if (CopyResult(sampleDataSize, pResultBuffer))
            {
                if (GetPass()->IsTimingPass())
                {
                    const GPA_HardwareCounters* pHardwareCounters = GetPass()->GetSessionContextCounterAccessor()->GetHardwareCounters();

                    for (CounterCount i = 0; i < GetPass()->GetEnabledCounterCount(); ++i)
                    {
                        CounterIndex counterIndex;
                        GetPass()->GetCounterByIndexInPass(i, &counterIndex);

                        if (counterIndex == pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[1] - timingData[0];
                        }
                        else if (counterIndex == pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[0];
                        }
                        else if (counterIndex == pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[1];
                        }
                        else if (counterIndex == pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[1] - timingData[0];
                        }
                        else if (counterIndex == pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[0];
                        }
                        else if (counterIndex == pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timingData[1];
                        }
                        else
                        {
                            GPA_LogError("Unknown timing counter.");
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = 0;
                        }
                    }
                }

                if (IsSampleContinuing())
                {
                    GPASampleResult* pSampleResult = dynamic_cast<VkGPAHardwareSample*>(GetContinuingSample())->PopulateSampleResults();

                    if (nullptr == pSampleResult)
                    {
                        GPA_LogError("Invalid GPASample encountered when populating results of continued sample.");
                    }
                    else
                    {
                        for (size_t counterIter = 0; counterIter < GetSampleResultLocation()->GetAsCounterSampleResult()->GetNumCounters(); counterIter++)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[counterIter] += pSampleResult->GetAsCounterSampleResult()->GetResultBuffer()[counterIter];
                        }
                    }
                }

                MarkAsCompleted();
            }
            else
            {
                GPA_LogError("Unable to get the result from the driver.");
            }
        }
    }

    return GetSampleResultLocation();
}

bool VkGPAHardwareSample::CopyResult(size_t sampleDataSize, void* pResultBuffer) const
{
    bool isDataReady = false;

    if (nullptr != pResultBuffer)
    {
        VkGPACommandList* pVkGpaCmdList = dynamic_cast<VkGPACommandList*>(GetCmdList());

        if (nullptr == pVkGpaCmdList)
        {
            GPA_LogError("Invalid GPACommandList encountered while copying hardware counter results.");
        }
        else
        {
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

            VkGPAContext* pVkGPAContext = dynamic_cast<VkGPAContext*>(pVkGpaCmdList->GetParentSession()->GetParentContext());

            if (nullptr == pVkGPAContext)
            {
                GPA_LogError("Invalid GPAContext encountered while copying hardware counter results.");
            }
            else
            {
                VkDevice vkDevice = pVkGPAContext->GetVkDevice();

                if (VK_NULL_HANDLE == extSession)
                {
                    GPA_LogError("Invalid profiling session encountered while copying results.");
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
                                GPA_LogError("Error occurred while getting sample results from driver.");
                            }
                        }
                        else
                        {
                            GPA_LogError("Error occurred while getting sample result size from driver.");
                        }
                    }
                }
            }
        }
    }

    return isDataReady;
}
