//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX11 Context Implementation
//==============================================================================

#include "dx11_gpa_context.h"
#include "gpa_unique_object.h"
#include "dx11_gpa_implementor.h"
#include "dx11_gpa_session.h"
#include "dxx_ext_utils.h"

DX11GPAContext::DX11GPAContext(ID3D11Device* pD3D11Device, GPA_HWInfo& hwInfo, GPA_OpenContextFlags contextFlags)
    : GPAContext(hwInfo, contextFlags),
    m_pD3D11Device(pD3D11Device),
    m_pDxExt(nullptr),
    m_pDxExtPE(nullptr),
    m_blockCounterInfo{},
    m_blockInfoInit{},
    m_gpuCaps(),
    m_clockMode()
{
#ifdef _DEBUG
    D3D_SET_OBJECT_NAME_A(m_pD3D11Device, "GPA_DX11DeviceRef");
#endif
    ULONG refCount = m_pD3D11Device->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    m_gpuCaps.version = 0u;
}

DX11GPAContext::~DX11GPAContext()
{
    GPA_Status setStableClocksStatus = SetStableClocks(false);

    if (GPA_STATUS_OK != setStableClocksStatus)
    {
        GPA_LogError("Driver was unable to set stable clocks back to default.");
    }

    if (nullptr != m_pDxExtPE)
    {
        m_pDxExtPE->Release();
    }

    if (nullptr != m_pDxExt)
    {
        m_pDxExt->Release();
    }

    if (nullptr != m_pD3D11Device)
    {
        ULONG refCount = m_pD3D11Device->Release();
        UNREFERENCED_PARAMETER(refCount);
        m_pD3D11Device = nullptr;
    }
}

GPA_SessionId DX11GPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId pRetSessionId = nullptr;

    DX11GPASession* pNewDX11GpaSession = new (std::nothrow) DX11GPASession(this, sampleType);

    if (nullptr == pNewDX11GpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewDX11GpaSession);

        if (nullptr != pNewDX11GpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewDX11GpaSession));
        }
    }

    return pRetSessionId;
}

bool DX11GPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool success = false;

    if (GPAUniqueObjectManager::Instance()->DoesExist(sessionId))
    {
        DX11GPASession* pDx11GpaSession = reinterpret_cast<DX11GPASession*>(sessionId->Object());

        unsigned int index;

        if (GetIndex(pDx11GpaSession, &index))
        {
            RemoveGpaSession(pDx11GpaSession);
            GPAUniqueObjectManager::Instance()->DeleteObject(sessionId);
            delete pDx11GpaSession;
            success = true;
        }
    }

    return success;
}

gpa_uint32 DX11GPAContext::GetMaxGPASessions() const
{
    // reported maximum latency was 4 for r6xx cards
    // had issues with this value. Had to switch to 32
    return 32;
}

GPA_API_Type DX11GPAContext::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

bool DX11GPAContext::Initialize()
{
    bool success = OpenCounters() && InitializeProfileAMDExtension();

    GPA_Status setStableClocksStatus = SetStableClocks(true);

    if (GPA_STATUS_OK != setStableClocksStatus)
    {
        GPA_LogError("Driver was unable to set stable clocks for profiling.");
    }

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}

IAmdDxExt* DX11GPAContext::GetAmdDxExtension() const
{
    return m_pDxExt;
}

IAmdDxExtPerfProfile* DX11GPAContext::GetAmdProfileExtension() const
{
    return m_pDxExtPE;
}

ID3D11Device* DX11GPAContext::GetDevice() const
{
    return m_pD3D11Device;
}

