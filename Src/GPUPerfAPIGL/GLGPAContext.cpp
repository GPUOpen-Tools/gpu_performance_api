//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA GL Context Implementation
//==============================================================================

#include "GLGPAContext.h"
#include "GPAUniqueObject.h"
#include "GLGPASession.h"
#include "GPAHardwareCounters.h"

GLGPAContext::GLGPAContext(GLContextPtr context,
                           GPA_HWInfo& pHwInfo,
                           GPA_OpenContextFlags contextFlags) :
    GPAContext(pHwInfo, contextFlags),
    m_glContext(context)
{
}

GPA_SessionId GLGPAContext::CreateSession()
{
    GPA_SessionId pRetSessionId = nullptr;

    GLGPASession* pNewGpaGLGpaSession = new(std::nothrow) GLGPASession(this);

    if (nullptr == pNewGpaGLGpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewGpaGLGpaSession);

        if (nullptr != pNewGpaGLGpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaGLGpaSession));
        }
    }

    return pRetSessionId;
}

bool GLGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    GLGPASession* pGLSession = reinterpret_cast<GLGPASession*>(sessionId->Object());

    if (nullptr != pGLSession)
    {
        RemoveGpaSession(pGLSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pGLSession);
        delete pGLSession;
        isDeleted = true;
    }

    return isDeleted;
}

gpa_uint32 GLGPAContext::GetMaxGPASessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GPA_API_Type GLGPAContext::GetAPIType() const
{
    return GPA_API_OPENGL;
}

bool GLGPAContext::Initialize()
{
    bool success = OpenCounters() && ValidateAndUpdateGLCounters();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}
const GLContextPtr& GLGPAContext::GetGLContext() const
{
    return m_glContext;
}

