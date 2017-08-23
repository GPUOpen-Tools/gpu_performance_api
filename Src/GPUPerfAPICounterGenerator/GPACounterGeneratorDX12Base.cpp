//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Common DX12 counter generation
//==============================================================================

#include "GPACounterGeneratorDX12Base.h"
#include "GPACounterGeneratorSchedulerManager.h"


const GPA_SoftwareCounterDesc GPA_CounterGeneratorDX12Base::s_dx12SWCounters[] =
{
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "D3DGPUTime",
        "D3D12",
        "Time spent in GPU",
        GPA_TYPE_FLOAT64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "PreBottomTimestamp",
        "D3D12",
        "Bottom of the pipeline GPU timestamp",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "PostBottomTimestamp",
        "D3D12",
        "Bottom of the pipeline GPU timestamp",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_OCCLUSION
        0,
        "Occlusion",
        "D3D12",
        "Get the number of samples that passed the depth and stencil tests.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_BINARY_OCCLUSION
        1,
        "BinaryOcclusion",
        "D3D12",
        "True/false if any samples passed depth and stencil tests.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAVertices
        3,
        "IAVertices",
        "D3D12",
        "Number of vertices read by input assembler.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAPrimitives
        3,
        "IAPrimitives",
        "D3D12",
        "Number of primitives read by the input assembler.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS VSInvocations
        3,
        "VSInvocations",
        "D3D12",
        "Number of times a vertex shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives
        3,
        "GSInvocations",
        "D3D12",
        "Number of times a geometry shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives
        3,
        "GSPrimitives",
        "D3D12",
        "Number of primitives output by a geometry shader.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CInvocations
        3,
        "CInvocations",
        "D3D12",
        "Number of primitives that were sent to the rasterizer.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CPrimitives
        3,
        "CPrimitives",
        "D3D12",
        "Number of primitives that were rendered.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS PSInvocations
        3,
        "PSInvocations",
        "D3D12",
        "Number of times a pixel shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS HSInvocations
        3,
        "HSInvocations",
        "D3D12",
        "Number of times a hull shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS DSInvocations
        3,
        "DSInvocations",
        "D3D12",
        "Number of times a domain shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CSInvocations
        3,
        "CSInvocations",
        "D3D12",
        "Number of times a compute shader was invoked.",
        GPA_TYPE_UINT64,
    },
};

const size_t GPA_CounterGeneratorDX12Base::s_dx12SWCountersCount =
    (sizeof(s_dx12SWCounters) / sizeof(GPA_SoftwareCounterDesc));


bool GPA_CounterGeneratorDX12Base::GetSwCounterDesc(
    const gpa_uint32 swCounterIndex, GPA_SoftwareCounterDesc& counterDesc)
{
    bool result = (s_dx12SWCountersCount >= swCounterIndex);

    if (result)
    {
        counterDesc = s_dx12SWCounters[swCounterIndex];
    }

    return result;
}

GPA_CounterGeneratorDX12Base::~GPA_CounterGeneratorDX12Base()
{
}

