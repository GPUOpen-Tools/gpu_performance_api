//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 utility function implementations
//==============================================================================

#include "DX12Utils.h"
#include "d3d12.h"
#include "Logging.h"

GPA_Status DX12Utils::DX12GetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pDevice)
    {
        GPA_LogError("Parameter 'pDevice' is NULL.");
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        ID3D12Device* dx12Device = static_cast<ID3D12Device*>(pDevice);
        LUID adapterLuid = dx12Device->GetAdapterLuid();

        IDXGIFactory* pDXGIFactory = nullptr;
        HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDXGIFactory));

        if (FAILED(hr) || (nullptr == pDXGIFactory))
        {
            GPA_LogError("Unable to get IDXGIFactory interface from ID3D12Device.");
            status = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            IDXGIAdapter* pAdapter = nullptr;

            for (UINT index = 0; pDXGIFactory->EnumAdapters(index, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++index)
            {
                memset(&adapterDesc, 0, sizeof(adapterDesc));
                hr = pAdapter->GetDesc(&adapterDesc);

                if (FAILED(hr))
                {
                    GPA_LogError("Could not get adapter description, hardware cannot be supported.");
                    status = GPA_STATUS_ERROR_FAILED;
                }
                else
                {
                    if (adapterDesc.AdapterLuid.HighPart == adapterLuid.HighPart && adapterDesc.AdapterLuid.LowPart == adapterLuid.LowPart)
                    {
                        // We found the matching adapter luid, so we're done.
                        break;
                    }
                }
            }
        }

        pDXGIFactory->Release();
    }

    return status;
}

bool DX12Utils::IsD3D12CommandList(void* pCmd, D3D12_COMMAND_LIST_TYPE* cmdType)
{
    IUnknown* pUnknown = static_cast<IUnknown*>(pCmd);
    ID3D12GraphicsCommandList* pD3DCommandList;
    HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pD3DCommandList));
    bool result = SUCCEEDED(hr);

    if (result && nullptr != cmdType)
    {
        *cmdType = pD3DCommandList->GetType();
        pD3DCommandList->Release();     // We need to release this as QueryInterface will call AddRef
    }

    return result;
}

bool DX12Utils::IsSameCmdType(const D3D12_COMMAND_LIST_TYPE* pDX12CmdType,
                              const GPA_Command_List_Type* pGpaCmdType)
{
    if (nullptr != pDX12CmdType && nullptr != pGpaCmdType)
    {
        if (D3D12_COMMAND_LIST_TYPE_BUNDLE == *pDX12CmdType &&
            GPA_COMMAND_LIST_SECONDARY == *pGpaCmdType)
        {
            return true;
        }

        if (D3D12_COMMAND_LIST_TYPE_BUNDLE != *pDX12CmdType &&
            GPA_COMMAND_LIST_PRIMARY == *pGpaCmdType)
        {
            return true;
        }
    }

    return false;
}

bool DX12Utils::GetD3D12Device(IUnknown* pInterfacePointer, ID3D12Device** ppD3D12Device)
{
    bool success = false;
    *ppD3D12Device = nullptr;

    // Check to see if it's an ID3D12Device
    HRESULT hr = pInterfacePointer->QueryInterface(__uuidof(ID3D12Device), reinterpret_cast<void**>(ppD3D12Device));

    if (hr == E_NOINTERFACE)
    {
        // It's not an ID3D12device, so see if it is an ID3D12DeviceChild-derived interface (like a ID3D12CommandList)
        ID3D12DeviceChild* pDeviceChild = nullptr;

        hr = pInterfacePointer->QueryInterface(__uuidof(ID3D12DeviceChild), reinterpret_cast<void**>(&pDeviceChild));

        if (SUCCEEDED(hr))
        {
            // Note: GetDevice increments a ref on out parameter
            hr = pDeviceChild->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(ppD3D12Device));
            pDeviceChild->Release();
        }
    }

    success = SUCCEEDED(hr);

    if (success)
    {
        (*ppD3D12Device)->Release();
    }

    return success;
}

bool DX12Utils::IsFeatureLevelSupported(ID3D12Device* pD3D12Device)
{
    bool isHardwareSupported = false;
    D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevels;
    const D3D_FEATURE_LEVEL requestedFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_12_1,
    };

    featureLevels.NumFeatureLevels =
        (sizeof(requestedFeatureLevels) / sizeof(D3D_FEATURE_LEVEL));
    featureLevels.pFeatureLevelsRequested = requestedFeatureLevels;
    featureLevels.MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL_12_1;
    HRESULT hr = pD3D12Device->CheckFeatureSupport(
                     D3D12_FEATURE_FEATURE_LEVELS, &featureLevels, sizeof(featureLevels));

    if (SUCCEEDED(hr))
    {
        if (D3D_FEATURE_LEVEL_12_0 <= featureLevels.MaxSupportedFeatureLevel)
        {
            isHardwareSupported = true;
        }
    }

    return isHardwareSupported;
}

bool DX12Utils::GetTimestampFrequency(ID3D12Device* pD3D12Device, UINT64& timestampFrequency)
{
    bool isSucceeded = false;
    ID3D12CommandQueue* pQueue = nullptr;
    D3D12_COMMAND_QUEUE_DESC queueDesc;
    ZeroMemory(&queueDesc, sizeof(queueDesc));
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    HRESULT hr = pD3D12Device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), reinterpret_cast<PVOID*>(&pQueue));

    if (SUCCEEDED(hr) || nullptr != pQueue)
    {
        UINT64 frequency = 0;
        hr = pQueue->GetTimestampFrequency(&frequency);

        if (SUCCEEDED(hr))
        {
            isSucceeded = true;
            timestampFrequency = frequency;
        }

        pQueue->Release();
    }

    return isSucceeded;
}
