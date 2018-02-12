//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware
//==============================================================================

#include <d3d11.h>

#ifdef EXTRA_COUNTER_INFO
    #include <sstream>
#endif

#include "GPACounterGeneratorDX11Base.h"
#include "Logging.h"

#include "GPASoftwareCounters.h"

#include "GPACounterGeneratorSchedulerManager.h"
#include "GPACommonDefs.h"

GPA_CounterGeneratorDX11Base::GPA_CounterGeneratorDX11Base()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(false, false, true); //enable sw counters
}

GPA_Status GPA_CounterGeneratorDX11Base::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_PublicCounters* pPublicCounters)
{
    // do nothing in base class
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pPublicCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX11Base::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_HardwareCounters* pHardwareCounters)
{
    // do nothing in base class
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pHardwareCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX11Base::GenerateSoftwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (pSoftwareCounters->m_countersGenerated)
    {
        return GPA_STATUS_OK;
    }

    pSoftwareCounters->Clear();
    GenerateD3DSoftwareCounters(desiredGeneration);
    pSoftwareCounters->m_groupCount = 1;
    m_d3dCounterGroup.m_numCounters = SwCounterManager::Instance()->GetNumSwCounters();
    m_d3dCounterGroup.m_maxActiveCounters = SwCounterManager::Instance()->GetNumSwCounters();
    pSoftwareCounters->m_pGroups = &m_d3dCounterGroup;

    GPA_SoftwareCounterDescExt counter;
    const SwCounterDescVec* pSwCounters = SwCounterManager::Instance()->GetSwCounters();

    for (gpa_uint32 c = 0; c < SwCounterManager::Instance()->GetNumSwCounters(); c++)
    {
        counter.m_groupIndex = 0;
        counter.m_groupIdDriver = GetD3D11Enum(c);

        // A D3D11_QUERY can return several values, we need to know the index into these values that the counter belongs to.
        // Re-purpose as the local index. This converts our counter index into a local index (if the counter happens to lie within an enum that has several values)
        counter.m_counterIdDriver = GetD3D11Enum(c);

        // assign the actual counter
        counter.m_pSoftwareCounter = const_cast<GPA_SoftwareCounterDesc*>(&((*pSwCounters)[c]));

        // add counter to the list
        pSoftwareCounters->m_counters.push_back(counter);
    }

    pSoftwareCounters->m_countersGenerated = true;

    return GPA_STATUS_OK;
}

void GPA_CounterGeneratorDX11Base::ComputeSWCounterValue(gpa_uint32 softwareCounterIndex,
                                                         gpa_uint64 value,
                                                         void* pResult,
                                                         const GPA_HWInfo* pHwInfo) const
{
    gpa_uint32 numAMDCounters = GetNumAMDCounters();

    if (softwareCounterIndex >= numAMDCounters)
    {
        softwareCounterIndex -= numAMDCounters;  //adjust index for AMD counters
    }

    const SwCounterDescVec* pSwCounters = SwCounterManager::Instance()->GetSwCounters();

    if (softwareCounterIndex < static_cast<gpa_uint32>(pSwCounters->size()))
    {
        const std::string nvGPUTime = "GPUTime";
        const std::string d3dGPUTime = "D3DGPUTime";
        const std::string counterName = pSwCounters->at(softwareCounterIndex).m_name;

        if (counterName == d3dGPUTime || counterName == nvGPUTime)
        {
            gpa_uint64 freq = 1u;
            GPA_ASSERT(pHwInfo->GetTimeStampFrequency(freq));
            gpa_float64* pBuf = static_cast<gpa_float64*>(pResult);
            *pBuf = static_cast<gpa_float64>(value) / static_cast<gpa_float64>(freq) * 1000.0;
        }
        else // other SW DX counters
        {
            GPA_Data_Type type = (*pSwCounters)[softwareCounterIndex].m_type;

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
                GPA_LogError("Unexpected software counter type");
            }
        }
    }
}

