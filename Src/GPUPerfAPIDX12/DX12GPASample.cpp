//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Sample implementation
//==============================================================================

#include "DX12GPASample.h"
#include "DX12GPACommandList.h"
#include "GPAHardwareCounters.h"
#include "GPAContextCounterMediator.h"

DX12GPASample::DX12GPASample(GPAPass* pPass,
                             IGPACommandList* pCmdList,
                             GpaSampleType sampleType,
                             ClientSampleId sampleId):
    GPASample(pPass, pCmdList, sampleType, sampleId)
{
}

bool DX12GPASample::UpdateResults()
{
    if (GPASampleState::RESULTS_COLLECTED == GetGpaSampleState())
    {
        return true;
    }

    bool isUpdated = false;

    if (IsSecondary())
    {
        MarkAsCompleted();
        isUpdated = true;
    }

    if (GPASampleState::PENDING_RESULTS == GetGpaSampleState() && !IsSecondary())
    {
        isUpdated = (nullptr != PopulateSampleResult());
    }

    return isUpdated;
}

bool DX12GPASample::BeginRequest()
{
    // TODO: Come back when we are implementing software counters, see if we need this
    return true;
}

bool DX12GPASample::EndRequest()
{
    // TODO: Come back when we are implementing software counters, see if we need this
    return true;
}

void DX12GPASample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

GPASampleResult* DX12GPASample::PopulateSampleResult()
{
    size_t sampleDataBytes = 0u;

    // Validate result space
    sampleDataBytes = GetSampleResultLocation()->GetBufferBytes();

    if (0 != sampleDataBytes)
    {
        if (nullptr != GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer())
        {
            gpa_uint64* pResultBuffer = nullptr;
            gpa_uint64 timingData[2] = {};

            if (GetPass()->IsTimingPass())
            {
                pResultBuffer = timingData;
                sampleDataBytes = sizeof(timingData);
            }
            else
            {
                pResultBuffer = GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer();
            }

            if (CopyResult(sampleDataBytes, pResultBuffer))
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
                    GPASampleResult* pSampleResult = reinterpret_cast<DX12GPASample*>(GetContinuingSample())->PopulateSampleResult();

                    for (size_t counterIter = 0; counterIter < GetPass()->GetEnabledCounterCount(); counterIter++)
                    {
                        GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[counterIter] += pSampleResult->GetAsCounterSampleResult()->GetResultBuffer()[counterIter];
                    }
                }

                MarkAsCompleted();
            }
            else
            {
                GPA_LogError("Unable to get the result from the driver.");
            }
        }
        else
        {
            GPA_LogError("Incorrect space allocated for sample result.");
        }
    }

    return GetSampleResultLocation();
}

bool DX12GPASample::CopyResult(size_t sampleDataSize, void* pResultBuffer) const
{
    bool isDataReady = false;
    bool isAnyHardwareCounterEnabled = GetPass()->GetEnabledCounterCount() > 0;

    if (nullptr != pResultBuffer)
    {
        if (isAnyHardwareCounterEnabled)
        {
            DX12GPACommandList* pDX12GpaCmdList = reinterpret_cast<DX12GPACommandList*>(GetCmdList());

            IAmdExtGpaSession* pResultSession = nullptr;

            if (IsCopied())
            {
                pResultSession = pDX12GpaCmdList->GetBundleResultAmdExtSession(GetClientSampleId());
            }
            else
            {
                pResultSession = pDX12GpaCmdList->GetAmdExtSession();
            }

            if (nullptr == pResultSession)
            {
                GPA_LogError("Invalid profiling session encountered while copying results.");
            }
            else
            {
                if (pResultSession->IsReady())
                {
                    size_t sampleDataSizeInDriver = 0u;
                    HRESULT driverResult = pResultSession->GetResults(GetDriverSampleId(), &sampleDataSizeInDriver, nullptr);
                    assert(SUCCEEDED(driverResult));
                    assert(sampleDataSize == sampleDataSizeInDriver);

                    if (SUCCEEDED(driverResult) && sampleDataSize == sampleDataSizeInDriver)
                    {
                        driverResult = pResultSession->GetResults(GetDriverSampleId(), &sampleDataSizeInDriver, pResultBuffer);
                        assert(SUCCEEDED(driverResult));

                        if (SUCCEEDED(driverResult))
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
        else
        {
            // there is no hardware counter enabled in the driver, put zeros in all result location
            memcpy(pResultBuffer, 0, sampleDataSize);
            isDataReady = true;
        }
    }

    return isDataReady;
}