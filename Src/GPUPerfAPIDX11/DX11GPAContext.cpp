//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX11 Context Implementation
//==============================================================================

#include "DX11GPAContext.h"
#include "GPAUniqueObject.h"
#include "DX11GPAImplementor.h"
#include "DX11GPASession.h"
#include "DxxExtUtils.h"

DX11GPAContext::DX11GPAContext(ID3D11Device* pD3D11Device,
                               GPA_HWInfo& hwInfo,
                               GPA_OpenContextFlags contextFlags):
    GPAContext(hwInfo, contextFlags)
{
    m_pD3D11Device = pD3D11Device;
#ifdef _DEBUG
    D3D_SET_OBJECT_NAME_A(m_pD3D11Device, "GPA_DX11DeviceRef");
#endif
    ULONG refCount = m_pD3D11Device->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    m_pDxExt = nullptr;
    m_pDxExtPE = nullptr;
}

DX11GPAContext::~DX11GPAContext()
{
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

    DX11GPASession* pNewDX11GpaSession = new(std::nothrow) DX11GPASession(this, sampleType);

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

bool DX11GPAContext::DeleteSession(GPA_SessionId pSessionId)
{
    bool success = false;

    if (GPAUniqueObjectManager::Instance()->DoesExist(pSessionId))
    {
        DX11GPASession* pDx11GpaSession = reinterpret_cast<DX11GPASession*>(pSessionId->Object());

        unsigned int index;

        if (GetIndex(pDx11GpaSession, &index))
        {
            RemoveGpaSession(pDx11GpaSession);
            GPAUniqueObjectManager::Instance()->DeleteObject(pSessionId);
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

    if (nullptr != m_pDxExt &&
        nullptr != m_pDxExtPE &&
        DxxExtUtils::IsMgpuPerfExtSupported(m_pDxExt))
    {
        unsigned int activeGpuCount = 0;
        unsigned int gpu = 0;
        PE_RESULT peResult = PE_OK;
        BOOL gpuProfileable = FALSE;

        constexpr unsigned int maxGpuCount = 8; // This value is taken from DXX ASIC info extension header

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
        else // Not ACF/CF - run a second pass to find the active GPU
        {
            gpu = 0;
            peResult = PE_OK;
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

bool DX11GPAContext::InitializeProfileAMDExtension()
{
    bool success = false;

    PFNAmdDxExtCreate11 dx11ExtensionFunc = DX11GPAImplementor::Instance()->GetAmdExtFuncPointer();

    if (nullptr != dx11ExtensionFunc)
    {
        // Note: PFNAmdDxExtCreate11 adds a ref on the out parameter
        HRESULT hr = dx11ExtensionFunc(m_pD3D11Device, &m_pDxExt);

        if (SUCCEEDED(hr))
        {
            m_pDxExtPE = reinterpret_cast<IAmdDxExtPerfProfile*>(m_pDxExt->GetExtInterface(AmdDxExtPerfProfileID));

            if (nullptr != m_pDxExtPE)
            {
                success = true;
            }
            else
            {
                m_pDxExt->Release();
                m_pDxExt = nullptr;
                GPA_LogError("Unable to initialize because the driver does not support the PerfProfile extension.");
            }
        }
        else
        {
            GPA_LogError("Unable to create DX11 extension.");
        }
    }
    else
    {
        GPA_LogError("AMD extension function is not initialized.");
    }

    return success;
}
