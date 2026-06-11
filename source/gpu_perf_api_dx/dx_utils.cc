//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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
        GpaLogger::Instance().LogError("NULL device.");
        status = kGpaStatusErrorNullPointer;
    }
    else
    {
        IDXGIDevice1* dxgi_device = nullptr;
        HRESULT       hr          = device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&dxgi_device));

        if (FAILED(hr) || (nullptr == dxgi_device))
        {
            GpaLogger::Instance().LogError("Unable to get IDXGIDevice1 interface from ID3D11Device.");
            status = kGpaStatusErrorFailed;
        }
        else
        {
            IDXGIAdapter* adapter = nullptr;
            hr                     = dxgi_device->GetAdapter(&adapter);

            if (FAILED(hr) || (nullptr == adapter))
            {
                GpaLogger::Instance().LogError("Unable to get Adapter from IDXGIDevice1.");
                status = kGpaStatusErrorFailed;
            }
            else
            {
                memset(&adapter_desc, 0, sizeof(adapter_desc));
                hr = adapter->GetDesc(&adapter_desc);

                if (S_OK != hr)
                {
                    GpaLogger::Instance().LogError("Could not get adapter description, hardware cannot be supported.");
                    status = kGpaStatusErrorHardwareNotSupported;
                }

                adapter->Release();
            }

            dxgi_device->Release();
        }
    }

    return status;
}
