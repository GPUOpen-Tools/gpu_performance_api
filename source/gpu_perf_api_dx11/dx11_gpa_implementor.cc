//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Implementation
//==============================================================================

#include <locale>
#include <codecvt>

#include <ADLUtil.h>
#include "DeviceInfoUtils.h"
#include "../gpu_perf_api_dx/dx_utils.h"
#include "dx11_gpa_implementor.h"
#include "dx11_gpa_context.h"
#include "dx11_utils.h"
#include "dxx_ext_utils.h"
#include "utility.h"
#include "dx_get_amd_device_info.h"
#include "gpa_custom_hw_validation_manager.h"
#include "gpa_common_defs.h"
#include "gpa_counter_generator_dx11.h"
#include "gpa_counter_generator_dx11_non_amd.h"
#include "gpa_counter_scheduler_dx11.h"
#include "dx11_include.h"


IGPAImplementor* s_pGpaImp = DX11GPAImplementor::Instance();
static GPA_CounterGeneratorDX11       s_generatorDX11;        ///< static instance of DX11 generator
static GPA_CounterGeneratorDX11NonAMD s_generatorDX11NonAMD;  ///< static instance of DX11 non-AMD generator
static GPA_CounterSchedulerDX11       s_schedulerDX11;        ///< static instance of DX11 scheduler

GPA_API_Type DX11GPAImplementor::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

bool DX11GPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    bool isSuccess = false;

    IUnknown*     pUnknownPtr  = static_cast<IUnknown*>(pContextInfo);
    ID3D11Device* pD3D11Device = nullptr;

    if (DX11Utils::GetD3D11Device(pUnknownPtr, &pD3D11Device) && DX11Utils::IsFeatureLevelSupported(pD3D11Device))
    {
        DXGI_ADAPTER_DESC adapterDesc;
        GPA_Status        gpaStatus = DXGetAdapterDesc(pD3D11Device, adapterDesc);

        if (GPA_STATUS_OK == gpaStatus)
        {
            if (AMD_VENDOR_ID == adapterDesc.VendorId)
            {
                HMONITOR hMonitor = DXGetDeviceMonitor(pD3D11Device);

                if (nullptr != hMonitor)
                {
                    if (GetAmdHwInfo(pD3D11Device, hMonitor, adapterDesc.VendorId, adapterDesc.DeviceId, hwInfo))
                    {
                        isSuccess = true;
                    }
                    else
                    {
                        GPA_LogError("Unable to get hardware information.");
                    }
                }
                else
                {
                    GPA_LogError("Could not get device monitor description, hardware cannot be supported.");
                }
            }
            else if (NVIDIA_VENDOR_ID == adapterDesc.VendorId || INTEL_VENDOR_ID == adapterDesc.VendorId)
            {
                hwInfo.SetVendorID(adapterDesc.VendorId);
                hwInfo.SetDeviceID(adapterDesc.DeviceId);
                hwInfo.SetRevisionID(adapterDesc.Revision);
                std::wstring adapterNameW(adapterDesc.Description);

                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToUtf8Converter;

                std::string adapterName = wideToUtf8Converter.to_bytes(adapterNameW);

                hwInfo.SetDeviceName(adapterName.c_str());

                if (NVIDIA_VENDOR_ID == adapterDesc.VendorId)
                {
                    hwInfo.SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
                }
                else if (INTEL_VENDOR_ID == adapterDesc.VendorId)
                {
                    hwInfo.SetHWGeneration(GDT_HW_GENERATION_INTEL);
                }

                isSuccess = true;
            }
            else
            {
                std::stringstream ss;
                ss << "Unknown device adapter (vendorid=" << adapterDesc.VendorId << ", deviceid=" << adapterDesc.DeviceId
                   << ", revision=" << adapterDesc.Revision << ").";
                GPA_LogError(ss.str().c_str());
            }
        }
        else
        {
            GPA_LogError("Unable to get adapter information.");
        }
    }
    else
    {
        GPA_LogError("Unable to get device or either device feature level is not supported.");
    }

    return isSuccess;
}

