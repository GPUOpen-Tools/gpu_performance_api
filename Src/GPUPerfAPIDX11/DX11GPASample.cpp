//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
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

    if (GetPass()->IsTimingPass() &&
        nullptr != m_pGPUTimeCounter)
    {
        ID3D11DeviceContext* pD3D11DevicContext = nullptr;
        DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());
        DX11GPAContext* pdx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());
        pdx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DevicContext);

        if (nullptr != pD3D11DevicContext)
        {
            HRESULT gpuTimeResultStatus = pD3D11DevicContext->GetData(m_pGPUTimeCounter, nullptr, 0, 0);
            isComplete = S_OK == gpuTimeResultStatus;

            if (isComplete)
            {
                isComplete = PopulateResult();
            }
            else
            {
                GPA_LogDebugMessage("GPU Time data not yet ready");
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
            ID3D11DeviceContext* pD3D11DevicContext = nullptr;
            pDx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DevicContext);

            UINT gpuTimeCounterDataSize = m_pGPUTimeCounter->GetDataSize();
            assert(gpuTimeCounterDataSize == counterCount * sizeof(gpa_uint64));
            assert(1 == counterCount);

            //TODO: Now, it has been exactly like the way it was in previous implementation, but the data seems off.
            //      And why there is a need of two gpa_uint64 ?

            // TimeStamps 'may' return 2 gpa_uint64
            gpa_uint64 timingData[2];
            HRESULT hr = pD3D11DevicContext->GetData(m_pGPUTimeCounter, timingData, gpuTimeCounterDataSize, 0);

            assert(hr == S_OK);

            if (S_OK == hr)
            {
                // copy top data if requested
                if (GetPass()->GPUTimeTopToBottomPresent())
                {
                    *(pSampleResult->m_pResultBuffer) = timingData[0];
                }

                // copy bottom data if requested
                if (GetPass()->GPUTimeBottomToBottomPresent())
                {
                    *(pSampleResult->m_pResultBuffer) = timingData[1];
                }

                // copy GPUTimestamp data
                if (GetPass()->GPUTimestampTopPresent())
                {
                    *(pSampleResult->m_pResultBuffer) = timingData[0];
                }

                populated = true;
            }
        }
        else
        {


            for (size_t counterIter = 0; counterIter < counterCount; counterIter++)
            {
                pSampleResult->m_pResultBuffer[counterIter] = m_ppCounters[counterIter]->GetData();
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

bool DX11GPASample::BeginRequest()
{
    bool success = false;

    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());
    DX11GPAContext* pdx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());

    if (nullptr != pdx11GpaContext)
    {
        const GPA_HardwareCounters* pHardwareCounters = pdx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

        if (pDx11GpaPass->IsTimingPass())
        {
            ID3D11Device* pDevice = pdx11GpaContext->GetDevice();
            ID3D11DeviceContext* pDeviceContext = nullptr;
            pDevice->GetImmediateContext(&pDeviceContext);

            if (nullptr == m_pGPUTimeCounter &&
                nullptr != pDeviceContext)
            {
                bool timestampTopPresent = pDx11GpaPass->GPUTimestampTopPresent();

                // counter not created, create here
                D3D11_COUNTER_DESC ctrDesc;
                CounterIndex GPUTImebottomToBottomCounter = 0u;
                pDx11GpaPass->GetCounterByIndexInPass(pDx11GpaPass->GPUTimeBottomToBottomOffset(), GPUTImebottomToBottomCounter);
                ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[GPUTImebottomToBottomCounter].m_counterIdDriver);

                if (timestampTopPresent)
                {
                    CounterIndex GPUTimeTopCounter = 0u;
                    pDx11GpaPass->GetCounterByIndexInPass(pDx11GpaPass->GPUTimestampTopOffset(), GPUTimeTopCounter);
                    ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[GPUTimeTopCounter].m_counterIdDriver);
                }

                assert(ctrDesc.Counter != 0);
                ctrDesc.MiscFlags = 0;

                D3D11_COUNTER_TYPE type = D3D11_COUNTER_TYPE_FLOAT32;
                gpa_uint32 activeCounters = 0;
                gpa_uint32 numAvailableCounterSize = sizeof(gpa_uint32);
                HRESULT hr = pDevice->CheckCounter(&ctrDesc, &type, &activeCounters, nullptr, nullptr, nullptr, &numAvailableCounterSize, nullptr, nullptr);

                if (S_OK == hr)
                {
                    hr = pDevice->CreateCounter(&ctrDesc, &m_pGPUTimeCounter);

                    if (S_OK == hr)
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
            }
        }
        else
        {
            if (CreateSampleExperiment() &&
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
        }
    }
    else
    {
        if (nullptr != m_pExperiment)
        {
            m_pExperiment->End();
            success = true;
        }
    }

    return success;
}

void DX11GPASample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

bool DX11GPASample::CreateSampleExperiment()
{
    bool success = false;
    DX11GPAPass* pDx11GpaPass = reinterpret_cast<DX11GPAPass*>(GetPass());
    DX11GPAContext* pdx11GpaContext = reinterpret_cast<DX11GPAContext*>(pDx11GpaPass->GetGpaSession()->GetParentContext());

    if (nullptr != pdx11GpaContext)
    {
        IAmdDxExt* pDxExt = pdx11GpaContext->GetAmdDxExtension();
        IAmdDxExtPerfProfile* pExtPE = pdx11GpaContext->GetAmdProfileExtension();

        if ((nullptr == m_pExperiment) &&
            (nullptr != pExtPE) &&
            pDx11GpaPass->GetEnabledCounterCount() > 0)
        {
            // create correct version of experiment based on driver version
            if (DxxExtUtils::IsMgpuPerfExtSupported(pDxExt))
            {
                GPUIndex activeGPU = pdx11GpaContext->GetActiveGpu();

                if (pdx11GpaContext->GetCFActiveGpu() == activeGPU)
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

            const GPA_HardwareCounters* pHardwareCounters = pdx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

            if (nullptr != m_pExperiment)
            {
                auto AssignEngineParam = [&](CounterIndex counterIndex)->bool
                {
                    const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[counterIndex];
                    engineParamSetsuccess = true;

                    if (pCounter->m_groupIdDriver == PE_BLOCK_SQ)
                    {
                        // set all valid shader engines to the current stage mask
                        for (unsigned int ii = 0; ii < pdx11GpaContext->GetHwInfo()->GetNumberShaderEngines(); ii++)
                        {
                            SQEngineParamValue sqEngineParamValue;

                            if (pDx11GpaPass->GetSQEngineParamValue(counterIndex, sqEngineParamValue))
                            {
                                PE_RESULT result = m_pExperiment->SetEngineParam(ii, PE_PARAM_SQ_SHADER_MASK, sqEngineParamValue);

                                if (PE_OK != result)
                                {
                                    GPA_LogError("Unable to set the shader engine paramater.");
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
                    GPA_LogError("Unable to set engine params");
                }
            }
        }
        else
        {
            GPA_LogError("Either experiment is already created or AMD extenison is not available.");
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
    const GPA_HardwareCounters* pHardwareCounters = GetPass()->GetGpaSession()->GetParentContext()->GetCounterAccessor()->GetHardwareCounters();

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
                GPA_LogError("Unable to add counter to the experiment");
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

    return success;
}

