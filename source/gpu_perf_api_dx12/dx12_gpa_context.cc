//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA DX12 Context implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_context.h"

#include "ADLUtil.h"
#include "DeviceInfoUtils.h"

#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_dx12/dx12_gpa_session.h"
#include "gpu_perf_api_dx12/dx12_utils.h"

Dx12GpaContext::Dx12GpaContext(ID3D12Device* d3d12_device, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : GpaContext(hw_info, flags)
{
    d3d12_device_           = d3d12_device;
    d3d12_device_->AddRef();
    amd_device_props_           = {};
    amd_ext_d3d_factory_object_ = nullptr;
    gpa_interface_              = nullptr;
    gpa_interface2_             = nullptr;
    clock_mode_                 = AmdExtDeviceClockMode::Default;

    AMDTADLUtils::Instance()->GetDriverVersion(driver_major_ver_, driver_minor_ver_, driver_sub_minor_ver_);
    AMDTADLUtils::DeleteInstance();
}

Dx12GpaContext::~Dx12GpaContext()
{
    CleanUp();
}

bool Dx12GpaContext::Initialize()
{
    bool is_succeeded = false;

    std::lock_guard<std::mutex> lock_initialization(dx12_gpa_context_mutex_);

    if (nullptr != d3d12_device_)
    {
        if (!InitializeAmdExtension())
        {
            GPA_LOG_ERROR("Unabled to initialize AMD profiling extension for DX12.");
        }
        else
        {
            is_succeeded = true;
        }
    }

    SetAsOpened(is_succeeded);
    return is_succeeded;
}

GpaSessionId Dx12GpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    GpaSessionId ret_session_id = nullptr;

    if (nullptr != gpa_interface_)
    {
        Dx12GpaSession* new_gpa_dx12_gpa_session = new (std::nothrow) Dx12GpaSession(this, sample_type, gpa_interface_);

        if (nullptr != new_gpa_dx12_gpa_session)
        {
            AddGpaSession(new_gpa_dx12_gpa_session);
            ret_session_id = reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance()->CreateObject(new_gpa_dx12_gpa_session));
        }
    }

    return ret_session_id;
}

bool Dx12GpaContext::DeleteSession(GpaSessionId session_id)
{
    bool success = false;

    if (GpaUniqueObjectManager::Instance()->DoesExist(session_id))
    {
        Dx12GpaSession* dx12_session = reinterpret_cast<Dx12GpaSession*>(session_id->Object());

        unsigned int index;

        if (GetIndex(dx12_session, &index))
        {
            RemoveGpaSession(dx12_session);
            GpaUniqueObjectManager::Instance()->DeleteObject(session_id);
            delete dx12_session;
            success = true;
        }
    }

    return success;
}

GpaApiType Dx12GpaContext::GetApiType() const
{
    return kGpaApiDirectx12;
}

ID3D12Device* Dx12GpaContext::GetD3D12Device() const
{
    return d3d12_device_;
}

GpaUInt32 Dx12GpaContext::GetNumInstances(AmdExtGpuBlock block) const
{
    GpaUInt32 instance_count = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        instance_count = static_cast<GpaUInt32>(amd_device_props_.blocks[static_cast<size_t>(block)].instanceCount);
    }

    return instance_count;
}

GpaUInt32 Dx12GpaContext::GetMaxEventId(AmdExtGpuBlock block) const
{
    GpaUInt32 max_event_id = 0;

    if (block < AmdExtGpuBlock::Count)
    {
        max_event_id = static_cast<GpaUInt32>(amd_device_props_.blocks[static_cast<size_t>(block)].maxEventId);
    }

    return max_event_id;
}

