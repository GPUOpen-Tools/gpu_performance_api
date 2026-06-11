//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_implementor.h"

#include <locale>
#include <codecvt>
#include <memory>

#include "device_info.hpp"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx12.h"

#include "gpu_perf_api_dx12/dx12_utils.h"

namespace
{
    std::unique_ptr<GpaCounterGeneratorDx12> counter_generator_dx12;    ///< Static instance of DX12 generator.
    std::unique_ptr<GpaCounterSchedulerDx12> counter_scheduler_dx12;    ///< Static instance of DX12 scheduler.
    std::unique_ptr<GpaCounterGeneratorDx12> generator_dx12_streaming;  ///< Static instance of DX12 generator.
    std::unique_ptr<GpaCounterSchedulerDx12> scheduler_dx12_streaming;  ///< Static instance of DX12 scheduler.
}  // namespace

IGpaImplementor& CreateImplementor()
{
    counter_generator_dx12 = std::make_unique<GpaCounterGeneratorDx12>(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_dx12 = std::make_unique<GpaCounterSchedulerDx12>(kGpaSessionSampleTypeDiscreteCounter);

    generator_dx12_streaming = std::make_unique<GpaCounterGeneratorDx12>(kGpaSessionSampleTypeStreamingCounter);
    scheduler_dx12_streaming = std::make_unique<GpaCounterSchedulerDx12>(kGpaSessionSampleTypeStreamingCounter);

    return Dx12GpaImplementor::Instance();
}

void DestroyImplementor()
{
    counter_generator_dx12.reset();
    counter_scheduler_dx12.reset();
    generator_dx12_streaming.reset();
    scheduler_dx12_streaming.reset();
}

GpaStatus Dx12GpaImplementor::Initialize(GpaInitializeFlags flags)
{
    GpaStatus status = GpaImplementor::Initialize(flags);
    return status;
}

GpaStatus Dx12GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);

    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

    IUnknown*     unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D12Device* d3d12_device;

    if (dx12_utils::GetD3D12Device(unknown_ptr, &d3d12_device) && dx12_utils::IsFeatureLevelSupported(d3d12_device))
    {
        DXGI_ADAPTER_DESC adapter_desc;
        GpaStatus         result = dx12_utils::Dx12GetAdapterDesc(d3d12_device, adapter_desc);

        if (kGpaStatusOk == result)
        {
            const std::wstring adapter_name_wide_string(adapter_desc.Description);
            const std::string  adapter_name = gpa_util::ConvertToStdString(adapter_name_wide_string);

            hw_info.SetDeviceName(adapter_name.c_str());

            // For now it is assumed that DX12 MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use DX12 MGPU extension to get the correct HW info
            hw_info.SetVendorId(adapter_desc.VendorId);
            hw_info.SetDeviceId(adapter_desc.DeviceId);
            hw_info.SetRevisionId(adapter_desc.Revision);

            if (const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(hw_info.GetDeviceDescription().value()); card_info.has_value())
            {
                hw_info.SetHwGeneration(card_info->generation);

                UINT64 device_frequency = 0ull;
                if (!dx12_utils::GetTimestampFrequency(d3d12_device, device_frequency))
                {
                    GpaLogger::Instance().LogError("GetTimestampFrequency Failed");
                }
                else
                {
                    hw_info.SetTimeStampFrequency(device_frequency);
                    status = kGpaStatusOk;
                }
            }
            else
            {
                GpaLogger::Instance().LogError("Unable to get device info from device_info library.");
            }
        }
    }

    return status;
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

std::unique_ptr<IGpaContext> Dx12GpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    IUnknown*                    unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D12Device*                d3d12_device;
    std::unique_ptr<IGpaContext> ret_gpa_context;

    if (dx12_utils::GetD3D12Device(unknown_ptr, &d3d12_device) && dx12_utils::IsFeatureLevelSupported(d3d12_device))
    {
        auto dx12_gpa_context = std::make_unique<Dx12GpaContext>(d3d12_device, hw_info, flags);

        if (dx12_gpa_context->Initialize())
        {
            ret_gpa_context = std::move(dx12_gpa_context);
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to open a context.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Hardware Not Supported.");
    }

    return ret_gpa_context;
}

bool Dx12GpaImplementor::CloseApiContext(std::unique_ptr<IGpaContext> context)
{
    assert(context);

    Dx12GpaContext* dx12_gpa_context          = reinterpret_cast<Dx12GpaContext*>(context.get());
    const GpaStatus set_default_clocks_result = dx12_gpa_context->SetStableClocks(false);
    if (set_default_clocks_result != kGpaStatusOk)
    {
        assert(!"Unable to set clocks back to default");
        GpaLogger::Instance().LogError("Unable to set clocks back to default");
    }

    // context destroyed when unique_ptr goes out of scope.

    return set_default_clocks_result == kGpaStatusOk;
}

GpaDeviceIdentifier Dx12GpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return static_cast<IUnknown*>(context_info);
}
