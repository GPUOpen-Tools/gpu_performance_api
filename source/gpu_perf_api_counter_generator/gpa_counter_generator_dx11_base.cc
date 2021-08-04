//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11_base.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include <d3d11.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"
#include "gpu_perf_api_counter_generator/gpa_software_counters.h"

GpaCounterGeneratorDx11Base::GpaCounterGeneratorDx11Base()
{
    // Enable sw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(false, false, true);
}

GpaStatus GpaCounterGeneratorDx11Base::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                              GDT_HW_ASIC_TYPE    asic_type,
                                                              GpaUInt8            generate_asic_specific_counters,
                                                              GpaDerivedCounters* public_counters)
{
    // Do nothing in base class.
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx11Base::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                                GDT_HW_ASIC_TYPE     asic_type,
                                                                GpaUInt8             generate_asic_specific_counters,
                                                                GpaHardwareCounters* hardware_counters)
{
    // Do nothing in base class.
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx11Base::GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                                                GDT_HW_ASIC_TYPE     asic_type,
                                                                GpaUInt8             generate_asic_specific_counters,
                                                                GpaSoftwareCounters* software_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (software_counters->counters_generated_)
    {
        return kGpaStatusOk;
    }

    software_counters->Clear();
    GenerateD3DSoftwareCounters(desired_generation);
    software_counters->group_count_                 = 1;
    d3d_counter_group_.num_counters                 = SwCounterManager::Instance()->GetNumSwCounters();
    d3d_counter_group_.max_active_discrete_counters = SwCounterManager::Instance()->GetNumSwCounters();
    d3d_counter_group_.max_active_spm_counters      = 0;
    software_counters->counter_group_desc_          = &d3d_counter_group_;

    GpaSoftwareCounterDescExt counter;
    const SwCounterDescVec*   sw_counters = SwCounterManager::Instance()->GetSwCounters();

    for (GpaUInt32 c = 0; c < SwCounterManager::Instance()->GetNumSwCounters(); c++)
    {
        counter.group_index     = 0;
        counter.group_id_driver = GetD3D11Enum(c);

        // A D3D11_QUERY can return several values, we need to know the index into these values that the counter belongs to.
        // Re-purpose as the local index. This converts our counter index into a local index (if the counter happens to lie within an enum that has several values).
        counter.counter_id_driver = GetD3D11Enum(c);

        // Assign the actual counter.
        counter.software_counter_desc = const_cast<GpaSoftwareCounterDesc*>(&((*sw_counters)[c]));

        // Add counter to the list.
        software_counters->software_counter_list_.push_back(counter);
    }

    software_counters->counters_generated_ = true;

    return kGpaStatusOk;
}

