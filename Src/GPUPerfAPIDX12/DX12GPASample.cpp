//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Sample implementation
//==============================================================================

#include "DX12GPASample.h"
#include "DX12GPACommandList.h"

DX12GPASample::DX12GPASample(GPAPass* pPass,
                             IGPACommandList* pCmdList,
                             GpaSampleType sampleType,
                             ClientSampleId sampleId):
    GPASample(pPass, pCmdList, sampleType, sampleId)
{
    DX12GPACommandList* pDx12GpaCmdList = reinterpret_cast<DX12GPACommandList*>(pCmdList);
    pDx12GpaCmdList->AddGpaSample(this);
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

bool DX12GPASample::BeginRequest(IGPAContext* pContextState, const std::vector<gpa_uint32>* pCounters)
{
    // TODO: Come back when we are implementing software counters, see if we need this
    UNREFERENCED_PARAMETER(pContextState);
    UNREFERENCED_PARAMETER(pCounters);
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
                GPASampleResult* pSampleResult = reinterpret_cast<DX12GPASample*>(GetContinuingSample())->PopulateSampleResult();

                for (size_t counterIter = 0; counterIter < GetPass()->GetCounterCount(); counterIter++)
                {
                    GetSampleResultLocation()->m_pResultBuffer[counterIter] += pSampleResult->m_pResultBuffer[counterIter];
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

    return GetSampleResultLocation();
}

bool DX12GPASample::CopyResult(size_t sampleDataSize, void* pResultBuffer) const
{
    bool isDataReady = false;

    if (nullptr != pResultBuffer)
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
            GPA_LogError("Invalid profiling session encountered while copying results");
        }
        else
        {
            if (pResultSession->IsReady())
            {
                size_t sampleDataSizeInDriver = 0u;
                HRESULT driverResult = pResultSession->GetResults(GetDriverSampleId(), &sampleDataSizeInDriver, nullptr);
                assert(S_OK == driverResult);
                assert(sampleDataSize == sampleDataSizeInDriver);

                if (S_OK == driverResult && sampleDataSize == sampleDataSizeInDriver)
                {
                    driverResult = pResultSession->GetResults(GetDriverSampleId(), &sampleDataSizeInDriver, pResultBuffer);
                    assert(S_OK == driverResult);
                    if (S_OK == driverResult)
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