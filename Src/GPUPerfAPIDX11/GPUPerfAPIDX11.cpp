//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 version of GPUPerfAPI
//==============================================================================

#include "GPUPerfAPIImp.h"
#include "GPACounterGenerator.h"

#include "DX11CounterDataRequest.h"
#include "D3D11SoftwareCounterDataRequest.h"
#include "DX11_PerfExperimentDataRequestHandler.h"
#include "DxxExtUtils.h"
#include "DX11ComSmartPtrs.h"

#include <d3d11.h>
#include <vector>
#include <string>
#include <assert.h>
#include <ADLUtil.h>
#include <DeviceInfoUtils.h>
#include <GPUPerfAPIRegistry.h>
#include "../GPUPerfAPIDX/dxUtils.h"
#include "DXGetAMDDeviceInfo.h"
#include "GPACustomHWValidationManager.h"

using std::string;

GPA_ContextStateDX11* getCurrentContext()
{
    return static_cast<GPA_ContextStateDX11* >(g_pCurrentContext);
}

gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 50;
}

//-----------------------------------------------------------------------------
/// Query time stamp frequency from hardware
//-----------------------------------------------------------------------------
bool queryTimeStampFrequency(void* context, gpa_uint64& frequency)
{
    ID3D11DevicePtr device = static_cast<ID3D11Device* >(context);
    ID3D11QueryPtr timeStampDisjointQuery;

    D3D11_QUERY_DESC timeStampDesc;
    timeStampDesc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
    timeStampDesc.MiscFlags = 0;

    HRESULT hr = E_FAIL;
    hr = device->CreateQuery(&timeStampDesc, &timeStampDisjointQuery);

    if (hr != S_OK)
    {
        GPA_LogError("Call to ID3D11Device::CreateQuery failed.");
        return false;
    }

    // get immediate context
    ID3D11DeviceContextPtr pD3DContext = nullptr;
    device->GetImmediateContext(&pD3DContext);

    if (pD3DContext == nullptr)
    {
        GPA_LogError("ERROR: Immediate Context is NULL.");
        return false;
    }

    //Submit the query
    pD3DContext->Begin(timeStampDisjointQuery);
    pD3DContext->End(timeStampDisjointQuery);

    // need to loop on checking the values, it may not be immediately available.
    while (pD3DContext->GetData(timeStampDisjointQuery, nullptr, 0, 0) != S_OK);

    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT timeStampDisjoint;
    assert(timeStampDisjointQuery->GetDataSize() == sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT));
    hr = pD3DContext->GetData(timeStampDisjointQuery, &timeStampDisjoint, sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 0);
    frequency = timeStampDisjoint.Frequency;
    assert(hr == S_OK);

    return true;
}

EXTERN_C IMAGE_DOS_HEADER __ImageBase; ///< __ImageBase symbol exported by MSVC linker
/// the HINSTANCE of the owning module
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

