//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX12 counter generation
//==============================================================================


/// \author GPU Developer Tools
/// \brief GPA_CounterGeneratorDX12 implementation

#include "GPACounterGeneratorDX12.h"
#include "GPACounterGeneratorSchedulerManager.h"

const GPA_SoftwareCounterDesc GPA_CounterGeneratorDX12::s_dx12SWCounters[] =
{
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "D3DGPUTime",
        "#D3D12#Time spent in GPU",
        GPA_TYPE_FLOAT64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "PreBottomTimestamp",
        "#D3D12#Bottom of the pipeline GPU timestamp",
        GPA_TYPE_FLOAT64,
    },
    {
        // D3D12_QUERY_TYPE_TIMESTAMP
        2,
        "PostBottomTimestamp",
        "#D3D12#Bottom of the pipeline GPU timestamp",
        GPA_TYPE_FLOAT64,
    },
    {
        // D3D12_QUERY_TYPE_OCCLUSION
        0,
        "Occlusion",
        "#D3D12#Get the number of samples that passed the depth and stencil tests.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_BINARY_OCCLUSION
        1,
        "BinaryOcclusion",
        "#D3D12#True/false if any samples passed depth and stencil tests.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAVertices
        3,
        "IAVertices",
        "#D3D12#Number of vertices read by input assembler.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS IAPrimitives
        3,
        "IAPrimitives",
        "#D3D12#Number of primitives read by the input assembler.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS VSInvocations
        3,
        "VSInvocations",
        "#D3D12#Number of times a vertex shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives
        3,
        "GSInvocations",
        "#D3D12#Number of times a geometry shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives
        3,
        "GSPrimitives",
        "#D3D12#Number of primitives output by a geometry shader.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CInvocations
        3,
        "CInvocations",
        "#D3D12#Number of primitives that were sent to the rasterizer.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CPrimitives
        3,
        "CPrimitives",
        "#D3D12#Number of primitives that were rendered.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS PSInvocations
        3,
        "PSInvocations",
        "#D3D12#Number of times a pixel shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS HSInvocations
        3,
        "HSInvocations",
        "#D3D12#Number of times a hull shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS DSInvocations
        3,
        "DSInvocations",
        "#D3D12#Number of times a domain shader was invoked.",
        GPA_TYPE_UINT64,
    },
    {
        // D3D12_QUERY_TYPE_PIPELINE_STATISTICS CSInvocations
        3,
        "CSInvocations",
        "#D3D12#Number of times a compute shader was invoked.",
        GPA_TYPE_UINT64,
    },
};

const size_t GPA_CounterGeneratorDX12::s_dx12SWCountersCount =
    (sizeof(s_dx12SWCounters) / sizeof(GPA_SoftwareCounterDesc));


bool GPA_CounterGeneratorDX12::GetSwCounterDesc(
    const gpa_uint32 swCounterIndex, GPA_SoftwareCounterDesc& counterDesc)
{
    bool result = (s_dx12SWCountersCount >= swCounterIndex);

    if (result)
    {
        counterDesc = s_dx12SWCounters[swCounterIndex];
    }

    return result;
} // end of GPA_CounterGeneratorDX12::GetSwCounterDesc

GPA_CounterGeneratorDX12::GPA_CounterGeneratorDX12()
    :
    GPA_CounterGeneratorBase()
{
    SetAllowedCounters(false, false, true); //enable sw counters

    for (int gen = GDT_HW_GENERATION_NVIDIA; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
} // end of GPA_CounterGeneratorDX12::GPA_CounterGeneratorDX12

GPA_CounterGeneratorDX12::~GPA_CounterGeneratorDX12()
{
} // end of GPA_CounterGeneratorDX12::~GPA_CounterGeneratorDX12

GPA_Status GPA_CounterGeneratorDX12::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pPublicCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        pPublicCounters->Clear();

        switch (desiredGeneration)
        {
            case GDT_HW_GENERATION_SOUTHERNISLAND:
            case GDT_HW_GENERATION_SEAISLAND:
            case GDT_HW_GENERATION_VOLCANICISLAND:
                break;

            default:
                status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                break;
        }
    }

    return status;
} // end of GPA_CounterGeneratorDX12::GeneratePublicCounters

GPA_Status GPA_CounterGeneratorDX12::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pHardwareCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        pHardwareCounters->Clear();

        switch (desiredGeneration)
        {
            case GDT_HW_GENERATION_SOUTHERNISLAND:
            case GDT_HW_GENERATION_SEAISLAND:
            case GDT_HW_GENERATION_VOLCANICISLAND:
                break;

            default:
                status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                break;
        }
    }

    return status;
} // end of GPA_CounterGeneratorDX12::GenerateHardwareCounters

GPA_Status GPA_CounterGeneratorDX12::GenerateSoftwareCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters)
{
    GPA_Status status = GPA_STATUS_OK;

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

    return status;
} // end of GPA_CounterGeneratorDX12::GenerateSoftwareCounters

void GPA_CounterGeneratorDX12::ComputeSWCounterValue(
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
                GPA_LogError("Unexpected software counter type");
            }
        }
    }
}

GPA_Status GPA_CounterGeneratorDX12::GenerateDX12SoftwareCounters()
{
    for (size_t ci = 0 ; s_dx12SWCountersCount > ci ; ++ci)
    {
        s_pSwCounterManager->GenerateSwCounter(s_dx12SWCounters[ci]);
    }

    GPA_Status result = GPA_STATUS_OK;

    if (0 == s_pSwCounterManager->GetNumSwCounters())
    {
        result = GPA_STATUS_ERROR_FAILED;
    }

    return result;
} // end of GPA_CounterGeneratorDX12::GenerateDX12SoftwareCounters

