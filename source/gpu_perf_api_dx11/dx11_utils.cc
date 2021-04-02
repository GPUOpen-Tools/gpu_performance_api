//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 utility function implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_utils.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

#include "gpu_perf_api_dx11/dxx_ext_utils.h"

bool dx11_utils::GetD3D11Device(IUnknown* interface_pointer, ID3D11Device** d3d11_device)
{
    *d3d11_device = nullptr;
    bool success  = false;

    // Check to see if it's an ID3D11Device.
    HRESULT hr = interface_pointer->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(d3d11_device));

    if (hr == E_NOINTERFACE)
    {
        // It's not an ID3D11device, so see if it is an ID3D11DeviceChild-derived interface.
        ID3D11DeviceChild* device_child = nullptr;
        hr                              = interface_pointer->QueryInterface(__uuidof(ID3D11DeviceChild), reinterpret_cast<void**>(&device_child));

        if (SUCCEEDED(hr))
        {
            // Note: GetDevice increments a ref on out parameter.
            device_child->GetDevice(d3d11_device);
            (*d3d11_device)->Release();
            device_child->Release();
        }
    }

    if (SUCCEEDED(hr))
    {
        success = true;
        (*d3d11_device)->Release();
    }

    return success;
}

bool dx11_utils::IsFeatureLevelSupported(ID3D11Device* d3d11_device)
{
    bool is_supported = true;

    // Get the current feature level in use by the application.
    D3D_FEATURE_LEVEL level = d3d11_device->GetFeatureLevel();

    // DX9 feature level is not supported.
    if (level == D3D_FEATURE_LEVEL_9_1 || level == D3D_FEATURE_LEVEL_9_2 || level == D3D_FEATURE_LEVEL_9_3)
    {
        GPA_LOG_ERROR("GPUPerfAPI does not support D3D_FEATURE_LEVEL_9_1, _9_2, and _9_3.");
        is_supported = false;
    }

    return is_supported;
}

bool dx11_utils::GetTimestampFrequency(ID3D11Device* d3d11_device, UINT64& timestamp_frequency)
{
    bool success = false;

    if (nullptr != d3d11_device)
    {
        ID3D11Query*     time_stamp_disjoint_query = nullptr;
        D3D11_QUERY_DESC time_stamp_desc;
        time_stamp_desc.Query     = D3D11_QUERY_TIMESTAMP_DISJOINT;
        time_stamp_desc.MiscFlags = 0;

        HRESULT hr = E_FAIL;
        hr         = d3d11_device->CreateQuery(&time_stamp_desc, &time_stamp_disjoint_query);

#ifdef _DEBUG
        D3D_SET_OBJECT_NAME_A(time_stamp_disjoint_query, "GPA_TimestampFrequencyQuery");
#endif

        if (SUCCEEDED(hr))
        {
            // Get immediate context.
            ID3D11DeviceContext* d3d_context = nullptr;
            d3d11_device->GetImmediateContext(&d3d_context);

            if (nullptr != d3d_context)
            {
                // Submit the query.
                d3d_context->Begin(time_stamp_disjoint_query);
                d3d_context->End(time_stamp_disjoint_query);

                // Need to loop on checking the values, it may not be immediately available.
                HRESULT data_ready = S_OK;

                do
                {
                    data_ready = d3d_context->GetData(time_stamp_disjoint_query, nullptr, 0, 0);

                    if (FAILED(data_ready))
                    {
                        GPA_LOG_ERROR("Call to ID3D11DeviceContext::GetData failed.");
                        return false;
                    }

                } while (S_FALSE == data_ready);  // S_OK == data ready; S_FALSE == data not ready.

                D3D11_QUERY_DATA_TIMESTAMP_DISJOINT time_stamp_disjoint;
                assert(time_stamp_disjoint_query->GetDataSize() == sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT));

                hr                  = d3d_context->GetData(time_stamp_disjoint_query, &time_stamp_disjoint, sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 0);
                timestamp_frequency = time_stamp_disjoint.Frequency;
                assert(SUCCEEDED(hr));
                success = true;

                d3d_context->Release();
                time_stamp_disjoint_query->Release();
                time_stamp_disjoint_query = nullptr;
            }
            else
            {
                GPA_LOG_ERROR("GetTimestampFrequency Immediate Context is NULL.");
            }
        }
        else
        {
            GPA_LOG_ERROR("GetTimestampFrequency Call to ID3D11Device::CreateQuery failed.");
        }
    }
    else
    {
        GPA_LOG_ERROR("GetTimestampFrequency DX11 Device is NULL.");
    }

    return success;
}
