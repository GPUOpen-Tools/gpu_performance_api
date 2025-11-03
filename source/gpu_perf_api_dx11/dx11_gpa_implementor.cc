//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Implementation
//==============================================================================

#include <locale>
#include <codecvt>

#include <ADLUtil.h>
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

        if (kGpaStatusOk == gpa_status)
        {
            if (kAmdVendorId == adapter_desc.VendorId)
            {
                if (GetAmdHwInfo(d3d11_device, adapter_desc.VendorId, adapter_desc.DeviceId, hw_info))
                {
                    is_success = true;
                }
                else
                {
                    GPA_LOG_ERROR("Unable to get hardware information.");
                }
            }
            else if (kNvidiaVendorId == adapter_desc.VendorId || kIntelVendorId == adapter_desc.VendorId)
            {
                hw_info.SetVendorId(adapter_desc.VendorId);
                hw_info.SetDeviceId(adapter_desc.DeviceId);
                hw_info.SetRevisionId(adapter_desc.Revision);
                std::wstring adapter_name_wide_string(adapter_desc.Description);

                std::string adapter_name = wide_to_utf8_converter(adapter_name_wide_string);

                hw_info.SetDeviceName(adapter_name.c_str());

                if (kNvidiaVendorId == adapter_desc.VendorId)
                {
                    hw_info.SetHwGeneration(GDT_HW_GENERATION_NVIDIA);
                }
                else if (kIntelVendorId == adapter_desc.VendorId)
                {
                    hw_info.SetHwGeneration(GDT_HW_GENERATION_INTEL);
                }

                is_success = true;
            }
            else
            {
                std::stringstream ss;
                ss << "Unknown device adapter (vendorid=" << adapter_desc.VendorId << ", deviceid=" << adapter_desc.DeviceId
                   << ", revision=" << adapter_desc.Revision << ").";
                GPA_LOG_ERROR(ss.str().c_str());
            }
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
    assert(nullptr != context);

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

bool Dx11GpaImplementor::GetAmdHwInfo(ID3D11Device* d3d11_device, const int& primary_vendor_id, const int& primary_device_id, GpaHwInfo& hw_info) const
{
    bool success = false;

    if (InitializeAmdExtFunction())
    {
        PFNAmdDxExtCreate11 amd_dx_ext_create11 = amd_dx_ext_create11_func_ptr_;

        if (nullptr != amd_dx_ext_create11)
        {
            IAmdDxExt*            dx_ext                  = nullptr;
            IAmdDxExtPerfProfile* amd_dx_ext_perf_profile = nullptr;
            HRESULT               hr                      = amd_dx_ext_create11(d3d11_device, &dx_ext);

            if (SUCCEEDED(hr))
            {
                unsigned int gpu_index = 0;

                if (dxx_ext_utils::IsMultiGpuPerfExtSupported(dx_ext))
                {
                    amd_dx_ext_perf_profile = reinterpret_cast<IAmdDxExtPerfProfile*>(dx_ext->GetExtInterface(AmdDxExtPerfProfileID));

                    if (nullptr == amd_dx_ext_perf_profile)
                    {
                        // Only fail here if the primary device is a device that is supposed to support the PerfProfile extension.
                        // Pre-GCN devices do not support this extension (they use the counter interface exposed by the API).
                        // By not returning a failure here on older devices, the caller code will do the right thing on those devices.
                        GDT_HW_GENERATION generation;

                        if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(primary_device_id, generation) &&
                            generation >= GDT_HW_GENERATION_SOUTHERNISLAND)
                        {
                            GPA_LOG_ERROR("Unable to get perf counter extension for GCN device.");
                        }

                        AMDTDeviceInfoUtils::DeleteInstance();
                    }
                    else
                    {
                        PE_RESULT pe_result       = PE_OK;
                        BOOL      gpu_profileable = FALSE;

                        while ((PE_OK == pe_result) && (FALSE == gpu_profileable))
                        {
                            pe_result = amd_dx_ext_perf_profile->IsGpuProfileable(gpu_index, &gpu_profileable);
                            gpu_index++;
                        }

                        if (FALSE == gpu_profileable)
                        {
                            GPA_LOG_ERROR("No profilable GPU device available.");
                        }
                        else
                        {
                            --gpu_index;  // GPU is over incremented in the loop above.
                        }
                    }
                }

                hw_info.SetGpuIndex(gpu_index);

                const int vendor_id = primary_vendor_id;
                const int device_id = primary_device_id;

                AsicInfoList asic_info_list;
                AMDTADLUtils::Instance()->GetAsicInfoList(asic_info_list);
                AMDTADLUtils::DeleteInstance();

                for (AsicInfoList::iterator asic_info_iter = asic_info_list.begin(); asic_info_list.end() != asic_info_iter; ++asic_info_iter)
                {
                    if ((asic_info_iter->vendorID == vendor_id) && (asic_info_iter->deviceID == device_id))
                    {
                        hw_info.SetVendorId(asic_info_iter->vendorID);
                        hw_info.SetDeviceId(asic_info_iter->deviceID);
                        hw_info.SetRevisionId(asic_info_iter->revID);
                        hw_info.SetDeviceName(asic_info_iter->adapterName.c_str());
                        hw_info.SetHwGeneration(GDT_HW_GENERATION_NONE);

                        GDT_HW_GENERATION hw_generation;

                        if (AMDTDeviceInfoUtils::Instance()->GetHardwareGeneration(asic_info_iter->deviceID, hw_generation))
                        {
                            hw_info.SetHwGeneration(hw_generation);
                            UINT64 device_frequency = 0ull;
                            if (!dx11_utils::GetTimestampFrequency(d3d11_device, device_frequency))
                            {
                                GPA_LOG_ERROR("GetTimestampFrequency failed");

                                if (nullptr != amd_dx_ext_perf_profile)
                                {
                                    amd_dx_ext_perf_profile->Release();
                                }

                                if (nullptr != dx_ext)
                                {
                                    dx_ext->Release();
                                }

                                return false;
                            }
                            hw_info.SetTimeStampFrequency(device_frequency);
                        }

                        AMDTDeviceInfoUtils::DeleteInstance();

                        if (nullptr != dx_ext)
                        {
                            IAmdDxExtASICInfo* amd_dx_ext_asic_info = reinterpret_cast<IAmdDxExtASICInfo*>(dx_ext->GetExtInterface(AmdDxExtASICInfoID));

                            if (nullptr != amd_dx_ext_asic_info)
                            {
                                AmdDxASICInfoParam info_param    = {};
                                AmdDxASICInfo*     new_asic_info = new (std::nothrow) AmdDxASICInfo();

                                if (nullptr != new_asic_info)
                                {
                                    info_param.pASICInfo = new_asic_info;
                                    amd_dx_ext_asic_info->GetInfoData(&info_param);

                                    // Fix RX 6800.
                                    if (new_asic_info->hwInfo[0].chipID == 0x73bf && new_asic_info->hwInfo[0].revisionID == 0xC3)
                                    {
                                        new_asic_info->hwInfo[0].numShaderEngines = 3;
                                    }

                                    if (nullptr != info_param.pASICInfo && gpu_index < info_param.pASICInfo->gpuCount)
                                    {
                                        AmdDxASICInfoHWInfo asic_info = info_param.pASICInfo->hwInfo[gpu_index];
                                        hw_info.SetNumberCus(asic_info.totalCU);
                                        hw_info.SetNumberSimds(asic_info.totalCU * asic_info.numSimdsPerCU);
                                        hw_info.SetNumberShaderEngines(asic_info.numShaderEngines);
                                        hw_info.SetNumberShaderArrays(asic_info.numShaderArraysPerSE * asic_info.numShaderEngines);
                                    }

                                    delete new_asic_info;
                                }

                                amd_dx_ext_asic_info->Release();
                            }
                        }

                        success = true;
                        break;
                    }
                }

                if (nullptr != amd_dx_ext_perf_profile)
                {
                    amd_dx_ext_perf_profile->Release();
                }

                if (nullptr != dx_ext)
                {
                    dx_ext->Release();
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to create DX11 extension.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to initialize because extension creation is not available.");
        }
    }
    else
    {
#ifdef X64
        GPA_LOG_ERROR("Unable to initialize because 'atidxx64.dll' is not available.");
#else
        GPA_LOG_ERROR("Unable to initialize because 'atidxx32.dll' is not available.");
#endif
    }

    return success;
}

Dx11GpaImplementor::Dx11GpaImplementor()
    : amd_dx_ext_create11_func_ptr_(nullptr)
{
}

bool Dx11GpaImplementor::InitializeAmdExtFunction() const
{
    bool success = false;

    if (nullptr == amd_dx_ext_create11_func_ptr_)
    {
        HMODULE h_dxx_dll = nullptr;

#ifdef X64
        h_dxx_dll = ::GetModuleHandleW(L"atidxx64.dll");
#else
        h_dxx_dll = ::GetModuleHandleW(L"atidxx32.dll");
#endif

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
