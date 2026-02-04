//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Implementation
//==============================================================================

#include <locale>
#include <codecvt>

#include <DeviceInfoUtils.h>

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

static GpaCounterGeneratorDx11* counter_generator_dx11 = nullptr;  ///< Static instance of DX11 generator.
static GpaCounterSchedulerDx11* counter_scheduler_dx11 = nullptr;  ///< Static instance of DX11 scheduler.

IGpaImplementor* CreateImplementor()
{
    counter_generator_dx11 = new GpaCounterGeneratorDx11(kGpaSessionSampleTypeDiscreteCounter);
    counter_scheduler_dx11 = new GpaCounterSchedulerDx11(kGpaSessionSampleTypeDiscreteCounter);
    return Dx11GpaImplementor::Instance();
}

void DestroyImplementor(IGpaImplementor* impl)
{
    if (counter_generator_dx11 != nullptr)
    {
        delete counter_generator_dx11;
        counter_generator_dx11 = nullptr;
    }

    if (counter_scheduler_dx11 != nullptr)
    {
        delete counter_scheduler_dx11;
        counter_scheduler_dx11 = nullptr;
    }

    if (nullptr != impl)
    {
        Dx11GpaImplementor::DeleteInstance();
    }
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

GpaApiType Dx11GpaImplementor::GetApiType() const
{
    return kGpaApiDirectx11;
}

bool Dx11GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    UNREFERENCED_PARAMETER(flags);

    bool is_success = false;

    IUnknown*     unknown_ptr  = static_cast<IUnknown*>(context_info);
    ID3D11Device* d3d11_device = nullptr;

    if (dx11_utils::GetD3D11Device(unknown_ptr, &d3d11_device) && dx11_utils::IsFeatureLevelSupported(d3d11_device))
    {
        DXGI_ADAPTER_DESC adapter_desc;
        GpaStatus         gpa_status = DxGetAdapterDesc(d3d11_device, adapter_desc);

        if (InitializeAmdExtFunction() == false)
        {
            GPA_LOG_ERROR("Unable to initialize AMD DX11 extensions.");
            gpa_status = kGpaStatusErrorFailed;
        }

        if (kGpaStatusOk == gpa_status)
        {
            // For now it is assumed that DX11 MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use DX11 MGPU extension to get the correct HW info
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

                    // GPA DX11 requires GFX10.
                    if (GDT_HW_GENERATION_GFX10 > hw_gen)
                    {
                        GPA_LOG_ERROR("Hardware not supported.");
                    }
                    else
                    {
                        UINT64 device_frequency = 0ull;
                        if (!dx11_utils::GetTimestampFrequency(d3d11_device, device_frequency))
                        {
                            GPA_LOG_ERROR("GetTimestampFrequency Failed");
                        }
                        else
                        {
                            hw_info.SetTimeStampFrequency(device_frequency);
                            is_success = true;
                        }
                    }
                }
            }

            hw_info.SetHwGeneration(hw_gen);
        }
        else
        {
            GPA_LOG_ERROR("Unable to get adapter information.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to get device or either device feature level is not supported.");
    }

    return is_success;
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

IGpaContext* Dx11GpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
{
    IUnknown*     unknown_ptr = static_cast<IUnknown*>(context_info);
    ID3D11Device* d3d11_device;
    IGpaContext*  ret_gpa_context = nullptr;

    if (dx11_utils::GetD3D11Device(unknown_ptr, &d3d11_device) && dx11_utils::IsFeatureLevelSupported(d3d11_device))
    {
        Dx11GpaContext* dx11_gpa_context = new (std::nothrow) Dx11GpaContext(d3d11_device, hw_info, flags);

        if (nullptr != dx11_gpa_context)
        {
            if (dx11_gpa_context->Initialize())
            {
                ret_gpa_context = dx11_gpa_context;
            }
            else
            {
                delete dx11_gpa_context;
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

bool Dx11GpaImplementor::CloseApiContext(IGpaContext* context)
{
    assert(context);

    GpaStatus set_default_clocks_result = kGpaStatusOk;

    if (nullptr != context)
    {
        Dx11GpaContext* dx11_gpa_context = reinterpret_cast<Dx11GpaContext*>(context);
        set_default_clocks_result        = dx11_gpa_context->SetStableClocks(false);
        if (set_default_clocks_result != kGpaStatusOk)
        {
            assert(!"Unable to set clocks back to default");
            GPA_LOG_ERROR("Unable to set clocks back to default");
        }
        delete dx11_gpa_context;
    }

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