bool DX11GPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    bool isSupported = false;

    IUnknown*     pUnknownPtr  = static_cast<IUnknown*>(pContextInfo);
    ID3D11Device* pD3D11Device = nullptr;

    if (DX11Utils::GetD3D11Device(pUnknownPtr, &pD3D11Device) && DX11Utils::IsFeatureLevelSupported(pD3D11Device))
    {
        GPA_Status status = GPA_STATUS_OK;

        if (hwInfo.IsAMD())
        {
            unsigned int   majorVer    = 0;
            unsigned int   minorVer    = 0;
            unsigned int   subMinorVer = 0;
            ADLUtil_Result adlResult   = AMDTADLUtils::Instance()->GetDriverVersion(majorVer, minorVer, subMinorVer);

            static const unsigned int MIN_MAJOR_VER        = 16;
            static const unsigned int MIN_MINOR_VER_FOR_16 = 15;

            if ((ADL_SUCCESS == adlResult || ADL_WARNING == adlResult))
            {
                if (majorVer < MIN_MAJOR_VER || (majorVer == MIN_MAJOR_VER && minorVer < MIN_MINOR_VER_FOR_16))
                {
                    GPA_LogError("Driver version 16.15 or newer is required.");

                    if (0 != majorVer || 0 != minorVer || 0 != subMinorVer)
                    {
                        // This is an error
                        status = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
                    }
                    else
                    {
                        // This is a warning due to an unsigned driver
                    }
                }
            }
        }
        else
        {
            GPA_HWInfo tempHwInfo = hwInfo;
            status                = GPACustomHwValidationManager::Instance()->ValidateHW(pContextInfo, &tempHwInfo);
        }

        if (GPA_STATUS_OK == status)
        {
            isSupported = true;
        }
    }

    return isSupported;
}

IGPAContext* DX11GPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    IUnknown*     pUnknownPtr = static_cast<IUnknown*>(pContextInfo);
    ID3D11Device* pD3D11Device;
    IGPAContext*  pRetGpaContext = nullptr;

    if (DX11Utils::GetD3D11Device(pUnknownPtr, &pD3D11Device) && DX11Utils::IsFeatureLevelSupported(pD3D11Device))
    {
        DX11GPAContext* pDX11GpaContext = new (std::nothrow) DX11GPAContext(pD3D11Device, hwInfo, flags);

        if (nullptr != pDX11GpaContext)
        {
            if (pDX11GpaContext->Initialize())
            {
                pRetGpaContext = pDX11GpaContext;
            }
            else
            {
                delete pDX11GpaContext;
                GPA_LogError("Unable to open a context.");
            }
        }
    }
    else
    {
        GPA_LogError("Hardware Not Supported.");
    }

    return pRetGpaContext;
}

bool DX11GPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(pDeviceIdentifier);
    assert(pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<DX11GPAContext*>(pContext);
        pContext = nullptr;
    }

    return (nullptr == pContext) && (nullptr != pDeviceIdentifier);
}

PFNAmdDxExtCreate11 DX11GPAImplementor::GetAmdExtFuncPointer() const
{
    return m_amdDxExtCreate11FuncPtr;
}

