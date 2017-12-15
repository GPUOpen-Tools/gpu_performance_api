//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX12 Context implementation
//==============================================================================

#include "DX12GPAContext.h"
#include "GPAUniqueObject.h"
#include "DX12Utils.h"
#include "DeviceInfoUtils.h"
#include "DX12GPASession.h"
#include "GPAHardwareCounters.h"
#include "GPACounterGeneratorBase.h"

DX12GPAContext::DX12GPAContext(ID3D12Device* pD3D12Device,
    GPA_HWInfo& hwInfo, 
    GPA_OpenContextFlags flags)
    : GPAContext(hwInfo, flags)
{
    m_pD3D12Device = pD3D12Device;
    m_pD3D12Device->AddRef();
    m_isAmdDevice = false;
    m_pAmdExtD3DFactoryObject = nullptr;
    m_pGpaInterface = nullptr;
    m_clockMode = AmdExtDeviceClockMode::Default;
}

DX12GPAContext::~DX12GPAContext()
{
    CleanUp();
}

bool DX12GPAContext::Initialize()
{
    bool isSucceeded = false;

    // TODO: Figure out why GPA is failing when it is uncommented
    //std::lock_guard<std::mutex> lockInitialization(m_gpaContextMutex);

    if (nullptr != m_pD3D12Device)
    {
        if (InitializeAMDExtension() && OpenCounters())
        {
            isSucceeded = true;
        }
    }

    SetAsOpened(isSucceeded);
    return isSucceeded;
}


GPA_SessionId DX12GPAContext::CreateSession()
{
    GPA_SessionId pRetSessionId = nullptr;

    if (nullptr != m_pGpaInterface)
    {
        std::lock_guard<std::mutex> lockSessionCreation(m_gpaContextMutex);
        DX12GPASession* pNewGpaDx12GpaSession = new(std::nothrow) DX12GPASession(this, m_pGpaInterface);
        m_gpaSessionList.push_back(pNewGpaDx12GpaSession);

        if (nullptr != pNewGpaDx12GpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaDx12GpaSession));
        }
    }

    return pRetSessionId;
}


bool DX12GPAContext::DeleteSession(GPA_SessionId pSessionId)
{
    bool success = false;

    if (GPAUniqueObjectManager::Instance()->DoesExist(pSessionId))
    {
        DX12GPASession* pDx12Session = reinterpret_cast<DX12GPASession*>(pSessionId->Object());

        unsigned int index;

        if (GetIndex(pDx12Session, &index))
        {
            std::lock_guard<std::mutex> lockSessionMap(m_gpaContextMutex);
            m_gpaSessionList.remove(pDx12Session);
            GPAUniqueObjectManager::Instance()->DeleteObject(pSessionId);
            delete pDx12Session;
            success = true;
        }
    }

    return success;
}

gpa_uint32 DX12GPAContext::GetMaxGPASessions() const
{
    return GPA_SESSION_NO_LIMIT;
}

bool DX12GPAContext::DoesSessionExist(GPA_SessionId pSessionId) const
{
    return GetIndex(reinterpret_cast<DX12GPASession*>(pSessionId->Object()));
}

GPA_API_Type DX12GPAContext::GetAPIType() const
{
    return GPA_API_DIRECTX_12;
}

ID3D12Device* DX12GPAContext::GetD3D12Device() const
{
    return m_pD3D12Device;
}

gpa_uint32 DX12GPAContext::GetInstanceCount(AmdExtGpuBlock block) const
{
    gpa_uint32 instanceCount = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        instanceCount = static_cast<gpa_uint32>(m_amdDeviceProps.blocks[static_cast<size_t>(block)].instanceCount);
    }

    return instanceCount;
}

gpa_uint32 DX12GPAContext::GetMaxEventIdCount(AmdExtGpuBlock block) const
{
    gpa_uint32 maxEventId = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        maxEventId = static_cast<gpa_uint32>(m_amdDeviceProps.blocks[static_cast<size_t>(block)].maxEventId);
    }

    return maxEventId;
}

