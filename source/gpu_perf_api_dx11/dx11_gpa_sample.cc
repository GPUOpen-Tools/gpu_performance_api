//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 GPA Sample Implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_gpa_sample.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_pass.h"

#include "gpu_perf_api_dx11/dx11_gpa_context.h"
#include "gpu_perf_api_dx11/dx11_gpa_pass.h"
#include "gpu_perf_api_dx11/dxx_ext_utils.h"

/// Macro to assert on a PerfExperiment error.
#ifdef _DEBUG
#define ASSERT_ON_PE_ERROR(result)                      \
    if (result == PE_ERROR_OUT_OF_RESOURCES)            \
        assert(!(result == PE_ERROR_OUT_OF_RESOURCES)); \
    if (result == PE_ERROR_INVALID_ARGUMENT)            \
        assert(!(result == PE_ERROR_INVALID_ARGUMENT)); \
    if (result == PE_ERROR_FINALIZED)                   \
        assert(!(result == PE_ERROR_FINALIZED));        \
    if (result == PE_ERROR_UNAVAILABLE)                 \
        assert(!(result == PE_ERROR_UNAVAILABLE));      \
    if (result == PE_ERROR_RESOURCE_BUSY)               \
        assert(!(result == PE_ERROR_RESOURCE_BUSY));    \
    if (result == PE_ERROR_OUT_OF_MEMORY)               \
        assert(!(result == PE_ERROR_OUT_OF_MEMORY));    \
    if (result == PE_ERROR_NOT_SUPPORTED)               \
        assert(!(result == PE_ERROR_NOT_SUPPORTED));
#else
#define ASSERT_ON_PE_ERROR(result)
#endif

Dx11GpaSample::~Dx11GpaSample()
{
    ReleaseSampleResources();
}

Dx11GpaSample::Dx11GpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
    : GpaSample(pass, cmd_list, sample_type, sample_id)
    , amd_dx_ext_perf_experiment_(nullptr)
    , amd_dx_ext_perf_counters_(nullptr)
    , gpu_time_counter_(nullptr)
{
}

bool Dx11GpaSample::UpdateResults()
{
    bool         is_complete   = false;
    Dx11GpaPass* dx11_gpa_pass = reinterpret_cast<Dx11GpaPass*>(GetPass());

    if (GetPass()->IsTimingPass() && nullptr != gpu_time_counter_)
    {
        ID3D11DeviceContext* d3d11_device_context = nullptr;
        Dx11GpaContext*      dx11_gpa_context     = reinterpret_cast<Dx11GpaContext*>(dx11_gpa_pass->GetGpaSession()->GetParentContext());
        dx11_gpa_context->GetDevice()->GetImmediateContext(&d3d11_device_context);

        if (nullptr != d3d11_device_context)
        {
            HRESULT gpu_time_result_status = d3d11_device_context->GetData(gpu_time_counter_, nullptr, 0, 0);

            if (FAILED(gpu_time_result_status))
            {
                GPA_LOG_ERROR("Call to ID3D11DeviceContext::GetData failed.");
            }
            else
            {
                is_complete = S_OK == gpu_time_result_status;  // S_OK == data ready; S_FALSE == data not ready.
                d3d11_device_context->Release();

                if (is_complete)
                {
                    is_complete = PopulateResult();
                }
                else
                {
                    GPA_LOG_DEBUG_MESSAGE("GPU Time data not yet ready.");
                }
            }
        }
    }
    else if (nullptr != amd_dx_ext_perf_experiment_)
    {
        BOOL ret_val = amd_dx_ext_perf_experiment_->WaitCompletion(10);

        if (ret_val && PopulateResult())
        {
            is_complete = true;
        }
    }
    else if (0 == dx11_gpa_pass->GetEnabledCounterCount())
    {
        // If there are no actual hardware counters in this sample, then indicate results are ready.
        is_complete = true;
    }

    return is_complete;
}

