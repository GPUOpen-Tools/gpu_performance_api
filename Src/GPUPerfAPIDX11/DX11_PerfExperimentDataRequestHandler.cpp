//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Implementation for sampling performance counters using the DX
/// Performance Experiment extension.
//==============================================================================

#include "D3D11.h"
#include "DX11_PerfExperimentDataRequestHandler.h"
#include "AmdDxExtPerfProfileApi.h"
#include "..\GPUPerfAPI-Common\Logging.h"
#include "..\GPUPerfAPI-Common\GPUPerfAPITypes.h"
#include "DeviceInfoUtils.h"
#include "DxxExtUtils.h"

#include "ADLUtil.h"
// This is from ADL's include directory.
#include "customer/oem_structures.h"

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

DX11_PerfExperimentDataRequestHandler::GpuBlockInstanceLimitMap DX11_PerfExperimentDataRequestHandler::ms_blockInstanceLimits;

//-----------------------------------------------------------------------------
DX11_PerfExperimentDataRequestHandler::DX11_PerfExperimentDataRequestHandler(GPA_DataRequest* pParentCounter)
{
    m_pExt = nullptr;
    m_pExtPE = nullptr;
    m_pExperiment = nullptr;
    m_counters = nullptr;

    m_GPUTimeCounter = nullptr;

    m_parentCounter = pParentCounter;
}

//-----------------------------------------------------------------------------
DX11_PerfExperimentDataRequestHandler::~DX11_PerfExperimentDataRequestHandler()
{
    TRACE_PRIVATE_FUNCTION(DX11_PerfExperimentDataRequestHandler::DESTRUCTOR);

    DestroyExperiment();

    // m_pExtPE must be released before m_pExt
    if (nullptr != m_pExtPE)
    {
        m_pExtPE->Release();
        m_pExtPE = nullptr;
    }

    if (nullptr != m_pExt)
    {
        // Due to an issue in CFX/DXX support for the perf extension, releasing the extension causes
        // an app crash when running in a PX setup. This issue is tracked via EPR #410086
        // Removing this Release call prevents the crash, but leads to a large memory leak deemed
        // unacceptable when profiling a frame with a large number of draw calls.
        m_pExt->Release();
        m_pExt = nullptr;
    }

    if (nullptr != m_GPUTimeCounter)
    {
        m_GPUTimeCounter->Release();
        m_GPUTimeCounter = nullptr;
    }
}

