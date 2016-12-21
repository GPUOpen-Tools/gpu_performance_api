//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA DX12 API implementation
//==============================================================================

#include "GPUPerfAPIDX12.h"

#include <DeviceInfoUtils.h>
#include <GPUPerfAPIImp.h>
#include "GPACounterGenerator.h"
#include "DX12Utils.h"
#include "GPAContextStateDX12.h"
#include "DX12CounterDataRequestProxy.h"

/// Access to the current GPA DX12 context
/// \return The current DX12 GPA context
inline GPA_ContextStateDX12* GetCurrentContext()
{
    return static_cast<GPA_ContextStateDX12*>(g_pCurrentContext);
} // end of GetCurrentContext

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
        IUnknown* pUnknown = static_cast<IUnknown*>(pContext);

        ID3D12GraphicsCommandList* pCommandList = nullptr;
        HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pCommandList));

        if (S_OK != hr)
        {
            GPA_LogError("Failed to get command list from context");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            ID3D12Device* pDevice;
            hr = pCommandList->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(&pDevice));

            if (S_OK != hr)
            {
                GPA_LogError("Failed to get device from command list");
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

                    if (nullptr == g_pCurrentContext)
                    {
                        GPA_LogError("g_pCurrentContext is NULL.");
                        result = GPA_STATUS_ERROR_NULL_POINTER;
                        return result;
                    }

                    GetCurrentContext()->SetCommandList(pCommandList);
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

                        // TODO: To enable running on WARP driver, fake a Bonaire HW ID if the device is the WARP device
                        if (0x8c == adapterDesc.DeviceId && AMD_VENDOR_ID == adapterDesc.VendorId)
                        {
                            pHwInfo->SetDeviceID(0x665C);
                            pHwInfo->SetRevisionID(0);
                        }
                        else
                        {
                            pHwInfo->SetVendorID(adapterDesc.VendorId);
                            pHwInfo->SetDeviceID(adapterDesc.DeviceId);
                            pHwInfo->SetRevisionID(adapterDesc.Revision);
                        }

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
                            AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(adapterDesc.DeviceId, hwGen);
                        }

                        pHwInfo->SetHWGeneration(hwGen);
                        pHwInfo->SetTimeStampFrequency(freq);
                    }

                }

                pDevice->Release();
            }

            pCommandList->Release();
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
} // end of GPA_IMP_CompareHwInfo

GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if ((nullptr == pContext) || (nullptr == pHwInfo))
    {
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        IUnknown* pUnknown = static_cast<IUnknown*>(pContext);

        ID3D12GraphicsCommandList* pCommandList = nullptr;
        HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pCommandList));

        if (S_OK != hr)
        {
            GPA_LogError("Failed to get command list from context");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            ID3D12Device* pDevice;
            hr = pCommandList->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(&pDevice));

            if (S_OK != hr)
            {
                GPA_LogError("Failed to get D3D12 device");
                result = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevels;
                static const D3D_FEATURE_LEVEL requestedFeatureLevels[] =
                {
                    D3D_FEATURE_LEVEL_11_0,
                    D3D_FEATURE_LEVEL_11_1,
                };
                featureLevels.NumFeatureLevels =
                    (sizeof(requestedFeatureLevels) / sizeof(D3D_FEATURE_LEVEL));
                featureLevels.pFeatureLevelsRequested = requestedFeatureLevels;
                featureLevels.MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL_11_1;
                hr = pDevice->CheckFeatureSupport(
                         D3D12_FEATURE_FEATURE_LEVELS, &featureLevels, sizeof(featureLevels));

                if (S_OK != hr)
                {
                    GPA_LogError("Failed to get D3D12 device feature levels");
                    result = GPA_STATUS_ERROR_FAILED;
                }
                else
                {
                    if (D3D_FEATURE_LEVEL_11_0 > featureLevels.MaxSupportedFeatureLevel)
                    {
                        result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                    }
                    else
                    {
                        // TODO Once DX12 performance extension is available, check
                        //      it's possible to create a HW counter
                    }
                }

                pDevice->Release();
            }

            pCommandList->Release();
        }
    }

    return result;
} // end of GPA_IMP_VerifyHwSupport

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
        GPA_LogError("Unable to create context");
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        (*ppNewContext) = pContext;
    }

    return result;
} // end of GPA_IMP_CreateContext

