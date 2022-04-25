//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file contains the implementation of three macro redefinitions
///         from pix3_win.h with AMD RGP marker support.
///         This requires AMD driver with a device level marker extension support
///         (driver 17.30.1081 or newer).
///         To use: Update the pix3.h file to replace #include "pix3_win.h" by 
///                 including this file instead. Also check the RGP
///                 user documentation for a complete user guide.
/// \warning Only support the unicode character set (does not support multi-byte)
//==============================================================================
#ifndef _AMD_PIX3_H_
#define _AMD_PIX3_H_

// include original Microsoft PIX3 header file
#include "../pix3_win.h"

#include <stdio.h>
#include <stdarg.h>
#include "AmdExtD3D.h"
#include "AmdExtD3DDeviceApi.h"

// undefine three macro definitions from pix3_win.h to be redefined with AMD RGP marker support
#undef PIXSetCPUMarkerOnContext
#undef PIXBeginCPUEventOnContext
#undef PIXEndCPUEventOnContext

#define MAX_MARKER_STRING_LENGTH 1024

// per thread amd ext device object using TLS
static __declspec(thread) IAmdExtD3DDevice1* tls_pAmdExtDeviceObject = nullptr;

// this function will initialize the tls_pAmdExtDeviceObject per thread
// tls_pAmdExtDeviceObject contains the marker API
inline void InitializeAmdExtDeviceObject(ID3D12GraphicsCommandList* pCommandList)
{
    // return immediately if the device extension object has been created for the thread
    if (nullptr != tls_pAmdExtDeviceObject)
    {
        return;
    }

    HMODULE hpAmdD3dDl2 = LoadLibrary(L"amdxc64.dll");

    if (nullptr != hpAmdD3dDl2)
    {
        PFNAmdExtD3DCreateInterface pAmdExtD3dCreateFunc = (PFNAmdExtD3DCreateInterface) GetProcAddress(hpAmdD3dDl2,
                                                           "AmdExtD3DCreateInterface");

        if (nullptr != pAmdExtD3dCreateFunc)
        {
            ID3D12Device* pDevice = nullptr;

            if (nullptr != pCommandList)
            {
                pCommandList->GetDevice(__uuidof(ID3D12Device),
                                        reinterpret_cast<void**>(&pDevice));
            }

            if (nullptr != pDevice)
            {
                // create the extension object factory
                IAmdExtD3DFactory* pAmdExtObject = nullptr;
                pAmdExtD3dCreateFunc(pDevice,
                                     __uuidof(IAmdExtD3DFactory),
                                     reinterpret_cast<void**>(&pAmdExtObject));

                if (nullptr != pAmdExtObject)
                {
                    // use the extension factory object to create a device extension object that contains the marker API
                    pAmdExtObject->CreateInterface(pDevice,
                                                   __uuidof(IAmdExtD3DDevice1),
                                                   reinterpret_cast<void**>(&tls_pAmdExtDeviceObject));
                }
            }
        }
    }
}

inline void RgpSetMarker(ID3D12GraphicsCommandList* pCommandList, PCWSTR formatString, ...)
{
    InitializeAmdExtDeviceObject(pCommandList);

    if (nullptr != tls_pAmdExtDeviceObject)
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
        tls_pAmdExtDeviceObject->SetMarker(pCommandList, markerString);
    }
}

inline void RgpPushMarker(ID3D12GraphicsCommandList* pCommandList, PCWSTR formatString, ...)
{
    InitializeAmdExtDeviceObject(pCommandList);

    if (nullptr != tls_pAmdExtDeviceObject)
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
        tls_pAmdExtDeviceObject->PushMarker(pCommandList, markerString);
    }
}

inline void RgpPopMarker(ID3D12GraphicsCommandList* pCommandList)
{
    InitializeAmdExtDeviceObject(pCommandList);

    if (nullptr != tls_pAmdExtDeviceObject)
    {
        tls_pAmdExtDeviceObject->PopMarker(pCommandList);
    }
}

inline void RgpSetMarker(ID3D12CommandQueue*, PCWSTR, ...)
{
    // there is no queue-based marker yet
}

inline void RgpPushMarker(ID3D12CommandQueue*, PCWSTR, ...)
{
    // there is no queue-based marker yet
}

inline void RgpPopMarker(ID3D12CommandQueue*)
{
    // there is no queue-based marker yet
}

// redefine the three macros from pix_win3.h
#define PIXSetCPUMarkerOnContext(context, metadata, formatString, ...)              \
    RgpSetMarker(context, formatString, __VA_ARGS__);                               \
    MakeCPUSetMarkerForContext(metadata, context, formatString, __VA_ARGS__)

#define PIXBeginCPUEventOnContext(context, metadata, formatString, ...)             \
    RgpPushMarker(context, formatString,  __VA_ARGS__);                             \
    MakeCPUBeginEventForContext(metadata, context, formatString, __VA_ARGS__)

#define PIXEndCPUEventOnContext(context)                                            \
    RgpPopMarker(context);                                                          \
    MakeCPUEndEventForContext(context)

#endif //_AMD_PIX3_H_
