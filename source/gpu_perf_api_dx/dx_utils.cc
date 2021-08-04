//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Common DX utility function implementations
//==============================================================================

#include "dx_utils.h"

GpaStatus DxGetAdapterDesc(IUnknown* device, DXGI_ADAPTER_DESC& adapter_desc)
{
    GpaStatus status = kGpaStatusOk;

    if (nullptr == device)
    {
        GPA_LOG_ERROR("NULL device.");
        status = kGpaStatusErrorNullPointer;
    }
    else
    {
        IDXGIDevice1* dxgi_device = nullptr;
        HRESULT       hr          = device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&dxgi_device));

        if (FAILED(hr) || (nullptr == dxgi_device))
        {
            GPA_LOG_ERROR("Unable to get IDXGIDevice1 interface from ID3D11Device.");
            status = kGpaStatusErrorFailed;
        }
        else
        {
            IDXGIAdapter* adapter = nullptr;
            hr                     = dxgi_device->GetAdapter(&adapter);

            if (FAILED(hr) || (nullptr == adapter))
            {
                GPA_LOG_ERROR("Unable to get Adapter from IDXGIDevice1.");
                status = kGpaStatusErrorFailed;
            }
            else
            {
                memset(&adapter_desc, 0, sizeof(adapter_desc));
                hr = adapter->GetDesc(&adapter_desc);

                if (S_OK != hr)
                {
                    GPA_LOG_ERROR("Could not get adapter description, hardware cannot be supported.");
                    status = kGpaStatusErrorHardwareNotSupported;
                }

                adapter->Release();
            }

            dxgi_device->Release();
        }
    }

    return status;
}

HMONITOR DxGetDeviceMonitor(IUnknown* device)
{
    HMONITOR h_monitor = nullptr;

    if (nullptr == device)
    {
        GPA_LOG_ERROR("NULL device.");
    }
    else
    {
        IDXGIDevice1* dxgi_device = nullptr;
        HRESULT       hr          = device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&dxgi_device));

        if (FAILED(hr) || (nullptr == dxgi_device))
        {
            GPA_LOG_ERROR("Unable to get IDXGIDevice1 interface from ID3D11Device.");
        }
        else
        {
            IDXGIAdapter* adapter = nullptr;
            hr                     = dxgi_device->GetAdapter(&adapter);

            if (FAILED(hr) || (nullptr == adapter))
            {
                GPA_LOG_ERROR("Unable to get Adapter from IDXGIDevice1.");
            }
            else
            {
                IDXGIOutput* output = nullptr;
                hr                   = adapter->EnumOutputs(0, &output);

                if (S_OK != hr)
                {
                    GPA_LOG_ERROR("Unable to get Adapter outputs.");
                }
                else
                {
                    DXGI_OUTPUT_DESC output_desc;
                    hr = output->GetDesc(&output_desc);

                    if (S_OK != hr)
                    {
                        GPA_LOG_ERROR("Failed to get output description.");
                    }
                    else
                    {
                        h_monitor = output_desc.Monitor;
                    }

                    output->Release();
                }

                adapter->Release();
            }

            dxgi_device->Release();
        }
    }

    return h_monitor;
}