bool Dx11GpaSample::PopulateResult()
{
    bool             populated     = false;
    GpaSampleResult* sample_result = GetSampleResultLocation();

    if (nullptr != sample_result)
    {
        size_t counter_count = GetPass()->GetEnabledCounterCount();

        if (GetPass()->IsTimingPass() && nullptr != gpu_time_counter_)
        {
            Dx11GpaContext*      dx11_gpa_context     = reinterpret_cast<Dx11GpaContext*>(GetPass()->GetGpaSession()->GetParentContext());
            ID3D11DeviceContext* d3d11_device_context = nullptr;
            dx11_gpa_context->GetDevice()->GetImmediateContext(&d3d11_device_context);

            if (nullptr != d3d11_device_context)
            {
                UINT gpu_time_counter_data_size = gpu_time_counter_->GetDataSize();

                if ((1 != counter_count) || (gpu_time_counter_data_size != counter_count * sizeof(GpaUInt64)))
                {
                    GPA_LOG_ERROR("Call to DX11 PopulateResult encountered invalid number of counters, or invalid number of bytes.");
                    return false;
                }

                // An array of 2x gpa_uint64 is passed to ID3D11DeviceContext::GetData.
                // However, note that the size of the array passed to the API is 1x gpa_uint64.
                // The driver writes 2x gpa_uint64 values.
                // Passing a single gpa_uint64 array will cause a trailing memory overwrite.
                // Passing the actual size of the array will cause a Direct3D11 error.
                // Therefore, this may appear to be incorrect, but it's actually correct.
                GpaUInt64 timing_data[2] = {};

                HRESULT hr = d3d11_device_context->GetData(gpu_time_counter_, &timing_data, gpu_time_counter_data_size, 0);

                // The above should never return S_FALSE (data not ready) because UpdateResults will only call this function
                // if it has determined that the data is ready.
                assert(S_FALSE != hr);

                if (SUCCEEDED(hr))
                {
                    // Copy top data if requested.
                    if (GetPass()->GetTopToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                    {
                        *sample_result->GetAsCounterSampleResult()->GetResultBuffer() = timing_data[0];
                    }

                    // Copy bottom data if requested.
                    if (GetPass()->GetBottomToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                    {
                        *sample_result->GetAsCounterSampleResult()->GetResultBuffer() = timing_data[1];
                    }

                    populated = true;
                }
                else
                {
                    assert(SUCCEEDED(hr));
                    GPA_LOG_ERROR("Call to ID3D11DeviceContext::GetData failed.");
                }

                d3d11_device_context->Release();
            }
        }
        else
        {
            for (size_t counter_iter = 0; counter_iter < counter_count; counter_iter++)
            {
                sample_result->GetAsCounterSampleResult()->GetResultBuffer()[counter_iter] = amd_dx_ext_perf_counters_[counter_iter]->GetData();
            }

            populated = true;
        }
    }

    if (populated)
    {
        MarkAsCompleted();
    }

    return populated;
}

void Dx11GpaSample::ReleaseSampleResources()
{
    if (nullptr != amd_dx_ext_perf_counters_)
    {
        delete[] amd_dx_ext_perf_counters_;
        amd_dx_ext_perf_counters_ = nullptr;
    }

    if (nullptr != amd_dx_ext_perf_experiment_)
    {
        amd_dx_ext_perf_experiment_->ReleaseResources();
        amd_dx_ext_perf_experiment_->Destroy();
        amd_dx_ext_perf_experiment_ = nullptr;
    }

    if (nullptr != gpu_time_counter_)
    {
        gpu_time_counter_->Release();
        gpu_time_counter_ = nullptr;
    }
}

bool Dx11GpaSample::BeginRequest()
{
    bool success = false;

    Dx11GpaPass*    dx11_gpa_pass    = reinterpret_cast<Dx11GpaPass*>(GetPass());
    Dx11GpaContext* dx11_gpa_context = reinterpret_cast<Dx11GpaContext*>(dx11_gpa_pass->GetGpaSession()->GetParentContext());

    if (nullptr != dx11_gpa_context)
    {
        IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(dx11_gpa_context);
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

        if (dx11_gpa_pass->IsTimingPass())
        {
            ID3D11Device*        device         = dx11_gpa_context->GetDevice();
            ID3D11DeviceContext* device_context = nullptr;
            device->GetImmediateContext(&device_context);

            if (nullptr == gpu_time_counter_ && nullptr != device_context)
            {
                // Counter not created, create here.
                D3D11_COUNTER_DESC ctr_desc = {};
                ctr_desc.Counter            = static_cast<D3D11_COUNTER>(
                    hardware_counters->hardware_counters_.at(hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_).counter_id_driver);

                if (dx11_gpa_pass->GetTopToBottomTimingDurationCounterIndex() != static_cast<DWORD>(-1))
                {
                    ctr_desc.Counter = static_cast<D3D11_COUNTER>(
                        hardware_counters->hardware_counters_.at(hardware_counters->gpu_time_top_to_bottom_duration_counter_index_).counter_id_driver);
                }

                assert(ctr_desc.Counter != 0);
                ctr_desc.MiscFlags = 0;

                D3D11_COUNTER_TYPE type                       = D3D11_COUNTER_TYPE_FLOAT32;
                GpaUInt32          active_counters            = 0;
                GpaUInt32          num_available_counter_size = sizeof(GpaUInt32);
                HRESULT hr = device->CheckCounter(&ctr_desc, &type, &active_counters, nullptr, nullptr, nullptr, &num_available_counter_size, nullptr, nullptr);

                if (SUCCEEDED(hr))
                {
                    hr = device->CreateCounter(&ctr_desc, &gpu_time_counter_);

                    if (SUCCEEDED(hr))
                    {
                        device_context->Begin(gpu_time_counter_);
                        success = true;
                    }
                    else
                    {
                        GPA_LOG_DEBUG_ERROR("Call to ID3D11Device::CreateCounter failed on the GPUTime counter.");
                        GPA_LOG_ERROR("Call to ID3D11Device::CreateCounter failed.");
                        device_context->Release();
                    }
                }
                else
                {
                    // Make sure any counters which worked are released.
                    GPA_LOG_DEBUG_ERROR("Call to ID3D11Device::CheckCounter failed on the GPUTime counter.");
                    device_context->Release();
                }

                device_context->Release();
            }
        }
        else
        {
            if (0 == dx11_gpa_pass->GetEnabledCounterCount())
            {
                // If there are no actual hardware counters in this sample, log a debug message and return true.
                GPA_LOG_DEBUG_MESSAGE("No counters enabled in this sample.");
                success = true;
            }
            else if (CreateSampleExperiment() && CreateAndAddCounterToExperiment())
            {
                // Finalize the experiment.
                PE_RESULT result = amd_dx_ext_perf_experiment_->Finalize();

                if (PE_OK == result)
                {
                    result = amd_dx_ext_perf_experiment_->Begin();

                    if (PE_OK == result)
                    {
                        success = true;
                    }
                    else
                    {
                        ASSERT_ON_PE_ERROR(result);
                        GPA_LOG_DEBUG_ERROR("Call to IPerfExperiment::Begin failed.");
                    }
                }
                else
                {
                    if (result == PE_ERROR_OUT_OF_MEMORY)
                    {
                        GPA_LOG_ERROR("Counter could not be enabled due to an Out Of Memory error.");
                    }
                    else
                    {
                        ASSERT_ON_PE_ERROR(result);
                        GPA_LOG_DEBUG_ERROR("Call to IPerfExperiment::Finalize failed.");
                    }
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to create the sample experiment or unable to initialize the counters.");
            }
        }
    }

    return success;
}

bool Dx11GpaSample::EndRequest()
{
    bool success = false;

    Dx11GpaPass* dx11_gpa_pass = reinterpret_cast<Dx11GpaPass*>(GetPass());

    if (dx11_gpa_pass->IsTimingPass())
    {
        Dx11GpaContext*      dx11_gpa_context = reinterpret_cast<Dx11GpaContext*>(dx11_gpa_pass->GetGpaSession()->GetParentContext());
        ID3D11Device*        d3d_device       = dx11_gpa_context->GetDevice();
        ID3D11DeviceContext* device_context   = nullptr;
        d3d_device->GetImmediateContext(&device_context);

        if (nullptr != device_context)
        {
            device_context->End(gpu_time_counter_);
            success = true;
            device_context->Release();
        }
    }
    else
    {
        if (nullptr != amd_dx_ext_perf_experiment_)
        {
            amd_dx_ext_perf_experiment_->End();
            success = true;
        }
        else if (0 == dx11_gpa_pass->GetEnabledCounterCount())
        {
            // If there are no actual hardware counters in this sample, return true.
            success = true;
        }
    }

    return success;
}

void Dx11GpaSample::ReleaseCounters()
{
    ReleaseSampleResources();
}

bool Dx11GpaSample::CreateSampleExperiment()
{
    bool            success          = false;
    Dx11GpaPass*    dx11_gpa_pass    = reinterpret_cast<Dx11GpaPass*>(GetPass());
    Dx11GpaContext* dx11_gpa_context = reinterpret_cast<Dx11GpaContext*>(dx11_gpa_pass->GetGpaSession()->GetParentContext());

    if (nullptr != dx11_gpa_context)
    {
        IAmdDxExt*            dx_ext = dx11_gpa_context->GetAmdDxExtension();
        IAmdDxExtPerfProfile* ext_pe = dx11_gpa_context->GetAmdProfileExtension();

        if (0 == dx11_gpa_pass->GetEnabledCounterCount())
        {
            GPA_LOG_DEBUG_MESSAGE("No counters enabled in this sample.");
        }
        else
        {
            if ((nullptr == amd_dx_ext_perf_experiment_) && (nullptr != ext_pe))
            {
                // Create correct version of experiment based on driver version.
                if (dxx_ext_utils::IsMultiGpuPerfExtSupported(dx_ext))
                {
                    GpuIndex active_gpu = dx11_gpa_context->GetActiveGpu();

                    if (dx11_gpa_context->GetCfActiveGpu() == active_gpu)
                    {
                        // When checking block limits, if in Crossfire mode, always use GPU zero; if in PX mode, use the active GPU.
                        active_gpu = 0;

                        // In CF/ACF scenario let the driver create the experiment on the
                        // current frame active GPU.
                        amd_dx_ext_perf_experiment_ = ext_pe->CreateExperiment();
                    }
                    else
                    {
                        amd_dx_ext_perf_experiment_ = ext_pe->CreateExperimentEx(active_gpu);
                    }
                }
                else
                {
                    amd_dx_ext_perf_experiment_ = ext_pe->CreateExperiment();
                }

                bool engine_param_set_success = true;

                IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(dx11_gpa_context);
                const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

                if (nullptr != amd_dx_ext_perf_experiment_)
                {
                    auto assign_engine_param = [&](CounterIndex counter_index) -> bool {
                        const GpaHardwareCounterDescExt* counter = &hardware_counters->hardware_counters_.at(counter_index);
                        engine_param_set_success                 = true;

                        if (counter->group_id_driver == PE_BLOCK_SQ ||
                            counter->group_id_driver == PE_BLOCK_SQWGP)
                        {
                            // Set all valid shader engines to the current stage mask.
                            for (unsigned int ii = 0; ii < dx11_gpa_context->GetHwInfo()->GetNumberShaderEngines(); ii++)
                            {
                                SqEngineParamValue sq_engine_param_value;

                                if (dx11_gpa_pass->GetSqEngineParamValue(counter_index, sq_engine_param_value))
                                {
                                    PE_RESULT result = amd_dx_ext_perf_experiment_->SetEngineParam(ii, PE_PARAM_SQ_SHADER_MASK, sq_engine_param_value);

                                    if (PE_OK != result)
                                    {
                                        GPA_LOG_ERROR("Unable to set the shader engine parameter.");
                                        engine_param_set_success = false;
                                        break;
                                    }
                                }
                            }
                        }

                        return engine_param_set_success;
                    };

                    dx11_gpa_pass->IterateEnabledCounterList(assign_engine_param);

                    success = engine_param_set_success;

                    if (!success)
                    {
                        GPA_LOG_ERROR("Unable to set engine params.");
                    }
                }
            }
            else
            {
                GPA_LOG_ERROR("Either the experiment has already been created or the driver extension is not available.");
            }
        }
    }

    return success;
}

bool Dx11GpaSample::CreateAndAddCounterToExperiment()
{
    // Assuming things will succeed; gets set to false if an error occurs.
    bool success = true;
    assert(nullptr == amd_dx_ext_perf_counters_);

    CounterCount enabled_counter_count       = GetPass()->GetEnabledCounterCount();
    CounterCount enabled_counter_count_index = 0;
    amd_dx_ext_perf_counters_                = new (std::nothrow) IAmdDxExtPerfCounter*[enabled_counter_count];

    if (nullptr != amd_dx_ext_perf_counters_)
    {
        IGpaCounterAccessor*       counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetPass()->GetGpaSession()->GetParentContext());
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

        auto add_counter_to_experiment = [&](CounterIndex counter_index) -> bool {
            success = true;
            // Need to Add a counter.
            const GpaHardwareCounterDescExt* counter = &hardware_counters->hardware_counters_.at(counter_index);
            UINT32 instance = static_cast<unsigned int>(hardware_counters->internal_counter_groups_[counter->group_index].block_instance);

            // Add valid counters to the experiment.
            PE_RESULT result = PE_ERROR_NOT_SUPPORTED;

            if (nullptr != amd_dx_ext_perf_experiment_)
            {
                result = amd_dx_ext_perf_experiment_->AddCounter(static_cast<PE_BLOCK_ID>(counter->group_id_driver),
                                                                 instance,
                                                                 static_cast<UINT>(counter->hardware_counters->counter_index_in_group),
                                                                 &amd_dx_ext_perf_counters_[enabled_counter_count_index]);

                if (PE_OK != result)
                {
                    GPA_LOG_ERROR("Unable to add counter to the experiment.");
                    success = false;
                }
                else
                {
                    if (counter->group_id_driver == PE_BLOCK_SQ)
                    {
                        // The SQ_SIMD_MASK only applies to GFX9 and earlier, and is ignored on newer generations.
                        result = amd_dx_ext_perf_counters_[enabled_counter_count_index]->SetParam(PE_COUNTER_SQ_SIMD_MASK, 0xF);

                        if (result != PE_OK)
                        {
                            ASSERT_ON_PE_ERROR(result);
                            GPA_LOG_DEBUG_ERROR("call to IAmdDxExtPerfCounter::SetParam failed.");
                            success = false;
                        }
                    }
                }

                enabled_counter_count_index++;
            }
            else
            {
                success = false;
            }

            return success;
        };

        Dx11GpaPass* dx11_gpa_pass = reinterpret_cast<Dx11GpaPass*>(GetPass());

        dx11_gpa_pass->IterateEnabledCounterList(add_counter_to_experiment);

        if (!success)
        {
            // If not successful, delete allocations.
            delete[] amd_dx_ext_perf_counters_;
            amd_dx_ext_perf_counters_ = nullptr;
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to allocate memory for performance counters.");
        success = false;
    }

    return success;
}