void GPA_CounterGeneratorDX11Base::GenerateD3DSoftwareCounters(GDT_HW_GENERATION desiredGeneration)
{
    GPA_SoftwareCounterDesc tempCounter;
    gpa_uint64 counterIndexInGroup = 0;
    tempCounter.m_counterIndexInGroup = 0;

    SwCounterManager::Instance()->SetNumAmdCounters(GetNumAMDCounters());

    if (SwCounterManager::Instance()->SwCountersGenerated())
    {
        return;
    }

    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Time spent in GPU");
    tempCounter.m_type = GPA_DATA_TYPE_FLOAT64;

    if (IsAMDGPU(desiredGeneration)) // AMD card
    {
        sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "D3DGPUTime");
    }
    else // non-AMD card
    {
        sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "GPUTime");
    }

    SwCounterManager::Instance()->AddSwCounter(tempCounter);  //GPUTime || D3DGPUTime

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Get the number of samples that passed the depth and stencil tests.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "Occlusion");
    tempCounter.m_type = GPA_DATA_TYPE_UINT64;
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //Occlusion

    //D3D11_QUERY_DATA_PIPELINE_STATISTICS description from http://msdn.microsoft.com/en-us/library/windows/desktop/ff476192%28v=vs.85%29.aspx

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of vertices read by input assembler.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "IAVertices");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //IAVertices

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives read by the input assembler.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "IAPrimitives");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //IAPrimitives

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a vertex shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "VSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //VSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a geometry shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "GSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //GSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives output by a geometry shader.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "GSPrimitives");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //GSPrimitives

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives that were sent to the rasterizer.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "CInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //CInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives that were rendered.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "CPrimitives");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //CPrimitives

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a pixel shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a hull shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "HSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //HSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a domain shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "DSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //DSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of times a compute shader was invoked.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "CSInvocations");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //CSInvocations

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Did any samples pass the depth and stencil tests?");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OcclusionPredicate");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //OcclusionPredicate

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream-output buffers.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsWritten");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsWritten

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Primitives not written to the SO buffers due to limited space.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsStorageNeed");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsStorageNeed

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Determines if any of the streaming output buffers overflowed.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OverflowPred");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);   //OverflowPred

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 0 buffer.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsWritten_S0");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsWritten_S0

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 0 due to limited space.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S0");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsStorageNeed_S0

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 0 buffer overflowed.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OverflowPred_S0");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //OverflowPred_S0

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 1 buffer.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsWritten_S1");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsWritten_S1

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 1 due to limited space.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S1");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsStorageNeed_S1

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 1 buffer overflowed.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OverflowPred_S1");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //OverflowPred_S1

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 2 buffer.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsWritten_S2");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsWritten_S2

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 2 due to limited space.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S2");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsStorageNeed_S2

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 2 buffer overflowed.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OverflowPred_S2");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //OverflowPred_S2

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Number of primitives written to the stream 3 buffer.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsWritten_S3");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsWritten_S3

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Primitives not written to stream 3 due to limited space.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "PrimsStorageNeed_S3");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //PrimsStorageNeed_S3

    tempCounter.m_counterIndexInGroup = counterIndexInGroup++;
    sprintf_s(tempCounter.m_group, maxSoftwareCounterGroupLength, "%s", "D3D11");
    sprintf_s(tempCounter.m_description, maxSoftwareCounterDescriptionLength, "%s", "Determines if the stream 3 buffer overflowed.");
    sprintf_s(tempCounter.m_name, maxSoftwareCounterNameLength, "%s", "OverflowPred_S3");
    SwCounterManager::Instance()->AddSwCounter(tempCounter);    //OverflowPred_S3
    SwCounterManager::Instance()->SetSwCountersGenerated(true);
}

gpa_uint32 GPA_CounterGeneratorDX11Base::GetD3D11Enum(gpa_uint32 index) const
{

    D3DCOUNTERS counterIndex = static_cast<D3DCOUNTERS>(index);

    switch (counterIndex)
    {
        case D3DCOUNTERS::GPUTIME:
            return static_cast<gpa_uint32>(D3D11_QUERY_TIMESTAMP);

        case D3DCOUNTERS::OCCLUSION:
            return static_cast<gpa_uint32>(D3D11_QUERY_OCCLUSION);

        case D3DCOUNTERS::IAVERTICES:
        case D3DCOUNTERS::IAPRIMITIVES:
        case D3DCOUNTERS::VSINVOCATIONS:
        case D3DCOUNTERS::GSINVOCATIONS:
        case D3DCOUNTERS::GSPRIMITIVES:
        case D3DCOUNTERS::CINVOCATIONS:
        case D3DCOUNTERS::CPRIMITIVES:
        case D3DCOUNTERS::PSINVOCATIONS:
        case D3DCOUNTERS::HSINVOCATIONS:
        case D3DCOUNTERS::DSINVOCATIONS:
        case D3DCOUNTERS::CSINVOCATIONS:
            return static_cast<gpa_uint32>(D3D11_QUERY_PIPELINE_STATISTICS);

        case D3DCOUNTERS::OCCLUSIONPREDICATE:
            return static_cast<gpa_uint32>(D3D11_QUERY_OCCLUSION_PREDICATE);

        /// D3D11_QUERY_SO_STATISTICS
        case D3DCOUNTERS::SOPRIMSWRITTEN:
        case D3DCOUNTERS::SOPRIMSSTORAGENEED:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_STATISTICS);

        case D3DCOUNTERS::SOOVERFLOWPRED:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE);

        /// D3D11_QUERY_SO_STATISTICS_STREAM0
        case D3DCOUNTERS::PRIMSWRITTEN_S0:
        case D3DCOUNTERS::PRIMSSTORAGENEED_S0:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_STATISTICS_STREAM0);

        case D3DCOUNTERS::OVERFLOWPRED_S0:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0);

        /// D3D11_QUERY_SO_STATISTICS_STREAM1
        case D3DCOUNTERS::PRIMSWRITTEN_S1:
        case D3DCOUNTERS::PRIMSSTORAGENEED_S1:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_STATISTICS_STREAM1);

        case D3DCOUNTERS::OVERFLOWPRED_S1:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1);

        /// D3D11_QUERY_SO_STATISTICS_STREAM2
        case D3DCOUNTERS::PRIMSWRITTEN_S2:
        case D3DCOUNTERS::PRIMSSTORAGENEED_S2:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_STATISTICS_STREAM2);

        case D3DCOUNTERS::OVERFLOWPRED_S2:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2);

        /// D3D11_QUERY_SO_STATISTICS_STREAM3
        case D3DCOUNTERS::PRIMSWRITTEN_S3:
        case D3DCOUNTERS::PRIMSSTORAGENEED_S3:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_STATISTICS_STREAM3);

        case D3DCOUNTERS::OVERFLOWPRED_S3:
            return static_cast<gpa_uint32>(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3);

        default:
            return static_cast<gpa_uint32>(0);
    }
}

bool GPA_CounterGeneratorDX11Base::IsAMDGPU(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}
