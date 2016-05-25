//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 utility function implementations
//==============================================================================

#include "DX12Utils.h"
#include "d3d12.h"

GPA_Status DX12GetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc)
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