//-----------------------------------------------------------------------------
bool DX11_PerfExperimentDataRequestHandler::Initialize(void* context)
{
    HMODULE hDll = nullptr;

#ifdef X64
    hDll = GetModuleHandle("atidxx64.dll");
#else
    hDll = GetModuleHandle("atidxx32.dll");
#endif

    if (nullptr == hDll)
    {
#ifdef X64
        GPA_LogError("Unable to initialize because 'atidxx64.dll' is not available.");
#else
        GPA_LogError("Unable to initialize because 'atidxx32.dll' is not available.");
#endif
        return false;
    }

    PFNAmdDxExtCreate11 AmdDxExtCreate11;
    AmdDxExtCreate11 = (PFNAmdDxExtCreate11)GetProcAddress(hDll,  "AmdDxExtCreate11");

    if (nullptr == AmdDxExtCreate11)
    {
        GPA_LogError("Unable to initialize because extension creation is not available.");
        return false;
    }

    HRESULT hr = AmdDxExtCreate11((ID3D11Device*)context, &m_pExt);

    if (FAILED(hr) || nullptr == m_pExt)
    {
        GPA_LogError("Unable to initialize because extension creation is not available.");
        return false;
    }

    m_pExtPE = (IAmdDxExtPerfProfile*)m_pExt->GetExtInterface(AmdDxExtPerfProfileID);

    if (nullptr == m_pExtPE)
    {
        m_pExt->Release();
        m_pExt = nullptr;
        GPA_LogError("Unable to initialize because the driver does not support the PerfProfile extension.");
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
void DX11_PerfExperimentDataRequestHandler::CreateExperiment()
{
    if ((nullptr == m_pExperiment) && (nullptr != m_pExtPE))
    {
        m_gpuToCheckBlockLimits = GetActiveGpu();

        // create correct version of experiment based on driver version
        if (IsMgpuPerfExtSupported(m_pExt))
        {
            if (ActiveGpuCF == m_gpuToCheckBlockLimits)
            {
                // When checking block limits, if in Crossfire mode, always use GPU zero; if in PX mode, use the active GPU
                m_gpuToCheckBlockLimits = 0;

                // In CF/ACF scenario let the driver create the experiment on the
                // current frame active GPU
                m_pExperiment = m_pExtPE->CreateExperiment();
            }
            else
            {
                m_pExperiment = m_pExtPE->CreateExperimentEx(m_gpuToCheckBlockLimits);
            }
        }

        m_pExperiment = m_pExtPE->CreateExperiment();

        PopulateBlockInstanceLimits(m_gpuToCheckBlockLimits);

        // TODO: Set experiment parameters here
    }
    else
    {
        GPA_LogError("Perf Experiment was not created.");
    }
}

//-----------------------------------------------------------------------------
void DX11_PerfExperimentDataRequestHandler::DestroyExperiment()
{
    if (nullptr != m_counters)
    {
        delete[] m_counters;
        m_counters = nullptr;
    }

    if (nullptr != m_pExperiment)
    {
        m_pExperiment->ReleaseResources();
        m_pExperiment->Destroy();
        m_pExperiment = nullptr;
    }
}

//-----------------------------------------------------------------------------
void DX11_PerfExperimentDataRequestHandler::Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(DXPerformanceExperimentProfile::Reset);

    // reset object
    const gpa_uint32 newActiveCounters = static_cast<gpa_uint32>(pCounters->size());

    // Destroy the experiment since the previous one was finalized and cannot have new counters enabled.
    // The previous experiment may be able to be reused if the counter selectionID is the same, but don't try that for now.
    DestroyExperiment();

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    // refresh timestamp details
    m_parentCounter->ResetGPUTimeState(pCounters, pHardwareCounters->m_gpuTimeTopToBottomCounterIndex, pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex,
                                       pHardwareCounters->m_gpuTimestampTopCounterIndex, pHardwareCounters->m_gpuTimestampPreBottomCounterIndex, pHardwareCounters->m_gpuTimestampPostBottomCounterIndex);

    // recreate the experiment
    CreateExperiment();

    // new array of counters
    m_counters = new(std::nothrow) IAmdDxExtPerfCounter*[newActiveCounters];

    if (nullptr == m_counters)
    {
        GPA_LogError("Unable to allocate memory for counters.");
    }
    else
    {
        // clear the array of counters
        for (gpa_uint32 i = 0; i < newActiveCounters; i++)
        {
            m_counters[i] = nullptr;
        }

        m_parentCounter->SetCounterSelectionID(selectionID);
        m_parentCounter->SetNumActiveCounters(newActiveCounters);
    }
}

//-----------------------------------------------------------------------------
bool DX11_PerfExperimentDataRequestHandler::BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(DXPerformanceExperimentProfile::Begin);

    // reset object since may be reused
    Reset(selectionID, pCounters);

    ID3D11Device* pDevice = static_cast<ID3D11Device* >(pContextState->m_pContext);
    ID3D11DeviceContext* pDeviceContext = nullptr;
    pDevice->GetImmediateContext(&pDeviceContext);

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    bool bottomToBottomPresent = m_parentCounter->GPUTimeBottomToBottomPresent();
    bool topToBottomPresent    = m_parentCounter->GPUTimeTopToBottomPresent();
    bool timestampTopPresent   = m_parentCounter->GPUTimestampTopPresent();

    if (bottomToBottomPresent || topToBottomPresent || timestampTopPresent)
    {
        if (nullptr == m_GPUTimeCounter)
        {
            // counter not created, create here
            D3D11_COUNTER_DESC ctrDesc;

            ctrDesc.Counter = (D3D11_COUNTER)pHardwareCounters->m_counters[(*pCounters)[m_parentCounter->GPUTimeBottomToBottomOffset()]].m_counterIdDriver;

            if (timestampTopPresent)
            {
                ctrDesc.Counter = (D3D11_COUNTER)pHardwareCounters->m_counters[(*pCounters)[m_parentCounter->GPUTimestampTopOffset()]].m_counterIdDriver;
            }

            assert(ctrDesc.Counter != 0);
            ctrDesc.MiscFlags = 0;

            D3D11_COUNTER_TYPE type   = D3D11_COUNTER_TYPE_FLOAT32;
            gpa_uint32 activeCounters = 0;
            gpa_uint32 numAvailableCounterSize = sizeof(gpa_uint32);
            HRESULT hr = pDevice->CheckCounter(&ctrDesc, &type, &activeCounters, nullptr, nullptr, nullptr, &numAvailableCounterSize, nullptr, nullptr);

            if (hr != S_OK)
            {
                // make sure any counters which worked are released
                Reset(selectionID, pCounters);
                GPA_LogDebugError("Call to ID3D11Device::CheckCounter failed on the GPUTime counter.");
                pDeviceContext->Release();
                return false;
            }

            hr = pDevice->CreateCounter(&ctrDesc, &m_GPUTimeCounter);

            if (hr != S_OK)
            {
                // make sure any counters which worked are released
                Reset(selectionID, pCounters);
                GPA_LogDebugError("Call to ID3D11Device::CreateCounter failed on the GPUTime counter.");
                GPA_LogError("Call to ID3D11Device::CreateCounter failed.");
                pDeviceContext->Release();
                return false;
            }
        }

        pDeviceContext->Begin(m_GPUTimeCounter);
    }
    else
    {
        if (nullptr == m_pExperiment)
        {
            GPA_LogDebugError("Experiment is NULL, cannot profile.");
            return false;
        }

        // We need to figure out how many SX (pixel shader cross bars) there are
        GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;
        getCurrentContext()->m_hwInfo.GetHWGeneration(generation);

        // add all desired counters
        for (size_t i = 0; i < pCounters->size(); i++)
        {
            // don't expect the counter to already exist
            assert(nullptr == m_counters[i]);

            // need to Add a counter
            GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[i]];
            unsigned int instance = (unsigned int)pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance;

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
                for (unsigned int ii = 0; ii < getCurrentContext()->m_hwInfo.GetNumberShaderEngines(); ii++)
                {
                    if (nullptr != m_pExperiment)
                    {
                        m_pExperiment->SetEngineParam(ii, PE_PARAM_SQ_SHADER_MASK, maskValue);
                    }
                }

                // reset the instance because there is only 1 SQ
                //instance = 0;
            }
            else if (pCounter->m_groupIdDriver == PE_BLOCK_RLC)
            {
                // RLC counters cause a reboot, so don't allow them to be enabled.
                Reset(selectionID, pCounters);
                GPA_LogError("An unstable counter is included in the counter selection. Please remove it and re-profile.");
                pDeviceContext->Release();
                return false;
            }

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
                continue;
            }

            // add valid counters to the experiment
            PE_RESULT result = PE_ERROR_NOT_SUPPORTED;

            if (nullptr != m_pExperiment)
            {
                result = m_pExperiment->AddCounter((PE_BLOCK_ID)(pCounter->m_groupIdDriver), instance, (UINT)pCounter->m_pHardwareCounter->m_counterIndexInGroup, &m_counters[i]);
            }

            if (result != PE_OK)
            {
                Reset(selectionID, pCounters);

                if (result == PE_ERROR_OUT_OF_MEMORY) { GPA_LogError("Counter could not be enabled due to an Out Of Memory error."); }

                ASSERT_ON_PE_ERROR(result);
                GPA_LogDebugError("Call to IPerfExperiment::AddCounter failed on block %d, instance %d, counter %d.", pCounter->m_groupIdDriver, instance, pCounter->m_pHardwareCounter->m_counterIndexInGroup);
                pDeviceContext->Release();
                return false;
            }

            if (pCounter->m_groupIdDriver == PE_BLOCK_SQ)
            {
                result = m_counters[i]->SetParam(PE_COUNTER_SQ_SIMD_MASK, 0xF);

                if (result != PE_OK)
                {
                    ASSERT_ON_PE_ERROR(result);
                    GPA_LogDebugError("call to IAmdDxExtPerfCounter::SetParam failed.");
                }
            }
        }

        m_parentCounter->SetNumActiveCounters(pCounters->size());

        // finalize the experiment
        PE_RESULT result = PE_ERROR_NOT_SUPPORTED;

        if (nullptr != m_pExperiment)
        {
            result = m_pExperiment->Finalize();
        }

        if (result != PE_OK)
        {
            if (result == PE_ERROR_OUT_OF_MEMORY) { GPA_LogError("Counter could not be enabled due to an Out Of Memory error."); }

            ASSERT_ON_PE_ERROR(result);
            GPA_LogDebugError("Call to IPerfExperiment::Finalize failed.");
            pDeviceContext->Release();
            return false;
        }

        // begin the experiment
        if (nullptr != m_pExperiment)
        {
            result = m_pExperiment->Begin();
        }

        if (result != PE_OK)
        {
            if (result == PE_ERROR_OUT_OF_MEMORY) { GPA_LogError("Unable to begin the profile pass due to an Out Of Memory error."); }

            ASSERT_ON_PE_ERROR(result);
            GPA_LogDebugError("Call to IPerfExperiment::Begin failed.");
            pDeviceContext->Release();
            return false;
        }
    }

    pDeviceContext->Release();
    return true;
}