bool DX11GPAImplementor::GetAmdHwInfo(ID3D11Device* pD3D11Device,
                                      HMONITOR      hMonitor,
                                      const int&    primaryVendorId,
                                      const int&    primaryDeviceId,
                                      GPA_HWInfo&   hwInfo) const
{
    bool success = false;

    if (InitializeAmdExtFunction())
    {
        PFNAmdDxExtCreate11 AmdDxExtCreate11 = m_amdDxExtCreate11FuncPtr;

        if (nullptr != AmdDxExtCreate11)
        {
            IAmdDxExt*            pExt            = nullptr;
            IAmdDxExtPerfProfile* pExtPerfProfile = nullptr;
            HRESULT               hr              = AmdDxExtCreate11(pD3D11Device, &pExt);

            if (SUCCEEDED(hr))
            {
                unsigned int gpuIndex = 0;

                if (DxxExtUtils::IsMgpuPerfExtSupported(pExt))
                {
                    pExtPerfProfile = reinterpret_cast<IAmdDxExtPerfProfile*>(pExt->GetExtInterface(AmdDxExtPerfProfileID));

                    if (nullptr == pExtPerfProfile)
                    {
                        // only fail here if the primary device is a device that is supposed to support the PerfProfile extension.
                        // Pre-GCN devices do not support this extension (they use the counter interface exposed by the API).
                        // By not returning a failure here on older devices, the caller code will do the right thing on those devices.
                        GDT_HW_GENERATION generation;

                        if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(primaryDeviceId, generation) &&
                            generation >= GDT_HW_GENERATION_SOUTHERNISLAND)
                        {
                            GPA_LogError("Unable to get perf counter extension for GCN device.");
                        }
                    }
                    else
                    {
                        PE_RESULT peResult       = PE_OK;
                        BOOL      gpuProfileable = FALSE;

                        while ((PE_OK == peResult) && (FALSE == gpuProfileable))
                        {
                            peResult = pExtPerfProfile->IsGpuProfileable(gpuIndex, &gpuProfileable);
                            gpuIndex++;
                        }

                        if (FALSE == gpuProfileable)
                        {
                            GPA_LogError("No profilable GPU device available.");
                        }
                        else
                        {
                            --gpuIndex;  // gpu is over incremented in the loop above
                        }
                    }
                }

                hwInfo.SetGpuIndex(static_cast<unsigned int>(gpuIndex));

                std::string strDLLName;

                if (GPAUtil::GetCurrentModulePath(strDLLName))
                {
                    int vendorId = primaryVendorId;
                    int deviceId = primaryDeviceId;

                    std::string dllName("GPUPerfAPIDXGetAMDDeviceInfo");

                    strDLLName.append(dllName);
#ifdef X64
                    strDLLName.append("-x64");
#endif

                    HMODULE hModule = 0;
#ifdef _DEBUG
                    // Attempt to load the debug version of the DLL if it exists
                    {
                        std::string debugDllName(strDLLName);
                        debugDllName.append("-d");
                        debugDllName.append(".dll");
                        hModule = LoadLibraryA(debugDllName.c_str());
                    }
#endif

                    if (nullptr == hModule)
                    {
                        strDLLName.append(".dll");
                        hModule = LoadLibraryA(strDLLName.c_str());
                    }

                    if (nullptr != hModule)
                    {
                        static const char*                    pEntryPointName = "DXGetAMDDeviceInfo";
                        typedef decltype(DXGetAMDDeviceInfo)* DXGetAMDDeviceInfo_FuncType;
                        DXGetAMDDeviceInfo_FuncType           DXGetAMDDeviceInfoFunc =
                            reinterpret_cast<DXGetAMDDeviceInfo_FuncType>(GetProcAddress(hModule, pEntryPointName));

                        if (nullptr != DXGetAMDDeviceInfoFunc)
                        {
                            // NOTE: DXGetAMDDeviceInfo is failing on system with Baffin and Fiji system, driver version Radeon Software Version 17.12.2
                            // Previous Implementation of the DX11 GPA was also not relying on it successful operation.
                            // TODO: Track down why AMD extension function under DXGetAMDDeviceInfo is failing
                            DXGetAMDDeviceInfoFunc(hMonitor, vendorId, deviceId);
                        }
                        else
                        {
                            std::string strLogErrorMsg = "Entry point '";
                            strLogErrorMsg.append(pEntryPointName);
                            strLogErrorMsg.append("' could not be found in ");
                            strLogErrorMsg.append(strDLLName);
                            strLogErrorMsg.append(".");
                            GPA_LogError(strLogErrorMsg.c_str());
                        }
                    }
                    else
                    {
                        GPA_LogError("Unable to load the get device info dll.");
                    }

                    AsicInfoList asicInfoList;
                    AMDTADLUtils::Instance()->GetAsicInfoList(asicInfoList);

                    for (AsicInfoList::iterator asicInfoIter = asicInfoList.begin(); asicInfoList.end() != asicInfoIter; ++asicInfoIter)
                    {
                        if ((asicInfoIter->vendorID == vendorId) && (asicInfoIter->deviceID == deviceId))
                        {
                            hwInfo.SetVendorID(asicInfoIter->vendorID);
                            hwInfo.SetDeviceID(asicInfoIter->deviceID);
                            hwInfo.SetRevisionID(asicInfoIter->revID);
                            hwInfo.SetDeviceName(asicInfoIter->adapterName.c_str());
                            hwInfo.SetHWGeneration(GDT_HW_GENERATION_NONE);

                            GDT_HW_GENERATION hwGeneration;

                            if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(asicInfoIter->deviceID, hwGeneration))
                            {
                                hwInfo.SetHWGeneration(hwGeneration);
                                UINT64 deviceFrequency = 0ull;
                                if (!DX11Utils::GetTimestampFrequency(pD3D11Device, deviceFrequency))
                                {
                                    GPA_LogError("GetTimestampFrequency failed");

                                    if (nullptr != pExtPerfProfile)
                                    {
                                        pExtPerfProfile->Release();
                                    }

                                    if (nullptr != pExt)
                                    {
                                        pExt->Release();
                                    }

                                    return false;
                                }
                                hwInfo.SetTimeStampFrequency(deviceFrequency);
                            }

                            unsigned int   majorVer    = 0;
                            unsigned int   minorVer    = 0;
                            unsigned int   subMinorVer = 0;
                            ADLUtil_Result adlResult   = AMDTADLUtils::Instance()->GetDriverVersion(majorVer, minorVer, subMinorVer);

                            static const unsigned int MIN_MAJOR_VER        = 19;
                            static const unsigned int MIN_MINOR_VER_FOR_30 = 30;

                            if ((ADL_SUCCESS == adlResult || ADL_WARNING == adlResult))
                            {
                                if (majorVer >= MIN_MAJOR_VER && minorVer >= MIN_MINOR_VER_FOR_30)
                                {
                                    if (nullptr != pExt)
                                    {
                                        IAmdDxExtASICInfo* pExtAsicInfo = reinterpret_cast<IAmdDxExtASICInfo*>(pExt->GetExtInterface(AmdDxExtASICInfoID));

                                        if (nullptr != pExtAsicInfo)
                                        {
                                            AmdDxASICInfoParam infoParam    = {};
                                            AmdDxASICInfo*     pNewAsicInfo = new (std::nothrow) AmdDxASICInfo();

                                            if (nullptr != pNewAsicInfo)
                                            {
                                                infoParam.pASICInfo = pNewAsicInfo;
                                                pExtAsicInfo->GetInfoData(&infoParam);

                                                if (nullptr != infoParam.pASICInfo && gpuIndex < infoParam.pASICInfo->gpuCount)
                                                {
                                                    AmdDxASICInfoHWInfo asicInfo = infoParam.pASICInfo->hwInfo[gpuIndex];
                                                    hwInfo.SetNumberCUs(asicInfo.totalCU);
                                                    hwInfo.SetNumberShaderEngines(asicInfo.numShaderEngines);
                                                    hwInfo.SetNumberShaderArrays(asicInfo.numShaderArraysPerSE);
                                                    hwInfo.SetNumberSIMDs(asicInfo.totalCU * asicInfo.numSimdsPerCU);
                                                }

                                                delete pNewAsicInfo;
                                            }

                                            pExtAsicInfo->Release();
                                        }
                                    }
                                }
                            }

                            success = true;
                            break;
                        }
                    }
                }
                else
                {
                    GPA_LogError("Unable to get the module path.");
                }

                if (nullptr != pExtPerfProfile)
                {
                    pExtPerfProfile->Release();
                }

                if (nullptr != pExt)
                {
                    pExt->Release();
                }
            }
            else
            {
                GPA_LogError("Unable to create DX11 extension.");
            }
        }
        else
        {
            GPA_LogError("Unable to initialize because extension creation is not available.");
        }
    }
    else
    {
#ifdef X64
        GPA_LogError("Unable to initialize because 'atidxx64.dll' is not available.");
#else
        GPA_LogError("Unable to initialize because 'atidxx32.dll' is not available.");
#endif
    }

    return success;
}

DX11GPAImplementor::DX11GPAImplementor()
    : m_amdDxExtCreate11FuncPtr(nullptr)
{
}

bool DX11GPAImplementor::InitializeAmdExtFunction() const
{
    bool success = false;

    if (nullptr == m_amdDxExtCreate11FuncPtr)
    {
        HMODULE hDxxDll = nullptr;

#ifdef X64
        hDxxDll = ::GetModuleHandleW(L"atidxx64.dll");
#else
        hDxxDll = ::GetModuleHandleW(L"atidxx32.dll");
#endif

        if (nullptr != hDxxDll)
        {
            PFNAmdDxExtCreate11 AmdDxExtCreate11 = reinterpret_cast<PFNAmdDxExtCreate11>(GetProcAddress(hDxxDll, "AmdDxExtCreate11"));

            if (nullptr != AmdDxExtCreate11)
            {
                m_amdDxExtCreate11FuncPtr = AmdDxExtCreate11;
                success                   = true;
            }
        }
    }
    else
    {
        success = true;
    }

    return success;
}

GPADeviceIdentifier DX11GPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return static_cast<IUnknown*>(pContextInfo);
}