GPA_Status GPA_CounterGeneratorDX12Base::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(pPublicCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX12Base::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(pHardwareCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX12Base::GenerateSoftwareCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters)
{
    GPA_Status status = GPA_STATUS_OK;

    if (true == pSoftwareCounters->m_countersGenerated)
    {
        return status;
    }

    if (nullptr == pSoftwareCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        switch (desiredGeneration)
        {
            case GDT_HW_GENERATION_SOUTHERNISLAND:
            case GDT_HW_GENERATION_SEAISLAND:
            case GDT_HW_GENERATION_VOLCANICISLAND:
            case GDT_HW_GENERATION_GFX9:
            case GDT_HW_GENERATION_INTEL:
            case GDT_HW_GENERATION_NVIDIA:
                break;

            default:
                status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                break;
        }

        if (GPA_STATUS_OK == status)
        {
            status = GenerateDX12SoftwareCounters();

            if (GPA_STATUS_OK == status)
            {
                const size_t dx12SwCounterCount = s_pSwCounterManager->GetNumSwCounters();
                const SwCounterDescVec* pDX12SoftwareCounters = s_pSwCounterManager->GetSwCounters();
                pSoftwareCounters->m_counters.resize(dx12SwCounterCount);

                for (size_t ci = 0 ; dx12SwCounterCount > ci ; ++ci)
                {
                    (pSoftwareCounters->m_counters)[ci].m_groupIndex = 0;
                    (pSoftwareCounters->m_counters)[ci].m_groupIdDriver = static_cast<gpa_uint32>(ci);
                    (pSoftwareCounters->m_counters)[ci].m_counterIdDriver =
                        static_cast<gpa_uint32>((*pDX12SoftwareCounters)[ci].m_counterIndexInGroup);
                    (pSoftwareCounters->m_counters)[ci].m_pSoftwareCounter =
                        const_cast<GPA_SoftwareCounterDesc*>(&((*pDX12SoftwareCounters)[ci]));
                }
            }
        }
    }

    pSoftwareCounters->m_countersGenerated = true;

    return status;
}

void GPA_CounterGeneratorDX12Base::ComputeSWCounterValue(
    gpa_uint32 counterIndex, gpa_uint64 value, void* pResult, GPA_HWInfo* pHwInfo)
{
    const SwCounterDescVec* pSwCounters = s_pSwCounterManager->GetSwCounters();

    if (counterIndex < static_cast<gpa_uint32>(pSwCounters->size()))
    {
        const std::string d3dGPUTime = "D3DGPUTime";
        const std::string preTimeStamp = "PreBottomTimestamp";
        const std::string postTimeStamp = "PostBottomTimestamp";
        const std::string counterName = pSwCounters->at(counterIndex).m_name;

        if (counterName == d3dGPUTime)
        {
            gpa_uint64 freq = pHwInfo->GetTimeStampFrequency();
            gpa_float64* pBuf = static_cast<gpa_float64*>(pResult);
            *pBuf = static_cast<gpa_float64>(value) / static_cast<gpa_float64>(freq) * 1000.0;
        }
        else if (counterName == preTimeStamp || counterName == postTimeStamp)
        {
            gpa_uint64 freq = pHwInfo->GetTimeStampFrequency();
            gpa_float64* pBuf = static_cast<gpa_float64*>(pResult);
            *pBuf = static_cast<gpa_float64>(value * 1000.0) / freq;
        }
        else // other SW DX counters
        {
            GPA_Type type = (*pSwCounters)[counterIndex].m_type;

            if (GPA_TYPE_UINT64 == type)
            {
                gpa_uint64* pBuf = static_cast<gpa_uint64*>(pResult);
                *pBuf = static_cast<gpa_uint64>(value);
            }
            else if (GPA_TYPE_FLOAT64 == type)
            {
                memcpy(pResult, &value, sizeof(gpa_float64));
            }
            else
            {
                GPA_LogError("Unexpected software counter type.");
            }
        }
    }
}

GPA_Status GPA_CounterGeneratorDX12Base::GenerateDX12SoftwareCounters()
{
    GPA_Status result = GPA_STATUS_OK;

    s_pSwCounterManager->SetNumAmdCounters(GetNumAMDCounters());

    if (!s_pSwCounterManager->SwCountersGenerated())
    {
        for (size_t ci = 0; s_dx12SWCountersCount > ci; ++ci)
        {
            s_pSwCounterManager->GenerateSwCounter(s_dx12SWCounters[ci]);
        }

        if (0 == s_pSwCounterManager->GetNumSwCounters())
        {
            result = GPA_STATUS_ERROR_FAILED;
        }

        s_pSwCounterManager->SetSwCountersGenerated(true);
    }

    return result;
}