bool DX12GPAContext::InitializeAMDExtension()
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr != m_pD3D12Device)
    {
        if (nullptr == m_pGpaInterface && m_isAmdDevice)
        {
            result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            HMODULE hDll = nullptr;
#ifdef X64
            hDll = GetModuleHandle("amdxc64.dll");
#else
            hDll = GetModuleHandle("amdxc32.dll");
#endif

            if (nullptr == hDll)
            {
                GPA_LogError("Unable to get driver module handle.");
            }
            else
            {
                PFNAmdExtD3DCreateInterface pAmdExtD3dCreateFunc =
                    reinterpret_cast<PFNAmdExtD3DCreateInterface>(GetProcAddress(hDll, "AmdExtD3DCreateInterface"));

                if (nullptr == pAmdExtD3dCreateFunc)
                {
                    GPA_LogError("Unable to get driver extension entry point.");
                }
                else
                {
                    HRESULT hr = pAmdExtD3dCreateFunc(m_pD3D12Device,
                                                      __uuidof(IAmdExtD3DFactory),
                                                      reinterpret_cast<void**>(&m_pAmdExtD3DFactoryObject));

                    if (FAILED(hr))
                    {
                        GPA_LogError("Unable to get driver extension interface.");
                    }
                    else
                    {
                        hr = m_pAmdExtD3DFactoryObject->CreateInterface(m_pD3D12Device,
                                                                        __uuidof(IAmdExtGpaInterface),
                                                                        reinterpret_cast<void**>(&m_pGpaInterface));

                        if (FAILED(hr))
                        {
                            GPA_LogError("Unable to get driver GPA extension interface.");
                        }
                        else
                        {
                            hr = m_pGpaInterface->GetPerfExperimentProperties(&m_amdDeviceProps);

                            if (FAILED(hr))
                            {
                                GPA_LogError("Unable to get current hardware perf experiment properties.");
                            }
                            else
                            {
                                if (0 == m_amdDeviceProps.features.counters)
                                {
                                    GPA_LogError("Active GPU hardware does not support performance counters.");
                                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                                }
                                else
                                {
                                    SetStableClocks(true);
                                    result = GPA_STATUS_OK;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result == GPA_STATUS_OK ? true : false;
}

void DX12GPAContext::CleanUp()
{
    SetStableClocks(false);

    std::lock_guard<std::mutex> lockContextResources(m_gpaContextMutex);
    // Release Device
    if (nullptr != m_pD3D12Device)
    {
        m_pD3D12Device->Release();
        m_pD3D12Device = nullptr;
    }

    if (nullptr != m_pGpaInterface)
    {
        for (auto it = m_gpaSessionList.cbegin(); it != m_gpaSessionList.cend(); ++it)
        {
            // Release GPASessions - It is less likely this code path will execute but in case
            delete(*it);   // Delete the GPA Session
        }

        m_gpaSessionList.clear();
        m_pGpaInterface->Release();
        m_pGpaInterface = nullptr;
    }

    // Release AMD D3D Factory
    if (nullptr != m_pAmdExtD3DFactoryObject)
    {
        m_pAmdExtD3DFactoryObject->Release();
        m_pAmdExtD3DFactoryObject = nullptr;
    }
}

void DX12GPAContext::SetStableClocks(bool useProfilingClocks)
{
    if (nullptr != m_pGpaInterface)
    {
        AmdExtDeviceClockMode amdClockMode = AmdExtDeviceClockMode::Default;

        if (useProfilingClocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
                case DeviceClockMode::Default:
                    amdClockMode = AmdExtDeviceClockMode::Default;
                    break;

                case DeviceClockMode::MinimumEngine:
                    amdClockMode = AmdExtDeviceClockMode::MinimumEngine;
                    break;

                case DeviceClockMode::MinimumMemory:
                    amdClockMode = AmdExtDeviceClockMode::MinimumMemory;
                    break;

                case DeviceClockMode::Peak:
                    amdClockMode = AmdExtDeviceClockMode::Peak;
                    break;

                case DeviceClockMode::Profiling:
                    amdClockMode = AmdExtDeviceClockMode::Profiling;
                    break;

                default:
                    amdClockMode = AmdExtDeviceClockMode::Profiling;
                    break;
            }
        }

        std::lock_guard<std::mutex> lockAmdClock(m_gpaContextMutex);

        if (amdClockMode != m_clockMode)
        {
            m_clockMode = amdClockMode;
            m_pGpaInterface->SetClockMode(m_clockMode, nullptr);
        }
    }
}

bool DX12GPAContext::GetIndex(DX12GPASession* pDx12GpaSession, unsigned int* pIndex) const
{
    std::lock_guard<std::mutex> lock(m_gpaContextMutex);
    bool found = false;
    unsigned int index = 0;

    for (auto iter = m_gpaSessionList.cbegin(); iter != m_gpaSessionList.cend(); ++iter)
    {
        if (pDx12GpaSession == *iter)
        {
            found = true;

            if (nullptr != pIndex)
            {
                *pIndex = index;
                break;
            }
        }

        index++;

    }

    return found;
}
