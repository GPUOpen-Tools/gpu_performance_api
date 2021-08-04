//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 utility function implementations
//==============================================================================

#include "gpu_perf_api_dx12/dx12_utils.h"

#include "d3d12.h"

#include "gpu_perf_api_common/logging.h"

GpaStatus dx12_utils::Dx12GetAdapterDesc(IUnknown* device, DXGI_ADAPTER_DESC& adapter_desc)
{
    GpaStatus status = kGpaStatusOk;

    if (nullptr == device)
    {
        GPA_LOG_ERROR("Parameter 'device' is NULL.");
        status = kGpaStatusErrorNullPointer;
    }
    else
    {
        ID3D12Device* dx12_device  = static_cast<ID3D12Device*>(device);
        LUID          adapter_luid = dx12_device->GetAdapterLuid();

        IDXGIFactory* dxgi_factory = nullptr;
        HRESULT       hr           = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgi_factory));

        if (FAILED(hr) || (nullptr == dxgi_factory))
        {
            GPA_LOG_ERROR("Unable to get IDXGIFactory interface from ID3D12Device.");
            status = kGpaStatusErrorFailed;
        }
        else
        {
            IDXGIAdapter* adapter = nullptr;

            for (UINT index = 0; dxgi_factory->EnumAdapters(index, &adapter) != DXGI_ERROR_NOT_FOUND; ++index)
            {
                memset(&adapter_desc, 0, sizeof(adapter_desc));
                hr = adapter->GetDesc(&adapter_desc);

                if (FAILED(hr))
                {
                    GPA_LOG_ERROR("Could not get adapter description, hardware cannot be supported.");
                    status = kGpaStatusErrorFailed;
                }
                else
                {
                    if (adapter_desc.AdapterLuid.HighPart == adapter_luid.HighPart && adapter_desc.AdapterLuid.LowPart == adapter_luid.LowPart)
                    {
                        // We found the matching adapter luid, so we're done.
                        break;
                    }
                }
            }
        }

        dxgi_factory->Release();
    }

    return status;
}

bool dx12_utils::IsD3D12CommandList(void* cmd, D3D12_COMMAND_LIST_TYPE* cmd_type)
{
    IUnknown*                  unknown = static_cast<IUnknown*>(cmd);
    ID3D12GraphicsCommandList* d3d_command_list;
    HRESULT                    hr     = unknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&d3d_command_list));
    bool                       result = SUCCEEDED(hr);

    if (result && nullptr != cmd_type)
    {
        *cmd_type = d3d_command_list->GetType();
        d3d_command_list->Release();  // We need to release this as QueryInterface will call AddRef.
    }

    return result;
}

bool dx12_utils::IsSameCmdType(const D3D12_COMMAND_LIST_TYPE* dx12_cmd_type, const GpaCommandListType* gpa_cmd_type)
{
    if (nullptr != dx12_cmd_type && nullptr != gpa_cmd_type)
    {
        if (D3D12_COMMAND_LIST_TYPE_BUNDLE == *dx12_cmd_type && kGpaCommandListSecondary == *gpa_cmd_type)
        {
            return true;
        }

        if (D3D12_COMMAND_LIST_TYPE_BUNDLE != *dx12_cmd_type && kGpaCommandListPrimary == *gpa_cmd_type)
        {
            return true;
        }
    }

    return false;
}

bool dx12_utils::GetD3D12Device(IUnknown* interface_pointer, ID3D12Device** d3d12_device)
{
    bool success  = false;
    *d3d12_device = nullptr;

    // Check to see if it's an ID3D12Device.
    HRESULT hr = interface_pointer->QueryInterface(__uuidof(ID3D12Device), reinterpret_cast<void**>(d3d12_device));

    if (hr == E_NOINTERFACE)
    {
        // It's not an ID3D12device, so see if it is an ID3D12DeviceChild-derived interface (like a ID3D12CommandList).
        ID3D12DeviceChild* device_child = nullptr;

        hr = interface_pointer->QueryInterface(__uuidof(ID3D12DeviceChild), reinterpret_cast<void**>(&device_child));

        if (SUCCEEDED(hr))
        {
            // Note: GetDevice increments a ref on out parameter.
            hr = device_child->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(d3d12_device));
            device_child->Release();
        }
    }

    success = SUCCEEDED(hr);

    if (success)
    {
        (*d3d12_device)->Release();
    }

    return success;
}

bool dx12_utils::IsFeatureLevelSupported(ID3D12Device* d3d12_device)
{
    D3D12_FEATURE_DATA_FEATURE_LEVELS feature_levels             = {};
    const D3D_FEATURE_LEVEL           requested_feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_12_1,
    };

    feature_levels.NumFeatureLevels        = _countof(requested_feature_levels);
    feature_levels.pFeatureLevelsRequested = requested_feature_levels;

    HRESULT hr = d3d12_device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &feature_levels, sizeof(feature_levels));

    return SUCCEEDED(hr);
}

bool dx12_utils::GetTimestampFrequency(ID3D12Device* d3d12_device, UINT64& timestamp_frequency)
{
    bool                     is_succeeded = false;
    ID3D12CommandQueue*      queue        = nullptr;
    D3D12_COMMAND_QUEUE_DESC queue_desc;
    ZeroMemory(&queue_desc, sizeof(queue_desc));
    queue_desc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    HRESULT hr       = d3d12_device->CreateCommandQueue(&queue_desc, __uuidof(ID3D12CommandQueue), reinterpret_cast<PVOID*>(&queue));

    if (SUCCEEDED(hr) || nullptr != queue)
    {
        UINT64 frequency = 0;
        hr               = queue->GetTimestampFrequency(&frequency);

        if (SUCCEEDED(hr))
        {
            is_succeeded        = true;
            timestamp_frequency = frequency;
        }
        else
        {
            GPA_LOG_ERROR("Calling GetTimestampFrequency on Direct Command Queue failed");
        }

        queue->Release();
    }
    else
    {
        GPA_LOG_ERROR("GetTimestampFrequency Create Command Queue failed");
    }

    return is_succeeded;
}
