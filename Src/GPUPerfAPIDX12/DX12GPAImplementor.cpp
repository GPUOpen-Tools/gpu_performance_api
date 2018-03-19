//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 GPA Implementation
//==============================================================================

#include "DX12GPAImplementor.h"
#include "DX12GPAContext.h"
#include "DX12Utils.h"
#include "DeviceInfoUtils.h"

IGPAImplementor* s_pGpaImp = DX12GPAImplementor::Instance();

GPA_API_Type DX12GPAImplementor::GetAPIType() const
{
    return GPA_API_DIRECTX_12;
}

bool DX12GPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    bool success = false;

    IUnknown* pUnknownPtr = static_cast<IUnknown*>(pContextInfo);
    ID3D12Device* pD3D12Device;

    if (DX12Utils::GetD3D12Device(pUnknownPtr, &pD3D12Device) && DX12Utils::IsFeatureLevelSupported(pD3D12Device))
    {
        DXGI_ADAPTER_DESC adapterDesc;
        GPA_Status result = DX12Utils::DX12GetAdapterDesc(pD3D12Device, adapterDesc);

        if (GPA_STATUS_OK == result)
        {
            // For now it is assumed that DX12 MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use DX12 MGPU extension (and possibly ADL util)
            // to get the correct HW info
            hwInfo.SetVendorID(adapterDesc.VendorId);
            hwInfo.SetDeviceID(adapterDesc.DeviceId);
            hwInfo.SetRevisionID(adapterDesc.Revision);
            std::wstring adapterNameW(adapterDesc.Description);
            std::string adapterName(adapterNameW.begin(), adapterNameW.end());
            hwInfo.SetDeviceName(adapterName.c_str());
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
                        GPA_LogError("Hardware not supported.");
                    }
                    else
                    {
                        UINT64 deviceFrequency = 0ull;
                        GPA_ASSERT(DX12Utils::GetTimestampFrequency(pD3D12Device, deviceFrequency));
                        hwInfo.SetTimeStampFrequency(deviceFrequency);
                        success = true;
                    }
                }
            }

            hwInfo.SetHWGeneration(hwGen);
        }
    }

    return success;
}

bool DX12GPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(hwInfo);

    bool success = false;

    IUnknown* pUnknownPtr = static_cast<IUnknown*>(pContextInfo);
    ID3D12Device* pD3D12Device;

    if (DX12Utils::GetD3D12Device(pUnknownPtr, &pD3D12Device) &&
        DX12Utils::IsFeatureLevelSupported(pD3D12Device))
    {
        success = true;
    }

    return success;
}

IGPAContext* DX12GPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    IUnknown* pUnknownPtr = static_cast<IUnknown*>(pContextInfo);
    ID3D12Device* pD3D12Device;
    IGPAContext* pRetGpaContext = nullptr;

    if (DX12Utils::GetD3D12Device(pUnknownPtr, &pD3D12Device) &&
        DX12Utils::IsFeatureLevelSupported(pD3D12Device))
    {
        DX12GPAContext* pDX12GpaContext = new(std::nothrow) DX12GPAContext(pD3D12Device, hwInfo, flags);

        if (nullptr != pDX12GpaContext)
        {
            if (pDX12GpaContext->Initialize())
            {
                pRetGpaContext = pDX12GpaContext;
            }
            else
            {
                delete pDX12GpaContext;
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

bool DX12GPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(pDeviceIdentifier);
    assert(pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<DX12GPAContext*>(pContext);
    }

    return (nullptr != pContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier DX12GPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return static_cast<IUnknown*>(pContextInfo);
}