GPUIndex DX11GPAContext::GetActiveGpu() const
{
    GPUIndex activeGpu = 0;

    if (nullptr != m_pDxExt && nullptr != m_pDxExtPE && DxxExtUtils::IsMgpuPerfExtSupported(m_pDxExt))
    {
        unsigned int activeGpuCount = 0;
        unsigned int gpu            = 0;
        PE_RESULT    peResult       = PE_OK;
        BOOL         gpuProfileable = FALSE;

        constexpr unsigned int maxGpuCount = 8;  // This value is taken from DXX ASIC info extension header

        // First pass get the number of active GPUs
        while ((PE_OK == peResult) && (maxGpuCount > gpu))
        {
            peResult = m_pDxExtPE->IsGpuProfileable(gpu, &gpuProfileable);

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
        else  // Not ACF/CF - run a second pass to find the active GPU
        {
            gpu            = 0;
            peResult       = PE_OK;
            gpuProfileable = FALSE;

            while ((PE_OK == peResult) && (FALSE == gpuProfileable) && (maxGpuCount > gpu))
            {
                peResult = m_pDxExtPE->IsGpuProfileable(gpu, &gpuProfileable);

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

GPUIndex DX11GPAContext::GetCFActiveGpu() const
{
    return ms_activeGpuCF;
}

gpa_uint32 DX11GPAContext::GetInstanceCount(PE_BLOCK_ID block) const
{
    gpa_uint32 retVal = 0u;

    if (m_blockInfoInit[block])
    {
        retVal = m_blockCounterInfo[block].instanceCount;
    }

    return retVal;
}

gpa_uint32 DX11GPAContext::GetMaxEventIdCount(PE_BLOCK_ID block) const
{
    gpa_uint32 retVal = 0u;

    if (m_blockInfoInit[block])
    {
        retVal = m_blockCounterInfo[block].maxEventId;
    }

    return retVal;
}

bool DX11GPAContext::InitializeProfileAMDExtension()
{
    bool success = true;

    PFNAmdDxExtCreate11 dx11ExtensionFunc = DX11GPAImplementor::Instance()->GetAmdExtFuncPointer();

    if (nullptr == dx11ExtensionFunc)
    {
        GPA_LogError("AMD extension function is not initialized.");
        success = false;
    }
    else
    {
        // Note: PFNAmdDxExtCreate11 adds a ref on the out parameter
        HRESULT hr = dx11ExtensionFunc(m_pD3D11Device, &m_pDxExt);

        if (FAILED(hr))
        {
            GPA_LogError("Unable to create DX11 extension.");
            success = false;
        }
        else
        {
            m_pDxExtPE = reinterpret_cast<IAmdDxExtPerfProfile*>(m_pDxExt->GetExtInterface(AmdDxExtPerfProfileID));

            if (nullptr == m_pDxExtPE)
            {
                m_pDxExt->Release();
                m_pDxExt = nullptr;
                GPA_LogError("Unable to initialize because the driver does not support the PerfProfile extension.");
                success = false;
            }
            else
            {
                GPUIndex activeGpu = GetActiveGpu();

                if (PE_OK != m_pDxExtPE->GetGpuCaps(activeGpu, &m_gpuCaps))
                {
                    GPA_LogError("Unable to get device capabilities from the driver.");
                    success = false;
                }

                for (auto gpuBlockIter = 0u; gpuBlockIter < PE_BLOCK_ID_MAX; gpuBlockIter++)
                {
                    // Note: if using an older driver (one that doesn't support the new Perf Experiment interface -- see IsMgpuPerfExpSupported)
                    //       gpuID will be 0. However, looking at driver sources, the implementation of GetBlockCounterInfo in those older
                    //       drivers ignores this parameter anyway

                    if (PE_OK == m_pDxExtPE->GetBlockCounterInfo(activeGpu, static_cast<PE_BLOCK_ID>(gpuBlockIter), &m_blockCounterInfo[gpuBlockIter]))
                    {
                        m_blockInfoInit[gpuBlockIter] = true;
                        success &= true;
                    }
                    else
                    {
                        m_blockInfoInit[gpuBlockIter] = false;
                    }
                }
            }
        }
    }

    return success;
}

GPA_Status DX11GPAContext::SetStableClocks(bool useProfilingClocks)
{
    GPA_Status result = GPA_STATUS_OK;

    // Only use Stable PState feature if driver supports at least extension version 3
    if (3 > m_gpuCaps.version)
    {
        GPA_LogMessage("DX11 stable clock extension is not available.");

        // TODO: return an error once we no longer need to support pre-19.30 drivers
        // result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
    }
    else
    {
        PE_CLOCK_MODE clockMode = PE_CLOCK_MODE_DEFAULT;

        if (useProfilingClocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
            case DeviceClockMode::Default:
                clockMode = PE_CLOCK_MODE_DEFAULT;
                break;

            case DeviceClockMode::Profiling:
                clockMode = PE_CLOCK_MODE_PROFILING;
                break;

            case DeviceClockMode::MinimumMemory:
                clockMode = PE_CLOCK_MODE_MIN_MEMORY;
                break;

            case DeviceClockMode::MinimumEngine:
                clockMode = PE_CLOCK_MODE_MIN_ENGINE;
                break;

            case DeviceClockMode::Peak:
                clockMode = PE_CLOCK_MODE_PEAK;
                break;

            default:
                assert(0);
                clockMode = PE_CLOCK_MODE_PROFILING;
                break;
            }
        }

        if (clockMode != m_clockMode)
        {
            m_clockMode = clockMode;

            PE_RESULT status = m_pDxExtPE->SetClockMode(clockMode, nullptr);
            result = (PE_OK == status) ? GPA_STATUS_OK : GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            if (PE_OK != status)
            {
                GPA_LogError("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}