bool GLGPAContext::ValidateAndUpdateGLCounters() const
{
    bool success = false;
    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;
    gpa_uint32 deviceId = 0;
    gpa_uint32 revisionId = 0;
    gpa_uint32 vendorId = 0;

    GPA_HWInfo hwInfo = *(GetHwInfo());

    if (!hwInfo.GetHWGeneration(generation) &&
        !hwInfo.GetDeviceID(deviceId) &&
        !hwInfo.GetVendorID(vendorId) &&
        !hwInfo.GetRevisionID(revisionId))
    {
        GPA_LogError("Unable to get necessary hardware info.");
    }
    else if (hwInfo.IsAMD())
    {
        // Query the GL API to get the hardware counter group names and Ids so that the expected groups can be verified and the group Ids can be updated.

        // Get the number of performance counter groups
        GLint nNumGroups;
        _oglGetPerfMonitorGroupsAMD(&nNumGroups, 0, nullptr);

        assert(nNumGroups > 0);

        if (nNumGroups == 0)
        {
            GPA_LogError("No counter groups are exposed by GL_AMD_performance_monitor.");
        }
        else
        {
            // const_cast is the feasible and simple workaround here, as GL is the only API in which we are changing the hardware counter info
            GPA_HardwareCounters* pHardwareCounters = const_cast<GPA_HardwareCounters*>(GetCounterAccessor()->GetHardwareCounters());
            unsigned int expectedDriverGroups = pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount - 1;

            if (nNumGroups < static_cast<int>(expectedDriverGroups))
            {
                // We should not proceed if the driver exposes less groups that we expect
                std::stringstream error;
                error << "GL_AMD_performance_monitor exposes " << nNumGroups << " counter groups, but GPUPerfAPI requires at least " << static_cast<int>(expectedDriverGroups) << ".";
                GPA_LogError(error.str().c_str());
            }
            else
            {
                if (nNumGroups > static_cast<int>(expectedDriverGroups))
                {
                    // report an error if the driver exposes more groups than we expect, but allow the code to continue.
                    std::stringstream error;
                    error << "GL_AMD_performance_monitor exposes " << nNumGroups << " counter groups, but GPUPerfAPI expected " << static_cast<int>(expectedDriverGroups) << ".";
                    GPA_LogError(error.str().c_str());
                }

                // Get the group Ids
                GLuint* pPerfGroups = new(std::nothrow) GLuint[nNumGroups];

                if (nullptr == pPerfGroups)
                {
                    GPA_LogError("Unable to allocate memory to store the group IDs.");
                }
                else
                {
                    _oglGetPerfMonitorGroupsAMD(nullptr, nNumGroups, pPerfGroups);

                    // declare this outside the loops
                    std::vector<GPA_HardwareCounterDescExt>::iterator internalCounterIter = pHardwareCounters->m_counters.begin();

                    int driverGroupNum = -1;

                    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
                    for (int g = 0; g < static_cast<int>(pHardwareCounters->m_groupCount); g++)
                    {
                        driverGroupNum++;
                        char strName[64] = {};
                        GLint nCounters = 0;
                        GLint nMaxActive = 0;

                        // Get the group name
                        if (g < nNumGroups)
                        {
                            _oglGetPerfMonitorGroupStringAMD(pPerfGroups[driverGroupNum], 64, nullptr, strName);

                            // Get the number of counters and max active counters
                            _oglGetPerfMonitorCountersAMD(pPerfGroups[driverGroupNum], &nCounters, &nMaxActive, 0, nullptr);

                            if (generation == GDT_HW_GENERATION_SEAISLAND && strncmp(strName, "TCS", 64) == 0)
                            {
                                // skip the TCS counter group because it is only exposed on Kabini and GPA GL does not currently support it.
                                GPA_LogMessage("Skipping TCS group.");
                                driverGroupNum++;
                                _oglGetPerfMonitorGroupStringAMD(pPerfGroups[driverGroupNum], 64, nullptr, strName);

                                // Get the number of counters and max active counters
                                _oglGetPerfMonitorCountersAMD(pPerfGroups[driverGroupNum], &nCounters, &nMaxActive, 0, nullptr);
                            }

                            // validate the values
                            if (strncmp(pHardwareCounters->m_pGroups[g].m_pName, "GPUTime", 8) == 0)
                            {
                                // ignore the GPUTime group -- it is not explicitly exposed by the driver -- it is handled separately by GPA
                                // we break here because GPUTime is always the last group exposed by GPA
                                break;
                            }
                            else if (strncmp(pHardwareCounters->m_pGroups[g].m_pName, strName, 64) != 0)
                            {
                                std::stringstream error;
#ifndef GLES
                                error << "GPUPerfAPI's group name '" << pHardwareCounters->m_pGroups[g].m_pName << "' does not match the OpenGL returned name of '" << strName << "'.";
#else
                                error << "GPUPerfAPI's group name '" << pHardwareCounters->m_pGroups[g].m_pName << "' does not match the OpenGL ES returned name of '" << strName << "'.";
#endif // GLES
                                GPA_LogError(error.str().c_str());
                            }
                            else
                            {
                                // only check for later errors if the group name is the same. If the group name is different, we expect these other two errors to happen also,
                                // so there is no reason to check for them.

                                if (generation == GDT_HW_GENERATION_SOUTHERNISLAND && strncmp(strName, "WM_MD", 64) == 0)
                                {
                                    // For SI, the driver exposes WM_MD with 36 counters, but it really only has 6, so change this number
                                    nCounters = 6;
                                }

                                // Make sure GPA and the driver have same number of counters.
                                // There will be no catastrophic errors if the GPA expects less counters than GL exposes, but we may not have the right counters... and may be reporting bad results.
                                // There could be major issues if the GPA expects more counters than GL exposes, because we may try to enable a counter that doesn't exist,
                                // in which case we hope the driver will return a 0 result and not write unexpected values into the register.

                                // TODO: Temporarily disabling this - SWDEV-143627
                                /*
                                 *assert(pHardwareCounters->m_pGroups[g].m_numCounters == static_cast<unsigned int>(nCounters));

                                if (pHardwareCounters->m_pGroups[g].m_numCounters != static_cast<unsigned int>(nCounters))
                                {
                                    std::stringstream error;
                                    error << "GPUPerfAPI's group '" << pHardwareCounters->m_pGroups[g].m_pName << "' has " << pHardwareCounters->m_pGroups[g].m_numCounters << " counters, but OpenGL exposes '" << nCounters << ".";

                                    if (pHardwareCounters->m_pGroups[g].m_numCounters < static_cast<unsigned int>(nCounters))
                                    {
                                        // log as a message, because this isn't so bad
                                        GPA_LogMessage(error.str().c_str());
                                    }
                                    else
                                    {
                                        // log as an error, because we should definitely fix this
                                        GPA_LogError(error.str().c_str());
                                    }
                                }

                                // This assert is good for debugging, but it will fire on most EG cards, because we "expect" SQ to have 8 max counters on cypress (high end), but
                                // we know that it will actually have less on lower end EG cards, and the driver returns the correct values, so our 8 != what the driver returns.
                                //assert( pHardwareCounters->Groups[g].maxActiveCounters == (unsigned int)nMaxActive );
                                */
                            }
                        }

                        // update the group Id based on what was returned from the driver
                        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

                        for (unsigned int c = 0; c < numCountersInGroup; c++)
                        {
                            internalCounterIter->m_groupIdDriver = pPerfGroups[driverGroupNum];

                            if (internalCounterIter != pHardwareCounters->m_counters.end())
                            {
                                ++internalCounterIter;
                            }
                        }
                    }

                    delete[] pPerfGroups;
                    success = true;
                }
            }
        }
    }

    return success;
}