//-----------------------------------------------------------------------------
bool DX11_PerfExperimentDataRequestHandler::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(DXPerformanceExperimentProfile::End);

    if (m_parentCounter->GPUTimeBottomToBottomPresent() || m_parentCounter->GPUTimeTopToBottomPresent() || m_parentCounter->GPUTimestampTopPresent())
    {
        ID3D11DeviceContext* pDeviceContext = getCurrentContext()->DX11DeviceContext();
        pDeviceContext->End(m_GPUTimeCounter);
    }
    else
    {
        if (nullptr != m_pExperiment)
        {
            m_pExperiment->End();
        }
    }

    return true;
}

//-----------------------------------------------------------------------------
bool DX11_PerfExperimentDataRequestHandler::CollectResults(GPA_CounterResults& resultStorage, size_t numActiveCounters, gpa_uint32 sampleId)
{
    UNREFERENCED_PARAMETER(sampleId);
    UNREFERENCED_PARAMETER(numActiveCounters);

    ID3D11DeviceContext* pDevContext = getCurrentContext()->DX11DeviceContext();

    if (m_parentCounter->GPUTimeBottomToBottomPresent() || m_parentCounter->GPUTimeTopToBottomPresent() || m_parentCounter->GPUTimestampTopPresent())
    {
        // check if GPUTime is ready
        HRESULT hr = pDevContext->GetData(m_GPUTimeCounter, nullptr, 0, 0);

        if (hr != S_OK)
        {
            return false;
        }
    }
    else
    {
        BOOL retVal = true;

        if (nullptr != m_pExperiment)
        {
            retVal = m_pExperiment->WaitCompletion(10);
        }

        if (!retVal)
        {
            return false;
        }
    }

    // query and store the results
    for (gpa_uint32 i = 0; i < m_parentCounter->NumActiveCounters(); ++i)
    {
        if (m_parentCounter->IsTimeStamp(i))
        {
            assert(m_GPUTimeCounter != nullptr);
            assert(m_GPUTimeCounter->GetDataSize() == sizeof(gpa_uint64));

            // TimeStamps return 2 gpa_uint64
            gpa_uint64 tsData[2];
            HRESULT hr = pDevContext->GetData(m_GPUTimeCounter, tsData, m_GPUTimeCounter->GetDataSize(), 0);
            assert(hr == S_OK);

            if (hr != S_OK)
            {
                GPA_LogDebugError("GetData returned '%X' when requesting GPUTime results.", hr);
            }

            // copy top data if requested
            if (m_parentCounter->GPUTimeTopToBottomPresent())
            {
                resultStorage.m_pResultBuffer[m_parentCounter->GPUTimeTopToBottomOffset()] = tsData[0];
            }

            // copy bottom data if requested
            if (m_parentCounter->GPUTimeBottomToBottomPresent())
            {
                resultStorage.m_pResultBuffer[m_parentCounter->GPUTimeBottomToBottomOffset()] = tsData[1];
            }

            // copy GPUTimestamp data
            if (m_parentCounter->GPUTimestampTopPresent())
            {
                resultStorage.m_pResultBuffer[m_parentCounter->GPUTimestampTopOffset()] = tsData[0];
            }
        }
        else
        {
            if (nullptr == m_counters[i])
            {
                resultStorage.m_pResultBuffer[i] = 0;
            }
            else
            {
                resultStorage.m_pResultBuffer[i] = m_counters[i]->GetData();
            }
        }
    }

    return true;
}

