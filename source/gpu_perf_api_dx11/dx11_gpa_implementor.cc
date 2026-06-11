//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Implementation
//==============================================================================

#include <locale>
#include <codecvt>
#include <memory>

#include "device_info.hpp"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/utility.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx11.h"

#include "gpu_perf_api_dx/dx_utils.h"

#include "gpu_perf_api_dx11/dx11_gpa_context.h"
#include "gpu_perf_api_dx11/dx11_gpa_implementor.h"
#include "gpu_perf_api_dx11/dx11_include.h"
#include "gpu_perf_api_dx11/dx11_utils.h"
#include "gpu_perf_api_dx11/dxx_ext_utils.h"

namespace
{
    std::unique_ptr<GpaCounterGeneratorDx11> counter_generator_dx11;  ///< Static instance of DX11 generator.
    std::unique_ptr<GpaCounterSchedulerDx11> counter_scheduler_dx11;  ///< Static instance of DX11 scheduler.
}  // namespace

IGpaImplementor& CreateImplementor()
{
    counter_generator_dx11 = std::make_unique<GpaCounterGeneratorDx11>(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_dx11 = std::make_unique<GpaCounterSchedulerDx11>(kGpaSessionSampleTypeDiscreteCounter);
    return Dx11GpaImplementor::Instance();
}

void DestroyImplementor()
{
    counter_generator_dx11.reset();
    counter_scheduler_dx11.reset();
}

GpaStatus Dx11GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);

    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

    IUnknown*     unknown_ptr  = static_cast<IUnknown*>(context_info);
    ID3D11Device* d3d11_device = nullptr;

    if (dx11_utils::GetD3D11Device(unknown_ptr, &d3d11_device) && dx11_utils::IsFeatureLevelSupported(d3d11_device))
    {
        DXGI_ADAPTER_DESC adapter_desc;
        GpaStatus         gpa_status = DxGetAdapterDesc(d3d11_device, adapter_desc);

        if (InitializeAmdExtFunction() == false)
        {
            GpaLogger::Instance().LogError("Unable to initialize AMD DX11 extensions.");
            gpa_status = kGpaStatusErrorFailed;
        }

        if (kGpaStatusOk == gpa_status)
        {
            const std::wstring adapter_name_wide_string(adapter_desc.Description);
            const std::string  adapter_name = gpa_util::ConvertToStdString(adapter_name_wide_string);

            hw_info.SetDeviceName(adapter_name.c_str());

            // For now it is assumed that DX11 MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use DX11 MGPU extension to get the correct HW info
            hw_info.SetVendorId(adapter_desc.VendorId);
            hw_info.SetDeviceId(adapter_desc.DeviceId);
            hw_info.SetRevisionId(adapter_desc.Revision);

            if (const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(hw_info.GetDeviceDescription().value()); card_info.has_value())
            {
                hw_info.SetHwGeneration(card_info->generation);

                UINT64 device_frequency = 0ull;
                if (!dx11_utils::GetTimestampFrequency(d3d11_device, device_frequency))
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
        else
        {
            GpaLogger::Instance().LogError("Unable to get adapter information.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to get device or either device feature level is not supported.");
    }

    return status;
}

bool Dx11GpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(hw_info);

    bool is_supported = false;

    IUnknown*     unknown_ptr  = static_cast<IUnknown*>(context_info);
    ID3D11Device* d3d11_device = nullptr;

    if (dx11_utils::GetD3D11Device(unknown_ptr, &d3d11_device) && dx11_utils::IsFeatureLevelSupported(d3d11_device))
    {
        is_supported = true;
    }

    return is_supported;
}

std::unique_ptr<IGpaContext> Dx11GpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    IUnknown*                    unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D11Device*                d3d11_device;
    std::unique_ptr<IGpaContext> ret_gpa_context;

    if (dx11_utils::GetD3D11Device(unknown_ptr, &d3d11_device) && dx11_utils::IsFeatureLevelSupported(d3d11_device))
    {
        auto dx11_gpa_context = std::make_unique<Dx11GpaContext>(d3d11_device, hw_info, flags);

        if (dx11_gpa_context->Initialize())
        {
            ret_gpa_context = std::move(dx11_gpa_context);
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

bool Dx11GpaImplementor::CloseApiContext(std::unique_ptr<IGpaContext> context)
{
    assert(context);

    Dx11GpaContext* dx11_gpa_context          = reinterpret_cast<Dx11GpaContext*>(context.get());
    const GpaStatus set_default_clocks_result = dx11_gpa_context->SetStableClocks(false);
    if (set_default_clocks_result != kGpaStatusOk)
    {
        assert(!"Unable to set clocks back to default");
        GpaLogger::Instance().LogError("Unable to set clocks back to default");
    }
    // context destroyed when unique_ptr goes out of scope.

    return set_default_clocks_result == kGpaStatusOk;
}

PFNAmdDxExtCreate11 Dx11GpaImplementor::GetAmdExtFuncPointer() const
{
    return amd_dx_ext_create11_func_ptr_;
}

bool Dx11GpaImplementor::InitializeAmdExtFunction() const
{
    bool success = false;

    if (nullptr == amd_dx_ext_create11_func_ptr_)
    {
        const HMODULE h_dxx_dll = ::GetModuleHandleW(L"atidxx64.dll");
        if (nullptr != h_dxx_dll)
        {
            PFNAmdDxExtCreate11 amd_dx_ext_create11 = reinterpret_cast<PFNAmdDxExtCreate11>(GetProcAddress(h_dxx_dll, "AmdDxExtCreate11"));

            if (nullptr != amd_dx_ext_create11)
            {
                amd_dx_ext_create11_func_ptr_ = amd_dx_ext_create11;
                success                       = true;
            }
        }
    }
    else
    {
        success = true;
    }

    return success;
}

GpaDeviceIdentifier Dx11GpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    return static_cast<IUnknown*>(context_info);
}
