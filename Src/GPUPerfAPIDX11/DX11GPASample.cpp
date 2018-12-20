//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 GPA Sample Implementation
//==============================================================================

#include "DxxExtUtils.h"
#include "DX11GPAContext.h"
#include "GPAHardwareCounters.h"
#include "GPAPass.h"
#include "DX11GPASample.h"
#include "DX11GPAPass.h"
#include "GPAContextCounterMediator.h"

/// Macro to assert on a PerfExperiment error
#ifdef _DEBUG
#define ASSERT_ON_PE_ERROR(result) if (result == PE_ERROR_OUT_OF_RESOURCES) assert(!(result == PE_ERROR_OUT_OF_RESOURCES));\
    if (result == PE_ERROR_INVALID_ARGUMENT) assert(!(result == PE_ERROR_INVALID_ARGUMENT));\
    if (result == PE_ERROR_FINALIZED) assert(!(result == PE_ERROR_FINALIZED));\
    if (result == PE_ERROR_UNAVAILABLE) assert(!(result == PE_ERROR_UNAVAILABLE));\
    if (result == PE_ERROR_RESOURCE_BUSY) assert(!(result == PE_ERROR_RESOURCE_BUSY));\
    if (result == PE_ERROR_OUT_OF_MEMORY) assert(!(result == PE_ERROR_OUT_OF_MEMORY));\
    if (result == PE_ERROR_NOT_SUPPORTED) assert(!(result == PE_ERROR_NOT_SUPPORTED));
#else
#define ASSERT_ON_PE_ERROR(result)
#endif


DX11GPASample::~DX11GPASample()
{
    ReleaseSampleResources();
}

DX11GPASample::DX11GPASample(GPAPass* pPass,
                             IGPACommandList* pCmdList,
                             GpaSampleType sampleType,
                             ClientSampleId sampleId) :
    GPASample(pPass, pCmdList, sampleType, sampleId),
    m_pExperiment(nullptr),
    m_ppCounters(nullptr),
    m_pGPUTimeCounter(nullptr)
{
}

bool DX11GPASample::UpdateResults()
{
    bool isComplete = false;
    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());

    if (GetPass()->IsTimingPass() &&
        nullptr != m_pGPUTimeCounter)
    {
        ID3D11DeviceContext* pD3D11DeviceContext = nullptr;
        DX11GPAContext* pdx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());
        pdx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DeviceContext);

        if (nullptr != pD3D11DeviceContext)
        {
            HRESULT gpuTimeResultStatus = pD3D11DeviceContext->GetData(m_pGPUTimeCounter, nullptr, 0, 0);

            if (FAILED(gpuTimeResultStatus))
            {
                GPA_LogError("Call to ID3D11DeviceContext::GetData failed.");
            }
            else
            {
                isComplete = S_OK == gpuTimeResultStatus; // S_OK == data ready; S_FALSE == data not ready
                pD3D11DeviceContext->Release();

                if (isComplete)
                {
                    isComplete = PopulateResult();
                }
                else
                {
                    GPA_LogDebugMessage("GPU Time data not yet ready.");
                }
            }
        }
    }
    else if (nullptr != m_pExperiment)
    {
        BOOL retVal = m_pExperiment->WaitCompletion(10);

        if (retVal && PopulateResult())
        {
            isComplete = true;
        }
    }
    else if (0 == pDx11GpaPass->GetEnabledCounterCount())
    {
        // if there are no actual hardware counters in this sample, then indicate results are ready
        isComplete = true;
    }

    return isComplete;
}

