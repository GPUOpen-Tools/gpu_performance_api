//==============================================================================
// Copyright (c) 2017-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Common DX12 counter generation.
//==============================================================================

#include <d3d12.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

const GpaSoftwareCounterDesc GpaCounterGeneratorDx12Base::kDx12SoftwareCounters[] = {
    {
        // D3D12_QUERY_TYPE_TIMESTAMP.
        D3D12_QUERY_TYPE_TIMESTAMP,
        "D3DGPUTime",
        "D3D12",
        "Time spent in GPU",
        kGpaDataTypeFloat64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP.
        D3D12_QUERY_TYPE_TIMESTAMP,
        "PreBottomTimestamp",
        "D3D12",
        "Bottom of the pipeline GPU timestamp",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP.
        D3D12_QUERY_TYPE_TIMESTAMP,
        "PostBottomTimestamp",
        "D3D12",
        "Bottom of the pipeline GPU timestamp",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_OCCLUSION.
        D3D12_QUERY_TYPE_OCCLUSION,
        "Occlusion",
        "D3D12",
        "Get the number of samples that passed the depth and stencil tests.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_BINARY_OCCLUSION.
        D3D12_QUERY_TYPE_BINARY_OCCLUSION,
        "BinaryOcclusion",
        "D3D12",
        "True/false if any samples passed depth and stencil tests.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAVertices.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "IAVertices",
        "D3D12",
        "Number of vertices read by input assembler.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAPrimitives.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "IAPrimitives",
        "D3D12",
        "Number of primitives read by the input assembler.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS VSInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "VSInvocations",
        "D3D12",
        "Number of times a vertex shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "GSInvocations",
        "D3D12",
        "Number of times a geometry shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "GSPrimitives",
        "D3D12",
        "Number of primitives output by a geometry shader.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "CInvocations",
        "D3D12",
        "Number of primitives that were sent to the rasterizer.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CPrimitives.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "CPrimitives",
        "D3D12",
        "Number of primitives that were rendered.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS PSInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "PSInvocations",
        "D3D12",
        "Number of times a pixel shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS HSInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "HSInvocations",
        "D3D12",
        "Number of times a hull shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS DSInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "DSInvocations",
        "D3D12",
        "Number of times a domain shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CSInvocations.
        D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
        "CSInvocations",
        "D3D12",
        "Number of times a compute shader was invoked.",
        kGpaDataTypeUint64,
    },
};

const size_t GpaCounterGeneratorDx12Base::kDx12SoftwareCountersCount = (sizeof(kDx12SoftwareCounters) / sizeof(GpaSoftwareCounterDesc));

bool GpaCounterGeneratorDx12Base::GetSwCounterDesc(const GpaUInt32 sw_counter_index, GpaSoftwareCounterDesc& sw_counter_desc)
{
    if (sw_counter_index < kDx12SoftwareCountersCount)
    {
        sw_counter_desc = kDx12SoftwareCounters[sw_counter_index];
    }

    return sw_counter_index < kDx12SoftwareCountersCount;
}