bool Dx12GpaContext::InitializeAmdExtension()
{
    GpaStatus result = kGpaStatusOk;

    if (nullptr != d3d12_device_)
    {
        if (nullptr == gpa_interface_ && IsAmdDevice())
        {
            result = kGpaStatusErrorDriverNotSupported;

            HMODULE h_dll = nullptr;
#ifdef X64
            h_dll = ::GetModuleHandleW(L"amdxc64.dll");
#else
            h_dll = ::GetModuleHandleW(L"amdxc32.dll");
#endif

            if (nullptr == h_dll)
            {
                GPA_LOG_ERROR("Unable to get driver module handle.");
            }
            else
            {
                PFNAmdExtD3DCreateInterface amd_ext_d3d_create_func =
                    reinterpret_cast<PFNAmdExtD3DCreateInterface>(GetProcAddress(h_dll, "AmdExtD3DCreateInterface"));

                if (nullptr == amd_ext_d3d_create_func)
                {
                    GPA_LOG_ERROR("Unable to get driver extension entry point.");
                }
                else
                {
                    HRESULT hr = amd_ext_d3d_create_func(d3d12_device_, __uuidof(IAmdExtD3DFactory), reinterpret_cast<void**>(&amd_ext_d3d_factory_object_));

                    if (FAILED(hr))
                    {
                        GPA_LOG_ERROR("Unable to get driver extension interface.");
                    }
                    else
                    {
                        hr = amd_ext_d3d_factory_object_->CreateInterface(
                            d3d12_device_, __uuidof(IAmdExtGpaInterface2), reinterpret_cast<void**>(&gpa_interface2_));
                        if (FAILED(hr))
                        {
                            hr = amd_ext_d3d_factory_object_->CreateInterface(
                                d3d12_device_, __uuidof(IAmdExtGpaInterface), reinterpret_cast<void**>(&gpa_interface_));
                        }
                        else
                        {
                            gpa_interface_ = gpa_interface2_;
                        }

                        if (FAILED(hr))
                        {
                            GPA_LOG_ERROR("Unable to get driver GPA extension interface.");
                        }
                        else
                        {
                            if (nullptr != gpa_interface2_)
                            {
                                hr = gpa_interface2_->GetPerfExperimentProperties2(&amd_device_props_, AmdExtGpuBlock::Count);
                            }
                            else if (nullptr != gpa_interface_)
                            {
                                hr = gpa_interface_->GetPerfExperimentProperties(&amd_device_props_);
                            }
                            else
                            {
                                GPA_LOG_ERROR("No valid GPA interface.");
                                result = kGpaStatusErrorFailed;
                            }

                            if (FAILED(hr))
                            {
                                GPA_LOG_ERROR("Unable to get current hardware perf experiment properties.");
                            }
                            else
                            {
                                if (0 == amd_device_props_.features.counters)
                                {
                                    GPA_LOG_ERROR("Active GPU hardware does not support performance counters.");
                                    result = kGpaStatusErrorHardwareNotSupported;
                                }
                                else
                                {
                                    result = SetStableClocks(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result == kGpaStatusOk;
}

void Dx12GpaContext::CleanUp()
{
    std::lock_guard<std::mutex> lock_context_resources(dx12_gpa_context_mutex_);

    // Release Device.
    if (nullptr != d3d12_device_)
    {
        d3d12_device_->Release();
        d3d12_device_ = nullptr;
    }

    if (nullptr != gpa_interface_)
    {
        IterateGpaSessionList([](IGpaSession* gpa_session) -> bool {
            delete gpa_session;
            return true;
        });
        ClearSessionList();

        if (nullptr != gpa_interface2_)
        {
            gpa_interface2_->Release();
            gpa_interface2_ = nullptr;
        }
        else
        {
            gpa_interface_->Release();
        }

        gpa_interface_ = nullptr;
    }

    // Release AMD D3D Factory.
    if (nullptr != amd_ext_d3d_factory_object_)
    {
        ULONG remaining_refs = amd_ext_d3d_factory_object_->Release();
        UNREFERENCED_PARAMETER(remaining_refs);
        amd_ext_d3d_factory_object_ = nullptr;
    }
}

GpaStatus Dx12GpaContext::SetStableClocks(bool use_profiling_clocks)
{
    if (nullptr != gpa_interface_)
    {
        AmdExtDeviceClockMode amd_clock_mode = AmdExtDeviceClockMode::Default;

        if (use_profiling_clocks)
        {
            DeviceClockMode device_clock_mode = GetDeviceClockMode();

            switch (device_clock_mode)
            {
            case DeviceClockMode::kDefault:
                amd_clock_mode = AmdExtDeviceClockMode::Default;
                break;

            case DeviceClockMode::kMinimumEngine:
                amd_clock_mode = AmdExtDeviceClockMode::MinimumEngine;
                break;

            case DeviceClockMode::kMinimumMemory:
                amd_clock_mode = AmdExtDeviceClockMode::MinimumMemory;
                break;

            case DeviceClockMode::kPeak:
                amd_clock_mode = AmdExtDeviceClockMode::Peak;
                break;

            case DeviceClockMode::kProfiling:
                amd_clock_mode = AmdExtDeviceClockMode::Profiling;
                break;

            default:
                amd_clock_mode = AmdExtDeviceClockMode::Profiling;
                break;
            }
        }

        if (amd_clock_mode != clock_mode_)
        {
            clock_mode_ = amd_clock_mode;
            gpa_interface_->SetClockMode(clock_mode_, nullptr);
        }
    }

    return kGpaStatusOk;
}

void Dx12GpaContext::GetDriverVersion(uint32_t& major, uint32_t& minor, uint32_t& sub_minor)
{
    major     = driver_major_ver_;
    minor     = driver_minor_ver_;
    sub_minor = driver_sub_minor_ver_;
}
