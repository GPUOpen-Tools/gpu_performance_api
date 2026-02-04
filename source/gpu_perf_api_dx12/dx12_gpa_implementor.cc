//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_implementor.h"

#include <locale>
#include <codecvt>

#include <DeviceInfoUtils.h>

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx12.h"

#include "gpu_perf_api_dx12/dx12_utils.h"

static GpaCounterGeneratorDx12* counter_generator_dx12 = nullptr;  ///< Static instance of DX12 generator.
static GpaCounterSchedulerDx12* counter_scheduler_dx12 = nullptr;  ///< Static instance of DX12 scheduler.

static GpaCounterGeneratorDx12* generator_dx12_streaming = nullptr;  ///< Static instance of DX12 generator.
static GpaCounterSchedulerDx12* scheduler_dx12_streaming = nullptr;  ///< Static instance of DX12 scheduler.

IGpaImplementor* CreateImplementor()
{
    counter_generator_dx12 = new GpaCounterGeneratorDx12(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_dx12 = new GpaCounterSchedulerDx12(kGpaSessionSampleTypeDiscreteCounter);

    generator_dx12_streaming = new GpaCounterGeneratorDx12(kGpaSessionSampleTypeStreamingCounter);
    scheduler_dx12_streaming = new GpaCounterSchedulerDx12(kGpaSessionSampleTypeStreamingCounter);

    return Dx12GpaImplementor::Instance();
}

void DestroyImplementor(IGpaImplementor* impl)
{
    if (counter_generator_dx12 != nullptr)
    {
        delete counter_generator_dx12;
        counter_generator_dx12 = nullptr;
    }

    if (counter_scheduler_dx12 != nullptr)
    {
        delete counter_scheduler_dx12;
        counter_scheduler_dx12 = nullptr;
    }

    if (generator_dx12_streaming != nullptr)
    {
        delete generator_dx12_streaming;
        generator_dx12_streaming = nullptr;
    }

    if (scheduler_dx12_streaming != nullptr)
    {
        delete scheduler_dx12_streaming;
        scheduler_dx12_streaming = nullptr;
    }

    if (nullptr != impl)
    {
        Dx12GpaImplementor::DeleteInstance();
    }
}

GpaStatus Dx12GpaImplementor::Initialize(GpaInitializeFlags flags)
{
    GpaStatus status = GpaImplementor::Initialize(flags);
    return status;
}

/// @brief Converts string from wide to utf-8 encoding.
///
/// @return The converted utf-8 encoded string.
static std::string wide_to_utf8_converter(const std::wstring& wide)
{
    int         num_bytes_needed = WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), nullptr, 0, nullptr, nullptr);
    std::string utf8;
    utf8.resize(num_bytes_needed);
    WideCharToMultiByte(CP_UTF8, 0, wide.data(), (int)wide.size(), utf8.data(), num_bytes_needed, nullptr, nullptr);
    return utf8;
}

Dx12GpaImplementor::~Dx12GpaImplementor()
{
    Dx12GpaImplementor::Destroy();
}

GpaApiType Dx12GpaImplementor::GetApiType() const
{
    return kGpaApiDirectx12;
}

bool Dx12GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);

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
            // we will need to use DX12 MGPU extension to get the correct HW info
            hw_info.SetVendorId(adapter_desc.VendorId);
            hw_info.SetDeviceId(adapter_desc.DeviceId);
            hw_info.SetRevisionId(adapter_desc.Revision);
            std::wstring adapter_name_wide_string(adapter_desc.Description);

            std::string adapter_name = wide_to_utf8_converter(adapter_name_wide_string);

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

                if (AMDTDeviceInfoUtils::GetDeviceInfo(adapter_desc.DeviceId, adapter_desc.Revision, card_info))
                {
                    hw_gen = card_info.m_generation;

                    // GPA DX12 requires GFX10.
                    if (GDT_HW_GENERATION_GFX10 > hw_gen)
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

bool Dx12GpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);
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

IGpaContext* Dx12GpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
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

bool Dx12GpaImplementor::CloseApiContext(IGpaContext* context)
{
    assert(context);

    GpaStatus set_default_clocks_result = kGpaStatusOk;

    if (nullptr != context)
    {
        Dx12GpaContext* dx12_gpa_context = reinterpret_cast<Dx12GpaContext*>(context);
        set_default_clocks_result        = dx12_gpa_context->SetStableClocks(false);
        if (set_default_clocks_result != kGpaStatusOk)
        {
            assert(!"Unable to set clocks back to default");
            GPA_LOG_ERROR("Unable to set clocks back to default");
        }

        delete dx12_gpa_context;
    }

    return set_default_clocks_result == kGpaStatusOk;
}

GpaDeviceIdentifier Dx12GpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return static_cast<IUnknown*>(context_info);
}