bool DX11GPASample::PopulateResult()
{
    bool populated = false;
    GPASampleResult* pSampleResult = GetSampleResultLocation();

    if (nullptr != pSampleResult)
    {
        size_t counterCount = GetPass()->GetEnabledCounterCount();

        if (GetPass()->IsTimingPass() &&
            nullptr != m_pGPUTimeCounter)
        {
            DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(GetPass()->GetGpaSession()->GetParentContext());
            ID3D11DeviceContext* pD3D11DeviceContext = nullptr;
            pDx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DeviceContext);

            if (nullptr != pD3D11DeviceContext)
            {
                UINT gpuTimeCounterDataSize = m_pGPUTimeCounter->GetDataSize();

                if ((1 != counterCount) || (gpuTimeCounterDataSize != counterCount * sizeof(gpa_uint64)))
                {
                    GPA_LogError("Call to DX11 PopulateResult encountered invalid number of counters, or invalid number of bytes.");
                    return false;
                }

                // An array of 2x gpa_uint64 is passed to ID3D11DeviceContext::GetData
                // However, note that the size of the array passed to the API is 1x gpa_uint64
                // The driver writes 2x gpa_uint64 values
                // Passing a single gpa_uint64 array will cause a trailing memory overwrite
                // Passing the actual size of the array will cause a Direct3D11 error
                // Therefore, this may appear to be incorrect, but it's actually correct
                gpa_uint64 timingData[2] = {};

                HRESULT hr = pD3D11DeviceContext->GetData(m_pGPUTimeCounter, &timingData, gpuTimeCounterDataSize, 0);

                // The above should never return S_FALSE (data not ready) because UpdateResults will only call this function
                // if it has determined that the data is ready
                assert(S_FALSE != hr);

                if (SUCCEEDED(hr))
                {
                    // copy top data if requested
                    if (GetPass()->GetTopToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                    {
                        *pSampleResult->GetAsCounterSampleResult()->GetResultBuffer() = timingData[0];
                    }

                    // copy bottom data if requested
                    if (GetPass()->GetBottomToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                    {
                        *pSampleResult->GetAsCounterSampleResult()->GetResultBuffer() = timingData[1];
                    }

                    populated = true;
                }
                else
                {
                    assert(SUCCEEDED(hr));
                    GPA_LogError("Call to ID3D11DeviceContext::GetData failed.");
                }

                pD3D11DeviceContext->Release();
            }
        }
        else
        {
            for (size_t counterIter = 0; counterIter < counterCount; counterIter++)
            {
                pSampleResult->GetAsCounterSampleResult()->GetResultBuffer()[counterIter] = m_ppCounters[counterIter]->GetData();
            }

            populated = true;
        }
    }

    if (populated)
    {
        MarkAsCompleted();
    }

    return populated;
}

void DX11GPASample::ReleaseSampleResources()
{
    if (nullptr != m_ppCounters)
    {
        delete[] m_ppCounters;
        m_ppCounters = nullptr;
    }

    if (nullptr != m_pExperiment)
    {
        m_pExperiment->ReleaseResources();
        m_pExperiment->Destroy();
        m_pExperiment = nullptr;
    }

    if (nullptr != m_pGPUTimeCounter)
    {
        m_pGPUTimeCounter->Release();
        m_pGPUTimeCounter = nullptr;
    }
}

bool DX11GPASample::BeginRequest()
{
    bool success = false;

    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());
    DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());

    if (nullptr != pDx11GpaContext)
    {
        IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(pDx11GpaContext);
        const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

        if (pDx11GpaPass->IsTimingPass())
        {
            ID3D11Device* pDevice = pDx11GpaContext->GetDevice();
            ID3D11DeviceContext* pDeviceContext = nullptr;
            pDevice->GetImmediateContext(&pDeviceContext);

            if (nullptr == m_pGPUTimeCounter &&
                nullptr != pDeviceContext)
            {
                // counter not created, create here
                D3D11_COUNTER_DESC ctrDesc = {};
                ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex].m_counterIdDriver);

                if (pDx11GpaPass->GetTopToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                {
                    ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex].m_counterIdDriver);
                }

                assert(ctrDesc.Counter != 0);
                ctrDesc.MiscFlags = 0;

                D3D11_COUNTER_TYPE type = D3D11_COUNTER_TYPE_FLOAT32;
                gpa_uint32 activeCounters = 0;
                gpa_uint32 numAvailableCounterSize = sizeof(gpa_uint32);
                HRESULT hr = pDevice->CheckCounter(&ctrDesc, &type, &activeCounters, nullptr, nullptr, nullptr, &numAvailableCounterSize, nullptr, nullptr);

                if (SUCCEEDED(hr))
                {
                    hr = pDevice->CreateCounter(&ctrDesc, &m_pGPUTimeCounter);

                    if (SUCCEEDED(hr))
                    {
                        pDeviceContext->Begin(m_pGPUTimeCounter);
                        success = true;
                    }
                    else
                    {
                        GPA_LogDebugError("Call to ID3D11Device::CreateCounter failed on the GPUTime counter.");
                        GPA_LogError("Call to ID3D11Device::CreateCounter failed.");
                        pDeviceContext->Release();
                    }
                }
                else
                {
                    // make sure any counters which worked are released
                    GPA_LogDebugError("Call to ID3D11Device::CheckCounter failed on the GPUTime counter.");
                    pDeviceContext->Release();
                }

                pDeviceContext->Release();
            }
        }
        else
        {
            if (0 == pDx11GpaPass->GetEnabledCounterCount())
            {
                // if there are no actual hardware counters in this sample, log a debug message and return true
                GPA_LogDebugMessage("No counters enabled in this sample.");
                success = true;
            }
            else if (CreateSampleExperiment() &&
                     CreateAndAddCounterToExperiment())
            {
                // finalize the experiment
                PE_RESULT result = m_pExperiment->Finalize();

                if (PE_OK == result)
                {
                    result = m_pExperiment->Begin();

                    if (PE_OK == result)
                    {
                        success = true;
                    }
                    else
                    {
                        ASSERT_ON_PE_ERROR(result);
                        GPA_LogDebugError("Call to IPerfExperiment::Begin failed.");
                    }
                }
                else
                {
                    if (result == PE_ERROR_OUT_OF_MEMORY)
                    {
                        GPA_LogError("Counter could not be enabled due to an Out Of Memory error.");
                    }
                    else
                    {
                        ASSERT_ON_PE_ERROR(result);
                        GPA_LogDebugError("Call to IPerfExperiment::Finalize failed.");
                    }
                }
            }
            else
            {
                GPA_LogError("Unable to create the sample experiment or unable to initialize the counters.");
            }
        }
    }

    return success;
}