void GpaCounterGeneratorDx11Base::ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const
{
    GpaUInt32 num_amd_counters = GetNumAmdCounters();

    if (software_counter_index >= num_amd_counters)
    {
        // Adjust index for AMD counters.
        software_counter_index -= num_amd_counters;
    }

    const SwCounterDescVec* sw_counters = SwCounterManager::Instance()->GetSwCounters();

    if (software_counter_index < static_cast<GpaUInt32>(sw_counters->size()))
    {
        const std::string kNvGpuTime   = "GPUTime";
        const std::string kD3dGpuTime  = "D3DGPUTime";
        const std::string counter_name = sw_counters->at(software_counter_index).name;

        if (counter_name == kD3dGpuTime || counter_name == kNvGpuTime)
        {
            GpaUInt64 freq = 1u;
            GPA_ASSERT(hw_info->GetTimeStampFrequency(freq));
            GpaFloat64* buf = static_cast<GpaFloat64*>(result);
            *buf            = static_cast<GpaFloat64>(value) / static_cast<GpaFloat64>(freq) * 1000.0;
        }
        else
        {
            // Other SW DX counters.
            GpaDataType type = (*sw_counters)[software_counter_index].type;

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

void GpaCounterGeneratorDx11Base::GenerateD3DSoftwareCounters(GDT_HW_GENERATION desired_generation)
{
    GpaSoftwareCounterDesc temp_counter;
    GpaUInt64              counter_index_in_group = 0;
    temp_counter.counter_index_in_group           = 0;

    SwCounterManager::Instance()->SetNumAmdCounters(GetNumAmdCounters());

    if (SwCounterManager::Instance()->SwCountersGenerated())
    {
        return;
    }

    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Time spent in GPU");
    temp_counter.type = kGpaDataTypeFloat64;

    if (IsAmdGpu(desired_generation))
    {
        sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "D3DGPUTime");
    }
    else
    {
        // Non-AMD card.
        sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "GPUTime");
    }

    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // GPUTime || D3DGPUTime.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Get the number of samples that passed the depth and stencil tests.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "Occlusion");
    temp_counter.type = kGpaDataTypeUint64;
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // Occlusion.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of vertices read by input assembler.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "IAVertices");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // IAVertices.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives read by the input assembler.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "IAPrimitives");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // IAPrimitives.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a vertex shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "VSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // VSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a geometry shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "GSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // GSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives output by a geometry shader.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "GSPrimitives");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // GSPrimitives.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives that were sent to the rasterizer.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "CInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // CInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives that were rendered.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "CPrimitives");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // CPrimitives.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a pixel shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a hull shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "HSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // HSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a domain shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "DSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // DSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of times a compute shader was invoked.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "CSInvocations");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // CSInvocations.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Did any samples pass the depth and stencil tests?");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OcclusionPredicate");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OcclusionPredicate.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream-output buffers.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsWritten");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsWritten.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Primitives not written to the SO buffers due to limited space.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsStorageNeed");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsStorageNeed.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Determines if any of the streaming output buffers overflowed.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OverflowPred");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OverflowPred.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 0 buffer.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsWritten_S0");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsWritten_S0.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 0 due to limited space.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S0");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsStorageNeed_S0.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 0 buffer overflowed.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OverflowPred_S0");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OverflowPred_S0.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 1 buffer.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsWritten_S1");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsWritten_S1.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 1 due to limited space.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S1");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsStorageNeed_S1.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 1 buffer overflowed.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OverflowPred_S1");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OverflowPred_S1.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 2 buffer.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsWritten_S2");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsWritten_S2.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 2 due to limited space.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S2");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsStorageNeed_S2.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 2 buffer overflowed.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OverflowPred_S2");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OverflowPred_S2.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 3 buffer.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsWritten_S3");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsWritten_S3.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 3 due to limited space.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S3");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // PrimsStorageNeed_S3.

    temp_counter.counter_index_in_group = counter_index_in_group++;
    sprintf_s(temp_counter.group, kMaxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(temp_counter.description, kMaxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 3 buffer overflowed.");
    sprintf_s(temp_counter.name, kMaxSoftwareCounterNameLength, "%s", "OverflowPred_S3");
    SwCounterManager::Instance()->AddSwCounter(temp_counter);  // OverflowPred_S3.
    SwCounterManager::Instance()->SetSwCountersGenerated(true);
}

GpaUInt32 GpaCounterGeneratorDx11Base::GetD3D11Enum(GpaUInt32 index) const
{
    D3DCounters counter_index = static_cast<D3DCounters>(index);

    switch (counter_index)
    {
    case D3DCounters::kGpuTime:
        return static_cast<GpaUInt32>(D3D11_QUERY_TIMESTAMP);

    case D3DCounters::kOcclusion:
        return static_cast<GpaUInt32>(D3D11_QUERY_OCCLUSION);

    case D3DCounters::kIaVertices:
    case D3DCounters::kIaPrimitives:
    case D3DCounters::kVsInvocations:
    case D3DCounters::kGsInvocations:
    case D3DCounters::kGsPrimitives:
    case D3DCounters::kCInvocations:
    case D3DCounters::kCPrimitives:
    case D3DCounters::kPsInvocations:
    case D3DCounters::kHsInvocations:
    case D3DCounters::kDsInvocations:
    case D3DCounters::kCsInvocations:
        return static_cast<GpaUInt32>(D3D11_QUERY_PIPELINE_STATISTICS);

    case D3DCounters::kOcclusionPredicate:
        return static_cast<GpaUInt32>(D3D11_QUERY_OCCLUSION_PREDICATE);

    /// D3D11_QUERY_SO_STATISTICS.
    case D3DCounters::kSoPrimsWritten:
    case D3DCounters::kSoPrimsStorageNeed:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_STATISTICS);

    case D3DCounters::kSoOverFlowPred:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE);

    /// D3D11_QUERY_SO_STATISTICS_STREAM0.
    case D3DCounters::kPrimsWrittenS0:
    case D3DCounters::kPrimsStorageNeedS0:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_STATISTICS_STREAM0);

    case D3DCounters::kOverFlowPredS0:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0);

    /// D3D11_QUERY_SO_STATISTICS_STREAM1.
    case D3DCounters::kPrimsWrittenS1:
    case D3DCounters::kPrimsStorageNeedS1:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_STATISTICS_STREAM1);

    case D3DCounters::kOverFlowPredS1:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1);

    /// D3D11_QUERY_SO_STATISTICS_STREAM2.
    case D3DCounters::kPrimsWrittenS2:
    case D3DCounters::kPrimsStorageNeedS2:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_STATISTICS_STREAM2);

    case D3DCounters::kOverFlowPredS2:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2);

    /// D3D11_QUERY_SO_STATISTICS_STREAM3.
    case D3DCounters::kPrimsWrittenS3:
    case D3DCounters::kPrimsStorageNeedS3:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_STATISTICS_STREAM3);

    case D3DCounters::kOverFlowPredS3:
        return static_cast<GpaUInt32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3);

    default:
        return static_cast<GpaUInt32>(0);
    }
}

bool GpaCounterGeneratorDx11Base::IsAmdGpu(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}
