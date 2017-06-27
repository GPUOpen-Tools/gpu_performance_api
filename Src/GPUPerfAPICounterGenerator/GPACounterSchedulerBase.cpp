//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Base Class for counter scheduling
//==============================================================================

#include "GPACounterSchedulerBase.h"
#include "GPAICounterScheduler.h"
#include "GPACounterGeneratorBase.h"
#include "Logging.h"
#include <sstream>
#include <vector>
#include <list>
#include <DeviceInfoUtils.h>

GPA_CounterSchedulerBase::GPA_CounterSchedulerBase()
    : m_counterSelectionChanged(false),
      m_pCounterAccessor(nullptr),
      m_passIndex(0)
{
}

GPA_CounterSchedulerBase::~GPA_CounterSchedulerBase()
{
}

void GPA_CounterSchedulerBase::Reset()
{
    DisableAllCounters();
    m_passIndex = 0;
    m_pCounterAccessor = nullptr;
    m_counterSelectionChanged = false;
}

GPA_Status GPA_CounterSchedulerBase::SetCounterAccessor(GPA_ICounterAccessor* pCounterAccessor, gpa_uint32 vendorId, gpa_uint32 deviceId, gpa_uint32 revisionId)
{
    if (nullptr == pCounterAccessor)
    {
        GPA_LogError("Parameter 'pCounterAccessor' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    m_pCounterAccessor = pCounterAccessor;
    m_vendorId = vendorId;
    m_deviceId = deviceId;
    m_revisionId = revisionId;

    // make sure there are enough bits to track the enabled counters
    m_enabledPublicCounterBits.resize(pCounterAccessor->GetNumCounters());
    fill(m_enabledPublicCounterBits.begin(), m_enabledPublicCounterBits.end(), false);

    return GPA_STATUS_OK;
}

gpa_uint32 GPA_CounterSchedulerBase::GetNumEnabledCounters()
{
    return (gpa_uint32)m_enabledPublicIndices.size();
}

GPA_Status GPA_CounterSchedulerBase::EnableCounter(gpa_uint32 index)
{
    // see if counter already enabled
    #pragma region Check using only m_enabledPublicIndices
    //   for (gpa_uint32 i = 0; i < (gpa_uint32)m_enabledPublicIndices.size(); i++)
    //   {
    //      if (m_enabledPublicIndices[i] == index)
    //      {
    //         return GPA_STATUS_ERROR_ALREADY_ENABLED;
    //      }
    //   }
    #pragma endregion
    if (m_enabledPublicCounterBits[index])
    {
        std::stringstream message;
        message << "Counter index " << index << " has already been enabled.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_ALREADY_ENABLED;
    }

    m_enabledPublicIndices.push_back(index);
    m_enabledPublicCounterBits[index] = true;
    m_counterSelectionChanged = true;

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterSchedulerBase::DisableCounter(gpa_uint32 index)
{
    // see if counter enabled
    for (int i = 0 ; i < (int)m_enabledPublicIndices.size() ; i++)
    {
        if (m_enabledPublicIndices[i] == index)
        {
            m_enabledPublicIndices.erase(m_enabledPublicIndices.begin() + i);

            if (GPA_STATUS_OK == DoDisableCounter(index))
            {
                m_counterSelectionChanged = true;
                return GPA_STATUS_OK;
            }
        }
    }

    std::stringstream message;
    message << "Counter index " << index << " was not previously enabled, so it could not be disabled.";
    GPA_LogError(message.str().c_str());
    return GPA_STATUS_ERROR_NOT_ENABLED;
}

void GPA_CounterSchedulerBase::DisableAllCounters()
{
    m_enabledPublicIndices.clear();
    fill(m_enabledPublicCounterBits.begin(), m_enabledPublicCounterBits.end(), false);
    m_counterSelectionChanged = true;
}

GPA_Status GPA_CounterSchedulerBase::GetEnabledIndex(gpa_uint32 enabledIndex, gpa_uint32* pCounterAtIndex)
{
    if (enabledIndex >= static_cast<gpa_uint32>(m_enabledPublicIndices.size()))
    {
        std::stringstream message;
        message << "Parameter 'enabledNumber' is " << enabledIndex << " but must be less than the number of enabled counters (" << m_enabledPublicIndices.size() << ").";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    (*pCounterAtIndex) = static_cast<gpa_uint32>(m_enabledPublicIndices[enabledIndex]);

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterSchedulerBase::IsCounterEnabled(gpa_uint32 counterIndex)
{
    if (counterIndex >= m_enabledPublicCounterBits.size())
    {
        std::stringstream message;
        message << "Parameter 'counterIndex' is " << counterIndex << " but must be less than the number of enabled counters (" << m_enabledPublicCounterBits.size() << ").";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (m_enabledPublicCounterBits[counterIndex])
    {
        return GPA_STATUS_OK;
    }
    else
    {
        std::stringstream message;
        message << "Parameter 'counterIndex' (" << counterIndex << ") is not an enabled counter.";
        GPA_LogMessage(message.str().c_str());
        return GPA_STATUS_ERROR_NOT_FOUND;
    }

    #pragma region Previous method based on only using the enabled index list
#if 0
    gpa_uint32 count = 0;
    GPA_Status result = GPA_GetEnabledCount(&count);

    if (result != GPA_STATUS_OK)
    {
        return result;
    }

    for (gpa_uint32 i = 0 ; i < count ; i++)
    {
        gpa_uint32 enabledCounterIndex;
        result = GetEnabledIndex(i, &enabledCounterIndex);

        if (result != GPA_STATUS_OK)
        {
            return result;
        }

        if (enabledCounterIndex == counterIndex)
        {
            return GPA_STATUS_OK;
        }
    }

#endif
    #pragma endregion

}

GPA_Status GPA_CounterSchedulerBase::GetNumRequiredPasses(gpa_uint32* pNumRequiredPassesOut)
{
    if (!m_counterSelectionChanged)
    {
        *pNumRequiredPassesOut = (gpa_uint32)m_passPartitions.size();
        return GPA_STATUS_OK;
    }

    GPA_CounterGeneratorBase* pGenerator = reinterpret_cast<GPA_CounterGeneratorBase*>(m_pCounterAccessor);

    if (nullptr == pGenerator)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    GPA_HardwareCounters* pHWCounters = pGenerator->GetHardwareCounters();

    unsigned int numSQMaxCounters = 0;

    GDT_DeviceInfo deviceInfo;

    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(m_deviceId, m_revisionId, deviceInfo))
    {
        numSQMaxCounters = static_cast<unsigned int>(deviceInfo.m_nNumSQMaxCounters);
    }

    IGPASplitCounters* pSplitter = GPASplitCounterFactory::GetNewCounterSplitter(GetPreferredSplittingAlgorithm(),
                                   pHWCounters->m_gpuTimeIndex,
                                   pHWCounters->m_gpuTimeBottomToBottomCounterIndex,
                                   pHWCounters->m_gpuTimeTopToBottomCounterIndex,
                                   numSQMaxCounters,
                                   pHWCounters->m_sqGroupCount,
                                   pHWCounters->m_pSQCounterGroups);

    if (nullptr == pSplitter)
    {
        GPA_LogError("Failed to create a counter splitting algorithm.");
        return GPA_STATUS_ERROR_FAILED;
    }

    // build the list of counters to split
    std::vector<const GPA_PublicCounter*> publicCountersToSplit;
    std::vector<GPAHardwareCounterIndices> internalCountersToSchedule;
    std::vector<GPASoftwareCounterIndices> softwareCountersToSchedule;

    for (std::vector<gpa_uint32>::iterator counterIter = m_enabledPublicIndices.begin(); counterIter != m_enabledPublicIndices.end(); ++counterIter)
    {
        GPACounterTypeInfo info = m_pCounterAccessor->GetCounterTypeInfo(*counterIter);

        switch (info.m_counterType)
        {
            case PUBLIC_COUNTER:
            {
                publicCountersToSplit.push_back(m_pCounterAccessor->GetPublicCounter(*counterIter));
                break;
            }

            case HARDWARE_COUNTER:
            {
                // hardware counter
                std::vector<unsigned int> requiredCounters = m_pCounterAccessor->GetInternalCountersRequired(*counterIter);
                assert(requiredCounters.size() == 1);

                if (requiredCounters.size() == 1)
                {
                    GPAHardwareCounterIndices indices;
                    indices.m_publicIndex = *counterIter;
                    indices.m_hardwareIndex = requiredCounters[0];
                    internalCountersToSchedule.push_back(indices);
                }

                break;
            }

            case SOFTWARE_COUNTER:
#if defined(WIN32)
                {
                    // software counter
                    std::vector<unsigned int> requiredCounters = m_pCounterAccessor->GetInternalCountersRequired(*counterIter);
                    assert(requiredCounters.size() == 1);

                    if (requiredCounters.size() == 1)
                    {
                        GPASoftwareCounterIndices indices;
                        indices.m_publicIndex = *counterIter;

                        indices.m_softwareIndex = requiredCounters[0] + pHWCounters->GetNumCounters(); // Add the number of HW counters so that the SW counters in effect are after the end of the HW counters

                        softwareCountersToSchedule.push_back(indices);
                    }

                    break;
                }

#endif

            case UNKNOWN_COUNTER:
            default:
            {
                // do something sensible
                GPA_LogError("UNKNOWN_COUNTER.");
                return GPA_STATUS_ERROR_FAILED;
            }

        }
    }

    // Get the Sw counters
    GPA_SoftwareCounters* pSWCounters = pGenerator->GetSoftwareCounters();

    // build the list of max counters per group (includes both hardware and software groups)
    std::vector<unsigned int> maxCountersPerGroup;

    // Create space for the number of HW and SW groups
    maxCountersPerGroup.reserve(pHWCounters->m_groupCount + pHWCounters->m_additionalGroupCount + pSWCounters->m_groupCount);

    // Add the HW groups max's
    for (unsigned int i = 0; i < pHWCounters->m_groupCount; ++i)
    {
        maxCountersPerGroup.push_back(pHWCounters->m_pGroups[i].m_maxActiveCounters);
    }

    // Add the Additional groups max's
    for (unsigned int i = 0; i < pHWCounters->m_additionalGroupCount; ++i)
    {
        maxCountersPerGroup.push_back(pHWCounters->m_pAdditionalGroups[i].m_maxActiveCounters);
    }

    // TODO: properly handle software groups -- right now, this works because there is only ever a single group defined
    if (pSWCounters->m_groupCount == 1)
    {
        maxCountersPerGroup.push_back(DoGetNumSoftwareCounters());
    }

    GPACounterGroupAccessor accessor(pHWCounters->m_pGroups,
                                     pHWCounters->m_groupCount,
                                     pHWCounters->m_pAdditionalGroups,
                                     pHWCounters->m_additionalGroupCount,
                                     pSWCounters->m_pGroups,
                                     pSWCounters->m_groupCount);

    unsigned int numInternalCountersScheduled = 0;

    m_passPartitions = pSplitter->SplitCounters(publicCountersToSplit,
                                                internalCountersToSchedule,
                                                softwareCountersToSchedule,
                                                (IGPACounterAccessor*)&accessor,
                                                maxCountersPerGroup,
                                                numInternalCountersScheduled);

    m_counterResultLocationMap = pSplitter->GetCounterResultLocations();

    delete pSplitter;
    pSplitter = nullptr;

    m_counterSelectionChanged = false;
    *pNumRequiredPassesOut = (gpa_uint32)m_passPartitions.size();

    return GPA_STATUS_OK;
}

bool GPA_CounterSchedulerBase::GetCounterSelectionChanged()
{
    return m_counterSelectionChanged;
}

GPA_Status GPA_CounterSchedulerBase::BeginProfile()
{
    m_passIndex = 0;
    m_counterSelectionChanged = false;

    return DoBeginProfile();
}

void GPA_CounterSchedulerBase::BeginPass()
{
    DoBeginPass();

    m_passIndex++;
}

std::vector<unsigned int>* GPA_CounterSchedulerBase::GetCountersForPass(gpa_uint32 passIndex)
{
    auto iter = m_passPartitions.begin();
    unsigned int i = 0;

    while (i < passIndex)
    {
        iter++;
        i++;
    }

    return &(iter->m_counters);
}

void GPA_CounterSchedulerBase::EndPass()
{
    DoEndPass();
}

GPA_Status GPA_CounterSchedulerBase::EndProfile()
{
    if (m_passIndex < m_passPartitions.size())
    {
        return GPA_STATUS_ERROR_NOT_ENOUGH_PASSES;
    }

    return DoEndProfile();
}

CounterResultLocationMap* GPA_CounterSchedulerBase::GetCounterResultLocations(unsigned int publicCounterIndex)
{
    auto iter = m_counterResultLocationMap.find(publicCounterIndex);

    if (iter != m_counterResultLocationMap.end())
    {
        return &(iter->second);
    }

    return nullptr;
}

void GPA_CounterSchedulerBase::SetDrawCallCounts(const int iCounts)
{
    DoSetDrawCallCounts(iCounts);
}

GPA_Status GPA_CounterSchedulerBase::DoDisableCounter(gpa_uint32 index)
{
    m_enabledPublicCounterBits[index] = false;
    return GPA_STATUS_OK;
}

gpa_uint32 GPA_CounterSchedulerBase::DoGetNumSoftwareCounters()
{
    gpa_uint32 retVal = 0;

    GPA_CounterGeneratorBase* pGenerator = reinterpret_cast<GPA_CounterGeneratorBase*>(m_pCounterAccessor);

    if (nullptr != pGenerator)
    {
        GPA_SoftwareCounters* pSwCounters = pGenerator->GetSoftwareCounters();

        if (nullptr != pSwCounters)
        {
            retVal = static_cast<gpa_uint32>(pSwCounters->m_counters.size());
        }
    }

    return retVal;
}

GPA_Status GPA_CounterSchedulerBase::DoBeginProfile()
{
    // do nothing in base class
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterSchedulerBase::DoEndProfile()
{
    // do nothing in base class
    return GPA_STATUS_OK;
}

void GPA_CounterSchedulerBase::DoBeginPass()
{
    // do nothing in base class
}

void GPA_CounterSchedulerBase::DoEndPass()
{
    // do nothing in base class
}

void GPA_CounterSchedulerBase::DoSetDrawCallCounts(const int iCount)
{
    UNREFERENCED_PARAMETER(iCount);
    // do nothing in base
}

