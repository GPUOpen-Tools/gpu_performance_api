//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Common DX utility function implementations
//==============================================================================

#include "dx_utils.h"

GPA_Status DXGetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pDevice)
    {
        GPA_LogError("NULL device.");
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        IDXGIDevice1* pDXGIDevice = nullptr;
        HRESULT       hr          = pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDXGIDevice));

        if (FAILED(hr) || (nullptr == pDXGIDevice))
        {
            GPA_LogError("Unable to get IDXGIDevice1 interface from ID3D11Device.");
            status = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            IDXGIAdapter* pAdapter = nullptr;
            hr                     = pDXGIDevice->GetAdapter(&pAdapter);

            if (FAILED(hr) || (nullptr == pAdapter))
            {
                GPA_LogError("Unable to get Adapter from IDXGIDevice1.");
                status = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                memset(&adapterDesc, 0, sizeof(adapterDesc));
                hr = pAdapter->GetDesc(&adapterDesc);

                if (S_OK != hr)
                {
                    GPA_LogError("Could not get adapter description, hardware cannot be supported.");
                    status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                }

                pAdapter->Release();
            }

            pDXGIDevice->Release();
        }
    }

    return status;
}

HMONITOR DXGetDeviceMonitor(IUnknown* pDevice)
{
    HMONITOR hMonitor = nullptr;

    if (nullptr == pDevice)
    {
        GPA_LogError("NULL device.");
    }
    else
    {
        IDXGIDevice1* pDXGIDevice = nullptr;
        HRESULT       hr          = pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDXGIDevice));

        if (FAILED(hr) || (nullptr == pDXGIDevice))
        {
            GPA_LogError("Unable to get IDXGIDevice1 interface from ID3D11Device.");
        }
        else
        {
            IDXGIAdapter* pAdapter = nullptr;
            hr                     = pDXGIDevice->GetAdapter(&pAdapter);

            if (FAILED(hr) || (nullptr == pAdapter))
            {
                GPA_LogError("Unable to get Adapter from IDXGIDevice1.");
            }
            else
            {
                IDXGIOutput* pOutput = nullptr;
                hr                   = pAdapter->EnumOutputs(0, &pOutput);

                if (S_OK != hr)
                {
                    GPA_LogError("Unable to get Adapter outputs.");
                }
                else
                {
                    DXGI_OUTPUT_DESC outputDesc;
                    hr = pOutput->GetDesc(&outputDesc);

                    if (S_OK != hr)
                    {
                        GPA_LogError("Failed to get output description.");
                    }
                    else
                    {
                        hMonitor = outputDesc.Monitor;
                    }

                    pOutput->Release();
                }

                pAdapter->Release();
            }

            pDXGIDevice->Release();
        }
    }

    return hMonitor;
}
