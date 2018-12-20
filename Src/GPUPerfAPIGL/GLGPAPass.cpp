//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL GPA Pass Object Implementation
//==============================================================================

#include "GLGPAPass.h"
#include "GLGPACommandList.h"
#include "GLGPASample.h"
#include "GPAHardwareCounters.h"
#include "GPAContextCounterMediator.h"

GLGPAPass::GLGPAPass(IGPASession* pGpaSession,
                     PassIndex passIndex,
                     GPACounterSource counterSource,
                     CounterList* pPassCounters):
                     GPAPass(pGpaSession, passIndex, counterSource, pPassCounters)
{
    EnableAllCountersForPass();
}

GLGPAPass::~GLGPAPass()
{
    for (auto  iter = m_glPerfMonitorInfoList.begin();
         iter != m_glPerfMonitorInfoList.end(); ++iter)
    {
        iter->second.Clear(true);
    }
}

GPASample* GLGPAPass::CreateAPISpecificSample(IGPACommandList* pCmdList,
                                              GpaSampleType sampleType,
                                              ClientSampleId sampleId)
{
    GPASample* pRetSample = nullptr;

    GLGPASample* pGLGpaSample = new(std::nothrow) GLGPASample(this,
                                                              pCmdList,
                                                              sampleType,
                                                              sampleId);

    if (nullptr == pGLGpaSample)
    {
        GPA_LogError("Unable to allocate memory for the sample.");
    }
    else
    {
        pRetSample = pGLGpaSample;
    }

    return pRetSample;

}

bool GLGPAPass::ContinueSample(ClientSampleId srcSampleId,
                               IGPACommandList* pPrimaryGpaCmdList)
{
    // continuing samples not supported for OpenGL
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(pPrimaryGpaCmdList);
    return false;
}

IGPACommandList* GLGPAPass::CreateAPISpecificCommandList(void* pCmd,
                                                         CommandListId commandListId,
                                                         GPA_Command_List_Type cmdType)
{
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);

    GLGPACommandList* pRetCmdList = new(std::nothrow) GLGPACommandList(GetGpaSession(), this, commandListId);
    return pRetCmdList;
}

bool GLGPAPass::EndSample(IGPACommandList* pCmdList)
{
    bool retVal = false;

    if (nullptr != pCmdList)
    {
        retVal = pCmdList->CloseLastSample();
    }

    return retVal;
}

bool GLGPAPass::GetPerfMonitor(GLPerfMonitorId& glPerfMonitorId)
{
    bool success = false;
    bool perfMonitorAvailable = false;

    GLPerfMonitor glPerfMonitorFound;

    if (!m_glPerfMonitorInfoList.empty())
    {
        for (auto perfMonitorListConstIter = m_glPerfMonitorInfoList.cbegin();
             perfMonitorListConstIter != m_glPerfMonitorInfoList.cend();
             ++perfMonitorListConstIter)
        {
            if (perfMonitorListConstIter->second.IsDataCollected())
            {
                perfMonitorAvailable = true;
                glPerfMonitorFound = perfMonitorListConstIter->second;
                success = true;
                break;
            }
        }
    }

    if (!perfMonitorAvailable)
    {
        GLPerfMonitor newPerfMonitor;

        if (newPerfMonitor.Initialize())
        {
            GLPerfMonitorId newPerfMonitorId = newPerfMonitor.GetPerfMonitorId();

            if (InitializeCounters(newPerfMonitorId))
            {
                m_glPerfMonitorInfoList.insert(std::pair<GLPerfMonitorId, GLPerfMonitor>(newPerfMonitorId, newPerfMonitor));
                success = true;
                glPerfMonitorFound = newPerfMonitor;
            }
        }
    }

    if (success)
    {
        glPerfMonitorId = glPerfMonitorFound.GetPerfMonitorId();
        glPerfMonitorFound.AddRef();
    }

    return success;
}

void GLGPAPass::MarkDataCollected(const GLPerfMonitorId glPerfMonitorId)
{
    m_glPerfMonitorInfoList.at(glPerfMonitorId).Release();
}

const GLCounter* GLGPAPass::GetGLCounter(const GLuint& counterGroup,
                                         const GLuint& counterIndex,
                                         unsigned int& indexOfCounterWithinPass) const
{
    const GLCounter* pRetGlCounter = nullptr;
    unsigned int counterIndexWithinPass = 0;
    bool found = false;

    for (auto glCounterIter = m_glCounterList.cbegin();
         glCounterIter != m_glCounterList.cend();
         ++glCounterIter)
    {
        if (glCounterIter->m_counterGroup == counterGroup &&
            glCounterIter->m_counterIndex == counterIndex)
        {
            found = true;
            break;
        }

        counterIndexWithinPass++;
    }

    if (found)
    {
        pRetGlCounter = &(m_glCounterList.data()[counterIndexWithinPass]);
        indexOfCounterWithinPass = counterIndexWithinPass;
    }

    return pRetGlCounter;
}

