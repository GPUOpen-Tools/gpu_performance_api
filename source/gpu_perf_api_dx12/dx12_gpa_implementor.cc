//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_implementor.h"

#include <locale>
#include <codecvt>

#include "DeviceInfoUtils.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_non_amd.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx12.h"

#include "gpu_perf_api_dx12/dx12_utils.h"

IGpaImplementor*                     gpa_imp = Dx12GpaImplementor::Instance();
static GpaCounterGeneratorDx12       counter_generator_dx12;          ///< Static instance of DX12 generator.
static GpaCounterGeneratorDx12NonAmd counter_generator_dx12_non_amd;  ///< Static instance of DX12 non-AMD generator.
static GpaCounterSchedulerDx12       counter_scheduler_dx12;          ///< Static instance of DX12 scheduler.

Dx12GpaImplementor::~Dx12GpaImplementor()
{
    Dx12GpaImplementor::Destroy();
}

GpaApiType Dx12GpaImplementor::GetApiType() const
{
    return kGpaApiDirectx12;
}

bool Dx12GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const
{
    bool success = false;

    IUnknown*     unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D12Device* d3d12_device;

    if (dx12_utils::GetD3D12Device(unknown_ptr, &d3d12_device) && dx12_utils::IsFeatureLevelSupported(d3d12_device))
    {
        DXGI_ADAPTER_DESC adapter_desc;
        GpaStatus         result = dx12_utils::Dx12GetAdapterDesc(d3d12_device, adapter_desc);

        if (kGpaStatusOk == result)
        {
            // For now it is assumed that DX12 MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use DX12 MGPU extension (and possibly ADL util)
            // to get the correct HW info
            hw_info.SetVendorId(adapter_desc.VendorId);
            hw_info.SetDeviceId(adapter_desc.DeviceId);
            hw_info.SetRevisionId(adapter_desc.Revision);
            std::wstring adapter_name_wide_string(adapter_desc.Description);

            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wide_to_utf8_converter;

            std::string adapter_name = wide_to_utf8_converter.to_bytes(adapter_name_wide_string);

            hw_info.SetDeviceName(adapter_name.c_str());
            GDT_HW_GENERATION hw_gen = GDT_HW_GENERATION_NONE;

            if (kNvidiaVendorId == adapter_desc.VendorId)
            {
                hw_gen = GDT_HW_GENERATION_NVIDIA;
            }
            else if (kIntelVendorId == adapter_desc.VendorId)
            {
                hw_gen = GDT_HW_GENERATION_INTEL;
            }
            else if (kAmdVendorId == adapter_desc.VendorId)
            {
                GDT_GfxCardInfo card_info;

                if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(adapter_desc.DeviceId, adapter_desc.Revision, card_info))
                {
                    hw_gen = card_info.m_generation;

                    // GPA DX12 requires GFX8 or above (but also works on Hawaii).
                    if (GDT_HW_GENERATION_VOLCANICISLAND > hw_gen && GDT_HAWAII != card_info.m_asicType)
                    {
                        GPA_LOG_ERROR("Hardware not supported.");
                    }
                    else
                    {
                        UINT64 device_frequency = 0ull;
                        if (!dx12_utils::GetTimestampFrequency(d3d12_device, device_frequency))
                        {
                            GPA_LOG_ERROR("GetTimestampFrequency Failed");
                        }
                        else
                        {
                            hw_info.SetTimeStampFrequency(device_frequency);
                            success = true;
                        }
                    }
                }
            }

            hw_info.SetHwGeneration(hw_gen);
        }
    }

    return success;
}

bool Dx12GpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(hw_info);

    bool success = false;

    IUnknown*     unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D12Device* d3d12_device;

    if (dx12_utils::GetD3D12Device(unknown_ptr, &d3d12_device) && dx12_utils::IsFeatureLevelSupported(d3d12_device))
    {
        success = true;
    }

    return success;
}

GpaStatus Dx12GpaImplementor::Destroy()
{
    DeleteContexts();
    return GpaImplementor::Destroy();
}

bool Dx12GpaImplementor::IsCommandListRequired() const
{
    return true;
}

bool Dx12GpaImplementor::IsContinueSampleOnCommandListSupported() const
{
    return true;
}

bool Dx12GpaImplementor::IsCopySecondarySampleSupported() const
{
    return true;
}

IGpaContext* Dx12GpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    IUnknown*     unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D12Device* d3d12_device;
    IGpaContext*  ret_gpa_context = nullptr;

    if (dx12_utils::GetD3D12Device(unknown_ptr, &d3d12_device) && dx12_utils::IsFeatureLevelSupported(d3d12_device))
    {
        Dx12GpaContext* dx12_gpa_context = new (std::nothrow) Dx12GpaContext(d3d12_device, hw_info, flags);

        if (nullptr != dx12_gpa_context)
        {
            if (dx12_gpa_context->Initialize())
            {
                ret_gpa_context = dx12_gpa_context;
            }
            else
            {
                delete dx12_gpa_context;
                GPA_LOG_ERROR("Unable to open a context.");
            }
        }
    }
    else
    {
        GPA_LOG_ERROR("Hardware Not Supported.");
    }

    return ret_gpa_context;
}

bool Dx12GpaImplementor::CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context)
{
    assert(device_identifier);
    assert(context);

    UNREFERENCED_PARAMETER(device_identifier);
    UNREFERENCED_PARAMETER(context);

    if (nullptr != context)
    {
        Dx12GpaContext* dx12_gpa_context = reinterpret_cast<Dx12GpaContext*>(context);

        // Deleting the context resources at this point is causing
        // some issue in driver as some of the resources are still in use on factory object
        // We will defer the release of driver extension resources at time of destroying the GPA
        dx12_gpa_context->SetStableClocks(false);
        dx12_gpa_context_list_.push_back(dx12_gpa_context);
    }

    return true;
}

GpaDeviceIdentifier Dx12GpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return static_cast<IUnknown*>(context_info);
}

void Dx12GpaImplementor::DeleteContexts()
{
    for (Dx12GpaContext* temp_context : dx12_gpa_context_list_)
    {
        delete temp_context;
    }

    dx12_gpa_context_list_.clear();
}