bool DX11GPASample::EndRequest()
{
    bool success = false;

    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());

    if (pDx11GpaPass->IsTimingPass())
    {
        DX11GPAContext* pdx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());
        ID3D11Device* pD3dDevice = pdx11GpaContext->GetDevice();
        ID3D11DeviceContext* pDeviceContext = nullptr;
        pD3dDevice->GetImmediateContext(&pDeviceContext);

        if (nullptr != pDeviceContext)
        {
            pDeviceContext->End(m_pGPUTimeCounter);
            success = true;
            pDeviceContext->Release();
        }
    }
    else
    {
        if (nullptr != m_pExperiment)
        {
            m_pExperiment->End();
            success = true;
        }
        else if (0 == pDx11GpaPass->GetEnabledCounterCount())
        {
            // if there are no actual hardware counters in this sample, return true
            success = true;
        }
    }

    return success;
}

void DX11GPASample::ReleaseCounters()
{
    ReleaseSampleResources();
}

bool DX11GPASample::CreateSampleExperiment()
{
    bool success = false;
    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());
    DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());

    if (nullptr != pDx11GpaContext)
    {
        IAmdDxExt* pDxExt = pDx11GpaContext->GetAmdDxExtension();
        IAmdDxExtPerfProfile* pExtPE = pDx11GpaContext->GetAmdProfileExtension();

        if (0 == pDx11GpaPass->GetEnabledCounterCount())
        {
            GPA_LogDebugMessage("No counters enabled in this sample.");
        }
        else
        {
            if ((nullptr == m_pExperiment) &&
                (nullptr != pExtPE))
            {
                // create correct version of experiment based on driver version
                if (DxxExtUtils::IsMgpuPerfExtSupported(pDxExt))
                {
                    GPUIndex activeGPU = pDx11GpaContext->GetActiveGpu();

                    if (pDx11GpaContext->GetCFActiveGpu() == activeGPU)
                    {
                        // When checking block limits, if in Crossfire mode, always use GPU zero; if in PX mode, use the active GPU
                        activeGPU = 0;

                        // In CF/ACF scenario let the driver create the experiment on the
                        // current frame active GPU
                        m_pExperiment = pExtPE->CreateExperiment();
                    }
                    else
                    {
                        m_pExperiment = pExtPE->CreateExperimentEx(activeGPU);
                    }
                }
                else
                {
                    m_pExperiment = pExtPE->CreateExperiment();
                }

                bool engineParamSetsuccess = true;

                IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(pDx11GpaContext);
                const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

                if (nullptr != m_pExperiment)
                {
                    auto AssignEngineParam = [&](CounterIndex counterIndex)->bool
                    {
                        const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[counterIndex];
                        engineParamSetsuccess = true;

                        if (pCounter->m_groupIdDriver == PE_BLOCK_SQ)
                        {
                            // set all valid shader engines to the current stage mask
                            for (unsigned int ii = 0; ii < pDx11GpaContext->GetHwInfo()->GetNumberShaderEngines(); ii++)
                            {
                                SQEngineParamValue sqEngineParamValue;

                                if (pDx11GpaPass->GetSQEngineParamValue(counterIndex, sqEngineParamValue))
                                {
                                    PE_RESULT result = m_pExperiment->SetEngineParam(ii, PE_PARAM_SQ_SHADER_MASK, sqEngineParamValue);

                                    if (PE_OK != result)
                                    {
                                        GPA_LogError("Unable to set the shader engine parameter.");
                                        engineParamSetsuccess = false;
                                        break;
                                    }
                                }
                            }
                        }

                        return engineParamSetsuccess;
                    };

                    pDx11GpaPass->IterateEnabledCounterList(AssignEngineParam);

                    success = engineParamSetsuccess;

                    if (!success)
                    {
                        GPA_LogError("Unable to set engine params.");
                    }
                }
            }
            else
            {
                GPA_LogError("Either the experiment has already been created or the driver extension is not available.");
            }
        }
    }

    return success;
}