bool GLGPAPass::InitializeCounters(const GLPerfMonitorId& glPerfMonitorId)
{
    bool isSuccessFul = true;

    auto EnableCounter = [&](const CounterIndex& counterIndex) ->bool
    {
        bool isCounterEnabled = false;
        // need to Enable counters
        IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext());
        const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();
        const GPA_HardwareCounterDescExt* pCounter = pCounterAccessor->GetHardwareCounterExt(counterIndex);

        unsigned int uGroupIndex = pCounter->m_groupIndex;

        GLint nCounters = 0;

        if (uGroupIndex < pHardwareCounters->m_groupCount)
        {
            nCounters = static_cast<GLint>(pHardwareCounters->m_pGroups[uGroupIndex].m_numCounters);
        }
        else
        {
            nCounters = static_cast<GLint>(pHardwareCounters->m_pAdditionalGroups[uGroupIndex - pHardwareCounters->m_groupCount].m_numCounters);
        }

        assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= static_cast<unsigned int>(nCounters));

        // validate Counter result type
        GLuint resultType = 0;
        oglUtils::_oglGetPerfMonitorCounterInfoAMD(pCounter->m_groupIdDriver, static_cast<GLuint>(pCounter->m_pHardwareCounter->m_counterIndexInGroup), GL_COUNTER_TYPE_AMD, &resultType);

        if (!oglUtils::CheckForGLError("GetPerfMonitorCounterInfoAMD throws an Error."))
        {
            oglUtils::_oglSelectPerfMonitorCountersAMD(glPerfMonitorId,
            GL_TRUE,
            pCounter->m_groupIdDriver,
            1,
            reinterpret_cast<GLuint*>(&pCounter->m_pHardwareCounter->m_counterIndexInGroup));

            if (!oglUtils::CheckForGLError("Unable to enable counter in GL driver."))
            {
                isCounterEnabled = true;
            }
        }
        else
        {
            char groupName[256];
            char counterName[256];
            memset(groupName, 0, 256);
            memset(counterName, 0, 256);
            GLsizei nLength = 0;

            if (uGroupIndex <= (pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount))
            {
                oglUtils::_oglGetPerfMonitorGroupStringAMD(pCounter->m_groupIdDriver, 256, &nLength, groupName);

                if (oglUtils::CheckForGLError("glGetPerfMonitorGroupStringAMD failed getting group name."))
                {
                    return false;
                }
            }

            if (pCounter->m_pHardwareCounter->m_counterIndexInGroup <= static_cast<unsigned int>(nCounters))
            {
                oglUtils::_oglGetPerfMonitorCounterStringAMD(pCounter->m_groupIdDriver,
                                                             static_cast<GLuint>(pCounter->m_pHardwareCounter->m_counterIndexInGroup),
                                                             256,
                                                             &nLength,
                                                             counterName);

                oglUtils::CheckForGLError("glGetPerfMonitorCounterStringAMD failed getting counter name.");
            }

        }

        isSuccessFul &= isCounterEnabled;

        if (isCounterEnabled)
        {
            GLCounter glCounter;
            glCounter.m_counterType = resultType;
            glCounter.m_counterID = counterIndex;
            glCounter.m_counterGroup = pCounter->m_groupIdDriver;
            glCounter.m_counterIndex = static_cast<GLuint>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
            m_glCounterList.push_back(glCounter);
        }

        return isCounterEnabled;
    };

    IterateEnabledCounterList(EnableCounter);

    return isSuccessFul;
}

GLGPAPass::GLPerfMonitor::GLPerfMonitor():
    m_glPerfMonitorId(0u),
    m_refCount(0u)
{
}

bool GLGPAPass::GLPerfMonitor::Initialize()
{
    // Create perf monitor
    oglUtils::_oglGenPerfMonitorsAMD(1, &m_glPerfMonitorId);
    return !oglUtils::CheckForGLError("Unable to create AMD PerfMonitor GL extension.");
}

GLPerfMonitorId GLGPAPass::GLPerfMonitor::GetPerfMonitorId() const
{
    return m_glPerfMonitorId;
}

bool GLGPAPass::GLPerfMonitor::IsDataCollected() const
{
    // Even count will have no pending results
    return (m_refCount % 2 == 0);
}

unsigned int GLGPAPass::GLPerfMonitor::AddRef()
{
    return ++m_refCount;
}

unsigned int GLGPAPass::GLPerfMonitor::Release()
{
    return --m_refCount;
}

bool GLGPAPass::GLPerfMonitor::Clear(bool forceClear)
{
    if (!forceClear && m_refCount != 0)
    {
        return false;
    }

    oglUtils::_oglDeletePerfMonitorsAMD(1, &m_glPerfMonitorId);
    return !oglUtils::CheckForGLError("Unable to delete AMD GL extension perf monitor.");
}

