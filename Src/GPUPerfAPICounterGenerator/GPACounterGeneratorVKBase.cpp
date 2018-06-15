//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for VK counter generation
//==============================================================================

#include "GPACounterGeneratorVKBase.h"
#include "GPACounterGeneratorSchedulerManager.h"

#include "GPASwCounterManager.h"
#include "GPACommonDefs.h"

const GPA_SoftwareCounterDesc GPA_CounterGeneratorVKBase::s_VKSWCounters[] =
{
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP
        2,
        "VKGPUTime",
        "VK",
        "Time spent in GPU",
        GPA_DATA_TYPE_FLOAT64,
    },
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP
        2,
        "PreBottomTimestamp",
        "VK",
        "Bottom of the pipeline GPU timestamp",
        GPA_DATA_TYPE_FLOAT64,
    },
    {
        // GPA_VK_QUERY_TYPE_TIMESTAMP
        2,
        "PostBottomTimestamp",
        "VK",
        "Bottom of the pipeline GPU timestamp",
        GPA_DATA_TYPE_FLOAT64,
    },
    {
        // GPA_VK_QUERY_TYPE_OCCLUSION (with PRECISE flag)
        0,
        "Occlusion",
        "VK",
        "Get the number of samples that passed the depth and stencil tests.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_OCCLUSION_BINARY (Occlusion, but without PRECISE flag)
        1,
        "BinaryOcclusion",
        "VK",
        "True/false if any samples passed depth and stencil tests.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS IAVertices
        3,
        "IAVertices",
        "VK",
        "Number of vertices read by input assembler.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS IAPrimitives
        3,
        "IAPrimitives",
        "VK",
        "Number of primitives read by the input assembler.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS VSInvocations
        3,
        "VSInvocations",
        "VK",
        "Number of times a vertex shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS GSInvocations
        3,
        "GSInvocations",
        "VK",
        "Number of times a geometry shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS GSPrimitives
        3,
        "GSPrimitives",
        "VK",
        "Number of primitives output by a geometry shader.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CInvocations
        3,
        "CInvocations",
        "VK",
        "Number of primitives that were sent to the rasterizer.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CPrimitives
        3,
        "CPrimitives",
        "VK",
        "Number of primitives that were rendered.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS PSInvocations
        3,
        "PSInvocations",
        "VK",
        "Number of times a pixel shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS TCSInvocations
        3,
        "TCSInvocations",
        "VK",
        "Number of times a tessellation control shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS TESInvocations
        3,
        "TESInvocations",
        "VK",
        "Number of times a tessellation evaluation shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
    {
        // GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS CSInvocations
        3,
        "CSInvocations",
        "VK",
        "Number of times a compute shader was invoked.",
        GPA_DATA_TYPE_UINT64,
    },
};

const size_t GPA_CounterGeneratorVKBase::s_VKSWCountersCount =
    (sizeof(s_VKSWCounters) / sizeof(GPA_SoftwareCounterDesc));


bool GPA_CounterGeneratorVKBase::GetSwCounterDesc(
    const gpa_uint32 swCounterIndex, GPA_SoftwareCounterDesc& swCounterDesc)
{
    bool result = (s_VKSWCountersCount >= swCounterIndex);

    if (result)
    {
        swCounterDesc = s_VKSWCounters[swCounterIndex];
    }

    return result;
}

GPA_Status GPA_CounterGeneratorVKBase::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_DerivedCounters* pPublicCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pPublicCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorVKBase::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pHardwareCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorVKBase::GenerateSoftwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    GPA_Status status = GPA_STATUS_OK;

    if (pSoftwareCounters->m_countersGenerated)
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
            status = GenerateVKSoftwareCounters();

            if (GPA_STATUS_OK == status)
            {
                const size_t VKSwCounterCount = SwCounterManager::Instance()->GetNumSwCounters();
                const SwCounterDescVec* pVKSoftwareCounters = SwCounterManager::Instance()->GetSwCounters();
                pSoftwareCounters->m_counters.resize(VKSwCounterCount);

                for (size_t ci = 0 ; VKSwCounterCount > ci ; ++ci)
                {
                    (pSoftwareCounters->m_counters)[ci].m_groupIndex = 0;
                    (pSoftwareCounters->m_counters)[ci].m_groupIdDriver = static_cast<gpa_uint32>(ci);
                    (pSoftwareCounters->m_counters)[ci].m_counterIdDriver =
                        static_cast<gpa_uint32>((*pVKSoftwareCounters)[ci].m_counterIndexInGroup);
                    (pSoftwareCounters->m_counters)[ci].m_pSoftwareCounter =
                        const_cast<GPA_SoftwareCounterDesc*>(&((*pVKSoftwareCounters)[ci]));
                }
            }
        }
    }

    pSoftwareCounters->m_countersGenerated = true;

    return status;
}

void GPA_CounterGeneratorVKBase::ComputeSWCounterValue(
    gpa_uint32 counterIndex, gpa_uint64 value, void* pResult, const GPA_HWInfo* pHwInfo) const
{
    const SwCounterDescVec* pSwCounters = SwCounterManager::Instance()->GetSwCounters();

    if (counterIndex < static_cast<gpa_uint32>(pSwCounters->size()))
    {
        const std::string VKGPUTime = "VKGPUTime";
        const std::string preTimeStamp = "PreBottomTimestamp";
        const std::string postTimeStamp = "PostBottomTimestamp";
        const std::string counterName = pSwCounters->at(counterIndex).m_name;

        if (counterName == VKGPUTime)
        {
            gpa_uint64 freq = 1u;
            GPA_ASSERT(pHwInfo->GetTimeStampFrequency(freq));
            gpa_float64* pBuf = static_cast<gpa_float64*>(pResult);
            *pBuf = static_cast<gpa_float64>(value) / static_cast<gpa_float64>(freq) * 1000.0;
        }
        else if (counterName == preTimeStamp || counterName == postTimeStamp)
        {
            gpa_uint64 freq = 1u;
            GPA_ASSERT(pHwInfo->GetTimeStampFrequency(freq));
            gpa_float64* pBuf = static_cast<gpa_float64*>(pResult);
            *pBuf = static_cast<gpa_float64>(value * 1000.0) / freq;
        }
        else // other SW VK counters
        {
            GPA_Data_Type type = (*pSwCounters)[counterIndex].m_type;

            if (GPA_DATA_TYPE_UINT64 == type)
            {
                gpa_uint64* pBuf = static_cast<gpa_uint64*>(pResult);
                *pBuf = static_cast<gpa_uint64>(value);
            }
            else if (GPA_DATA_TYPE_FLOAT64 == type)
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

GPA_Status GPA_CounterGeneratorVKBase::GenerateVKSoftwareCounters()
{
    GPA_Status result = GPA_STATUS_OK;

    SwCounterManager::Instance()->SetNumAmdCounters(GetNumAMDCounters());

    if (!SwCounterManager::Instance()->SwCountersGenerated())
    {
        for (size_t ci = 0; s_VKSWCountersCount > ci; ++ci)
        {
            SwCounterManager::Instance()->AddSwCounter(s_VKSWCounters[ci]);
        }

        if (0 == SwCounterManager::Instance()->GetNumSwCounters())
        {
            result = GPA_STATUS_ERROR_FAILED;
        }

        SwCounterManager::Instance()->SetSwCountersGenerated(true);
    }

    return result;
}

