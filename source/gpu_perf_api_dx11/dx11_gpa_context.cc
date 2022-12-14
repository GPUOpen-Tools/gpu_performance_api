//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA DX11 Context Implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_gpa_context.h"

#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_dx11/dx11_gpa_implementor.h"
#include "gpu_perf_api_dx11/dx11_gpa_session.h"
#include "gpu_perf_api_dx11/dxx_ext_utils.h"

Dx11GpaContext::Dx11GpaContext(ID3D11Device* d3d11_device, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags)
    : GpaContext(hw_info, context_flags)
    , d3d11_device_(d3d11_device)
    , dx_ext_(nullptr)
    , dx_ext_pe_(nullptr)
    , block_counter_info_{}
    , block_info_init_{}
    , gpu_caps_()
    , clock_mode_()
{
#ifdef _DEBUG
    D3D_SET_OBJECT_NAME_A(d3d11_device_, "GPA_DX11DeviceRef");
#endif
    ULONG refCount = d3d11_device_->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    gpu_caps_.version = 0u;
}

Dx11GpaContext::~Dx11GpaContext()
{
    GpaStatus set_stable_clocks_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks back to default.");
    }

    if (nullptr != dx_ext_pe_)
    {
        dx_ext_pe_->Release();
    }

    if (nullptr != dx_ext_)
    {
        dx_ext_->Release();
    }

    if (nullptr != d3d11_device_)
    {
        ULONG ref_count = d3d11_device_->Release();
        UNREFERENCED_PARAMETER(ref_count);
        d3d11_device_ = nullptr;
    }
}

GpaSessionId Dx11GpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    GpaSessionId ret_session_id = nullptr;

    Dx11GpaSession* new_dx11_gpa_session = new (std::nothrow) Dx11GpaSession(this, sample_type);

    if (nullptr == new_dx11_gpa_session)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(new_dx11_gpa_session);

        if (nullptr != new_dx11_gpa_session)
        {
            ret_session_id = reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance()->CreateObject(new_dx11_gpa_session));
        }
    }

    return ret_session_id;
}

bool Dx11GpaContext::DeleteSession(GpaSessionId session_id)
{
    bool success = false;

    if (GpaUniqueObjectManager::Instance()->DoesExist(session_id))
    {
        Dx11GpaSession* dx11_gpa_session = reinterpret_cast<Dx11GpaSession*>(session_id->Object());

        unsigned int index;

        if (GetIndex(dx11_gpa_session, &index))
        {
            RemoveGpaSession(dx11_gpa_session);
            GpaUniqueObjectManager::Instance()->DeleteObject(session_id);
            delete dx11_gpa_session;
            success = true;
        }
    }

    return success;
}

GpaUInt32 Dx11GpaContext::GetMaxGpaSessions() const
{
    // Reported maximum latency was 4 for r6xx cards
    // had issues with this value. Had to switch to 32.
    return 32;
}

GpaApiType Dx11GpaContext::GetApiType() const
{
    return kGpaApiDirectx11;
}

bool Dx11GpaContext::Initialize()
{
    bool is_success = false;

    if (!OpenCounters())
    {
        GPA_LOG_ERROR("Unable to open counters for DX11.");
    }
    else if (!InitializeProfileAMDExtension())
    {
        GPA_LOG_ERROR("Unable to initialize AMD profile extension for DX11.");
    }
    else
    {
        GpaStatus set_stable_clocks_status = SetStableClocks(true);
        if (kGpaStatusOk != set_stable_clocks_status)
        {
            GPA_LOG_ERROR("Driver was unable to set stable clocks for profiling.");
        }

        // Even if the stable clocks could not be set, this is considered successful.
        is_success = true;
    }

    SetAsOpened(is_success);
    return is_success;
}

IAmdDxExt* Dx11GpaContext::GetAmdDxExtension() const
{
    return dx_ext_;
}

IAmdDxExtPerfProfile* Dx11GpaContext::GetAmdProfileExtension() const
{
    return dx_ext_pe_;
}

ID3D11Device* Dx11GpaContext::GetDevice() const
{
    return d3d11_device_;
}

GpuIndex Dx11GpaContext::GetActiveGpu() const
{
    GpuIndex active_gpu = 0;

    if (nullptr != dx_ext_ && nullptr != dx_ext_pe_ && dxx_ext_utils::IsMultiGpuPerfExtSupported(dx_ext_))
    {
        unsigned int active_gpu_count = 0;
        unsigned int gpu              = 0;
        PE_RESULT    pe_result        = PE_OK;
        BOOL         gpu_profileable  = FALSE;

        constexpr unsigned int max_gpu_count = 8;  // This value is taken from DXX ASIC info extension header.

        // First pass get the number of active GPUs.
        while ((PE_OK == pe_result) && (max_gpu_count > gpu))
        {
            pe_result = dx_ext_pe_->IsGpuProfileable(gpu, &gpu_profileable);

            if (TRUE == gpu_profileable)
            {
                ++active_gpu_count;
            }

            ++gpu;
        }

        if (1 < active_gpu_count)
        {
            active_gpu = kActiveGpuCf;
        }
        else  // Not ACF/CF - run a second pass to find the active GPU.
        {
            gpu             = 0;
            pe_result       = PE_OK;
            gpu_profileable = FALSE;

            while ((PE_OK == pe_result) && (FALSE == gpu_profileable) && (max_gpu_count > gpu))
            {
                pe_result = dx_ext_pe_->IsGpuProfileable(gpu, &gpu_profileable);

                if (TRUE == gpu_profileable)
                {
                    active_gpu = gpu;
                }

                ++gpu;
            }
        }
    }

    return active_gpu;
}