GPA_Status GPA_IMP_Initialize()
{
    // TODO Set the registry key to set the DX12 counter extension registry key
    return GPA_STATUS_OK;
} // end of GPA_IMP_Initialize

GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
} // end of GPA_IMP_Destroy

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
        IUnknown* pUnknown = static_cast<IUnknown*>(pContext);

        ID3D12GraphicsCommandList* pCommandList = nullptr;
        HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pCommandList));

        if (S_OK != hr)
        {
            GPA_LogError("Failed to get command list from context");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            bool setCommandList = GetCurrentContext()->SetCommandList(pCommandList);

            if (!setCommandList)
            {
                result = GPA_STATUS_ERROR_FAILED;
            }

            if (GPA_STATUS_OK == result)
            {
                gpa_uint32 vendorId = 0;
                gpa_uint32 deviceId = 0;
                gpa_uint32 revisionId = 0;

                if (false == (g_pCurrentContext->m_hwInfo.GetVendorID(vendorId)))
                {
                    result = GPA_STATUS_ERROR_FAILED;
                }
                else if (false == (g_pCurrentContext->m_hwInfo.GetDeviceID(deviceId)))
                {
                    result = GPA_STATUS_ERROR_FAILED;
                }
                else if (false == (g_pCurrentContext->m_hwInfo.GetRevisionID(revisionId)))
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
                        g_pCurrentContext->m_pCounterAccessor =
                            static_cast<GPA_CounterGeneratorBase*>(pCounterAccessor);
                        g_pCurrentContext->m_pCounterScheduler = pCounterScheduler;
                    }
                }
            }

            pCommandList->Release();
        }
    }

    return result;
} // end of GPA_IMP_OpenContext

GPA_Status GPA_IMP_CloseContext()
{
    if (nullptr != GetCurrentContext())
    {
        GetCurrentContext()->Cleanup();
    }

    return GPA_STATUS_OK;
} // end of GPA_IMP_CloseContext

GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);
    return GPA_STATUS_OK;
} // end of GPA_IMP_SelectContext

GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    GPA_Status result = GetCurrentContext()->BeginSession();

    if (GPA_STATUS_OK != result)
    {
        GPA_LogError("Failed to enable stable power state in begin session");
    }

    return result;
} // end of GPA_IMP_BeginSession

GPA_Status GPA_IMP_EndSession()
{
    GPA_Status result = GetCurrentContext()->EndSession();

    if (GPA_STATUS_OK != result)
    {
        GPA_LogError("Failed to disable stable power state in end session");
    }

    return result;
} // end of GPA_IMP_EndSession

GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
} // end of GPA_IMP_BeginPass

GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
} // end of GPA_IMP_EndPass

GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleId)
{
    UNREFERENCED_PARAMETER(sampleId);
    return GPA_STATUS_OK;
} // end of GPA_IMP_BeginSample

GPA_Status GPA_IMP_EndSample()
{
    return GPA_STATUS_OK;
} // end of GPA_IMP_EndSample

gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    static const gpa_uint32 hwMaxSessions = 32; // Use the same value as in DX11
    gpa_uint32 maxSessions = hwMaxSessions;
    return maxSessions;
} // end of GPA_IMP_GetDefaultMaxSessions

gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 50; // Use the same value as in DX11
} // end of GPA_IMP_GetPreferredCheckResultFrequency()

GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    GPA_DataRequest* pDataRequest = nullptr;
    GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("No context available. Unable to create a data request.");
        return nullptr;
    }
    else if (false == g_pCurrentContext->m_hwInfo.GetHWGeneration(hwGen))
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
} // end of GPA_IMP_CreateDataRequest
