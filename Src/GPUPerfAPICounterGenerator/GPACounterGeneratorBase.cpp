//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class for counter generation
//==============================================================================

#if defined(WIN32)
    #include <windows.h>
#endif

#include "GPACounterGeneratorBase.h"

GPA_CounterGeneratorBase::GPA_CounterGeneratorBase()
    :   m_doAllowPublicCounters(false),
        m_doAllowHardwareCounters(false),
        m_doAllowSoftwareCounters(false)
{
}

GPA_CounterGeneratorBase::~GPA_CounterGeneratorBase()
{
}

void GPA_CounterGeneratorBase::SetAllowedCounters(bool bAllowPublicCounters, bool bAllowHardwareCounters, bool bAllowSoftwareCounters)
{
    m_doAllowPublicCounters = bAllowPublicCounters;

#ifdef AMDT_INTERNAL
    // Only allow HW counters for internal builds
    m_doAllowHardwareCounters = bAllowHardwareCounters;
#else
    UNREFERENCED_PARAMETER(bAllowHardwareCounters);
    // Force HW counters to OFF for non internal builds
    m_doAllowHardwareCounters = false;
#endif

    m_doAllowSoftwareCounters = bAllowSoftwareCounters;
}

GPA_Status GPA_CounterGeneratorBase::GenerateCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters)
{
    GPA_Status status = GPA_STATUS_ERROR_NOT_ENABLED;

    m_publicCounters.Clear();
    m_hardwareCounters.Clear();
    m_softwareCounters.Clear();

    if (m_doAllowPublicCounters)
    {
        status = GeneratePublicCounters(desiredGeneration, asicType, generateAsicSpecificCounters, &m_publicCounters);

        if (status != GPA_STATUS_OK)
        {
            return status;
        }
    }

    if (m_doAllowPublicCounters || m_doAllowHardwareCounters) // hw counters are required if generating public counters
    {
        status = GenerateHardwareCounters(desiredGeneration, asicType, generateAsicSpecificCounters, &m_hardwareCounters);

        if (status != GPA_STATUS_OK)
        {
            return status;
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        status = GenerateSoftwareCounters(desiredGeneration, asicType, generateAsicSpecificCounters, &m_softwareCounters);

        if (status != GPA_STATUS_OK)
        {
            return status;
        }
    }

    if (0 == GetNumCounters())
    {
        // no counters reported, return hardware not supported
        status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return status;
}

gpa_uint32 GPA_CounterGeneratorBase::GetNumCounters() const
{
    gpa_uint32 count = 0;

    if (m_doAllowPublicCounters)
    {
        count += m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        count += m_hardwareCounters.GetNumCounters();
    }

    if (m_doAllowSoftwareCounters)
    {
        count += m_softwareCounters.GetNumCounters();
    }

    return count;
}

gpa_uint32 GPA_CounterGeneratorBase::GetNumAMDCounters() const //to be used for SW D3D counters for AMD
{
    gpa_uint32 count = 0;

    if (m_doAllowPublicCounters)
    {
        count += m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        count += m_hardwareCounters.GetNumCounters();
    }

    return count;
}

const char* GPA_CounterGeneratorBase::GetCounterName(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterName(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterName(index);
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return m_softwareCounters.GetCounterName(index);
        }
    }

    return nullptr;
}

bool GPA_CounterGeneratorBase::GetCounterIndex(const char* pName, gpa_uint32* pIndex) const
{

    bool retVal = false;

    if (nullptr != pIndex)
    {
        CounterNameIndexMap::const_iterator it = m_counterIndexCache.find(pName);

        if (m_counterIndexCache.end() != it)
        {
            *pIndex = m_counterIndexCache[pName];
            retVal = ms_COUNTER_NOT_FOUND != *pIndex;
        }
    }

    if (!retVal)
    {
        gpa_uint32 numCounters = GetNumCounters();

        for (gpa_uint32 i = 0; i < numCounters; i++)
        {
            const char* pCounterName = GetCounterName(i);

            if (0 == _strcmpi(pName, pCounterName))
            {
                m_counterIndexCache[pName] = i;
                *pIndex = i;
                retVal = true;
                break;
            }
        }
    }

    if (!retVal)
    {
        // cache the fact that it wasn't found
        m_counterIndexCache[pName] = ms_COUNTER_NOT_FOUND;
    }

    return retVal;

}

const char* GPA_CounterGeneratorBase::GetCounterGroup(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterGroup(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterGroup(index);
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return m_softwareCounters.GetCounterGroup(index);
        }
    }

    return nullptr;
}

const char* GPA_CounterGeneratorBase::GetCounterDescription(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterDescription(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterDescription(index);
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return m_softwareCounters.GetCounterDescription(index);
        }
    }

    return nullptr;
}

