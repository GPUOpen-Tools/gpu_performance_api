//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class for counter generation
//==============================================================================

#include "GPACounterGeneratorBase.h"

GPA_CounterGeneratorBase::GPA_CounterGeneratorBase()
    : m_doAllowPublicCounters(false)
    , m_doAllowHardwareCounters(false)
    , m_doAllowSoftwareCounters(false)
    , m_doAllowHardwareExposedCounters(false)
{
}

void GPA_CounterGeneratorBase::SetAllowedCounters(bool bAllowPublicCounters, bool bAllowHardwareCounters, bool bAllowSoftwareCounters)
{
    m_doAllowPublicCounters = bAllowPublicCounters;

#ifdef AMDT_INTERNAL
    // Only allow HW counters for internal builds
    m_doAllowHardwareCounters        = bAllowHardwareCounters;
    m_doAllowHardwareExposedCounters = false;
#else
    UNREFERENCED_PARAMETER(bAllowHardwareCounters);
    // Force HW counters to OFF for non internal builds
    m_doAllowHardwareCounters        = false;
    m_doAllowHardwareExposedCounters = bAllowHardwareCounters;
#endif

    m_doAllowSoftwareCounters = bAllowSoftwareCounters;
}

GPA_Status GPA_CounterGeneratorBase::GenerateCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, gpa_uint8 generateAsicSpecificCounters)
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

    if (m_doAllowPublicCounters || m_doAllowHardwareCounters)  // hw counters are required if generating public counters
    {
        status = GenerateHardwareCounters(desiredGeneration, asicType, generateAsicSpecificCounters, &m_hardwareCounters);

        if (status != GPA_STATUS_OK)
        {
            return status;
        }
    }

    if (!m_doAllowHardwareCounters && m_doAllowHardwareExposedCounters)
    {
        status = GenerateHardwareExposedCounters(desiredGeneration, asicType, generateAsicSpecificCounters, &m_hardwareCounters);

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
    else if (m_doAllowHardwareExposedCounters)
    {
        count += m_hardwareCounters.GetNumHardwareExposedCounters();
    }

    if (m_doAllowSoftwareCounters)
    {
        count += m_softwareCounters.GetNumCounters();
    }

    return count;
}

gpa_uint32 GPA_CounterGeneratorBase::GetNumAMDCounters() const  //to be used for SW D3D counters for AMD
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
    else if (m_doAllowHardwareExposedCounters)
    {
        count += m_hardwareCounters.GetNumHardwareExposedCounters();
    }

    return count;
}

GPA_Status GPA_CounterGeneratorBase::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
                                                                     GDT_HW_ASIC_TYPE      asicType,
                                                                     gpa_uint8             generateAsicSpecificCounters,
                                                                     GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pHardwareCounters);
    return GPA_STATUS_OK;
}

bool GPA_CounterGeneratorBase::MapHardwareExposedCounter(GPA_HardwareCounters* pHardwareCounters)
{
    bool success = true;

    if (nullptr == pHardwareCounters)
    {
        return !success;
    }

    pHardwareCounters->m_hardwareExposedCounters.clear();
    for (unsigned int g = 0; g < pHardwareCounters->m_hardwareExposedCounterGroupCount; g++)
    {
        const gpa_uint32 blockCounterStartIndex = pHardwareCounters->m_pHardwareExposedCounterGroups[g].m_hardwareBlockStartIndex;

        unsigned int countIter = 0;
        for (auto iter = pHardwareCounters->m_pHardwareExposedCounterGroups[g].m_whiteListCounters.cbegin();
             iter != pHardwareCounters->m_pHardwareExposedCounterGroups[g].m_whiteListCounters.cend();
             ++iter)
        {
            GPA_HardwareCounterDesc* pWhitelistCounter = pHardwareCounters->m_ppHardwareExposedCounter[g] + countIter;
            pHardwareCounters->m_hardwareExposedCounters.push_back(*pWhitelistCounter);
            pHardwareCounters->m_hardwareExposedCounterInternalIndices.push_back(blockCounterStartIndex + (*iter));
            pHardwareCounters->m_counters[blockCounterStartIndex + (*iter)].m_pHardwareCounter = pWhitelistCounter;
            countIter++;
        }
    }

    return success;
}

const char* GPA_CounterGeneratorBase::GetCounterName(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterName(index);
        }

        index -= m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterName(index);
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return m_hardwareCounters.GetHardwareExposedCounterName(index);
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

