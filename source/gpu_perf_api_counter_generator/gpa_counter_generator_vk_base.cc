//==============================================================================
// Copyright (c) 2017-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"
#include "gpu_perf_api_counter_generator/gpa_sw_counter_manager.h"

const GpaSoftwareCounterDesc GpaCounterGeneratorVkBase::kVkSoftwareCounters[] = {
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP.
        2,
        "VKGPUTime",
        "VK",
        "Time spent in GPU",
        kGpaDataTypeFloat64,
    },
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP.
        2,
        "PreBottomTimestamp",
        "VK",
        "Bottom of the pipeline GPU timestamp",
        kGpaDataTypeFloat64,
    },
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP.
        2,
        "PostBottomTimestamp",
        "VK",
        "Bottom of the pipeline GPU timestamp",
        kGpaDataTypeFloat64,
    },
    {
        // GPA_VK_QUERY_TYPE_OCCLUSION (with PRECISE flag).
        0,
        "Occlusion",
        "VK",
        "Get the number of samples that passed the depth and stencil tests.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_OCCLUSION_BINARY (Occlusion, but without PRECISE flag).
        1,
        "BinaryOcclusion",
        "VK",
        "True/false if any samples passed depth and stencil tests.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS IAVertices.
        3,
        "IAVertices",
        "VK",
        "Number of vertices read by input assembler.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS IAPrimitives.
        3,
        "IAPrimitives",
        "VK",
        "Number of primitives read by the input assembler.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS VSInvocations.
        3,
        "VSInvocations",
        "VK",
        "Number of times a vertex shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS GSInvocations.
        3,
        "GSInvocations",
        "VK",
        "Number of times a geometry shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives.
        3,
        "GSPrimitives",
        "VK",
        "Number of primitives output by a geometry shader.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CInvocations.
        3,
        "CInvocations",
        "VK",
        "Number of primitives that were sent to the rasterizer.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CPrimitives.
        3,
        "CPrimitives",
        "VK",
        "Number of primitives that were rendered.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS PSInvocations.
        3,
        "PSInvocations",
        "VK",
        "Number of times a pixel shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS TCSInvocations.
        3,
        "TCSInvocations",
        "VK",
        "Number of times a tessellation control shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS TESInvocations.
        3,
        "TESInvocations",
        "VK",
        "Number of times a tessellation evaluation shader was invoked.",
        kGpaDataTypeUint64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CSInvocations.
        3,
        "CSInvocations",
        "VK",
        "Number of times a compute shader was invoked.",
        kGpaDataTypeUint64,
    },
};

const size_t GpaCounterGeneratorVkBase::kVkSoftwareCountersCount = (sizeof(kVkSoftwareCounters) / sizeof(GpaSoftwareCounterDesc));

bool GpaCounterGeneratorVkBase::GetSwCounterDesc(const GpaUInt32 sw_counter_index, GpaSoftwareCounterDesc& sw_counter_desc)
{
    if (sw_counter_index < kVkSoftwareCountersCount)
    {
        sw_counter_desc = kVkSoftwareCounters[sw_counter_index];
    }

    return sw_counter_index < kVkSoftwareCountersCount;
}

GpaStatus GpaCounterGeneratorVkBase::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
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

GpaStatus GpaCounterGeneratorVkBase::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
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

GpaStatus GpaCounterGeneratorVkBase::GenerateSoftwareCounters(GDT_HW_GENERATION    desiredGeneration,
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

    switch (desiredGeneration)
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
        status = GenerateVKSoftwareCounters();

        if (kGpaStatusOk == status)
        {
            const size_t            vk_sw_counter_count  = SwCounterManager::Instance()->GetNumSwCounters();
            const SwCounterDescVec* vk_software_counters = SwCounterManager::Instance()->GetSwCounters();
            software_counters->software_counter_list_.resize(vk_sw_counter_count);

            for (size_t ci = 0; vk_sw_counter_count > ci; ++ci)
            {
                (software_counters->software_counter_list_)[ci].group_index       = 0;
                (software_counters->software_counter_list_)[ci].group_id_driver   = static_cast<GpaUInt32>(ci);
                (software_counters->software_counter_list_)[ci].counter_id_driver = static_cast<GpaUInt32>((*vk_software_counters)[ci].counter_index_in_group);
                (software_counters->software_counter_list_)[ci].software_counter_desc = const_cast<GpaSoftwareCounterDesc*>(&((*vk_software_counters)[ci]));
            }
        }
    }

    software_counters->counters_generated_ = true;

    return status;
}

void GpaCounterGeneratorVkBase::ComputeSwCounterValue(GpaUInt32 counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const
{
    const SwCounterDescVec* sw_counters = SwCounterManager::Instance()->GetSwCounters();

    if (counter_index < static_cast<GpaUInt32>(sw_counters->size()))
    {
        const std::string kVkGpuTime     = "VKGPUTime";
        const std::string kPreTimeStamp  = "PreBottomTimestamp";
        const std::string kPostTimeStamp = "PostBottomTimestamp";
        const std::string counter_name   = sw_counters->at(counter_index).name;

        if (counter_name == kVkGpuTime)
        {
            GpaUInt64 freq = 1u;
            GPA_ASSERT(hw_info->GetTimeStampFrequency(freq));
            GpaFloat64* buf = static_cast<GpaFloat64*>(result);
            *buf            = static_cast<GpaFloat64>(value) / static_cast<GpaFloat64>(freq) * 1000.0;
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
            // Other SW VK counters.
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

GpaStatus GpaCounterGeneratorVkBase::GenerateVKSoftwareCounters()
{
    GpaStatus result = kGpaStatusOk;

    SwCounterManager::Instance()->SetNumAmdCounters(GetNumAmdCounters());

    if (!SwCounterManager::Instance()->SwCountersGenerated())
    {
        for (size_t ci = 0; kVkSoftwareCountersCount > ci; ++ci)
        {
            SwCounterManager::Instance()->AddSwCounter(kVkSoftwareCounters[ci]);
        }

        if (0 == SwCounterManager::Instance()->GetNumSwCounters())
        {
            result = kGpaStatusErrorFailed;
        }

        SwCounterManager::Instance()->SetSwCountersGenerated(true);
    }

    return result;
}
