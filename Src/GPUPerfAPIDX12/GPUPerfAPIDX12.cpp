//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX12 API implementation
//==============================================================================

#include "GPUPerfAPIDX12.h"

#include <DeviceInfoUtils.h>
#include "GPUPerfAPIImp.h"
#include "GPUPerfAPI.h"
#include "GPACounterGenerator.h"
#include "DX12Utils.h"
#include "GPAContextStateDX12.h"
#include "DX12CounterDataRequestProxy.h"

/// Access to the current GPA DX12 context
/// \return The current DX12 GPA context
inline GPA_ContextStateDX12* GetCurrentContext()
{
    return static_cast<GPA_ContextStateDX12* >(g_pCurrentContext);
}


/// Get an ID3D12Device from pContext which could be one of several interface types
/// \param pContext The GPA context pointer
/// \param ppDevice The returned ID3D12Device pointer
/// \return HRESULT indicating success or failure
static HRESULT GetID3D12Device(void* pContext, ID3D12Device** ppDevice)
{
    *ppDevice = nullptr;

    // pContext could be an ID3D12Device or ID3D12CommandList
    IUnknown* pUnknown = static_cast<IUnknown*>(pContext);

    // Check to see if it's an ID3D12Device
    HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12Device), reinterpret_cast<void**>(ppDevice));

    if (hr == E_NOINTERFACE)
    {
        // It's not an ID3D12device, so see if it's an ID3D12CommandList or other ID3D12DeviceChild derived interface
        ID3D12DeviceChild* pDeviceChild = nullptr;

        hr = pUnknown->QueryInterface(__uuidof(ID3D12DeviceChild), reinterpret_cast<void**>(&pDeviceChild));
        if (SUCCEEDED(hr))
        {
            hr = pDeviceChild->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(ppDevice));
            pDeviceChild->Release();
        }
    }
    return hr;
}

GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        ID3D12Device* pDevice = nullptr;
        HRESULT hr = GetID3D12Device(pContext, &pDevice);

        if (FAILED(hr))
        {
            GPA_LogError("Failed to get command list from context.");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            DXGI_ADAPTER_DESC adapterDesc;
            result = DX12GetAdapterDesc(pDevice, adapterDesc);

            if (GPA_STATUS_OK != result)
            {
                GPA_LogError("Could not get adapter description, hardware cannot be supported.");
                result = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                //get Time stamp frequency
                gpa_uint64 freq = 0ull;

                result = GetCurrentContext()->SetD3D12Device(pDevice, adapterDesc.VendorId == AMD_VENDOR_ID);

                if (GPA_STATUS_OK == result)
                {
                    result = GetCurrentContext()->GetTimestampFrequency(freq);

                    if (GPA_STATUS_OK != result)
                    {
                        GPA_LogError("GetTimestampFrequency() failed.");
                    }
                    else
                    {
                        // For now it is assumed that DX12 MGPU support is exposed to the app
                        // and the app always opens the device on the correct GPU.
                        // In case where MGPU support hides the GPU from the app, then
                        // we will need to use DX12 MGPU extension (and possibly ADL util)
                        // to get the correct HW info
                        pHwInfo->SetVendorID(adapterDesc.VendorId);

                        pHwInfo->SetVendorID(adapterDesc.VendorId);
                        pHwInfo->SetDeviceID(adapterDesc.DeviceId);
                        pHwInfo->SetRevisionID(adapterDesc.Revision);

                        std::wstring adapterNameW(adapterDesc.Description);
                        std::string adapterName(adapterNameW.begin(), adapterNameW.end());
                        pHwInfo->SetDeviceName(adapterName.c_str());
                        GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

                        if (NVIDIA_VENDOR_ID == adapterDesc.VendorId)
                        {
                            hwGen = GDT_HW_GENERATION_NVIDIA;
                        }
                        else if (INTEL_VENDOR_ID == adapterDesc.VendorId)
                        {
                            hwGen = GDT_HW_GENERATION_INTEL;
                        }

                        else if (AMD_VENDOR_ID == adapterDesc.VendorId)
                        {
                            GDT_GfxCardInfo cardInfo;

                            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(adapterDesc.DeviceId, adapterDesc.Revision, cardInfo))
                            {
                                hwGen = cardInfo.m_generation;

                                // GPA DX12 requires GFX8 or above (but also works on Hawaii)
                                if (GDT_HW_GENERATION_VOLCANICISLAND > hwGen && GDT_HAWAII != cardInfo.m_asicType)
                                {
                                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                                }
                            }
                        }

                        pHwInfo->SetHWGeneration(hwGen);
                        pHwInfo->SetTimeStampFrequency(freq);
                    }
                }
            }

            pDevice->Release();
        }
    }

    return result;
}

GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_HWInfo hwInfo;
        result = GPA_IMP_GetHWInfo(pContext, &hwInfo);

        if (GPA_STATUS_OK == result)
        {
            result = CompareHwInfo(pHwInfo, &hwInfo);
        }
    }

    return result;
}

GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    // NOTE: checking that the hardware supports hw perf counters is done in GPA_ContextStateDX12::SetD3D12Device

    GPA_Status result = GPA_STATUS_OK;

    if ((nullptr == pContext) || (nullptr == pHwInfo))
    {
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        ID3D12Device* pDevice = nullptr;
        HRESULT hr = GetID3D12Device(pContext, &pDevice);

        if (FAILED(hr))
        {
            GPA_LogError("Failed to get device from context.");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevels;
            static const D3D_FEATURE_LEVEL requestedFeatureLevels[] =
            {
                D3D_FEATURE_LEVEL_12_0,
                D3D_FEATURE_LEVEL_12_1,
            };

            featureLevels.NumFeatureLevels =
                (sizeof(requestedFeatureLevels) / sizeof(D3D_FEATURE_LEVEL));
            featureLevels.pFeatureLevelsRequested = requestedFeatureLevels;
            featureLevels.MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL_12_1;
            hr = pDevice->CheckFeatureSupport(
                     D3D12_FEATURE_FEATURE_LEVELS, &featureLevels, sizeof(featureLevels));

            if (FAILED(hr))
            {
                GPA_LogError("Failed to get D3D12 device feature levels.");
                result = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                // require at least DX12 feature-level-capable hardware
                if (D3D_FEATURE_LEVEL_12_0 > featureLevels.MaxSupportedFeatureLevel)
                {
                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                }
            }

            pDevice->Release();
        }
    }

    return result;
}

GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateDX12* pContext = new(std::nothrow) GPA_ContextStateDX12;

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to create context.");
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        (*ppNewContext) = pContext;
    }

    return result;
}

GPA_Status GPA_IMP_Initialize()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_OpenContext(void* pContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to open context. Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        ID3D12Device* pDevice = nullptr;
        HRESULT hr = GetID3D12Device(pContext, &pDevice);

        if (FAILED(hr))
        {
            GPA_LogError("Failed to get command list from context.");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            gpa_uint32 vendorId = 0;
            gpa_uint32 deviceId = 0;
            gpa_uint32 revisionId = 0;

            if (false == (GetCurrentContext()->m_hwInfo.GetVendorID(vendorId)))
            {
                result = GPA_STATUS_ERROR_FAILED;
            }
            else if (false == (GetCurrentContext()->m_hwInfo.GetDeviceID(deviceId)))
            {
                result = GPA_STATUS_ERROR_FAILED;
            }
            else if (false == (GetCurrentContext()->m_hwInfo.GetRevisionID(revisionId)))
            {
                result = GPA_STATUS_ERROR_FAILED;
            }

            if (GPA_STATUS_OK == result)
            {
                GPA_ICounterAccessor* pCounterAccessor = nullptr;
                GPA_ICounterScheduler* pCounterScheduler = nullptr;
                result = GenerateCounters(
                                GPA_API_DIRECTX_12,
                                vendorId,
                                deviceId,
                                revisionId,
                                &pCounterAccessor,
                                &pCounterScheduler);

                if (GPA_STATUS_OK == result)
                {
                    GetCurrentContext()->m_pCounterAccessor =
                        static_cast<GPA_CounterGeneratorBase*>(pCounterAccessor);
                    GetCurrentContext()->m_pCounterScheduler = pCounterScheduler;
                }
            }

            pDevice->Release();
        }
    }

    return result;
}

GPA_Status GPA_IMP_CloseContext()
{
    if (nullptr != GetCurrentContext())
    {
        GetCurrentContext()->Cleanup();
    }

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndSession()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSampleList(void* pSampleList)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pSampleList)
    {
        GPA_LogError("Cannot begin a sample list for a null sample list.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        result = GetCurrentContext()->BeginCommandList(pSampleList);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Unable to begin a sample list.");
        }
    }

    if (GPA_STATUS_OK == result)
    {
        g_pCurrentContext->SetInvalidateAndFlushL2Cache(true);
    }

    return result;
}

GPA_Status GPA_IMP_EndSampleList(void* pSampleList)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pSampleList)
    {
        GPA_LogError("Cannot end a sample list for a null sample list.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        result = GetCurrentContext()->EndCommandList(pSampleList);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Unable to end a sample list.");
        }
    }

    return result;
}

GPA_Status GPA_IMP_BeginSampleInSampleList(gpa_uint32 sampleID, void* pSampleList)
{
    UNREFERENCED_PARAMETER(sampleID);
    UNREFERENCED_PARAMETER(pSampleList);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndSampleInSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID)
{
    UNREFERENCED_PARAMETER(sampleID);
    GPA_LogError("GPA_BeginSample is not supported. Use GPA_BeginSampleInSampleList instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

GPA_Status GPA_IMP_EndSample()
{
    GPA_LogError("GPA_EndSample is not supported. Use GPA_EndSampleInSampleList instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    static const gpa_uint32 hwMaxSessions = 32;
    return hwMaxSessions;
}

gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 0;
}

GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    GPA_DataRequest* pDataRequest = nullptr;
    GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

    if (nullptr == GetCurrentContext())
    {
        GPA_LogError("No context available. Unable to create a data request.");
        return nullptr;
    }
    else if (false == GetCurrentContext()->m_hwInfo.GetHWGeneration(hwGen))
    {
        GPA_LogError("Unable to get hardware generation.");
    }
    else
    {
        if (GDT_HW_GENERATION_NONE == hwGen)
        {
            GPA_LogError("Invalid hardware generation.");
        }
        else
        {
            pDataRequest = new(std::nothrow) DX12CounterDataRequestProxy;
        }
    }

    return pDataRequest;
}