GpuIndex Dx11GpaContext::GetCfActiveGpu() const
{
    return kActiveGpuCf;
}

GpaUInt32 Dx11GpaContext::GetNumInstances(PE_BLOCK_ID block) const
{
    GpaUInt32 ret_val = 0u;

    if (block_info_init_[block])
    {
        ret_val = block_counter_info_[block].instanceCount;
    }

    return ret_val;
}

GpaUInt32 Dx11GpaContext::GetMaxEventId(PE_BLOCK_ID block) const
{
    GpaUInt32 ret_val = 0u;

    if (block_info_init_[block])
    {
        ret_val = block_counter_info_[block].maxEventId;
    }

    return ret_val;
}

bool Dx11GpaContext::InitializeProfileAMDExtension()
{
    bool success = true;

    PFNAmdDxExtCreate11 dx11_extension_func = Dx11GpaImplementor::Instance()->GetAmdExtFuncPointer();

    if (nullptr == dx11_extension_func)
    {
        GPA_LOG_ERROR("AMD extension function is not initialized.");
        success = false;
    }
    else
    {
        // Note: PFNAmdDxExtCreate11 adds a ref on the out parameter.
        HRESULT hr = dx11_extension_func(d3d11_device_, &dx_ext_);

        if (FAILED(hr))
        {
            GPA_LOG_ERROR("Unable to create DX11 extension.");
            success = false;
        }
        else
        {
            dx_ext_pe_ = reinterpret_cast<IAmdDxExtPerfProfile*>(dx_ext_->GetExtInterface(AmdDxExtPerfProfileID));

            if (nullptr == dx_ext_pe_)
            {
                dx_ext_->Release();
                dx_ext_ = nullptr;
                GPA_LOG_ERROR("Unable to initialize because the driver does not support the PerfProfile extension.");
                success = false;
            }
            else
            {
                GpuIndex active_gpu = GetActiveGpu();

                if (PE_OK != dx_ext_pe_->GetGpuCaps(active_gpu, &gpu_caps_))
                {
                    GPA_LOG_ERROR("Unable to get device capabilities from the driver.");
                    success = false;
                }

                for (auto gpu_block_iter = 0u; gpu_block_iter < PE_BLOCK_ID_MAX; gpu_block_iter++)
                {
                    // Note: if using an older driver (one that doesn't support the new Performance Experiment interface -- see IsMgpuPerfExpSupported)
                    //       gpuID will be 0. However, looking at driver sources, the implementation of GetBlockCounterInfo in those older
                    //       drivers ignores this parameter anyway.
                    PE_RESULT block_counter_info_result =
                        dx_ext_pe_->GetBlockCounterInfo(active_gpu, static_cast<PE_BLOCK_ID>(gpu_block_iter), &block_counter_info_[gpu_block_iter]);
                    if (PE_OK == block_counter_info_result)
                    {
                        block_info_init_[gpu_block_iter] = true;
                        success &= true;
                    }
                    else
                    {
                        block_info_init_[gpu_block_iter] = false;
                        GPA_LOG_DEBUG_ERROR("Failed to retrieve block counter info, block info will not be set on this iteration.");
                    }
                }
            }
        }
    }

    return success;
}

GpaStatus Dx11GpaContext::SetStableClocks(bool use_profiling_clocks)
{
    GpaStatus result = kGpaStatusOk;

    // Only use Stable PState feature if driver supports at least extension version 3.
    if (3 > gpu_caps_.version)
    {
        GPA_LOG_MESSAGE("DX11 stable clock extension is not available.");
    }
    else
    {
        PE_CLOCK_MODE clock_mode = PE_CLOCK_MODE_DEFAULT;

        if (use_profiling_clocks)
        {
            DeviceClockMode device_clock_mode = GetDeviceClockMode();

            switch (device_clock_mode)
            {
            case DeviceClockMode::kDefault:
                clock_mode = PE_CLOCK_MODE_DEFAULT;
                break;

            case DeviceClockMode::kProfiling:
                clock_mode = PE_CLOCK_MODE_PROFILING;
                break;

            case DeviceClockMode::kMinimumMemory:
                clock_mode = PE_CLOCK_MODE_MIN_MEMORY;
                break;

            case DeviceClockMode::kMinimumEngine:
                clock_mode = PE_CLOCK_MODE_MIN_ENGINE;
                break;

            case DeviceClockMode::kPeak:
                clock_mode = PE_CLOCK_MODE_PEAK;
                break;

            default:
                assert(0);
                clock_mode = PE_CLOCK_MODE_PROFILING;
                break;
            }
        }

        if (clock_mode != clock_mode_)
        {
            clock_mode_ = clock_mode;

            PE_RESULT status = dx_ext_pe_->SetClockMode(clock_mode, nullptr);
            result           = (PE_OK == status) ? kGpaStatusOk : kGpaStatusErrorDriverNotSupported;

            if (PE_OK != status)
            {
                GPA_LOG_ERROR("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}