GpaStatus GpaCounterGeneratorDx12Base::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                              GDT_HW_ASIC_TYPE    asic_type,
                                                              GpaUInt8            generate_asic_specific_counters,
                                                              GpaDerivedCounters* public_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx12Base::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                                GDT_HW_ASIC_TYPE     asic_type,
                                                                GpaUInt8             generate_asic_specific_counters,
                                                                GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx12Base::GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                                                GDT_HW_ASIC_TYPE     asic_type,
                                                                GpaUInt8             generate_asic_specific_counters,
                                                                GpaSoftwareCounters* software_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (nullptr == software_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    GpaStatus status = kGpaStatusOk;

    if (software_counters->counters_generated_)
    {
        return status;
    }

    switch (desired_generation)
    {
    case GDT_HW_GENERATION_SOUTHERNISLAND:
    case GDT_HW_GENERATION_SEAISLAND:
    case GDT_HW_GENERATION_VOLCANICISLAND:
    case GDT_HW_GENERATION_GFX9:
    case GDT_HW_GENERATION_GFX10:
    case GDT_HW_GENERATION_GFX103:
    case GDT_HW_GENERATION_GFX11:
    case GDT_HW_GENERATION_INTEL:
    case GDT_HW_GENERATION_NVIDIA:
        break;

    default:
        status = kGpaStatusErrorHardwareNotSupported;
        break;
    }

    if (kGpaStatusOk == status)
    {
        status = GenerateDX12SoftwareCounters();

        if (kGpaStatusOk == status)
        {
            const size_t            dx12_sw_counter_count  = SwCounterManager::Instance()->GetNumSwCounters();
            const SwCounterDescVec* dx12_software_counters = SwCounterManager::Instance()->GetSwCounters();
            software_counters->software_counter_list_.resize(dx12_sw_counter_count);

            for (size_t ci = 0; dx12_sw_counter_count > ci; ++ci)
            {
                (software_counters->software_counter_list_)[ci].group_index     = 0;
                (software_counters->software_counter_list_)[ci].group_id_driver = static_cast<GpaUInt32>(ci);
                (software_counters->software_counter_list_)[ci].counter_id_driver =
                    static_cast<GpaUInt32>((*dx12_software_counters)[ci].counter_index_in_group);
                (software_counters->software_counter_list_)[ci].software_counter_desc = const_cast<GpaSoftwareCounterDesc*>(&((*dx12_software_counters)[ci]));
            }
        }
    }

    software_counters->counters_generated_ = true;

    return status;
}

void GpaCounterGeneratorDx12Base::ComputeSwCounterValue(GpaUInt32 counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const
{
    const SwCounterDescVec* sw_counters = SwCounterManager::Instance()->GetSwCounters();

    if (counter_index < static_cast<GpaUInt32>(sw_counters->size()))
    {
        const std::string kD3dGpuTime    = "D3DGPUTime";
        const std::string kPreTimeStamp  = "PreBottomTimestamp";
        const std::string kPostTimeStamp = "PostBottomTimestamp";
        const std::string counter_name   = sw_counters->at(counter_index).name;

        if (counter_name == kD3dGpuTime)
        {
            GpaUInt64 freq = 1u;
            GPA_ASSERT(hw_info->GetTimeStampFrequency(freq));
            GpaFloat64* pBuf = static_cast<GpaFloat64*>(result);
            *pBuf            = static_cast<GpaFloat64>(value) / static_cast<GpaFloat64>(freq) * 1000.0;
        }
        else if (counter_name == kPreTimeStamp || counter_name == kPostTimeStamp)
        {
            GpaUInt64 freq = 1u;
            GPA_ASSERT(hw_info->GetTimeStampFrequency(freq));
            GpaFloat64* buf = static_cast<GpaFloat64*>(result);
            *buf            = static_cast<GpaFloat64>(value * 1000.0) / freq;
        }
        else
        {
            // Other SW DX counters.
            GpaDataType type = (*sw_counters)[counter_index].type;

            if (kGpaDataTypeUint64 == type)
            {
                GpaUInt64* buf = static_cast<GpaUInt64*>(result);
                *buf           = static_cast<GpaUInt64>(value);
            }
            else if (kGpaDataTypeFloat64 == type)
            {
                memcpy(result, &value, sizeof(GpaFloat64));
            }
            else
            {
                GPA_LOG_ERROR("Unexpected software counter type.");
            }
        }
    }
}

GpaStatus GpaCounterGeneratorDx12Base::GenerateDX12SoftwareCounters() const
{
    GpaStatus result = kGpaStatusOk;

    SwCounterManager::Instance()->SetNumAmdCounters(GetNumAmdCounters());

    if (!SwCounterManager::Instance()->SwCountersGenerated())
    {
        for (size_t ci = 0; kDx12SoftwareCountersCount > ci; ++ci)
        {
            SwCounterManager::Instance()->AddSwCounter(kDx12SoftwareCounters[ci]);
        }

        if (0 == SwCounterManager::Instance()->GetNumSwCounters())
        {
            result = kGpaStatusErrorFailed;
        }

        SwCounterManager::Instance()->SetSwCountersGenerated(true);
    }

    return result;
}
