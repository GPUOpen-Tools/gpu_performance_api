//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Context Counter Mediator Implementation
//==============================================================================

#include "GPAContextCounterMediator.h"
#include "GPACounterGenerator.h"

GPAContextCounterMediator* GPAContextCounterMediator::ms_pCounterManager = nullptr;

GPAContextCounterMediator* GPAContextCounterMediator::Instance()
{
    if (nullptr == ms_pCounterManager)
    {
        ms_pCounterManager = new (std::nothrow) GPAContextCounterMediator();
    }

    return ms_pCounterManager;
}

void GPAContextCounterMediator::DeleteInstance()
{
    delete ms_pCounterManager;
    ms_pCounterManager = nullptr;
}

GPAContextCounterMediator::~GPAContextCounterMediator()
{
    m_contextInfoMap.clear();
}

GPA_Status GPAContextCounterMediator::GenerateCounters(const IGPAContext* pGpaContext, GPA_OpenContextFlags flags, gpa_uint8 generateAsicSpecificCounters)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (DoesContextExist(pGpaContext))
    {
        return GPA_STATUS_ERROR_CONTEXT_ALREADY_OPEN;
    }

    GPA_Status            retStatus         = GPA_STATUS_OK;
    IGPACounterAccessor*  pCounterAccessor  = nullptr;
    IGPACounterScheduler* pCounterScheduler = nullptr;
    const GPA_HWInfo*     pHwInfo           = pGpaContext->GetHwInfo();

    if (nullptr == pHwInfo)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 vendorId;
    gpa_uint32 deviceId;
    gpa_uint32 revisionId;

    if (pHwInfo->GetVendorID(vendorId) && pHwInfo->GetDeviceID(deviceId) && pHwInfo->GetRevisionID(revisionId))
    {
        GPA_Status result = ::GenerateCounters(
            pGpaContext->GetAPIType(), vendorId, deviceId, revisionId, flags, generateAsicSpecificCounters, &pCounterAccessor, &pCounterScheduler);

        if (GPA_STATUS_OK == result)
        {
            GPAContextStatus contextStatus = {pCounterScheduler, pCounterAccessor};

            if (GPA_STATUS_OK == pCounterScheduler->SetCounterAccessor(pCounterAccessor, vendorId, deviceId, revisionId))
            {
                m_contextInfoMap.insert(GpaCtxStatusInfoPair(pGpaContext, contextStatus));
            }
            else
            {
                retStatus = GPA_STATUS_ERROR_FAILED;
                GPA_LogError("Failed to set counter accessor.");
            }
        }
    }
    else
    {
        retStatus = GPA_STATUS_ERROR_FAILED;
    }

    return retStatus;
}

bool GPAContextCounterMediator::IsCounterSchedulingSupported(const IGPAContext* pGpaContext) const
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return false;
    }

    return nullptr != m_contextInfoMap.at(pGpaContext).m_pCounterScheduler && nullptr != m_contextInfoMap.at(pGpaContext).m_pCounterAccessor;
}

IGPACounterAccessor* GPAContextCounterMediator::GetCounterAccessor(const IGPAContext* pGpaContext) const
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return nullptr;
    }

    return m_contextInfoMap.at(pGpaContext).m_pCounterAccessor;
}

GPA_Status GPAContextCounterMediator::ScheduleCounters(const IGPAContext*             pGpaContext,
                                                       const IGPASession*             pGpaSession,
                                                       const std::vector<gpa_uint32>& counterSet)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPASession* pActiveSession = pGpaContext->GetActiveSession();

    if (nullptr != pActiveSession && pGpaSession != pActiveSession)
    {
        return GPA_STATUS_ERROR_OTHER_SESSION_ACTIVE;
    }

    IGPACounterScheduler* pCounterScheduler = m_contextInfoMap.at(pGpaContext).m_pCounterScheduler;

    for (std::vector<gpa_uint32>::const_iterator it = counterSet.cbegin(); it != counterSet.cend(); ++it)
    {
        pCounterScheduler->EnableCounter(*it);
    }

    return GPA_STATUS_OK;
}

GPA_Status GPAContextCounterMediator::UnscheduleCounters(const IGPAContext*             pGpaContext,
                                                         const IGPASession*             pGpaSession,
                                                         const std::vector<gpa_uint32>& counterSet)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPASession* pActiveSession = pGpaContext->GetActiveSession();

    if (nullptr != pActiveSession && pGpaSession != pActiveSession)
    {
        return GPA_STATUS_ERROR_OTHER_SESSION_ACTIVE;
    }

    IGPACounterScheduler* pCounterScheduler = m_contextInfoMap.at(pGpaContext).m_pCounterScheduler;

    for (std::vector<gpa_uint32>::const_iterator it = counterSet.cbegin(); it != counterSet.cend(); ++it)
    {
        pCounterScheduler->DisableCounter(*it);
    }

    return GPA_STATUS_OK;
}

GPA_Status GPAContextCounterMediator::GetRequiredPassCount(const IGPAContext*             pGpaContext,
                                                           const std::vector<gpa_uint32>& counterSet,
                                                           unsigned int&                  passRequired)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    IGPACounterScheduler* pCounterScheduler = m_contextInfoMap.at(pGpaContext).m_pCounterScheduler;

    gpa_uint32 passReq = 0u;
    pCounterScheduler->DisableAllCounters();

    bool succeed = true;

    for (std::vector<gpa_uint32>::const_iterator it = counterSet.cbegin(); it != counterSet.cend() && succeed; ++it)
    {
        succeed &= GPA_STATUS_OK == pCounterScheduler->EnableCounter(*it);
    }

    if (!succeed)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    GPA_Status retStatus = pCounterScheduler->GetNumRequiredPasses(&passReq);

    if (GPA_STATUS_OK == retStatus)
    {
        passRequired = passReq;
    }

    return retStatus;
}

CounterResultLocationMap* GPAContextCounterMediator::GetCounterResultLocations(const IGPAContext* pGpaContext, const unsigned int& publicCounterIndex)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return nullptr;
    }

    IGPACounterScheduler* pCounterScheduler = m_contextInfoMap.at(pGpaContext).m_pCounterScheduler;

    if (nullptr == pCounterScheduler)
    {
        return nullptr;
    }

    return pCounterScheduler->GetCounterResultLocations(publicCounterIndex);
}

void GPAContextCounterMediator::RemoveContext(IGPAContext* pGpaContext)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (DoesContextExist(pGpaContext))
    {
        m_contextInfoMap.erase(pGpaContext);
    }
}

CounterList* GPAContextCounterMediator::GetCounterForPass(IGPAContext* pGpaContext, PassIndex passIndex)
{
    std::lock_guard<std::mutex> lock(m_contextInfoMapMutex);

    if (!DoesContextExist(pGpaContext))
    {
        return nullptr;
    }

    IGPACounterScheduler* pCounterScheduler = m_contextInfoMap[pGpaContext].m_pCounterScheduler;

    if (nullptr == pCounterScheduler)
    {
        return nullptr;
    }

    return pCounterScheduler->GetCountersForPass(passIndex);
}

bool GPAContextCounterMediator::DoesContextExist(const IGPAContext* pGpaContext) const
{
    return m_contextInfoMap.find(pGpaContext) != m_contextInfoMap.cend();
}