GPA_Data_Type GPA_CounterGeneratorBase::GetCounterDataType(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterDataType(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // hardware counters are always 'uint64'
            return GPA_DATA_TYPE_UINT64;
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        GPA_Data_Type type = GPA_DATA_TYPE_UINT64;

        if (SwCounterManager::Instance()->SwCounterEnabled())
        {
            if (index >= GetNumAMDCounters())
            {
                index -= GetNumAMDCounters();
            }
        }

        if (index < m_softwareCounters.GetNumCounters())
        {
            type = m_softwareCounters.GetCounterType(index);
        }

        return type;
    } // m_bAllowSoftwareCounters

    return GPA_DATA_TYPE_UINT64;
}

GPA_Usage_Type GPA_CounterGeneratorBase::GetCounterUsageType(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterUsageType(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // hardware counters are always considered 'items'
            return GPA_USAGE_TYPE_ITEMS;
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (SwCounterManager::Instance()->SwCounterEnabled())
        {
            if (index >= GetNumAMDCounters())
            {
                index -= GetNumAMDCounters();
            }
        }

        if (0 == index)  //SW GPUTime counter
        {
            return GPA_USAGE_TYPE_MILLISECONDS;
        }

        return GPA_USAGE_TYPE_ITEMS;
    }

    return GPA_USAGE_TYPE_ITEMS;
}

GPA_UUID GPA_CounterGeneratorBase::GetCounterUuid(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterUuid(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterUuid(index);
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return m_softwareCounters.GetCounterUuid(index);
        }
    }

    return GPA_UUID{};
}


const GPA_PublicCounter* GPA_CounterGeneratorBase::GetPublicCounter(gpa_uint32 index) const
{
    return m_publicCounters.GetCounter(index);
}

const GPA_HardwareCounterDescExt* GPA_CounterGeneratorBase::GetHardwareCounterExt(gpa_uint32 index) const
{
    return &(m_hardwareCounters.m_counters[index]);
}

gpa_uint32 GPA_CounterGeneratorBase::GetNumPublicCounters() const
{
    gpa_uint32 count = 0;

    if (m_doAllowPublicCounters)
    {
        count += m_publicCounters.GetNumCounters();
    }

    return count;
}

std::vector<gpa_uint32> GPA_CounterGeneratorBase::GetInternalCountersRequired(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetInternalCountersRequired(index);
        }
        else
        {
            index -= m_publicCounters.GetNumCounters();
        }
    }

    std::vector<gpa_uint32> vecInternalCounters;

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // the index is now the same as the needed hardware counter
            vecInternalCounters.push_back(index);
            return vecInternalCounters;
        }
        else
        {
            index -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            // the index is now the same as the needed hardware counter
            vecInternalCounters.push_back(index + m_hardwareCounters.GetNumCounters());
        }
        else
        {
            index -= m_softwareCounters.GetNumCounters();
        }
    }

    return vecInternalCounters;
}

void GPA_CounterGeneratorBase::ComputePublicCounterValue(gpa_uint32 counterIndex, vector<gpa_uint64*>& results, vector<GPA_Data_Type>& internalCounterTypes, void* pResult, const GPA_HWInfo* pHwInfo) const
{
    m_publicCounters.ComputeCounterValue(counterIndex, results, internalCounterTypes, pResult, pHwInfo);
}

void GPA_CounterGeneratorBase::ComputeSWCounterValue(gpa_uint32 counterIndex,
    gpa_uint64 value,
    void* pResult,
    const GPA_HWInfo* pHwInfo) const
{
    UNREFERENCED_PARAMETER(counterIndex);
    UNREFERENCED_PARAMETER(pHwInfo);

    if (nullptr != pResult)
    {
        gpa_uint64* pValue = static_cast<gpa_uint64*>(pResult);
        *pValue = value;
    }
}

const GPA_HardwareCounters* GPA_CounterGeneratorBase::GetHardwareCounters() const
{
    return &m_hardwareCounters;
}

const GPA_SoftwareCounters* GPA_CounterGeneratorBase::GetSoftwareCounters() const
{
    return &m_softwareCounters;
}

GPACounterSourceInfo GPA_CounterGeneratorBase::GetCounterSourceInfo(gpa_uint32 globalIndex) const
{
    if (m_doAllowPublicCounters)
    {
        if (globalIndex < m_publicCounters.GetNumCounters())
        {
            GPACounterSourceInfo info;
            info.Set(globalIndex, GPACounterSource::PUBLIC);
            return info;
        }
        else
        {
            globalIndex -= m_publicCounters.GetNumCounters();
        }
    }

    if (m_doAllowHardwareCounters)
    {
        if (globalIndex < m_hardwareCounters.GetNumCounters())
        {
            GPACounterSourceInfo info;
            info.Set(globalIndex, GPACounterSource::HARDWARE);
            return info;
        }
        else
        {
            globalIndex -= m_hardwareCounters.GetNumCounters();
        }
    }

    if (m_doAllowSoftwareCounters)
    {
        GPACounterSourceInfo info;
        info.Set(globalIndex, GPACounterSource::SOFTWARE);
        return info;
    }

    /// Unknown counter
    GPACounterSourceInfo info;
    info.Set(globalIndex, GPACounterSource::UNKNOWN);
    return info;
}