bool DX11_PerfExperimentDataRequestHandler::GetBlockCounterInfo(UINT gpuID, PE_BLOCK_ID block, PE_BLOCK_COUNTER_INFO* pBlockInfo)
{
    // Note: if using an older driver (one that doesn't support the new Perf Experiment interface -- see IsMgpuPerfExpSupported)
    //       gpuID will be 0. However, looking at driver sources, the imlpementation of GetBlockCounterInfo in those older
    //       drivers ignores this parameter anyway

    PE_RESULT result = m_pExtPE->GetBlockCounterInfo(gpuID, block, pBlockInfo);

    if (PE_OK != result)
    {
        GPA_LogError("Error querying Block Counter Info.");
        GPA_LogDebugError("  GPU: %d, Block %d.", gpuID, block);
    }

    return result == PE_OK;
}

//-----------------------------------------------------------------------------
void DX11_PerfExperimentDataRequestHandler::ReleaseCounters()
{
    DestroyExperiment();
}

unsigned int DX11_PerfExperimentDataRequestHandler::GetActiveGpu() const
{
    unsigned int activeGpu = 0;

    if (IsMgpuPerfExtSupported(m_pExt))
    {
        unsigned int activeGpuCount = 0;
        unsigned int gpu = 0;
        PE_RESULT peResult = PE_OK;
        BOOL gpuProfileable = FALSE;

        static const unsigned int maxGpuCount = 8; // This value is taken from DXX ASIC info extension header

        // First pass get the number of active GPUs
        while ((PE_OK == peResult) && (maxGpuCount > gpu))
        {
            peResult = m_pExtPE->IsGpuProfileable(gpu, &gpuProfileable);

            if (TRUE == gpuProfileable)
            {
                ++activeGpuCount;
            }

            ++gpu;
        }

        if (1 < activeGpuCount)
        {
            activeGpu = ActiveGpuCF;
        }
        else // Not ACF/CF - run a second pass to find the active GPU
        {
            gpu = 0;
            peResult = PE_OK;
            gpuProfileable = FALSE;

            while ((PE_OK == peResult) && (FALSE == gpuProfileable) && (maxGpuCount > gpu))
            {
                peResult = m_pExtPE->IsGpuProfileable(gpu, &gpuProfileable);

                if (TRUE == gpuProfileable)
                {
                    activeGpu = gpu;
                }

                ++gpu;
            }
        }
    }

    return activeGpu;
}

void DX11_PerfExperimentDataRequestHandler::PopulateBlockInstanceLimits(UINT activeGpu)
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