#ifdef AMDT_INTERNAL
bool GPA_CounterGeneratorBase::SetCounterName(gpa_uint32 index, const char* pName)
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return false;  // not allowed to change name of derived counters
        }

        index -= m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.SetCounterName(index, pName);
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return false;  // not allowed to change name of exposed hardware counters
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return false;  // not allowed to change name of derived counters
        }
    }

    return false;
}
#endif

bool GPA_CounterGeneratorBase::GetCounterIndex(const char* pName, gpa_uint32* pIndex) const
{
    bool retVal              = false;
    bool counterFoundInCache = false;

    if (nullptr == pIndex)
    {
        return false;
    }

    CounterNameIndexMap::const_iterator it = m_counterIndexCache.find(pName);

    if (m_counterIndexCache.end() != it)
    {
        *pIndex             = m_counterIndexCache[pName];
        counterFoundInCache = true;
        retVal              = ms_COUNTER_NOT_FOUND != *pIndex;
    }

    if (!counterFoundInCache)
    {
        gpa_uint32 numCounters = GetNumCounters();

        for (gpa_uint32 i = 0; i < numCounters; i++)
        {
            const char* pCounterName = GetCounterName(i);

            if (0 == _strcmpi(pName, pCounterName))
            {
                m_counterIndexCache[pName] = i;
                *pIndex                    = i;
                retVal                     = true;
                break;
            }
        }

#ifdef AMDT_INTERNAL
        if (!retVal)
        {
            std::vector<std::string> tokens;
            std::string              token;
            const char*              pLocalName = pName;

            // first tokenize the input string on the ':' delimiter
            while (*pLocalName != '\0')
            {
                if (*pLocalName == ':' && !token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                else
                {
                    token.push_back(*pLocalName);
                }

                pLocalName++;
            }

            // add the trailing token to the list
            if (!token.empty())
            {
                tokens.push_back(token);
            }

            // valid strings must have 3 or 4 tokens: block, instance, eventid, alternate_name
            // "alternate_name" is optional
            if (3 == tokens.size() || 4 == tokens.size())
            {
                std::string gpaGroupName = tokens[0] + tokens[1];
                std::string gpaGroupNameAlt;
                bool        checkAltGroupName = false;

                // special case instance 0 -- in cases where a block is single-instance,
                // the GPA name for the block won't have '0' appended to it. We need to
                // account for that situation here
                if ("0" == tokens[1])
                {
                    gpaGroupNameAlt   = tokens[0];
                    checkAltGroupName = true;
                }

                for (gpa_uint32 i = m_publicCounters.GetNumCounters(); i < numCounters; i++)
                {
                    const char* pCounterGroup = GetCounterGroup(i);

                    if (nullptr != pCounterGroup)
                    {
                        bool groupNameFound    = false;
                        bool altGroupNameFound = false;

                        groupNameFound = (0 == _strcmpi(gpaGroupName.c_str(), pCounterGroup));

                        if (!groupNameFound && checkAltGroupName)
                        {
                            groupNameFound = (0 == _strcmpi(gpaGroupNameAlt.c_str(), pCounterGroup));

                            if (groupNameFound)
                            {
                                altGroupNameFound = true;
                            }
                        }

                        if (groupNameFound)
                        {
                            // this is the specified block, now just index to the specified event id
                            gpa_uint32 counterIndex = i + atoi(tokens[2].c_str());

                            if (4 <= tokens.size())
                            {
                                // if user is asking for an alternate name, set the name so that subsequent calls to GetCounterName will return the modified name
                                // it's not ideal casting away constness here, but it is required since we're in a const function
                                // (we don't want to change that since this is only used in internal builds)
                                const_cast<GPA_CounterGeneratorBase*>(this)->SetCounterName(counterIndex, tokens[3].c_str());
                            }

                            pCounterGroup = GetCounterGroup(counterIndex);

                            // make sure the specified index is still in the specified block
                            if (nullptr != pCounterGroup)
                            {
                                bool correctGroupName = false;

                                if (altGroupNameFound)
                                {
                                    correctGroupName = (0 == _strcmpi(gpaGroupNameAlt.c_str(), pCounterGroup));
                                }
                                else
                                {
                                    correctGroupName = (0 == _strcmpi(gpaGroupName.c_str(), pCounterGroup));
                                }

                                if (correctGroupName)
                                {
                                    m_counterIndexCache[pName] = counterIndex;
                                    *pIndex                    = counterIndex;
                                    retVal                     = true;
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }
#endif

        if (!retVal)
        {
            // cache the fact that it wasn't found
            m_counterIndexCache[pName] = ms_COUNTER_NOT_FOUND;
        }
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

        index -= m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            return m_hardwareCounters.GetCounterGroup(index);
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return m_hardwareCounters.GetHardwareExposedCounterGroup(index);
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return m_hardwareCounters.GetHardwareExposedCounterDescription(index);
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

        index -= m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // hardware counters are always 'uint64'
            return GPA_DATA_TYPE_UINT64;
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // hardware counters are always 'uint64'
            return GPA_DATA_TYPE_UINT64;
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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
    }  // m_bAllowSoftwareCounters

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
            // hardware counters are always 'uint64'
            return GPA_USAGE_TYPE_ITEMS;
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumCounters())
        {
            // hardware counters are always 'uint64'
            return GPA_USAGE_TYPE_ITEMS;
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return m_hardwareCounters.GetHardwareExposedCounterUuid(index);
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

GPA_Counter_Sample_Type GPA_CounterGeneratorBase::GetCounterSampleType(gpa_uint32 index) const
{
    if (m_doAllowPublicCounters)
    {
        if (index < m_publicCounters.GetNumCounters())
        {
            return m_publicCounters.GetCounterSampleType(index);
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
            return m_hardwareCounters.GetCounterSampleType(index);
        }

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            return m_hardwareCounters.GetHardwareExposedCounterSampleType(index);
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
    }

    if (m_doAllowSoftwareCounters)
    {
        if (index < m_softwareCounters.GetNumCounters())
        {
            return m_softwareCounters.GetCounterSampleType(index);
        }
    }

    return GPA_COUNTER_SAMPLE_TYPE_DISCRETE;
}

const GPA_DerivedCounter* GPA_CounterGeneratorBase::GetPublicCounter(gpa_uint32 index) const
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

        index -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (index < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            // the index is now the same as the needed hardware counter
            vecInternalCounters.push_back(m_hardwareCounters.GetHardwareExposedCounterInternalIndex(index));
            return vecInternalCounters;
        }

        index -= m_hardwareCounters.GetNumHardwareExposedCounters();
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

GPA_Status GPA_CounterGeneratorBase::ComputePublicCounterValue(gpa_uint32                       counterIndex,
                                                               const vector<const gpa_uint64*>& results,
                                                               vector<GPA_Data_Type>&           internalCounterTypes,
                                                               void*                            pResult,
                                                               const GPA_HWInfo*                pHwInfo) const
{
    return m_publicCounters.ComputeCounterValue(counterIndex, results, internalCounterTypes, pResult, pHwInfo);
}

void GPA_CounterGeneratorBase::ComputeSWCounterValue(gpa_uint32 softwareCounterIndex, gpa_uint64 value, void* pResult, const GPA_HWInfo* pHwInfo) const
{
    UNREFERENCED_PARAMETER(softwareCounterIndex);
    UNREFERENCED_PARAMETER(pHwInfo);

    if (nullptr != pResult)
    {
        gpa_uint64* pValue = static_cast<gpa_uint64*>(pResult);
        *pValue            = value;
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
    GPACounterSourceInfo info = GPACounterSourceInfo();

    if (m_doAllowPublicCounters)
    {
        if (globalIndex < m_publicCounters.GetNumCounters())
        {
            info.Set(globalIndex, GPACounterSource::PUBLIC);
            return info;
        }

        globalIndex -= m_publicCounters.GetNumCounters();
    }

    if (m_doAllowHardwareCounters)
    {
        if (globalIndex < m_hardwareCounters.GetNumCounters())
        {
            info.Set(globalIndex, GPACounterSource::HARDWARE);
            return info;
        }

        globalIndex -= m_hardwareCounters.GetNumCounters();
    }
    else if (m_doAllowHardwareExposedCounters)
    {
        if (globalIndex < m_hardwareCounters.GetNumHardwareExposedCounters())
        {
            info.Set(globalIndex, GPACounterSource::HARDWARE);
            return info;
        }

        globalIndex -= m_hardwareCounters.GetNumHardwareExposedCounters();
    }

    if (m_doAllowSoftwareCounters)
    {
        info.Set(globalIndex, GPACounterSource::SOFTWARE);
        return info;
    }

    /// Unknown counter
    info.Set(globalIndex, GPACounterSource::UNKNOWN);
    return info;
}