/// Get the HW Info for an AMD device
/// \param pDevice the D3D device
/// \param[out] pHwInfo the hw info
/// \param hMonitor the monitor where the device is rendering
/// \param primaryVendorId the vendor id of the primary device
/// \param primaryDeviceId the device id of the primary device
/// \return GPA_STATUS_OK on success
static GPA_Status GetAmdHwInfo(
    ID3D11Device* pDevice,
    GPA_HWInfo* pHwInfo,
    HMONITOR hMonitor,
    const int primaryVendorId,
    const int primaryDeviceId)
{
    GPA_Status result = GPA_STATUS_OK;

    HMODULE hDxxDll = nullptr;
#ifdef X64
    hDxxDll = GetModuleHandle("atidxx64.dll");
#else
    hDxxDll = GetModuleHandle("atidxx32.dll");
#endif

    if (nullptr == hDxxDll)
    {
#ifdef X64
        GPA_LogError("Unable to initialize because 'atidxx64.dll' is not available.");
#else
        GPA_LogError("Unable to initialize because 'atidxx32.dll' is not available.");
#endif
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        PFNAmdDxExtCreate11 AmdDxExtCreate11;
        AmdDxExtCreate11 = reinterpret_cast<PFNAmdDxExtCreate11>(GetProcAddress(hDxxDll, "AmdDxExtCreate11"));

        if (nullptr == AmdDxExtCreate11)
        {
            GPA_LogError("Unable to initialize because extension creation is not available.");
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            IAmdDxExt* pExt = nullptr;
            IAmdDxExtPerfProfile* pExtPerfProfile = nullptr;
            HRESULT hr = AmdDxExtCreate11(pDevice, &pExt);

            if (S_OK != hr)
            {
                result = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                unsigned int gpuIndex = 0;

                if (IsMgpuPerfExtSupported(pExt))
                {
                    pExtPerfProfile = reinterpret_cast<IAmdDxExtPerfProfile*>(pExt->GetExtInterface(AmdDxExtPerfProfileID));

                    if (nullptr == pExtPerfProfile)
                    {
                        // only fail here if the primary device is a device that is supposed to support the PerfProfile extension.
                        // Pre-GCN devices do not support this extension (they use the counter interface exposed by the API).
                        // By not returning a failure here on older devices, the caller code will do the right thing on those devices.
                        GDT_HW_GENERATION generation;

                        if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(primaryDeviceId, generation) && generation >= GDT_HW_GENERATION_SOUTHERNISLAND)
                        {
                            result = GPA_STATUS_ERROR_FAILED;
                        }
                    }
                    else
                    {
                        PE_RESULT peResult = PE_OK;
                        BOOL gpuProfileable = FALSE;

                        while ((PE_OK == peResult) && (FALSE == gpuProfileable))
                        {
                            peResult = pExtPerfProfile->IsGpuProfileable(gpuIndex, &gpuProfileable);
                            ++gpuIndex;
                        }

                        if (FALSE == gpuProfileable)
                        {
                            result = GPA_STATUS_ERROR_FAILED;
                        }
                        else
                        {
                            --gpuIndex; // gpu is over incremented in the loop above
                        }
                    }
                }

                pHwInfo->SetGpuIndex(gpuIndex);

                if (nullptr != pExtPerfProfile)
                {
                    pExtPerfProfile->Release();
                }

                if (nullptr != pExt)
                {
                    pExt->Release();
                }

                string strDLLName;
                char szThisModuleName[MAX_PATH];

                if (0 != GetModuleFileNameA(HINST_THISCOMPONENT, szThisModuleName, MAX_PATH))
                {
                    char szThisModulePath[MAX_PATH];
                    strncpy_s(szThisModulePath, MAX_PATH, szThisModuleName, strrchr(szThisModuleName, '\\') + 1 - szThisModuleName);
                    strDLLName = szThisModulePath;
                }

                int vendorId = primaryVendorId;
                int deviceId = primaryDeviceId;

                strDLLName.append("GPUPerfAPIDXGetAMDDeviceInfo");

#ifdef X64
                strDLLName.append("-x64");
#endif

                strDLLName.append(".dll");

                HMODULE hModule = LoadLibraryA(strDLLName.c_str());

                if (nullptr != hModule)
                {
                    static const char* pEntryPointName = "DXGetAMDDeviceInfo";
                    typedef decltype(DXGetAMDDeviceInfo)* DXGetAMDDeviceInfo_FuncType;
                    DXGetAMDDeviceInfo_FuncType DXGetAMDDeviceInfoFunc = reinterpret_cast<DXGetAMDDeviceInfo_FuncType>(GetProcAddress(hModule, pEntryPointName));

                    if (nullptr != DXGetAMDDeviceInfoFunc)
                    {
                        DXGetAMDDeviceInfoFunc(hMonitor, vendorId, deviceId);
                    }
                    else
                    {
                        string strLogErrorMsg = "Entry point '";
                        strLogErrorMsg.append(pEntryPointName);
                        strLogErrorMsg.append("' could not be found in ");
                        strLogErrorMsg.append(strDLLName);
                        strLogErrorMsg.append(".");
                        GPA_LogError(strLogErrorMsg.c_str());
                    }
                }
                else
                {
                    string strLogErrorMsg = strDLLName;
                    strLogErrorMsg.append(" could not be loaded. Make sure it is in the same location as ");
                    strLogErrorMsg.append(szThisModuleName);
                    strLogErrorMsg.append(".");
                    GPA_LogError(strLogErrorMsg.c_str());
                }

                AsicInfoList asicInfoList;
                AMDTADLUtils::Instance()->GetAsicInfoList(asicInfoList);

                for (AsicInfoList::iterator asicInfoIter = asicInfoList.begin(); asicInfoList.end() != asicInfoIter; ++asicInfoIter)
                {
                    if ((asicInfoIter->vendorID == vendorId) && (asicInfoIter->deviceID == deviceId))
                    {
                        pHwInfo->SetVendorID(asicInfoIter->vendorID);
                        pHwInfo->SetDeviceID(asicInfoIter->deviceID);
                        pHwInfo->SetRevisionID(asicInfoIter->revID);
                        pHwInfo->SetDeviceName(asicInfoIter->adapterName.c_str());
                        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_NONE);

                        GDT_HW_GENERATION hwGeneration;

                        if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(asicInfoIter->deviceID, hwGeneration))
                        {
                            pHwInfo->SetHWGeneration(hwGeneration);
                        }

                        break;
                    }
                }
            }
        }
    }

    return result;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        ID3D11Device* pDevice = static_cast<ID3D11Device*>(pContext);
        DXGI_ADAPTER_DESC adapterDesc;
        result = DXGetAdapterDesc(pDevice, adapterDesc);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Could not get adapter description, hardware cannot be supported.");
        }
        else
        {
            if (AMD_VENDOR_ID == adapterDesc.VendorId)
            {
                HMONITOR hMonitor = DXGetDeviceMonitor(pDevice);

                if (nullptr == hMonitor)
                {
                    GPA_LogError("Could not get device monitor description, hardware cannot be supported.");
                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                }
                else
                {
                    result = GetAmdHwInfo(pDevice, pHwInfo, hMonitor, adapterDesc.VendorId, adapterDesc.DeviceId);
                }
            }
            else if (NVIDIA_VENDOR_ID == adapterDesc.VendorId || INTEL_VENDOR_ID == adapterDesc.VendorId)
            {
                pHwInfo->SetVendorID(adapterDesc.VendorId);
                pHwInfo->SetDeviceID(adapterDesc.DeviceId);
                pHwInfo->SetRevisionID(adapterDesc.Revision);
                std::wstring adapterNameW(adapterDesc.Description);
                std::string adapterName(adapterNameW.begin(), adapterNameW.end());
                pHwInfo->SetDeviceName(adapterName.c_str());

                if (NVIDIA_VENDOR_ID == adapterDesc.VendorId)
                {
                    pHwInfo->SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
                }
                else if (INTEL_VENDOR_ID == adapterDesc.VendorId)
                {
                    pHwInfo->SetHWGeneration(GDT_HW_GENERATION_INTEL);
                }

                result = GPA_STATUS_OK;
            }
        }
    }

    return result;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        ID3D11Device* pDevice = static_cast<ID3D11Device*>(pContext);
        DXGI_ADAPTER_DESC adapterDesc;
        result = DXGetAdapterDesc(pDevice, adapterDesc);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Could not get adapter description, hardware cannot be supported.");
        }
        else
        {
            if (AMD_VENDOR_ID == adapterDesc.VendorId)
            {
                HMONITOR hMonitor = DXGetDeviceMonitor(pDevice);

                if (nullptr == hMonitor)
                {
                    GPA_LogError("Could not get device monitor description, hardware cannot be supported.");
                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                }
                else
                {
                    GPA_HWInfo amdHwInfo;
                    result = GetAmdHwInfo(pDevice, &amdHwInfo, hMonitor, adapterDesc.VendorId, adapterDesc.DeviceId);

                    if (GPA_STATUS_OK == result)
                    {
                        unsigned int deviceId;
                        pHwInfo->GetDeviceID(deviceId);
                        unsigned int amdDeviceId;
                        amdHwInfo.GetDeviceID(amdDeviceId);

                        if ((pHwInfo->IsAMD() == amdHwInfo.IsAMD()) && (deviceId == amdDeviceId))
                        {
                            result = GPA_STATUS_OK;
                        }
                        else
                        {
                            result = GPA_STATUS_ERROR_FAILED;
                        }
                    }
                }
            }
            else if (NVIDIA_VENDOR_ID == adapterDesc.VendorId)
            {
                result = GPA_STATUS_OK;
            }
        }
    }

    return result;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    // Get the current feature level in use by the application
    ID3D11DevicePtr pDevice = static_cast<ID3D11Device*>(pContext);
    D3D_FEATURE_LEVEL level = pDevice->GetFeatureLevel();

    // DX9 feature level is not supported
    if (level == D3D_FEATURE_LEVEL_9_1      ||
        level == D3D_FEATURE_LEVEL_9_2  ||
        level == D3D_FEATURE_LEVEL_9_3)
    {
        GPA_LogError("GPUPerfAPI does not support D3D_FEATURE_LEVEL_9_1, _9_2, and _9_3.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    if (nullptr == pHwInfo)
    {
        GPA_LogError("hardware info is null.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    GPA_Status status = GPACustomHwValidationManager::Instance()->ValidateHW(pContext, pHwInfo);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    gpa_uint64 freq = 0;

    if (queryTimeStampFrequency(pContext, freq))
    {
        pHwInfo->SetTimeStampFrequency(freq);
    }

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'ppNewContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateDX11* pContext = new(std::nothrow) GPA_ContextStateDX11;

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

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_Initialize()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
// Startup / exit
GPA_Status GPA_IMP_OpenContext(void* pContext)
{

    GDT_HW_GENERATION gen = GDT_HW_GENERATION_NONE;

    if (g_pCurrentContext->m_hwInfo.GetHWGeneration(gen) == false)
    {
        GPA_LogError("Unable to get current hardware generation.");
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 vendorId = 0;

    if (g_pCurrentContext->m_hwInfo.GetVendorID(vendorId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    unsigned int majorVer;
    unsigned int minorVer;
    unsigned int subMinorVer;
    ADLUtil_Result adlResult = AMDTADLUtils::Instance()->GetDriverVersion(majorVer, minorVer, subMinorVer);

    static const unsigned int MIN_MAJOR_VER = 16;
    static const unsigned int MIN_MINOR_VER_FOR_16 = 15;

    if (AMD_VENDOR_ID == vendorId  && (ADL_SUCCESS == adlResult || ADL_WARNING == adlResult))
    {
        if (majorVer < MIN_MAJOR_VER || (majorVer == MIN_MAJOR_VER && minorVer < MIN_MINOR_VER_FOR_16))
        {
            GPA_LogError("Driver version 16.15 or newer is required.");
            return GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
        }
    }

    ID3D11DevicePtr pDevice = static_cast<ID3D11Device*>(pContext);

    if (pDevice == nullptr)
    {
        GPA_LogError("Device is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }

    ID3D11DeviceContextPtr pDeviceContext = nullptr;
    pDevice->GetImmediateContext(&pDeviceContext);

    if (pDeviceContext == nullptr)
    {
        GPA_LogError("ImmediateContext is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }


    gpa_uint32 deviceId = 0;

    if (g_pCurrentContext->m_hwInfo.GetDeviceID(deviceId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 revisionId = 0;

    if (g_pCurrentContext->m_hwInfo.GetRevisionID(revisionId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    getCurrentContext()->SetDX11DeviceContext(pDeviceContext);

    return GenerateCounters(GPA_API_DIRECTX_11, vendorId, deviceId, revisionId, (GPA_ICounterAccessor**) & (g_pCurrentContext->m_pCounterAccessor), &(getCurrentContext()->m_pCounterScheduler));
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CloseContext()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_EndSession()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_BeginSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_EndSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);

    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_BeginSampleInSampleList(gpa_uint32 sampleID, void* pSampleList)
{
    UNREFERENCED_PARAMETER(sampleID);
    UNREFERENCED_PARAMETER(pSampleList);

    GPA_LogError("GPA_BeginSampleInSampleList is not supported. Use GPA_BeginSample instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_EndSampleInSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);

    GPA_LogError("GPA_EndSampleInSampleList is not supported. Use GPA_EndSample instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID)
{
    UNREFERENCED_PARAMETER(sampleID);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_EndSample()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    // reported maximum latency was 4 for r6xx cards
    // had issues with this value. Had to switch to 32
    return 32;
}

//-----------------------------------------------------------------------------
GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("No context available. Unable to create a data request.");
        return nullptr;
    }

    return new(std::nothrow) DX11CounterDataRequest();
}
