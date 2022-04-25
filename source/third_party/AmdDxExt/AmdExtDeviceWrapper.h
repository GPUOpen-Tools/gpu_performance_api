//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file contains a wrapper implementation for the IAmdExtD3DDevice1
///         interface.
///         This requires AMD driver with a device level marker extension support
///         (driver 17.30.1081 or newer).
/// \warning Only support the unicode character set (does not support multi-byte)
//==============================================================================
#ifndef _AMD_EXT_DEVICE_WRAPPER_H_
#define _AMD_EXT_DEVICE_WRAPPER_H_

#include <stdio.h>
#include <stdarg.h>
#include "AmdExtD3D.h"
#include "AmdExtD3DDeviceApi.h"

class AmdExtD3DDeviceWrapper
{
public:
    static const uint32_t MAX_MARKER_STRING_LENGTH = 1024;

    ~AmdExtD3DDeviceWrapper()
    {
        if (nullptr != m_pAmdExtDeviceObject)
        {
            m_pAmdExtDeviceObject = nullptr;

            m_d3d12Device.Reset();
        }
    }

    // this function will initialize the m_pAmdExtDeviceObject which contains the marker API
    inline void InitializeAmdExtDeviceObject(ID3D12GraphicsCommandList* pCommandList)
    {
        // return immediately if the device extension object has been created
        if (nullptr != m_pAmdExtDeviceObject)
        {
            return;
        }

        HMODULE hpAmdD3dDl2 = LoadLibrary(L"amdxc64.dll");

        if (nullptr != hpAmdD3dDl2)
        {
            PFNAmdExtD3DCreateInterface pAmdExtD3dCreateFunc = (PFNAmdExtD3DCreateInterface)GetProcAddress(hpAmdD3dDl2,
                "AmdExtD3DCreateInterface");

            if (nullptr != pAmdExtD3dCreateFunc)
            {
                if (nullptr != pCommandList)
                {
                    pCommandList->GetDevice(__uuidof(ID3D12Device),
                        reinterpret_cast<void**>(m_d3d12Device.GetAddressOf()));
                }

                if (nullptr != m_d3d12Device.Get())
                {
                    // create the extension object factory
                    IAmdExtD3DFactory* pAmdExtObject = nullptr;
                    pAmdExtD3dCreateFunc(m_d3d12Device.Get(),
                        __uuidof(IAmdExtD3DFactory),
                        reinterpret_cast<void**>(&pAmdExtObject));

                    if (nullptr != pAmdExtObject)
                    {
                        // use the extension factory object to create a device extension object that contains the marker API
                        pAmdExtObject->CreateInterface(m_d3d12Device.Get(),
                            __uuidof(IAmdExtD3DDevice1),
                            reinterpret_cast<void**>(&m_pAmdExtDeviceObject));
                    }
                }
            }
        }
    }

    inline void RgpSetMarker(ID3D12GraphicsCommandList* pCommandList, PCWSTR formatString, ...)
    {
        if (nullptr != m_pAmdExtDeviceObject)
        {
            // convert from wchar_t to char string
            char formatStringInChar[MAX_MARKER_STRING_LENGTH];
            size_t retValue = 0;
            wcstombs_s(&retValue, formatStringInChar, MAX_MARKER_STRING_LENGTH, formatString, MAX_MARKER_STRING_LENGTH);

            // create a new marker string that includes all the variadic args
            char markerString[MAX_MARKER_STRING_LENGTH];
            va_list args;
            va_start(args, formatString);
            vsprintf_s(markerString, formatStringInChar, args);
            va_end(args);

            // set the rgp marker
            m_pAmdExtDeviceObject->SetMarker(pCommandList, markerString);
        }
    }

    inline void RgpPushMarker(ID3D12GraphicsCommandList* pCommandList, PCWSTR formatString, ...)
    {
        if (nullptr != m_pAmdExtDeviceObject)
        {
            // convert from wchar_t to char string
            char formatStringInChar[MAX_MARKER_STRING_LENGTH];
            size_t retValue = 0;
            wcstombs_s(&retValue, formatStringInChar, MAX_MARKER_STRING_LENGTH, formatString, MAX_MARKER_STRING_LENGTH);

            // create a new marker string that includes all the variadic args
            char markerString[MAX_MARKER_STRING_LENGTH];
            va_list args;
            va_start(args, formatString);
            vsprintf_s(markerString, formatStringInChar, args);
            va_end(args);

            // push the rgp marker
            m_pAmdExtDeviceObject->PushMarker(pCommandList, markerString);
        }
    }

    inline void RgpPopMarker(ID3D12GraphicsCommandList* pCommandList)
    {
        if (nullptr != m_pAmdExtDeviceObject)
        {
            m_pAmdExtDeviceObject->PopMarker(pCommandList);
        }
    }

private:
    // IDirect3D12Device interface object
    ComPtr<ID3D12Device> m_d3d12Device;

    // IAmdExtD3DDevice1 interface object
    IAmdExtD3DDevice1* m_pAmdExtDeviceObject = nullptr;

} static gs_amdExtD3DDeviceWrapper;

#endif //_AMD_EXT_DEVICE_WRAPPER_H_
