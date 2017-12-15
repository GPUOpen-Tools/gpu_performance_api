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

DX11GPASample::GpuBlockInstanceLimitMap DX11GPASample::ms_blockInstanceLimits;

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
    m_pGPUTimeCounter(nullptr),
    m_gpuToCheckBlockLimits()
{
    if (nullptr != pPass)
    {
        IGPASession* pGpaSession = pPass->GetGpaSession();

        if (nullptr != pGpaSession)
        {
            m_pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(pGpaSession->GetParentContext());
        }
    }
}

bool DX11GPASample::UpdateResults()
{
    bool isComplete = false;

    if (m_pPass->IsTimingPass() && nullptr != m_pGPUTimeCounter && nullptr != m_pDx11GpaContext)
    {
        ID3D11DeviceContext* pD3D11DevicContext = nullptr;
        m_pDx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DevicContext);

        if (nullptr != pD3D11DevicContext)
        {
            HRESULT gpuTimeResultStatus = pD3D11DevicContext->GetData(m_pGPUTimeCounter, nullptr, 0, 0);
            isComplete = S_OK == gpuTimeResultStatus;
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

bool DX11GPASample::BeginRequest(IGPAContext* pContextState, const std::vector<gpa_uint32>* pCounters)
{
    bool success = false;

    if (nullptr != pContextState &&
        nullptr == m_pDx11GpaContext)
    {
        m_pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(pContextState);
    }

    if (nullptr != m_pDx11GpaContext)
    {
        const GPA_HardwareCounters* pHardwareCounters = m_pDx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

        if (GetPass()->IsTimingPass())
        {
            ID3D11Device* pDevice = m_pDx11GpaContext->GetDevice();
            ID3D11DeviceContext* pDeviceContext = nullptr;
            pDevice->GetImmediateContext(&pDeviceContext);

            if (nullptr == m_pGPUTimeCounter && nullptr != pDeviceContext)
            {
                bool timestampTopPresent = GetPass()->GPUTimestampTopPresent();

                // counter not created, create here
                D3D11_COUNTER_DESC ctrDesc;
                ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[(*pCounters)[GetPass()->GPUTimeBottomToBottomOffset()]].m_counterIdDriver);

                if (timestampTopPresent)
                {
                    ctrDesc.Counter = static_cast<D3D11_COUNTER>(pHardwareCounters->m_counters[(*pCounters)[GetPass()->GPUTimestampTopOffset()]].m_counterIdDriver);
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

                    if(S_OK == hr)
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
            if (CreateSampleExperiment(pCounters) &&
                InitializeCounters(pCounters))
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

    if (GetPass()->IsTimingPass())
    {
        ID3D11Device* pD3dDevice = m_pDx11GpaContext->GetDevice();
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

bool DX11GPASample::GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo) const
{
    // Note: if using an older driver (one that doesn't support the new Perf Experiment interface -- see IsMgpuPerfExpSupported)
    //       gpuID will be 0. However, looking at driver sources, the imlpementation of GetBlockCounterInfo in those older
    //       drivers ignores this parameter anyway

    PE_RESULT result = PE_ERROR_UNAVAILABLE;

    if (nullptr != m_pDx11GpaContext)
    {
        IAmdDxExtPerfProfile* pExtPE = m_pDx11GpaContext->GetAmdProfileExtension();
        result = pExtPE->GetBlockCounterInfo(gpuID, block, pBlockInfo);

        if (PE_OK != result)
        {
            GPA_LogError("Error querying Block Counter Info.");
            GPA_LogDebugError("  GPU: %d, Block %d.", gpuID, block);
        }
    }

    return result == PE_OK;
}

bool DX11GPASample::CreateSampleExperiment(const std::vector<gpa_uint32>* pCounters)
{
    bool success = false;

    if (nullptr != m_pDx11GpaContext)
    {
        IAmdDxExt* pDxExt = m_pDx11GpaContext->GetAmdDxExtension();
        IAmdDxExtPerfProfile* pExtPE = m_pDx11GpaContext->GetAmdProfileExtension();

        if ((nullptr == m_pExperiment) && (nullptr != pExtPE))
        {
            m_gpuToCheckBlockLimits = GetActiveGpu();

            // create correct version of experiment based on driver version
            if (DxxExtUtils::IsMgpuPerfExtSupported(pDxExt))
            {
                if (ms_activeGpuCF == m_gpuToCheckBlockLimits)
                {
                    // When checking block limits, if in Crossfire mode, always use GPU zero; if in PX mode, use the active GPU
                    m_gpuToCheckBlockLimits = 0;

                    // In CF/ACF scenario let the driver create the experiment on the
                    // current frame active GPU
                    m_pExperiment = pExtPE->CreateExperiment();
                }
                else
                {
                    m_pExperiment = pExtPE->CreateExperimentEx(m_gpuToCheckBlockLimits);
                }
            }

            m_pExperiment = pExtPE->CreateExperiment();

            PopulateBlockInstanceLimits(m_gpuToCheckBlockLimits);
            success = SetExperimentParams(pCounters);
        }
        else
        {
            GPA_LogError("Either experiment is already created or AMD extenison is not available.");
        }
    }

    return success;
}

bool DX11GPASample::InitializeCounters(const std::vector<gpa_uint32>* pCounters)
{
    // Assuming things will succeed; gets set to false if an error occurs
    bool success = true;
    assert(nullptr == m_ppCounters);

    m_ppCounters = new(std::nothrow) IAmdDxExtPerfCounter*[pCounters->size()];

    const GPA_HardwareCounters* pHardwareCounters = m_pDx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

    for (size_t counterIter = 0; counterIter < pCounters->size(); counterIter++)
    {
        // need to Add a counter
        const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[counterIter]];
        unsigned int instance = static_cast<unsigned int>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);

        // On mid and low end hardware, not all block instances are available. This logic makes sure that we only attempt to
        // enable counters for block instances which exist.
        bool dontEnableCounter = false;

        if (ms_blockInstanceLimits.find(m_gpuToCheckBlockLimits) != ms_blockInstanceLimits.end())
        {
            BlockInstanceLimitMap blockLimits = ms_blockInstanceLimits[m_gpuToCheckBlockLimits];
            PE_BLOCK_ID blockId = static_cast<PE_BLOCK_ID>(pCounter->m_groupIdDriver);

            if (instance >= blockLimits[blockId])
            {
                // Don't try to enable this counter. When the results are collected, this will be given
                // a result of 0, so that it has no contribution.
                dontEnableCounter = true;
            }
        }

        if (dontEnableCounter)
        {
            m_pPass->DisableCounterForPass(static_cast<CounterIndex>(counterIter));
            continue;
        }

        // add valid counters to the experiment
        PE_RESULT result = PE_ERROR_NOT_SUPPORTED;

        if (nullptr != m_pExperiment)
        {
            result = m_pExperiment->AddCounter(static_cast<PE_BLOCK_ID>(pCounter->m_groupIdDriver),
                                               instance,
                                               static_cast<UINT>(pCounter->m_pHardwareCounter->m_counterIndexInGroup),
                                               &m_ppCounters[counterIter]);

            if (PE_OK == result)
            {
                m_pPass->EnableCounterForPass(static_cast<CounterIndex>(counterIter));
            }
            else
            {
                // If unable to add counter, don't attempt to add next one. break and mark all counters are disabled.
                m_pPass->DisableAllCountersForPass();
                success = false;
                break;
            }
        }
    }

    if (!success)
    {
        // If not successful, delete allocations
        delete[] m_ppCounters;
        m_ppCounters = nullptr;
    }

    return success;
}

bool DX11GPASample::SetExperimentParams(const std::vector<gpa_uint32>* pCounters) const
{
    bool success = true;

    if (nullptr != m_pExperiment &&
        nullptr != m_pDx11GpaContext)
    {
        // We need to figure out how many SX (pixel shader cross bars) there are
        const GPA_HardwareCounters* pHardwareCounters = m_pDx11GpaContext->GetCounterAccessor()->GetHardwareCounters();

        // add all desired counters
        for (size_t i = 0; i < pCounters->size(); i++)
        {
            const GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[i]];

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

                // set all valid shader engines to the current stage mask
                for (unsigned int ii = 0; ii < m_pDx11GpaContext->GetHwInfo()->GetNumberShaderEngines(); ii++)
                {
                    PE_RESULT result = m_pExperiment->SetEngineParam(ii, PE_PARAM_SQ_SHADER_MASK, maskValue);

                    if (PE_OK != result)
                    {
                        GPA_LogError("Unable to set the shader engine paramater.");
                        success = false;
                        break;
                    }
                }

                if (!success)
                {
                    break;
                }

                // reset the instance because there is only 1 SQ
                //instance = 0;
            }
            else if (pCounter->m_groupIdDriver == PE_BLOCK_RLC)
            {
                // RLC counters cause a reboot, so don't allow them to be enabled.
                success = false;
                break;
            }
        }
    }
    else
    {
        GPA_LogDebugError("Experiment is NULL, cannot profile.");
        success = false;
    }

    return success;
}


bool DX11GPASample::PopulateResult()
{
    bool populated = false;

    if (nullptr != m_pSampleResult)
    {
        if (m_pPass->IsTimingPass() && nullptr != m_pGPUTimeCounter)
        {
            DX11GPAContext* pDx11GpaContext = reinterpret_cast<DX11GPAContext*>(m_pPass->GetGpaSession()->GetParentContext());
            ID3D11DeviceContext* pD3D11DevicContext = nullptr;
            pDx11GpaContext->GetDevice()->GetImmediateContext(&pD3D11DevicContext);

            assert(m_pGPUTimeCounter->GetDataSize() == 2 * sizeof(gpa_uint64));
            assert(1 == m_pSampleResult->m_numCounters);

            // TimeStamps return 2 gpa_uint64
            gpa_uint64 timingData[2];
            HRESULT hr = pD3D11DevicContext->GetData(m_pGPUTimeCounter, timingData, m_pGPUTimeCounter->GetDataSize(), 0);

            assert(hr == S_OK);

            if (S_OK == hr)
            {
                *m_pSampleResult->m_pResultBuffer = timingData[1] - timingData[0];
                populated = true;
            }
        }
        else
        {
            size_t counterCount = m_pSampleResult->m_numCounters;

            for (size_t counterIter = 0; counterIter < counterCount; counterIter++)
            {
                m_pSampleResult->m_pResultBuffer[counterIter] = m_ppCounters[counterIter]->GetData();
            }

            populated = true;
        }

        if (populated)
        {
            MarkAsCompleted();
        }
    }

    return populated;
}

unsigned int DX11GPASample::GetActiveGpu() const
{
    unsigned int activeGpu = 0;

    if (nullptr != m_pDx11GpaContext)
    {
        IAmdDxExt* pDxExt = m_pDx11GpaContext->GetAmdDxExtension();
        IAmdDxExtPerfProfile* pExtPE = m_pDx11GpaContext->GetAmdProfileExtension();

        if (nullptr != pDxExt &&
            nullptr != pExtPE &&
            DxxExtUtils::IsMgpuPerfExtSupported(pDxExt))
        {
            unsigned int activeGpuCount = 0;
            unsigned int gpu = 0;
            PE_RESULT peResult = PE_OK;
            BOOL gpuProfileable = FALSE;

            constexpr unsigned int maxGpuCount = 8; // This value is taken from DXX ASIC info extension header

            // First pass get the number of active GPUs
            while ((PE_OK == peResult) && (maxGpuCount > gpu))
            {
                peResult = pExtPE->IsGpuProfileable(gpu, &gpuProfileable);

                if (TRUE == gpuProfileable)
                {
                    ++activeGpuCount;
                }

                ++gpu;
            }

            if (1 < activeGpuCount)
            {
                activeGpu = ms_activeGpuCF;
            }
            else // Not ACF/CF - run a second pass to find the active GPU
            {
                gpu = 0;
                peResult = PE_OK;
                gpuProfileable = FALSE;

                while ((PE_OK == peResult) && (FALSE == gpuProfileable) && (maxGpuCount > gpu))
                {
                    peResult = pExtPE->IsGpuProfileable(gpu, &gpuProfileable);

                    if (TRUE == gpuProfileable)
                    {
                        activeGpu = gpu;
                    }

                    ++gpu;
                }
            }
        }
    }

    return activeGpu;
}

void DX11GPASample::PopulateBlockInstanceLimits(UINT activeGpu) const
{
    if (ms_blockInstanceLimits.find(activeGpu) == ms_blockInstanceLimits.end())
    {
        PE_BLOCK_COUNTER_INFO blockInfo;
        BlockInstanceLimitMap blockLimits;

        for (int blockId = PE_BLOCK_UNKNOWN + 1; blockId < PE_BLOCK_MAX_CI; blockId++)
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