bool DX11GPASample::CreateAndAddCounterToExperiment()
{
    // Assuming things will succeed; gets set to false if an error occurs
    bool success = true;
    assert(nullptr == m_ppCounters);

    CounterCount enabledCounterCount = GetPass()->GetEnabledCounterCount();
    CounterCount enabledCounterCountIndex = 0;
    m_ppCounters = new(std::nothrow) IAmdDxExtPerfCounter*[enabledCounterCount];

    if (nullptr != m_ppCounters)
    {
        IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(GetPass()->GetGpaSession()->GetParentContext());
        const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

        auto AddCounterToExperiment = [&](CounterIndex counterIndex)->bool
        {
            success = true;
            // need to Add a counter
            const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[counterIndex];
            UINT32 instance = static_cast<unsigned int>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);

            // add valid counters to the experiment
            PE_RESULT result = PE_ERROR_NOT_SUPPORTED;

            if (nullptr != m_pExperiment)
            {
                result = m_pExperiment->AddCounter(static_cast<PE_BLOCK_ID>(pCounter->m_groupIdDriver),
                instance,
                static_cast<UINT>(pCounter->m_pHardwareCounter->m_counterIndexInGroup),
                &m_ppCounters[enabledCounterCountIndex]);

                if (PE_OK != result)
                {
                    success = false;
                    GPA_LogError("Unable to add counter to the experiment.");
                }

                if (pCounter->m_groupIdDriver == PE_BLOCK_SQ)
                {
                    result = m_ppCounters[enabledCounterCountIndex]->SetParam(PE_COUNTER_SQ_SIMD_MASK, 0xF);

                    if (result != PE_OK)
                    {
                        ASSERT_ON_PE_ERROR(result);
                        GPA_LogDebugError("call to IAmdDxExtPerfCounter::SetParam failed.");
                    }
                }

                enabledCounterCountIndex++;
            }

            return success;
        };

        DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());

        pDx11GpaPass->IterateEnabledCounterList(AddCounterToExperiment);

        if (!success)
        {
            // If not successful, delete allocations
            delete[] m_ppCounters;
            m_ppCounters = nullptr;
        }
    }
    else
    {
        GPA_LogError("Unable to allocate memory for performance counters.");
        success = false;
    }

    return success;
}

