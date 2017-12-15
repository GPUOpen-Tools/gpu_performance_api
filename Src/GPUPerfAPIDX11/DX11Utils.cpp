//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 utility function implementation
//==============================================================================

#include "DX11Utils.h"
#include "DxxExtUtils.h"
#include "GPACommonDefs.h"


bool DX11Utils::GetD3D11Device(IUnknown* pInterfacePointer, ID3D11Device** ppD3D11Device)
{
    *ppD3D11Device = nullptr;

    // Check to see if it's an ID3D11Device
    HRESULT hr = pInterfacePointer->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(ppD3D11Device));

    if (hr == E_NOINTERFACE)
    {
        // It's not an ID3D11device, so see if it is an ID3D11DeviceChild-derived interface
        ID3D11DeviceChild* pDeviceChild = nullptr;

        hr = pInterfacePointer->QueryInterface(__uuidof(ID3D11DeviceChild), reinterpret_cast<void**>(&pDeviceChild));

        if (SUCCEEDED(hr))
        {
            // Note: GetDevice increments a ref on out parameter
            pDeviceChild->GetDevice(ppD3D11Device);
            pDeviceChild->Release();
        }
    }

    return SUCCEEDED(hr);
}

bool DX11Utils::IsFeatureLevelSupported(ID3D11Device* pD3D11Device)
{
    bool isSupported = true;

    // Get the current feature level in use by the application
    D3D_FEATURE_LEVEL level = pD3D11Device->GetFeatureLevel();

    // DX9 feature level is not supported
    if (level == D3D_FEATURE_LEVEL_9_1 ||
        level == D3D_FEATURE_LEVEL_9_2 ||
        level == D3D_FEATURE_LEVEL_9_3)
    {
        GPA_LogError("GPUPerfAPI does not support D3D_FEATURE_LEVEL_9_1, _9_2, and _9_3.");
        isSupported = false;
    }

    return isSupported;
}

bool DX11Utils::GetTimestampFrequency(ID3D11Device* pD3D11Device, UINT64& timestampFrequency)
{
    bool success = false;

    ID3D11Query* timeStampDisjointQuery;
    D3D11_QUERY_DESC timeStampDesc;
    timeStampDesc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
    timeStampDesc.MiscFlags = 0;

    HRESULT hr = E_FAIL;
    hr = pD3D11Device->CreateQuery(&timeStampDesc, &timeStampDisjointQuery);

    if (hr == S_OK)
    {
        // get immediate context
        ID3D11DeviceContext* pD3DContext = nullptr;
        pD3D11Device->GetImmediateContext(&pD3DContext);

        if (pD3DContext != nullptr)
        {
            //Submit the query
            pD3DContext->Begin(timeStampDisjointQuery);
            pD3DContext->End(timeStampDisjointQuery);

            // need to loop on checking the values, it may not be immediately available.
            while (S_OK != pD3DContext->GetData(timeStampDisjointQuery, nullptr, 0, 0))
            {
                // Wait for the data to be ready
            }

            D3D11_QUERY_DATA_TIMESTAMP_DISJOINT timeStampDisjoint;
            assert(timeStampDisjointQuery->GetDataSize() == sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT));

            hr = pD3DContext->GetData(timeStampDisjointQuery, &timeStampDisjoint, sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 0);
            timestampFrequency = timeStampDisjoint.Frequency;
            assert(hr == S_OK);
            success = true;
        }
        else
        {
            GPA_LogError("ERROR: Immediate Context is NULL.");
        }
    }
    else
    {
        GPA_LogError("Call to ID3D11Device::CreateQuery failed.");
    }

    return success;
}

